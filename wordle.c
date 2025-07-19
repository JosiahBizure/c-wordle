/* wordle.txt */
#include <stdio.h>  // printf, fopen
#include <string.h> // strcspn, strncpy
#include <stdlib.h> // malloc, free

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

int main(int argc, char** argv) {
    if (argc != 2) {
        // Some kind of error message
    }

    char* words[NUM_WORDS];
    for (size_t i = 0; i < NUM_WORDS; ++i) {
        words[i] = malloc(WORD_LEN + 1);
        if (words[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for words[%zu]\n", i);
            return 1;
        }
    }

    populate_words("words5.txt", words);

    // Print the first 10 words as a sanity check
    for (size_t i = 0; i < 10; ++i) {
        printf("Word %zu: '%s'\n", i, words[i]);
    }

    // Free memory
    for (size_t i = 0; i < NUM_WORDS; ++i) {
        free(words[i]);
    }

    return 0;
}