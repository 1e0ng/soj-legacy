<?php
$conn = new mysqli();
@$conn->connect("211.87.227.89", "soj", "soj-001-soj", "soj");
if($myerror = mysqli_connect_error())
{
	die("MySql Error!".$myerror);
}
?>
