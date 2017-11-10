<?php

 /**
 * @file
 * Contains Iframe for the stats.
 */

/**
 * Custom code for stats iframe.
  */
  
function mailjet_stats_iframe() {
  if (!variable_get('mailjet_username') && !variable_get('mailjet_password')) {
    drupal_set_message(t('You need to add your Mailjet API details before you can continue'), 'warning');
    drupal_goto('admin/config/system/mailjet');
  }
  $token = variable_get("APItoken");
  if (!empty($token)) {
    global $base_url;
    global $language;

    $lang_codes_map = array(
      'en' => 'en_US',
      'fr' => 'fr_FR',
      'de' => 'de_DE',
      'es' => 'es_ES',
    );
    $default_lang = 'en';
    $locale = isset($lang_codes_map[$language->language]) ? $lang_codes_map[$language->language] : $lang_codes_map[$default_lang];

    $callbackurl = 't=' . $token . '&show_menu=none&sp=display&u=Drupal-3.0&locale=' . $locale;
//    $callbackurl = 'r=commerceguys&t=' . $token . '&show_menu=none&sp=display&u=Drupal-3.0&locale=' . $locale;

    $default_url = IFRAME_URL . "stats?";

    return '<iframe src="' . $default_url . $callbackurl . '" width="100%" height="1080px" frameborder="0"></iframe>';
  }
  return t('Unable to generate registration form.');
}
