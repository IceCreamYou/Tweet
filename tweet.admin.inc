<?php

/**
 * @file
 *   Allows adding images ("decos") that can be "bought" with Userpoints.
 */

/**
 * Settings page.
 */
function tweet_admin() {
  $form['tweet_node'] = array(
    '#type' => 'select',
    '#title' => t('Type of link to show on nodes'),
    '#default_value' => variable_get('tweet_node', 'icon'),
    '#options' => array('icon' => 'icon', 'icon_text' => 'icon_text', 'text' => 'text', 'none' => 'none'),
  );
  $form['tweet_teaser'] = array(
    '#type' => 'select',
    '#title' => t('Type of link to show on teasers'),
    '#default_value' => variable_get('tweet_teaser', 'none'),
    '#options' => array('icon' => 'icon', 'icon_text' => 'icon_text', 'text' => 'text', 'none' => 'none'),
  );
  $form['tweet_title'] = array(
    '#type' => 'select',
    '#title' => t('Include page title in tweet'),
    '#default_value' => variable_get('tweet_title', 1),
    '#options' => array(1 => 'Yes', 0 => 'No'),
  );
  $form['tweet_new_window'] = array(
    '#type' => 'radios',
    '#title' => t('Open Twitter'),
    '#default_value' => variable_get('tweet_new_window', 'target'),
    '#options' => array(0 => t('In same window'), 'target' => t('In new window with target="_blank" (not XHTML 1.0 Strict compliant)'), 'js' => t('In new window with JavaScript')),
  );
  $methods = array();
  if (function_exists('file_get_contents')) {
    $methods['php'] = t('PHP');
  }
  if (function_exists('curl_exec')) {
    $methods['curl'] = t('cURL');
  }
  if (empty($methods)) {
    if (variable_get('tweet_method', 'curl') != 'none') {
      variable_set('tweet_method', 'none');
    }
    $form['tweet_method'] = array(
      '#type' => 'radios',
      '#title' => t('Method'),
      '#description' => '<p>'. t('The method to use to retrieve the abbreviated URL.') .'</p>'.
        '<p><strong>'. t('Your PHP installation does not support the URL abbreviation feature of the Tweet module.') .'</strong> '.
        t('You must compile PHP with either the cURL library or the file_get_contents() function to use this option.') .'</p>',
      '#default_value' => 'none',
      '#options' => array('none' => t('None')),
      '#disabled' => TRUE,
    );
    $form['tweet_service'] = array(
      '#type' => 'radios',
      '#title' => t('Service'),
      '#description' => t('The service to use to create the abbreviated URL.'),
      '#default_value' => 'none',
      '#options' => array('none' => t('None')),
    );
    $form['tweet_service_backup'] = array(
      '#type' => 'radios',
      '#title' => t('Backup Service'),
      '#description' => t('The service to use to create the abbreviated URL if the primary service is down.'),
      '#default_value' => 'none',
      '#options' => array('none' => t('None')),
    );
  }
  else {
    $form['tweet_method'] = array(
      '#type' => 'radios',
      '#title' => t('Method'),
      '#description' => t('The method to use to retrieve the abbreviated URL.'),
      '#default_value' => variable_get('tweet_method', 'curl'),
      '#options' => $methods,
    );
    $services = drupal_map_assoc(array('hex.io', 'idek.net', 'is.gd', 'lin.cr', 'ri.ms', 'th8.us', 'TinyURL'));
    $services['none'] = t('None');
    $form['tweet_service'] = array(
      '#type' => 'select',
      '#title' => t('Service'),
      '#description' => t('The service to use to create the abbreviated URL.'),
      '#default_value' => variable_get('tweet_service', 'is.gd'),
      '#options' => $services,
    );
    $form['tweet_service_backup'] = array(
      '#type' => 'select',
      '#title' => t('Backup Service'),
      '#description' => t('The service to use to create the abbreviated URL if the primary service is down.'),
      '#default_value' => variable_get('tweet_service_backup', 'TinyURL'),
      '#options' => $services,
    );
  }
  $node_types = variable_get('tweet_types', array());
  //If all types are selected, un-select them, because the system will still save the result as all selected and it looks better.
  if ($node_types == _tweet_node_types()) {
    $node_types = array();
  }
  $form['tweet_types'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#title' => t('Node types on which to display link'),
    '#description' => t('If no types are selected, the link will appear on all types.  To stop links from appearing on all nodes, choose "none" in the teaser and node display options above.'),
    '#default_value' => $node_types,
    '#options' => _tweet_node_types(),
  );
  $image_location = drupal_get_path('module', 'tweet') .'/icon.png';
  $form['tweet_image'] = array(
    '#type' => 'textfield',
    '#title' => t('Image'),
    '#description' => t('Enter the URL for the image you want to show up if you allow images to appear in your links, relative to your Drupal installation.  Ex.: sites/all/modules/tweet/icon.png'),
    '#default_value' => variable_get('tweet_image', $image_location),
  );
  $form['tweet_exclude'] = array(
    '#type' => 'textfield', 
    '#title' => t('Exclude nodes'),
    '#description' => t('Enter the NIDs of nodes which should not have Tweet links, separated by commas.'),
    '#default_value' => variable_get('tweet_exclude', ''),
  );
  $form['tweet_hashtag'] = array(
    '#type' => 'textfield',
    '#title' => t('Suffix'),
    '#description' => t('If you include the title in your tweets, this text will be automatically appended to the end of the tweet.  This allows you to add hashtags if you wish.'),
    '#maxlength' => 123,
    '#default_value' => variable_get('tweet_hashtag', ''),
  );
  return system_settings_form($form);
}

/**
 * Validation handler for tweet_admin().
 * @see tweet_admin()
 * @see tweet_admin_validate()
 */
function tweet_admin_validate($form, &$form_state) {
  if ($form_state['values']['tweet_service'] == $form_state['values']['tweet_service_backup'] && $form_state['values']['tweet_service_backup'] != 'none') {
    form_set_error('tweet_service_backup', t('You must select a backup abbreviation service that is different than your primary service.'));
  }
  if ($form_state['values']['tweet_service'] == 'none' && $form_state['values']['tweet_service_backup'] != 'none') {
    drupal_set_message(t('You have selected a backup URL abbreviation service, but no primary service.  Your URLs will not be abbreviated with these settings.'));
  }
}

/**
 * Submit handler for tweet_admin().
 * @see tweet_admin()
 * @see tweet_admin_validate()
 */
function tweet_admin_submit($form, &$form_state) {
  variable_set('tweet_node', $form_state['values']['tweet_node']);
  variable_set('tweet_teaser', $form_state['values']['tweet_teaser']);
  variable_set('tweet_title', $form_state['values']['tweet_title']);
  variable_set('tweet_new_window', $form_state['values']['tweet_new_window']);
  variable_set('tweet_method', $form_state['values']['tweet_method']);
  variable_set('tweet_service', $form_state['values']['tweet_service']);
  variable_set('tweet_service_backup', $form_state['values']['tweet_service_backup']);
  variable_set('tweet_image', $form_state['values']['tweet_image']);
  variable_set('tweet_exclude', $form_state['values']['tweet_exclude']);
  variable_set('tweet_hashtag', $form_state['values']['tweet_hashtag']);
  //If no types are selected, assign all types.
  if ($form_state['values']['tweet_types'] == array()) {
    $form_state['values']['tweet_types'] = _tweet_node_types();
  }
  variable_set('tweet_types', $form_state['values']['tweet_types']);
  //Clear the general cache because changed settings may mean that different URLs should be used.
  cache_clear_all('*', 'cache', TRUE);
  drupal_set_message(t('The configuration options have been saved.'));
}