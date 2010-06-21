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

?>
<div align = "center">
<?
$page_string = paged_disp($conn, "user", null, $top, $pagesize, "rank.php");
echo $page_string;
?>
<table border="1" bordercolor="#ffffff" style="BORDER-COLLAPSE: collapse">
	<tr>
	<th width = "80" bgcolor="#6589d1" class="h"><font color="#FFFFFF">Rank</font></th>
	<th width = "400" bgcolor="#6589d1" class="h"><font color="#FFFFFF">NickName</font></th>
	<th width = "100" bgcolor="#6589d1" class="h"><font color="#FFFFFF">AC Ration</font></th>
	</tr>
<?php
$top--;
$sql = "select uid, nickname, accepted, submitted from user
	order by accepted desc, submitted asc limit $top, $pagesize";
$top++;
if($result = $conn->query($sql))
{
	$i = 0;
	while($user = $result->fetch_object())
	{
		if ($user->uid%2==0){
			echo "<tr bgcolor=\"#A2B9E6\">\n";
		}
		else {
			echo "<tr bgcolor=\"#B7C8EA\">\n";
		}
		
		gen_cell($top + $i++);
		gen_cell("<a href=\"user.php?uid=$user->uid\">$user->nickname</a>");
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
<?php echo $page_string; }?>
</div>

