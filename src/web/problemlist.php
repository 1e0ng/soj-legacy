<?php
if(!isset($MAGICAL))
{
	$view = "problemlist.php";
	include "index.php";
}
else
{
	$title = "";
	if(isset($_POST['pid'])) {
		$pid = (int)$_POST['pid'];
    }
	if(isset($_POST['title'])) {
		$title = trim($_POST['title']);
    }
    
?>

    <form name = "formSearchProblem" action = "problemlist.php" 
         method = "post" onsubmit = "return checkSearchProblemItems()">
         ID
         <input type="text" name="pid" value="<?php echo isset($pid) ? $pid : ""; ?>" size="8" maxlength="8">
         Title
         <input type="text" name="title" value="<?php echo $title; ?>" size="20" maxlength="50">
         <input type = "submit" name = "submit" value = "Go">
         </form>
<?php

         include "conn.php";
	include "common.php";
	$pagesize = 20;
	$top = 1;

	$href_prefix = "problemlist.php";
	$sql_condition = "";
	if(!empty($pid)) {
		$href_prefix .= "?pid=$pid";
		$sql_condition = "pid=" . $conn->real_escape_string($pid);
	}
	if(!empty($title)) {
		$href_prefix .= "?title=".urlencode($title);
        if (!empty($sql_condition)) {
            $sql_condition .= " and ";
        }
		$sql_condition .= " problemName like '%" . $conn->real_escape_string($title)."%'";
	}
    
	if(isset($_GET['top']) && $_GET['top'] > 0)
		$top = (int)$_GET['top'];
	
	$page_string = paged_disp($conn, 'problem', $sql_condition, $top, $pagesize, $href_prefix);
	echo $page_string;

    ?>
	<table border="1">
         <tr>
         <th>ID</th>
         <th>Title</th>
         <th>Accept Ratio</th>
         </tr>
         <?php

         $top--;
    $sql = "select pid, problemName, accepted, submitted from problem "
        .($sql_condition ? "where $sql_condition ": "")."order by pid"." limit $top, $pagesize";
    //var_dump($sql);
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
                echo "<td>
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
    echo "</table>";
    echo $page_string;
}
?>
