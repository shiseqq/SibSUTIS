<?php
$servername = "localhost";
$username = "username";
$password = "pass";
$dbname = "sample";

$conn = mysqli_connect($servername, $username, $password, $dbname);
$sql = "SELECT * FROM notebook_br01";
if($result = $conn->query($sql)){
    foreach($result as $row){
        foreach ($row as $item=>$item) {

        }
        print $row['id'];
        print ". Name - ";
        print $row['name'];
        print "<br/>";
        print "City - ";
        print $row['city'];
        print "<br/>";
        print "Address - ";
        print $row['address'];
        print "<br/>";
        print "Birthday - ";
        print $row['birthday'];
        print "<br/>";
        print "Mail - ";
        print $row['mail'];
        print "<br/><br/>";
    }
}