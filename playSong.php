<?php
require 'PlayerManager.php';

static $PLAYER_BIN = "mplayer ";

// First kill any currently playing songs
PlayerManager::stop();

$output;
$return_var;

$file = $_GET['f'];
$file = urldecode($file);

$cmd = $PLAYER_BIN . "\"" . $file . "\" > /dev/null &";

error_log("Executing command: " . $cmd);

exec($cmd);

?>
