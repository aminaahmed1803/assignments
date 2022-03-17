/**
 * a class that lets you play rock papers and scissors
 * 
 * @author aahmed1
 * Created: Tuesday, Jan 25
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/**
 * @brief function which calculates the score
 * 
 * @param you 
 * @param computer 
 * @return *** int 
 */
int game(char you, char computer)
{
	if (you == computer)
    {
        printf("You both chose the same!!!\n");
        return 1;
    }
		

	else if (you == 'r' && computer == 'p')
    {
        printf("AI chose Paper\nPaper covers rock\n");
        return 0;
    }

	else if (you == 'p' && computer == 'r') 
    {
        printf("AI chose Rock\nPaper covers rock\n");
        return 1;
    }

	else if (you == 'r' && computer == 's')
    {
        printf("AI chose Scissors\nRock bashes scissors\n");
        return 1;
    }

	else if (you == 's' && computer == 'r')
	{
        printf("AI chose Rock\nRock bashes scissors\n");
        return 0;
    }

	else if (you == 'p' && computer == 's')
	{
        printf("AI chose Scissors\nScissors cut paper\n");
        return 0;
    }
	else if (you == 's' && computer == 'p')
	{
        printf("AI chose Paper\nScissors cut paper\n");
        return 1;
    }
    else 
        return -1;
}

/**
 * @brief function to assign random value to AI and take input from user
 * 
 * @return  int 
 */
int roundds()
{
    srand(time(0));
    char moves [] = "rps";
    printf("\n");
    int n = rand() % 3;
	char you = 'p';
    char computer = moves[n]; 
	printf("Which do you choose? rock, paper, or scissors? (Enter r, p, s) ");
	scanf(" %c", &you);
    return    game(you, computer);
}

int main()
{
    int rounds=6; 
    int AI=0;
    int human=0;
    int score;
    printf("\nWelcome to Rock, Paper, Scissors!\nHow many rounds do you want to play? ");
    scanf("%d", &rounds);
    
    for (int i=0; i<rounds;i++)
    {
        score = roundds();
        if (score == 0)
                AI++;
        else if (score == 1)
            human++;
        else 
            printf("\nERROR\n");
        printf("AI score: %d, Player score: %d\n\n",AI,human);
    }
}

