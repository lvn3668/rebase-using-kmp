makefile:
all: backtranslation
backtranslation: backtranslation.o
				g++ -g -o backtranslation backtranslation.o
backtranslation.o: backtranslation.cpp
				g++ -c -g backtranslation.cpp
  