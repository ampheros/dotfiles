#!/bin/bash

if [ "$1" == "up"  ]; then
	xdotool mousemove_relative -- 0 -30
fi

if [ "$1" == "down"  ]; then
	xdotool mousemove_relative 0 30
fi

if [ "$1" == "right"  ]; then
	xdotool mousemove_relative 30 0
fi

if [ "$1" == "left"  ]; then
	xdotool mousemove_relative -- -30 0
fi
