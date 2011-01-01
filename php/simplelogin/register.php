<?php
if( isset($_POST['username']) && isset($_POST['password']) )
{
    $conn = mysql_connect( "localhost", "root", "root" )
        or die( "Failed to connect to database server" );

    mysql_select_db( "test", $conn )
        or die( "Failed to select the database, test" );

    $username = $_POST['username'];
    $password = $_POST['password'];

	$query = "select * from login where usr='$username';";
	$result = mysql_query( $query )
			or die( "could not execute query to verify the user's authenticity." );
    
    if( mysql_num_rows($result) != 0 )
    {
        mysql_close( $conn );
        header( "location:index.php?msg=regfail" );
        exit;
    }

    $query = "insert into login (usr, pwd) VALUES ('$username', '$password')";
    $result = mysql_query( $query )
    or die( "Unable to register values in DB. Error!" );
 
    mysql_close( $conn );
    header( "location:index.php?msg=regsuccess" );
    exit;
}
else
{
	header( "location:index.php?msg=invalid" );
	exit;
}
?>
