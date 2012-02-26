<?php
if(!isset($MAGICAL)) {
	include("index.php");
}
else {
?>
<pre class="content">

Hi,

Welcome to <a href="home.php">Small Online Judge!</a>

Small Online Judge is a place where you can practise
programming with algorithm and mathematics knowledges.


To start using SOJ, just

0.<a href="register.php">Register</a> an account
1.Find a <a href="problemlist.php">Problem</a> which interests you
2.Write code to solve the problem
3.<a href="submit.php">Submit</a> your code to SOJ
4.SOJ will tell you whether your code is right or needs
  to be improved at <a href="status.php">Realtime Status</a>.


You may also view <a href="help.php">The Tour</a> or <a href="fqa.php">FQA</a> to get more information
about how to use SOJ.

Have fun!

</pre>
<?php
}
?>

