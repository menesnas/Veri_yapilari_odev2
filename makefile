all : derle calistir

derle:
	g++ -I ./include/ -o ./lib/Dugum.o -c ./src/Dugum.cpp
	g++ -I ./include/ -o ./lib/Yigin.o -c ./src/Yigin.cpp
	g++ -I ./include/ -o ./lib/Avlagaci.o -c ./src/Avlagaci.cpp
	g++ -I ./include/ -o ./bin/program ./lib/Dugum.o ./lib/Yigin.o ./lib/Avlagaci.o ./src/main.cpp

calistir:
	./bin/program