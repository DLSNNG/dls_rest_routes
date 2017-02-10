<?php

  function dls_rest_routes_remove_route($name) {
    $routes = variable_get('dls_rest_routes', '');
    unset($routes[$name]);
    variable_set('dls_rest_routes', $routes);
  }