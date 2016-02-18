sh ~/.screenlayout/3screens.sh &
udiskie &
mouseserver &
xbindkeys &
xrdb -load ~/.Xresources &
mpd &
xsetroot -cursor_name left_ptr &
wallpaper &
#feh --bg-center ~/Pictures/Wallpaper/blackandblue.png --bg-scale ~/Pictures/Wallpaper/citylights.jpg --bg-scale ~/Pictures/Wallpaper/Day/waterfall.jpg &
redshift -l 39.517549:-119.858093 &
compton --config ~/.config/compton.conf -b &
#songupdate.sh &
#bsmpd.new.sh &
eval $(/usr/bin/gnome-keyring-daemon --start --components=pkcs11,secrets,ssh) &
export SSH_AUTH_SOC &


#exec dwm

sxhkd &
[ -e "$BSPWM_FIFO" ] && rm "$BSPWM_FIFO"
mkfifo "$BSPWM_FIFO"
exec bspwm -s "$BSPWM_FIFO"

#2bwm 
#exec i3 --force-xinerama
#exec xmonad

