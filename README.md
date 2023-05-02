# Minishell

Gros problèmes.

## Parsing

### vérifier qu'il n'y a pas d'erreur

 1. vérifier que les quotes et simple quotes sont bien fermés 
 ``` 
 al"l"o 'alh'u"il"e 
 ```    Bien
 ``` 
 al'lo "alhu'il"e 
 ```    Pas bien

### Interpréter les caractères spéciaux

 1. Supprimer ce qui suit apres une dièse /!\ uniquement quand # est le premier caractere d'un mot

```
les jeunes sont accros au réseaux et n'ont aucun recul sur les informations
 qu'ils voient #pauvrefrance #decadence 
```

va donner
```
les jeunes sont accros au réseaux et n'ont aucun recul sur les informations
qu'ils voient
```

2. Split | 

Attention ce premier split ne supprime pas les quotes. Il split t_line.line sur le caractere |, compte le nb de commandes, malloc t_cmd et remplit t_cmd[i].line avec le retour de split
Desormais on ne devrait plus avoir qu'a travailler sur t_cmd[i].line

 3. a. Interpréter les dollars

```
var1=oignon
var2=fi
var3=Var
var4=coll
salade tomate $var1 'j'ai la $var2 icelle' "j'habite dans le $var3" il est un peu $var4ant
```
va donner
```
salade tomate oignon 'j'ai la $var2 icelle' "j'habite dans le Vars" il est un peu 
```

les dollard point d'interrogation.
``` salade tomate oignon 'j'ai la $var2 icelle' "j'habite dans le Var" il est un peu ```

3. b. Gerer les redirections ( < << >> >)
chaque fois qu'on tombe sur une redirection > ou >>, on crée le fichier cible, on modifie le fdout et on detruit ou ignore la redirection dans t_cmd.line

3. c Splitter avec espace (+trim ??)
Sauf entre les quotes, et les quotes doivent rester dans les bouts de string finaux (ca doit pas split quand " ou ' sinon 'e''c''h''o' ne marche pas). Remplir les champs de t_cmd avec le char** qui sort de split
echo" pouet" -> command not found: echo pouet

4. fork + execve ou builtin