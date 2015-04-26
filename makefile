all: main

main: main.o Rows.o stringAlias.o Indexed.o analyze.o tokenize.o types.o
	g++ main.o Rows.o stringAlias.o Indexed.o analyze.o tokenize.o types.o -o analyze

main.o: main.cpp
	g++ -c main.cpp
    
Rows.o: Rows.cpp
	g++ -c Rows.cpp
    
stringAlias.o: stringAlias.cpp
	g++ -c stringAlias.cpp
    
Indexed.o: Indexed.cpp
	g++ -c Indexed.cpp

analyze.o: analyze.cpp
	g++ -c analyze.cpp

tokenize.o: tokenize.cpp
	g++ -c tokenize.cpp
    
types.o: types.cpp
	g++ -c types.cpp

clean:
	rm *.o
