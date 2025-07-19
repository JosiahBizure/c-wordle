/* wordle.txt */
#include <stdio.h>  // printf

#include "wordle.h"

Color check_char(const char guess_char, const size_t index, const char* answer) {
    if (guess_char == answer[index]) return GREEN;

    for (int i = 0; i < WORD_LEN; ++i) {
        if (guess_char == answer[i]) return YELLOW;
    }

    return RED;
}

void check_word(const char* guess, const char* answer, Color* results) {
    for (int i = 0; i < WORD_LEN; ++i) {
        results[i] = check_char(guess[i], i, answer);
    }

    return;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        // Some kind of error message
    }

    const char* answer = "plant";
    const char* guess1 = "plaza";  // expect: G G G R Y
    const char* guess2 = "tulip";  // expect: Y R Y R Y
    const char* guess3 = "plant";  // expect: G G G G G

    Color results[WORD_LEN];

    check_word(guess1, answer, results);
    printf("Test 1: ");
    for (int i = 0; i < WORD_LEN; ++i)
        printf("%d ", results[i]);
    printf("\n");

    check_word(guess2, answer, results);
    printf("Test 2: ");
    for (int i = 0; i < WORD_LEN; ++i)
        printf("%d ", results[i]);
    printf("\n");

    check_word(guess3, answer, results);
    printf("Test 3: ");
    for (int i = 0; i < WORD_LEN; ++i)
        printf("%d ", results[i]);
    printf("\n");

    return 0;
}