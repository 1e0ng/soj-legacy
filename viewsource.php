<?php
if(!isset($MAGICAL))
	include("index.php");
else
{
?>
<div align = "center">
<table width = "600"><tr><td>
<?php
	include("conn.php");
	include("common.php");

function canView($user)
{
	//now our policy is that only code owner can view code
	if(!isset($_SESSION['uid']) || $_SESSION['uid'] != $user)
	{
		return false;
	}
	return true;
}
if(!isset($_GET['sid']))
{
	alert_and_go_back("Please select a source code to view first!");
}
else if(!is_numeric($_GET['sid']))
{
	alert_and_go_back("Bad source code id format");
}
else
{
	$sql = "select uid, sourceCode from status where rid = {$_GET['sid']}";
	if($result = $conn->query($sql))
	{
		if(list($uid, $source) = $result->fetch_row())
		{
			if(canView($uid))
			{
				if($source == "")
					alert("This source code is empty!");
				echo my_htmlentities($source);
			}
			else
			{
				alert_and_go_back("Sorry, but you don't have permission to view this code.");
			}
		}
		else
		{
			alert_and_go_back("Source code not found!");
		}
	}
	else
	{
		error_log($conn->error." File:".__FILE__."; Line: ".__LINE__."; Sql string: $sql");
		alert_and_go_back("Error occured, please try again later.");
	}
}
?>
</td></tr></table>
</div>
<?php
}
?>
