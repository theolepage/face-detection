CC = gcc
BIN = FaceDetection
SRC = src/*.c src/*/*.c
CFLAGS = -Wall -Wextra -std=c99

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(BIN) -lSDL2 -lSDL2_image -lm

clean:
	rm -rf $(BIN)
