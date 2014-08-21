<?php

class PlayerManager{
	static function stop()
	{
		exec("pkill mplayer");
	}
}

?>