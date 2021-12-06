SOURCE_FOLDER = src
OUTPUT_FOLDER = out
MALLOQUEIRO_FOLDER = Malloqueiro
MALLOQUEIRO_OUTPUT_FOLDER = ${OUTPUT_FOLDER}/${MALLOQUEIRO_FOLDER}
MALLOQUEIRO_SOURCE_FOLDER = ${SOURCE_FOLDER}/${MALLOQUEIRO_FOLDER}
LIB_FOLDER = lib
CXXFLAGS = -O3 -Wall -std=c++17
CXX = g++
DEBUG =

all: clean setup compile run

test: CXXFLAGS += -DTEST
test: clean setup compile
	@echo "----------------- Running tests"
	$(OUTPUT_FOLDER)/Tests.out

benchmark: CXXFLAGS += -DTEST
benchmark: clean setup compile
	@echo "----------------- Running tests"
	./benchmark.sh

clean:
	@echo "----------------- Cleaning output folder"
	rm -rf $(OUTPUT_FOLDER)/*
	rm -rf $(LIB_FOLDER)/*
	rm -rf ./resultados/*

setup:
	@echo "----------------- Setup"
	@if [ ! -d "out/Malloqueiro/" ]; then  \
		echo "out/Malloqueiro/ folder not found, creating folder and subfolders"; \
		mkdir -p "out/Malloqueiro/"; \
    fi
	@if [ ! -d "lib/" ]; then  \
		echo "lib/ folder not found, creating folder"; \
		mkdir -p "lib/"; \
    fi
	@if [ ! -d "resultados/" ]; then  \
		echo "resultados/ folder not found, creating folder"; \
		mkdir -p "resultados/"; \
    fi

compile: library
	@echo "----------------- Compiling program"
	$(CXX) $(SOURCE_FOLDER)/Program.cpp -o $(OUTPUT_FOLDER)/Program.out $(CXXFLAGS) -L${MALLOQUEIRO_OUTPUT_FOLDER}/ -lmalloqueiro
	$(CXX) $(SOURCE_FOLDER)/Tests.cpp -o $(OUTPUT_FOLDER)/Tests.out $(CXXFLAGS) -L${MALLOQUEIRO_OUTPUT_FOLDER}/ -lmalloqueiro
	$(CXX) $(SOURCE_FOLDER)/Benchmark.cpp -o $(OUTPUT_FOLDER)/Benchmark.out $(CXXFLAGS) -L${MALLOQUEIRO_OUTPUT_FOLDER}/ -lmalloqueiro

library: setup
	@echo "----------------- Linking libraries"
	$(CXX) -c ${MALLOQUEIRO_SOURCE_FOLDER}/Malloqueiro.cpp -o ${MALLOQUEIRO_OUTPUT_FOLDER}/Malloqueiro.o $(CXXFLAGS)
	$(CXX) -c ${MALLOQUEIRO_SOURCE_FOLDER}/Management/MalloqueiroManagement.cpp -o ${MALLOQUEIRO_OUTPUT_FOLDER}/MalloqueiroManagement.o $(CXXFLAGS)
	$(CXX) -c ${MALLOQUEIRO_SOURCE_FOLDER}/LowLevel/MalloqueiroLowLevel.cpp -o ${MALLOQUEIRO_OUTPUT_FOLDER}/MalloqueiroLowLevel.o $(CXXFLAGS)

	ar rvs ${MALLOQUEIRO_OUTPUT_FOLDER}/libmalloqueiro.a \
		${MALLOQUEIRO_OUTPUT_FOLDER}/Malloqueiro.o \
		${MALLOQUEIRO_OUTPUT_FOLDER}/MalloqueiroManagement.o \
		${MALLOQUEIRO_OUTPUT_FOLDER}/MalloqueiroLowLevel.o

	rm -rf ${MALLOQUEIRO_OUTPUT_FOLDER}/*.o

run: compile
	@echo "----------------- Running program"
	$(OUTPUT_FOLDER)/Program.out