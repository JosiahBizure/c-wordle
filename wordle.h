#ifndef WORDLE_H
#define WORDLE_H

#include <stddef.h>  // for size_t

#define WORD_LEN 5

typedef enum Color {
    GREEN,
    YELLOW,
    RED
} Color;

/* 
    Checks a single character in the user-entered guess against the answer word.

    Parameters:
        - guess_char: a char in the user's guess word
        - index: the index at which the guess_char is located
        - answer: the target word to compare against

    Return values:
        - GREEN if guess == answer[index]
        - YELLOW if guess is in answer but at a different position
        - RED if guess is not in answer at all
*/
Color check_char(const char guess_char, const size_t index, const char* answer);

/*
    Compares each character in the guess to the target answer word.

    Parameters:
        - guess: a 5-character null-terminated guess word
        - answer: the correct answer word (also 5 characters)
        - results: caller-allocated array of length WORD_LEN to hold Color values

    Notes:
        - The function does not allocate memory.
        - Each results[i] will be set to GREEN, YELLOW, or RED based on match status.
*/
void check_word(const char* guess, const char* answer, Color* results);

#endif