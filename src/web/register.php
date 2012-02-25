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
        $ans = false;
		if (empty($username)) {
			alert_and_go_back("Username can't be empty!");
		}
		else if (strlen($username) > 32) {
			alert_and_go_back("Username is too long!");
		}
        else {
            $ans = true;
        }
		return $ans;
	}

	function verify_nickname($nickname)
	{
        $ans = false;
		if (empty($nickname)) {
			alert_and_go_back("Display name can't be empty!");
		}
		else if (strlen($nickname) > 64) {
			alert_and_go_back("Display name is too long!");
		}
        else {
            $ans = true;
        }
		return $ans;
	}

	function verify_password($pwd1, $pwd2)
	{
        $ans = false;
		if ($pwd1 != $pwd2) {
			alert_and_go_back("Passwords are not the same!");
		}
		else if (empty($pwd1) or empty($pwd2)) {
			alert_and_go_back("Password can't be empty!");
		}
        else {
            $ans = true;
        }
		return $ans;
	}

	function verify_gender($gender)
	{
        $ans = false;
		if (!($gender >=0 && $gender <=2)) {
			alert_and_go_back("Gender id invalid!");
		}
        else {
            $ans = true;
        }
		return $ans;
	}

	function verify_email($email)
	{
        $ans = false;
        if (empty($email)) {
            $ans = true;
        }
        else if(strlen($email <= 128) and 
                preg_match("/^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,4}$/i", $email)) {
            $ans = true;
		}
        else {
            alert_and_go_back("Email is invalid.");
        }
		return $ans;
	}

	function verify_school($school)
	{
        $ans = false;
        if (empty($school)) {
            $ans = true;
        }
        else {
			if(strlen($school > 32)) {
				alert_and_go_back("School name is too long!");
			}
            else {
                $ans = true;
            }
		}
		return $ans;
	}

	if(isset($_POST['submit']))
	{
		//we assume all these items except the two passwords are trimed before sent here
		//under normal condition real_escape_string won't affect anything
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
			$username = $conn->real_escape_string($username);
			$nickname = $conn->real_escape_string($nickname);
			$school = $conn->real_escape_string($school);
			$email = $conn->real_escape_string($email);
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

<table border="1">
<tr>
<td>User Name(*):</td>
<td><input type = "text" name = "username" value = "" maxlength = "32" size = "25"/></td>
<td>Alphabet, digits and underscore.</td>
</tr>
<tr>
<td>Display Name(*):</td>
<td><input type = "text" name = "nickname" value = "" maxlength = "64" size = "25"/></td>
<td>Alphabet, digits and underscore.</td>
</tr>
<tr>
<td>Password(*):</td>
<td><input type = "password" name = "password1" value = "" maxlength = "16" size = "25"/></td>
<td>Length should be between 6 and 16.</td>
</tr>
<tr>
<td>Confirm password(*):</td>
<td><input type = "password" name = "password2" value=""  maxlength = "16" size = "25"/></td>
<td></td>
</tr>
<tr>
<td>Gender:</td>
<td><select name="gender" size = "1">
<option value = "2">--</option>
<option value = "1">Male</option>
<option value = "0">Female</option>
</select></td>
<td></td>
</tr>
<tr>
<td>Email</td>
<td><input type = "text" name = "email" value = "" maxlength = "128" size = "25"/></td>
<td></td>
</tr>
<tr>
<td>School</td>
<td><input type = "text" name = "school" value = "" maxlength = "32" size = "25"/></td>
<td></td>
</tr>
<tr><td colspan = "3" align = "center" >
<input type = "submit" name = "submit" value = "submit" /></td></tr>
</table>
</form>
<?php
	}
}
?>
