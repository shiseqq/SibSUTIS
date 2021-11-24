<html> <head>
    <title> Листинг 4. Обработка данных формы
        из листинга 3 </title> </head> <body>
<?php
$user = $_POST["user"];
$hobby = $_POST["hobby"];
print "<p>$user, оказывается, вы предпочитаете";
print "<ul>\n";
foreach ($_POST as $key=>$value) {
    if (gettype($value) == "array") {
        foreach ($value as $v) {
            print "<li>$v<br>";
        }
    }
}
print "</ul>\n";
?>
</body> </html>