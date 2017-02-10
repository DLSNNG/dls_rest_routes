<?php

  function dls_rest_routes_get_route($name) {
    $routes = variable_get('dls_rest_routes');
    $route = isset($routes[$name]) ? $routes[$name]['path'] : 'No Route Found';
    return $route;
  }