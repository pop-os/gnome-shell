from apport.hookutils import *

def add_info(report):
	attach_gsettings_package(report, 'gnome-shell-common')
	attach_gsettings_schema(report, 'org.gnome.desktop.interface')
