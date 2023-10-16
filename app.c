#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

 struct Mob
{
    int healthPoint;
    int defense;
    int minStrength;
    int maxStrength;
};


 struct Myself
{
    int healthPoint;
    int defense;
    int minStrength;
    int maxStrength;
    int weaponPower; 
    int turns;
};

// Function to calculate the damage of an attack
int calculateDamage(int minStrength, int maxStrength, int defense, int weaponPower) {
    int playerDamage = rand() % (maxStrength - minStrength + 1) + minStrength;
    int damageDealt = playerDamage - defense - weaponPower;
    return damageDealt > 0 ? damageDealt : 0;
}

// Functinon to verify if all the mobs are dead
int randomMobsAreAlive(struct Mob mob[], int mobCount) {
    for (int i = 0; i < mobCount; i++) {
        if (mob[i].healthPoint > 0) {
            return 1; 
        }
    }
    return 0; 
}

int main(){

    char input[50];

    printf("Welcome to DOOMSDAY. Type one of the following words :\n");
    printf("\"NEW GAME\"\n");
    printf("\"RESUME GAME\"\n");
    printf("\"CREDITS\" \n");
    printf("\"QUIT\" \n");
    printf("\n");



// Random mobs

    // Random number based on the current time
    srand(time(NULL));
    // Random number from 1 to 10
    int randomNumber = (rand() % 10) + 1;

    // Array of structs to save the mobs datas
    struct Mob mob[randomNumber];

    // Generating the datas for each mob
    for (int i = 0; i < randomNumber; i++) {
        mob[i].healthPoint = rand() % 101; 
        mob[i].minStrength = rand() % 21; 
        mob[i].maxStrength = mob[i].minStrength + rand() % 31;  // Max strength = min strength + 30
        mob[i].defense = rand() % 11;
    }



// Player's strength
    struct Myself myself;
    myself.healthPoint = 200 + rand() % 101; 
    myself.minStrength = rand() % 31; 
    myself.maxStrength = myself.minStrength + rand() % 51;  //
    myself.turns = rand() % 3;




// Fights 

    printf("Your are being attacked by %d mobs  \n",randomNumber);
    printf("\n");

    // Print each mob's datas
    for (int i = 0; i < randomNumber; i++) {
        printf("Mob %d : Health Point : %d, Defense : %d\n", i + 1, mob[i].healthPoint, mob[i].defense);
    }


   while (myself.healthPoint > 0 && !allMobsDead(mob, randomNumber)) {
        printf("\nYour turns left: %d\n", myself.turns);

        // While the user has turns
        for (int turn = 0; turn < myself.turns; turn++) {
            printf("Turn %d\n", turn + 1);
           
           // Attacking a mob
            for (int i = 0; i < randomNumber; i++) {
                if (mob[i].healthPoint > 0) {
                    int damage = calculateDamage(myself.minStrength, myself.maxStrength, mob[i].defense, myself.weaponPower);
                    mob[i].healthPoint -= damage;
                    printf("You dealt %d damage to Mob %d\n", damage, i + 1);
                }
            }
        }

        // Mobs attack the user
        for (int i = 0; i < randomNumber; i++) {
            if (mob[i].healthPoint > 0) {
                int damage = calculateDamage(mob[i].minStrength, mob[i].maxStrength, myself.defense, 0);
                myself.healthPoint -= damage;
                printf("Mob %d dealt %d damage to you\n", i + 1, damage);
            }
        }

       // Reset the turns for the next round
        myself.turns = rand() % 3;
    }

    if (myself.healthPoint <= 0) {
        printf("You have been defeated.\n");
    } else {
        printf("All mobs have been defeated. Generating new mobs for the next turn...\n");
        // Generating new mobs
        for (int i = 0; i < randomNumber; i++) {
            mob[i].healthPoint = rand() % 201;  
            mob[i].minStrength = rand() % 41; 
            mob[i].maxStrength = mob[i].minStrength + rand() % 61;  
            mob[i].defense = rand() % 21; 
        }
    }


     
    
    return 0;
}