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

  $admin_user = user_load(1);
  $form['notifications']['email'] = array(
    '#type' => 'textfield',
    '#title' => 'Email',
    '#description' => 'The email address the notification will be sent to',
    '#disabled' => TRUE,
    '#value' => $admin_user->mail,
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

  // Actually handle turning off/on the email.
  // Currently the drush daemon has no way to configure this option :-(
  // However, the daemon saves the timestamp for when to next check if the daemon is
  // dead in a Drupal Variable. Thus we can highjack that variable to tell Drush Daemon
  // to never check the daemon by setting this variable to FALSE.
  if ($form_state['values']['notify'] == FALSE) {
    variable_set('drushd_next_notification_tripal_daemon', FALSE);
    drupal_set_message('Notifications for Tripal Daemon are turned off. This means that if the daemon dies unexpectedly you will not be notified via email.', 'warning');
  }
  // Ensure the daemon notification is turned on.
  // Turn the daemon notification back on by setting the next time to check the daemon
  // to the current time.
  else {
    variable_set('drushd_next_notification_tripal_daemon', time());
    drupal_set_message('Notifications for Tripal Daemon are turned on.');

  }

}
