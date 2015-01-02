//= require jquery_ujs

$(document).ready(function() {
  $('a[data-method="delete"]').live('ajax:success', function(){});
  $('.nav-tabs').button();
});
