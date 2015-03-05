#!/bin/bash
# decrease width by 20 
wid=$(xdotool getactivewindow)
x=$(xwininfo -id $wid | grep Width | awk '{print $2}')
y=$(xwininfo -id $wid | grep Height | awk '{print $2}')
X=$(($x - 40))
xdotool windowsize $wid $X $y
