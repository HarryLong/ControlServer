<?php
require 'Page.inc';
require 'KernelWrapper.inc';

class ControllerPage extends Page
{
  public $PAGE_TITLE = "Harry's Controller";
  private $kernelWrapper;

  function __construct()
  {
        parent::__construct($this->PAGE_TITLE);
        $this->kernelWrapper = new kernelWrapper();
  }

  public function ptintWhoAmI()
  {
  }

  protected function echoBody()
  {
      ?>
        <input type="submit" onclick='playsong("ayawaska-HOT.mp3")' value="play" />
      <?php
  }
  
  protected function echoJS()
  {
        ?>
        <script type="text/javascript">
        function playsong(song)
        {
          alert(song);
        }
        </script>; 
        <?php
  }
  
  protected function echoCSS()
  {
        ?>
        <?php
  }

  public function select() {
      echo "The select function is called.";
      exit;
  }

  public function insert() {
      echo "The insert function is called.";
      exit;
  }

  protected function execute()
  {
    $this->kernelWrapper->execute("/usr/bin/mplayer /home/harry/passport/fat32/Music/ayawaska-HOT.mp3", true);
  }
}
