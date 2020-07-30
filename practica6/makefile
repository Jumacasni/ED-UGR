CXX=g++
CXXFLAGS=-I$(INC) -Wall -g
INC=include/
SRC=src/
OBJ=obj/
BIN=bin/

$(BIN)principal: $(OBJ)principal.o $(OBJ)clinvar.o $(OBJ)enfermedad.o $(OBJ)mutacion.o
	$(CXX) -std=c++11 -o $(BIN)principal $(OBJ)principal.o $(OBJ)clinvar.o $(OBJ)enfermedad.o $(OBJ)mutacion.o

$(OBJ)principal.o: $(INC)clinvar.h $(SRC)principal.cpp
	$(CXX) -std=c++11 -c $(CXXFLAGS) -o $(OBJ)principal.o $(SRC)principal.cpp

$(OBJ)mutacion.o: $(INC)mutacion.h $(INC)enfermedad.h $(SRC)mutacion.cpp
	$(CXX) -std=c++11 -c $(CXXFLAGS) -o $(OBJ)mutacion.o $(SRC)mutacion.cpp

$(OBJ)enfermedad.o: $(INC)enfermedad.h $(SRC)enfermedad.cpp
	$(CXX) -std=c++11 -c $(CXXFLAGS) -o $(OBJ)enfermedad.o $(SRC)enfermedad.cpp

$(OBJ)clinvar.o: $(INC)clinvar.h $(INC)mutacion.h $(SRC)clinvar.cpp
	$(CXX) -std=c++11 -c $(CXXFLAGS) -o $(OBJ)clinvar.o $(SRC)clinvar.cpp

clean:
	echo "Limpiando ..."
	rm $(OBJ)*.o

mrproper:
	rm $(BIN)principal