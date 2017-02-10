<?php

  module_load_include('inc', 'dls_rest_routes', '/includes/models/dls_rest_routes.rest_routes');

  class RestCredentials {
    
    var $routes;
    
    //keep this private so nobody else can instantiate this singleton
    private function __construct() {
        $this->groups = variable_get('dls_rest_credentials', array());
    }
    
    public function setCredentials($group, $username = '', $password = '') {
      $this->groups[$group] = array(
        'username' => $username,
        'password' => $password,
      );
      return $this; //for method chaining
    }
    
    public function removeCredentials($group) {
      unset($this->groups[$group]);
      return $this; //for method chaining
    }
    
    public function getCredentialsFor($group) {
      $credentials = isset($this->groups[$group]) ? $this->groups[$group] : FALSE;
      return $credentials;
    }
    
    public function appendCredentialsToPath($path, $group) {
      $credentials = $this->getCredentialsFor($group);
      $credentialPrefix = $credentials['username'] . ':' . $credentials['password'] . '@';
      $pathArray = explode('://', $path);
      $pathArray[1] = $credentialPrefix . $pathArray[1];
      $newPath = implode('://', $pathArray);
      return $newPath;
    }
    
    public function save() {
      variable_set('dls_rest_credentials', $this->groups);
      return $this; //for method chaining
    }
    
    public static function get() {
      //follows the singleton pattern
      static $inst = null;
      if($inst === null) {
        $inst = new RestCredentials();
      }
      return $inst;
    }
  
  }