from apport.hookutils import *
import os

def is_process_running(proc):
    '''
    Determine if process has a registered process id
    '''
    log = command_output(['pidof', proc])
    if not log or log[:5] == "Error" or len(log)<1:
        return False
    return True

def add_info(report):
    attach_related_packages(report, ['mutter-common'])

    attach_gsettings_package(report, 'gnome-shell-common')
    attach_gsettings_package(report, 'gsettings-desktop-schemas')
    attach_gsettings_package(report, 'mutter-common')
    attach_gsettings_schema(report, 'org.gnome.settings-daemon.plugins.color')
    attach_gsettings_schema(report, 'org.gnome.settings-daemon.peripherals.touchscreen')

    try:
        monitors = os.path.join(os.environ['XDG_CONFIG_HOME'], 'monitors.xml')
    except KeyError:
        monitors = os.path.expanduser('~/.config/monitors.xml')

    attach_file_if_exists(report, monitors, 'monitors.xml')

    result = ''

    dm_list = apport.hookutils.command_output(['sh', '-c', 
	'apt-cache search \"display manager\" | cut -d \' \' -f1 | grep -E \"dm$|^gdm3?\\b\"'])

    for line in dm_list.split('\n'):
        if (is_process_running(line)):
            result = line
            break

    report['DisplayManager'] = result

    if command_available('journalctl') and os.path.exists('/run/systemd/system'):
        report['ShellJournal'] = command_output(['journalctl',
                                                 '/usr/bin/gnome-shell',
                                                 '-b', '-o', 'short-monotonic',
                                                 '--lines', '3000'])
