#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_tally.h"

/** Function to be passed in to llFree to delete allocated keys */
void deleteKey(LLNode *node, void *userdata)
{
    if (node->key != NULL) {
        free(node->key);
    }
}

/** Delete the contents of all of the word lists */
void deleteWordLists(LLNode **wordListHeads, int maxLen)
{
    for (int i = 0; i <= maxLen; i++) {
        if (wordListHeads[i] != NULL) {
            llFree(wordListHeads[i], deleteKey, NULL);
            wordListHeads[i] = NULL;
        }
    }
}

/** Print out all of the data in a word list */
void printData(char *filename, LLNode *wordListHeads[], int maxLen)
{
    LLNode *node;

    printf("All word count data from file '%s':\n", filename);

    for (int i = 0; i < maxLen; i++) {
        node = wordListHeads[i];
        if (node != NULL) {
            printf("Length %d:\n", i);
            while (node != NULL) {
                printf("    '%s' %d\n", node->key, node->value);
                node = node->next;
            }
        }
    }
}

/** Print out only the hapax legomena in a word list */
void printHapax(char *filename, LLNode *wordListHeads[], int maxLen, int hapaxLength)
{
    if (hapaxLength < 0 || hapaxLength >= maxLen) {
        fprintf(stderr, "Hapax length %d is invalid.\n", hapaxLength);
        return;
    }

    LLNode *node = wordListHeads[hapaxLength];
    printf("Hapax legomena from file '%s' of length %d:\n", filename, hapaxLength);

    while (node != NULL) {
        if (node->value == 1) {
            printf("    '%s'\n", node->key);
        }
        node = node->next;
    }
}

/* Print out the command-line help */
void usage()
{
    fprintf(stderr, "\n");
    fprintf(stderr, "Find and print the hapax legomena in one or more files.\n");
    fprintf(stderr, "A \"hapax legomenon\" is a word that occurs only once in the file\n");

    fprintf(stderr, "\n");
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "    hapax [<options>] <datafile> [ <datafile> ...]\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "-d     : print out all data loaded before printing hapax legomena.\n");
    fprintf(stderr, "-h     : this help. You are looking at it.\n");
    fprintf(stderr, "-l <N> : only print hapax legomena of length <N>.\n");
    fprintf(stderr, "       : If no -l option is given, all hapax legomena are printed.\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Sample command line:\n");
    fprintf(stderr, "    hapax -l 5 smalldata.txt\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "This example would print all words of length 5 that exist in the\n");
    fprintf(stderr, "file \"smalldata.txt\".\n");
    fprintf(stderr, "\n");

    // Exit the program
    exit(1);
}


/**
 * Program mainline
 */

// define the maximum length of word we will look for, and by extension,
// the number of entries that must be in the array of word lists
#define	MAX_WORD_LEN	24

int main(int argc, char **argv)
{
    int shouldPrintData = 0, didProcessing = 0, printHapaxLength = -1;

    // TODO: Allocate an array of list heads of the required size
    LLNode **wordListHeads = malloc(MAX_WORD_LEN * sizeof(LLNode *));
    if (wordListHeads == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for wordListHeads.\n");
        return 1;
    }

    for (int i = 0; i < MAX_WORD_LEN; i++) {
        wordListHeads[i] = NULL;
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-d") == 0) {
                shouldPrintData = 1;
            } else if (strcmp(argv[i], "-h") == 0) {
                usage();
                return 0;
            } else if (strcmp(argv[i], "-l") == 0) {
                // TODO: Set printHapaxLength based on the next argument
                i++;
                if (i < argc) {
                    printHapaxLength = atoi(argv[i]);
                } else {
                    fprintf(stderr, "Error: -l option requires a length argument.\n");
                    return 1;
                }
            } else {
                fprintf(stderr, "Error: Unknown option '%s'\n", argv[i]);
                usage();
                return 1;
            }
        } else {
            // Process the input file
            if (tallyWordsInFile(argv[i], wordListHeads, MAX_WORD_LEN) == 0) {
                fprintf(stderr, "Error: Processing '%s' failed -- exiting\n", argv[i]);
                return 1;
            }

            didProcessing = 1;

            printf("Tally loaded\n");

            // Conditionally print out all the words loaded
            if (shouldPrintData) {
                printData(argv[i], wordListHeads, MAX_WORD_LEN);
            }

            // Print out hapax legomena
            printHapax(argv[i], wordListHeads, MAX_WORD_LEN, printHapaxLength);

            // Clean up memory
            deleteWordLists(wordListHeads, MAX_WORD_LEN);
        }
    }

    if (!didProcessing) {
        fprintf(stderr, "No data processed -- provide the name of a file on the command line\n");
        usage();
        return 1;
    }

    // Clean up remaining memory
    free(wordListHeads);

    return 0;
}