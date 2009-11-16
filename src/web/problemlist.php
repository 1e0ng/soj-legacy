<?php
if(!isset($MAGICAL))
{
	$view = "problemlist.php";
	include("index.php");
}
else
{
	$pid = 0;
	$title = "";
	if(isset($_GET['pid']) && $_GET['pid'])
		$pid = (int)$_GET['pid'];
	if(isset($_GET['title']))
		$title = trim($_GET['title']);
?>
<!--Search Division-->
<div align = "center">
<form name = "formSearchProblem" action = "problemlist.php" 
			method = "post" onsubmit = "return checkSearchProblemItems()" align = "center">
	<p>
	ID
	<input type="text" name="pid" value="<?php echo $pid == 0? "": $pid; ?>" size="8" maxlength="8">
	Title
	<input type="text" name="title" value="<?php echo $title; ?>" size="20" maxlength="50">
	<input type = "submit" name = "submit" value = "Go">
	</p>
</form>
<?php
if(!isset($_POST['submit']))
{
	include("conn.php");
	include('common.php');
	$pagesize = 20;
	$top = 1;

	$href_prefix = "problemlist.php";
	$sql_condition = "";
	if($pid !=  0)
	{
		$href_prefix .= "?pid=$pid";
		$sql_condition = "pid=$pid";
	}
	else if($title != "")
	{
		$href_prefix .= "?title=".urlencode($title);
		$sql_condition = "title like '%".$conn->escape_string($title)."%'";
	}

	if(isset($_GET['top']) && $_GET['top'] > 0)
		$top = (int)$_GET['top'];
	
	$page_string = paged_disp($conn, 'problem', $sql_condition, $top, $pagesize, $href_prefix);
	echo $page_string;
}
?>
<!--Table Header Division-->
	<table>
		<tr>
			<th align = "center" width = "60">ID</th>
			<th align = "left" width = "400">Title</th>
			<th align = "center" width = "80">AC Ratio</th>
		</tr>
<?php
$top--;
$sql = "select pid, problemName, accepted, submitted from problem "
	.($sql_condition? "and $sql_condition": "")." limit $top, $pagesize";
$top++;

if($result = $conn->query($sql))
{
	if($result->num_rows > 0)
	{
		//here generates the content of table
		while($problem = $result->fetch_object())
		{
			echo "<tr>";
			echo "<td>$problem->pid</td>";
			echo "<td align = \"left\">
				<a href=\"problem.php?pid=$problem->pid\">
				$problem->problemName</a></td>";
			echo "<td>";
			if($problem->submitted > 0)
				$ratio = ($problem->accepted / $problem->submitted) * 100;
			else
				$ratio = 0;
			printf("%.2f%%", $ratio);
			echo "($problem->accepted/$problem->submitted)";
			echo "</td></tr>";
		}
	}
	else
	{
		alert_and_go_back("No problem returned!");
	}
}
else
{
	error_log($conn->error." File:".__FILE__."; Line: ".__LINE__."; Sql string: $sql");	
	die("Database Error.");
}
?>
	</table>
<?php
if(!isset($_POST['submit']))
	echo $page_string;
?>
</div>
<?php
}
?>