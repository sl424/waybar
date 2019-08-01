# waybar-modules
A repository of programs I use for custom waybar modules. 

![My Waybar](mywaybar.jpg)

## battery (C)
A battery module that displays the battery percentage and current power draw in watts. Dynamically selects an appropriate battery icon based on battery percentage. Displays an additional charging icon when charging. Does not display current power draw in watts when charging.

The program will also return the current state of the battery (charging/discharging), in lowercase. This allows changing the theme based on battery states in your waybar.css.

Here's an example module in my Waybar config:

```
  "custom/battery": {
    "interval": 8,
    "tooltip": false,
    "format": "{}",
    "return-type": "json",
    "exec": "$HOME/path/to/battery/binary"
  },
```

Here's some example Waybar css for this battery module:

```
#custom-battery {
    padding: 0 5px;
    margin: 0 4px;
    background-color: transparent;
    border-bottom: 2px solid #bff874;
    color: #ffffff;
}

#custom-battery.charging {
  border-bottom: 2px solid #00ff96;
}
```

## vpn_detect (sh)
This script takes the name of a VPN interface, like "mullvad-us3", and returns json data containing information on the state of the VPN connection. 

Here's an example module in my Waybar config:

```
"custom/vpn": {
  "interval": 5,
  "tooltip": false,
  "format": "{}",
  "return-type": "json",
  "exec": "bash /path/to/vpn_detect your-vpn-name"
},
```
