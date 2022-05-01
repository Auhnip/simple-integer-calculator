#include "token.h"

const Operator& Operator::None()
{
	static Operator none(NONE);
	return none;
}

const Operator& Operator::Add()
{
	static Operator add(ADD);
	return add;
}

const Operator& Operator::Subtract()
{
	static Operator subtract(SUBTRACT);
	return subtract;
}

const Operator& Operator::Multiply()
{
	static Operator multiply(MULTIPLY);
	return multiply;
}

const Operator& Operator::Divide()
{
	static Operator divide(DIVIDE);
	return divide;
}

const Operator& Operator::Power()
{
	static Operator power(POWER);
	return power;
}

const Operator& Operator::LeftScope()
{
	static Operator left_scope(LEFT_SCOPE);
	return left_scope;
}

const Operator& Operator::RightScope()
{
	static Operator right_scope(RIGHT_SCOPE);
	return right_scope;
}

int Operator::InsideWeight() const
{
	static int weight[8] = {0, 3, 3, 5, 5, 7, 1, 8};

	return weight[operation_];
}

int Operator::OutsideWeight() const
{
	static int weight[8] = {0, 2, 2, 4, 4, 6, 8, 1};

	return weight[operation_];
}

Number Operator::Execute(const Number& lhs, const Number& rhs) const
{
	switch (operation_)
	{
	case ADD:
		return Number(lhs.value() + rhs.value());
	case SUBTRACT:
		return Number(lhs.value() - rhs.value());
	case MULTIPLY:
		return Number(lhs.value() * rhs.value());
	case DIVIDE:
		return Number(lhs.value() / rhs.value());
	case POWER:
		return Number(Power(lhs.value(), rhs.value()));
	default:
		break;
	}
	return lhs;
}

Number::value_type Operator::Power(Number::value_type lhs, Number::value_type rhs)
{
	if (rhs < 0)
		throw PowerArgumentError(rhs, "calculate power error");
	
	Number::value_type sum = 1;
	while (rhs)
	{
		if (rhs & 0x1) sum *= lhs;
		
		rhs >>= 1;
		lhs *= lhs;
	}
	
	return sum;
}

bool operator==(const Token& lhs, const Token& rhs)
{
	if (&lhs == &rhs)
		return true;
	
	if (lhs.is_digit() != rhs.is_digit())
		return false;
	
	if (lhs.is_digit())
	{
		return dynamic_cast<const Number&>(lhs).value() == dynamic_cast<const Number&>(rhs).value();
	}
	
	return dynamic_cast<const Operator&>(lhs).operation() == dynamic_cast<const Operator&>(rhs).operation();
}