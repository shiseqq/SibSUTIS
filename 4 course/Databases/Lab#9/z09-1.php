<?php
$servername = "localhost";
$username = "username";
$password = "pass";
$dbname = "sample";

$conn = mysqli_connect($servername, $username, $password, $dbname);

if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

$val = mysqli_query($conn,"select 1 from notebook_br01 LIMIT 1");

if($val == FALSE)
{
    $sql = "CREATE TABLE notebook_br01 (
    id INT(6) NOT NULL AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(30),
    city VARCHAR(30),
    address VARCHAR(30),
    birthday DATE,
    mail VARCHAR(20)
    );";

    if (!($conn->query($sql) == TRUE)) {
        echo "Error creating table: " . $conn->error;
    }
}

$reg = [$_POST['name'],$_POST['city'],$_POST['address'],$_POST['date'],$_POST['mail']];

for($i=0;$i<sizeof($reg);$i++){
    $reg[$i]=((!$reg[$i])?'NULL':"'".$reg[$i]."'");
}

$sql = "INSERT INTO notebook_br01 (name, city, address, birthday, mail)
VALUES ($reg[0], $reg[1], $reg[2], $reg[3], $reg[4] );";

if (mysqli_query($conn, $sql)) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . mysqli_error($conn);
}
echo
    "<br/><a href='z09-3.php'>Вывести записи</a>";
mysqli_close($conn);
