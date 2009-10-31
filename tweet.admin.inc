<?php
// $Id$

/**
 * @file
 *   Builds links to post pages to twitter.
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
  $form['tweet_new_window'] = array(
    '#type' => 'radios',
    '#title' => t('Open Twitter'),
    '#default_value' => variable_get('tweet_new_window', 'target'),
    '#options' => array(0 => t('In same window'), 'target' => t('In new window with target="_blank" (not XHTML 1.0 Strict compliant)'), 'js' => t('In new window with JavaScript')),
  );
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
  $options = array();
  $vocabularies = taxonomy_get_vocabularies();
  foreach ($vocabularies as $key => $vocabulary) {
    $options[$key] = check_plain($vocabulary->name);
  }
  $form['tweet_node_vocabs'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#title' => t('Include taxonomy terms from these vocabularies as #hashtags in tweets when used in the current node'),
    '#default_value' => variable_get('tweet_node_vocabs', array()),
    '#options' => $options,
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
  $form['tweet_format'] = array(
    '#type' => 'textfield',
    '#title' => t('Format'),
    '#description' => t('Manipulate the elements of the tweet by changing their order, removing them, or adding them (like hashtags).  You can use the case-insensitive tokens [url], [title], and [node-tags].'),
    '#maxlength' => 140,
    '#default_value' => variable_get('tweet_format', '[url] [title][node-tags]'),
  );
  $form['tweet_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Text of link'),
    '#description' => t('This is only relevant if you picked a display format that uses text.'),
    '#default_value' => variable_get('tweet_text', t('Post to Twitter')),
  );
  return system_settings_form($form);
}

/**
 * Submit handler for tweet_admin().
 */
function tweet_admin_submit($form, &$form_state) {
  //If no types are selected, assign all types.
  if ($form_state['values']['tweet_types'] == array()) {
    $form_state['values']['tweet_types'] = _tweet_node_types();
  }
  variable_set('tweet_types', $form_state['values']['tweet_types']);
  //Clear the general cache because changed settings may mean that different URLs should be used.
  cache_clear_all('*', 'cache', TRUE);
  drupal_set_message(t('The configuration options have been saved.'));
}