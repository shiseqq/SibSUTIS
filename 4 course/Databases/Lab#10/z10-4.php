<?php
    define('MYSQL_SERVER', 'localhost'); // Хост
    define('MYSQL_USER', 'username'); // Логин
    define('MYSQL_PASS', 'pass'); // Пароль
    define('MYSQL_DB', 'sample'); // Имя базы
    $conn = mysqli_connect(MYSQL_SERVER, MYSQL_USER, MYSQL_PASS, MYSQL_DB);
    if (!$conn) {
        die("Connection failed: " . mysqli_connect_error());
    }