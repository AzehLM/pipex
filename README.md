# Ressources pour le projet Pipex (42)

## References YouTube
- [CodeVault Playlist (Notions importantes pour le projet et plus)](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)
- [Autre vidéo sur les pipelines](https://www.youtube.com/watch?v=QD9YKSg3wCc&list=PLK4FY1IoDcHG-jUt93Cl7n7XLQDZ0q7Tv)

## Ressources globales C

[Documentation C devdocs](https://devdocs.io/c/)
##### Codequoi:
- [La méthode `pipe` pour la communication inter-processus](https://www.codequoi.com/pipe-une-methode-de-communication-inter-processus/)
- [Gestion des erreurs en C avec `errno`](https://www.codequoi.com/errno-et-la-gestion-derreur-en-c/)
- [Création et gestion des processus fils en C](https://www.codequoi.com/creer-et-tuer-des-processus-fils-en-c/)

## Outils interactifs
- [Explainshell : explication des commandes shell](https://explainshell.com/explain?cmd=cat+%7C+cat+%7C+ls)

---

## Ressources spécifiques au projet Pipex
### A regarder en dernier
L'objectif est de comprendre les processus dans leur ensemble et non seulement pour le rendu du projet 42. Toutefois, les explications des fonctions autorisées peuvent aider à la recherche de notions externes au projet.

- [Reactive : Guide complet pour Pipex](https://reactive.so/post/42-a-comprehensive-guide-to-pipex/)
- [CSNotes : Tutoriel sur Pipex](https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901)
- [Medium : Comprendre les pipelines en C avec Pipex](https://medium.com/@omimouni33/pipex-the-42-project-understanding-pipelines-in-c-71984b3f2103)
- [Medium : Pipex 42 - Chapitre 1](https://medium.com/@lannur-s/pipex-42-chapter-1-metamorphosis-execve-1a4710ab8cb1)

### Partie bonus (Heredoc)
- [Documentation sur Bash Heredoc](https://linuxize.com/post/bash-heredoc/)
- [Phoenixnap : Guide sur Bash Heredoc](https://phoenixnap.com/kb/bash-heredoc)

---

## Le type `pid_t`

`pid_t` est un type de donnée utilisé pour représenter les ID de processus. C'est un entier signé, garantissant une portabilité entre les systèmes UNIX, peu importe la taille réelle du PID.

### Utilité :
- Retour des fonctions `fork()` et `getpid()`
- Stockage des PID des processus parents/enfants
- Argument pour les fonctions `waitpid()` et `kill()`

#### Sources :
- [POSIX : sys/types.h](https://pubs.opengroup.org/onlinepubs/009695399/basedefs/sys/types.h.html)
- [StackOverflow : Différence entre unistd.h et sys/types.h](https://stackoverflow.com/questions/29984328/difference-between-unistd-h-and-sys-types-h-in-linux)
- [POSIX : unistd.h](https://pubs.opengroup.org/onlinepubs/7908799/xsh/unistd.h.html)
- [POSIX : tcgetpgrp](https://pubs.opengroup.org/onlinepubs/7908799/xsh/tcgetpgrp.html)


---
## Fonctions `dup()` et `dup2()`

### `dup()`
- [Manpage `dup()`](https://linux.die.net/man/2/dup)
- Crée une copie du descripteur de fichier `oldfd` sur le plus petit numéro de fichier disponible. Retourne le nouveau descripteur de fichier.

### `dup2()`
- [Manpage `dup2()`](https://linux.die.net/man/2/dup2)
- Force la copie de `oldfd` vers `newfd` et ferme `newfd` s'il existe déjà. Plus précis car il permet de contrôler le descripteur de fichier de destination.

#### Différences principales :
- `dup2()` permet de spécifier un descripteur de fichier exact (`newfd`), tandis que `dup()` choisit automatiquement.
- `dup2()` est préférable pour Pipex, car il permet de contrôler les redirections des entrées/sorties (`STDIN_FILENO` ou `STDOUT_FILENO`).

#### Analogie :
- `dup()` est comme avoir une seule clé pour une serrure, alors que `dup2()` permet d'avoir deux clés (lorsque l'on en jete une, on peut toujours utiliser la deuxième).

---

## Fonction `access()`

- [Manpage `access()`](https://linux.die.net/man/2/access)
- Vérifie si un processus a les permissions d'accès à un fichier ou répertoire. Retourne `0` si OK, `-1` si erreur.

### Modes principaux :
- `F_OK`: Vérifie l'existence du fichier
- `R_OK`: Permission de lecture
- `W_OK`: Permission d'écriture
- `X_OK`: Permission d'exécution

---

## Fonction `execve()`

`execve(pathname, av, env)`

- Remplace l'image du processus courant par un nouveau programme spécifié par le chemin `pathname`. L'exécution du programme commence à partir de son point d'entrée.

### `NULL` dans les paramètres `env` :
- Vous pouvez passer `NULL` dans `env` pour exécuter un programme dans un processus enfant.

---

## Comprendre l'image d'un processus

Lorsqu'un processus est exécuté par l'OS, il possède une "image" en mémoire. Cette image comprend :
- Le **code exécutable** : les instructions lues à partir du fichier binaire.
- Les **segments de données** :
  - Statique : Variables globales, constantes...
  - Dynamique (heap) : Mémoire allouée dynamiquement avec `malloc()`, etc.
- La **pile** (stack) : Utilisée pour les appels de fonctions, les variables locales, etc.
- Les **descripteurs de fichiers** : Informations sur les fichiers ouverts.
- Le **contexte d'exécution** : Registres du CPU, pointeur d'instruction, etc.

### Ce qui se passe lorsque `execve()` est appelé :
- L'ancienne image du processus est remplacée par la nouvelle image (à partir du fichier binaire du programme spécifié).
- Le PID reste inchangé, mais l'image du processus (le programme) est mise à jour.
- `execve()` permet d'exécuter un autre programme dans le même processus, tout en conservant certaines ressources (si configurées pour persister).

---
### Pieges a eviter
#### Utilisation successive de sleep :
- `./pipex infile "sleep 5" "sleep 4" outfile `
  
##### On pourrait s'attendre a ce que le programme sorte apres avoir executer les deux sleep l'un apres l'autre. Cependant `fork` ne fonctionne pas de cette facon, tous les processus s'execute en meme temps.

Ici notre programme doit sortir apres 5 secondes. (cela aurait aussi ete le cas avec `./pipex infile "sleep 3" "sleep 5" outfile`)

#### Commandes vides
- `./pipex infile "" " " outfile`


Risque de segfault dans les process si ce cas n'est pas geré, `execve` est probablement la source du probleme.
Solution : check isspace jusqu'a ce qu'on tombe sur un autre charactère, a partir de la nos fonctions `get_path` et `exec` prennent le relai. 

---

## Check leak

Etant donner la nature du projet, une mauvaise utilisation de `valgrind` ou de `fsanitize` ralentirai la detection de leaks. 

### Solution

Plusieurs options:
- avec `valgrind` : utiliser les options `--leak-check=full --trace-children=yes --track-origins=yes` en compilant avec `-g3`
- avec `fsanitize` : compiler avec `-g -fsanitize=address`

Neanmoins, l'utilisation d'`execve` pertube la detection de leaks puisque les images des processus sont redefinis.
Bien penser a mettre en commentaire les parties ou `execve` est utilisé.

---
## Minishell

### Qu'est-ce que Minishell ?
- [Vidéo YouTube : Introduction à Minishell](https://www.youtube.com/watch?v=yTR00r8vBH8)
- [Documentation sur la création d'un shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [Architecture de Minishell](https://whimsical.com/minishell-architecture-big-picture-7b9N8PL3qHrddbs977mQ2J)

### Quelques rendus avec erreurs :
- [Rendu de Minishell avec erreurs (Push invalidés)](https://projects.intra.42.fr/1331/aascedu)
- [Autre rendu avec erreurs](https://projects.intra.42.fr/projects/42cursus-minishell/projects_users/3658701)
- [Encore un autre rendu](https://projects.intra.42.fr/projects/42cursus-minishell/projects_users/3676106)

---

## Autres ressources

### Garbage Collector
Pas sûr si c'est nécessaire pour le projet, mais voici quelques ressources :
- [Écrire un simple Garbage Collector en C](https://maplant.com/2020-04-25-Writing-a-Simple-Garbage-Collector-in-C.html)
- [BDWGC : Garbage Collector pour C](https://github.com/ivmai/bdwgc)

--- 

### List symbols from object files `nm`
Option `-u` utile pour voir la liste des symboles.
- GNU extension affiche une seule fois chaque symbole de chaque type en cours d'utilisation

 
 ---
## Infodump

Récupérer la valeur du bon enfant avec `waitpid`

 [Tutoriel sur les compilateurs](https://ruslanspivak.com/lsbasi-part1/)

##### Norme ANSI
- [Guide des règles de programmation sécurisées en C (ANSSI)](https://cyber.gouv.fr/sites/default/files/2020/07/anssi-guide-regles_de_programmation_pour_le_developpement_securise_de_logiciels_en_langage_c-v1.4.pdf)


---

# TO DO

WIFEXITED explained

