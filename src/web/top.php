<?php
if(!isset($MAGICAL)) {
	include("index.php");
}
else {
    echo '<table>'; 
    echo '<tr>';
    echo '<td class="h"><a href="home.php">Home</a></td>';
    echo '<td class="h"><a href="problemlist.php">Problems</a></td>';
    echo '<td class="h"><a href="submitproblem.php">Submit</a></td>';
    echo '<td class="h"><a href="status.php">Status</a></td>';
    echo '<td class="h"><a href="rank.php">Rank</a></td>';
    //if not logged in, display the login and register link
    if(!isset($_SESSION['uid'])) {
        echo '<td class="h"><a href="login.php">Login</a></td>';
        echo '<td class="h"><a href="register.php">Register</a></td>';
    }
    //else display the user link
    else {
        $nickname = $_SESSION['nickname'];
        echo '<td class="h"><a href=\"user.php?uid=".$_SESSION["uid"]."\">$nickname</a></td>';
        if(!isset($_POST['submit'])) {
            echo '<td class="h"><a href=\"logout.php\">Logout</a></td>';
        }
    }
    echo '</tr>';
    echo '</table>';
}
?>
