#include<stdio.h>
#include <stdlib.h>
#include <time.h>

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
    int turns;
};

int main(){

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

    // Print each mob's datas
    for (int i = 0; i < randomNumber; i++) {
        printf("Mob %d : Health Point = %d, Defense = %d\n", i + 1, mob[i].healthPoint, mob[i].defense);
    }




// Player's strength
    struct Myself myself;
    myself.healthPoint = 200 + rand() % 101; 
    myself.minStrength = rand() % 31; 
    myself.maxStrength = myself.minStrength + rand() % 51;  //
    myself.turns = rand() % 3;





    return 0;
}