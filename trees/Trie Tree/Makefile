CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra

SRC_DIR = src
INC_DIR = include
OUT_DIR = src/output

TARGET  = $(OUT_DIR)/trie
SOURCES = $(SRC_DIR)/Trie.cpp $(SRC_DIR)/main.cpp
HEADERS = $(INC_DIR)/Trie.hpp

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	@mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) $(SOURCES) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(OUT_DIR)/trie
