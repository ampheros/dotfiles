#!/bin/bash

curr=$(mpc current)
echo $(mpc current) | skroll -n 20 -d 0.5 -r > ~/.barscripts/song &
while true; do
sleep .5 
	if [ "$curr" != "$(mpc current)" ]
	then
		echo $(mpc current) | skroll -n 30 -d 0.13 -r > ~/.barscripts/song 
		curr=$(mpc current)
	fi

done
