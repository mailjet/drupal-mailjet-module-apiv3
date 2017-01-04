---
This module for Drupal 7.x. provides complete control of Email settings with Drupal and Mailjet.
It simply replaces your default SMTP settings in order to make all your emails go through Mailjet: this will improve your deliverability and allow you to optimize your campaigns.

Mailjet helps to send and track emails in real time, while ensuring their deliverability.
You'll take advantage of our reporting tools and get advanced statistics to monitor and optimize your emails.

Prerequisits
------------

The Mailjet plugin relies on the PHPMailer v5.2.8 for sending emails. This script must be uplodaded manually by the user in the Drupal instalation.
1) Create a folder named "phpmailer" inside DRUPAL_ROOT/sites/all/libraries
2) Get the PHPMailer v5.2.8 from Git Hub here: http://github.com/PHPMailer/PHPMailer/archive/v5.2.8.zip
3) Unzip the archive and put all contents inside the DRUPAL_ROOT/sites/all/libraries/phpmailer folder that was created in step 2

Installation
------------

1) Upload all content in your Drupal sites/all/modules/ directory.
2) Log in as administrator in Drupal.
3) Enable the Mailjet settings module on the Administer > Site building > Modules page.
4) Fill in required settings on the Administer > Site configuration > Mailjet settings page

Author
------
Mailjet SAS
plugins@mailjet.com
