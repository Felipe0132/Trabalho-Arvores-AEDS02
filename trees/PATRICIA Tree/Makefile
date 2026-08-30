CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra

SRC_DIR = src
INC_DIR = include
OUT_DIR = src/output

TARGET  = $(OUT_DIR)/patricia
SOURCES = $(SRC_DIR)/PATRICIA.cpp $(SRC_DIR)/main.cpp
HEADERS = $(INC_DIR)/PATRICIA.hpp

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) $(SOURCES) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(OUT_DIR)/patricia
