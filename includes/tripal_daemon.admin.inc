<?php
/**
 * @file
 * Administration of the Tripal Drush Daemon.
 */

/**
 * Settings Form.
 */
function tripal_daemon_admin_settings_form($form, $form_state) {

  $form['msg'] = array(
    '#type' => 'item',
    '#markup' => 'The following form allows you to provide settings for the 
      Tripal Drush Daemon. Keep in mind, some of these settings may be overriden
      when the daemon is run on the command-line.',
  );

  return $form;
}
