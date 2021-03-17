# My dwm config

**This is a modification of [DistroTube's dwm config](https://gitlab.com/dwt1/dwm-distrotube).**

Since DistroTube introduced me to dwm through his gitlab and his videos, I thought using his config would be a good starting point for learning and using dwm. A lot of the info on this README is just copied from his README because I didn't change a whole lot.

## Patches

- alpha (for transparency)
- attachaside (new clients appear in the stack rather than as the master)
- cyclelayouts (cycles through the available layouts)
- gridmode (adding a grid layout)
- restartsig (allows dwm to be restarted with a keybinding)
- rotatestack (moves a window through the stack, in either direction)
- statuspadding (horizontal and vertical padding in the status bar are now configurable options)
- uselessgap (adding gaps when more than one window)

## Dependencies

- libxft
- ttf-hack
- ttf-joypixels
- st
- dmenu
- tabbed

Also, you will need to add the following from the AUR:

- nerd-fonts-complete (optional)
- https://aur.archlinux.org/packages/libxft-bgra/ (needed for colored fonts and emojis)

Also, if you are building this on an Ubuntu-based system, you need to install libx11-dev and xorg-dev.

## Installing

```
git clone https://github.com/Zaedus/dwm.git
cd dwm
sudo make clean install
```

# Using

## Scripts

My dwm config relies on a few scripts. All of these scripts should be places in `~/.dwm/`

### `autostart.sh`

This is what is run when dwm starts. I run dwmblocks, a compositer (picom), and set my background (nitrogen).

```
dwmblocks &
picom &
nitrogen --restore &
```

### dmenu scripts

These scripts were from [DistroTube's Repo](https://gitlab.com/dwt1/dmscripts). I put them in the `~/.dmscripts/` directory.

## Keybindings

The MODKEY is set to the Super/Windows key. Anything in parentheses is the default I've set it to, but it is always changeable.

| Keybinding              | Action |
| :-------------------    | :----- |
| `MODKEY + RETURN`       | opens selected terminal (`st`) |
| `MODKEY + SPACE`        | opens selected run launcher (`dmenu`) |
| `MODKEY + q`            | closes window with focus |
| `MODKEY + SHIFT + r`    | restarts dwm |
| `MODKEY + SHIFT + q`    | quits dwm |
| `MODKEY + 1-9`          | switch focus to workspaces 1-9 |
| `MODKEY + SHIFT + 1-9`  | send focused window to workspaces 1-9 |
| `MODKEY + Left`         | select the next window in the stack |
| `MODKEY + Right`        | select the previous window in the stack |
| `MODKEY + SHIFT + Left` | rotate the windows forward in the stack |
| `MODKEY + SHIFT + Right`| rotate the windows backward in the stack |
| `MODKEY + UP`           | expand the size of the secondary windows |
| `MODKEY + DOWN`         | shrinks the size of the secondary windows |
| `MODKEY + .`            | switches focus next monitors |
| `MODKEY + ,`            | switches focus to prev monitors |
