if [ $# -ge 1 ]; then
        game="$(which $1)"
        bspwm="$(which bspwm)"
        tmpgame="/tmp/tmpgame.sh"
        DISPLAY=:1.0
        echo -e "${bspwm} &\n${game}" > ${tmpgame}
        echo "starting ${game}"
        xinit ${tmpgame} -- :1 -layout Steam || exit 1
else
        echo "not a valid argument"
fi
