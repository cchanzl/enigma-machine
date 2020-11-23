enigma:  main.o enigma.o rotor.o reflector.o plugboard.o
	g++ -g main.o enigma.o rotor.o reflector.o plugboard.o -o enigma

main.o: main.cpp enigma.h
	g++ -Wall -g -c main.cpp

enigma.o: enigma.cpp rotor.h reflector.h enigma.h errors.h
	g++ -Wall -g -c enigma.cpp

rotor.o: rotor.cpp rotor.h enigma.h errors.h
	g++ -Wall -g -c rotor.cpp

reflector.o: reflector.cpp reflector.h enigma.h errors.h
	g++ -Wall -g -c reflector.cpp

plugboard.o: plugboard.cpp plugboard.h enigma.h errors.h
	g++ -Wall -g -c plugboard.cpp


clean:
	rm -f *.o
