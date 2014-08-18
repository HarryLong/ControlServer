<?php
$cmd = ""
$output;
$return_var;

$file = $_GET['d'];

$cmd = "ls "

error_log("Going to execute command: " . $cmd);

exec($cmd, $output, $return_var);

error_log("Return code: " . $return_var);

?>