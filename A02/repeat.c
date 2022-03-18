/**
 * a program that repeats a word a certain number of times
 * 
 * @author aahmed1
 * Created: Wednesday, Feb 2
 */
#include <stdio.h>
#include<string.h>
#include <stdlib.h>


/**
 * @brief function that repeats a word a certain number of times
 * 
 * @param wort to repeat
 * @param size of word 
 * @param count number of times to repeat
 */
void repeat(const char * word, int count, int size)
{
    size++;
    int new_size = count*size*sizeof(char);
    if (count == 0) return;

    char * newword = (char *)malloc(new_size); 
    if (newword == NULL)   
    {
        printf("Cannot allocate new string. Exiting...\n");
        return;
    }
    strcpy (newword, word);
    while (--count > 0) {
        strcat (newword, word);
    }
    puts (newword);
    free(newword);
    printf("\n");
}

int main()
{
    char word[32];
    int count; 
    printf("\nEnter a word: ");
    scanf(" %s" , word);
    printf("\nEnter a count: ");
    scanf(" %d", &count);
    printf("\n");
    repeat(word,count,strlen(word)); 
    return 0; 
}
