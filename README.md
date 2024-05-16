# Logitech G600 Mapping on Linux with Wayland and X11
Utility program for binding actions to keys on the Logitech G600 gaming mouse. Uses `ydotool` to support key combinations on x11 and Wayland. Supports 16 keys and the G-shift button for a total of 32 fast shortcuts.

Before running this program open the Logitech Gaming Software on a Windows or Mac OS machine. Assign the three basic mouse buttons to their standard functions. The G-shift button should be assigned to the G-shift function. All the remaining buttons (scroll left, scroll right, G7, ... G20) should be set to emulate (unique) keyboard keys (but not modifier keys).

## Usage

### Download ydotool
It is the newer xdotool. Link to installation is [here](https://gabrielstaples.com/ydotool-tutorial/#gsc.tab=0).
Add the ydotool daemon path to your bashrc for QOL, and to make this script work.

`export YDOTOOL_SOCKET="$HOME/.ydotool_socket"`

### Setup Mapping Script
1. Clone this repository.
2. Open `g600.c` and fill in the commands for the keys.
3. Compile with `gcc g600.c -o g600`.
4. Run with `sudo ./g600`.

For command ideas you can look at programs like `ydotool`, `xdo`, `pulseaudio-ctl`, `xclip`, `i3-msg`. You can also run your own scripts.

The program needs privileges to communicate with G600 so typically it'll be started with `sudo`. Alternatively (works on Ubuntu 18.04) you can force the program to run as the `input` group with:

```bash
sudo chown .input g600
sudo chmod g+s g600
```

### Setup Compiled Executable to run on startup
