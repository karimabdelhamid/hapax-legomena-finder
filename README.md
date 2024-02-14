Hapax Legomena Finder
This repository contains a Hapax Legomena Finder, a tool developed as a part of the CIS*2520 course at the University of Guelph. It's designed to process textual data to find unique words, known as hapax legomena, which occur only once within a document.

What is a Hapax Legomenon?
A hapax legomenon is a word that appears only once within a context, typically within the works of an author or in a single text. Identifying hapax legomena can be significant in various fields such as linguistics, literary analysis, and natural language processing.

Program Functionality
The tool operates via the command line and accepts multiple data files as input. It provides the functionality to list all unique words in the document(s) by processing each word and keeping a count of occurrences.

Usage
php
Copy code
hapax [<options>] <datafile> [ <datafile> ...]
Options
-d : Print out all data loaded before printing hapax legomena.
-h : Help menu.
-l <N> : Print hapax legomena of length <N>. If not specified, all hapax legomena are printed.
Sample Output
When running the program, the output will display the total word count and a list of hapax legomena from the input file(s). For example:

csharp
Copy code
$ ./hapax smalldata.txt 
Total word count 10
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
Files Included
Parser: A tool to extract words from text files.
Linked List: Data structure to hold and manage the words.
Main Program: The driver code that integrates all components and executes the command-line instructions.
Makefile: Used for compiling the project with make.
Source C Tools
word_extractor.h & word_extractor.c: For parsing words out of text files.
LLNode.h & LLNode.c: A linked list implementation.
word_tally.h & word_tally.c: The core functionality for tallying word occurrences.
hapax_main.c: The main file which utilizes the word tally system and linked lists to find and display hapax legomena.
Sample Data Files
smalldata.txt: A simple text file to demonstrate the program's functionality.
jabberwocky.txt: The famous poem from Alice in Wonderland.
*-output.txt: Generated outputs when the program is executed with sample text files.
Building and Running
Compile the program using the provided makefile:

go
Copy code
make
Run the program with:

php
Copy code
./hapax <options> <datafile>
Authors
Karim Abdelhamid - YourGitHubUsername
Acknowledgments
This project was part of an academic assignment for the CIS*2520 Data Structures course at the University of Guelph.
All code was written by the author, building upon initial code skeletons and guidelines provided by the course instructors.
Academic Integrity
This project is posted for demonstration purposes only. Any academic use of this code must adhere to the University of Guelph's academic integrity policies and any other applicable academic integrity guidelines.

