# IP Catalogue

## Introduction

**IP Catalogue** est une application console qui permet de cataloguer des adresses IP (IPv4). Il offre plusieurs fonctionnalités clés, notamment le stockage persistant des adresses IP, la possibilité de filtrer les adresses en fonction d’un masque, l’affichage des adresses IP sous différentes formes (binaire, hexadécimal, décimal), et la validation des entrées d’adresses IP pour garantir leur conformité.

## Fonctionnalités

### 1) Persistance
Le programme stocke les adresses IP de manière permanente, ce qui signifie que les adresses IP ajoutées sont sauvegardées entre les différentes exécutions du programme.De cette façon, l’utilisateur peut construire et maintenir un catalogue d’adresses IP au fil du temps.

### 2) Filtrage par masque
Le programme permet a utilisateur de filtrer les adresses IP en fonction d'un masque spécifié. L'utilisateur fournit une adresse IP et un masque, puis le programme renvoie les adresses IP stockées avec le meme masque.

### 3) Binaire/hexadécimal/décimal
Les adresses IP peuvent être affichées en binaire, en hexadécimal et en décimal. Cette fonctionnalité permet à l'utilisateur d'afficher les adresses IP de manière appropriée.



### 4) Validation
Une validation rigoureuse est mise en place pour s'assurer que seules les adresses IP authentiques sont autorisées. Les caractères non autorisés, les valeurs numériques qui ne sont pas dans la plage valide (0-255), les segments manquants ou les points d'adresse mal positionnés sont des exemples d'entrées invalides.

Exemples d'entrées invalides :
- `afs.213.sf.23ew`
- `300.192.1.2`
- `-12.23.12.23`
- `172.45.223..1`

## Boucle principale

Le programme ne se ferme pas sans que l'utilisateur le demande explicitement car il fonctionne comme un menu interactif. Les options suivantes sont disponibles via le menu :
- **a** - Ajouter une nouvelle adresse IP
- **l** - Liste des adresses IP
- **s** - Rechercher des adresses similaires par masque
- **d** - Supprimer une adresse IP
- **q** - Quitter



Exemple d'interaction :

a - Add a new IP address.
l - List IP addresses.
s - Search similar by mask.
d - Delete an IP.
q - quit.

Please choose one : a

Enter IP Address :  192.168.1.1
Enter Mask Address : 255.255.0.0

The IP Address :  192.168.1.1 and The Mask : 255.255.0.0 are added successfully!

Le programme continue à interagir avec l'utilisateur tant qu'il ne choisit pas l'option de quitter (**q**).


## Comment exécuter le programme

Si vous n'avez pas gcc ou vous êtes sur un environnement autre que unix etc...
Installer [docker](https://docs.docker.com/) et suivez les 2,3
1. Clonez le dépôt du projet.
2. générer l'image à partir du Dockerfile : docker build -t c-img .
3. lancer le conteneur docker : docker run -ti -v $(pwd):/IP_Catalogue
4. Compiler le programme main.c gcc main.c
5. Exécuter le fichier a.out
6. Suivez les instructions du menu interactif pour utiliser les fonctionnalités offertes par l'appplication.

## Remarques
Assurez-vous que vous disposez des autorisations nécessaires pour conserver les données sur le système de fichiers  pour sauvegarder les adresses IP entre les sessions du programme.