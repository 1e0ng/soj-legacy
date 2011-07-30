<?php
if(!isset($MAGICAL))
{
	$view = "problem.php";
	include("index.php");
}
else
{
include("conn.php");
include("common.php");

//generate section titles such like discription, InputCase, etc
function gen_section($title, $content)
{
	echo "<div>$title</div>\n";
	$change_array=array('\n'=>'<br>');
	$content=strtr($content,$change_array);
	//echo "<div style=\"word-break:break-all\">$content</div>\n";
	echo $content;
}

//pid must be numeric
if(isset($_GET['pid']) && is_numeric($_GET['pid']) && $_GET['pid'] > 0)
{
	$pid = (int)$_GET['pid'];
}
else
	alert_and_go_back("Problem not existed!");
?>
<div>
<?php
$sql = "select pid, problemName, accepted, submitted, discription, input, output, inputCase,
	outputCase, timeLimit, memoryLimit from problem where pid = $pid";
if($result = $conn->query($sql))
{
	if(!($problem = $result->fetch_object()))
	{
		alert_and_go_back("No problem returned!");
		die();
	}
}
else
{
	error_log($conn->error." File:".__FILE__."; Line: ".__LINE__."; Sql string: $sql");
	die("Database Error.");
}
//title area

echo "<h2>$problem->problemName</h2>\n";
//limitations and statistics area
?>
<table width="100%" border="0" background="table_back.jpg">
  <tr>
    <td>
<div align = "center"><table>
<tr><td width = "140">Time Limit:</td><td width = "80"><?=$problem->timeLimit?>ms</td>
<td width = "140">Memory Limit:</td><td width = "80"><?=$problem->memoryLimit?>KB</td></tr>
<tr><td width = "140">Accepted:</td><td width = "80"><?=$problem->accepted?></td>
<td width = "140">Submitted:</td><td width = "80"><?=$problem->submitted?></td></tr>
</table></div>
<?
//problem discription area
/*
gen_section("DISCRIPTION", my_htmlentities($problem->discription));
gen_section("INPUT", my_htmlentities($problem->input));
gen_section("OUTPUT", my_htmlentities($problem->output));
gen_section("INPUT CASE", my_htmlentities($problem->inputCase));
gen_section("OUTPUT CASE", my_htmlentities($problem->outputCase));
 */
$infile="problem/{$problem->pid}.htm";
include $infile;
echo "<div align = \"center\">\n";
echo "<a href=\"submitproblem.php?pid=$pid\">Submit</a>";
echo "&nbsp;&nbsp;&nbsp;&nbsp;";
echo "<a href=\"statistics.php?pid=$pid\">Statistics</a>";
echo "</div>\n";
?>
</div>
</td>
  </tr>
</table>
<?php
}
?>
