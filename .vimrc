syntax on
colorscheme elflord
set nu
" check file change every 4 seconds ('CursorHold') and reload the buffer upon detecting change
set autoread                                                                                             
au CursorHold * checktime
set mouse=a
set nocompatible
filetype off
set rtp+=~/.vim/bundle/vundle/
call vundle#rc()
set grepprg=grep\ -nH\ $*
let g:tex_flavor = "latex"
set runtimepath=~/.nvim,$VIM/vimfiles,$VIMRUNTIME,$VIM/vimfiles/after,~/.nvim/after
filetype plugin indent on
set tabstop=4
set shiftwidth=4
set expandtab
