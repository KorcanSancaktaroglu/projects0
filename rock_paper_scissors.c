#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

typedef struct GameHistory {
    char playerChoice;
    char computerChoice;
    int result; // 1: Player Wins, 0: Computer Wins, -1: Draw
    struct GameHistory* next;
} GameHistory;

int playGame(char player, char computer);

int main() {
    char player, computer;
    int randomNumber;

    srand((unsigned int)time(0));
    randomNumber = rand() % 100;

    // Logic: Assigning computer's choice based on random number
    if (randomNumber <= 33) {
        computer = 'R'; // Rock (Tas)
    } else if (randomNumber <= 66) {
        computer = 'P'; // Paper (Kagit)
    } else {
        computer = 'S'; // Scissors (Makas)
    }

    printf("--- Rock, Paper, Scissors Game ---\n");
    printf("R (Rock) - P (Paper) - S (Scissors): ");
    
    // Space before %c skips any leftover newline characters
    scanf(" %c", &player);
    player = (char)toupper(player);

    int result = playGame(player, computer);

    printf("\nComputer: %c\nYou: %c\n", computer, player);

    if (result == 1) {
        printf("RESULT: You Won!\n");
    } else if (result == -1) {
        printf("RESULT: It's a Draw!\n");
    } else if (result == -2) {
        printf("ERROR: Invalid input.\n");
    } else {
        printf("RESULT: You Lost!\n");
    }

    printf("Game Over.\n");

    return 0;
}

int playGame(char player, char computer) {
    if (player == '\0') return -2;

    // Rock Beats Scissors, Scissors Beats Paper, Paper Beats Rock
    if ((player == 'R' && computer == 'S') || 
        (player == 'S' && computer == 'P') || 
        (player == 'P' && computer == 'R')) {
        return 1;
    } 
    else if (computer == player) {
        return -1;
    } 
    else {
        return 0;
    }
}
