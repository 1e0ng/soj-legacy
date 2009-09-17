<?php
if(!isset($MAGICAL))
	include("index.php");
else
{
	include_once("common.php");
	include_once("conn.php");
function verify_user($conn, $username, $password)
{
	if($result = $conn->query(\
		"select uid, username, nickname, password from user where username = '$username'"))
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
	if(verify_user($conn, $conn->escape_string($_POST['username']), $_POST['password']))
	{
		if(isset($_GET['view']) && $_GET['view'] == 'login')
		{
			redirect("index.php");;	
		}
		else
		{
			go_back();
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
<form name = "formLogin" action = "<?php echo $_SERVER['REQUEST_URI'].'&noalert=1';?>" method = "post" onsubmit = "return checkLoginItems()">
	<table>
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
			<td align = "center" colspan = "2"><a href="index.php?view=register">
				<i>Not registerred yet?Click here to register immediately!</i></a></td>
		</tr>
	</table>
</form>
<div>
<?php
}
}
?>
