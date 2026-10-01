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
};
}