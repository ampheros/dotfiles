#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return
alias redwm='cd ~/dwm; updpkgsums; makepkg -efi --noconfirm; killall dwm'
alias ls='ls --color=auto'
PS1='\[\033[0;36m\]╔═(\[\033[0m\033[0;36m\]\u\[\033[0m\]@\[\033[0;32m\]\h\[\033[0m\033[0;36m\])────(\[\033[0m\]\t \d\[\033[0;36m\])────(\[\033[0m\]\w\[\033[0;36m\])\n\[\033[0;36m\]╚═══[ \[\033[0m\033[0;36m\]\$\[\033[0m\033[0;36m\]]>\[\033[0m\] '
export PATH=$PATH:/home/nava/bin
#eval $(dircolors ~/.dircolors)
. /etc/profile.d/vte.sh
export EDITOR="vim"
