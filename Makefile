# Makefile

FILES	= Lexer.cpp Parser.cpp
CC	= g++
CFLAGS	= -std=c++11 -Wno-write-strings -Wno-deprecated-register

test:		$(FILES)
		$(CC) $(CFLAGS) $(FILES) -o test

Lexer.cpp:	Lexer.l 
		flex Lexer.l

Parser.cpp:	Parser.y Lexer.cpp
		bison Parser.y

clean:
		rm -f *.o *~ Lexer.cpp Lexer.h Parser.cpp Parser.h test