# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Machines à états finis logicielles
+ Section #  : 2
+ Équipe #   : 35
+ Correcteur : Tristan Rioux

# LISIBILITÉ
## En-têtes en début de programme   

| Pénalité par erreur                          | -1.5       |
| -------------------------------------------- | ---------- |
| Noms des auteurs                             |            |
| Description du programme                     |            |
| Identifications matérielles (Broches I/O)    |            |
| Table des états ou autres s'il y a lieu      |            |
| __Résultat partiel__                         | __(1.5/1.5)__ |

## Identificateurs significatifs (Autodocumentation)

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de *chiffres magiques*               | (0.5/0.5)     |
| Noms de variables décrivent l'intention      | (0.5/0.5)     |
| Noms de fonctions décrivent l'intention      | (0.5/0.5)     |
| __Résultat partiel__                         | __(1.5/1.5)__ |

## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme 
 + Procédure peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'Internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| __Résultat partiel__                         | __(1.0/1.0)__ |


## Indentation   

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Indentation structurée                       | (0.0/0.5)     |
| Indentation uniforme dans le programme       | (0.5/0.5)     |
| __Résultat partiel__                         | __(0.5/1.0)__ |


# MODULARITÉ ET COMPRÉHENSION
## Fonctions bien définies

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Responsabilité unique d'une fonction         |            |
| Maximum de 4 paramètres                      |            |
| Absence de code dupliqué                     |            |
| etc                                          |            |
| __Résultat partiel__                         | __(0.0/1.0)__ |


## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0       |
| -------------------------------------------- | ---------- |
| Utilisation appropriée des registres         |            |
| Machine à états codée clairement             |            |
| Délais et minuteries utilisés judicieusement |            |
| PWM bien établi                              |            |
| Scrutation et interruptions bien utilisées   |            |
| etc                                          |            |
| __Résultat partiel__                         | __(2.0/4.0)__ |

# FONCTIONNALITÉS
## Git

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Fichiers aux bons endroits                   | (1.5/1.5)     |
| Absence de fichiers inutiles                 | (1.5/1.5)     |
| __Résultat partiel__                         | __(3.0/3.0)__ |


## Compilation    

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de messages d'erreurs de compilation | (1.5/1.5)     |
| Absence de messages d'attention (*warning*)  | (0.5/0.5)     |
| __Résultat partiel__                         | __(2.0/2.0)__ |
   

## Évaluation boîte noire  

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Cas normal de fonctionnement                 | (2.5/2.5)     |
| Cas limites observables                      | (2.5/2.5)     |
| __Résultat partiel__                         | __(5.0/5.0)__ |

# Résultat

__Total des points: 16.5/20__

# Commentaires du correcteur:

- Les enum devraient être défini dans le scope global. Je n'ai pas enlevé de
  points.

Voici les endroits où j'ai enlevé des points:
- Mauvaise indentation après les cases des switch cases.
- Fonction `buttonIsPressed` de type `if true return true else return false` inutile.
- Duplication de code pour le debounced
- Fonction `makeDelAmber` avec plusieurs responsabilités (regarde le bouton et
  change la couleur).
- Bitshift incorrect pour `DEL_OFF` (utilisation du `|` au lieu du `&`)
- Machine à états mal défini (test d'entrée à 2 endroits, plusieurs sorties dans
  un même état).



# Basé sur le commit suivant
```
commit 57b0fa892e79614f60ca420196d6cc3c1c40d71f
Author: ¨Astir <¨astir.tadrous@polymtl.ca¨>
Date:   Fri Sep 16 12:38:58 2022 -0400

    added tp3 with pb 2 not working
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp2/pb1`
```
make: Entering directory '/home/tristan/Documents/Poly/inf1900/inf1900-grader-A2022/correction_tp2/35/tp/tp2/pb1'
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c pb1.cpp
avr-gcc -Wl,-Map,pb1.elf.map -mmcu=atmega324pa -o pb1.elf  pb1.o \
-lm 
avr-objcopy -j .text -j .data \
	-O ihex pb1.elf pb1.hex
make: Leaving directory '/home/tristan/Documents/Poly/inf1900/inf1900-grader-A2022/correction_tp2/35/tp/tp2/pb1'

```

## Sortie de `make` dans `tp/tp2/pb2`
```
make: Entering directory '/home/tristan/Documents/Poly/inf1900/inf1900-grader-A2022/correction_tp2/35/tp/tp2/pb2'
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c pb2.cpp
avr-gcc -Wl,-Map,pb2.elf.map -mmcu=atmega324pa -o pb2.elf  pb2.o \
-lm 
avr-objcopy -j .text -j .data \
	-O ihex pb2.elf pb2.hex
make: Leaving directory '/home/tristan/Documents/Poly/inf1900/inf1900-grader-A2022/correction_tp2/35/tp/tp2/pb2'

```
