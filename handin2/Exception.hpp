#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <random>

#ifndef EXCEPTIONDEF
#define EXCEPTIONDEF

#include <string>
class Exception	{
	private:
		std::string mTag, mProblem;
	public:
		Exception(std::string tagString, std::string probString);
		void PrintDebug() const;
};

#endif //EXCEPTIONDEF
