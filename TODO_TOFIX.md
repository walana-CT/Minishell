TODO
* Gestion d'erreurs (code d'erreur de la derniere commande stockée dans $?)
* Gerer >| et une ligne comme ps | >| pouet ls (redirections)
* Gerer mieux les | | | | |
* quitter une commande avec ctrl-C doit renvoyer 1 dans $?
* export A+=
* signaux marchent bizarre / pas dans certains cas (heredoc, passwd)
* $$ le vrai bash renvoi son pid mais je ne voit pas comment faire avec les
	fonctions autorisées (on pourrait avec sigaction mais c'est vraiment dégueu);
* assigner correctement les valeurs d'err.


OK
* copier / coller dans le prompt fait un truc bizarre. Ca fait des artefacts juste apres le prompt, impossible de delete : c'etait RESET dans le prompt
* leaks sur les builtins
* export A=pouet fait un truc bizarre dans env (ligne export ?)
* export A=pouet 10 fois va faire 10 entrees dans export et env
* Gerer $A$B
* Gerer $A$B$C
* Gerer $$
* $? à gérer dans dollar_replace