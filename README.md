# Hapax Legomena Finder

This repository contains a Hapax Legomena Finder, a command-line tool developed for the CIS*2520 Data Structures course at the University of Guelph. It analyzes textual data to identify unique words, termed 'hapax legomena,' which appear only once within a document.

## Introduction

A hapax legomenon is a term used in the analysis of text for a word that occurs only once within a context: typically a single written work, the works of an author, or the works within a particular genre.

## Program Functionality

This command-line tool reads through one or more text files, counts the occurrence of each word, and lists those that appear only once — the hapax legomena.

### Usage

```bash
hapax [<options>] <datafile> [ <datafile> ...]

### Options

- `-d`: Print out all data loaded before printing hapax legomena.
- `-h`: Help menu.
- `-l <N>`: Print hapax legomena of length `<N>`. If not specified, all hapax legomena are printed.

### Sample Output

Executing the program will display the total word count and a list of unique words from the input file(s). For instance:

$ ./hapax smalldata.txt 
Total word count: 10
Tally loaded
Hapax legomena from file 'smalldata.txt':
    a
    is
    line
    test
    this
    three
    there
    where



### Files and Directories

- `src/`: Contains all the C source files.
- `include/`: Contains all the header files.
- `data/`: Contains sample data files used for testing.
- `Makefile`: For compiling the project.
- `README.md`: This file, describing the project and how to use it.

### Source C Tools

- `word_extractor.h`, `word_extractor.c`: Tools to parse words from text files.
- `LLNode.h`, `LLNode.c`: Implementation of a linked list to hold words.
- `word_tally.h`, `word_tally.c`: Core functionality to tally occurrences of words.
- `hapax_main.c`: Main routine to orchestrate the finding and printing of hapax legomena.

### Sample Data Files

- `smalldata.txt`: A text file containing a small amount of data to demonstrate functionality.
- `jabberwocky.txt`: The famous poem from "Alice in Wonderland".
- `*-output.txt`: Example output files generated by the program.

### Building the Project

Compile the program with the provided Makefile:
make


Execute the program with:
./hapax <options> <datafile>
