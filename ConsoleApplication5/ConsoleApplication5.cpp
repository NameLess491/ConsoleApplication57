#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
template <typename T>
class Matrix {
private:
    T** data;
    size_t rows;
    size_t cols;
    void allocateMemory() {
        data = new T * [rows];
        for (size_t i = 0; i < rows; ++i) {
            data[i] = new T[cols]();
        }
    }
    void freeMemory() {
        for (size_t i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
public:
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
        allocateMemory();
    }
    ~Matrix() {
        freeMemory();
    }
    void fillRandom(T minVal, T maxVal) {
        srand(static_cast<unsigned>(time(0)));
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = minVal + (rand() % (maxVal - minVal + 1));
            }
        }
    }
    void fillFromInput() {
        std::cout << "Enter elements of the matrix (" << rows << "x" << cols << "):\n";
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cin >> data[i][j];
            }
        }
    }
    void display() const {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cout << std::setw(5) << data[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
    T findMax() const {
        T maxVal = data[0][0];
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (data[i][j] > maxVal) {
                    maxVal = data[i][j];
                }
            }
        }
        return maxVal;
    }
    T findMin() const {
        T minVal = data[0][0];
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (data[i][j] < minVal) {
                    minVal = data[i][j];
                }
            }
        }
        return minVal;
    }
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match for subtraction.");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Invalid matrix dimensions for multiplication.");
        }
        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                for (size_t k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }
    Matrix operator/(T scalar) const {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero is not allowed.");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        allocateMemory();
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    Matrix& operator=(const Matrix& other) {
        if (this == &other) {
            return *this;
        }
        freeMemory();
        rows = other.rows;
        cols = other.cols;
        allocateMemory();
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }
};
int main() {
    Matrix<int> mat1(3, 3);
    mat1.fillRandom(1, 10);
    std::cout << "Matrix 1:\n";
    mat1.display();

    Matrix<int> mat2(3, 3);
    mat2.fillRandom(1, 10);
    std::cout << "Matrix 2:\n";
    mat2.display();
    Matrix<int> sum = mat1 + mat2;
    std::cout << "Sum of matrices:\n";
    sum.display();
    std::cout << "Max element in Matrix 1: " << mat1.findMax() << "\n";
    std::cout << "Min element in Matrix 1: " << mat1.findMin() << "\n";
    return 0;
}