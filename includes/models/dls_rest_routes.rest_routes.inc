<?php

  module_load_include('inc', 'dls_rest_routes', '/includes/models/dls_rest_routes.rest_credentials');

  class RestRoutes {
    
    var $groups;
    
    //keep this private so nobody else can instantiate this singleton
    private function __construct() {
        $this->groups = variable_get('dls_rest_routes', array());
    }
    
    public function setRoute($group, $name, $path = '') {
      $this->groups[$group][$name] = $path;
      return $this; //for method chaining
    }
    
    public function removeRoute($group, $name) {
      unset($this->groups[$group][$name]);
      return $this; //for method chaining
    }
    
    public function getRoutesForGroup($group) {
      $routes = $this->groups[$group];
      return $routes;
    }
    
    public function removeGroup($group) {
      unset($this->groups[$group]);
      return $this; //for method chaining
    }
    
    public function numRoutes() {
      $count = 0;
      foreach($this->groups as $group => $routes) {
        foreach($routes as $name => $path) {
          $count++;
        }
      }
      return $count;
    }
    
    public function getPathFor($group, $name) {
      $group = $this->groups[$group];
      $path = $group[$name];
      return $path;
    }
    
    public function getPathWithCredentialsFor($group, $name) {
      $path = $this->getPathFor($group, $name);
      $pathWithCredentials = RestCredentials::get()
        ->appendCredentialsToPath($path, $group);
      return $pathWithCredentials;
    }
    
    public function save() {
      variable_set('dls_rest_routes', $this->groups);
      return $this; //for method chaining
    }
    
    public static function get() {
      //follows the singleton pattern
      static $inst = null;
      if($inst === null) {
        $inst = new RestRoutes();
      }
      return $inst;
    }
  
  }