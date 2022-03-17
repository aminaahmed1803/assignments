/**
 * a class that comes up with a bad password 
 * after inputing a rnadom word
 * 
 * @author aahmed1
 * Created: Tuesday, Jan 25
 */
#include <stdio.h>
#include<string.h>

/**
 * @brief function to exchange e, l and a with 3, 1 and @
 * 
 * @param pass 
 * @param size 
 * @return char* 
 */
char* badpass(char *pass, int size)
{
    for (int i=0; pass[i] != '\0'; i++) 
    {       
            if (*(pass+i) == 'e')
                *(pass+i) = '3';

            if (*(pass+i) == 'l')
                *(pass+i) = '1';

            if (*(pass+i) == 'a')
                *(pass+i) = '@';
    }

    return pass;
}

int main()
{
    char password[100];
    printf("\nEnter a word: ");
    fgets(password, sizeof(password), stdin);  // read string
    char * badpassword = badpass(password, strlen(password));
    printf("Your bad password is: ");
    puts(badpassword);
    return 0;
}
