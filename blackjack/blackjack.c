#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

/**
 * BLACKJACK GAME IN C
 * Author: Gökhan Korcan Sancaktaroğlu
 * Description: A simple command-line Blackjack game with Ace logic.
 */

#define MAX_HAND 12
#define DEALER_MIN 17
#define TARGET_SCORE 21

// Function Prototypes
int draw_card();
int card_to_value(int card);
void print_card(int card);
int calculate_score(int hand[], int count);

int main() {
    srand((unsigned int)time(NULL));

    int player_hand[MAX_HAND], dealer_hand[MAX_HAND];
    int p_count = 0, d_count = 0;
    char action;

    // Initial Deal
    player_hand[p_count++] = draw_card();
    player_hand[p_count++] = draw_card();
    dealer_hand[d_count++] = draw_card();
    dealer_hand[d_count++] = draw_card();

    printf("=================================\n");
    printf("   WELCOME TO C-LANG CASINO   \n");
    printf("=================================\n");

    printf("Dealer shows: ");
    print_card(dealer_hand[0]);
    printf("[Hidden]\n");

    // Player's Turn
    while (1) {
        int score = calculate_score(player_hand, p_count);
        printf("\nYour Hand: ");
        for (int i = 0; i < p_count; i++) print_card(player_hand[i]);
        printf("(Total: %d)\n", score);

        if (score == TARGET_SCORE) {
            printf(">> BLACKJACK! <<\n");
            break;
        } 
        if (score > TARGET_SCORE) {
            printf(">> BUST! You lose. <<\n");
            return 0;
        }

        printf("Action: [H]it or [S]tand? ");
        scanf(" %c", &action);
        action = (char)tolower(action);

        if (action == 'h') {
            player_hand[p_count++] = draw_card();
        } else if (action == 's') {
            break;
        }
    }

    // Dealer's Turn
    printf("\nDealer reveals: ");
    for (int i = 0; i < d_count; i++) print_card(dealer_hand[i]);
    printf("\n");

    while (calculate_score(dealer_hand, d_count) < DEALER_MIN) {
        dealer_hand[d_count++] = draw_card();
        printf("Dealer hits: ");
        print_card(dealer_hand[d_count - 1]);
        printf("\n");
    }

    int p_final = calculate_score(player_hand, p_count);
    int d_final = calculate_score(dealer_hand, d_count);

    printf("\n--- FINAL RESULTS ---\n");
    printf("Player: %d | Dealer: %d\n", p_final, d_final);

    if (d_final > TARGET_SCORE) printf("RESULT: Dealer busts! YOU WIN!\n");
    else if (p_final > d_final) printf("RESULT: YOU WIN!\n");
    else if (p_final < d_final) printf("RESULT: DEALER WINS!\n");
    else printf("RESULT: IT'S A PUSH!\n");

    return 0;
}

int draw_card() {
    return rand() % 13 + 1;
}

int card_to_value(int card) {
    return (card > 10) ? 10 : card;
}

void print_card(int card) {
    if (card == 1) printf("[A] ");
    else if (card == 11) printf("[J] ");
    else if (card == 12) printf("[Q] ");
    else if (card == 13) printf("[K] ");
    else printf("[%d] ", card);
}

int calculate_score(int hand[], int count) {
    int sum = 0, aces = 0;
    for (int i = 0; i < count; i++) {
        sum += card_to_value(hand[i]);
        if (hand[i] == 1) aces++;
    }
    while (aces > 0 && sum + 10 <= TARGET_SCORE) {
        sum += 10;
        aces--;
    }
    return sum;
}
