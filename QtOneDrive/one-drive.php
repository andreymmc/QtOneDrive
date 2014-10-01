<?

$PORT = 54432;
$code = @$_GET['code'];
$error = @$_GET['error_description'];

if( $code != "" )
    header( "Location: http://localhost:$port?code=@@@[$code]@@@" );
else if( $error != "" )
    header( "Location: http://localhost:$port?error=@@@[$error]@@@" );
else
{
var_dump($_GET);
echo "<hr>";
var_dump($_POST);
//der( "Location: http://localhost:$port?success=1" );

}
