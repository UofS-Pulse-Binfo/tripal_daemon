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

  $form['notifications'] = array(
    '#type' => 'fieldset',
    '#title' => 'Notifications',
  );

  $form['notifications']['notify'] = array(
    '#title' => 'Notify Admin by Email if not running.',
    '#type' => 'checkbox',
    '#description' => 'The email of the admin user (uid=1) will be contacted whenever drupal cron detects the Tripal Daemon is not running.',
    '#default_value' => variable_get('tripald_daemon_notify', TRUE),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save Settings',
  );

  return $form;
}

/**
 * Settings Form: Validate
 */
function tripal_daemon_admin_settings_form_validate($form, &$form_state) { }

/**
 * Settings Form: Submit
 */
function tripal_daemon_admin_settings_form_submit($form, &$form_state) {

  // Save Notification Settings.
  variable_set('tripald_daemon_notify', $form_state['values']['notify']);

}
