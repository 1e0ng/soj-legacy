<?php
if (!isset($MAGICAL)) {
	$view = "about.php";
	include("index.php");
}
else {
?>

<pre class="content">

<a href="about.php">About</a>

SOJ (Small Online Judge) is designed and
developed by <a href="mailto:powerx1202@gmail.com">Wilbur Ding</a> and <a href="http://liangsun.org">Liang Sun</a>.

The SOJ project is an open source project, under
the <a href="http://www.gnu.org/licenses/old-licenses/gpl-2.0.html">GNU GPL v2</a> license. Anyone can download
the source code of SOJ from <a href="http://soj.googlecode.com">Google Code</a>.

If you find bugs or have advices for SOJ, please
submit it <a href="http://code.google.com/p/soj/issues/list">here</a>.

</pre>
<?php
}
