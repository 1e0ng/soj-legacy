<?php
if (isset($conn)) {
    $conn->ping();
}
else {
    $conn = new mysqli();
    $conn->connect("localhost", "soj", "soj-001-asar-002", "soj");
    if ($myerror = mysqli_connect_error()) {
    	die("MySql Error!".$myerror);
    }
}
