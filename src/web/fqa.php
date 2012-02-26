<?php
if (!isset($MAGICAL)) {
	$view = "fqa.php";
	include("index.php");
}
else {
?>

<pre class="content">

<a href="fqa.php">FQA (Frequently Asked Questions)</a>

1. What's SOJ?
SOJ means Small Online Judge.

2. What's Online Judge?
Find the most accurate defination at <a href="http://en.wikipedia.org/wiki/Online_judge">wikipedia</a>.

3. What's A+B problem?
A+B problem is a very simple problem, simply read pairs
of two integer number and output a sum for each pair.
A+B problem is generally used to guide you to become
familiar with a online judge system.

4. Could you give me a sample code for A+B problem? 
For C++ Language:
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
For C language:
<div>
#include &lt;stdio.h&gt;
int main(void) {
    int a, b;
    while (scanf("%d%d", &amp;a, &amp;b) != EOF) {
        printf("%d", a + b);
    }
    return 0;
}
</div>
For Java language:
<div>
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        while (in.hasNext()) {
            int a = in.nextInt();
            int b = in.nextInt();
            System.out.println(a + b);
        }
    }
}
</div>
For Pascal language:
<div>
program p1001(Input,Output); 
var 
  a,b:Integer; 
begin 
  while not eof(Input) do 
    begin 
      Readln(a, b); 
      Writeln(a + b); 
    end; 
end.
</div>
</pre>
<?php
}
