<?php

  function dls_rest_routes_add_routes($routesArray) {
    $routes = variable_get('dls_rest_routes', '');
    foreach($routesArray as $name => $route) {
        $routes[$name] = isset($routes[$name]) ? $routes[$name] : $route;
    }
    variable_set('dls_rest_routes', $routes);
  }