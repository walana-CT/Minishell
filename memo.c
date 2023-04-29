

/*
			readline
*/
#include <curses.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <term.h>
#include <unistd.h>

char	*readline (const char *prompt);
/*
-permet de lire une ligne du terminal

-retourne une valeur allouee avec malloc(3)

-pour plus d'info consulter THE GNU READLINe LIBRARY

-retour : string vide si rien NULL si err
*/

void	rl_clear_history (void);
/*
supprime tout l'historique
*/

int	rl_on_new_line (void);
/*
- Notifie la fonction d'update qu'une nouvelle ligne a ete rentree.

- Cela se fait apres l'affichage de la nouvelle ligne.
*/

void	rl_replace_line (const char *text, int clear_undo);
/*
- Remplace le contenu de rl_line_buffer avec text.
- La ponctuation est preservee si possible.
- Si clear_undo a une valeur non-nulle alors la undo list associee est
reeinitialisee
*/

void	rl_redisplay (void);
/*
- Modifie l'affichage de l'ecran pour se conformer a l'etat actuel de rl_line_buffer
*/

void	add_history (line);
/*
permet d'ajouter une ligne a l'historique
*/


char	*getcwd ( char *buffer, size_t size );
/*
- Permet de retourner le chemin vers le repertoire de travail courant.

- Retourne un pointeur vers buffer en cas de succes et NULL en cas d'erreur.

- En cas d'erreur la variable erno sera fixee.
*/

int	chdir (const char *path);
/*
- Permet de definir le repertoire de travail courant.

- Retourne 0 en cas de succes et -1 en cas d'erreur.

- En cas d'erreur la variable erno sera fixee.
*/


int	stat (const char *path, struct stat *buf);
/*
- Recupre l'etat du fichier pointe par path.
*/

int fstat(int fd, struct stat *buf);
/*
- fstat() est identique à stat(), sauf que le  fichier  dont  l'état  est  donné  est  celui
référencé par le descripteur de fichier fd.
*/


int	lstat (const char *path, struct stat *buf);
/*
- lstat()  est  identique  à stat(), sauf que dans le cas où path est un lien symbolique, il
donne l'état du lien lui-même plutôt que celui du fichier visé.
*/


int	unlink (const char *pathname);
/*
- unlink() détruit un nom dans le système de fichiers. Si ce nom était le dernier lien sur un
fichier, et si aucun processus n'a ouvert ce fichier, ce dernier est effacé, et l'espace
qu'il utilisait est rendu disponible.

- Si le nom était le dernier lien sur un fichier, mais qu'un processus
conserve encore le fichier ouvert, celui-ci continue d'exister
jusqu'à ce que le dernier descripteur le référençant soit fermé.

- Si le nom correspond à un lien symbolique, le lien est supprimé.

- Si le nom correspond à une socket, une FIFO, ou un périphérique,le nom est
supprimé mais les processus qui ont ouvert l'objet peuvent continuer à l'utiliser.
*/

DIR	*opendir (const char *name);
/*
- La fonction opendir() ouvre un flux répertoire correspondant au répertoire name, et renvoie
un pointeur sur ce flux. Le flux est positionné sur la première entrée du répertoire.
*/

int	readdir (DIR *dir, struct dirent *entry, struct dirent **result);
/*
La fonction readdir() renvoie un pointeur sur une structure dirent représentant l'entrée suivante
du flux répertoire pointé par dir. Elle renvoie NULL à la fin du répertoire, ou en cas d'erreur.
*/

struct dirent {
    ino_t          d_ino;       /* numéro d'inœud */
    off_t          d_off;       /* décalage jusqu'à la dirent suivante */
    unsigned short d_reclen;    /* longueur de cet enregistrement */
    unsigned char  d_type;      /* type du fichier */
    char           d_name[256]; /* nom du fichier */
};

int	closedir (DIR *dir);
/*
- La fonction closedir() ferme le flux de répertoire associé à dir. Après cette invocation,
le descripteur dir du flux de répertoire n'est plus disponible.
- La fonction closedir() renvoie 0 si elle réussit, ou -1 si elle échoue, auquel cas
errno contient le code d'erreur.  
*/

int isatty(int desc);
/*
- renvoie 1 si desc est un descripteur de fichier ouvert connecté à un terminal, ou 0 autrement.  
*/

int	ttyname_r (int fd, char *buf, size_t buflen);
/*
- La fonction ttyname() renvoie un pointeur sur le chemin d'accès terminé par un octet nul du
périphérique terminal ouvert associé au descripteur de fichier fd, ou NULL en cas
d'erreur (par exemple si fd n'est pas connecté à un terminal). La valeur renvoyée peut
pointer vers des données statiques, susceptibles d'être écrasées lors d'un appel ultérieur.
La fonction ttyname_r() stocke la valeur dans le tampon buf de longueur buflen.

- La fonction ttyname() renvoie un pointeur sur le chemin d'accès. En cas d'erreur, elle
renvoie NULL et remplit errno avec le code d'erreur. La fonction ttyname_r() renvoie zéro
si elle réussit et un code d'erreur si elle échoue.
*/

int ttyslot(void);
/*
- Ainsi, la fonction ttyslot() renvoie l'index du terminal de contrôle du processus appelant
dans le fichier /etc/ttys, qui est aussi (en principe) l'index de l'entrée pour l'utilisateur
en cours dans le fichier /etc/utmp. BSD utilise encore le fichier /etc/ttys, mais pas les
systèmes System V, qui ne peuvent donc pas s'y référer. Sur ces systèmes, la documentation dit
que ttyslot() renvoie l'index de l'utilisateur appelant dans la base de données de comptabilité
des utilisateurs.

- Si elle réussit, cette fonction renvoie le numéro d'entrée. Si elle échoue (par exemple si
aucun des descripteurs 0, 1 ou 2 n'est associé avec un terminal trouvé dans la base de données),
elle renvoie 0 sur Unix V6 et V7 les systèmes BSD, mais -1 sur les autres systèmes System V.
*/


int	ioctl(int d, int requête, ...);
/*
- La fonction ioctl() modifie le comportement des périphériques sous-jacents des fichiers spéciaux.
En particulier, de nombreuses caractéristiques des fichiers spéciaux en mode caractère (par
exemple des terminaux) peuvent être contrôlées avec des requêtes ioctl(). L'argument d doit être
un descripteur de fichier ouvert.

-  Le second argument est le code de la requête dépendant du périphérique. Le troisième argument
est un pointeur non typé. Il est traditionnellement défini en char *argp (ceci date de l'époque
avant que void * soit du C valide), et sera ainsi nommé dans le reste de cette page.

- En principe, ioctl() renvoie 0 s'il réussit, ou -1 s'il échoue. Certaines requêtes ioctl()
utilisent la valeur de retour comme paramètre de sortie, et renvoient une valeur positive si
elles réussissent (et -1 pour les erreurs). En cas d'échec, errno contient le code d'erreur.
*/


char	*getenv (const char * varName);
/*
- Cette fonction est utilisée pour récupérer le contenu d'une variable d'environnement. Les
variables d'environnement sont définies par le système d'exploitation utilisé et permmettent
d'obtenir des informations sur l'environnement dans lequel s'exécute le processus (le programme)
en cours.

- varName : définie le nom de la variable d'environnement souhaitée. Notez que,
conventionnellement, les variables d'environnement sont souvent nommées en
majuscules (bien que cela ne soit pas une obligation absolue).
Par exemple : PATH, LD_LIBRARY_PATH, ...

- Si la variable d'environnement demandée n'existe pas, un pointeur nul (NULL) vous sera
retourné. Dans le cas ou la variable existe bel et bien, sa valeur (une chaine de caractères)
vous sera retourné. Il ne faut surtout pas chercher à libérer la mémoire de la variable
d'environnement après son utilisation : en fait, elle est stockée dans une zone
de mémoire gérée par le processus et vous ne devez en aucun cas chercher à modifier cette valeur. 
*/


//termios

int tcsetattr(int fd, int optional_actions,
			const struct termios *termios_p);
/*
- fixe les paramètres du terminal (à moins que le matériel sous-jacent ne le
prenne pas en charge) en lisant la structure termios pointée par termios_p.
optional_actions précise quand les changements auront lieu
*/


int tcgetattr(int fd, struct termios *termios_p);
/*
- tcgetattr() récupère les paramètres associés à l'objet référencé par fd
et les stocke dans la structure termios pointée par termios_p.
Cette fonction peut être appelée par un processus en arrière-plan ;
néanmoins, les attributs de terminal peuvent être modifiés par la suite
par le processus en avant-plan. 
*/


int tgetent (char *bp, const char *name);
/*
- The tgetent routine loads the entry for name. It returns 1 on success,
0 if there is no such entry, and -1 if the terminfo database could not
be found. The emulation ignores the buffer pointer bp. 
*/

int	tgetflag (char *id);
/*
- The tgetflag routine gets the boolean entry for id, or zero if it is not available.
*/


int	tgetnum(char *id);
/*
- The tgetnum routine gets the numeric entry for id, or -1 if it is not available.
*/


char *tgetstr(char *id, char **area);
/*
- The tgetstr routine returns the string entry for id,
or zero if it is not available. Use tputs to output the
returned string. The return value will also be copied to
the buffer pointed to by area, and the area value will be
updated to point past the null ending this value. 
*/

char	*tgoto(const char *cap, int col, int row);
/*
-The tgoto routine instantiates the parameters into the given capability.
The output from this routine is to be passed to tputs. 
*/


int tputs(const char *str, int affcnt, int (*putc)(int));
/*
- The tputs routine is described on the curs_terminfo(3X) manual page.
It can retrieve capabilities by either termcap or terminfo name.
*/


/*
very bad trip
the hangover					very bad leaks
projet X
due date
date limite
supergrave/superbad
wedding crashers
search party

"Terminable"
"On redouble notre Terminal"
"Phase terminal"
"Terminal GNL"
"fissure_terminale"
""
*/



