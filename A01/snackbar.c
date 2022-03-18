/**
 * a class that lets sells you snacks when you are hungry
 * 
 * @author aahmed1
 * Created: Tuesday, Jan 25
 */
#include <stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#include<string.h>

/**
 * @brief a structre to encapsulate the information of a sncak
 * 
 */
struct snack {
    char name[20]; 
    int quantity; 
    float cost; 
};

/**
 * @brief a function that makes a default snack shop
 * it stores three snacks in an array of snacks
 * 
 * @return struct snack* 
 */
struct snack * makeshop()
{
    struct snack* s = (struct snack*)malloc(sizeof(struct snack) * 10); 
    
    //s->name = malloc(sizeof(4*20));
    strcpy(s->name, "Coco Puffs");
    s->quantity =4; 
    s->cost =1.5;

    //(s+1)->name = malloc(sizeof(4*20));
    strcpy((s+1)->name, "Manchego cheese");
    (s+1)->quantity =6; 
    (s+1)->cost =15.5;

    //(s+2)->name = malloc(sizeof(4*20));
    strcpy((s+2)->name ,"Magic beans");
    (s+2)->quantity =0; 
    (s+2)->cost =0.5;

    return s;
}

/**
 * @brief a function that prints the contents of a snack shop
 * 
 * @param s 
 * @param total 
 */
void printshop(struct snack* s, int total)
{   
    for(int i=0; i<total; i++)
    {
        printf("%d) %s          cost: $%0.2f     quantity: %d\n",i, (s+i)->name, (s+i)->cost, (s+i)->quantity);
    }
}   

/**
 * @brief a function that runs the shop
 * 
 * @param s 
 * @param size 
 * @return ** void 
 */
void runshop(struct snack* s, int size)
{
    int choice; 
    float money; 

    printf("Welcome to Steven Struct's Snack Bar. \nHow much money do you have? ");
    scanf("%0.2f", &money); 
    printshop(s,size);
    printf("What snack would you like to buy? [0,1,2...] ");
    scanf("%d", &choice);

    if (choice >= size || choice < 0)
    {
        printf("Invalid Choice! \n");
        return;
    }
    if ( (s+choice)->quantity<= 0)
    {
        printf("Sorry, we are out of the selected snack\n");
        return; 
    }
    if ( (s+choice)->cost > money)
    {
        printf("You can't afford it!\n");
        return; 
    }
    money = money - (s+choice)->cost; 
    printf("You bought %s\nYou have $%0.2f left",(s+choice)->name, money); 
    (s+choice)->quantity--; 
    return;
}

int main()
{
    struct snack * shop = makeshop();
    runshop(shop, 3);
    free (shop);	
    return 0; 
}
