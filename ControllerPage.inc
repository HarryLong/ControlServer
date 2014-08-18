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
        <input type="submit" onclick='playsong("/mnt/passport/fat32/Music/ayawaska-HOT.mp3")' value="play" />
        <div id="current_dir">/</div>
        <table id="directories">
        </table>
        </div>
      <?php
  }
  
  protected function echoJS()
  {
        ?>
        <script type="text/javascript">
        function playsong(song)
        {
          // code for IE7+, Firefox, Chrome, Opera, Safari
          xmlhttp=new XMLHttpRequest();
          xmlhttp.onreadystatechange=function() {
            if (xmlhttp.readyState==4 && xmlhttp.status==200) {
              document.getElementById("response").innerHTML=xmlhttp.responseText;
            }
          }
          xmlhttp.open("GET","playSong.php?f="+song,true);
          xmlhttp.send();
        }

        function moveToDir(directory)
        {
          xmlhttp=new XMLHttpRequest();
          xmlhttp.onreadystatechange=function() {
            if (xmlhttp.readyState==4 && xmlhttp.status==200) {
              document.getElementById("response").innerHTML=xmlhttp.responseText;
            }
          }
          xmlhttp.open("GET","playSong.php?f="+song,true);
          xmlhttp.send();
        }

        function upOneDir()
        {
          var currentDir = document.getElementById("current_dir").innerHTML;
          var upDirStrIdx = current_dir.lastIndexOf("/");
          if(upIdx != 0)
          {
            var upDirIdx = 
          }
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
}
