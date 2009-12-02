<?php
if(!isset($MAGICAL))
{
	$view = "submitproblem.php";
	include_once("index.php");
}
else
{
include_once("common.php");

//language and pid must not be empty, must be a number, must be a valid value
function verify_language($lan)
{
	global $LANGUAGE;
	/*
	if(($lan = trim($lan)) == "")
	{
		alert_and_go_back("Please select a language!");
		return false;
	}
	else if(!is_numeric($lan))
	{
		alert_and_go_back("Language invalid!");
		return false;
	}
	 */
	if($lan <= 0 || $lan >= count($LANGUAGE))
	{
		alert_and_go_back("Language invalid!");
		false;
	}
	else
		return true;
}

function verify_pid($conn, $pid)
{
	if($pid == "")
	{
		alert_and_go_back("Please select a problem!");
		return false;
	}
	else if(($pid = (int)$pid) <= 0)
	{
		alert_and_go_back("Problem ID invalid!");
		return false;
	}
	else
	{
		$sql = "select * from problem where pid = $pid";
		$result = $conn->query($sql);
		if($result && $result->num_rows > 0)
			return true;
		else
		{
			alert_and_go_back("Problem not existed!");
			return false;
		}
	}
	return false;//never reach here
}
function verify_source($source)
{
	if($source == "")
	{
		alert_and_go_back("Source code can't be empty!");
		return false;
	}
	if(strlen($source) > 65535)//This is the limitation of mysql BLOB type
	{
		alert_and_go_back("Source code is too long!");
		return false;
	}
	return true;
}
//only logged in one can submit
if(!isset($_SESSION['uid']))
{
	if(!isset($_GET['noalert']) || !$_GET['noalert'])
	{
		alert_and_redirect("You haven't logged in yet!", 
			"login.php?from=".urlencode($_SERVER['REQUEST_URI']));
	}
}
else
{
	if(isset($_POST['submit']))
	{
		include_once("conn.php");
		$lan = trim($_POST['language']);
		$pid = trim($_POST['pid']);
		if(!verify_language($lan))
			die();//if failed test, never reach here
		if(!verify_pid($conn, $pid))
			die();//if failed test, never reach here
		if(!verify_source($_POST['source']))
			die();

		//remember client's preferred language
		$_SESSION['pref_lan'] = $lan;
		$_SESSION['last_pid'] = $pid;

		$tm = date('Y-m-d H:i:s');
		//no need for escape
		#die($_POST['source']);
		$sql = "insert into status (pid, uid, language, submitTime,sourceCode) 
			values ($pid,{$_SESSION['uid']}, $lan, '$tm','{$_POST['source']}')";
		//actually we need transaction here, but MyIASM doesn't support it yet
		if($result = $conn->query($sql))
		{
			$result = $conn->query("update user set submitted = submitted + 1 where uid = {$_SESSION['uid']}");
			if(!$result)
			{
				error_log($conn->error." File:".__FILE__."; Line: ".__LINE__);
			}
			$result = $conn->query("update problem set submitted = submitted + 1 where pid = $pid");
			if(!$result)
			{
				error_log($conn->error." File:".__FILE__."; Line: ".__LINE__);
			}
			redirect("status.php");
			if(!$result)
			{
				//something wrong occured and the database is in inconsistent state
				//put handle code here
				alert("update partially failed.");
			}
		}
		else
		{
			error_log($conn->error." File:".__FILE__."; Line: ".__LINE__."; Sql string: $sql");
			die("Error occured, please try again later.");
		}
	}
	else
	{
?>
<form name = "formSubmitProblem" method = "post" action = "index.php?view=submitproblem"
onsubmit = "return checkSubmitProblemItems()">
<table align = "center"><tr>
<td>ProblemID</td>
<td><input type = "text" maxlength = "8" size = "20" name = "pid" 
<?php 
		if(isset($_GET['pid'])) 
			echo "value = \"{$_GET['pid']}\"";
		else if(isset($_SESSION['last_pid']))
			echo "value = \"{$_SESSION['last_pid']}\"";
?>
/>
</td>
<td>Language</td>
<td><select name = "language" size = "1">
<?php
$preferred_lan = 0;
if(isset($_SESSION['pref_lan']))
{
	$preferred_lan = $_SESSION['pref_lan'];
}
gen_options($LANGUAGE, null, $preferred_lan);
?>
</td></tr>
<tr><td colspan = "4">
<textarea name = "source" cols = "80" rows = "20"></textarea>
</td></tr>
<tr><td colspan = "4" align = "center">
<input type = "submit" name = "submit" value = "submit"/>
</td></tr>
</table>
</form>
<?php
	}
}
}
?>
