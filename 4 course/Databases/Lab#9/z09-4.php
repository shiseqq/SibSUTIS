<meta charset="utf-8">

<?php
$servername = "localhost";
$username = "username";
$password = "pass";
$dbname = "sample";

$conn = mysqli_connect($servername, $username, $password, $dbname);

$sql  = "SELECT * from notebook_br01";

$result = mysqli_query($conn, $sql);
$num_fields = mysqli_num_fields($result);
$num_rows = mysqli_num_rows($result);

echo '<form action="z09-4-1.php" method="POST">';
echo '<table border="2" cellpadding="5" cellspacing="0"><tr>';
for ($i = 0; $i < $num_fields; $i++) {
    $name = mysqli_fetch_field_direct($result, $i)->name;
    echo "<th>$name</th>";
}
echo "</tr>";
while ($row = mysqli_fetch_row($result)) {
    echo "<tr>";
    foreach ($row as $field)
        print "<td>$field</td>";
    echo "<td><input type=\"radio\" name=\"id\" value=\"$row[0]\"></td>";
    echo "</tr>";
}
echo "</table>";
echo '<p><input type="submit" value="Edit"></p>';
echo '</form>';
mysqli_close($conn);
?>