<?php

  class RestRoute {
    
    public static function make($name, $path = '') {
      $route = array(
        'name' => $name,
        'path' => $path,
      );
      return $route;
    }
  
  }