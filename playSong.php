<?php
static $PLAYER_BIN = "/usr/bin/mplayer ";
$output;
$return_var;

$file = $_GET['f'];

$cmd = $PLAYER_BIN . $file . " > /dev/null &";

error_log("Going to execute command: " . $cmd);


exec($cmd, $output, $return_var);

error_log("Return code: " . $return_var);

?>