/* wordle.txt */
#include <stdio.h>  // printf, fopen
#include <string.h> // strcspn, strncpy
#include <stdlib.h> // malloc, free
#include <time.h>   // time

#include "wordle.h"

Color check_char(const char guess_char, const size_t index, const char* answer) {
    if (guess_char == answer[index]) return GREEN;

    for (size_t i = 0; i < WORD_LEN; ++i) {
        if (guess_char == answer[i]) return YELLOW;
    }

    return RED;
}


void check_word(const char* guess, const char* answer, Color* results) {
    for (size_t i = 0; i < WORD_LEN; ++i) {
        results[i] = check_char(guess[i], i, answer);
    }

    return;
}


void populate_words(const char* file_name, char** words) {
    char buffer[WORD_LEN + 3]; // +1 for /r, +1 for /n, and +1 for \0
    FILE* fd = fopen(file_name, "r");
    if (fd == NULL) {
        perror("[ERROR] populate_words() fopen()");
        return;
    }

    for (size_t i = 0; i < NUM_WORDS; ++i) {
        if (fgets(buffer, sizeof(buffer), fd) == NULL) {
            fprintf(stderr, "[WARN] Expected %zu words, but file ended early.\n", (size_t)NUM_WORDS);
            break;
        }

        buffer[strcspn(buffer, "\r\n")] = '\0'; // remove newline
        strncpy(words[i], buffer, WORD_LEN + 1); // assumes words[i] is already malloc'd
    }

    fclose(fd);
}


char* random_word(char** words) {
    size_t index = rand() % NUM_WORDS;
    return words[index];
}


void set_seed() {
    srand((unsigned int)time(NULL));
}


void game_loop(const char* answer, size_t word_len, char** words) {
    char guess[word_len + 2];  // +1 for newline, +1 for null
    Color results[word_len];

    printf("Welcome to Wordle in C!\nGuess the %zu-letter word.\n\n", word_len);

    int attempt = 0;
    while (attempt < MAX_ATTEMPTS) {
        printf("Attempt %d/%d: ", attempt + 1, MAX_ATTEMPTS);

        // Get user input
        if (fgets(guess, sizeof(guess), stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        }

        // Remove newline characters
        guess[strcspn(guess, "\r\n")] = '\0';

        // Validate length
        if (strlen(guess) != word_len) {
            printf("Guess must be exactly %zu letters.\n\n", word_len);
            continue;
        }

        // Convert guess to lowercase
        for (size_t i = 0; i < word_len; ++i) {
            if (guess[i] >= 'A' && guess[i] <= 'Z') {
                guess[i] = guess[i] - 'A' + 'a';
            }
        }

        if (!is_valid_word(guess, words)) {
            printf("'%s' is not a valid word.\n\n", guess);
            continue;
        }

        ++attempt;

        // Evaluate guess
        check_word(guess, answer, results);

        // Print colored result
        for (size_t i = 0; i < word_len; ++i) {
            switch (results[i]) {
                case GREEN:  printf("\033[0;32m%c\033[0m", guess[i]); break;
                case YELLOW: printf("\033[0;33m%c\033[0m", guess[i]); break;
                case RED:    printf("\033[0;31m%c\033[0m", guess[i]); break;
            }
        }
        printf("\n\n");

        // Win condition
        if (strcmp(guess, answer) == 0) {
            printf("You guessed it! The word was \"%s\".\n", answer);
            return;
        }
    }

    printf("Out of attempts! The word was \"%s\".\n", answer);
}


int is_valid_word(const char* guess, char** words) {
    for (size_t i = 0; i < NUM_WORDS; ++i) {
        if (strcmp(guess, words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


int main(int argc, char** argv) {
    if (argc != 2) {
        // Some kind of error message
    }

    set_seed();

    char* words[NUM_WORDS];
    for (size_t i = 0; i < NUM_WORDS; ++i) {
        words[i] = malloc(WORD_LEN + 1);
        if (words[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for words[%zu]\n", i);
            return 1;
        }
    }

    populate_words("words5.txt", words);
    char* answer = random_word(words);

    // Play
    game_loop(answer, WORD_LEN, words);

    // Free memory
    for (size_t i = 0; i < NUM_WORDS; ++i) {
        free(words[i]);
    }

    return 0;
}