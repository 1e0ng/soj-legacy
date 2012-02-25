<?php
if (!isset($MAGICAL)) {
	$view = "help.php";
	include("index.php");
}
else {
?>

<pre class="content">

<a href="help.php">The Tour</a>

1. <a href="register">Register</a> an account freely.
2. Once you have an account, you can login with
   it. (You needn't to login immediately after
   you registered an account.)
3. <a href="problemlist.php">View Problems</a>, and find one, for example,
   the A+B problem.
4. You need to write a program to solve this
   problem. Here is a sample code in C++
   language:
<div>
#include &lt;iostream&gt;
using namespace std;
int main() {
    int a, b;
    while (cin &gt;&gt; a &gt;&gt; b) {
        cout &lt;&lt; a + b &lt;&lt; endl;
    }
    return 0;
}
</div>
5. Copy the code to <a href="submitcode.php">Submit Code</a>, and Submit.
6. View the result at <a href="status.php">Realtime Status</a>.

</pre>
<?php
}
