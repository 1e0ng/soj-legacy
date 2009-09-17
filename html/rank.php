<?php
if(!isset($MAGICAL))
{
	$view = "rank.php";
	include("index.php");
}
else
{
include("common.php");
include("conn.php");

$pagesize = 20;
$top = 1;

if(isset($_GET['top']) && $_GET['top'] > 0)
	$top = $_GET['top'];

$page_string = paged_disp($conn, "user", null, $top, $pagesize, "user.php");
echo $page_string;
?>
<div align = "center">
<table>
	<tr>
	<th width = "80">Rank</th>
	<th width = "400">NickName</th>
	<th width = "100">AC Ration</th>
	</tr>
<?php
$top--;
$sql = "select uid, nickname, accepted, submitted from user
	order by accepted desc, submitted desc limit $top, $pagesize";
$top++;
if($result = $conn->query($sql))
{
	$i = 0;
	while($user = $result->fetch_object())
	{
		echo "<tr>\n";
		gen_cell($top + $i++);
		gen_cell("<a href=\"index.php?view=user&uid=$user->uid\">$user->nickname</a>");
		echo "<td>";
		if($user->submitted > 0)
			$ratio = ($user->accepted / $user->submitted) * 100;
		else
			$ratio = 0;
		printf("%.2f%%", $ratio);
		echo "($user->accepted/$user->submitted)</td>\n";
	}
	if($i == 0)
	{
?>
<tr><td colspan = "3"><i>No user yet!</i></td></tr>
<?php
	}
}
else
{
	error_log($conn->error." File:".__FILE__."; Line: ".__LINE__."; Sql string: $sql");
	die("Database Error.");
}
?>
</table>
</div>
<?php echo $page_string; }?>

