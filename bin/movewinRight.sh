#!/bin/bash
# move right +10

wid=$(xdotool getactivewindow)
x=$(xwininfo -id $wid | awk '/Abs.+X/ { sub(/^.+\s/,""); print }')
y=$(xwininfo -id $wid | awk '/Abs.+Y/ { sub(/^.+\s/,""); print }')
X=$(($x + 40))
xdotool windowmove $wid $X $y
