<?php
if(!isset($MAGICAL))
{
	$view = "status.php";
	include("index.php");
}
else
{
include("conn.php");
include("common.php");

$pid = "";
$username = "";
$judgeStatus = 0;
$language = 0;

$querys = array();
$conds = array();
if(isset($_GET['pid']) && ($pid = trim($_GET['pid'])) != "")
{
	$querys[] = "pid=$pid";
	$pid = $conn->escape_string($pid);
	$conds[] = "pid=$pid";
}
if(isset($_GET['username']) && ($username = trim($_GET['pid'])) != "")
{
	$querys[] = "username=".urlencode($username);
	$username = $conn->escape_string($username);
	$conds[] = "nickname=$username";
}
if(isset($_GET['judgeStatus']) && $_GET['judgeStatus'] != "")
{
	$judgeStatus = (int)$_GET['judgeStatus'];
	if($judgeStatus > 0 && $judgeStatus < count($judgeStatus))
	{
		$query[] = "judgeStatus={$judgeStatus}";
		$conds[] = "judgeStatus = {$judgeStatus}";
	}
	else
	{
		//alert_and_go_back("JudgeStatus Invalid!");
	}
}
if(isset($_GET['language']) && $_GET['language'] != "")
{
	$language = (int)$_GET['language'];
	if($language > 0 && $language < count($LANGUAGE))
	{
		$querys[] = "language={$language}";
		$conds[] = "language = {$language}";
	}
	else
	{
		//alert_and_go_back("Language Invalid!");
	}
}

$pagesize = 20;
$top = 1;

if(isset($_GET['top']) && $_GET['top'] > 0)
	$top = $_GET['top'];

$condition = "";
$table = "status";
if($conds)
{
	$table .= ", user";
	$condition = "user.uid = status.uid ".join(" and ", $conds);
}
$page_string = paged_disp($conn, $table, $condition, $top, $pagesize, 
	"status.php".($querys? "?".join("&", $querys) : ""), true);
?>
<div align = "center">
<form action = "status.php" method = "get">
	<p>
	ProblemID
	<input type = "text" name = "pid" value="<?php echo $pid;?>" size = "8"  maxlength = "8"/>
	Username
	<input type = "text" name = "username" value = "<?php echo $username;?>" size = "10" maxlength = "32"/>
	JudgeStatus
	<select name = "judgeStatus" size = "1" width = "10">
<?php
	gen_options($JUDGE_STATUS, null, $judgeStatus);
?>
	</select>
	Language
	<select name = "language" size = "1">
<?php
	gen_options($LANGUAGE, null, $language);
?>
	</select>
	<input type = "submit" name = "submit" value = "Go"/>
	</p>
</form>
<?php

echo $page_string;
?>
	<table>
		<tr>
			<th width = "80" align = "center">RunID</th>
			<th width = "80" align = "center">ProblemID</th>
			<th width = "160" align = "center">Username</th>
			<th width = "160" align = "center">Judge Status</th>
			<th width = "80" align = "center">Language</th>
			<th width = "100" align = "center">Time</th>
			<th width = "100" align = "center">Memory</th>
			<th width = "200" align = "center">Submitted Time</th>
		</tr>
<?php
//in mysql minimum top value is 0, so we need dec it by 1 and restore it later
$top--;
$sql = "select rid, pid, user.uid, user.nickname, judgeStatus, 
	language, rtime, rmemory, submitTime
	from status, user where status.uid = user.uid ";
$sql .= join(" and ", $conds) . " order by rid desc limit $top, $pagesize";
$top++;
if($result = $conn->query($sql))
{
	if($result->num_rows > 0)
	{
		while($status = $result->fetch_object())
		{
			echo "<tr>";

			gen_cell($status->rid);

			gen_cell("<a href=\"problem.php?pid=$status->pid\">$status->pid</a>");

			gen_cell("<a href=\"user.php?uid=$status->uid\">
				$status->nickname</a>");

			gen_cell($JUDGE_STATUS[$status->judgeStatus]);

			if(isset($_SESSION['uid']) && $_SESSION['uid'] == $status->uid)
				gen_cell("<a href=\"viewsource.php?sid={$status->rid}\">{$LANGUAGE[$status->language]}</a>");
			else
				gen_cell($LANGUAGE[$status->language]);

			if($status->rtime == null)
				$rtime = "--";
			else
				$rtime = $status->rtime."ms";
			gen_cell($rtime);

			if($status->rmemory == null)
				$rmemory = "--";
			else
				$rmemory = $status->rmemory."KiB";
			gen_cell($rmemory);

			gen_cell($status->submitTime);

			echo "</tr>";
		}
	}
	else
	{
		alert_and_go_back("No status returned!");
	}
}
else
{
	error_log($conn->error." File:".__FILE__."; Line: ".__LINE__."; Sql string: $sql");
}
?>
	</table>
<?php
echo $page_string;
?>
</div>
<?php } ?>
