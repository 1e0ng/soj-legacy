<?php
if(!isset($MAGICAL))
{
	$view = "problem.php";
	include "index.php";
}
else
{
include "conn.php";
include "common.php";

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
<table border="1">
  <tr>
    <td>
<table border="1">
     <tr><td>Time Limit:</td><td><?php echo $problem->timeLimit; ?>ms</td>
     <td>Memory Limit:</td><td><?php echo $problem->memoryLimit; ?>KiB</td></tr>
     <tr><td>Accepted:</td><td><?php echo $problem->accepted; ?></td>
     <td>Submitted:</td><td><?php echo $problem->submitted; ?></td></tr>
</table>
<?php
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

echo "<a href=\"submitproblem.php?pid=$pid\">Submit</a>";

echo "<a href=\"statistics.php?pid=$pid\">Statistics</a>";

?>
</td>
  </tr>
</table>
<?php
}
?>
