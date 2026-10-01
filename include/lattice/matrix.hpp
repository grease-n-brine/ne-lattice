#pragma once

#include <vector>
#include <stdexcept>
#include <cassert>
#include <iostream>

#include <lattice/core/exceptions.hpp>

namespace ne_pp::lattice {
class Matrix {
    private:
        std::vector<double> data_;
        size_t rows_;
        size_t cols_;

    public:
        Matrix(size_t rows, size_t cols)
        : rows_(rows), cols_(cols), data_(rows * cols, 0.0) {
            if (rows <= 0 || cols <= 0) {
                throw LatticeException("Matrix dimensions must be greater than zero");
            }
        }

        Matrix(size_t rows, size_t cols, std::vector<double>& data)
        : rows_(rows), cols_(cols), data_(data) {
            if (rows <= 0 || cols <= 0) {
                throw LatticeException("Matrix dimensions must be greater than zero");
            }
            if (data.size() != rows * cols) {
                throw LatticeDimensionMismatchException(
                    "Provided data size (" + std::to_string(data.size()) +
                    ") does not match Lattice dimensions"
                );
            }
        }

        size_t rows() const {
            return rows_;
        }

        size_t cols() const {
            return cols_;
        }

        double& operator()(size_t r, size_t c) {
            if (r >= rows_ && c >= cols_) {
                throw LatticeOutOfBoundsException("Matrix index out of bounds");
            }

            return data_[r * cols_ + c];
        }

        const double& operator()(size_t r, size_t c) const {
            if (r >= rows_ && c >= cols_) {
                throw LatticeOutOfBoundsException("Matrix index out of bounds");
            }

            return data_[r * cols_ + c];
        }

        Matrix operator*(const Matrix& other) const {
            if (this->cols_ != other.rows_) {
                throw LatticeDimensionMismatchException("Dimension mismatch (multiplication)");
            }
            Matrix result(this->rows_, other.cols_);

            for (size_t i = 0; i < this->rows_; ++i) {
                for (size_t j = 0; j < other.cols_; ++j) {
                    double sum = 0.0;

                    for (size_t k = 0; k < this->cols_; ++k) {
                        sum += (*this)(i, k) * other(k, j);
                    }
                    result(i, j) = sum;
                }
            }
            return result;
        }

        Matrix operator+(const Matrix& other) {
            if (this->cols_ != other.rows_) {
                throw LatticeDimensionMismatchException("Dimension mismatch (addition)");
            }
            Matrix result(this->rows_, this->cols_);

            for (size_t i = 0; i < data_.size(); ++i) {
                result.data_[i] = this->data_[i] + other.data_[i];
            }
            return result;
        }

        Matrix operator-(const Matrix& other) {
            if (this->cols_ != other.rows_) {
                throw LatticeDimensionMismatchException("Dimension mismatch (subtraction)");
            }
            Matrix result(this->rows_, this->cols_);

            for (size_t i = 0; i < data_.size(); ++i) {
                result.data_[i] = this->data_[i] - other.data_[i];
            }
            return result;
        }

        void print() const {
            for (size_t i = 0; i < rows_; ++i) {
                for (size_t j = 0; j < cols_; ++j) {
                    std::cout << (*this)(i, j) << "\t";
                }
                std::cout << "\n";
            }
        }
};
}