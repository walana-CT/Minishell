TODO

* tests sous linux avec fsanitize de compet. Qques leaks (random !), pas mal de segfault souvent liés à unset on dirait. Bcp de tests c/c en dessous, 3 patterns de plantage détectés p/r fonctions qui plantent


* unset crash random ?

msh > unset QDFGFSD
msh > unset HOME
msh > unset USER
msh > unset PATH
LeakSanitizer:DEADLYSIGNAL
==9224==ERROR: LeakSanitizer: SEGV on unknown address 0x616000010000 (pc 0x55ccd90733de bp 0x7fff28ffbfa0 sp 0x7fff28ffbf70 T0)
==9224==The signal is caused by a WRITE memory access.
    #0 0x55ccd90733de in unset_arg Sources/ms_unset.c:65
    #1 0x55ccd90734a2 in ms_unset Sources/ms_unset.c:84
    #2 0x55ccd906f209 in ms_do_builtin Sources/ms_exec01.c:32
    #3 0x55ccd906f5ee in ms_exec Sources/ms_exec01.c:87
    #4 0x55ccd906d557 in ms_launch_cmds Sources/minishell.c:21
    #5 0x55ccd906d6c9 in minishell Sources/minishell.c:51


//////////////// autre session ////////////////////////
msh > unset HOME
msh > unset SHLVL
msh > unset USER
msh > unset HOME
AddressSanitizer:DEADLYSIGNAL
=================================================================
==8223==ERROR: AddressSanitizer: SEGV on unknown address (pc 0x562beddc0435 bp 0x7fff637149a0 sp 0x7fff637149a0 T0)
==8223==The signal is caused by a READ memory access.
==8223==Hint: this fault was caused by a dereference of a high value address (see register values below).  Dissassemble the provided pc to learn which register was used.
    #0 0x562beddc0435 in is_env Sources/ms_unset.c:17
    #1 0x562beddc04a9 in ms_env_pos Sources/ms_unset.c:39
    #2 0x562beddc0504 in unset_arg Sources/ms_unset.c:53
    #3 0x562beddc0662 in ms_unset Sources/ms_unset.c:84
    #4 0x562beddbc3c9 in ms_do_builtin Sources/ms_exec01.c:32
    #5 0x562beddbc7ae in ms_exec Sources/ms_exec01.c:87
    #6 0x562beddba717 in ms_launch_cmds Sources/minishell.c:21
    #7 0x562beddba889 in minishell Sources/minishell.c:51
    #8 0x562beddbaa5f in main Sources/minishell.c:105

//////////////// autre session ////////////////////////
msh > unset LANGUAGE
msh > unset SSH_AUTH_SOCK
msh > unset LANGUAGE
msh > unset XDG_VTNR
msh > unset LANGUAGE
LeakSanitizer:DEADLYSIGNAL
==8988==ERROR: LeakSanitizer: SEGV on unknown address 0x00006e006e75 (pc 0x55fb700e7275 bp 0x7ffebaf57ce0 sp 0x7ffebaf57ce0 T0)
==8988==The signal is caused by a READ memory access.
    #0 0x55fb700e7275 in is_env Sources/ms_unset.c:17
    #1 0x55fb700e72e9 in ms_env_pos Sources/ms_unset.c:39
    #2 0x55fb700e7344 in unset_arg Sources/ms_unset.c:53
    #3 0x55fb700e74a2 in ms_unset Sources/ms_unset.c:84

//////////////// autre session ////////////////////////
msh > unset SHELL
msh > unset USER
msh > unset HOME
msh > unset LANGUAGE
msh > unset XDG_VTNR
msh > unset SSH_AUTH_SOCK
msh > unset DISPLAY
msh > unset SHELL
LeakSanitizer:DEADLYSIGNAL
==9051==ERROR: LeakSanitizer: SEGV on unknown address 0x00006e006e75 (pc 0x55dfbc00e275 bp 0x7ffc40f0f180 sp 0x7ffc40f0f180 T0)
==9051==The signal is caused by a READ memory access.
    #0 0x55dfbc00e275 in is_env Sources/ms_unset.c:17
    #1 0x55dfbc00e2e9 in ms_env_pos Sources/ms_unset.c:39
    #2 0x55dfbc00e344 in unset_arg Sources/ms_unset.c:53

//////////////// autre session ////////////////////////
msh > unset PATH
msh > unset HOME
msh > unset USER
msh > unset LANGUAGE
LeakSanitizer:DEADLYSIGNAL
==9112==ERROR: LeakSanitizer: SEGV on unknown address 0x00006e006e75 (pc 0x562fc2aae60a bp 0x7ffff5a0f6b0 sp 0x7ffff5a0f6b0 T0)
==9112==The signal is caused by a READ memory access.
    #0 0x562fc2aae60a in ft_strnstr /mnt/data/Docs/42/minishell/libft/ft_strnstr.c:29
    #1 0x562fc2aaaf60 in ms_getpath Sources/ms_lexing.c:21
    #2 0x562fc2aab36e in ms_lex Sources/ms_lexing.c:104
    #3 0x562fc2aa7540 in ms_launch_cmds Sources/minishell.c:19
    #4 0x562fc2aa76c9 in minishell Sources/minishell.c:51




* unset PATH segfault des fois
msh > unset PATH
msh > ls
msh: ls: command not found
-> comportmeent ok

//////////////// autre session ////////////////////////
msh > unset PATH
msh > ls

AddressSanitizer:DEADLYSIGNAL
=================================================================
==8092==ERROR: AddressSanitizer: SEGV on unknown address (pc 0x55de30c18e4c bp 0x7ffdf1538ae0 sp 0x7ffdf1538aa0 T0)
==8092==The signal is caused by a READ memory access.
==8092==Hint: this fault was caused by a dereference of a high value address (see register values below).  Dissassemble the provided pc to learn which register was used.
    #0 0x55de30c18e4c in ft_strnstr /mnt/data/Docs/42/minishell/libft/ft_strnstr.c:29
    #1 0x55de30c14120 in ms_getpath Sources/ms_lexing.c:21
    #2 0x55de30c1452e in ms_lex Sources/ms_lexing.c:104
    #3 0x55de30c10700 in ms_launch_cmds Sources/minishell.c:19
    #4 0x55de30c10889 in minishell Sources/minishell.c:51
    #5 0x55de30c10a5f in main Sources/minishell.c:105
    #6 0x7fbf6692dd8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #7 0x7fbf6692de3f in __libc_start_main_impl ../csu/libc-start.c:392
    #8 0x55de30c10614 in _start (/mnt/data/Docs/42/minishell/minishell+0x2614)

//////////////// autre session ////////////////////////
msh > unset ZSH
msh > unset XDG_SEAT
AddressSanitizer:DEADLYSIGNAL
=================================================================
==8132==ERROR: AddressSanitizer: SEGV on unknown address (pc 0x55fb1625de4c bp 0x7ffc1bf6cde0 sp 0x7ffc1bf6cda0 T0)
==8132==The signal is caused by a READ memory access.
==8132==Hint: this fault was caused by a dereference of a high value address (see register values below).  Dissassemble the provided pc to learn which register was used.
    #0 0x55fb1625de4c in ft_strnstr /mnt/data/Docs/42/minishell/libft/ft_strnstr.c:29
    #1 0x55fb16259120 in ms_getpath Sources/ms_lexing.c:21
    #2 0x55fb1625952e in ms_lex Sources/ms_lexing.c:104
    #3 0x55fb16255700 in ms_launch_cmds Sources/minishell.c:19
    #4 0x55fb16255889 in minishell Sources/minishell.c:51
    #5 0x55fb16255a5f in main Sources/minishell.c:105
    #6 0x7f6734342d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #7 0x7f6734342e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #8 0x55fb16255614 in _start (/mnt/data/Docs/42/minishell/minishell+0x2614)




* leaks apres unset PATH (?) Des fois...
=================================================================
==7942==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 2 byte(s) in 1 object(s) allocated from:
    #0 0x7fbeb4aa3867 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x55cbb8a9afc6 in ft_itoa /mnt/data/Docs/42/minishell/libft/ft_itoa.c:61
    #2 0x55cbb8a95250 in replace_qm Sources/ms_dollar_replace_00.c:23
    #3 0x55cbb8a952da in dol_replace Sources/ms_dollar_replace_00.c:37
    #4 0x55cbb8a955f9 in ms_trim_empty_dolls Sources/ms_dollar_replace_01.c:47
    #5 0x55cbb8a98429 in ms_lex Sources/ms_lexing.c:95
    #6 0x55cbb8a94700 in ms_launch_cmds Sources/minishell.c:19
    #7 0x55cbb8a94889 in minishell Sources/minishell.c:51
    #8 0x55cbb8a94a5f in main Sources/minishell.c:105





* permission denied sur creation de fichier dans repertoire sans droit
msh > echo bonjour >/tut
msh: /tut: No such file or directory
msh > echo $?
1




* unset SHLVL puis relancer ./minishell segfault (bash met SHLVL à 1 dans ce cas)
msh > unset SHLVL
msh > ./minishell 
AddressSanitizer:DEADLYSIGNAL
=================================================================
==7881==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x55dcb2f708e6 bp 0x7ffcca1d6e00 sp 0x7ffcca1d6dd0 T0)
==7881==The signal is caused by a READ memory access.
==7881==Hint: address points to the zero page.
    #0 0x55dcb2f708e6 in incr_shell_lvl Sources/ms_env_utils_00.c:22
    #1 0x55dcb2f70d67 in ms_copy_env Sources/ms_env_utils_01.c:59
    #2 0x55dcb2f6fa3e in main Sources/minishell.c:101
    #3 0x7fca45575d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #4 0x7fca45575e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #5 0x55dcb2f6f614 in _start (/mnt/data/Docs/42/minishell/minishell+0x2614)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV Sources/ms_env_utils_00.c:22 in incr_shell_lvl
==7881==ABORTING




* SHLVL10
msh > ./minishell
msh > ./minishell
msh > ./minishell
=================================================================
==5714==ERROR: AddressSanitizer: attempting free on address which was not malloc()-ed: 0x6020000011f6 in thread T0
    #0 0x7f0646337517 in __interceptor_free ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:127
    #1 0x55e9de20b129 in ft_strresize /mnt/data/Docs/42/minishell/libft/ft_strresize.c:38
    #2 0x55e9de203914 in incr_shell_lvl Sources/ms_env_utils_00.c:26
    #3 0x55e9de203d67 in ms_copy_env Sources/ms_env_utils_01.c:59
    #4 0x55e9de202a3e in main Sources/minishell.c:101
    #5 0x7f0646030d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #6 0x7f0646030e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #7 0x55e9de202614 in _start (/mnt/data/Docs/42/minishell/minishell+0x2614)




* apres unset SHLVL on peut plus execve (?!). Puis segfault sur env
msh > unset SHLVL
msh > ls
msh: ls: command not found
msh > env
SSH_AUTH_SOCK=/tmp/ssh-XXXXXXtRe7w5/agent.1297
LANGUAGE=fr_FR
LANG=fr_FR.UTF-8
etc.

AddressSanitizer:DEADLYSIGNAL
=================================================================
==8038==ERROR: AddressSanitizer: SEGV on unknown address (pc 0x56478d34cc71 bp 0x7ffe352d65c0 sp 0x7ffe352d65c0 T0)
==8038==The signal is caused by a READ memory access.
==8038==Hint: this fault was caused by a dereference of a high value address (see register values below).  Dissassemble the provided pc to learn which register was used.
    #0 0x56478d34cc71 in ms_env_hasval Sources/ms_env_utils_01.c:27
    #1 0x56478d34cf64 in ms_printtab Sources/ms_env.c:19
    #2 0x56478d34d005 in ms_env Sources/ms_env.c:38
    #3 0x56478d34d313 in ms_do_builtin Sources/ms_exec01.c:24
    #4 0x56478d34d7ae in ms_exec Sources/ms_exec01.c:87
    #5 0x56478d34b717 in ms_launch_cmds Sources/minishell.c:21
    #6 0x56478d34b889 in minishell Sources/minishell.c:51
    #7 0x56478d34ba5f in main Sources/minishell.c:105

//////////////// autre session ////////////////////////
msh > unset HOME
msh > unset USER
msh > unset SHLVL
msh > env
SSH_AUTH_SOCK=/tmp/ssh-XXXXXXtRe7w5/agent.1297
LANGUAGE=fr_FR
LANG=fr_FR.UTF-8
GTK3_MODULES=xapp-gtk3-module
XDG_CURRENT_DESKTOP=XFCE
SSH_AGENT_PID=1298
SESSION_MANAGER=local/DellOptiPlex:@/tmp/.ICE-unix/1042,unix/DellOptiPlex:/tmp/.ICE-unix/1042
XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/mamat
COLORTERM=truecolor
DESKTOP_SESSION=xfce
XDG_MENU_PREFIX=xfce-
XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session0
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
XDG_VTNR=7
XDG_SEAT=seat0
COMPIZ_CONFIG_PROFILE=mint
GTK_MODULES=gail:atk-bridge
XDG_CONFIG_DIRS=/etc/xdg/xdg-xfce:/etc/xdg:/etc/xdg
VTE_VERSION=6800
XDG_SESSION_DESKTOP=xfce
QT_ACCESSIBILITY=1
XDG_DATA_DIRS=/usr/share/xfce4:/home/mamat/.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/share:/usr/share:/usr/share
LOGNAME=mamat
XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
PATH=/home/mamat/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
XDG_RUNTIME_DIR=/run/user/1000
WINDOWID=83886083
SHELL=/bin/zsh
XDG_SESSION_ID=c1
CLUTTER_BACKEND=x11
XDG_SESSION_TYPE=x11
PANEL_GDK_CORE_DEVICE_EVENTS=0
GDM_LANG=fr_FR
XAUTHORITY=/home/mamat/.Xauthority
QT_QPA_PLATFORMTHEME=qt5ct
PWD=/home/mamat/Docs/42/minishell
XDG_SESSION_CLASS=user
GDMSESSION=xfce
TERM=xterm-256color
DISPLAY=:0.0
ZSH=/home/mamat/.oh-my-zsh
PAGER=less
LESS=-R
LSCOLORS=Gxfxcxdxbxegedabagacad
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
_=/home/mamat/Docs/42/minishell/./minishell
AddressSanitizer:DEADLYSIGNAL
=================================================================
==8395==ERROR: AddressSanitizer: SEGV on unknown address (pc 0x55d68ef70c71 bp 0x7ffffb176240 sp 0x7ffffb176240 T0)
==8395==The signal is caused by a READ memory access.
==8395==Hint: this fault was caused by a dereference of a high value address (see register values below).  Dissassemble the provided pc to learn which register was used.
    #0 0x55d68ef70c71 in ms_env_hasval Sources/ms_env_utils_01.c:27
    #1 0x55d68ef70f64 in ms_printtab Sources/ms_env.c:19
    #2 0x55d68ef71005 in ms_env Sources/ms_env.c:38
    #3 0x55d68ef71313 in ms_do_builtin Sources/ms_exec01.c:24
    #4 0x55d68ef717ae in ms_exec Sources/ms_exec01.c:87
    #5 0x55d68ef6f717 in ms_launch_cmds Sources/minishell.c:21
    #6 0x55d68ef6f889 in minishell Sources/minishell.c:51
    #7 0x55d68ef6fa5f in main Sources/minishell.c:105
    #8 0x7f3dad0b6d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #9 0x7f3dad0b6e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #10 0x55d68ef6f614 in _start (/mnt/data/Docs/42/minishell/minishell+0x2614)


OK
* copier / coller dans le prompt fait un truc bizarre. Ca fait des artefacts juste apres le prompt, impossible de delete : c'etait RESET dans le prompt
* leaks sur les builtins
* export A=pouet fait un truc bizarre dans env (ligne export ?)
* export A=pouet 10 fois va faire 10 entrees dans export et env
* Gerer $A$B
* Gerer $A$B$C
* Gerer $$
* $? à gérer dans dollar_replace
* assigner correctement les valeurs d'err.
* quitter une commande avec ctrl-C doit renvoyer 1 dans $?
* Gestion d'erreurs (code d'erreur de la derniere commande stockée dans $?)
* Gerer mieux les | | | | |
* Gerer >| -> syntax error
* historique permanent dans fichier .ms_history
* exit n'exit plus ?
* signaux marchent bizarre / pas dans certains cas (heredoc, passwd, minishell dans minishell)
* segfault quand argument invalides.
* enlever les $EMPTY au debut de ms_lex avant de quotesplit
* cd, cd - (oldpasswd)
* env : pas de valeurs vides
* export declare -x, content des variables entre quotes
* permission denied a l'execution d'un fichier ./ ou / si chmod -x
* exit segfault
* (est-ce le cas pour toutes les builtins ?) echo $? renvoie 0 apres un fd incorrect (devrait renvoyer 1)
* unset detruit toutes les variables apres le arg
* export leaks
* signaux : sauter une ligne apres ctrl-C (apres passwd, as, ce genre de plans)
* appeler deux fois export segfault
* export A+=
* export doit dol_replace(comment ça px ile fait pas le sacripan)
* desactiver sigquit (reactivé pour certains tests)
