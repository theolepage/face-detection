var getImagePixels = require("get-pixels")
var Matrix = require('./Matrix.js')

class Pixel {

    constructor(x, y, r, g, b) {
        this.x = x
        this.y = y
        this.intensity = (r + g + b) / (3 * 255)
    }

    computeGradient(top, right, bottom, left) {
        if(top == undefined && left == undefined) {
            console.log(right)
            console.log(bottom)
        }
    }

}

module.exports = class Image {

    constructor(path, callback) {
        this.dimensionsMultipleOf = 4

        this.path = path
        this.callback = callback
        getImagePixels(this.path, this.registerPixels.bind(this))
    }

    registerPixels(error, data) {
        if (!error) {
            this.width = data.shape[0]
            this.height = data.shape[1]
            this.adjustDimensions()

            let matrix = new Matrix(this.width, this.height)
            this.pixels = []
            for(let y = 0; y < this.height; y++) {
                let tmp = []
                for (let x = 0; x < this.width; x++) {
                    let p = new Pixel(x, y, data.get(x, y, 0), data.get(x, y, 1), data.get(x, y, 2))
                    tmp.push(p)
                    matrix.data[y][x] = Math.round((data.get(x, y, 0) + data.get(x, y, 1) + data.get(x, y, 2)) / 3)
                }
                this.pixels.push(tmp)
            }

            this.callback(matrix)
        }
    }

    getMatrix() {

    }

    computePixelsGradient() {
        for (let y = 0; y < this.height; y++) {
            for (let x = 0; x < this.width; x++) {
                let  bottom = undefined
                let top = undefined
                if(y + 1 < this.height) {
                    bottom = this.pixels[y + 1][x]
                }
                if(y - 1 >= 0) {
                    top = this.pixels[y - 1][x]
                }
                this.pixels[y][x].computeGradient(
                    top,
                    this.pixels[y][x + 1],
                    bottom,
                    this.pixels[y][x - 1]
                )
            }
        }
    }

    getPixel(x, y) {
       return this.pixels[y][x];
    }

    adjustDimensions() {
        if(this.width % this.dimensionsMultipleOf != 0) {
            this.width = this.width - (this.width % this.dimensionsMultipleOf)
        }
        if (this.height % this.dimensionsMultipleOf != 0) {
            this.height = this.height - (this.height % this.dimensionsMultipleOf)
        }
    }
}