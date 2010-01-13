<?php
$conn = new mysqli();
@$conn->connect("localhost", "soj", "soj-001-soj", "soj");
if($myerror = mysqli_connect_error())
{
	die("MySql Error!".$myerror);
}
?>
