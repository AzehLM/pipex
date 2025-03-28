# Pipex

*This project will let you discover in detail a UNIX mechanism that you already know
by using it in your program.*

---

# Ressources pour le projet Pipex (42)

### Table des matières
1. [Références YouTube](#références-youtube)
2. [Autres références](#autres-références)
3. [Outils interactifs](#outils-interactifs)
4. [Ressources spécifiques au projet Pipex](#ressources-spécifiques-au-projet-pipex)
5. [Le type pid_t](#le-type-pid_t)
6. [Fonctions dup() et dup2()](#fonctions-dup-et-dup2)
7. [Fonction access()](#fonction-access)
8. [Fonction execve()](#fonction-execve)
9. [Comprendre l'image d'un processus](#comprendre-limage-dun-processus)
10. [Pipe et pourquoi close les fds](#pipe-et-pourquoi-close-les-fds)
11. [Fonction fork()](#fonction-fork)
12. [Fonction wait() et wait(pid)](#fonction-wait-et-waitpid)
13. [Pièges à éviter](#pièges-à-éviter)
14. [Check leak](#check-leak)
15. [Autres ressources](#autres-ressources)
16. [Infodump](#infodump)

---

## References YouTube
- [CodeVault Playlist (Notions importantes pour le projet et plus)](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)
- [Autre vidéo sur les pipelines](https://www.youtube.com/watch?v=QD9YKSg3wCc&list=PLK4FY1IoDcHG-jUt93Cl7n7XLQDZ0q7Tv)

## Autres références

[Understanding command execution and input/output data flow](https://www.rozmichelle.com/pipes-forks-dups/)

##### Codequoi:
- [La méthode `pipe` pour la communication inter-processus](https://www.codequoi.com/pipe-une-methode-de-communication-inter-processus/)
- [Gestion des erreurs en C avec `errno`](https://www.codequoi.com/errno-et-la-gestion-derreur-en-c/)
- [Création et gestion des processus fils en C](https://www.codequoi.com/creer-et-tuer-des-processus-fils-en-c/)

## Outils interactifs

[Explainshell : explication des commandes shell](https://explainshell.com/explain?cmd=cat+%7C+cat+%7C+ls)

---

## Ressources spécifiques au projet Pipex
L'objectif est de comprendre les processus dans leur ensemble et non seulement pour le rendu du projet. Toutefois, les explications des fonctions autorisées peuvent aider à la recherche de notions externes au projet.

- [CSNotes : Tutoriel sur Pipex](https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901)
- [Reactive : Guide complet pour Pipex](https://reactive.so/post/42-a-comprehensive-guide-to-pipex/)
- [Medium : Comprendre les pipelines en C avec Pipex](https://medium.com/@omimouni33/pipex-the-42-project-understanding-pipelines-in-c-71984b3f2103)
- [Medium : Pipex 42 - Chapitre 1](https://medium.com/@lannur-s/pipex-42-chapter-1-metamorphosis-execve-1a4710ab8cb1)

### Partie bonus (heredoc)
- [Documentation sur Bash heredoc](https://linuxize.com/post/bash-heredoc/)
- [Phoenixnap : Guide sur Bash heredoc](https://phoenixnap.com/kb/bash-heredoc)

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
- Le **segment de texte** : zone mémoire ou est le **code exécutable** est stocké
  - Il contient les inscructions machines lues à partir du fichier binaire.
  - Ce segment est en **lecture seule** pour empêcher les modifications accidentelles ou malveillantes du code.
- Les **segments de données** :
  - Statique : Variables globales, constantes...
  - Dynamique (heap) : Mémoire allouée dynamiquement avec `malloc()`, etc.
- La **pile** (stack) : Utilisée pour les appels de fonctions, les variables locales, etc.
- Les **descripteurs de fichiers** : Informations sur les fichiers ouverts.
- Le **contexte d'exécution** : Registres du CPU, pointeur d'instruction (adresse de la prochaine instruction à exécuter), pointeur de pile (indique le sommet de la pile).

### Ce qui se passe lorsque `execve()` est appelé :
- L'ancienne image du processus est remplacée par la nouvelle image (à partir du fichier binaire du programme spécifié).
- Le PID reste inchangé, mais l'image du processus (le programme) est mise à jour.
- `execve()` permet d'exécuter un autre programme dans le même processus, tout en conservant certaines ressources (si configurées pour persister).

---

## Pipe et pourquoi close les fds
`pipe()`
- [Manpage `pipe()`](https://linux.die.net/man/2/pipe)
- La fonction `pipe()` crée un pipeline (buffer, voir suite) de communication unidirectionnel entre processus.
#### Data flow : `write end -> buffer -> read end`

#### Pourquoi fermer tous les fd ?
- Fuites de ressources
- Comportement inattendu des pipes (blocage dans les pipe)

Chaque fois qu'un pipe est créé avec la fonction `pipe(fd)`, il ouvre deux fd:
- `fd[0]` pour la lecture (read end)
- `fd[1]` pour l'écriture (write end)

Si ces descripteurs ne sont pas fermés:
- Ils restent ouverts dans le processus et consomment une ressource système
- Avec plusieurs pipelines, on peut attendre la limite maximale du nombre de fd ouverts par un processus (entrainant `EMFILE` (``"Too many open files"``))

#### Un `pipe` est un canal de communication entre deux processus:
- Si un processus tente de lire un pipe, mais aucun autre processus n'écrit dans ce pipe (car `fd[1]` est ouvert), le processus lecteur peut se bloquer en attente de donnée
- Un processus écrivant dans un pipe peut se bloquer si le lecteur ne lit pas les données et que le buffer du pipe est plein.

### Buffer d'un pipe
Le buffer d'un pipe est une zone de mémoire temporaire qui sert à stocker les données en transit entre le processus qui écrit et le processus qui lit.
Quelques spécificités de ce buffer:
- A une taille limite (64KB (``65536 bytes``))
- En réalité selon l'OS: taille définit par `PIPE_BUF` (`<limits.h>`)
#### Ce comporte de telle manière:
Quand le buffer est plein:
- Le `write()` se bloque en attendant qu'il y ait de la place
- Ou renvoie une erreur si le pipe est non-bloquant (`O_NONBLOCK`)
Quand le buffer est vide:
- Le `read()` se bloque en attendant des données
- Ou renvoie -1 si le write end (`fd[1]`)est fermé

---

## Fonction `fork()`

### `fork()`
- [Manpage `dup()`](https://linux.die.net/man/2/fork)
- La fonction `fork()` est utilisée pour créer un nouveau processus, appelé processus enfant, en dupliquant le processus parent.
#### Comportement:
- Après l'appel à `fork()`m deux processus existent: le parent et l'enfant.
- Dans le processus parent, `fork()` retourne le `pid` du processus enfant.
- Dans le processus enfant, `fork()` retourne 0.
- Si `fork()` échoue, la fonction retourne -1 et aucun processus n'est créé. `errno` est défini et indique l'erreur.

Pour `pipex`, `fork()` est utilisé pour créer les processus enfant en charge d'exécuter les commande via `execve()`.

---

## Fonction `wait()` et `waitpid()`
- Ces fonctions permettent au processus parent d'attendre la terminaise d'un ou plusieurs processus enfants.
- Après un `fork()`, le parent peut utiliser l'une de ces deux fonciton pour attendre la fin de ses enfants.
- Cela permet de synchroniser correctement les étapes du pipeline et de récupere les codes de sorties des commandes exécutées.

---

### Pieges a eviter
#### Utilisation successive de sleep :
- `./pipex infile "sleep 5" "sleep 3" outfile `

**On pourrait s'attendre a ce que le programme sorte apres avoir executer les deux sleep l'un apres l'autre. Cependant `fork` ne fonctionne pas de cette facon, tous les processus s'execute en meme temps.**

Ici notre programme doit sortir apres 5 secondes. (cela aurait aussi ete le cas avec `./pipex infile "sleep 3" "sleep 5" outfile`)

Il y en a d'autres, je vous laisserai les découvrir par vous meme. Je recommande grandement de faire joujou avec : [Outils interactifs](#outils-interactifs).

---

## Check leak

Etant donner la nature du projet, une mauvaise utilisation de `valgrind` ou de `fsanitize` ralentirai la detection de leaks.

### Solution

Plusieurs options:
- avec `valgrind` : utiliser les options `--leak-check=full --trace-children=yes --track-origins=yes` en compilant avec `-g3`
- avec `fsanitize` : compiler avec `-g -fsanitize=address`

Neanmoins, l'utilisation d'`execve` pertube la detection de leaks puisque les images des processus sont redefinis.
Pour débuguer correctement, voici les options que j'ai utilisé avec valgrind :
- `--leak-check=full --show-leak-kinds=all --track-origins=yes --show-mismatched-frees=yes --track-fds=yes --trace-children=yes`
---

### List symbols from object files **`nm`** (`nm -u`)
Option `-u` utile pour voir la liste des symboles.
- GNU extension affiche une seule fois chaque symbole de chaque type en cours d'utilisation


 ---
## Infodump

 [Tutoriel sur les compilateurs](https://ruslanspivak.com/lsbasi-part1/)
