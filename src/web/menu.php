<?php
if(!isset($MAGICAL)) {
	include("index.php");
}
else {
?>
<ul id="menu">
<li class="bar"><a href="home.php">Home</a></li>
<li class="bar"><a href="problemlist.php">Problems</a></li>
<li class="bar"><a href="#">Accounts</a></li>
<li class="bar"><a href="#">Staticstics</a></li>
<li class="bar"><a href="#">Help</a></li>
<li class="bar"><a href="#">About</a></li>


<!--
<td><a href="problemlist.php">Problems</a></td>
<td><a href="submitproblem.php">Submit</a></td>
<td><a href="status.php">Status</a></td>
<td><a href="rank.php">Rank</a></td>
<?php
    //if not logged in, display the login and register link
    if(!isset($_SESSION['uid'])) {
        echo '<td><a href="login.php">Login</a></td>';
        echo '<td><a href="register.php">Register</a></td>';
    }
    //else display the user link
    else {
        $nickname = $_SESSION['nickname'];
        echo "<td><a href=\"user.php?uid=".$_SESSION["uid"]."\">$nickname</a></td>";
        if(!isset($_POST['submit'])) {
            echo "<td><a href=\"logout.php\">Logout</a></td>";
        }
    }
    echo '</tr>';
    echo '</table></p><hr>';
}
?>
-->
</ul>
