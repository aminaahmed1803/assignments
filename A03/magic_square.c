//---------------------------------------------------------------------
// magic_square.c 
// CS223 - Spring 2022
// Identify whether a matrix is a magic square
// Name: Amina Ahmed 
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/**
 * @brief 
 * 
 * @param filename 
 * @return int**
 */

int** retMatrix(char* filename)
{
    FILE* infile = NULL;

    infile = fopen(filename, "r");
    if (infile == NULL) {
    printf("Error: unable to open file %s\n", "input.txt");
    exit(1);
    }

    int r, c;
    fscanf(infile, "%d %d", &r, &c);

    int ** matrix = (int**)malloc(r * sizeof(int*));
    for (int i = 0; i < r; i++)
        matrix[i] = (int*)malloc(c * sizeof(int));

    for (int i=0 ; i<r ; i++){
        for (int j=0 ; j<c ; j++){
            fscanf(infile,"%d ",&matrix[i][j]); 
        }
    }
    fclose(infile);
    for (int i=0 ; i<r ; i++){
        for (int j=0 ; j<c ; j++){
            printf("%d ", matrix[i][j]); 
        }
        printf("\n");
    }
    return matrix; 
}

int* getdim(char* filename)
{
    FILE* infile = NULL;
    infile = fopen(filename, "r");
    if (infile == NULL) {
    printf("Error: unable to open file %s\n", filename);
    exit(1);
    }
    int * d = (int*)malloc(2 * sizeof(int));
    fscanf(infile, "%d %d", &d[0], &d[1]);

    fclose(infile);
    return d; 
}

bool checkMagic(int ** matrix, int r, int c)
{
    if ( r !=c )
        return false; 

    //obtain sum for both diagnols and test if they have same sum
    int d1 = 0, d2 = 0;
    for (int i = 0; i < r; i++)
    {
        d1 += matrix[i][i];
        int i2 = r-1-i; 
        d2 += matrix[i][i2];
        //printf("d1: %d d2: %d",d1,d2);
    }
    if(d1 != d2)
        return false;

    //sum of rows and coulumns 
    int row, col;
    for (int i = 0; i < r; i++) {
        row = 0;
        col = 0;
        for (int j = 0; j < c; j++)
        {
            row += matrix[i][j];
            col += matrix[j][i];
        }
        if (row != col || col != d1)
            return false;
    }
    return true; 
}

int main() {

    char filename[32]; 
    printf("Enter a file name: ");
    scanf(" %s", filename);

    int ** matrix = retMatrix(filename); 
    int * d = getdim(filename);  
    
    if (checkMagic(matrix, d[0], d[1] ) )
        printf("It is a magic square");
    else 
        printf("It is not a magic square");
    
    for (int i = 0; i < d[0]; i++)
        free(matrix[i]);
    free(matrix); 
    free(d); 
    matrix = NULL;
}

