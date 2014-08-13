<?php

class KernelWrapper
{
	private $runningPIDs;

	function __construct()
	{
		$runningPIDs = array();
	}

	function __destruct()
	{
		//TODO: Destroy all pids
	}

	function execute($cmd, $bgd)
	{
		static $SUCCESS = 0;

		if($bgd)
		{
			$whoami = exec('whoami');
			error_log("Running in background as $whoami");
			$cmd = $cmd . " &";
		}
		
		$return_var;

		error_log("Running command: ".$cmd);

		exec($cmd, $return_var);

		if($return_var == $SUCCESS)
			$runningPIDs[] = 12; // Add_TO-PIDS
	}
}

?>