/*
Nom ......... : s1-01.c
Role ........ : Interpreteur de commande permettant de gerer une formation universitaire
Auteur ...... : Yohann PECH / Felix WANG
Version ..... : V1.0 du 01/10/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#pragma warning (disable : 4996)

enum {
  NB_SEMESTRES = 2,
  MIN_UE = 3,
  MAX_UE = 6,
  MAX_MATIERES = 10,
  MAX_EPREUVES = 5,
  MAX_ETUDIANTS = 100,
  MAX_CHAR = 30,
  MAX_CHAR_CLAVIER = 120
};

const float MIN_NOTE = 0., MAX_NOTE = 20.;
#define CHAINE_VIDE "\0"
const int MIN_SEMESTRE = 1, MAX_SEMESTRE = 2;
const float NoteNonDefinie = -1.;
const float NoteMoyenne = 10.;

typedef char Nom[MAX_CHAR];

typedef struct {
  Nom nomMatiere; // Nom de la matière
  float note; // Moyenne de la matière
  unsigned int UE; // UE corespondant
}Moyenne;

typedef struct {
  Nom nomMatiere; // Nom de la matière
  Nom nomEpreuve; // Nom de l'épreuve
  unsigned int NumeroSemestre; // Numéro du semestre
  float note; // Note obtenu
}Note;

typedef struct {
  Nom PrenomEtudiant; // Nom de l'étudiant
  Note notes[MAX_MATIERES * MAX_EPREUVES * NB_SEMESTRES]; // Tableau de notes de l'étudiant
  int nbNotes; // Nombre de notes de l'étudiant
  float MoyenneSemestre1[MAX_UE]; // Moyennes du premier Semestre
  float MoyenneSemestre2[MAX_UE]; // Moyennes du deuxième Semestre
  float MoyennesAnnuelles[MAX_UE]; // Moyennes annuelle
}Etudiant;

typedef struct {
  Nom nom; // Nom de l'épreuve
  float coef[MAX_UE]; // Coefficents de l'épreuve par rapport aux nombre
  // d'unité d'enseignement
}Epreuve;

typedef struct {
  Nom nom; // Nom de la matière
  unsigned int nbEpreuves; // Nombre d'épreuves de la matière
  Epreuve epreuves[MAX_EPREUVES]; // Tableau d'épreuves de la matière
}Matiere;

typedef struct {
  unsigned int nbMatieres; // Nombre de matières du semestre
  Matiere matieres[MAX_MATIERES]; // Tableau de matières du semestre
}Semestre;

typedef struct {
  unsigned int nbUE; // Nombre d'UE par formation
  unsigned int nbEtudiants; // Nombre d'etudiants dans la formation
  Semestre semestres[NB_SEMESTRES]; // Tableau semestres
  Etudiant etudiants[MAX_ETUDIANTS]; // Tableau d'étudiants
}Formation;

//Prototypes des fonctions
void formation(Formation* inOutF);
void epreuve(Formation* inOutF);
void coefficients(Formation* InOutF);
void note(Formation* inOutF);
void notes(Formation* inOutF);
void releve(Formation* inOutF);
void decision(Formation* InOutF);
int exitcommand();
void Initialisationformation(Formation* InOutF);
void help();

int main() {
  char nomcommande[MAX_CHAR_CLAVIER] = "";
  Formation maformation;
  Initialisationformation(&maformation);
  do {
    scanf("%s", &nomcommande);
    if (strcmp(nomcommande, "formation") == 0)
      formation(&maformation);
    else if (strcmp(nomcommande, "epreuve") == 0)
      epreuve(&maformation);
    else if (strcmp(nomcommande, "coefficients") == 0) 
      coefficients(&maformation);
    else if (strcmp(nomcommande, "note") == 0)
      note(&maformation);
    else if (strcmp(nomcommande, "notes") == 0)
      notes(&maformation);
    else if (strcmp(nomcommande, "releve") == 0)
      releve(&maformation);
    else if (strcmp(nomcommande, "decision") == 0)
      decision(&maformation);
    else if (strcmp(nomcommande, "help") == 0 ||
      strcmp(nomcommande, "?") == 0) {
      help();
    }
    else if (strcmp(nomcommande, "exit") != 0) {
      printf("Commande incorrect ou inconnu\n");
      help();
    }
  } while (strcmp(nomcommande, "exit") != 0);
  exitcommand();
}

/* help, la commande permet d'afficher les aides nécessaires pour toutes
*        les commandes disponibles avec les différents arguments.
*        La commande est appelée quand l'utilisateur rentre au clavier 'help', '?' ou
*        une commande inconnue.
*/
void help() {
  printf("****************************************************************\n");
  printf("**\n");
  printf("** 'formation'    suivie du nombre d'UE la composant\n");
  printf("**\n");
  printf("** 'epreuve'      suivie du numero de semestre,\n");
  printf("**                du nom de la matière,\n");
  printf("**                du nom de l'épreuve,\n");
  printf("**                d'un coefficient par UE\n");
  printf("**\n");
  printf("** 'coefficients' suivie du numéro de semestre\n");
  printf("**\n");
  printf("** 'note'         suivie du numéro de semestre,\n");
  printf("**                du nom d'un étudiant,\n");
  printf("**                du nom d'une matiere,\n");
  printf("**                du nom d'une épreuve,\n");
  printf("**                d'une note\n");
  printf("**\n");
  printf("** 'notes'        suivie du numéro de semestre,\n");
  printf("**                du nom d'un étudiant\n");
  printf("**\n");
  printf("** 'releve'       suivie du numéro de semestre,\n");
  printf("**                du nom d'un étudiant\n");
  printf("**\n");
  printf("***************************************************************\n");
}

/* exitcommand, permet de sortir du programme avec SUCCESS
 *  La commande est appelée quand l'utilisateur rentre au clavier 'exit'
 */
int exitcommand() {
  exit(EXIT_SUCCESS);
  return EXIT_SUCCESS;
}

/* verifUE, permet de vérifier si le nombre d'UE a été défini
 * [in]  inF, formation
 * [return]  0 UE non defini, sinon 1
 */
unsigned int verifUE(const Formation* inF) {
  unsigned int out = 1;
  if (inF->nbUE == 0) {
    int charactere = 0;
    scanf("%c", &charactere);
    while (charactere != '\n') {
      scanf("%c", &charactere);
    }
    printf("Le nombre d'UE n'est pas defini\n");
    out = 0;
  }
  return out;
}

/* verifSemestre, permet de verifier si le nombre de semestre est correct
 * [in]  inSemestrechar, numero du semestre
 * [return]  Numero du semestre, sinon 0
 */
unsigned int verifSemestre(const unsigned int inNumerosum) {
  unsigned int bonsemestre = inNumerosum;
  if (bonsemestre != 0) {
    if (inNumerosum != MIN_SEMESTRE && inNumerosum != MAX_SEMESTRE) {
      printf("Le numero de semestre est incorrect\n");
      bonsemestre = 0;
    }
  }
  return bonsemestre;
}

/* verifEtudiant, permet de verifier si le prenom de l'étudiant existe deja
 * [in]  inPrenomEtu, chaine de caractères contentant le prénom de l'étudiant
 * [in]  inOutF, Formation
 * [in]  inAffichage, Afficher le message 'etudiant inconnu' si inAffichage = 1
 * [return]  Return l'index du tableau etudiants, sinon -1 (etudiant non trouvé)
 */
unsigned int verifEtudiant(Nom inPrenomEtu, const Formation* inF, const int inAffichage) {
  unsigned int index = -1;
  for (unsigned int i = 0; i < inF->nbEtudiants; i++) {
    if (strcmp(inF->etudiants[i].PrenomEtudiant, inPrenomEtu) == 0) {
      index = i;
      break;
    }
  }
  if (index == -1 && inAffichage == 1)
    printf("Etudiant inconnu\n");
  return index;
}

/* verifNoteEtu, permet de verifier si toutes les notes de l'étudiant ont étées ajoutées
 * [in]  inIndexEtu, index de l'étudiant
 * [in]  inOutF, Formation
 * [in]  inAffichage, Afficher le message 'note correctes': inAffichage = 1,
                    sinon 'il manque au moins une note a cet etudiant': inAffichage = 0
 * [in]  inNumSem, numéro du semestre
 * [return]  Return 0 s'il manque une note, sinon 1
 */
unsigned int verifNoteEtu(const int inIndexEtu, const Formation* inF, const int inAffichage, const int inNumSem) {
  int NoteBon = 1;
  unsigned int SommeEpr = 0;
  for (unsigned int i = 0; i < inF->semestres[inNumSem - 1].nbMatieres; i++)
    SommeEpr += inF->semestres[inNumSem - 1].matieres[i].nbEpreuves;
  unsigned int ComptNote = 0;
  for (unsigned int i = 0; i < inF->etudiants[inIndexEtu].nbNotes; i++)
    if (inF->etudiants[inIndexEtu].notes[i].NumeroSemestre == inNumSem && inF->etudiants[inIndexEtu].notes[i].note != -1.0f)
      ComptNote++;
  if (SommeEpr == ComptNote && inAffichage == 1)
    printf("Notes correctes\n");
  if (SommeEpr == ComptNote && inAffichage == 0)
    return NoteBon;
  if (SommeEpr != ComptNote) {
    printf("Il manque au moins une note pour cet etudiant\n");
    NoteBon = 0;
  }
  return NoteBon;
}

/* affichageReleve, permet de d'afficher le releve de note du semestre donné
                    pour un etudiant
 * [in]  inF, Formation
 * [in]  inIndexEtu, index de l'étudiant
 * [in]  moyennes, tableau de Moyenne de toutes les matières
 * [in]  inNbMoyenneMatiere, nombre totale de moyennes
 * [in]  inNumsem, numéro du semestre
 */
void affichageReleve(const Formation* inF, const int inIndexEtu, Moyenne inMoyennes[], const int inNbMoyenneMatiere, const int inNumsem) {
  unsigned int lenMat = 0;
  unsigned int MaxlenMat = 0;
  for (unsigned int i = 0; i < inF->semestres[inNumsem - 1].nbMatieres; i++) {
    char* Matiere = inF->semestres[inNumsem - 1].matieres[i].nom;
    lenMat = strlen(Matiere);
    if (MaxlenMat < lenMat)
      MaxlenMat = lenMat;
  }
  if (MaxlenMat < strlen("Moyennes"))
    MaxlenMat = strlen("Moyennes");
  for (unsigned int i = 0; i < MaxlenMat; i++)
    printf(" ");
  printf(" ");
  for (unsigned int i = 0; i < inF->nbUE; i++)
    printf(" UE%d ", i + 1);
  printf("\n");
  unsigned int i = 0;
  for (i; i < inF->semestres[inNumsem - 1].nbMatieres; i++) {
    char* Matiere = inF->semestres[inNumsem - 1].matieres[i].nom;
    printf("%s ", Matiere);
    for (unsigned int i = 0; i < MaxlenMat - strlen(Matiere); i++)
      printf(" ");
    for (unsigned int k = 0; k < inF->nbUE; k++) {
      for (int j = 0; j < inNbMoyenneMatiere; j++) {
        int bMatiere = strcmp(Matiere, inMoyennes[j].nomMatiere);
        if (bMatiere == 0 && k == inMoyennes[j].UE) {
          float note = inMoyennes[j].note;
          if (note >= NoteMoyenne)
            printf("%.1f ", floorf(note * 10) / 10);
          else if (note < NoteMoyenne && note > MIN_NOTE)
            printf(" %.1f ", floorf(note * 10) / 10);
          else if (note == MIN_NOTE) {
            float coef = 0.;
            for (unsigned int l = 0; l < inF->semestres[inNumsem - 1].matieres[i].nbEpreuves; l++)
              coef += inF->semestres[inNumsem - 1].matieres[i].epreuves[l].coef[k];
            if (coef == 0.)
              printf("  ND ");
            else
              printf(" 0.0 ");
          }

        }
      }
    }
    printf("\n");
  }
  printf("--\n");
  printf("Moyennes");
  for (unsigned int i = 0; i < MaxlenMat - strlen("Moyennes"); i++)
    printf(" ");
  for (unsigned int i = 0; i < inF->nbUE; i++) {
    switch (inNumsem) {
    case 1:
      if (inF->etudiants[inIndexEtu].MoyenneSemestre1[i] < NoteMoyenne && inF->etudiants[inIndexEtu].MoyenneSemestre1[i] > MIN_NOTE)
        printf("  %.1f", floorf(inF->etudiants[inIndexEtu].MoyenneSemestre1[i] * 10) / 10);
      else if (inF->etudiants[inIndexEtu].MoyenneSemestre1[i] >= NoteMoyenne)
        printf(" %.1f", floorf(inF->etudiants[inIndexEtu].MoyenneSemestre1[i] * 10) / 10);
      break;
    case 2:
      if (inF->etudiants[inIndexEtu].MoyenneSemestre2[i] < NoteMoyenne && inF->etudiants[inIndexEtu].MoyenneSemestre2[i] > MIN_NOTE)
        printf("  %.1f", floorf(inF->etudiants[inIndexEtu].MoyenneSemestre2[i] * 10) / 10);
      else if (inF->etudiants[inIndexEtu].MoyenneSemestre2[i] >= NoteMoyenne)
        printf(" %.1f", floorf(inF->etudiants[inIndexEtu].MoyenneSemestre2[i] * 10) / 10);
      break;
    }
  }
  printf(" \n");
}

/* CalculReleve, permet de calculer les moyennes de chaque matières
 * [in]  inOutF, Formation
 * [in]  inIndexEtu, index de l'étudiant
 * [in]  inNumsem, numéro du semestre
 * [in]  inAffichage, Afficher les moyennes de chaque matière: inAffichage = 1, sinon inAffichage = 0
 */
void CalculReleve(Formation* inOutF, const int inIndexEtu, const unsigned int inNumSem, const int inAffichage) {
  Moyenne moyennes[MAX_MATIERES * MAX_UE];
  int indexMoyenneMatiere = 0;
  for (unsigned int l = 0; l < inOutF->nbUE; l++) {
    float SommeCoefUE = 0.;
    float NoteUE = 0.;
    for (unsigned int j = 0; j < inOutF->semestres[inNumSem - 1].nbMatieres; j++) {
      char* Matiere = inOutF->semestres[inNumSem - 1].matieres[j].nom;
      float CalculNote = 0.;
      float SommeCoefMatiere = 0.;
      unsigned int k = 0;
      for (k; k < inOutF->semestres[inNumSem - 1].matieres[j].nbEpreuves; k++) {
        char* Epreuve = inOutF->semestres[inNumSem - 1].matieres[j].epreuves[k].nom;
        float coef = inOutF->semestres[inNumSem - 1].matieres[j].epreuves[k].coef[l];
        for (unsigned int i = 0; i < inOutF->etudiants[inIndexEtu].nbNotes; i++) {
          char* MatiereEtu = inOutF->etudiants[inIndexEtu].notes[i].nomMatiere;
          char* EpreuveEtu = inOutF->etudiants[inIndexEtu].notes[i].nomEpreuve;
          float NoteEtu = inOutF->etudiants[inIndexEtu].notes[i].note;
          int SemEtu = inOutF->etudiants[inIndexEtu].notes[i].NumeroSemestre;
          int bMatiere = strcmp(Matiere, MatiereEtu);
          int bEpreuve = strcmp(Epreuve, EpreuveEtu);

          if (SemEtu == inNumSem && bMatiere == 0 && bEpreuve == 0) {
            CalculNote += NoteEtu * coef;
            SommeCoefMatiere += coef;
            SommeCoefUE += coef;
            NoteUE += NoteEtu * coef;
          }
        }
      }
      float MoyenneMatiere = 0.;
      if (SommeCoefMatiere > 0.) {
        MoyenneMatiere = CalculNote / SommeCoefMatiere;
      }
      strcpy(moyennes[indexMoyenneMatiere].nomMatiere, Matiere);
      moyennes[indexMoyenneMatiere].note = MoyenneMatiere;
      moyennes[indexMoyenneMatiere].UE = l;

      indexMoyenneMatiere++;
    }
    switch (inNumSem) {
    case 1:
      inOutF->etudiants[inIndexEtu].MoyenneSemestre1[l] = NoteUE / SommeCoefUE;
      break;
    case 2:
      inOutF->etudiants[inIndexEtu].MoyenneSemestre2[l] = NoteUE / SommeCoefUE;
      break;
    }
  }
  if (inAffichage == 1)
    affichageReleve(inOutF, inIndexEtu, moyennes, indexMoyenneMatiere, inNumSem);
}

/* Initialisationformation, permet d'initialiser toutes les structures à partir de formation
 * [out]  inOutF,Formation à initialiser
 */
void Initialisationformation(Formation* inOutF) {
  inOutF->nbUE = 0;
  inOutF->nbEtudiants = 0;
  for (int i = 0; i < NB_SEMESTRES; i++)
  {
    inOutF->semestres[i].nbMatieres = 0;
    for (int j = 0; j < MAX_MATIERES; j++)
    {
      inOutF->semestres[i].matieres[j].nbEpreuves = 0;
      strcpy(inOutF->semestres[i].matieres[j].nom, CHAINE_VIDE);
      for (int k = 0; k < MAX_EPREUVES; k++)
      {
        strcpy(inOutF->semestres[i].matieres[j].epreuves[k].nom, CHAINE_VIDE);
        for (int l = 0; l < MAX_UE; l++)
          inOutF->semestres[i].matieres[j].epreuves[k].coef[l] = 0.;
      }
    }
    for (int m = 0; m < MAX_ETUDIANTS; m++)
    {
      inOutF->etudiants[m].nbNotes = 0;
      strcpy(inOutF->etudiants[m].PrenomEtudiant, CHAINE_VIDE);

      for (unsigned int o = 0; o < MAX_UE; o++) {
        inOutF->etudiants[m].MoyennesAnnuelles[o] = NoteNonDefinie;
        inOutF->etudiants[m].MoyenneSemestre1[o] = NoteNonDefinie;
        inOutF->etudiants[m].MoyenneSemestre2[o] = NoteNonDefinie;
      }
      for (int n = 0; n < MAX_EPREUVES * MAX_MATIERES; n++)
      {
        strcpy(inOutF->etudiants[m].notes[n].nomMatiere, CHAINE_VIDE);
        strcpy(inOutF->etudiants[m].notes[n].nomEpreuve, CHAINE_VIDE);
        inOutF->etudiants[m].notes[n].NumeroSemestre = 0;
        inOutF->etudiants[m].notes[n].note = NoteNonDefinie;
      }
    }
  }
}

/* ajoutMatiereEpreuve, permet de créer des matières, des épreuves et affecter les coefficients des UEs
 * [in]  inmatierename, chaine de caractere contentant le nom de la matière
 * [in]  inepreuvename, chaine de caractere contentant le nom de l'épreuve
 * [in]  inTabCoef, tableau contenant les coefficients
 * [in]  inNbSem, numero de semestre
 * [in-out]  inOutF, Formation
 */
void ajoutMatiereEpreuve(Nom inmatierename, Nom inepreuvename, const float* inTabCoef, const unsigned int inNbSem, Formation* inOutF) {
  int i = 0;
  for (i = 0; i < MAX_MATIERES; i++) {
    if (strcmp(inOutF->semestres[inNbSem].matieres[i].nom, inmatierename) == 0)
      break;
    else if (strcmp(inOutF->semestres[inNbSem].matieres[i].nom, CHAINE_VIDE) == 0) {
      strcpy(inOutF->semestres[inNbSem].matieres[i].nom, inmatierename);
      inOutF->semestres[inNbSem].nbMatieres++;
      printf("Matiere ajoutee a la formation\n");
      break;
    }
  }
  if (inepreuvename != NULL && strcmp(inepreuvename, inmatierename) != 0) {
    for (int j = 0; j < MAX_EPREUVES; j++) {
      if (strcmp(inOutF->semestres[inNbSem].matieres[i].epreuves[j].nom, CHAINE_VIDE) == 0) {
        strcpy(inOutF->semestres[inNbSem].matieres[i].epreuves[j].nom, inepreuvename);
        for (unsigned int m = 0; m < inOutF->nbUE; m++)
          inOutF->semestres[inNbSem].matieres[i].epreuves[j].coef[m] = inTabCoef[m];
        inOutF->semestres[inNbSem].matieres[i].nbEpreuves++;
        printf("Epreuve ajoutee a la formation\n");
        break;
      }
    }
  }
}

/* formation, permet de créer une formation d'UE
 * [in-out]  inOutF, retun the Formation
 */
void formation(Formation* inOutF) {
  int ue = 0;
  scanf("%d", &ue);
  if (inOutF->nbUE == 0) {
    if (ue >= MIN_UE && ue <= MAX_UE) {
      printf("Le nombre d'UE est defini\n");
      inOutF->nbUE = ue;
    }
    else
      printf("Le nombre d'UE est incorrect\n");
  }
  else
    printf("Le nombre d'UE est deja defini\n");
}

/* epreuve, commande epreuve permet de créer des matières, des epreuves et affecter des coefficients
 * [in-out]  inOutF, Formation
 */
void epreuve(Formation* inOutF) {
  unsigned int UE = verifUE(inOutF);
  if (UE == 0)
    return;
  unsigned int numsem = 0;
  Nom matierechar;
  Nom epreuvechar;
  scanf("%d %s %s", &numsem, matierechar, epreuvechar);
  int Taille = inOutF->nbUE;
  float coefTab[MAX_UE];
  for (int i = 0; i < Taille; i++) {
    float value = 0.;
    scanf("%f", &value);
    coefTab[i] = value;
  }
  unsigned int checkSem = verifSemestre(numsem);
  if (checkSem != 0) {
    for (int k = 0; k < MAX_EPREUVES; k++) {
      for (int j = 0; j < MAX_MATIERES; j++) {
        if (strcmp(inOutF->semestres[numsem - 1].matieres[j].epreuves[k].nom, epreuvechar) == 0) {
          if (strcmp(inOutF->semestres[numsem - 1].matieres[j].nom, matierechar) == 0) {
            printf("Une meme epreuve existe deja\n");
            return;
          }
        }
      }
    }
    int coefnegatif = 0;
    unsigned int checkcoefnul = 0;
    unsigned int boncoef = 0;
    for (unsigned int i = 0; i < inOutF->nbUE; i++) {
      float numerocoef = coefTab[i];
      if (numerocoef == 0.)
        checkcoefnul++;
      else if (numerocoef < 0.) {
        coefnegatif = 1;
        break;
      }
      else if (numerocoef > 0.)
        boncoef++;
    }
    if (coefnegatif == 1 || checkcoefnul == inOutF->nbUE) {
      printf("Au moins un des coefficients est incorrect\n");
      return;
    }
    if (coefnegatif == 0 && boncoef >= 1 && matierechar != NULL && epreuvechar != NULL)
      ajoutMatiereEpreuve(matierechar, epreuvechar, coefTab, numsem - 1, inOutF);
  }
}

/* coefficients, commande coefficients permet de verifier les coefficients
 * [in-out]  inOutF, Formation
 */
void coefficients(Formation* inOutF) {
  unsigned int UE = verifUE(inOutF);
  if (UE == 0)
    return;
  unsigned int numerosem = 0;
  scanf("%d", &numerosem);
  unsigned int numsem = verifSemestre(numerosem);
  if (numsem != 0) {
    unsigned int NbEpr = 0;
    for (unsigned int i = 0; i < inOutF->semestres[numsem - 1].nbMatieres; i++) {
      NbEpr += inOutF->semestres[numsem - 1].matieres[i].nbEpreuves;
    }
    if (NbEpr == 0) {
      printf("Le semestre ne contient aucune epreuve\n");
      return;
    }
    unsigned int nbUE = inOutF->nbUE;
    unsigned int affichage = 1;
    for (unsigned int l = 0; l < nbUE; l++) {
      float coef = 0.;
      for (unsigned int i = 0; i < inOutF->semestres[numsem - 1].nbMatieres; i++) {
        for (unsigned int j = 0; j < inOutF->semestres[numsem - 1].matieres->nbEpreuves; j++) {
          coef += inOutF->semestres[numsem - 1].matieres[i].epreuves[j].coef[l];
        }
      }
      if (coef == 0.)
        affichage = 0;
    }
    if (affichage == 1)
      printf("Coefficients corrects\n");
    else
      printf("Les coefficients d'au moins une UE de ce semestre sont tous nuls\n");
  }
}

/* note, commande coefficients permet de verifier la note d'un étudiant
 * [in-out]  inOutF, Formation
 */
void note(Formation* inOutF) {
  unsigned int UE = verifUE(inOutF);
  if (UE == 0)
    return;
  unsigned int numsem = 0;
  Nom PNomEtudiant;
  Nom matierechar;
  Nom epreuvechar;
  float noteEtu;
  scanf("%d %s %s %s %f", &numsem, PNomEtudiant, matierechar, epreuvechar, &noteEtu);

  unsigned int checkSem = verifSemestre(numsem);
  if (checkSem != 0) {
    unsigned int MatiereConnue = 0;
    unsigned int EpreuveConnue = 0;
    unsigned int j = 0;
    for (j; j < inOutF->semestres[numsem - 1].nbMatieres; j++) {
      if (strcmp(inOutF->semestres[numsem - 1].matieres[j].nom, matierechar) == 0) {
        MatiereConnue = 1;
        break;
      }
    }
    if (MatiereConnue == 0) {
      printf("Matiere inconnue\n");
      return;
    }
    for (unsigned int k = 0; k < inOutF->semestres[numsem - 1].matieres[j].nbEpreuves; k++) {
      if (strcmp(inOutF->semestres[numsem - 1].matieres[j].epreuves[k].nom, epreuvechar) == 0) {
        EpreuveConnue = 1;
        break;
      }
    }
    if (EpreuveConnue == 0) {
      printf("Epreuve inconnue\n");
      return;
    }
    if (noteEtu < MIN_NOTE || noteEtu > MAX_NOTE) {
      printf("Note incorrecte\n");
      return;
    }
    unsigned int AjoutNote = 1;
    int indexEtu = verifEtudiant(PNomEtudiant, inOutF, 0);
    if (indexEtu == -1) {
      strcpy(inOutF->etudiants[inOutF->nbEtudiants].PrenomEtudiant, PNomEtudiant);

      indexEtu = inOutF->nbEtudiants;
      inOutF->nbEtudiants++;
      printf("Etudiant ajoute a la formation\n");
    }
    else {
      for (int i = 0; i < MAX_EPREUVES; i++) {
        if (strcmp(inOutF->etudiants[indexEtu].notes[i].nomMatiere,
          matierechar) == 0) {
          if (strcmp(inOutF->etudiants[indexEtu].notes[i].nomEpreuve,
            epreuvechar) == 0) {
            if (numsem == inOutF->etudiants[indexEtu].notes[i].NumeroSemestre) {

              if (inOutF->etudiants[indexEtu].notes[i].note != NoteNonDefinie) {
                printf("Une note est deja definie pour cet etudiant\n");
                AjoutNote = 0;
              }
            }
          }
        }
      }
    }
    if (AjoutNote == 1) {
      int index = inOutF->etudiants[indexEtu].nbNotes;
      assert(index < MAX_MATIERES* MAX_EPREUVES* NB_SEMESTRES);
      strcpy(inOutF->etudiants[indexEtu].notes[index].nomMatiere, matierechar);
      strcpy(inOutF->etudiants[indexEtu].notes[index].nomEpreuve, epreuvechar);
      inOutF->etudiants[indexEtu].notes[index].NumeroSemestre = numsem;
      inOutF->etudiants[indexEtu].notes[index].note = noteEtu;
      inOutF->etudiants[indexEtu].nbNotes++;
      printf("Note ajoutee a l'etudiant\n");
    }
  }
}

/* notes, commande coefficients permet de verifier les notes d'un étudiant
 * [in-out]  inOutF, Formation
 */
void notes(Formation* inOutF) {
  unsigned int UE = verifUE(inOutF);
  if (UE == 0)
    return;
  unsigned int numsem = 0;
  Nom PNomEtudiant;
  scanf("%d %s", &numsem, PNomEtudiant);
  unsigned int checkSem = verifSemestre(numsem);
  if (checkSem != 0) {
    int indexEtu = verifEtudiant(PNomEtudiant, inOutF, 1);
    if (indexEtu == -1)
      return;
    verifNoteEtu(indexEtu, inOutF, 1, numsem);
  }
}

/* releve, commande affichant le releve de notes d'un étudiant
 * [in]  inF, Formation
 */
void releve(const Formation* inF) {
  unsigned int UE = verifUE(inF);
  if (UE == 0)
    return;
  unsigned int numsem = 0;
  Nom PNomEtudiant;
  scanf("%d %s", &numsem, PNomEtudiant);

  unsigned int checkSem = verifSemestre(numsem);
  if (checkSem != 0) {
    int indexEtu = verifEtudiant(PNomEtudiant, inF, 1);
    if (indexEtu == -1)
      return;
    for (unsigned int i = 0; i < inF->nbUE; i++) {
      float SommeCoef = 0.;
      for (unsigned int j = 0; j < inF->semestres[numsem - 1].nbMatieres; j++) {
        for (unsigned int k = 0; k < inF->semestres[numsem - 1].matieres[j].nbEpreuves; k++)
          SommeCoef += inF->semestres[numsem - 1].matieres[j].epreuves[k].coef[i];
      }
      if (SommeCoef == 0.) {
        printf("Les coefficients de ce semestre sont incorrects\n");
        return;
      }
    }
    int NoteBon = verifNoteEtu(indexEtu, inF, 0, numsem);
    if (NoteBon == 0)
      return;
    CalculReleve(inF, indexEtu, numsem, 1);
  }
}

/* decision, commande affichant la decision du jury
 * [in-out]  inF, Formation
 */
void decision(Formation* inOutF) {
  unsigned int UE = verifUE(inOutF);
  if (UE == 0)
    return;
  Nom PNomEtudiant;
  scanf("%s", PNomEtudiant);
  int indexEtu = verifEtudiant(PNomEtudiant, inOutF, 1);
  if (indexEtu == -1)
    return;
  for (unsigned int l = 0; l < NB_SEMESTRES; l++) {
    for (unsigned int i = 0; i < inOutF->nbUE; i++) {
      float SommeCoef = 0.;
      for (unsigned int j = 0; j < inOutF->semestres[l].nbMatieres; j++) {
        for (unsigned int k = 0; k < inOutF->semestres[l].matieres[j].nbEpreuves; k++)
          SommeCoef += inOutF->semestres[l].matieres[j].epreuves[k].coef[i];
      }
      if (SommeCoef == 0.) {
        printf("Les coefficients d'au moins un semestre sont incorrects\n");
        return;
      }
    }
    int NoteBon = verifNoteEtu(indexEtu, inOutF, 0, l + 1);
    if (NoteBon == 0)
      return;
  }

  unsigned int CalculFaitSem1 = 1;
  unsigned int CalculFaitSem2 = 1;
  for (unsigned int i = 0; i < MAX_UE; i++) {
    if (inOutF->etudiants[indexEtu].MoyenneSemestre1[i] == -1.0f)
      CalculFaitSem1 = 0;
    if (inOutF->etudiants[indexEtu].MoyenneSemestre2[i] == -1.0f)
      CalculFaitSem2 = 0;
  }
  if (CalculFaitSem1 == 0)
    CalculReleve(inOutF, indexEtu, 1, 0);
  if (CalculFaitSem2 == 0)
    CalculReleve(inOutF, indexEtu, 2, 0);

  for (unsigned int i = 0; i < inOutF->nbUE; i++) {
    float moyenne1 = 0.;
    float moyenne2 = 0.;
    float moyenneAnnee = 0.;
    moyenne1 = inOutF->etudiants[indexEtu].MoyenneSemestre1[i];
    moyenne2 = inOutF->etudiants[indexEtu].MoyenneSemestre2[i];
    moyenneAnnee = (moyenne1 + moyenne2) / 2;
    inOutF->etudiants[indexEtu].MoyennesAnnuelles[i] = moyenneAnnee;
  }
  unsigned int compteurUE = 0;
  int Passage = 1;
  for (unsigned int i = 0; i < inOutF->nbUE; i++) {
    if (inOutF->etudiants[indexEtu].MoyennesAnnuelles[i] >= NoteMoyenne)
      compteurUE++;
  }
  if (compteurUE > 0) {
    if (compteurUE > inOutF->nbUE / 2)
      Passage = 2;
  }
  printf("                   ");
  for (unsigned int i = 0; i < inOutF->nbUE; i++)
    printf(" UE%d ", i + 1);
  printf("\n");
  printf("S1                 ");

  for (unsigned int i = 0; i < inOutF->nbUE; i++) {
    if (inOutF->etudiants[indexEtu].MoyenneSemestre1[i] >= NoteMoyenne)
      printf("%.1f ", floorf(inOutF->etudiants[indexEtu].MoyenneSemestre1[i] * 10) / 10);
    else if (inOutF->etudiants[indexEtu].MoyenneSemestre1[i] < NoteMoyenne && inOutF->etudiants[indexEtu].MoyenneSemestre1[i] > MIN_NOTE)
      printf(" %.1f ", floorf(inOutF->etudiants[indexEtu].MoyenneSemestre1[i] * 10) / 10);
  }
  printf("\nS2                 ");

  for (unsigned int i = 0; i < inOutF->nbUE; i++) {
    if (inOutF->etudiants[indexEtu].MoyenneSemestre2[i] >= NoteMoyenne)
      printf("%.1f ", floorf(inOutF->etudiants[indexEtu].MoyenneSemestre2[i] * 10) / 10);
    else if (inOutF->etudiants[indexEtu].MoyenneSemestre2[i] < NoteMoyenne && inOutF->etudiants[indexEtu].MoyenneSemestre2[i] > MIN_NOTE)
      printf(" %.1f ", floorf(inOutF->etudiants[indexEtu].MoyenneSemestre2[i] * 10) / 10);
  }
  printf("\n--\n");
  printf("Moyennes annuelles ");
  for (unsigned int i = 0; i < inOutF->nbUE; i++) {
    if (inOutF->etudiants[indexEtu].MoyennesAnnuelles[i] >= NoteMoyenne)
      printf("%.1f ", floorf(inOutF->etudiants[indexEtu].MoyennesAnnuelles[i] * 10) / 10);
    else if (inOutF->etudiants[indexEtu].MoyennesAnnuelles[i] < NoteMoyenne && inOutF->etudiants[indexEtu].MoyennesAnnuelles[i] > MIN_NOTE)
      printf(" %.1f ", floorf(inOutF->etudiants[indexEtu].MoyennesAnnuelles[i] * 10) / 10);
  }
  printf("\nAcquisition        ");
  unsigned int Acquisition = 0;
  for (unsigned int i = 0; i < inOutF->nbUE; i++) {
    if (inOutF->etudiants[indexEtu].MoyennesAnnuelles[i] >= NoteMoyenne) {
      printf("UE%d", i + 1);
      Acquisition++;
      compteurUE--;
      if (compteurUE >= 1)
        printf(", ");
    }
  }
  if (Acquisition == 0)
    printf("Aucune");
  printf("\nDevenir            ");
  switch (Passage) {
  case 1:
    printf("Redoublement\n");
    break;
  case 2:
    printf("Passage\n");
    break;
  }
}
