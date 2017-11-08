<div id="branding" class="clearfix">
  <?php print $breadcrumb; ?>
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <h1 class="page-title"><?php print $title; ?></h1>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php print render($primary_local_tasks); ?>
</div>

<div id="page">
  <?php if (!isset($secondary_local_tasks) && !empty($secondary_local_tasks)): ?>
    <div class="tabs-secondary clearfix"><?php print render($secondary_local_tasks); ?></div>
  <?php endif; ?>

  <div id="content" class="clearfix">
    <div class="element-invisible"><a id="main-content"></a></div>
    <?php if ($messages): ?>
      <div id="console" class="clearfix"><?php print $messages; ?></div>
    <?php endif; ?>
    <?php if ($page['help']): ?>
      <div id="help">
        <?php print render($page['help']); ?>
      </div>
    <?php endif; ?>
    <?php
    if (drupal_get_path_alias() == 'admin/config/system/mailjet/mailjet-panel') {
      if ($output_links_mailjet) {
        ?>
        <ul><?php print render($output_links_mailjet); ?></ul>
        <?php
      }
    }
    else {
      if ($action_links) {
        ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
        <?php
      }

      if (drupal_get_path_alias() == 'admin/config/system/mailjet/signup-setttings') {
        print render($signup_forms);
      }
      else {
        print render($page['content']);
      }
    }
    ?>

  </div>

  <div id="footer">
    <?php print $feed_icons; ?>
  </div>

</div>
