#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "token.h"
#include "stack.h"
#include "scanner.h"

Number CalculateExpression(const std::string& expression);

class GrammerError: public std::runtime_error
{
public:
	GrammerError(const char* message): std::runtime_error(message) {}
};

#endif