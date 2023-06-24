#include "FileNotOpenException.hpp"

FileNotOpenException::FileNotOpenException(std::string probString) : Exception("File", probString) {
 //derived constructor
}