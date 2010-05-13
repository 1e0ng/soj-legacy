<?php
if(!isset($MAGICAL))
{
	$view = "login.php";
	include("index.php");
}
else
{
	include_once("common.php");
	include_once("conn.php");
function verify_user($conn, $username, $password)
{
	$username = $conn->escape_string($username);
	if(($result = $conn->query(
		"select uid, username, nickname, password from user where username = '$username'"))
		&& $result->num_rows > 0)
	{
		$user = $result->fetch_object();
		if($user->password == md5($password))
		{
			//$_SESSION['username'] = $user->username;
			$_SESSION['uid'] = $user->uid;
			$_SESSION['nickname'] = $user->nickname;
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

if(isset($_POST['username']) && isset($_POST['password']))
{
	if(verify_user($conn, $_POST['username'], $_POST['password']))
	{
		if(isset($_GET['from']) && $_GET['from'] != "")
		{
			header("location:{$_GET['from']}");
		}
		else
		{
			header("location:index.php");
		}
	}
	else
	{
		echo alert_and_go_back("username or password is wrong,please try again");
	}
}
else
{
?>
<div align = "center">
<form name = "formLogin" action = "
<?php 
	echo "login.php?noalert=1";
	if(isset($_GET['from']) && $_GET['from'] != "")
	{
		echo "&from=".urlencode($_GET['from']);
	}
?> 
		" method = "post" onsubmit = "return checkLoginItems()">
	<table background="table_back.jpg">
		<tr>
			<td align = "right">Username&nbsp;&nbsp;</td>
			<td align = "left"><input type="text" name="username" size="25" maxlength="32"></td>
		</tr>
		<tr>
			<td align = "right">Password&nbsp;&nbsp;</td>
			<td align = "left"><input type="password" name="password" size="25" length ="32"></td>
		</tr>
		<tr>
			<td align = "center" colspan="2">
				<input type="submit"name=submit value="Submit">
				&nbsp;&nbsp;&nbsp;&nbsp;
				<input type="reset" value="Reset">
			</td>
		</tr>
		<tr><td></td><td></td></tr>
		<tr>
			<td align = "center" colspan = "2"><a href="register.php">
				<i>Not registerred yet?Click here to register immediately!</i></a></td>
		</tr>
	</table>
</form>
<div>
<?php
}
echo "<center>Login Successful.</center>";
}
?>
