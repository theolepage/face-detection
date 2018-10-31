CC = g++
BIN = FaceDetection
SRC = src/*.cpp
CFLAGS = -Wall -Wextra

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(BIN)

clean:
	rm -rf $(BIN)
