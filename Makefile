CC = g++
BIN = FaceDetection
SRC = src/*.cpp src/*/*.cpp
CFLAGS = -Wall -Wextra

SDL2 = -lSDL2 -lSDL2_image
MATH = -lm

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(BIN) $(SDL2) $(MATH)

clean:
	rm -rf $(BIN)
