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
<link rel="stylesheet" href="static/css.css" type="text/css" />
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js"></script>
<script type="text/javascript" src="static/js.js"></script>
</head>
<body>

<?php
include("top.php");
include("menu.php");
if(!isset($view)) {
    $view = 'home.php';
}
?>
<div id="main">
<?php
include($view);
?>
</div>
<?php
include("bottom.php");
?>

</body>
</html>
