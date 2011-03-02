from django.conf.urls.defaults import *
from geekout.views import hello, hours_ahead, current_datetime

# Uncomment the next two lines to enable the admin:
# from django.contrib import admin
# admin.autodiscover()

urlpatterns = patterns('',
    # Example:
    # (r'^geekout/', include('geekout.foo.urls')),

    # Uncomment the admin/doc line below to enable admin documentation:
    # (r'^admin/doc/', include('django.contrib.admindocs.urls')),

    # Uncomment the next line to enable the admin:
    # (r'^admin/', include(admin.site.urls)),
    ('^hello/$', hello),
    #(r'^time/plus/\d+/$', hours_ahead),
    (r'^time/plus/(\d{1,2})/$', hours_ahead),
    ('^current_datetime/$', current_datetime),
)
