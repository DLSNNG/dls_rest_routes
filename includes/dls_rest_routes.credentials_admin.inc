<?php

  module_load_include('inc', 'dls_rest_routes', '/includes/models/dls_rest_routes.rest_credentials');

/**
 * @file Defines DLS REST Routes Admin page
 */

/**
 *
 * @param array $form
 * @param array $form_state
 */
function dls_rest_credentials_configuration_form($form, &$form_state) {
  $restCredentials = RestCredentials::get();
  //inform user if no routes are found
  if(count($restCredentials->groups) == 0) {
    $form['No items'] = array(
      '#type' => 'markup',
      '#markup' => 'It doesn\'t look like any Credentials have been defined yet',
      '#prefix' => '<p>',
      '#suffix' => '</p>',
    );
  }
  else {
    //display a collapsable fieldset for each group of credentials
    foreach($restCredentials->groups as $group => $credentials) {
      //add fieldset
      $group = replace_space($group);
      $form[$group] = array(
        '#type' => 'fieldset',
        '#title' => t($group),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form[$group][$group . 'username'] = array(
        '#type' => 'textfield',
        '#title' => 'User Name',
        '#default_value' => isset($credentials['username']) ? $credentials['username'] : '',
      );
      $form[$group][$group . 'password'] = array(
        '#type' => 'password',
        '#title' => 'Password',
        '#default_value' => isset($credentials['password']) ? $credentials['password'] : '',
      );
    }
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  return $form;
}

function dls_rest_credentials_configuration_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $restCredentials = RestCredentials::get();
  $groups = $restCredentials->groups;
  foreach($groups as $group => $credentials) {
    $groupName = replace_space($group);
    $username = $values[$groupName . 'username'];
    $password = $values[$groupName . 'password'];
    $restCredentials->setCredentials($group, $username, $password);
  }
  $restCredentials->save();
}

function replace_space($text) {
  return str_replace(' ', '%20', $text);
}