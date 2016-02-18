#!/bin/bash
BRANCH= #Enter a branch
NVIDIA=nvidia
NOUVEAU=xf86-video-nouveau

if [ $(pacman -Qqs ^mesa-libgl$) ]; then
	pacman -S $NVIDIA ${NVIDIA}-libgl lib32-${NVIDIA}-libgl
elif [ $(pacman -Qqs ^${NVIDIA}$) ]; then
	pacman -S --needed $NOUVEAU mesa-libgl lib32-mesa-libgl
	pacman -R $NVIDIA
fi
