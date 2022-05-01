#include "scanner.h"

void Scanner::LocateNextToken()
{
	while (index_ != expression_.size())
	{
		if (std::isblank(expression_[index_]))
			++index_;
		else if (std::isdigit(expression_[index_]) || std::strchr("+-*/^()", expression_[index_]))
			break;
		else
		{
			fail_ = true;
			break;
		}
	}

	if (index_ == expression_.size()) end_ = true;
}

void Scanner::ReadNumber()
{
	static Number return_number;

	Number::value_type number = 0;
	uint32_t count = 0;
	while (count <= kNumberMaxLength && std::isdigit(expression_[index_]))
	{
		number *= 10;
		number += expression_[index_] - '0';
		++ index_;
		++ count;
	}

	if (count > kNumberMaxLength)
		fail_ = true;

	LocateNextToken();
	
	return_number.set_value(number);
	
	last_token_ = &return_number;
}

void Scanner::ReadOperator()
{
	static Number zero(0);

	switch (expression_[index_])
	{
	case '+': last_token_ = & Operator::Add(); break;

	case '-':
		if (last_token_ == nullptr || last_token_ == & Operator::LeftScope())
		{
			last_token_ = & zero;
			return;
		}

		last_token_ = & Operator::Subtract();
		break;
	
	case '*': last_token_ = & Operator::Multiply(); break;

	case '/': last_token_ = & Operator::Divide(); break;

	case '^': last_token_ = & Operator::Power(); break;

	case '(': last_token_ = & Operator::LeftScope(); break;

	case ')': last_token_ = & Operator::RightScope(); break;

	default: fail_ = true; break;
	}

	++index_;
	LocateNextToken();
}

const Token& Scanner::NextToken()
{
	if (fail_)
		throw NoNextToken("there isn't a next token");

	if (end_)
	{
		fail_ = true;
		last_token_ = & Operator::None();
		return *last_token_;
	}
	
	if (std::isdigit(expression_[index_]))
		ReadNumber();
	else
		ReadOperator();

	return *last_token_;
}