<?php

function vid_structure($conn, $table){
    $header = "<h4>Структура таблицы $table</h4>";
    print $header;
    $mysql_data_type = array(
        3=>'int',
        5=>'double',
        10=>'date',
        253=>'varchar',
    );

    $query = "SELECT * FROM $table";
    $result = mysqli_query($conn, $query)
    or die ("<p>Ошибка: ".mysqli_error($conn));
    $num_fields = mysqli_num_fields($result);
    for ($x=0; $x<$num_fields; $x++) {
        $properties = mysqli_fetch_field_direct($result, $x);
        print $mysql_data_type[$properties->type]." ". ($properties->length). " ".($properties->name)." ".$properties->flags."</br>";
    }
}

function vid_content($conn, $table){
    $header = "<h4>Содержимое таблицы $table</h4>";
    print $header;

    $rus_name = array(
        "cnum" => "номер покупателя",
        "cname" => "имя покупателя",
        "city" => "город",
        "rating" => "рейтинг покупателя",
        "snum" => "номер продавца",
        "onum" => "номер заказа",
        "amt" => "стоимость заказа",
        "odate" => "дата заказа",
        "sname" => "имя продавца",
        "comm" => "комиссионные"
    );

    $query = "SELECT * FROM $table";
    $result = mysqli_query($conn, $query);
    $num_rows = mysqli_num_rows($result);
    $num_fields = mysqli_num_fields($result);
    print "<table border=\"1\" cellpadding=\"5\" cellspacing=\"1\">\n";
    print "<tr>\n";
    for ($x = 0; $x < $num_fields; $x++) {
        $name = mysqli_fetch_field_direct($result, $x)->name;
        print "\t<th>$rus_name[$name]</br>$name</th>\n";
    }
    print "</tr>\n";
    while ($a_row = mysqli_fetch_row($result)) {
        print "<tr style='padding:5px 10px'>\n";
        foreach ($a_row as $field)
            print "\t<td>$field</td>\n";
        print "</tr>\n";
    }
    print "</table>\n";
}

if(isset($_POST['sal1'])){
    vid_structure($conn, $_POST['sal1']);
}
if(isset($_POST['sal2'])){
    vid_content($conn, $_POST['sal2']);
}
if(isset($_POST['cust1'])){
    vid_structure($conn, $_POST['cust1']);
}
if(isset($_POST['cust2'])){
    vid_content($conn, $_POST['cust2']);
}
if(isset($_POST['ord1'])){
    vid_structure($conn, $_POST['ord1']);
}
if(isset($_POST['ord2'])){
    vid_content($conn, $_POST['ord2']);
}