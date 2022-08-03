# GNOME Shell Testing

## Logs

To begin watching logs, open a terminal with the following command:

```
journalctl -o cat -n 0 -f "$(which gnome-shell)" | grep -v warning
```

## Checklists

### Top Bar
 - [ ] Pop Shell extension icon is showing
 - [ ] Clicking on the clock shows the calendar
 - [ ] Notifications display under the clock
 - [ ] Notifications show in the notifications list
 - [ ] Notifications can be cleared
 - [ ] Do Not Disturb silences notifications 
 - [ ] `Super` + `V` shows notifications list
 - [ ] Open Weather app weather should now display under the calendar

### Global/Main Menu (all the following should be showing)
 - [ ] Sound can be adjusted
 - [ ] Display Brightness can be adjusted
 - [ ] Wi-Fi the following are working
   - Select Network
   - Turn On/Off (icon changes with state)
   - Wi-Fi Settings
 - [ ] Connect to a wired connection
   - Wired Connected/Off is showing
   - Turn On/Off (icon changes with state)
 - [ ] Bluetooth
   - Turning off bluetooth removes it from the menu
 - [ ] Power Menu
  - Machines with switchable graphics
     - Integrated Graphics
     - NVIDIA Graphics
     - Hybrid Graphics
     - Compute Graphics
  - All machines
     - Battery Life
     - Balanced
     - High Performance
 - [ ] Switchable graphics modes can be changed from the menu
 - [ ] Power modes can be changed from the menu
 - [ ] Settings
   - Launches gnome settings
 - [ ] Lock
   - Locks the desktop
 - [ ] Power Off / Log Out
  - [ ] All the following are working
     - Suspend
     - Restart
     - Power Off
     - Log Out

### GNOME Shell Settings (this could use more specific tests)
 - [ ] Settings can be launched and settings can be changed
 - [ ] Settings > Desktop > Desktop Options
     - [ ] Superkey action can be changed
     - [ ] Hot corner for workspaces works
     - [ ] Workspaces and Applications can be toggled on an off
     - [ ] Date & Time position can be move Center, Left, Right
     - [ ] Windows Controls Minimize and Maximize can be toggled on and off

### Reset GNOME Shell
- [ ] Gnome Shell restarts with `Alt` + `F2` type `r` and `Enter`

### Change GNOME Shell Setting from the terminal
#### Running the following commands makes changes to gnome-shell
  - [ ] Classic Button Layout
    - `gsettings set org.gnome.desktop.wm.preferences button-layout ':minimize,maximize,close'`
  - [ ] Default Button Layout
    - `gsettings set org.gnome.desktop.wm.preferences button-layout ':appmenu,minimize,close'`
   - [ ] Set time to 24 hour 
     - `gsettings set org.gnome.desktop.interface clock-format 24h`
   - [ ] Set time to default 12 hour
     - `gsettings set org.gnome.desktop.interface clock-format 12h`
  - [ ] Show Battery Percentage 
    - `gsettings set org.gnome.desktop.interface show-battery-percentage true`
  - [ ] Hide Battery Percentage
    - `gsettings set org.gnome.desktop.interface show-battery-percentage true`

### Reset GNOME initial setup
Run `sudo rm .config/gnome-initial-setup-done` then log out and log back in. 
 - [ ] Run through the initial setup
