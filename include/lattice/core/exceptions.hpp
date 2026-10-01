#pragma once

#include <stdexcept>
#include <string>

namespace ne_pp::lattice {
class LatticeException : public std::exception {
    private:
        std::string message;

    public:
        LatticeException(const std:: string& message)
            : message(message) {}
        
        const char* what() const noexcept override {
            return message.c_str();
        }
};

class LatticeDimensionMismatchException : public std::exception {
    private:
        std::string message;

    public:
        LatticeDimensionMismatchException(const std:: string& message)
            : message(message) {}
        
        const char* what() const noexcept override {
            return message.c_str();
        }
};

class LatticeOutOfBoundsException : public std::exception {
    private:
        std::string message;

    public:
        LatticeOutOfBoundsException(const std:: string& message)
            : message(message) {}
        
        const char* what() const noexcept override {
            return message.c_str();
        }
};
}