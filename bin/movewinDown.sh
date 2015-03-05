#!/bin/bash
# move Down +10

wid=$(xdotool getactivewindow)
x=$(xwininfo -id $wid | awk '/Abs.+X/ { sub(/^.+\s/,""); print }')
y=$(xwininfo -id $wid | awk '/Abs.+Y/ { sub(/^.+\s/,""); print }')
Y=$(($y + 40))
xdotool windowmove $wid $x $Y
