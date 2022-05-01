#include "calculator.h"

#include <iostream>
#include <string>

int main()
{
	std::cout << "Enter a simple arithmetic expression to be evaluated per line,\n";
	std::cout << "the supported operators include: +, -, *, /, ^, (, ).\n";
	std::cout << "(Example: -30 + (20 - 1) * 21)\n";
	std::cout << "Enter \"quit\" to exit\n";

	std::string expression;

	try
	{
		while (std::getline(std::cin, expression), expression != "quit")
		{
			Number result = CalculateExpression(expression);
			std::cout << result.value() << std::endl;
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';

		std::cerr << "Press Enter to exit\n";
		std::cin.get();
	}
	
	return 0;
}