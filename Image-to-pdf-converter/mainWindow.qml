import QtQuick 2.2
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.3

ApplicationWindow {
    id: win

    Material.theme: Material.Dark
    Material.accent: Material.Purple

    visible: true
    width: 640
    height: 480
    minimumWidth: 640
    minimumHeight: 480

    title: "Image to pdf converter"

    // окно проводника для  выбора изображений
    FileDialog {
        id: openFiles
        title: "Converter - Add image"
        nameFilters: ["Image files (*.png *.jpg *.jpeg *.gif)"]
        folder: shortcuts.pictures
        selectMultiple: true
        onAccepted: {
            actions.addImg(Array.from(openFiles.fileUrls))
            img.source = actions.getCurImg();
        }
    }

    //кнопки Add и Delete
    Row{
        spacing: 5
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottomMargin: 5
        Button {
            text: "Add image"
            width: 130
            height: 50
            onClicked: {
                openFiles.open()
            }
        }
        Button {
            text: "Delete image"
            width: 130
            height: 50
            onClicked: {
                img.source = actions.deleteImg()
            }
        }
    }

    //кнопка конвертации
    Button {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottomMargin: 5
        text: "Convert"
        width: 130
        height: 50
        onClicked: {
            if (actions.checkListOfImg()) {
                fileDialog.open()
            }
            else {
                messageDialog.open()
            }
        }
    }

    //Текущие отображаемое изображение
    Image {
        property color btnColor: Qt.rgba(26 / 255, 29 / 255, 50 / 255, 0.3)

        id: img
        width: parent.width - 10
        height: parent.height - 100
        
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 5
        anchors.topMargin: 5
        source: actions.getCurImg()

        DropArea {
            id: dropArea

            anchors.fill: parent
            keys: ["text/uri-list"]

            // Проверка списка url ссылок на то, что они являются изображениями
            function isImgList(drop) {
                drop.accepted = false;
                if (actions.isImgList(Array.from(drop.urls))) {
                    drop.accepted = true;
                }
            }

            onDropped: (drop) => {
                actions.dropEvent(Array.from(drop.urls));
                img.source = actions.getCurImg();
            }

            onEntered: (drop) => {
                isImgList(drop);
            }

            onPositionChanged: (drop) => {
                isImgList(drop);
            }
        }

        // Кнопка переключения на следующее изображение
        Rectangle {
            id: nextImgBtn

            width: 40
            height: parent.height

            anchors.right: parent.right
            anchors.top: parent.top

            
            color: nextBtnMsArea.containsPress ? Qt.darker(img.btnColor, 3) : img.btnColor

            Text {
                text: ">"
                anchors.centerIn: parent
                color: "white"
                font.pixelSize: 25
            }

            MouseArea {
                id: nextBtnMsArea
                anchors.fill: parent

                onClicked: {
                    img.source = actions.getNextImg()
                }
            }
        }

        // Кнопка переключения на предыдущие изображение
        Rectangle {
            id: prevImgBtn

            width: 40
            height: parent.height

            anchors.left: parent.left
            anchors.top: parent.top

            color: prevBtnMsArea.containsPress ? Qt.darker(img.btnColor, 3) : img.btnColor

            Text {
                text: "<"
                anchors.centerIn: parent
                color: "white"
                font.pixelSize: 25
            }

            MouseArea {
                id: prevBtnMsArea
                anchors.fill: parent

                onClicked: {
                    img.source = actions.getPrevImg()
                }
            }
        }
    }

    // Диалог сохранения файла в формате pdf
    FileDialog {
        id: fileDialog
        title: "Save as pdf"
        folder: shortcuts.documents
        selectExisting: false
        nameFilters: ["pdf (*.pdf)"]

        onAccepted: {
            actions.convert(fileDialog.fileUrl)
        }
    }

    // Окно ошибки, появляющиеся, если кнопка "convert" нажата, а изображения не выбраны
    MessageDialog {
        id: messageDialog
        title: "Error!"
        text: "You have not selected images to convert."
        icon: StandardIcon.Critical
        standardButtons: StandardButton.Cancel
    }
}
