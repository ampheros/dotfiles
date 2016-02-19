#!/bin/bash

#create user and directories
useradd -m -G wheel -s /bin/bash nava
mkdir /home/nava/git
mkdir /home/nava/builds
cd /home/nava/builds

# install devel packages and get fastest mirrors
pacman -S --noconfirm reflector base-devel git
reflector --verbose -l 5 --sort rate --save /etc/pacman.d/mirrorlist

# install aur helper
sudo sed -i "79i [haskell-core]" /etc/pacman.conf
sudo sed -i '80i Server = http://xsounds.org/~haskell/core/$arch' /etc/pacman.conf
pacman -Syu
git clone https://github.com/aurapm/aura.git
cd aura
makepkg -sri --noconfirm
cd ..

#install remaining packages
pacman -S --noconfirm sudo qutebrowser-git bspwm sxhkdrc xbindkeys dzen2 rxvt-unicode mpd ncmpcpp 
aura -A --noconfirm pdfjs 

