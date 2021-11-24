<?php

$otv = [2, 3, 1, 2, 3];
$name = "user";
$res = 0;

if (!empty($_POST['name']))
    $name = $_POST['name'];

$answers = [$_POST['q1'],$_POST['q2'],$_POST['q3'],$_POST['q4'],$_POST['q5']];

for ($i=0; $i<5; $i++){
    if ($otv[$i]==$answers[$i]){
        $res++;
    }
}
print "Результаты игрока $name - $res из 5";
