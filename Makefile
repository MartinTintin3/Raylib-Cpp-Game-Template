UNAME_S = $(shell uname -s)

CXX = clang++
CXXFLAGS = -std=c++20 -O3 -Wall -Wextra -pedantic -Ilib/raylib-cpp/include -Isrc
CXXFLAGS += -Wno-missing-field-initializers -Wno-unused-parameter -Wno-return-type
LDFLAGS = $(shell pkg-config --libs --cflags raylib)

ifeq ($(UNAME_S), Darwin)
    LDFLAGS += -framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa
endif

ifeq ($(UNAME_S), Linux)
    LDFLAGS += -ldl -lpthread
endif

TARGET = game
BIN = bin
SRC = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) $(wildcard src/**/**/*.cpp) $(wildcard src/**/**/**/*.cpp) $(wildcard src/**/**/**/**/*.cpp)
OBJ = $(SRC:.cpp=.o)

.PHONY: all clean dirs

all: dirs $(TARGET) clean

dirs:
	@echo "Dirs..."
	@mkdir -p ./$(BIN)

$(TARGET): $(OBJ)
	@echo "Compiling..."
	@$(CXX) $(LDFLAGS) -o $(BIN)/$(TARGET) $^

%.o : %.cpp
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@echo "Cleaning..."
	@rm -rf $(OBJ)