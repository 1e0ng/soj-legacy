<?php
if(!isset($MAGICAL))
{
	$view = "statistics.php";
	include("index.php");
}
else
{
?>
<table border="1">
<tr><td colspan = "6">Heroes List</td></tr>
<tr>
<th>Rank</th>
<th>Username</th>
<th>Language</th>
<th>Time</th>
<th>Memory</th>
<th>Submit Time</th>
</tr>
<?php
	include("conn.php");
	include("common.php");

	if(!isset($_GET['pid']) || $_GET['pid'] == "" || !is_numeric($_GET['pid']))
	{
		alert_and_go_back("Statistics for problem {$_GET['pid']} not existed!");
	}
	$sql = "select nickname, language, rtime, rmemory, submitTime from status, user "
		. "where status.uid = user.uid and pid = {$_GET['pid']} and judgeStatus = 3 "
		. "order by rtime, rmemory, submitTime limit 0, 20";

	if($result = $conn->query($sql))
	{
		$i = 1;
		while($stat = $result->fetch_object())
		{
			echo "<tr>\n";
			gen_cell($i);
			gen_cell($stat->nickname);
			gen_cell($stat->language);
			gen_cell($stat->rtime);
			gen_cell($stat->rmemory);
			gen_cell($stat->submitTime);
			echo "</tr>\n";
			$i++;
		}
		if($i == 1)//the result is empty
		{
			alert_and_go_back("Statistics for problem {$_GET['pid']} not existed or nobody has worked it out!");
			die();
		}
?>
</table>
<br/><br/><br/><br/>
<table border="1">
<tr><td colspan = "7">Statistic Data</td></tr>
<tr><th width = "100"></th>
<?php
		$sql = "select judgeStatus, count(*) as total from status where pid = {$_GET['pid']} "
		   ."group by judgeStatus";	
		if($result = $conn->query($sql))
		{
			//if the query is success, the result is not empty
			$sum = 0;
			$total[3] = 0;
			$total[4] = 0;
			$total[5] = 0;
			$total[6] = 0;
			$total[7] = 0;
			while(list($stts, $ttl) = $result->fetch_row())
			{
				if($stts >= 3)
				{
					$total[$stts] = $ttl;
					$sum += $ttl;
				}
			}
			for($i = 3; $i <= 7; $i++)
				echo "<th>{$JUDGE_STATUS[$i]}</th>\n";
			echo "<th>Sum</th>\n";
			echo "</tr>\n";
			echo "<tr><td>Total</td>\n";
			foreach($total as $t)
			{
				gen_cell($t);
			}
			gen_cell($sum);
			echo "</tr>";
			echo "<tr><td>Percentage</td>\n";
			foreach($total as $t)
			{
				printf("<td>%.2f%%</td>\n", 0 == $sum ? 0 : $t * 100 / $sum);
			}
			gen_cell("100%");
			echo "</tr>";
		}
		else
		{
			error_log($conn->error." File:".__FILE__."; Line: ".__LINE__."; Sql string: $sql");
			die("Database Error.");
		}
?>
</table>
<?php
	}
	else
	{
		error_log($conn->error." File:".__FILE__."; Line: ".__LINE__."; Sql string: $sql");
		die("Database Error.");
	}
}
?>
