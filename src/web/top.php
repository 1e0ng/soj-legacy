<?php
if(!isset($MAGICAL))
	include("index.php");
else
{?>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link href="soj.css" rel="stylesheet" type="text/css" />
<img src="banner.jpg" width="980" height="90" />
<?
echo "<div align = \"right\">";

//if not logged in, display the login and register link
if(!isset($_SESSION['uid']))
{
?>
<font face="sans-serif">
	<a href=login.php>Login</a>
	&nbsp;&nbsp;
	<a href=register.php>Register</a>
</font>
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
<table width="100%" 
border="1" bordercolor="#ffffff" style="BORDER-COLLAPSE: collapse">
  <tbody>
    <tr valign="top" align="middle" bgcolor="#6589d1">
      <th bgcolor="#6589d1" class="h"><a href="home.php"><font color="#FFFFFF">Home</font></a></th>
      <th bgcolor="#6589d1" class="h"><a href="problemlist.php"><font color="#FFFFFF">Problems</font></a></th>
      <th bgcolor="#6589d1" class="h"><a href="submitproblem.php"><font color="#FFFFFF">Submit</font></a></th>
      <th bgcolor="#6589d1" class="h"><a href="status.php"><font color="#FFFFFF">Status</font></a></th>
      <th bgcolor="#6589d1" class="h"><a href="rank.php"><font color="#FFFFFF">Rank</font></a></th>
    </tr>
  </tbody>
</table>
<?php
}
?>
