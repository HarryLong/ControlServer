<?php
require 'ControllerPage.inc';

$page = new ControllerPage();
$page->display();

  if (isset($_POST['action'])) {
    switch ($_POST['action']) {
        case 'insert':
            echo "Insert called";
            break;
        case 'select':
            echo "Select called";
            break;
    }
  }

?>