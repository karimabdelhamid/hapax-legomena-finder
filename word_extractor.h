/**
 * Word extractor tool.  Do not modify this file
 */

#ifndef	__WORD_EXTRACTOR_HEADER__
#define	__WORD_EXTRACTOR_HEADER__

/**
 * A tool to extract the words from a document.
 *
 * This code is provided as a tool for you, but you should not have
 * to change this file at all.
 */

struct WordExtractor {
	FILE *in;
	int hasSearchedForNextWord;
	int reachedEOF;
	char *pendingWord;
	int pendingWordMax;
	int pendingWordLen;
	int pushedChar;
};

// Create an extractor based on a file to read
struct WordExtractor *weCreateExtractor(char *filename, int maxletters);

/**
 * Determines whether or not there are any more words in the
 * file.  Useful as a means to check whether one should stop
 * iterating over all of the words
 *
 * Returns whether or not there are any more words to read
 */
int weHasMoreWords(struct WordExtractor *we);

/**
 * Reads the next part of the file to determine what the next
 * "word" might be.  A "word" is defined as a series of consecutive
 * characters made up of letters, hyphens, apostrophes or underscores.
 *
 * Returns the next word in the file, or NULL if there are no more
 */
char *weGetNextWord(struct WordExtractor *we);

/**
 * Clean up and deallocate
 */
void weDeleteExtractor(struct WordExtractor *we);

#endif
