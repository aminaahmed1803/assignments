#include <stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 * @brief a structre to encapsulate the information of a sncak
 * 
 */
struct snack {
    char* name; 
    int quantity; 
    float cost; 
};


/**
 * @brief a function that prints the contents of a snack shop
 * 
 * @param s 
 * @param total 
 */
void printshop(struct snack* s, int total)
{   
    printf("\n");
    for(int i=0; i<total; i++)
    {
        printf("%d) %s          cost: $%0.2f    quantity: %d\n",i, (s+i)->name, (s+i)->cost, (s+i)->quantity);
    }
} 

/**
 * @brief a function that allows user to enter snacks into the shop
 * it stores snacks in an array of snacks
 * 
 * @return struct snack* 
 */
struct snack * makeshop(int count)
{
    struct snack* s = (struct snack*)malloc(sizeof(struct snack) * count); 

    for (int i=0; i<count; i++) 
    {
         (s+i)->name = (char*)malloc(sizeof ( 4*20));
        printf("\nEnter a name: ");
        scanf(" %s", (s+i)->name);

        float cost; 
        printf("Enter a cost: ");
        scanf(" %f", &cost);

        int quantity;
        printf("Enter a quantity: ");
        scanf(" %d", &quantity);

        (s+i)->quantity =quantity; 
        (s+i)->cost =cost;
        
    }
    return s;
}

int main()
{
    int snacks;
    printf("\nEnter a number of snacks: "); 
    scanf(" %d", &snacks);
    struct snack * shop = makeshop(snacks);
    printshop(shop, snacks);
    free(shop);
    return 0; 
}