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
if(!isset($view)) {
	$view = 'home.php';
}
include($view);
include("bottom.php");
?>

</body>
</html>
