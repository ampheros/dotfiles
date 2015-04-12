#!/bin/bash

function statusbar {

    function desk() {
    DESKTOP=$(xprop -root _NET_CURRENT_DESKTOP | awk '{print $3}')
    case $DESKTOP in
	0)  echo "I"
	    ;;
	1)  echo "II"
	    ;;
	2)  echo "III"
	    ;;
        3)  echo "[Main-x-x-x]"
            ;;
        4)  echo "[x-Web-x-x]"
            ;;
        5)  echo "[x-x-Term-x]"
            ;;
        6)  echo "[x-x-x-Media]"
            ;;
        *)  echo "error"
    esac
    }

    function clock() {
    time=$(date "+%e %b  %l:%M")
    echo $time
    }

    function mem() {
    free=$(free -m | grep Mem  | awk '{print $3}' | awk '/[0-9]/')
    echo $free
    }

    function temp() {
    tem=$(sensors -u -A coretemp-isa-0000 | grep temp1_input |  awk '{print $2}')
    echo $tem
    }

    function sda() {
    dfh=$(dfc | grep "/dev/sda2" | awk '{print $3}')
    echo $dfh
    }

    
    function ncc() {
    mus=$(mpc current)
   echo $mus
  }
    

    echo "^fg(#2F888A)kYo $(desk)^fg(#AAAAAA) ^fg(#287373) ^fg(#914E89) ram $(mem) ^fg(#98CBFE) sda $(sda) ^fg(#AAAAAA)^fg(#2B7694)^fg(#AAAAAA)^fg(#5E468C)^fg(#AAAAAA)^fg(#8A2F58) cpu $(temp) °C ^fg(#AAAAAA) ^fg(#E5B0FF) now playing: $(ncc) ^fg(#395573) ^fg(#AAAAAA) //  ^fg(#FFFFFF) $(clock) ^fg(#AAAAAA)           "
}
 while true 
 do
     echo "$(statusbar)"
     sleep .25 

 done | dzen2 -bg '#262626' -fn 'tamsyn-8-' -h 20 -ta c -p -xs 2 -dock &
