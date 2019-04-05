# face-detection

![Screenshot](https://raw.githubusercontent.com/thdoteo/face-detection/master/docs/screenshot.png)  

Simple C++ program to detect human faces in an image.
Inspired by [this very interesting article](https://medium.com/@ageitgey/machine-learning-is-fun-part-4-modern-face-recognition-with-deep-learning-c3cffc121d78).

## Usage

Dependencies: `SDL2` and `SDL2_image`.  

1. Clone this repository with `git clone git@github.com:thdoteo/FaceDetection.git`.
2. Compile the project by running the command `make` in the project folder.
3. Execute the program with `./FaceDetection [path]`.

## To-Do

1. Improve the representation of HOGs on GUI
2. Add webcam as input
3. Improve performances and efficiency
4. Implement sliding window method
5. Create the NN and train it to recognize faces