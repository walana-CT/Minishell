TODO
* appeler deux fois export segfault
* export leaks
* export A+=
* export doit dol_replace
* unset detruit toutes les variables apres le arg
* signaux : sauter une ligne apres ctrl-C (apres passwd, as, ce genre de plans)
* desactiver sigquit (reactivé pour certains tests)

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
