enigma:  main.o enigma.o
	g++ -g main.o enigma.o -o enigma

main.o: main.cpp enigma.h
	g++ -Wall -g -c main.cpp

enigma.o: enigma.cpp enigma.h
	g++ -Wall -g -c enigma.cpp

clean:
	rm -f *.o
