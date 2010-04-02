<?php
include("conn.php");
$result = $conn->query("select discription from problem ");
?>
<center>
<table border="1" width="80%">
<?php
while($user = $result->fetch_object())
{
	echo "<tr><td>";
	//$table = get_html_translation_table(HTML_SPECIALCHARS);
	$table["\n"] = "<br/>";
	$table["\t"] = "&nbsp;&nbsp;&nbsp;&nbsp;";
	//$table[" "] = "&nbsp;";
	$change=array('\n'=>'<br><br>');
	$change+=array('\t'=>'&nbsp;&nbsp;&nbsp;&nbsp;');
	//$change+=array(' '=>'&nbsp;');
	$x=strtr($user->discription,$change);
	echo $x."<br>";
	echo "</tr></td>";
}
?>
</table></center>
