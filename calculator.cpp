#include "calculator.h"

inline void ExecuteOperationOnce(Stack<Number>& numbers, Stack<Operator>& operators)
{
	Number right_number = numbers.top();
	numbers.pop();
	
	Number left_number = numbers.top();
	numbers.pop();

	numbers.push(operators.top().Execute(left_number, right_number));
	operators.pop();

}

Number CalculateExpression(const std::string& expression)
{
	Scanner scanner(expression);
	Stack<Number> numbers;
	Stack<Operator> operators;

	operators.push(Operator::None());
	while (scanner.HasNextToken())
	{
		const Token& token = scanner.NextToken();
		if (token.is_digit())
		{
			numbers.push(dynamic_cast<const Number&>(token));
			continue;
		}

		const Operator& op = dynamic_cast<const Operator&>(token);

		if (operators.top().InsideWeight() < op.OutsideWeight())
		{
			operators.push(op);
		}
		else
		{
			while (operators.top().InsideWeight() > op.OutsideWeight())
			{
				if (numbers.size() < 2)
					throw GrammerError("fail to get 2 numbers to calculate");
				
				ExecuteOperationOnce(numbers, operators);
			}

			if (operators.top().InsideWeight() == op.OutsideWeight())
				operators.pop();
			else
				operators.push(op);
		}
	}
	
	if (numbers.size() != 1)
		throw GrammerError("grammer error with too many numbers");
	
	return numbers.top();
}