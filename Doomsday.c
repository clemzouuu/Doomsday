#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    int healthPoint;
    int defense;
    int minStrength;
    int maxStrength;
    int isAlive;
}Monstre;


/////////////////////////////////////////////////

typedef struct {
    char nom[50];   
    int type;       
    int valeur;     
    int cout;       
} Sort;

///////////////////////////////////////////////////////////

typedef struct
{
    int healthPoint;
    int defense;
    int minstrn;
    int maxstrn;
    int turns;
    int mana;
    Sort sorts[3];
int gold ;
}Joueur;
/////////////////////////////////////////////////////

Sort initSort(char *nom, int type, int valeur, int cout) {
    Sort nouveauSort;
    strcpy(nouveauSort.nom, nom);
    nouveauSort.type = type;
    nouveauSort.valeur = valeur;
    nouveauSort.cout = cout;
    return nouveauSort;
}



///////////////////////////////
typedef struct {
    int type; // 0 pour arme, 1 pour armure, etc.
    int maxpuis;
    int minpuis;
    int defense;
    int turns;
} Objets;

Objets genererArme(){
    Objets arme;
    arme.type=1;
    arme.minpuis=rand() % 10+1 ;
    arme.maxpuis= rand() % 10+1 + arme.minpuis;
    arme.defense=0;
    return  arme ;
}

Objets genererArmure() {
    Objets armure;
    armure.type = 0; // Type 1 pour armure
    armure.defense= rand() % 10 + 5;
    armure.minpuis=0;
    armure.maxpuis= 0;
    armure.turns=0;
    return armure;
}

typedef struct {
    int gold ;
    int mana;
    Objets objets[9];
    int nbr;
} Inventaire;


Inventaire *initInventaire(){
    Inventaire *inventaire = (Inventaire *)malloc(sizeof(Inventaire));
    inventaire->gold=0;
    inventaire->mana=0;
    inventaire->nbr=0;

    return inventaire;
}
void recom(Joueur * joueur,Inventaire *invent ){


    int gold=rand() % 100 ;
    int mana =rand() % 25 ;
    invent->gold+=gold;
    invent->mana+=mana;
   
    int randomNumber = rand() % 1 +1;
  if (randomNumber==1){
      Objets obj= genererArme();
invent->objets[invent->nbr++]=obj;
      printf("L'arme Sword %d - %d \n",obj.minpuis,obj.maxpuis);
  }else {
      Objets obj= genererArmure();
      printf("Armure d'acier est ajoutée defense : %d\n",obj.defense);
      invent->objets[invent->nbr++]=obj;
  }


}
void afficherInventaire(Inventaire * inventaire,Joueur*joueur){


    for (int i =0 ; i < inventaire->nbr ; i++){
        if (inventaire->objets[i].type==1)
            printf("%d - L'arme sword %d - %d\n",i,inventaire->objets[i].minpuis,inventaire->objets[i].maxpuis);
        else printf("%d - L'armure shield %d\n",i,inventaire->objets[i].defense);
    }

    int choix;
    printf("Entrez votre choix : ");
    scanf("%d", &choix);
    printf("\n");
    if (choix >= 0 && choix < inventaire->nbr) {
        
        if (inventaire->objets[choix].type == 1) {

            printf("Vous êtes équipé de l'arme sword %d - %d\n", inventaire->objets[choix].minpuis, inventaire->objets[choix].maxpuis);
            joueur->minstrn=inventaire->objets[choix].minpuis;
            joueur->maxstrn=inventaire->objets[choix].maxpuis;


        } else {
        
            printf("Vous êtes équipé de l'armure shield %d\n", inventaire->objets[choix].defense);
            joueur->defense=inventaire->objets[choix].defense;
        }
    } else {
        printf("Choix invalide.\n");
    }

}


bool monstresMorts(Monstre *monstres, int nbr) {
    for (int i = 0; i < nbr; i++) {
        if (monstres[i].healthPoint > 0) {
            return false; 
        }
    }
    return true; 
}


int genererNbrMonstre(){
    
    srand(time(NULL));
   
    int randomNumber = rand() % 5 + 1;
    return  randomNumber;

}
Monstre *initMonster(int nbr ){

    Monstre *monsters = (Monstre *)malloc(nbr * sizeof(Monstre));


 
    for (int i = 0; i < nbr; i++) {
        monsters[i].healthPoint = rand() % 20 +1;
        monsters[i].minStrength = rand() % 4 + 1;
        monsters[i].maxStrength = monsters[i].minStrength + (rand() % 15 + 1);  
        monsters[i].defense = rand() % 5+1;
        monsters[i].isAlive=1;
    }

    return  monsters;
}
Monstre *plusfort(int nbr,int lvl){

 Monstre* monstres_fort = malloc(nbr * sizeof(Monstre));
monstres_fort=initMonster(nbr);
    for (int i = 0; i < nbr; i++) {

        monstres_fort[i].healthPoint = (int)(monstres_fort[i].healthPoint)+lvl*20;
        monstres_fort[i].minStrength = (int)(monstres_fort[i].minStrength)+lvl*5;
        monstres_fort[i].maxStrength = (int)(monstres_fort[i].maxStrength)+lvl*10;
        monstres_fort[i].defense = (int)(monstres_fort[i].defense)+lvl * 5;;
    }
    return monstres_fort;
}
Joueur * initJoueur(){

    Joueur *joueur=malloc(sizeof(Joueur));
    joueur->healthPoint = 200 ;
    joueur->maxstrn =  5;
    joueur->minstrn =  5;
    joueur->defense=0;
    joueur->turns = 4;
    joueur->mana = 200;
    joueur->gold=0;
    joueur->sorts[0] = initSort("Sort de Guerison", 1, 30, 75);    
    joueur->sorts[1] = initSort("Sort de Bouclier", 2, 5, 10);     
    joueur->sorts[2] = initSort("Sort de Puissance", 3, 20, 50);
    return joueur;
}
void gameTest(Monstre *monstres, int nbr){

    printf("Vous êtes attaqué par %d mobs  \n",nbr);
    for (int i = 0; i < nbr; i++) {
        printf("Mob %d : Health Point : %d, Defense : %d\n", i + 1, monstres[i].healthPoint, monstres[i].defense);
    }
    printf("\n");
}
void calculateDamageJ(Monstre *monstres,int numeroMonstreAAttaquer ,int degatArme) {
    if (degatArme > monstres->defense) {
        int degatsInfliges = degatArme - monstres->defense;
        monstres[numeroMonstreAAttaquer].healthPoint -= degatsInfliges;
        monstres[numeroMonstreAAttaquer].defense = 0;
        if ( monstres[numeroMonstreAAttaquer].healthPoint < 0) {
            monstres[numeroMonstreAAttaquer].healthPoint = 0;
            monstres[numeroMonstreAAttaquer].isAlive = 0;
        }
    } else {
        monstres[numeroMonstreAAttaquer].defense -= degatArme;

    }
}
void attack(Monstre * monstres,Joueur *joueur,int nbr){
    for(int i=0;i<nbr;i++){
        if(monstres[i].healthPoint!=0){
            printf("%d monstre %d\n",i+1,monstres[i].healthPoint);
        }
    }



        int numerodemonstre;
        scanf("%d", &numerodemonstre);
    numerodemonstre--;

    int degats = rand() % (joueur->maxstrn - joueur->minstrn + 1) +joueur->minstrn;
        calculateDamageJ(monstres,numerodemonstre,degats);

}
void attackMonstre(Monstre * monstres,Joueur *joueur,int nbr){
    for (int i = 0; i < nbr; i++) {
        if (monstres[i].healthPoint > 0) {
            int degatsMonstre = rand() % (monstres[i].maxStrength - monstres[i].minStrength + 1) + monstres[i].minStrength;
            joueur->healthPoint -= degatsMonstre;

            printf("Le monstre %d inflige %d dégats au joueur.\n", i + 1, degatsMonstre);

            if (joueur->healthPoint <= 0) {
                printf("Le joueur a été vaincu. Fin de la partie.\n");
                return;
            }
        }
    }
}

void sauvegarderPartie(Joueur *joueur, Monstre *monstres, int nbr)
{
   FILE *fichier = fopen("sauvegarde.txt", "w");

   if (fichier == NULL)
   {
       fprintf(stderr, "Erreur lors de l'ouverture du fichier de sauvegarde.\n");
       exit(EXIT_FAILURE);
   }

   fprintf(fichier, "%d\n", joueur->healthPoint);
   fprintf(fichier, "%d\n", joueur->minstrn);
   fprintf(fichier, "%d\n", joueur->maxstrn);
   fprintf(fichier, "%d\n", joueur->turns);

   fprintf(fichier, "%d\n", nbr);
   for (int i = 0; i < nbr; i++)
   {
       fprintf(fichier, "%d %d %d %d %d\n", monstres[i].healthPoint, monstres[i].minStrength,
               monstres[i].maxStrength, monstres[i].defense, monstres[i].isAlive);
   }

   fclose(fichier);
}

void chargerPartie(Joueur *joueur, Monstre **monstres, int *nbr) {
    FILE *fichier = fopen("sauvegarde.txt", "r");

    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(fichier, "%d", &(joueur->healthPoint));
    fscanf(fichier, "%d", &(joueur->minstrn));
    fscanf(fichier, "%d", &(joueur->maxstrn));
    fscanf(fichier, "%d", &(joueur->turns));

    fscanf(fichier, "%d", nbr);
    *monstres = (Monstre *)malloc((*nbr) * sizeof(Monstre));

    for (int i = 0; i < *nbr; i++) {
        fscanf(fichier, "%d %d %d %d %d", &((*monstres)[i].healthPoint), &((*monstres)[i].minStrength),
               &((*monstres)[i].maxStrength), &((*monstres)[i].defense), &((*monstres)[i].isAlive));
    }

    fclose(fichier);
}

void afficherSanteJoueur(Joueur *joueur) {
    printf("Santé du joueur:\n [");
    for (int i = 0; i <joueur->healthPoint; i++) {
        putchar('#');
    }
    for (int i = joueur->healthPoint; i < 200; i++) {
        putchar('-');
    }
    printf("]\n");
    printf("Mana du joueur:\n [");
    for (int i = 0; i < joueur->mana; i++)
    {
        putchar('*');
    }
    for (int i = joueur->mana; i < 200; i++)
    {
        putchar('-');
    }
    printf("]\n");
    printf("Gold %d: \n",joueur->gold);
    printf("\n");
}

void utiliserSort(Joueur *joueur) {
    printf("Choisissez un sort :\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i + 1, joueur->sorts[i].nom);
    }

    int choix;
    int verifmana = joueur->mana;
    scanf("%d", &choix);

    if (choix >= 1 && choix <= 3) {
        Sort sortChoisi = joueur->sorts[choix - 1];

        switch (sortChoisi.type) {
            case 1:  // PV
                if((verifmana - sortChoisi.cout) > -1){
                    joueur->mana -= sortChoisi.cout;
                    if(joueur->healthPoint < 200){
                        joueur->healthPoint += sortChoisi.valeur;
                        if(joueur->healthPoint > 200){
                            joueur->healthPoint = 200;
                        }
                        joueur->turns --;

                    }
                    if(joueur->healthPoint == 200){
                        printf("Tu es full  \n");

                    }
                }
                else{
                    printf("Tu n'as pas assez de mana \n");
                }
                break;
            case 2:  // Défense
                if((verifmana - sortChoisi.cout) > -1){
                    joueur->mana -= sortChoisi.cout;
                    joueur->defense += sortChoisi.valeur;
                    joueur->turns --;

                }
                else{
                    printf("Tu n'as pas assez de mana \n");
                }
                break;
            case 3:  // Offense
                if((verifmana - sortChoisi.cout) > -1){
                    joueur->minstrn += sortChoisi.valeur;
                    joueur->maxstrn += sortChoisi.valeur;
                    joueur->mana -= sortChoisi.cout;
                    joueur->turns --;
                }
                else{
                    printf("Tu n'as pas assez de mana \n");
                }
                break;
            default:
                printf("Type de sort invalide.\n");
                break;
        }
    } else {
        printf("Choix invalide.\n");
    }
}






void game(Monstre * monstres,Joueur *joueur,Inventaire *inventaire,int nbr) {
    int choix;
int lvl =1;

    int nbrtotal=joueur->turns;
    while (joueur->healthPoint > 0 ) {

        if(joueur->turns==0)printf("Tu n'as plus de tour. Finis ton tour avec un 8\n");

        afficherSanteJoueur(joueur);


        printf("Bienvenue dans DOOMSDAY. Entre une des commandes suivantes :\n");
        printf("\"1 - Attaquer %d/%d\"\n",joueur->turns,nbrtotal);
        printf("\"2 - Boire une potion \"\n");
        printf("\"3 - Inventaire\" \n");
        printf("\"4 - Sauvegarder la partie\" \n");
        printf("\"8 - Finir le tour\" \n");
        printf("\"0 - Quitter le jeu\" \n");
        printf("\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                system("cls");
                system("clear");
                if (joueur->turns > 0) {
                    attack(monstres, joueur, nbr);
                      system("cls");
                system("clear");
                    joueur->turns--;
                } else { printf("/////Tu n'as plus de tour. Finis ta partie avec un 8////\n");
                    printf("\n");}
                break;
            case 2:
                if (joueur->turns > 0){
                    utiliserSort(joueur);
                }
                else
                {
                    printf("/////Tu n'as plus de tour. Fini ta partie avec un 8////\n");
                    printf("\n");
                }
                break;
            case 3:
                afficherInventaire(inventaire,joueur);
                break;

            case 4:
                sauvegarderPartie(joueur, monstres, nbr);
                break;
            case 8:
                system("cls");
                system("clear");
                attackMonstre(monstres, joueur, nbr);
                if (joueur->healthPoint <= 0) break;
                else {
                    if(joueur->mana+60>200)joueur->mana=200;
                    else joueur->mana+=60;
                    joueur->turns = 4;
                    break;
                }
            case 0:
                exit(0);
                break;
            default:
                printf("Option invalide\n");
                break;
        }

        if (joueur->healthPoint <= 0) {
            printf("La partie est fini pour toi haha\n");
            break;
        }

        if (monstresMorts(monstres, nbr)) {
            recom(joueur,inventaire);
            nbr = genererNbrMonstre();
            monstres = plusfort( nbr,lvl++);
            if(joueur->healthPoint+20>200)joueur->healthPoint=200;
            else joueur->healthPoint+=20;
            joueur->turns = 4;
            joueur->mana=200;
            printf("Nouvelle partie avec monstres plus puissants\n");
        }
    }

    printf("Joueur mort /////////////////////////");
}



/////////////////////////////////////////////////


///////////////////////////////////////

int main(){



    printf("**************************************** \n");

    int choix;
    bool boucle=true;
while(boucle) {

    printf("Bienvenue dans DOOMSDAY. Entre une des commandes suivantes :\n");
    printf("\"1 : Nouvelle partie\"\n");
    printf("\"2 : Reprendre une partie\"\n");
    printf("\"3 : Crédits\" \n");
    printf("\"4 : Quitter le jeu\" \n");
    printf("\n");
    printf("Entrez votre choix : ");
    scanf("%d", &choix);
    system("cls");
    //////////////////////////////////////////////////////////////////////////
    int nbr=genererNbrMonstre();
    Joueur *joueur=initJoueur();
    Monstre *monstres=initMonster(nbr);
    Inventaire *inventaire=initInventaire();
    ///////////////////////////////////////////////////////////////////
    switch (choix) {
        case 1:
            gameTest(monstres,nbr);
            system("cls");
            game(monstres, joueur, inventaire,nbr);
            system("cls");
            break;
        case 2:
            chargerPartie(joueur, &monstres, &nbr);
            gameTest(monstres, nbr);
            game(monstres, joueur,inventaire, nbr);
            break;
        case 3:
            printf("Développé par\n Rayan, Mohamed && Clément. "
                   " !\n");
            break;
        case 4:
            printf("Au revoir !\n");
            exit(0);
            break;
        default:
            printf("Option invalide\n");
            break;
    }
    system("cls");
    free(monstres);
    free(joueur);
}







    return 0;
}