#!/bin/bash
     function clock() {
    time=$(date "+%e %b  %l:%M")
    echo $time
    }
    
    function ncc() {
sed -n ${i}p ~/.barscripts/song
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
	
	down=$(conky -i 2 | sed -n '2p' | awk '{print $2}')
	up=$(conky -i 2 | sed -n '2p' | awk '{print $4}')
	con=$(ping -c 1 8.8.8.8 >/dev/null 2>&1 && echo "y" || echo "n")
	echo $con
	echo " ^fg(#000000)up: ^fg(#AAAAAA)$up/s ^fg(#000000)down: ^fg(#AAAAAA)$down/s"

	
    }    
function windowStatus(){
	wid=$(xdotool getactivewindow)
	winname=$(xwininfo -id $wid | grep Window | grep id | awk '{print substr($0, index($0,$5))}')
	echo " ^fg(#0C5AEB)w: $winname"
}

function statusbar {

    function desk() {
    DESKTOP=$(xprop -root _NET_CURRENT_DESKTOP | awk '{print $3}')
    case $DESKTOP in
    0)  echo "[^fg(#FFFFFF)I^fg(#0099FF) ii iii] [iv v vi vii]"
        ;;
    1)  echo "[i ^fg(#FFFFFF)II^fg(#0099FF) iii] [iv v vi vii]"
        ;;
    2)  echo "[i ii ^fg(#FFFFFF)III^fg(#0099FF)] [iv v vi vii]"
        ;;
        3)  echo "[i ii iii] [^fg(#FFFFFF)IV^fg(#0099FF) v vi vii]"
            ;;
        4)  echo "[i ii iii] [iv ^fg(#FFFFFF)V^fg(#0099FF) vi vii]"
            ;;
        5)  echo "[i ii iii] [v vi ^fg(#FFFFFF)VI^fg(#0099FF) vii]"
            ;;
        6)  echo "[i ii iii] [v vi vii ^fg(#FFFFFF)VII^fg(#0099FF)]"
            ;;
        *)  echo "error"
    esac
    }

	echo " ^fg(#0099FF) kYo=$(desk) ^fg(#0066FF):: " 
}

#desktop
 while true 
 do
 STRLEN=$(wc -l ~/.barscripts/song | awk '{print $1}')	
   for i in `seq 1 $STRLEN`;
   do
     echo "$(statusbar)"
     sleep .25 
   done
 done | dzen2 -bg '#262626' -fn 'tamsyn-8-' -w 200 -h 20 -ta l -p -xs 2 -dock &

#volume
while true
do
	echo "^fg(#5ED8EB)  v: $(vol)%$(windowStatus)" 	
	sleep 1
done | dzen2 -bg '#262626' -fn 'tamsyn-8-' -w 890 -h 20 -x 400 -ta l -p -xs 2 -dock & 
#music
while true
do
	mu=$(mpc status | grep ']' | awk '{print $1}')
	if [ "$mu" == "[playing]" ]
	then
	echo $(mpc current) | skroll -n 40 -d 0.25 -r 
	else
	echo "[paused]"
	fi
	sleep 1
done | dzen2 -bg '#262626' -fn 'Meguri P-8' -w 205 -h 20 -x 200 -ta l -p -xs 2 -dock &

#clock
while true
do
	echo "^fg(#FFFFFF) $(clock)"  
	sleep 1

done | dzen2 -bg '#262626' -fn 'tamsyn-8-' -w 350 -h 20 -x 1150 -ta c -p -xs 2 -dock &

#space
while true
do
	echo " "
	sleep 10	
done | dzen2 -bg '#262626' -fn 'tamsyn-8-' -w 700 -h 20 -x 1450 -ta l -p -xs 2 -dock &


#system info
while true
do
	echo "^fg(#000000)net: ^fg(#AAAAAA)$(net) ^fg(#0099CC) ram: $(mem) ^fg(#3366CC) cpu: $(cpu)% - $(temp) °C "
	sleep 1
done | dzen2 -bg '#262626' -fn 'tamsyn-8-' -w 1400 -h 20 -x 2150 -ta right -p -xs 2 -dock &
