<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Picasa Webalbums'),
  'description' => t('Adds Picasa Webalbum integration through the jQuery PWI-plugin.'),
  'category' => t('Social media'),
  'edit form' => 'vih_pwi_vih_pwi_edit_form',
  'render callback' => 'vih_pwi_vih_pwi_render',
  'admin info' => 'vih_pwi_vih_pwi_admin_info',
  'defaults' => array(
    'vih_pwi_picasa_user' => '',
    'vih_pwi_thumbsize' => '160',
    'vih_pwi_max_results' => '12',
  )
);

/**
 * 'admin info' callback for panel pane.
 */
function vih_pwi_vih_pwi_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    $block->content = t('Showing pictures from <em>@@username</em>.', array(
      '@username' => $conf['vih_pwi_picasa_user'],
    ));
    return $block;
  }
}

/**
 * 'Edit form' callback for the content type.
 */
function vih_pwi_vih_pwi_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['vih_pwi_picasa_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Picasa User'),
    '#required' => TRUE,
    '#default_value' => $conf['vih_pwi_picasa_user'],
  ); 
  // @todo create a select box with available sizes
  $form['vih_pwi_thumbsize'] = array(
    '#type' => 'textfield',
    '#title' => t('Thumbnail size'),
    '#required' => TRUE,
    '#default_value' => $conf['vih_pwi_thumbsize'],
  ); 
  $form['vih_pwi_max_results'] = array(
    '#type' => 'textfield',
    '#title' => t('Max results'),
    '#required' => TRUE,
    '#default_value' => $conf['vih_pwi_max_results'],
  );

  return $form;
}

/**
 * The submit form stores the data in $conf.
 */
function vih_pwi_vih_pwi_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function vih_pwi_vih_pwi_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();

  // initial content is blank
  $block->title = '';
  $block->content = '';

  if (!pwi_loaded()) {
    return;
  }
  
  drupal_add_js('
(function ($) {
  $(document).ready(function() {
    $("#picasaweb").pwi({
      username: \''.check_plain($conf['vih_pwi_picasa_user']).'\',
      maxResults: '.check_plain($conf['vih_pwi_max_results']).',
      showAlbumDescription: false,
      showPhotoCaption: false,
      photoCaptionLength: 5,
      thumbSize: '.check_plain($conf['vih_pwi_thumbsize']).',
      thumbCrop: 1,
      showPhotoDate: false,
      showSlideshowLink: true,
      labels: {photo:"'.t('photo').'",	//-- override labels, to translate into your required language
        photos: "'.t('photos').'",
        albums: "'.t('Back to albums').'",
        slideshow: "'.t('Show slideshow').'",
        loading: "'.t('Fetching pictures').'",
        page: "'.t('Page').'",
        prev: "'.t('Previous').'",
        next: "'.t('Next').'",
        devider: "|"
      },
      months: ["'.t('January').'","'.t('February').'","'.t('March').'","'.t('April').'","'.t('May').'","'.t('June').'","'.t('July').'","'.t('August').'","'.t('September').'","'.t('October').'","'.t('November').'","'.t('December').'"]
    });
  });
})(jQuery);', 'inline');

  // Add in the content
  $block->content .= '<div id="picasaweb"></div>';

  return $block;
}
