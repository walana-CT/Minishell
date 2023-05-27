TODO
* Gestion d'erreurs (code d'erreur de la derniere commande stockée dans $?)
* $? à gérer dans dollar_replace
* Gerer >| et une ligne comme ps | >| pouet ls (redirections)
* quitter une commande avec ctrl-C doit renvoyer 1 dans $?
* export A=pouet fait un truc bizarre dans env (ligne export ?)
* export A=pouet 10 fois va faire 10 entrees dans export et env
* export A+=
* signaux marchent bizarre / pas dans certains cas (heredoc, passwd)

OK
* copier / coller dans le prompt fait un truc bizarre. Ca fait des artefacts juste apres le prompt, impossible de delete : c'etait RESET dans le prompt
* leaks sur les builtins
