#!/bin/bash

function statusbar {

    function desk() {
    DESKTOP=$(xprop -root _NET_CURRENT_DESKTOP | awk '{print $3}')
    case $DESKTOP in
    0)  echo "[^fg(#FFFFFF)I^fg(#2F888A)-x-x] [x-x-x-x]"
        ;;
    1)  echo "[x-^fg(#FFFFFF)II^fg(#2F888A)-x] [x-x-x-x]"
        ;;
    2)  echo "[x-x-^fg(#FFFFFF)III^fg(#2F888A)] [x-x-x-x]"
        ;;
        3)  echo "[x-x-x] [^fg(#FFFFFF)iv^fg(#2F888A)-x-x-x]"
            ;;
        4)  echo "[x-x-x] [x-^fg(#FFFFFF)v^fg(#2F888A)-x-x]"
            ;;
        5)  echo "[x-x-x] [x-x-^fg(#FFFFFF)vi^fg(#2F888A)-x]"
            ;;
        6)  echo "[x-x-x] [x-x-x-^fg(#FFFFFF)vii^fg(#2F888A)]"
            ;;
        *)  echo "error"
    esac
    }

     function clock() {
    time=$(date "+%e %b  %l:%M")
    echo $time
    }
    
    function ncc() {
#    mus=$(mpc current)
#    mus=$(ncmpcpp --now-playing)
#   echo $mus
#   echo $mus | skroll -l -n 10 -d 0.25 -r > ~/.barscripts/song	
sed -n ${i}p ~/.barscripts/song
#    echo $muse
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

    function vol() {
        alsa=$(amixer get Master | sed -n 's/^.*\[\([0-9]\+\)%.*$/\1/p'| uniq)
        echo $alsa
    }
    function cpu() { use=$(ps -eo pcpu | awk 'BEGIN {sum=0.0f} {sum+=$1} END {print sum}')
        echo $use
    }
   function net() {
	con=$(ping -c 1 8.8.8.8 >/dev/null 2>&1 && echo "connected" || echo "disconnected")
	echo $con
    }    

    echo "^fg(#2F888A) kYo=$(desk) ^fg(#0066FF) m:^fg(#0099FF) $(ncc) ^fg(#5ED8EB)v: $(vol)%                                                                                                                                                     ^fg(#FFFFFF) $(clock)                                                                                                                                          ^fg(#000000)net: ^fg(#AAAAAA)$(net) ^fg(#0099CC) ram: $(mem) ^fg(#3366CC) cpu: $(cpu)% - $(temp) °C "
}
 while true 
 do
 STRLEN=$(wc -l ~/.barscripts/song | awk '{print $1}')	
   for i in `seq 1 $STRLEN`;
   do
     echo "$(statusbar)"
     sleep .25 
   done
 done | dzen2 -bg '#262626' -fn 'tamsyn-8-' -h 20 -ta l -p -xs 2 -dock &
