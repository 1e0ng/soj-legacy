<?php
session_start();

$MAGICAL = 'DWP';//this is a flag which used to test whether a page is requeted directly
$DEBUG = true;
if($DEBUG)
	error_reporting(E_ERROR|E_NOTICE|E_STRICT);
?>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Small Online Judge</title>
<script type="text/javascript" src="checkers.js"></script>
</head>
<body>
<?php
include("top.php");
if(!isset($view))
	$view = 'home.php';
?>
<center>
<table style="BORDER-RIGHT: 5px; BORDER-TOP: 1px ; BORDER-LEFT: 5px; BORDER-BOTTOM: 1px" cellSpacing=1 cellPadding=1 width="90%" border=0>
<tr><td>
<?php
include($view);
?>
</td></tr>
</table>
</center>
<?php
include("bottom.php");
?>
</body>
</html>
