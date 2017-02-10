<?php

  module_load_include('inc', 'dls_rest_routes', '/includes/models/dls_rest_routes.rest_route');

  function dls_rest_routes_add_route($name, $group = 'Miscellaneous') {
    $routes = variable_get('dls_rest_routes', '');
    $routes[$name] = isset($routes[$name]) ? $routes[$name] : RestRoute::make($group);
    variable_set('dls_rest_routes', $routes);
  }