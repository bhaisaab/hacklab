from django.conf.urls.defaults import *

urlpatterns = patterns('',
    (r'^$', 'webfolio.main.views.main'),
)
