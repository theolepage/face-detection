CC = g++
BIN = FaceDetection
SRC = src/*.cpp src/*/*.cpp
CFLAGS = -Wall -Wextra

SDL2 = -lSDL2 -lSDL2_image

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(BIN) $(SDL2)

clean:
	rm -rf $(BIN)
