<?
if(!isset($MAGICAL))
	include("index.php");
else
{
session_destroy();
echo "<script>history.back();</script>\n";
}
?>
