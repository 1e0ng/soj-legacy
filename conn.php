<?php
$conn = new mysqli();
@$conn->connect("localhost", "root", "dwp880412", "soj");
if($myerror = mysqli_connect_error())
{
	die("MySql Error!".$myerror);
}
?>
