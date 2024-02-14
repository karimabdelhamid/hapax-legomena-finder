
##
## This file builds assignment 1
##

##
## Some macros (makefile 'variables') are defined by default
## by make(1).  The ones relevant to C compiling are:
##  CC     : the name of the compiler (defaults to system compiler)
##  CFLAGS : the flags (options) to pass to the compiler
##
## There are similar macros for other languages, for example C++ uses
##  CXX      : the name of the c++ compiler (defaults to system compiler)
##  CXXFLAGS : the flags (options) to pass to the c++ compiler


## explicitly add debugger support to each file compiled
CFLAGS = -g -Wall

## uncomment/change this next line if you need to use a non-default compiler
#CC = cc


##
## We can define variables for values we will use repeatedly below
##

## define the two executables we want to build
HEXE = hapax
WEXE = printwords

## define the set of object files we need to build each executable
HOBJS		= hapax_main.o LLNode.o word_extractor.o word_tally.o
WOBJS		= words_main.o word_extractor.o


##
## TARGETS: below here we describe the target dependencies and rules
##

## top level target -- build all the dependent executables
all : $(HEXE) $(WEXE)

## targets for each executable, based on the object files indicated
$(HEXE) : $(HOBJS)
	$(CC) $(CFLAGS) -o $(HEXE) $(HOBJS)

$(WEXE): $(WOBJS)
	$(CC) $(CFLAGS) -o $(WEXE) $(WOBJS)

## convenience target to remove the results of a build
clean :
	- rm -f $(HOBJS) $(HEXE)
	- rm -f $(WOBJS) $(WEXE)

