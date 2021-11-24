<meta charset="utf-8">

<h1>Editing</h1>

<?php
$servername = "localhost";
$username = "username";
$password = "pass";
$dbname = "sample";

$conn = mysqli_connect($servername, $username, $password, $dbname);

$ID = $_POST['id'];
if($ID !=""){
    if(isset($_POST['field_name'])!=""){
        if(!(($_POST['field_name'] =="name" || $_POST['field_name'] == "mail") && $_POST['field_value'] == "")){
            $p = $_POST['field_name'];
            $q = $_POST['field_value'];
            $q = "UPDATE notebook_br01 
			SET $p='$q' 
			WHERE id=$ID ";
            $result = mysqli_query($conn, $q);
            if(!$result) die("Cant edit note with id=$ID!");
        }else {
            $p = $_POST['field_name'];
            echo "$p cant edit to null!";
        }
    }

    $result = mysqli_query($conn, "SELECT * from notebook_br01 WHERE id=$ID");
    if(!$result) die("No notes with id = $ID!");
    $num_fields = mysqli_num_fields($result);
    echo '<form action="z09-4-1.php" method="POST">';
    echo '<select name="field_name">';
    for ($i = 1; $i < $num_fields; $i++) {
        $name = mysqli_fetch_field_direct($result, $i)->name;
        echo "<option value=\"$name\">$name</option>";
    }

    echo '</select>';
    echo "<td><input type=\"text\" name=\"field_value\"></td>";
    echo '<br>';

    $row = mysqli_fetch_row($result);
    $ind = 0;
    foreach ($row as $field){
        $name = mysqli_fetch_field_direct($result, $ind)->name;
        print "row['$name'] = $field <br>";
        $ind++;
    }
    echo "<input type=\"hidden\" name=\"id\" value=\"$ID\">";
    echo '<p><input type="submit" value="Edit"></p>';
    echo '</form>';

}
else echo 'ID не задан!';
mysqli_close($conn);
?>
<form action="z09-4.php" method="post">
    <p><input type="submit" value="Вернуться назад"></p>
</form>
</body>
</html>