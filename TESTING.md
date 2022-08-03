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
 - [ ] Notification pop-ups display under the clock
 - [ ] Notifications show in the notifications list
 - [ ] Notifications can be cleared
 - [ ] Do Not Disturb silences notifications 
 - [ ] `Super` + `V` shows notifications list
 - [ ] Open Weather app; weather should now display under the calendar

### Global/Main Menu (all the following should be showing)
 - [ ] Sound can be adjusted
 - [ ] Display Brightness can be adjusted
 - [ ] Wi-Fi (the following are working):
   - Select Network
   - Turn On/Off (icon changes with state)
   - Wi-Fi Settings
 - [ ] Connect to a wired connection
   - Wired Connected/Off is showing
   - Turn On/Off (icon changes with state)
 - [ ] Bluetooth
   - Turning off Bluetooth removes it from the menu
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
   - Launches GNOME Settings
 - [ ] Lock
   - Locks the desktop
 - [ ] Power Off / Log Out
  - [ ] All the following are working
     - Suspend
     - Restart
     - Power Off
     - Log Out

### GNOME Shell Settings
 - [ ] Settings can be launched and settings can be changed
 - [ ] Settings > Desktop > Desktop Options
     - [ ] Super Key Action can be changed
     - [ ] Hot Corner for Workspaces works
     - [ ] Workspaces and Applications can be toggled on and off
     - [ ] Date & Time position can be moved to Center, Left, and Right
     - [ ] Window Controls - Minimize and Maximize can be toggled on and off
     
### GNOME Shell Extensions

#### Dock settings (Settings > Desktop > Dock)
- [ ] General Options
    - [ ] Enable/Disable Dock
    - [ ] Extend dock to the edges of the screen 
    - [ ] Show Launcher, Workspaces, Applications Icons in Dock
 - [ ] Dock visibility can be changed
    - [ ] Dock shows and hides when set to Always Hide
    - [ ] Dock hides when a window is maximized when set to Intelligently Hide
 - [ ] Dock size can be changed
 - [ ] Dock position can be changed
 - [ ] Dock and Icon Alignment on the Screen can be changed
     
#### Workspaces settings (Settings > Desktop > Workspaces)
- [ ] Switch between Dynamic and Fixed Workspaces
- [ ] Change number of Fixed Workspaces
- [ ] Change Multi-monitor Behavior (requires testing with external display)
- [ ] Change placement of the Workspace Picker
     
#### Gestures
- [ ] Four finger swipe up and down switches between workspaces
- [ ] Four finger swipe left toggles workspace menu
- [ ] Four finger swipe right toggles applications menu
- [ ] Pinch-Zoom works for the following apps
  - Firefox
  - GNOME Terminal
  - GIMP and Glimpse
  - Nautilus
  - Image Viewer
  - Inkscape
- [ ] Three finger swipe in any direction works to switch focus
  
#### Desktop Icons NG (DING)
- [ ] Right-click -> Desktop Icons Settings opens settings
- [ ] Show/hide the personal folder (home folder)
- [ ] Show/hide the trash icon
- [ ] Show/hide external drives
- [ ] Change desktop icon size

#### AppIndicators

- [ ] Launch an app that uses the notification tray (Mattermost, Slack, Psensor, Steam)
- [ ] Open Extensions, toggle Ubuntu AppIndicators off and on (icons hide and show in Top Bar)

### Reset GNOME Shell
- [ ] Gnome Shell restarts with `Alt` + `F2` type `r` and `Enter`

### Change GNOME Shell settings from the terminal
  - [ ] Classic button layout
    - `gsettings set org.gnome.desktop.wm.preferences button-layout ':minimize,maximize,close'`
  - [ ] Default button layout
    - `gsettings set org.gnome.desktop.wm.preferences button-layout ':appmenu,minimize,close'`
  - [ ] Set time to 24-hour
     - `gsettings set org.gnome.desktop.interface clock-format 24h`
  - [ ] Set time to default 12-hour
     - `gsettings set org.gnome.desktop.interface clock-format 12h`
  - [ ] Show battery percentage 
    - `gsettings set org.gnome.desktop.interface show-battery-percentage true`
  - [ ] Hide battery percentage
    - `gsettings set org.gnome.desktop.interface show-battery-percentage true`

### Pop Shell
 - [ ] Complete Pop Shell regression testing checklist: https://github.com/pop-os/shell/blob/master_jammy/TESTING.md
