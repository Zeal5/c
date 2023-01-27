#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// macros

#define L3 "    ________\n"              \
           "    |      \\|\n"            \
           "    o       | \n"            \
           "            | \n"            \
           "            | LIVES =  %d\n" \
           "            | \n"            \
           " ___________|___ \n"         \
           " |          | \n"            \
           " |          |\n\n\n"

#define L2 "    ________\n"              \
           "    |      \\|\n"            \
           "    o       | \n"            \
           "    |\\      | \n"           \
           "    |       | LIVES =  %d\n" \
           "            | \n"            \
           " ___________|___ \n"         \
           " |          | \n"            \
           " |          |\n\n\n"

#define L1 "    ________\n"              \
           "    |      \\|\n"            \
           "    o       | \n"            \
           "   /|\\      | \n"           \
           "    |       | LIVES =  %d\n" \
           "   /        | \n"            \
           " ___________|___ \n"         \
           " |          | \n"            \
           " |          |\n\n\n"

#define LIFE0 "    ________\n"      \
              "    |      \\| \n"   \
              "    o       | \n"    \
              "   /|\\      | \n"   \
              "    |       | \n"    \
              "   / \\      | \n"   \
              " ___________|___ \n" \
              " |          | \n"    \
              " |   R.I.P      |\n"

char secret_word(char *beforeword)
{
    FILE *fp = fopen("C:\\Users\\tassa\\Desktop\\c\\words.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    int total_words = 0;
    char word[20];
    while (fscanf(fp, "%s", word) != EOF)
    {
        total_words++;
    }

    int rand_word = rand() % total_words;
    rewind(fp);
    for (int i = 0; i <= rand_word; i++)
    {
        fscanf(fp, "%s", word);
    }
    fclose(fp);
    strcpy(beforeword, word);
}
void hangman()
{
    char secretWord[20];
    secret_word(secretWord);

    char guessed[20];
    int lives;

    for (int i = 0; i < strlen(secretWord); i++)
    {
        guessed[i] = '-';
    }

    // choose dificulty level
    int lvl;
    printf("choose dificulty level\n1. Easy\n2. Medium\n3. Hard\n");
    scanf("%d", &lvl);
    if (lvl == 1)
    {
        lives = 12;
    }
    else if (lvl == 2)
    {
        lives = 8;
    }
    else if (lvl == 3)
    {
        lives = strlen(secretWord);
    }
    else
    {
        lives = 6;
    }
    
    while (lives > 0 && strcmp(guessed, secretWord) != 0)
    {

        printf("Guessed: %s\n", guessed);

        char letter;
        printf("Guess a letter: ");
        scanf(" %c", &letter);

        // Check if the letter is in the secretWord
        int correct = 0;
        for (int i = 0; i < strlen(secretWord); i++)
        {
            if (secretWord[i] == letter)
            {
                guessed[i] = letter;
                correct = 1;
            }
        }

        // If the letter is not in the secretWord, decrease the number of lives
        if (!correct)
        {
            lives--;
            printf("Wrong!\n");
        }
        if (lives == 1)
        {
            printf(L1, lives);
        }
        else if (lives == 2)
        {
            printf(L2, lives);
        }
        else if (lives == 3)
        {
            printf(L3, lives);
        }
    }

    // Print the result of the game
    if (strcmp(guessed, secretWord) == 0)
    {
        printf("You won! The secretWord is %s\n", secretWord);
    }
    else
    {
        printf("You lost! The secretWord was %s\n", secretWord);
        printf(LIFE0);
    }

    char ans;
    printf("Do you want to play again!\nEnter y to play again ");
    scanf("%s", &ans);
    if (ans == 'y' || ans == 'Y')
    {
        hangman();
    }
    else
    {
        return;
    }
}
int main()
{
    // welcome screen

    printf("\n *      _    _          _   _  _____ __  __          _   _ \n *     | |  | "
           "|   /\\   | \\ | |/ ____|  \\/  |   /\\   | \\ | |\n *     | |__| |  /  \\  |  \\| | |  __| \\  / |  /  \\  |  \\| |\n *     "
           "|  __  | / /\\ \\ | . ` | | |_ | |\\/| | / /\\ \\ | . ` |\n *     | |  | |/ ____ \\| |\\"
           "  | |__| | |  | |/ ____ \\| |\\  |\n *     |_|  |_/_/    \\_\\_| \\_|\\_____|_|  |_/_/    \\_\\_| \\_|\n "
           "*                                      \n *                                      \n ");

    hangman();
    return 0;
}