#ifndef WORDLE_H
#define WORDLE_H

#include <stddef.h>  // for size_t

#define WORD_LEN 5
#define NUM_WORDS 5196
#define MAX_ATTEMPTS 6

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

/*
    Populates user-provided array of string buffers with 5-letter words from file.

    Parameters:
        - file_name: name of file containing one word per line
        - words: caller-allocated array of NUM_WORDS pointers, where each words[i] points to
                 a buffer of at least WORD_LEN + 1 bytes (assumed, no input validation is done!)

    Notes:
        - This function does not allocate any memory.
        - Caller must free each words[i] after use.
        - Only the first NUM_WORDS lines in the file will be read.
*/
void populate_words(const char* file_name, char** words);

/*
    Selects a random word from an array of user-provided words.

    Parameters:
        - words: caller-allocated array of NUM_WORDS pointers, where each words[i] points to
                 a buffer of at least WORD_LEN + 1 bytes (assumed, no input validation is done!)

    Return values:
        - A pointer to one of the strings in the 'words' array
*/
char* random_word(char** words);

/*
    Helper function for random word generation. Sets the seed.
*/
void set_seed();

/*
    Runs the main Wordle game loop.

    Parameters:
        - answer: the target 5-letter word
        - word_len: length of the word (typically 5)

    Notes:
        - Allows MAX_ATTEMPTS guesses
        - Prompts the user and prints color-coded feedback
        - Ends on win or max attempts
*/
void game_loop(const char* answer, size_t word_len, char** words);

/*
    Verifies that an entered guess is a part of the English language.
*/
int is_valid_word(const char* guess, char** words);

#endif