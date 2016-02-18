#!/bin/bash
mv /etc/X11/xorg.conf.d/steamconf /etc/X11/xorg.conf.d/steam.conf
startx
mv /etc/X11/xorg.conf.d/steam.conf /etc/X11/xorg.conf.d/steamconf
