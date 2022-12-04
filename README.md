BUT INFORMATIQUE - PARIS DESCARTES

# **Implémentation d’un besoin client**

Projet réalisé par Yohann PECH et Félix WANG du groupe 106 2022-2023


# **Présentation du projet :**

Cet SAE d’initiation au développement correspond à notre premier travail en groupe en rapport à la programmation, plus particulièrement sur le langage C. Il représente la finalisation des compétences acquises lors de ses six premières semaines de cours.

L’objectif du projet était de réaliser une application qui permettrait la conclusion d’un cycle universitaire d’un étudiant en BUT, à savoir si son année est validée ou non.
Pour ce faire, de nombreux critères devaient être respectés tels que la gestion des épreuves de différentes matières ou encore l’attribution de coefficients dans les différentes matières. 
Dans un environnement universitaire, il est nécessaire d’adopter des technologies de simplification afin de garder la gestion et l’organisation d’un effectif d’étudiants. C’est pourquoi le développement de cette application permettra de jouer un rôle dans cette voie. 

Cette application possède de nombreux points bénéfiques, atouts. Elle permet l'organisation d’un système universitaire en calculant la moyenne des notes pour un semestre d’un élève donné. Elle indique également les éventuelles erreurs d’entrées tels que l’oubli d’une note ou la non-existence d’un étudiant.
Des contraintes étaient également présentes ; des limitations d’effectifs à respecter, par exemple, la limite de matières établie à 10 ou un nombre d’UE entre 3 et 6. Au niveau des étapes, il fallait réaliser les commandes dans la continuité, dans l’ordre car il était impossible de passer à une commande sans faire celle qui la précède.

Les entrées de l’application doivent respecter des conditions qui permettront le bon fonctionnement de l’application. Ces critères rejoignent les contraintes exposées précédemment. Les entrées correspondent donc à une suite de caractères où le premier mot indique une commande précise, par exemple l’entrée de la chaîne caractère “note 2 Paul Architecture Interrogation 18” fera intervenir la commande nommée “note” qui ajoutera une note à l’étudiant “Paul” pour l’épreuve “Interrogation” de la matière “Architecture” du semestre “2”. 

Les sorties de l’application sont définies en fonction des entrées. Suivant les différentes commandes, l’application affichera un message qui validera ou pas le texte saisi de l’utilisateur. 


# **Organisation des tests**


Pour tester notre application, il nous a été fourni au total 8 jeux de tests, comprenant les fichiers d’entrées in-sp.txt et les fichiers de sortie out-sp.txt. Chaque sprint testait différentes fonctions de notre programme. Nous testions les entrées du programme avec les fichiers in-sp.txt. La validation d’un sprint nous permettait de passer au sprint suivant.

Chaque niveau de sprint comprenait deux fichiers : un fichier in-sp-base.txt qui contient les entrées qui permettront d’afficher les messages de base du programme, et un fichier in-sp-erreur.txt qui contient les entrées qui permettront d’afficher les messages d’erreur du programme. Les fichiers d’entrées s’accompagnent de fichiers de sorties pour chaque niveau, où encore une fois, deux types de fichiers sont présents : un fichier out-sp-base.txt et u fichier out-sp-erreur.txt.


# **Bilan de validations des tests de développement**

Après chaque fin de commande, nous testions notre programme avec les sprints ; en faisant cela, il nous a été permis par la suite de corriger nos erreurs.


+ Sprint 1: <br>
Pour le sprint 1, nous devions faire intervenir les commandes “formation”, "épreuve", “coefficient” et “exit”. La commande “formation” permet de déclarer une formation avec un nombre d’UE. Par la suite, en liaison à la formation, la commande “epreuve” permet de créer des matières, des épreuves ainsi que des coefficients. La commande “coefficient“ permet de vérifier si les coefficients rentrés par l’utilisateur respectent les contraintes, et la commande 
“exit” permet de mettre fin au programme. 

+ Sprint 2: <br>
Pour le sprint 2, il était obligé de valider le sprint 1 afin de poursuivre. Nous devions faire intervenir les commandes “note” et “notes”. La commande “note” permet d’ajouter une note dans une épreuve d’une matière à un étudiant qu’on ajoutera dans la formation. La commande “notes” permet de vérifier si les notes rentrées par l’utilisateur respectent les contraintes.

+ Sprint 3: <br>
Pour le sprint 3, il était obligé de valider le sprint 2 afin de poursuivre. Nous devions faire intervenir la commande “releve”. La commande “releve” permet de calculer les moyennes des matières du semestre indiqué par l’utilisateur et de les afficher.

+ Sprint 4:<br>
Pour le sprint 4, il était obligé de valider le sprint 3 afin de poursuivre. Nous devions faire intervenir la commande “decision”. Cette dernière permet d’afficher la moyenne des semestres et ainsi savoir quelles UEs sont validées. Par la suite, elle affiche le message qui indique le passage ou non.
Ainsi, les sprints demandés ont été validés avec succès ; nous avons utilisé les fonctionnalités du terminal Windows pour exécuter notre application, notamment avec les commandes ‘’fc /w’’ et ‘’fc'’ qui permet de comparer deux fichiers txt. Nous voulions être sûr que notre application soit fonctionnelle, c’est pourquoi nous avons développé notre propre jeu de test.


# <b>Notre jeu de test :</b>


fichier in-perso.txt <br>
```
epreuve 1 Informatique Interro 1 4 3 <br> 
formation 7 <br>
formation 3 <br>
formation 3 <br>
epreuve 3 Informatique Interro 2 2 0<br>
epreuve 1 Informatique Interro 1 4 0<br>
epreuve 1 SGBD DST 1 2 0<br>
epreuve 1 SGBD Ecrit 1 2 3<br>
epreuve 1 SGBD Oral 1 2 3<br>
epreuve 1 Systeme DST 1 2 3<br>
epreuve 1 Systeme Ecrit 1 2 3 <br>
epreuve 1 Systeme Oral 1 2 3<br>
epreuve 1 Programmation DST 1 2 0<br>
epreuve 1 Math DST 0 0 0<br>
epreuve 1 Math DST 1 2 3<br>
epreuve 1 Math Ecrit 1 2 3<br>
epreuve 2 Architecture DST 4 2 1<br>
epreuve 2 Architecture Ecrit 1 2 3<br>
epreuve 2 Anglais QCM 1 3 2<br>
coefficients 5<br>
coefficients 2<br>
coefficients 1<br>
epreuve 1 Programmation Ecrit 1 2 2<br>
coefficients 1<br>
note 8 Paul Programmation DST 14<br>
note 1 Paul Programmation Ecrit 24<br>
note 1 Paul Dessin Ecrit 12<br>
note 1 Paul Programmation Oral 14<br>
note 1 Paul Programmation Ecrit 12<br>
note 1 Paul Programmation Ecrit 12<br>
note 1 Paul SGBD DST 13<br>
note 1 Paul SGBD Ecrit 12<br>
note 1 Paul SGBD Oral 14<br>
note 1 Paul Systeme DST 16<br>
note 1 Paul Systeme Ecrit 12<br>
note 1 Paul Systeme Oral 12<br>
note 1 Paul Math Ecrit 13<br>
note 1 Paul Math DST 14<br>
note 2 Paul Architecture DST 12<br>
note 2 Paul Architecture Ecrit 14<br>
note 2 Paul Anglais QCM 18<br>
notes 3 Paul<br>
notes 1 Sylvie <br>
notes 1 Paul<br>
note 1 Paul Informatique Interro 13<br>
note 1 Paul Programmation DST 19<br>
notes 1 Paul <br>
releve 7 Paul<br>
releve 1 Sylvie<br>
epreuve 2 BDD Oral 1 2 0<br>
epreuve 2 BDD Ecrit 1 2 6<br>
coefficients 2<br>
note 2 Paul BDD Oral 13<br>
note 2 Paul BDD Ecrit 16<br>
notes 2 Paul<br>
releve 2 Paul<br>
decision Sylvie<br>
decision Paul<br>
epreuve 2 Gestion Oral 1 4 5<br>
epreuve 2 Gestion PPP 1 5 1<br>
note 2 Paul Gestion PPP 2<br>
notes 2 Paul<br>
note 2 Paul Gestion Oral 7<br>
releve 2 Paul<br>
decision Paul<br>
exit<br>
```
<b>fichier out-perso.txt:</b>
```
Le nombre d'UE n'est pas defini<br>
Le nombre d'UE est incorrect<br>
Le nombre d'UE est defini<br>
Le nombre d'UE est deja defini<br>
Le numero de semestre est incorrect
Matiere ajoutee a la formation
Epreuve ajoutee a la formation
Matiere ajoutee a la formation
Epreuve ajoutee a la formation
Epreuve ajoutee a la formation
Epreuve ajoutee a la formation
Matiere ajoutee a la formation
Epreuve ajoutee a la formation
Epreuve ajoutee a la formation
Epreuve ajoutee a la formation
Matiere ajoutee a la formation
Epreuve ajoutee a la formation
Au moins un des coefficients est incorrect
Matiere ajoutee a la formation
Epreuve ajoutee a la formation
Epreuve ajoutee a la formation
Epreuve ajoutee a la formation
Matiere ajoutee a la formation
Epreuve ajoutee a la formation
Epreuve ajoutee a la formation
Epreuve ajoutee a la formation
Matiere ajoutee a la formation
Epreuve ajoutee a la formation
Epreuve ajoutee a la formation
Epreuve ajoutee a la formation
Matiere ajoutee a la formation
Epreuve ajoutee a la formation
Epreuve ajoutee a la formation
Epreuve ajoutee a la formation
Le numero de semestre est incorrect
Coefficients corrects
Coefficients corrects
Epreuve ajoutee a la formation
Coefficients corrects
Le numero de semestre est incorrect
Note incorrecte
Matiere inconnue
Epreuve inconnue
Etudiant ajoute a la formation
Note ajoutee a l'etudiant
Une note est deja definie pour cet etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Le numero de semestre est incorrect
Etudiant inconnu
Il manque au moins une note pour cet etudiant
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Notes correctes
Le numero de semestre est incorrect
Etudiant inconnu
Matiere ajoutee a la formation
Epreuve ajoutee a la formation
Epreuve ajoutee a la formation
Coefficients corrects
Note ajoutee a l'etudiant
Note ajoutee a l'etudiant
Notes correctes
 UE1 UE2 UE3 
Architecture 13.3 14.6 15.4 
Anglais 12.6 13.4 12.0 
Com 12.0 12.0 12.0 
BDD 14.5 14.5 16.0 
--
Moyennes 13.0 13.5 13.6 
Etudiant inconnu
 UE1 UE2 UE3 
S1 13.7 13.6 13.3 
S2 13.0 13.5 13.6 
--
Moyennes annuelles 13.4 13.6 13.4 
Acquisition UE1, UE2, UE3
Devenir Passage
Matiere ajoutee a la formation
Epreuve ajoutee a la formation
Epreuve ajoutee a la formation
Note ajoutee a l'etudiant
Il manque au moins une note pour cet etudiant
Note ajoutee a l'etudiant
 UE1 UE2 UE3 
Architecture 13.3 14.6 15.4 
Anglais 12.6 13.4 12.0 
Com 12.0 12.0 12.0 
BDD 14.5 14.5 16.0 
Gestion 4.5 4.2 6.1 
--
Moyennes 12.0 10.9 12.3 
 UE1 UE2 UE3 
S1 13.7 13.6 13.3 
S2 12.0 10.9 12.3 
--
Moyennes annuelles 12.8 12.3 12.8 
Acquisition UE1, UE2, UE3
Devenir Passage
```


# **Bilan du projet**

Pour un premier projet, nous sommes satisfaits car nous avons finalisé et accompli tous les objectifs demandés. Nous avons rencontré des difficultés au niveau de la compréhension du sujet, notamment au début avec les structures et également au niveau de l’affichage des moyennes.

Mais nous avons su nous adapter, cette adaptation provient des cours en amphithéâtre, des travaux pratiques et dirigés dans lesquels certains exercices, exemples ainsi que les conseils et l’aide des enseignants permettaient une meilleure compréhension des énoncés.

De ce fait, le sujet a été approprié et par conséquent a pu nous apporter énormément d'idées que nous avons par la suite intégré au code, par exemple la création d’une commande ‘’help’’ qui indique la chaine de caractères à renseigner en cas d’erreur 
d’entrée.
