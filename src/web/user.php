<?php
if(!isset($MAGICAL))
{
	$view = "user.php";
	include("index.php");
}
else
{
include("conn.php");
include("common.php");

function gen_row($col1, $col2, $width1 = "200", $width2 = "400")
{
	echo "<tr><td width = \"$width1\">$col1</td><td width = \"$width2\">$col2</td></tr>\n";
}

echo "<div align = \"center\">\n<table>\n\n";

if(isset($_GET['uid']))
{
	if($_GET['uid'] > 0)
		$uid = (int)$_GET['uid'];
	else
		alert_and_go_back("User not found!");
}
else if(isset($_SESSION['uid']))
{
	$uid = $_SESSION['uid'];
}
else
{
	die("Something goes wrong.");
}
$sql = "select nickname, email, gender, accepted, submitted, registerTime
   	from user where uid = $uid";
if($result = $conn->query($sql))
{
	if($user = $result->fetch_object())
	{
		gen_row("Nickname", $user->nickname);
		gen_row("Email", $user->email);
		gen_row("Gender", $user->gender == null ? "Unknown" : ($user->gender ? "Male" : "Female"));

		echo "<tr height = \"100\" valign = \"top\"><td>Solved</td><td>";
		$sql = "select distinct pid from status where uid=$uid and judgeStatus=3";
		if($result = $conn->query($sql))
		{
			while($pros = $result->fetch_object())
			{
				echo "<a href=\"problem.php?pid=$pros->pid\">$pros->pid</a>";
			}
		}
		echo "</td></tr>\n";

		gen_row("Total Accepted", $user->accepted);
		gen_row("Total Submitted", $user->submitted);
		gen_row("Register Time", $user->registerTime ? $user->registerTime : "Unknown");
	}
	else
	{
		alert_and_go_back("User not found!");
	}
}
else
{
	error_log($conn->error." File:".__FILE__."; Line: ".__LINE__."; Sql string: $sql");
	die("Database Error.");
}
echo "</table></div>\n";
}
?>
