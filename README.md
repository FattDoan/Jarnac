# Projet-Jarnac

Le but de ce projet est de développer en binôme une application pour permettre à une ou deux personnes positionnées devant le même ordinateur de jouer à JARNAC sans matériel physique de jeu, en utilisant le dictionnaire de noms communs fourni dans le fichier.

## Installation

#### Télécharger les fichiers sources

Vous pouvez soit télécharger directement depuis Gitlab, soit cloner le dépôt.

- **Télécharger directement depuis gitlab**
  
  Cliquez sur la flèche vers le bas en haut à droite. Téléchargez le fichier zip et l'extrayez.

- **Cloner le dépôt et naviguer vers le répertoire**

```bash
git clone https://gitlab.dsi.universite-paris-saclay.fr/thanh-phat_doan_travo/Info111/2023-2024/Projet-Jarnac.git
cd Projet-Jarnac
```

#### Lancer l'exécutable

Double-cliquez sur le fichier "JeuJarnac" et le programme démarrera en mode texte dans votre terminal.

> **Si votre système ne vous permet pas d'ouvrir l'exécutable, vous devrez recompiler le programme et l'exécuter directement sur le terminal.**
> 
> **Il s'agit d'un bogue connu. Nous y travaillons.**

#### Compiler le programme

D'abord, assurez-vous que vous êtes dans le bon répertoire.

Pour vérifier, tapez sur ton terminal:

```bash
pwd
```

Si à la fin de la ligne de sortie se trouve **Projet-Jarnac**, c'est bon.

Pour compiler le programme, tapez :

```bash
./build.sh
```

Si le processus de compilation réussit, appuyez sur la touche Entrée et vous entrerez directement dans le jeu.

Si ce n'est pas le cas, tapez:

```bash
rm -rf build
```

Cette commande supprimera le dossier "build" actuel, ce qui pourrait entraîner des conflits. 

Ensuite, exécutez à nouveau la commande de compiler `./build.sh` et cela devrait fonctionner.

#### Exécuter le jeu

Si le jeu ne s’est pas lancé après l’exécution de `./build.sh`, tapez sur ton terminal :

```bash
./JeuJarnac
```

#### Activer l'exécutable de test (usage réservé aux développeurs)

Pour compiler le fichier **.cpp** de test dans le dossier "**tests**", tapez :

```bash
./build.sh -t
```

Pour l'exécuter, tapez :

```bash
./Test
```

## Utilisation

L’utilisateur est libre de développer le jeu à sa guise.

## Structure du Projet

- Le répertoire source src contient 6 fichiers **.cpp**, coeur du programme.

- Le répertoire include contient les documentations des fonctions au format **.hpp**.

- Le répertoire docs contient un tutoriel du jeu au format **.txt**.

- Le répertoire dictionnaire contient les dictionnaires dans différentes langues au format **.txt**.

## Auteurs

**Alexis VO**

**Thanh Phat Doan**
