<?php
include("conn.php");
$result = $conn->query("select * from user");
while($user = $result->fetch_object())
{
	echo $user->username."\n".$user->nickname."\n";
}
?>
