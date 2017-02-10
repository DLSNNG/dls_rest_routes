<?php

  module_load_include('inc', 'dls_rest_routes', '/includes/models/dls_rest_routes.rest_routes');

/**
 * @file Defines DLS REST Routes Admin page
 */

/**
 *
 * @param array $form
 * @param array $form_state
 */
function dls_rest_routes_configuration_form($form, &$form_state) {
  $restRoutes = RestRoutes::get();
  //inform user if no routes are found
  if($restRoutes->numRoutes() == 0) {
    $form['No items'] = array(
      '#type' => 'markup',
      '#markup' => 'It doesn\'t look like any routes have been defined yet',
      '#prefix' => '<p>',
      '#suffix' => '</p>',
    );
  }
  else {
    //display a collapsable fieldset for each group of routes
    foreach($restRoutes->groups as $group => $routes) {
      //add fieldset
      $form[$group] = array(
        '#type' => 'fieldset',
        '#title' => t($group),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      foreach($routes as $name => $path) {
        //add route to appropriate fieldset
        $formName = replace_space($name); //spaces not handled well by drupal form values
        $form[$group][$formName] = array(
          '#type' => 'textfield',
          '#title' => $name,
          '#default_value' => isset($path) ? $path : '',
        );
      }
    }
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  return $form;
}

function dls_rest_routes_configuration_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $restRoutes = RestRoutes::get();
  $groups = $restRoutes->groups;
  foreach($groups as $group => $routes) {
    foreach($routes as $name => $path) {
      $formName = replace_space($name); //need to match the name that was passed in form values
      $newPath = isset($values[$formName]) ? $values[$formName] : '';
      $restRoutes->setRoute($group, $name, $newPath); 
    }
  }
  $restRoutes->save();
}

function replace_space($text) {
  return str_replace(' ', '%20', $text);
}