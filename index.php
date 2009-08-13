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
<title>SDU Online Judge</title>
<script type="text/javascript" src="checkers.js"></script>
</head>
<body>
<?php
include("top.php");
if(!isset($_GET['view']))
	$view = 'home.php';
else
{
	switch($_GET['view'])
	{
	case 'home':
		$view = 'home.php';break;
	case 'problem':
		$view = 'problem.php';break;
	case 'problemlist':
		$view = 'problemlist.php';break;
	case 'submitproblem':
		$view = 'submitproblem.php';break;
	case 'statistics':
		$view = 'statistics.php';break;
	case 'status':
		$view = 'status.php';break;
	case 'rank':
		$view = 'rank.php';break;
	case 'login':
		$view = 'login.php';break;
	case 'logout':
		$view = 'logout.php';break;
	case 'register':
		$view = 'register.php';break;
	case 'user':
		$view = 'user.php';break;
	case 'viewsource':
		$view = 'viewsource.php';break;
	default:
		$view = 'home.php';
		//record for accident analysis;
		error_log("Unexpected request.view:{$_GET['view']}; Remote address:{$_SERVER['REMOTE_ADDR']};"
			. "Request uri: {$_SERVER['REQUEST_URI']}");
	}
}
include($view);
include("bottom.php");
?>
</body>
</html>
