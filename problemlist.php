<?php
if(!isset($MAGICAL))
	include("index.php");
else
{
?>
<!--Search Division-->
<div align = "center">
<form name = "formSearchProblem" action = "index.php?view=problemlist" 
			method = "post" onsubmit = "return checkSearchProblemItems()" align = "center">
	<p>
	ID
	<input type = "text" name = "pid" size = "8" maxlength = "8">
	Title
	<input type = "text" name = "title" size = "20" maxlength = "50">
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

	if(isset($_GET['top']) && $_GET['top'] > 0)
		$top = $_GET['top'];
	
	$page_string = paged_disp($conn, 'problem', null, $top, $pagesize, 'index.php?view=problemlist');
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
if(!isset($_POST['submit']))
{
	$top--;
	$sql = "select pid, problemName, accepted, submitted from problem limit $top, $pagesize";
	$top++;
}
else
{
	$sql = "select pid, problemName, accepted, submitted from problem ";
	 if(trim($_POST['pid']) != "")
	{
		$sql .= "where pid = ".mysql_real_escape_string(trim($_POST['pid']));
	}
	else if(trim($_POST['title']) != "")
	{
		$sql .= "where problemName like '%".mysql_real_escape_string(trim($_POST['title']))."%'";
	}
}
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
				<a href=\"index.php?view=problem&pid=$problem->pid\">
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
