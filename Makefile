SRC=./src/main.cpp
BUILD=./build/main
DATA=./data/peppers.pgm
OUTPUT_DIR=./out/
CUT_COUNT=58
all: compile run
compile:
	g++ $(SRC) -o $(BUILD)
run:
	$(BUILD) $(DATA) $(CUT_COUNT) $(OUTPUT_DIR)
clean:
	rm -f $(BUILD)
