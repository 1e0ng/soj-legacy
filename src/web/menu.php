<?php
if(!isset($MAGICAL)) {
	include("index.php");
}
else {
?>
<ul id="menu">
<li class="bar"><a href="problemlist.php">Problems</a>
<ul><li><a href="problemlist.php">View Problems</a></li><li><a href="problemlist.php">Find Problems</a></li></ul>
</li>
<li class="bar"><a href="login.php">Accounts</a>
<ul><li><a href="login.php">Login</a></li><li><a href="register.php">Register</a></li><li><a href="#">My Profile</a></li><li><a href="logout.php">Logout</a></li></ul>
</li>
<li class="bar"><a href="status.php">Statistics</a>
<ul><li><a href="rank.php">Rank List</a></li><li><a href="status.php">Explore</a></li></ul>
</li>
<li class="bar"><a href="#">Help</a>
<ul><li><a href="help.php">The Tour</a></li><li><a href="fqa.php">FQA</a></li><li><a href="about.php">About</a></li></ul>
</li>


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
