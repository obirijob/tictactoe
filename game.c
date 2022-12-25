#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

const int ROWS = 3, COLUMNS = 3;
char board[ROWS][COLUMNS];
const char COMPUTER = 'O', player = 'X';

void resetBoard();
void drawBoard();
void makePlay();
int isFree(int, int);
char winner();
int freeSlots();
void computerPlay();

int main()
{
    system("clear");
    printf("TICTACTOE GAME\n");

    resetBoard();

    do
    {
        drawBoard();
        if (freeSlots() > 0)
        {
            makePlay();
        }
        else
        {
            printf("\nNo winner its a tie!\n");
            break;
        }

    } while (winner() == ' ');

    if (winner() != ' ')
    {
        drawBoard();
        printf("\n\n%c wins", winner());
    }

    return 0;
}

void resetBoard()
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLUMNS; c++)
        {
            board[r][c] = ' ';
        }
    }
}

void drawBoard()
{
    printf("\n");

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLUMNS; c++)
        {
            if (c < COLUMNS - 1)
                printf(" %c |", board[r][c]);
            else
                printf(" %c ", board[r][c]);
        }
        if (r < ROWS - 1)
        {
            printf("\n");
            for (int c = 0; c < COLUMNS; c++)
            {
                if (c < COLUMNS - 1)
                    printf("---|");
                else
                    printf("---");
            }
            printf("\n");
        }
    }
    printf("\n");
}

void makePlay()
{
    int playerR, playerC;
    do
    {
        printf("Enter row: ");
        scanf("%d", &playerR);

        printf("Enter column: ");
        scanf("%d", &playerC);

    } while (isFree(playerR, playerC) == 0);
    board[playerR][playerC] = player;
    computerPlay();
}

int isFree(int r, int c)
{
    int free = board[r][c] == ' ' ? 1 : 0;
    return free;
}

int freeSlots()
{
    int free = COLUMNS * ROWS;
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLUMNS; c++)
        {
            if (board[r][c] != ' ')
                free--;
        }
    }
    return free;
}

void computerPlay()
{
    srand(time(0));
    int r = (rand() % ROWS);
    int c = (rand() % COLUMNS);

    do
    {
        if (freeSlots() > 0)
        {
            r = (rand() % ROWS);
            c = (rand() % COLUMNS);
        }
        else
        {
            break;
        }

    } while (isFree(r, c) == 0);
    board[r][c] = COMPUTER;
}

char winner()
{
    char win = ' ';
    for (int r = 0; r < ROWS; r++)
    {
        char f = board[r][0];
        for (int c = 1; c < COLUMNS; c++)
        {
            char cf = board[r][c];
            if (cf != f)
                break;
            if (cf == f && ((c + 1) == COLUMNS))
            {
                win = f;
                break;
            }
        }
    }
    for (int c = 0; c < COLUMNS; c++)
    {
        char f = board[0][c];
        for (int r = 1; r < ROWS; r++)
        {
            char cf = board[r][c];
            if (cf != f)
                break;
            if (cf == f && ((r + 1) == ROWS))
            {
                win = f;
                break;
            }
        }
    }

    // diagonals later
    return win;
}