* Gestion d'erreurs (code d'erreur de la derniere commande stockée dans $?)
* $? à gérer dans dollar_replace
* Gerer >| et une ligne comme ps | >| pouet ls (redirections)
* quitter une commande avec ctrl-C doit renvoyer 1 dans $?
* export A=pouet fait un truc bizarre dans env (ligne export ?)
* export A=pouet 10 fois va faire 10 entrees dans export et env
* copier / coller dans le prompt fait un truc bizarre (quand il y a un caractere de fin de ligne ?). Ca fait des artefacts juste apres le prompt, impossible de delete.
* signaux marchent bizarre dans certains cas.
* export += ?