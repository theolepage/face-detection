module.exports = class Matrix {

    constructor(rows, cols) {
        this.rows = rows
        this.cols = cols
        this.data = Array(this.rows).fill().map(() => Array(this.cols).fill(0))
    }

    static convolve(matrix, kernel) {
        let result = new Matrix(matrix.rows, matrix.cols)

        for (let y = 0; y < matrix.rows; y++) {
            for (let x = 0; x < matrix.cols; x++) {
                let left = 0
                let right = 0
                let top = 0
                let bottom = 0

                if (y - 1 >= 0) {
                    top = matrix.data[y - 1][x] * kernel.data[0][1]
                }
                if(y + 1 < matrix.rows) {
                    bottom = matrix.data[y + 1][x] * kernel.data[2][1]
                }
                if(x - 1 >= 0) {
                    left = matrix.data[y][x - 1] * kernel.data[1][0]
                }
                if(x + 1 < matrix.cols) {
                    right = matrix.data[y][x + 1] * kernel.data[1][2]
                }
                let horizontal = matrix.data[y][x] * kernel.data[1][1] + left + right
                let vertical = matrix.data[y][x] * kernel.data[1][1] + bottom + top
                result.data[y][x] = Math.round(90 + Math.atan(vertical / horizontal) * 180 / Math.PI)
            }
        }

        return result
    }

    map(func) {
        // Apply a function to every element of matrix
        for (let i = 0; i < this.rows; i++) {
            for (let j = 0; j < this.cols; j++) {
                let val = this.data[i][j];
                this.data[i][j] = func(val, i, j);
            }
        }
        return this;
    }

    static map(matrix, func) {
        // Apply a function to every element of matrix
        return new Matrix(matrix.rows, matrix.cols)
            .map((e, i, j) => func(matrix.data[i][j], i, j));
    }

    static subtract(a, b) {
        if (a.rows !== b.rows || a.cols !== b.cols) {
            console.log('Columns and Rows of A must match Columns and Rows of B.')
            return
        }

        // Return a new Matrix a-b
        return new Matrix(a.rows, a.cols)
            .map((_, i, j) => a.data[i][j] - b.data[i][j])
    }

    add(n) {
        if (n instanceof Matrix) {
            if (this.rows !== n.rows || this.cols !== n.cols) {
                console.log('Columns and Rows of A must match Columns and Rows of B.')
                return
            }
            return this.map((e, i, j) => e + n.data[i][j])
        } else {
            return this.map(e => e + n)
        }
    }

    static multiply(a, b) {
        // Matrix product
        if (a.cols !== b.rows) {
            console.log('Columns of A must match rows of B.')
            return
        }

        return new Matrix(a.rows, b.cols)
            .map((e, i, j) => {
                // Dot product of values in col
                let sum = 0
                for (let k = 0; k < a.cols; k++) {
                    sum += a.data[i][k] * b.data[k][j]
                }
                return sum
            })
    }

    multiply(n) {
        if (n instanceof Matrix) {
            if (this.rows !== n.rows || this.cols !== n.cols) {
                console.log('Columns and Rows of A must match Columns and Rows of B.')
                return
            }

            // hadamard product
            return this.map((e, i, j) => e * n.data[i][j])
        } else {
            // Scalar product
            return this.map(e => e * n)
        }
    }

    print() {
        console.table(this.data)
        return this
    }

}