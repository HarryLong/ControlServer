<?php

class PlayerManager{
	static function stop()
	{
		exec("sudo pkill mplayer");
	}
}

?>
