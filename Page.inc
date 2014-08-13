<?php
abstract class Page
{
  public $title;
  function __construct($title)
  {
	   $this->title = $title;
  }  

  public function display()
  {
    echo "<html>\n<head>\n";

    $this->echoCSS();
    $this->echoTitle();
    echo "</head>\n";
    $this->echoBody();
    $this->echoJS();

    echo "</html>\n";
  }

  protected function echoTitle()
  {
  	echo "<title>".$this->title."</title>\n";
  }
  
  protected abstract function echoBody();
  
  protected abstract function echoJS();
  
  protected abstract function echoCSS();
}
?>