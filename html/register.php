<?php
if(!isset($MAGICAL))
{
	$view = "register.php";
	include("index.php");
}
else
{
	include("common.php");
	include("conn.php");
	//we assume that all items are checked in the client side
	//and so here we only do some very necessary check.
	//if somebody want to trick with us ,like include a quote a blank character, 
	//just let him go
	function verify_username($username)
	{
		if($username == "")
		{
			alert_and_go_back("Username can't be empty!");
			return false;
		}
		if(strlen($username) > 32)
		{
			alert_and_go_back("Username is too long!");
			return false;
		}
		//invalid character check?
		//is username duplicated?
		return true;
	}
	function verify_nickname($nickname)
	{
		if($nickname == "")
		{
			alert_and_go_back("Nickname can't be empty!");
			return false;
		}
		if(strlen($nickname) > 64)
		{
			alert_and_go_back("Nickname is too long!");
			return false;
		}
		//invalid character check?
		//is nickname duplicated?
		return true;
	}
	function verify_password($pwd1, $pwd2)
	{
		if($pwd1 != $pwd2)
		{
			alert_and_go_back("Passwords are not the same!");
			return false;
		}
		if($pwd1 == "" || $pwd2 == "")
		{
			alert_and_go_back("Password can't be empty!");
			return false;
		}
		return true;
	}
	function verify_gender($gender)
	{
		if(!($gender >=0 && $gender <=2))
		{
			alert_and_go_back("Gender id invalid!");
			return false;
		}
		return true;
	}
	function verify_email($email)
	{
		if($email != "")
		{
			if(strlen($email <= 128))
				return true;
			else
			{
				alert_and_go_back("Email is too long!");
			}
		}
		return true;
	}
	function verify_school($school)
	{
		if($school != "")
		{
			if(strlen($school > 32))
			{
				alert_and_go_back("School name is too long!");
				return false;
			}
			return true;
		}
		return true;
	}
	if(isset($_POST['submit']))
	{
		//we assume all these items except the two passwords are trimed before sent here
		//under normal condition mysql_real_escape_string won't affect anything
		$username = $_POST['username'];
		$nickname = $_POST['nickname'];
		$pswd1 = $_POST['password1'];//reserve blank characters
		$pswd2 = $_POST['password2'];
		$gender = (int)$_POST['gender'];
		$school = $_POST['school'];
		$email = $_POST['email'];
		if(verify_username($username) && verify_nickname($nickname)
			&& verify_password($pswd1, $pswd2) && verify_gender($gender)
			&& verify_school($school) && verify_email($email))
		{
			$username = $conn->escape_string($username);
			$nickname = $conn->escape_string($nickname);
			$school = $conn->escape_string($school);
			$email = $conn->escape_string($email);
			date_default_timezone_set("Asia/Shanghai");
			$tm = date('Y-m-d H:i:s');
			$pswd = md5($pswd1);
			$sql = "insert into user (username, nickname, password, email, school, gender, registerTime)
				values('$username', '$nickname', '$pswd', '$email', '$school', $gender, '$tm')";
			if($conn->query($sql))
			{
				$_SESSION['uid'] = $conn->insert_id;
				$_SESSION['nickname'] = $nickname;
				alert_and_redirect("Congratulations!You have registered successfully!", "index.php");
			}
			else
			{
				if($conn->errno == 1062)//duplicate entry error
				{
					if(strpos($error, 'key 2') === false)
					{
						alert_and_go_back("Username has existed!");
					}
					else if(strpos($error, 'key 3') === false)
					{
						alert_and_go_back("Nickname has existed!");
					}
					else
					{
						//unknown duplicated error;
					}
				}
				//database error;
			}
		}
	}
	else
	{
?>
<form name = "formRegister" method = "post" action = "register.php" onsubmit = "return checkRegisterItems()">
<div align = "center">
<table cellpadding = "20">
<tr>
<td width = "300"><font color = "red">*</font>Username.Valid characters are alphabet, digits and underscore(_).</td>
<td width = "200"><input type = "text" name = "username" value = "" maxlength = "32" size = "25"/></td>
</tr>
<tr>
<td><font color = "red">*</font>Nickname.Punctuations other than underscore(_) are invalid.</td>
<td><input type = "text" name = "nickname" value = "" maxlength = "64" size = "25"/></td>
</tr>
<tr>
<td><font color = "red">*</font>Password.Length should be between 6 and 16.</td>
<td><input type = "password" name = "password1" value = "" maxlength = "16" size = "25"/></td>
</tr>
<tr>
<td><font color = "red">*</font>Confirm your password</td>
<td><input type = "password" name = "password2" value=""  maxlength = "16" size = "25"/></td>
</tr>
<tr>
<td>Gender</td>
<td><select name="gender" size = "1">
<option value = "2">--</option>
<option value = "1">Male</option>
<option value = "0"/>Female</option>
</select></td>
</tr>
<tr>
<td>Email</td>
<td><input type = "text" name = "email" value = "" maxlength = "128" size = "25"/></td>
</tr>
<tr>
<td>School</td>
<td><input type = "text" name = "school" value = "" maxlength = "32" size = "25"/></td>
</tr>
<tr><td colspan = "2" align = "center"><i>Items marked with a '*' are necessary.</i></td></tr>
<tr><td colspan = "2" align = "center" >
<input type = "submit" name = "submit" value = "submit" /></td></tr>
</table>
</div>
</form>
<?php
	}
}
?>
