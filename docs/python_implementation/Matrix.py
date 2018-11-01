import math

class Pixel(object):

    def __init__(self, y, x, magnitude, direction):
        self.y = y
        self.x = x
        self.magnitude = magnitude
        self.direction = math.degrees(direction)

class Block(object):

    def __init__(self, y, x, cells):
        self.cells = cells
        self.y = y
        self.x = x
        self.hog = []
        length = 1
        for cell in self.cells:
            for value in cell.hog:
                self.hog.append(value)
                length += value * value
        length = math.sqrt(length)
        for i in range(len(self.hog)):
            self.hog[i] = round(self.hog[i] / length, 2)


class Cell(object):

    def __init__(self, y, x, pixels):
        self.hog = [0, 0, 0, 0, 0, 0, 0, 0, 0]
        self.y = y
        self.x = x
        self.pixels = pixels
        self.computeHOG()

    def computeHOG(self):
        for pixel in self.pixels:
            angle = int(pixel.direction % 180)
            rightValue = pixel.magnitude * (angle % 20) / 20 # right bucket
            leftValue = pixel.magnitude - rightValue # left bucket
            leftAngle = angle - (angle % 20)
            rightAngle = leftAngle + 20
            self.hog[leftAngle // 20 - 1] += round(leftValue)
            self.hog[rightAngle // 20 - 1] += round(rightValue)

class Matrix(object):

    def __init__(self, rows, columns):
        self.data = [0]*rows
        for y in range(rows):
            self.data[y] = [0]*columns

    def get(self, y, x):
        if y < 0 or y >= len(self.data) or x < 0 or x >= len(self.data[0]):
            return 0
        return self.data[y][x]

    def convolve(self, kernel):
        pixels = Matrix(len(self.data), len(self.data[0]))
        for y in range(len(self.data)):
            for x in range(len(self.data[0])):
                gx = kernel[0] * self.get(y, x - 1) + kernel[1] * self.get(y, x) + kernel[2] * self.get(y, x + 1)
                gy = kernel[0] * self.get(y - 1, x) + kernel[1] * self.get(y, x) + kernel[2] * self.get(y + 1, x)
                magnitude = math.sqrt(gx * gx + gy * gy)
                direction = math.atan2(gy, gx)
                pixels.data[y][x] = Pixel(y, x, magnitude, direction)
        return pixels
