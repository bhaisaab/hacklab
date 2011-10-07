import os
import sys

sys.path.append(os.path.abspath('.'))
sys.path.append(os.path.abspath('..'))

os.environ['PYTHON_EGG_CACHE'] = os.path.abspath('.') + '/.python-egg'
os.environ['DJANGO_SETTINGS_MODULE'] = 'djangoblog.settings'

import django.core.handlers.wsgi
application = django.core.handlers.wsgi.WSGIHandler()
