<?php
session_start();

$MAGICAL = 'DWP';//this is a flag which used to test whether a page is requeted directly
$DEBUG = true;
if($DEBUG)
    error_reporting(E_ERROR|E_NOTICE|E_STRICT);
?>
<!doctype html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Small Online Judge</title>
<link rel="stylesheet" href="static/css.css" type="text/css" />
<script type="text/javascript" src="static/jquery-1.7.1.min.js"></script>
<script type="text/javascript" src="static/js.js"></script>
<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-35178850-1']);
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>
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
