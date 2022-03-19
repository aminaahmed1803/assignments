#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>

char * getword( char * filename)
{
    FILE* infile = NULL;

    infile = fopen(filename, "r");
    if (infile == NULL) {
        //puts(filename);
        printf("Error: unable to open file %s\n", filename);
        exit(1);    
    }

    srand(time(0));
    char t[32];
    fgets(t, sizeof(t), infile);
    int total = atoi(t); 
    //printf(" %d", total);
    int line = rand() % total +1;
    //printf(" %d", line+2);
    
    char* word = (char*)malloc(sizeof(char)*100);
    for (int i=0 ; i<line ; i++)
    {   
        fgets(word, sizeof(word), infile); 
        //puts(word);
    }
    fclose(infile);
    return word; 
}

void guess(char * word)
{
    int size=strlen(word) ; //word = 4+
    //puts(word);
    //printf(" %d", size); 
    char * guessword = (char*)malloc(1+(sizeof(char)*(size))); //lenght of guessword = 5
    strcpy(guessword, word);
    for (int i=0; i<size ;i++) 
        guessword[i] = '_';
    //guessword[size-1] ='\0';

    int wordsfilled =size, i; 
    printf("\nWelcome to Word Guess\n"); 
    for(i=0 ; wordsfilled>1; i++ )
    {
        char guess; 
        printf("\nTurn %d\n", i+1);
        printf("%s\n", guessword);
        printf("Guess a character: ");
        scanf(" %c", &guess); 
 
        int flag =0;
        for (int i=0; i<size; i++)
        {
            if (word[i] == guess)
            {
                word[i] = '_';
                guessword[i] = guess; 
                flag = 1;
                wordsfilled--;
            }
        }
        if (flag == 0)
            printf("Sorry,letter not found!\n");
    }
    
    
    printf("\n");
    printf("%s\n", guessword); 

    free(word);
    word = NULL;

    free(guessword);
    guessword = NULL;
    
    printf("You won in %d turns! \n",i);
}

int main()
{
    char file[32];
    printf("Enter file name: "); 
    scanf(" %s",file);
    puts(file);
    char * word = getword(file); 
    guess(word); 
    return 0;
}

