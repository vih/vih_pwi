<?php

/**
 * @file
 *   drush integration for views_infinite_scroll.
 */
 
define('PWI_DOWNLOAD_URI', 'http://pwi.googlecode.com/files/jquery.pwi-1.5.0.zip'); 

/**
 * Implements hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and
 * description.
 *
 * Notice how this structure closely resembles how
 * you define menu hooks.
 *
 * @See drush_parse_command() for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function vih_pwi_drush_command() {
  $items = array();

  $items['dl-pwi'] = array(
    'callback' => 'vih_pwi_drush_pwi_download',
    'description' => dt('Downloads the required PWI library.'),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function vih_pwi_drush_help($section) {
  switch ($section) {
    case 'drush:dl-pwi':
      return dt("Downloads the required PWI library.");
  }
}

/**
 * Example drush command callback.
 *
 * This is where the action takes place.
 *
 * In this function, all of Drupals API is (usually) available, including
 * any functions you have added in your own modules/themes.
 *
 * To print something to the terminal window, use drush_print().
 *
 */

/**
 * Command to download TCPDF.
 */
function vih_pwi_drush_pwi_download() {
  if (!drush_shell_exec('type unzip')) {
    return drush_set_error(dt('Missing dependency: unzip. Install it before using this command.'));
  }

  $args = func_get_args();
  if (!empty($args[0])) {
    $path = $args[0];
  }
  else {
    $path = 'sites/all/libraries';
  }

  // Create the path if it does not exist.
  if (!is_dir($path)) {
    drush_op('mkdir', $path);
    drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
  }

  // Set the directory to the download location.
  $olddir = getcwd();
  chdir($path);

  $filename = basename(PWI_DOWNLOAD_URI);
  $dirname = 'jquery.pwi';

  // Remove any existing directory
  if (is_dir($dirname)) {
    drush_log(dt('An existing PWI library was overwritten at @path', array('@path' => $path)), 'notice');
  }
  // Remove any existing zip archive
  if (is_file($filename)) {
    drush_op('unlink', $filename);
  }

  // Download the zip archive
  if (!drush_shell_exec('wget ' . PWI_DOWNLOAD_URI)) {
    drush_shell_exec('curl -O ' . PWI_DOWNLOAD_URI);
  }

  if (is_file($filename)) {
    // Decompress the zip archive
    drush_shell_exec('unzip -qq -o ' . $filename);
    // Remove the zip archive
    drush_op('unlink', $filename);
  }

  // Set working directory back to the previous working directory.
  chdir($olddir);
  if (is_dir($path . '/' . $dirname)) {
    drush_log(dt('PWI has been downloaded to @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to download PWI to @path', array('@path' => $path)), 'error');
  }
}
