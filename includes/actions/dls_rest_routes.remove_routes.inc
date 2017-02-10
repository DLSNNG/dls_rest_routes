<?php

  function dls_rest_routes_remove_routes($routesArray) {
    $routes = variable_get('dls_rest_routes', '');
    foreach($routesArray as $name) {
        unset($routes[$name]);
    }
    variable_set('dls_rest_routes', $routes);
  }