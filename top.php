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
	<a href=index.php?view=login>Login</a>
	&nbsp;&nbsp;
	<a href=index.php?view=register>Register</a>
<?php
}
//else display the user link
else
{
	$nickname = $_SESSION['nickname'];
	echo "<a href=index.php?view=user&uid=".$_SESSION['uid'].">$nickname</a>";
	echo "&nbsp;&nbsp;";
	echo "<a href=index.php?view=logout>Logout</a>";
}
echo "</div>\n";
?>
<h1><center>SDU Online Judge</center></h1>
<hr width = "80%">
<div align = "center">
	<a href="index.php?view=home">Home</a>
	&nbsp;&nbsp;&nbsp;&nbsp;
	<a href="index.php?view=problemlist">Problems</a>
	&nbsp;&nbsp;&nbsp;&nbsp;
	<a href="index.php?view=submitproblem">Submit</a>
	&nbsp;&nbsp;&nbsp;&nbsp;
	<a href="index.php?view=status">Status</a>
	&nbsp;&nbsp;&nbsp;&nbsp;
	<a href="index.php?view=rank">Rank</a>
</div>
<hr width = "40%">
<?php
}
?>
