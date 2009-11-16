<?php
if(!isset($MAGICAL))
	include("index.php");
else
{

echo "<div align = \"right\">";

//if not logged in, display the login and register link
if(!isset($_SESSION['uid']))
{
?>
	<a href=login.php>Login</a>
	&nbsp;&nbsp;
	<a href=register.php>Register</a>
<?php
}
//else display the user link
else
{
	$nickname = $_SESSION['nickname'];
	echo "<a href=\"user.php?uid=".$_SESSION['uid']."\">$nickname</a>";
	if(!isset($_POST['submit']))
	echo "&nbsp;&nbsp;";
	echo "<a href=\"logout.php\">Logout</a>";
}
echo "</div>\n";
?>
<h1><center>SDU Online Judge</center></h1>
<hr width = "80%">
<div align = "center">
	<a href="home.php">Home</a>
	&nbsp;&nbsp;&nbsp;&nbsp;
	<a href="problemlist.php">Problems</a>
	&nbsp;&nbsp;&nbsp;&nbsp;
	<a href="submitproblem.php">Submit</a>
	&nbsp;&nbsp;&nbsp;&nbsp;
	<a href="status.php">Status</a>
	&nbsp;&nbsp;&nbsp;&nbsp;
	<a href="rank.php">Rank</a>
</div>
<hr width = "40%">
<?php
}
?>
