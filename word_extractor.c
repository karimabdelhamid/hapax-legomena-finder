/**
 * Word extractor tool.  Do not modify this file
 */

#include <stdio.h>
#include <stdlib.h> // for malloc(), free()
#include <string.h> // for strerror()
#include <errno.h>
#include <ctype.h> // for isalpha()

#include "word_extractor.h"


/**
 * A tool to extract the words from a document.
 *
 * This code is provided as a tool for you, but you should not have
 * to change this file at all.
 */


/** forward declarations */
static char *scanForNextWord_(struct WordExtractor *we);
static int getNextChar_(struct WordExtractor *we);


/**
 * Create a WordExtractor which will read its words from
 * the supplied file.  A FileNotFoundException is thrown
 * if anything goes wrong.
 */
struct WordExtractor *
weCreateExtractor(char *filename, int maxletters)
{
	struct WordExtractor *we;
	FILE *in;

	/* try opening the file before anything else so that we don't
	 * have a memory leak if this fails */
	in = fopen(filename, "r");
	if (in == NULL) {
		fprintf(stderr, "Cannot open input file '%s' : %s\n",
				filename, strerror(errno));
		return NULL;
	}

	we = (struct WordExtractor *) malloc(sizeof(struct WordExtractor));

	we->in = in;
	we->hasSearchedForNextWord = 0;
	we->reachedEOF = 0;
	we->pushedChar = 0;
	we->pendingWord = (char *) malloc(maxletters + 1);
	we->pendingWord[0] = 0;
	we->pendingWordLen = 0;
	we->pendingWordMax = maxletters;

	return we;
}

/**
 * Determines whether or not there are any more words in the
 * file.  Useful as a means to check whether one should stop
 * iterating over all of the words
 *
 * @return whether or not there are any more words to read
 */
int
weHasMoreWords(struct WordExtractor *we)
{
	if (we->hasSearchedForNextWord == 0) {
		scanForNextWord_(we);
		we->hasSearchedForNextWord = 1;
	}

	if ((we->hasSearchedForNextWord == 1) && (we->pendingWordLen == 0)) {
		return 0;
	}

	return 1;
}

/**
 * Reads the next part of the file to determine what the next
 * "word" might be.  A "word" is defined as a series of consecutive
 * characters made up of letters, hyphens, apostrophes or underscores.
 *
 * @return the next word in the file, or NULL if there are no more
 */
char *
weGetNextWord(struct WordExtractor *we)
{
	char * nextWord = NULL;

	if ( ! weHasMoreWords(we) ) {
		return NULL;
	}

	/* hand out a pointer to the word we have stored */
	nextWord = we->pendingWord;
	we->hasSearchedForNextWord = 0;

	/* we now have no allocated word */
	we->pendingWordLen = 0;

	return nextWord;
}

/**
 * Clean up and deallocate
 */
void
weDeleteExtractor(struct WordExtractor *we)
{
	fclose(we->in);
	free(we->pendingWord);
	free(we);
}

/**
 * Remember a character for later
 */
static void
pushChar_(struct WordExtractor *we, int c)
{
	we->pushedChar = c;
}

/**
 * Get the next logical character in the file.
 */
static int
getNextChar_(struct WordExtractor *we)
{
	int nextChar;

	if (we->reachedEOF == 1)
		return (-1);

	if (we->pushedChar != 0) {
		nextChar = we->pushedChar;
		we->pushedChar = 0;
		return nextChar;
	}

	nextChar = fgetc(we->in);

	if (nextChar < 0)
		we->reachedEOF = 1;
	return nextChar;
}

/**
 * Determine where the next "word" begins and ends.  Called by
 * the getNextWord() method above to do the actual work.
 *
 * SEE ALSO getNextWord()
 */
static char *
scanForNextWord_(struct WordExtractor *we)
{
	// define some constants for readability below
	const int S_SKIP_LEADING = 0;
	const int S_IN_LETTERS   = 1;
	const int S_IN_OVERFLOW  = 2;

	int state = S_SKIP_LEADING;
	int aChar;

	we->pendingWordLen = 0;
	while ((aChar = getNextChar_(we)) > 0) {
		if (state == S_SKIP_LEADING) {
			// if the character is not  letter, skip to next read
			if ( ! isalpha(aChar))
				continue;

			state = S_IN_LETTERS;
			we->pendingWord[we->pendingWordLen++] = (char) aChar;

		} else if ( isalpha(aChar)
					|| aChar == '-' || aChar == '_' || aChar == '\'') {
			// if we have not overflowed the buffer, save the letters
			if (we->pendingWordLen < we->pendingWordMax) {
				we->pendingWord[we->pendingWordLen++] = (char) aChar;
			} else if (state != S_IN_OVERFLOW) {
				state = S_IN_OVERFLOW;
				we->pendingWord[we->pendingWordLen] = '\0';
				fprintf(stderr, "Warning: word beginning '%s' overflows"
						" length %d buffer\n",
						we->pendingWord, we->pendingWordMax);
				fprintf(stderr, "       : Ignoring remaining characters!\n");
			}

		} else {
			pushChar_(we, aChar);
			we->pendingWord[we->pendingWordLen] = '\0';
			return we->pendingWord;
		}
	}

	/** we have reached EOF, so return NULL */
	return NULL;
}

