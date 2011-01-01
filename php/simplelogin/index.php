<?php
	$loggedin = false;
    $msg = "Please Login";
	if( isset($_COOKIE["username"]) )
	{
		$username = $_COOKIE["username"];
        $msg = "Hello" + $username;
		$loggedin = true;
	}
    else
        echo "Not signed in";

	$messages = array(
        "success"		=>	"You have successfully Logged in.",
        "loggedout"		=>	"You have been logged out now.",
        "invalid"	=>	"This is not a valid operation.",
        "fail"		=>	"Sorry, wrong credentials.",
        "regfail"		=>	"Registration failed.",
        "regsuccess"		=>	"Registration successful, now login."
	);
	if( isset($_GET['msg']) )
		$msg = $messages[$_GET['msg']];
?>

<html>

<body>

<?php
echo <<<SYSMSG
<h4>System Message: $msg<br/><br/></h4>
SYSMSG;
?>

<br>
<p>Login here:</p>

<form method='post' action="login.php">
Enter your name :
<input name="username" type="text" size="20"><br>
Enter Password :
<input name="password" type="text" size="20"><br>
<input name="send" type="submit" id="send" value="Login">
</form>

<br>

<p>Register here:</p>
<form method='post' action="register.php">
Enter your name :
<input name="username" type="text" size="20"><br>
Enter Password :
<input name="password" type="text" size="20"><br>
<input name="send" type="submit" id="send" value="Register">
</form>


</body>
<html>
