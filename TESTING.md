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
   - Launches gnome settings
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
     - [ ] Superkey action can be changed
     - [ ] Hot corner for workspaces works
     - [ ] Workspaces and Applications can be toggled on an off
     - [ ] Date & Time position can be move Center, Left, Right
     - [ ] Windows Controls Minimize and Maximize can be toggled on and off
     
### GNOME Shell Extensions

#### Dock
- [ ] Settings > Desktop > Dock (toggle the settings)
     - [ ] Enable Dock
     - [ ] Extend dock to the edges of the screen 
     - [ ] Show Launcher in Dock
     - [ ] Show Workspaces in Dock
     - [ ] Show Application in Dock
     - [ ] Dock visibility can be changed
       - [ ] Dock shows and hides when set to Always Hide
       - [ ] Dock hides when a window is maximized when set to Intelligently Hide
     - [ ] Dock size can be changed
     - [ ] Dock position can be changed
     - [ ] Dock and Icon Alignment on the Screen can be changed
     
#### Workspaces
- [ ] Settings > Desktop > Workspaces
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
  
##### With tiling and show active hint enabled open any two windows.
- With windows next to each other.
  - [ ] Three finger swipe left and right swaps focus between the windows
- With windows on top of each other.
  - [ ] Three finger swipe up and down swaps focus between the windows
  
#### Desktop Icons NG (DING)
##### Test on an empty workspace right click and select Desktop Icons Settings
- [ ] Show the personal folder in the desktop
- [ ] Show the trash icon in the desktop
- [ ] Show external driver in the desktop
- [ ] Change size of the icons in the desktop

#### Install and open any of the following
##### Mattermost, Slack, Psensor, Steam
##### With any or all of the apps running open Extensions and toggle Ubuntu AppIndicators
- [ ] Toggling on and off hides and shows AppIndicators in the Top Bar

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

### Testing for pop-shell
After running all tests run through the pop-shell testing checklist
 - [ ] All pop-shell testing passed [pop-shell testing](https://github.com/pop-os/shell/blob/master_jammy/TESTING.md)
