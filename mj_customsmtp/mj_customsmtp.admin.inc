<?php
/**
 * Mailjet
 */

function mj_customsmtp_admin_settings() {

  if (module_exists('mimemail') &&
      strpos(variable_get('mj_customsmtp_library', ''), 'mimemail')) {
  }
  else {
    if (variable_get('mj_customsmtp_on', 0)) {
      $smtp_path = drupal_get_filename('module', 'mj_customsmtp');
      if ($smtp_path) {
        variable_set('mj_customsmtp_library', $smtp_path);
      }
      else {
        drupal_set_message(t("mj_customsmtp.module error: Can't find file."), 'error');
      }
    }
    else {
      variable_del('mj_customsmtp_library');
    }
  }

  $form['onoff'] = array(
    '#type'  => 'fieldset',
    '#title' => t('General settings'),
  );
  $form['onoff']['mj_customsmtp_on'] = array(
    '#type'          => 'radios',
    '#title'         => t('Enabled'),
    '#default_value' => variable_get('mj_customsmtp_on', 0),
    '#options'       => array(1 => t('Yes'), 0 => t('No')),
    '#description'   => t('To uninstall this module you must disable here first.'),
  );

  $form['onoff']['mj_customsmtp_from'] = array(
    '#type'          => 'textfield',
    '#title'         => t('E-mail from address'),
    '#default_value' => variable_get('mj_customsmtp_from', ''),
    '#description'   => t('The e-mail address that all e-mails will be from.'),
  );

  $form['onoff']['mj_customsmtp_test'] = array(
    '#type'          => 'radios',
    '#title'         => t('Send test mail now'),
    '#default_value' => variable_get('mj_customsmtp_test', 0),
    '#options'       => array(1 => t('Yes'), 0 => t('No')),
  );

  $form['onoff']['mj_customsmtp_test_address'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Recipient of test mail'),
    '#default_value' => variable_get('mj_customsmtp_test_address', ''),
  );

  $form['auth'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Mailjet settings'),
  );
  $form['auth']['mj_customsmtp_username'] = array(
    '#type'          => 'textfield',
    '#title'         => t('API Key'),
    '#default_value' => variable_get('mj_customsmtp_username', ''),
  );
  $form['auth']['mj_customsmtp_password'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Secret Key'),
    '#default_value' => variable_get('mj_customsmtp_password', ''),
  );

  $test_address = variable_get('mj_customsmtp_test_address', '');

  if (variable_get('mj_customsmtp_test', 0) && valid_email_address ($test_address)) {

    variable_set('mj_customsmtp_test', 0);
    global $language;
    $params['subject'] = t('Your test mail from Mailjet');
    $params['body']    = array(t('Your Mailjet configuration is ok!'));
    drupal_mail('mj_customsmtp', 'mj_customsmtp-test', $test_address, $language, $params);
    drupal_set_message(t('A test e-mail has been sent to @email. You may want to !check for any error messages.', array('@email' => $test_address, '!check' => l(t('check the logs'), 'admin/reports/dblog'))));
  }

  return system_settings_form($form);
}

function mj_customsmtp_admin_settings_validate($form, &$form_state) {

    if (empty ($form_state['values']['mj_customsmtp_from']) || !valid_email_address($form_state['values']['mj_customsmtp_from'])) {
      form_set_error('mj_customsmtp_from', t('The provided from e-mail address is not valid.'));
    }

    if (empty ($form_state['values']['mj_customsmtp_username'])) {
        form_set_error('mj_customsmtp_username', t('The API Key is mandatory.'));
    }

    if (empty ($form_state['values']['mj_customsmtp_password'])) {
        form_set_error('mj_customsmtp_password', t('The Secret Key is mandatory.'));
    }

    if ($form_state['values']['mj_customsmtp_test'] && !valid_email_address($form_state['values']['mj_customsmtp_test_address'])) {
        form_set_error('mj_customsmtp_test_address', t('The provided test e-mail address is not valid.'));
    }

    $configs = array (array ('ssl://', 465),
                      array ('tls://', 587),
                      array ('', 587),
                      array ('', 588),
                      array ('tls://', 25),
                      array ('', 25));

    $host = variable_get ('mj_customsmtp_host', '');
    $connected = FALSE;

    for ($i = 0; $i < count ($configs); ++$i)
    {
        $soc = @ fSockOpen ($configs [$i] [0].$host, $configs [$i] [1], $errno, $errstr, 5);

        if ($soc)
        {
            fClose ($soc);

            $connected = TRUE;

            break;
        }
    }

    if ($connected)
    {
        if ('ssl://' == $configs [$i] [0])
        {
            variable_set ('mj_customsmtp_protocol', 'ssl');
        }
        elseif ('tls://' == $configs [$i] [0])
        {
            variable_set ('mj_customsmtp_protocol', 'tls');
        }
        else
        {
            variable_set ('mj_customsmtp_protocol', 'standard');
        }

        variable_set ('mj_customsmtp_port', $configs [$i] [1]);
    }
    else
    {
        form_set_error ('mj_customsmtp_on', sPrintF (t('Please contact Mailjet support to sort this out.<br /><br />Error %d - %s'), $errno, $errstr));
    }
}
