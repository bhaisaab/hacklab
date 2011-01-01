<?php
if( isset($_POST['username']) && isset($_POST['password']) )
{
    //Here username = root, password = rohit
    $conn = mysql_connect( "localhost", "root", "root" )
        or die( "Failed to connect to database server" );

    mysql_select_db( "test", $conn )
        or die( "Failed to select the database, test" );

    $username = $_POST['username'];
    $password = $_POST['password'];

        
    $query = "select * from login where usr='$username' and pwd='$password';";
    $result = mysql_query( $query )
            or die( "could not execute query to verify the user's authenticity." );

    if( mysql_num_rows($result) != 1 )
    {
        mysql_close( $conn );
        header( "location:index.php?msg=fail" );
        exit;
    }

    $row = mysql_fetch_array( $result, MYSQL_ASSOC );

    setcookie( 'username', $username, time()+3600 );
    setcookie( 'password', $password, time()+3600 );
    mysql_close( $conn );

    header( "location:index.php?msg=success" );
    exit;
}
else
{
	header( "location:index.php?msg=invalid" );
	exit;
}
?>
