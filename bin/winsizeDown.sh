#!/bin/bash
# resize down 20 
wid=$(xdotool getactivewindow)
x=$(xwininfo -id $wid | grep Width | awk '{print $2}')
y=$(xwininfo -id $wid | grep Height | awk '{print $2}')
Y=$(($y - 40))
xdotool windowsize $wid $x $Y
