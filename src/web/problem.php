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
	echo "<div align = \"left\"><h3>$title</h3></div>\n";
	echo "<div>$content</div>\n";
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
echo "<center><h2>$problem->problemName</h2></center>\n";
//limitations and statistics area
echo "<div align = \"center\"><table>";
echo "<tr><td width = \"140\">Time Limit:</td><td width = \"80\">{$problem->timeLimit}ms</td>";
echo "<td width = \"140\">Memory Limit:</td><td width = \"80\">{$problem->memoryLimit}Kib</td></tr>";
echo "<tr><td width = \"140\">Accepted:</td><td width = \"80\">$problem->accepted</td>";
echo "<td width = \"140\">Submitted:</td><td width = \"80\">$problem->submitted</td></tr>\n";
echo "</table></div>\n";
//problem discription area
echo "<div align = \"left\">";
gen_section("DISCRIPTION", my_htmlentities($problem->discription));
gen_section("INPUT", my_htmlentities($problem->input));
gen_section("OUTPUT", my_htmlentities($problem->output));
gen_section("INPUT CASE", my_htmlentities($problem->inputCase));
gen_section("OUTPUT CASE", my_htmlentities($problem->outputCase));
echo "</div>";
echo "<div align = \"center\">\n";
echo "<a href=\"submitproblem.php?pid=$pid\">Submit</a>";
echo "&nbsp;&nbsp;&nbsp;&nbsp;";
echo "<a href=\"statistics?pid=$pid\">Statistics</a>";
echo "</div>\n";
?>
</div>
<?php
}
?>
