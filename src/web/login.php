<?php
if (!isset($MAGICAL)) {
    $view = "login.php";
	include("index.php");
}
else {
   	include("common.php");
	include("conn.php");

    function verify_user($conn, $username, $password)
    {
        $ans = false;
        $query = "select uid, username, nickname, password from user where username = '" . $conn->real_escape_string($username) . "'";
        //var_dump($query);
        if (($result = $conn->query($query)) and $result->num_rows > 0) {
            $user = $result->fetch_object();
            if($user->password == md5($password)) {
                $_SESSION['uid'] = $user->uid;
                $_SESSION['nickname'] = $user->nickname;
                $ans = true;
            }
        }
        return $ans;
    }

    if (isset($_POST['username']) && isset($_POST['password'])) {
        if (verify_user($conn, $_POST['username'], $_POST['password'])) {
            if(isset($_GET['from']) && $_GET['from'] != "") {
                header("location:{$_GET['from']}");
            }
            else {
                header("location:index.php");
            }
        }
        else {
            alert_and_go_back("username or password is wrong,please try again");
        }
    }
    else {
        ?>
        <form name = "formLogin" action = "
<?php 
	echo "login.php?noalert=1";
	if(!empty($_GET['from'])) {
		echo "&from=" . urlencode($_GET['from']);
	}

?> 
		" method = "post" onsubmit = "return checkLoginItems()">
            <table border="1">
            <tr>
			<td>Username:</td>
            <td><input type="text" name="username" size="25" maxlength="32"></td>
            </tr>
            <tr>
            <td>Password:</td>
            <td><input type="password" name="password" size="25" length ="32"></td>
            </tr>
            <tr>
            <td>
            <input type="submit" name="submit" value="Submit">
            </td><td>
            <input type="reset" value="Reset">
            </td>
            </tr>
            </table>
            </form>
            <?php
            }
    echo "Login Successful.";
}
?>
