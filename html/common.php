<?php
if(!isset($MAGICAL))
	include("index.php");
else
{
$LANGUAGE[] = "All";
$LANGUAGE[] = "C++";
$LANGUAGE[] = "C";
$LANGUAGE[] = "JAVA";

$JUDGE_STATUS[] = "All";
$JUDGE_STATUS[] = "Queueing";
$JUDGE_STATUS[] = "Judging";
$JUDGE_STATUS[] = "Accepted";
$JUDGE_STATUS[] = "Wrong Answer";
$JUDGE_STATUS[] = "Time Limit Exceeded";
$JUDGE_STATUS[] = "Memory Limit Exceeded";
$JUDGE_STATUS[] = "Compile Error";

function alert($msg)
{
	echo "<script>alert(\"$msg\");</script>";
}

function go_back()
{
	echo "<script>history.back();</script>";
}

function alert_and_go_back($msg)
{
	echo "<script>alert(\"$msg\");history.back();</script>";
}

function alert_and_redirect($msg, $href)
{
	echo "<script>alert(\"$msg\");location.href = \"$href\";</script>";
}

function redirect($href)
{
	echo "<script>location.href=\"$href\";</script>";
}

function gen_cell($content, $align = "center")
{
	echo "<td align = \"$align\">$content</td>\n";
}

function my_htmlentities($string)
{
	//return htmlentities($string, ENT_COMPAT, 'UTF-8');
	$table = get_html_translation_table(HTML_SPECIALCHARS);
	$table["\n"] = "<br/>";
	$table["\t"] = "&nbsp;&nbsp;&nbsp;&nbsp;";
	return strtr($string, $table);
}
/*
 * $conn: the database connection used
 * $tables: tables separated with comma to be queryed into
 * $condition: the where clause
 * $top: 
 * $pagesize:
 * $order: order by clause
 * $href:the address prefix
 * $bNextPrevOnly:
 */
function paged_disp($conn, $tables, $condition, $top, $pagesize, $href,  $bNextPrevOnly = false)
{
	$page_string = "";
	$sql = "select count(*) from $tables " . ($condition? "where $condition": "");
	if($result = $conn->query($sql))
	{
		list($size) = $result->fetch_row();
		if($size > $pagesize)
		{
			$page_number = (int)(($size - 1) / $pagesize) + 1;//total number of pages
			$t = ($top - $pagesize > 0)? $top - $pagesize: 1;//top of current processed page
			$page = (int)(($top - 1) / $pagesize) + 1;//current page
			$page_string .= "<a href=\"$href&top=$t\">&lt;Prev</a>\n";
			if(!$bNextPrevOnly)
			{
				for($i = 1; $i <= $page_number; $i++)
				{
					if($page == $i)
					{
						$page_string .= $i."\n";
					}
					else
					{
						$t = ($i - 1) * $pagesize + 1;
						$page_string .= "<a href=\"$href&top=$t\">$i</a>\n";
					}
				}
			}
			$t = ($top + $pagesize > $size)? $top: $top + $pagesize;
			$page_string .= "<a href=\"$href&top=$t\">Next&gt;</a>\n";
		}
	}
	else
	{
		error_log($conn->error." File:".__FILE__."; Line: ".__LINE__."; Sql string: $sql");
	}
	return $page_string;
}
}
?>
