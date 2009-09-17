<?php
include("common.php");

$query_string = "";
$sql_condition = "";
if(isset($_GET['pid']) && ($pid = trim($_GET['pid'])) != "")
{
	$query_string .= "&pid=$pid";
	$pid = $conn->escape_string($pid);
	$sql_condition .= "and pid=$pid ";
}
if(isset($_GET['username']) && ($username = trim($_GET['pid'])) != "")
{
	$query_string .= "&username=$username";
	$username = $conn->escape_string($username);
	$sql_condition .= "and nickname=$username ";
}
if(isset($_GET['judgeStatus']) && $_GET['judgeStatus'] != "")
{
	if(is_numeric($_GET['judgeStatus']) && $_GET['judgeStatus'] > 0 
		&& $_GET['judgeStatus'] < count($judgeStatus))
	{
		$query_string .= "&judgeStatus={$_GET['judgeStatus']}";
		$sql_condition .= "and judgeStatus = {$_GET['judgeStatus']} ";
	}
	else
	{
		alert_and_go_back("JudgeStatus Invalid!");
	}
}
if(isset($_GET['language']) && $_GET['language'] != "")
{
	if(is_numeric($_GET['judgeStatus']) && $_GET['language'] > 0 
		&& $_GET['language'] < count($LANGUAGE))
	{
		$query_string .= "&language={$_GET['language']}";
		$sql_condition .= "and language = {$_GET['language']} ";
	}
	else
	{
		alert_and_go_back("Language Invalid!");
	}
}

include("conn.php");

$pagesize = 20;
$top = 1;

if(isset($_GET['top']) && $_GET['top'] > 0)
	$top = $_GET['top'];

$table = "status";
$condition = "";
if($sql_condition)
{
	$table .= ", user";
	$condition = "user.uid = status.uid ".$sql_condition;
}
$page_string = paged_disp($conn, $table, $condition, $top, $pagesize, "index.php?view=status".$query_string, true);
?>
<div align = "center">
<form action = "index.php?view=status" method = "get">
	<p>
	ProblemID
	<input type = "text" name = "pid" size = "8"  maxlength = "8"/>
	Username
	<input type = "text" name = "username" size = "10" maxlength = "32"/>
	JudgeStatus
	<select name = "judgeStatus" size = "1" width = "10">
<?php
for($i = 0; $i < count($JUDGE_STATUS); $i++)
{
	echo "<option value = \"$i\">{$JUDGE_STATUS[$i]}\n";
}
?>
	</select>
	Language
	<select name = "language" size = "1">
<?php
for($i = 0; $i < count($LANGUAGE); $i++)
{
	echo "<option value = \"$i\">{$LANGUAGE[$i]}</option>\n";
}
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
$sql .= $sql_condition . " order by rid desc limit $top, $pagesize";
$top++;
if($result = $conn->query($sql))
{
	if($result->num_rows > 0)
	{
		while($status = $result->fetch_object())
		{
			echo "<tr>";

			gen_cell($status->rid);

			gen_cell("<a href=\"index.php?view=problem&pid=$status->pid\">$status->pid</a>");

			gen_cell("<a href=\"index.php?view=user&uid=$status->uid\">
				$status->nickname</a>");

			gen_cell($JUDGE_STATUS[$status->judgeStatus]);

			if(isset($_SESSION['uid']) && $_SESSION['uid'] == $status->uid)
				gen_cell("<a href=\"index.php?view=viewsource&sid={$status->rid}\">{$LANGUAGE[$status->language]}</a>");
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
