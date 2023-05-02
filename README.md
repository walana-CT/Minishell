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

 1. Supprimer ce qui suit apres une dièse

```
les jeunes sont accros au réseaux et n'ont aucun recul sur les informations
 qu'ils voient #pauvrefrance #decadence 
```

va donner
```
les jeunes sont accros au réseaux et n'ont aucun recul sur les informations
qu'ils voient
```


 2. Interpréter les dollards

```
var1=oignon
var2=fi
var3=Vars
var4=coll
salade tomate $var1 'j'ai la $var2 icelle' "j'habite dans le $var3" il est un peu $var4ant
```
va donner
```
salade tomate oignon 'j'ai la $var2 icelle' "j'habite dans le Vars" il est un peu 
```

les dollard point d'interrogation.


