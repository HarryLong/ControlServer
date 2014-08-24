<?php
require 'Page.inc';
require 'KernelWrapper.inc';

class ControllerPage extends Page
{
  public static $PAGE_TITLE = "Harry's Controller";
  public static $LAN_ADDRESS = "10.0.0.25/";
  public static $WAN_ADDRESS = "http://strawberrypi.no-ip.org/";

  public $local;
  public $address;

  function __construct()
  {
      parent::__construct(ControllerPage::$PAGE_TITLE);
  }

  public static function internal($from_lan)
  {
    $instance = new self();
    $instance->local = true;
    if($from_lan)
    {
      $instance->setAddress(ControllerPage::$LAN_ADDRESS);
    }
    else
    {
      $instance->setAddress(ControllerPage::$WAN_ADDRESS);
    }
    return $instance;
  }

  public static function external()
  {
    $instance = new self();
    $instance->local = false;

    return $instance;
  }


  public function setAddress($address)
  {
    $this->address = $address;
  }

  protected function echoBody()
  {
      ?>
      <body onload="init()">
        <?php
        if($this->local)
        {
          ?>
          <div id="player">
          <audio id="audio_controller" controls="controls">
            <source id="audio_src" type="audio/mpeg" />
            Your browser does not support the audio element.
          </audio>
          <?php
        }
        else
        {
          ?>
          <div id="player">
            <input id="btn_stop" type="image" src="./images/stop.png" onclick="stopSong()">
            <b> Now playing: </b> <span id="now_playing_txt">;
          </div>
          <?php
        }
        ?>
        <div id="root_container">
          <div class="horizontal_line"/>
          <div id="title_container">
            <h1 id="title_text"> Harry's Raspberry PI Controller</h1>
          </div>
          <div class="horizontal_line"/>
          <div id="info_div"> 
            <b>Current directory: </b> <span id='current_dir'/>
          </div>
        
          <!-- DIRECTORIES TABLE -->
          <div class="left_column">
            <table border="1" id="directories_table">
              <!-- <tr><td>HELLO</tr></td> -->
            </table>
          </div>

          <!-- FILES TABLE -->
          <div class="right_column">
            <table border="1" id="files_table">
              <!-- <tr><td>GOOD BYE</tr></td> -->
            </table>
          </div>
        </div>
      </body>
      <?php
  }
  
  protected function echoJS()
  {
        ?>
        <script type="text/javascript">
        function playsong(song)
        {
        <?php
          if($this->local)
          {
            ?>
            
            var controller = document.getElementById('audio_controller');
            var source = document.getElementById('audio_src');
            var url = decodePHPURIComponent(song);
            // url = url.replace("/home/harry/", self->address);
            alert("Playing song: " + url);
            source.src=url;
            controller.load(); //call this to just preload the audio without playing
            controller.play(); //call this to play the song right away

            <?php
          }
          else
          {
            ?>
            xmlhttp=new XMLHttpRequest();
            xmlhttp.open("GET","playSong.php?f="+song,true);
            xmlhttp.send();

            // Set song name
            setNowPlaying(formatSongName(song));
            <?php
          }
          ?>
        }

        function formatSongName(fullpath)
        {
          var decodedSong = decodePHPURIComponent(fullpath);
          decodedSong = decodedSong.substring(decodedSong.lastIndexOf("/")+1, decodedSong.length-3); // Get just the song name
          return decodedSong;
        }

        function decodePHPURIComponent(component)
        {
          var decoded = decodeURIComponent(component);
          decoded = decoded.replace(/\+/g,' ');
          return decoded;
        }

        function setNowPlaying(song)
        {
          document.getElementById("now_playing_txt").innerHTML = song;
        }

        function stopSong()
        {
          xmlhttp=new XMLHttpRequest();
          xmlhttp.open("GET","stopPlaying.php",true);
          xmlhttp.send();
          document.getElementById("now_playing_txt").innerHTML = "";
        }

        function getCurrentDir()
        {
          var currentDir = document.getElementById("current_dir").innerHTML;
          currentDir = currentDir.trim();
          return currentDir;
        }

        function setCurrentDir(dir)
        {
          document.getElementById("current_dir").innerHTML = dir;
        }

        function moveToDir(directory)
        {
          directory = formatDir(directory);

          // var audioElement = document.getElementById('browser_song');
          // audioElement.setAttribute('src', directory);
          // // audioElement.play();

          // First update the directories table
          setCurrentDir(directory);

          xmlhttp1=new XMLHttpRequest();
          xmlhttp1.onreadystatechange=function() {
            if (xmlhttp1.readyState==4 && xmlhttp1.status==200) {
              document.getElementById('directories_table').innerHTML=xmlhttp1.responseText;
            }
          }

          // First clear the table
          xmlhttp1.open("GET","listDirectories.php?d="+directory,true);
          xmlhttp1.send();


          // Now update the files table
          xmlhttp2=new XMLHttpRequest();
          xmlhttp2.onreadystatechange=function() {
            if (xmlhttp2.readyState==4 && xmlhttp2.status==200) {
              document.getElementById('files_table').innerHTML=xmlhttp2.responseText;
            }
          }
          // First clear the table
          xmlhttp2.open("GET","listMusicFiles.php?d="+directory,true);
          xmlhttp2.send();
        }

        function init()
        {
          moveToDir('/home/harry');
          stopSong();
        }

        function formatDir(directory)
        {
          var lastIdx = directory.lastIndexOf("..");
          if(lastIdx != -1)
          {
            // remove the first
            for(i = 0; i < 2; i++)
            {
                directory = directory.substring(0, directory.lastIndexOf("/"));
            }
          }
          return directory;
        }

        </script>
        <?php
  }
  
  protected function echoCSS()
  {
        ?>
        <style>
        .left_column{
          float: left;
          width: 50%;
        }
        .right_column{
          float: right;
          width: 50%;
        }
        #directories_table {
          width: 100%;
        }
        #files_table {
          width: 100%;
        }
        #root_container{
          width: 100%;
        }
        #title_container{
          text-align: center;
          vertical-align: center;
          padding-top: 5px;
          padding-bottom: 5px;
        }
        .song_cell:hover{
          cursor: pointer;
          background-color: white;
          font-weight: bold;
        }
        .dir_cell:hover{
          cursor: pointer;
          background-color: white;
          font-weight: bold;
        }
        .dir_cell{
          padding-top: 10px;
        }
        .song_cell{
          padding-top: 2px;
        }
        .table_header{
          background-color: black;
          color: white;
          text-align: center;
          font-weight: bold;
          font-size: 20px;
        }
        .horizontal_line{
          width: 100%;
          height: 2px;
          background-color: black;
        }
        #player{
          height: 40px;
        }
        #btn_stop{
          height:20px;
          padding-right: 5px;
        }
        #info_div{
          padding-top: 10px;
          padding-bottom: 10px;
        }
        body{
          background-color: #99FF66;
        }
        </style>
        <?php
  }
}
