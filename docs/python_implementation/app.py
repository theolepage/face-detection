# Imports
import sys, numpy, math, time, cv2
from Matrix import Matrix
from Matrix import Cell
from Matrix import Block
from Matrix import Pixel

# Settings
cellSize = 8
startTime = time.time()

def algo(image):
    # ----------------------------------------------
    # Step 1
    # Load image and preprocessing
    # ----------------------------------------------

    image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    print()
    print("Step 1 : Load image and preprocessing")

    # ----------------------------------------------
    # Step 2
    # Compute gradient for each pixel
    # ----------------------------------------------

    height = image.shape[0] - image.shape[0] % cellSize
    width = image.shape[1] - image.shape[1] % cellSize
    kernel = [-1, 0, 1]
    pixels = Matrix(height, width)

    def get(y, x):
        if y < 0 or y >= height or x < 0 or x >= width:
            return 0
        return int(image[y][x])

    for y in range(height):
        for x in range(width):
            gx = kernel[0] * get(y, x - 1) + kernel[1] * get(y, x) + kernel[2] * get(y, x + 1)
            gy = kernel[0] * get(y - 1, x) + kernel[1] * get(y, x) + kernel[2] * get(y + 1, x)
            magnitude = math.sqrt(gx * gx + gy * gy)
            direction = math.atan2(gy, gx)
            pixels.data[y][x] = Pixel(y, x, magnitude, direction)

    print("Step 2 : Compute gradient for each pixel")

    # ----------------------------------------------
    # Step 3
    # Compute histogram of gradients in 8x8 cells
    # ----------------------------------------------

    cells = []
    for y in range(0, height, cellSize):
        cells.append([])
        for x in range(0, width, cellSize):
            tmp = []
            for j in range(y, y + cellSize):
                for i in range(x, x + cellSize):
                    tmp.append(pixels.data[j][i])
            c = Cell(y, x, tmp)
            cells[y // cellSize].append(c)

    print("Step 3 : Compute histogram of gradients in 8x8 cells")

    # ----------------------------------------------
    # Step 4
    # 16×16 block normalization
    # ----------------------------------------------

    blocks = []
    for y in range(0, (height - 1) // cellSize):
        blocks.append([])
        for x in range(0, (width - 1) // cellSize):
            cellsForTheBlock = []
            cellsForTheBlock.append(cells[y][x])
            cellsForTheBlock.append(cells[y][x + 1])
            cellsForTheBlock.append(cells[y + 1][x])
            cellsForTheBlock.append(cells[y + 1][x + 1])
            b = Block(y, x, cellsForTheBlock)
            blocks[y].append(b)

    print("Step 4 : 16×16 block normalization")

    # ----------------------------------------------
    # Step 5
    # Sliding window and compute HOG feature vector
    # ----------------------------------------------

    def getFeatureVectorAt(y, x):
        tmp = []
        for y in range(y // cellSize, y // cellSize + 7):
            for x in range(x // cellSize, x // cellSize + 7):
                for value in blocks[y][x].hog:
                    tmp.append(value)
        return tmp

    for y in range(0, height - height % 64, 64):
        for x in range(0, width - width % 64, 64):
            getFeatureVectorAt(y, x)
            # so classifier ???

    print("Step 5 : Sliding window and compute HOG feature vector")
    print("Done in", round(time.time() - startTime, 4), "s")
    print()



cam = cv2.VideoCapture(0)
while True:
    ret_val, frame = cam.read()
    frame = cv2.flip(frame, 1)
    if cv2.waitKey(1) == 13:
        cv2.imshow('FaceDetection', frame)
        algo(frame)
    cv2.imshow('Webcam', frame)
cv2.destroyAllWindows()



# 1
# Train a SVM with positive and negative tests
# Train with 64x64 HOG centered on face
# https://pythonprogramming.net/linear-svc-example-scikit-learn-svm-python/
# http://note.sonots.com/SciSoftware/haartraining.html
# https://coding-robin.de/2013/07/22/train-your-own-opencv-haar-classifier.html

# 2
# Optimize : efficient and fast (< 1s)