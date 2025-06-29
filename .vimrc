syntax on
:set number
let g:user42 = 'hozhan'
let g:mail42 = 'hozhan@student.42kocaeli.com.tr'

" Hibrit modda başlat
set number relativenumber

" Göreceli numaraları kapatma kısayolu (F3)
nnoremap <F3> :set relativenumber!<CR>
" F4: TÜM satır numaralarını aç/kapa
nnoremap <F4> :set number!<CR>

" ----------------------------
" Temel Ayarlar
" ----------------------------
set nocompatible
filetype plugin indent on
syntax enable
set encoding=utf-8

" ----------------------------
" C Dili Özel Ayarları
" ----------------------------
autocmd FileType c setlocal
    \ tabstop=4
    \ shiftwidth=4
    \ softtabstop=4
    \ noexpandtab
    \ cindent
    \ cinoptions=:0,l1,t0,g0,(0
    \ textwidth=80
    \ colorcolumn=80
    \ formatoptions=croql

" ----------------------------
" Klavye Kısayolları
" ----------------------------
" 42Header için
" let g:user42 = 'kullanici_adiniz'
" let g:mail42 = 'eposta@adresiniz'
" map <F1> :42header<CR>

" Hızlı derleme ve çalıştırma
autocmd FileType c nnoremap <F5> :w<CR>:!gcc -Wall -Wextra -Werror % -o %:r && ./%:r<CR>
autocmd FileType c nnoremap <F6> :w<CR>:!gcc -g % -o %:r && valgrind ./%:r<CR>

" ----------------------------
" Eklentiler (Opsiyonel)
" ----------------------------
" Vim-plug ile eklenti yönetimi
call plug#begin('~/.vim/plugged')
Plug 'vim-syntastic/syntastic'           " Syntax kontrol
Plug 'preservim/nerdcommenter'           " Kolay yorum satırı
Plug 'rhysd/vim-clang-format'            " Formatlama
Plug 'preservim/tagbar'                   " Kod yapısı görselleştirme
Plug 'octol/vim-cpp-enhanced-highlight'   " Gelişmiş syntax vurgulama
call plug#end()

" ----------------------------
" Syntastic Ayarları
" ----------------------------
let g:syntastic_c_checkers = ['gcc']
let g:syntastic_c_compiler = 'gcc'
let g:syntastic_c_compiler_options = '-Wall -Wextra -Werror -std=c99'

" ----------------------------
" Clang Format Ayarları
" ----------------------------
let g:clang_format#style_options = {
    \ "BasedOnStyle": "Google",
    \ "IndentWidth": 4,
    \ "UseTab": "Always",
    \ "BreakBeforeBraces": "Linux"}

autocmd FileType c inoremap { {<CR>}<Esc>O
autocmd FileType c inoremap ( ()<Left>
autocmd FileType c inoremap [ []<Left>
autocmd FileType c inoremap " ""<Left>
autocmd FileType c inoremap ' ''<Left>
