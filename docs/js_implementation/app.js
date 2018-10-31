const cTable = require('console.table')

var Matrix = require('./Matrix.js')
var Image = require('./Image.js')

var image = new Image('tiny.jpg', function(pixels) {
    pixels.print()

    let kernel = new Matrix(3, 3)
    kernel.data[0][1] = -1
    kernel.data[2][1] = 1
    kernel.data[1][0] = -1
    kernel.data[1][1] = 0
    kernel.data[1][2] = 1
    kernel.print()

    let test = Matrix.convolve(pixels, kernel)
    test.print()
})


// ### DONE ###
// normalization : crop + colors
// array of pixels

// ### TO DO ###
// for each pixel => Gradient
// for each 8x8 pixels => HoG