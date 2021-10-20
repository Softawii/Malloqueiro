SOURCE_FOLDER = src
OUTPUT_FOLDER = out
MALLOQUEIRO_FOLDER = Malloqueiro
MALLOQUEIRO_OUTPUT_FOLDER = ${OUTPUT_FOLDER}/${MALLOQUEIRO_FOLDER}
MALLOQUEIRO_SOURCE_FOLDER = ${SOURCE_FOLDER}/${MALLOQUEIRO_FOLDER}
LIB_FOLDER = lib
CXXFLAGS = -O3 -Wall
CXX = g++

all: clean setup compile run

clean:
	@echo "----------------- Cleaning output folder"
	rm -rf $(OUTPUT_FOLDER)/*
	rm -rf $(LIB_FOLDER)/*

setup:
	@echo "----------------- Setup"
	@if [ ! -d "out/Malloqueiro/" ]; then  \
		echo "out/Malloqueiro/ folder not found, creating folder and subfolders"; \
		mkdir -p "out/Malloqueiro/"; \
    fi 

compile: library
	@echo "----------------- Compiling program"
	$(CXX) $(SOURCE_FOLDER)/Program.cpp -o $(OUTPUT_FOLDER)/Program.out $(CXXFLAGS) -L${MALLOQUEIRO_OUTPUT_FOLDER}/ -lmalloqueiro

library: setup
	@echo "----------------- Linking libraries"
	$(CXX) -c ${MALLOQUEIRO_SOURCE_FOLDER}/Malloqueiro.cpp -o ${MALLOQUEIRO_OUTPUT_FOLDER}/Malloqueiro.o
	$(CXX) -c ${MALLOQUEIRO_SOURCE_FOLDER}/Gerency/MalloqueiroGerency.cpp -o ${MALLOQUEIRO_OUTPUT_FOLDER}/MalloqueiroGerency.o

	ar rvs ${MALLOQUEIRO_OUTPUT_FOLDER}/libmalloqueiro.a \
		${MALLOQUEIRO_OUTPUT_FOLDER}/Malloqueiro.o \
		${MALLOQUEIRO_OUTPUT_FOLDER}/MalloqueiroGerency.o

	gcc -shared -o ${LIB_FOLDER}/malloqueiro.so ${MALLOQUEIRO_OUTPUT_FOLDER}/libmalloqueiro.a

run: compile
	@echo "----------------- Running program"
	$(OUTPUT_FOLDER)/Program.out