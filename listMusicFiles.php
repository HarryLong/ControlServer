<?php
$dir = $_GET['d'] . "/";

error_log("scanning " . $dir . " for files");

$files = scandir($dir);

echo "<tr><td class=\"table_header\">FILES</tr></td>";

foreach($files as $f)
{
	$full_path= $dir . $f;
	$full_path = urlencode($full_path);

	if(!is_dir($full_path) && isMp3($f))
	{
		error_log("Inserting" . "<tr class=\"song_cell\" ondblclick='playsong(\"" .$full_path ."\")'><td>".$f."</td></tr>");
		echo "<tr class=\"song_cell\" onclick='playsong(\"" .$full_path ."\")'><td>".$f."</td></tr>";
	}
}

function isMp3($str)
{
	return (substr($str, -3) == "mp3");
}

?>
