<?php
require 'Page.inc';
require 'KernelWrapper.inc';

class ControllerPage extends Page
{
  public $PAGE_TITLE = "Harry's Controller";

  function __construct()
  {
        parent::__construct($this->PAGE_TITLE);
  }

  protected function echoBody()
  {
      ?>
      <body onload="init()">
        <div id="now_playing_container">
          <input id="btn_stop" type="image" src="./images/stop.png" onclick="stopSong()">
          <b> Now playing: </b> <span id="now_playing_txt">;
        </div>
        <div id="root_container">
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
          // // code for IE7+, Firefox, Chrome, Opera, Safari
          xmlhttp=new XMLHttpRequest();
          xmlhttp.open("GET","playSong.php?f="+song,true);
          xmlhttp.send();

          // Set song name
          setNowPlaying(formatSongName(song));
        }

        function formatSongName(fullpath)
        {
          var decodedSong = decodeURIComponent(fullpath);
          decodedSong = decodedSong.substring(decodedSong.lastIndexOf("/")+1, decodedSong.length-3);
          decodedSong = decodedSong.replace(/\+/g,' ');
          return decodedSong;
        }

        function setNowPlaying(song)
        {
          document.getElementById("now_playing_container").style.display="inline";
          document.getElementById("now_playing_txt").innerHTML = song;
        }

        function stopSong()
        {
          xmlhttp=new XMLHttpRequest();
          xmlhttp.open("GET","stopPlaying.php",true);
          xmlhttp.send();
          document.getElementById("now_playing_txt").innerHTML = "";
          document.getElementById("now_playing_container").style.display="none";
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
        #now_playing_container{
          z-index: -1;
          height: 40px;
          display: none;
        }
        #btn_stop{
          height:40px;
          padding-right: 5px;
        }
        #info_div {
          padding-top: 5px;
          padding-bottom: 5px;
        }
        body{
          background-color: #99FF66;
        }
        </style>
        <?php
  }
}
