<?php
/**
 * This plugin array is more or less self documenting
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Picasa Webalbums'),
  'description' => t('Adds Picasa Webalbum integration through the jQuery PWI-plugin.'),
  'category' => t('Picasa'),
  'edit form' => 'vih_pwi_pane_custom_pane_edit_form(',
  'render callback' => 'vih_pwi_pane_custom_type_render',
  'admin info' => 'vih_pwi_pane_custom_pane_admin_info',
);


/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function vih_pwi_pane_custom_type_render($subtype, $conf, $context = NULL) {
  $block = new stdClass;
  $block->title = t('Picasa Webalbum');
  $block->content = _vih_pwi_vrite_this($conf);
  return $block;
}

/**
 * 'admin info' callback for panel pane.
 */
function vih_pwi_pane_custom_pane_admin_info($subtype, $conf, $context = NULL) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    $block->content = _vih_pwi_vrite_this($conf);
    return $block;
  }
}

/**
 * 'Edit form' callback for the content type.
 */
function vih_pwi_pane_custom_pane_edit_form(&$form, &$form_state) {
  $conf = $form_state['conf'];
  $form['vih_pwi_picasa_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Picasa User'),
    '#required' => TRUE,
    '#default_value' => !empty($conf['vih_pwi_picasa_user']) ? $conf['vih_pwi_picasa_user'] : '',
  ); 
  // @todo create a select box with available sizes
  $form['vih_pwi_thumbsize'] = array(
    '#type' => 'textfield',
    '#title' => t('Thumbnail size'),
    '#required' => TRUE,
    '#default_value' => !empty($conf['vih_pwi_thumbsize']) ? $conf['vih_pwi_thumbsize'] : 160,
  ); 
  $form['vih_pwi_max_results'] = array(
    '#type' => 'textfield',
    '#title' => t('Max results'),
    '#required' => TRUE,
    '#default_value' => !empty($conf['vih_pwi_max_results']) ? $conf['vih_pwi_max_results'] : 12,
  );
  return $form;
}

/**
 * Submit function, note anything in the formstate[conf] automatically gets saved 
 */
function vih_pwi_pane_custom_pane_edit_form_submit(&$form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
     if (isset($form_state['values'][$key])) {
       $form_state['conf'][$key] = $form_state['values'][$key];
     }
   }
}

/**
 * View the PWI.
 */
function _vih_pwi_vrite_this($conf) {
  $output = 'waiting for picasa';
  return $output;
}