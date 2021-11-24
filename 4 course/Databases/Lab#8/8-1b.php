<?php

$a = "center";
$va = "center";

if (!empty($_POST['radio']))
    $a = $_POST['radio'];
if (!empty($_POST['checkbox']))
    $va = $_POST['checkbox'];

echo
   '<meta charset="utf-8">
  <style>
   table {
    width: 300px;
    height: 300px;
   }
   td, th {
    text-align: '.$a.';
    vertical-align: '.$va.';
   }
  </style>
 </head> 
 <body>
  <table border="1px">
   <tr><td>Тут могла быть ваша реклама</td></tr>
  </table>';

echo
    "<a href='8-1a.html'>Назад</a>";