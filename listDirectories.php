<?php
$dir = $_GET['d'] . "/";

error_log("scanning " . $dir . " for directories");

$files = scandir($dir);

echo "<tr><td class=\"table_header\">DIRECTORIES</tr></td>";

foreach($files as $f)
{
	$full_path= $dir . $f;
	if(is_dir($full_path) && !isHiddenDir($f))
	{
		echo "<tr class=\"dir_cell\" onclick='moveToDir(\"" .$full_path ."\")'><td>".$f."</td></tr>";
	}
}

function isHiddenDir($dir)
{
	error_log("Is hidden directory: " . $dir . " ? ");

	if($dir == "..")
	{
		return false;
	}

	if(substr($dir,0,1) == '.')
	{
		return true;
	}
	return false;
}

?>