<?php

/**
 * Registration iframe form.
 */
function mailjet_register_iframe() {
    global $base_url;
    $default_url = IFRAME_URL."reseller/signup?r=commerceguys&p=drupal-3.0&cb=";
    $callbackurl = urlencode($base_url . '?q=/admin/config/system/mailjet/api/register/alter_callback');
    return '<iframe src="' . $default_url . $callbackurl . '" width="100%" height="1080px" frameborder="0"></iframe>';
}

/**
 * Check for user api.
 */
function mailjet_plans_iframe() {
  if (!variable_get('mailjet_username') && !variable_get('mailjet_password')) {
    drupal_set_message(t('You need to add your Mailjet API details before you can continue'), 'warning');
    drupal_goto('admin/config/system/mailjet/api');
  }

  $token = variable_get("APItoken");
  if (!empty($token)) {
    $callbackurl = 'r=commerceguys&t='.$token.'&show_menu=none';

    $default_url = IFRAME_URL."reseller/pricing/?";

    return '<iframe src="' . $default_url . $callbackurl . '" width="100%" height="1080px" frameborder="0"></iframe>';
  }
  return t('Unable to generate upgrade form.');
}
