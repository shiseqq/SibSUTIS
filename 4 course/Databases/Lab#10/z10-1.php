<meta charset="utf-8">
<form action="z10-2.php" method="POST">
    <fieldset>
        <div>
            <lable>Отобразить таблицы</lable><br>
            <lable>&ensp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  Структура&emsp;</lable> <lable>Содержимое</lable><br><br>
            <label for="sal">Продавцы (sal)</label>
            &emsp;&emsp;<input type="checkbox" id="sal" name="sal1" value="sal">&emsp;&emsp;&emsp;&emsp;&emsp;
            <input type="checkbox" id="sal" name="sal2" value="sal"><br>
            <label for="cust">Покупатели(cust)</label>
            &emsp;<input type="checkbox" id="cust" name="cust1" value="cust">&emsp;&emsp;&emsp;&emsp;&emsp;
            <input type="checkbox" id="cust" name="cust2" value="cust"><br>
            <label for="ord">Заказы(ord)</label>
            &emsp;&emsp;&emsp;&ensp;<input type="checkbox" id="ord" name="ord1" value="ord">&emsp;&emsp;&emsp;&emsp;&emsp;
            <input type="checkbox" id="ord" name="ord2" value="ord">
        </div>

        <div>
            <button type="submit">Вывести!</button>
        </div>
    </fieldset>
</form>
