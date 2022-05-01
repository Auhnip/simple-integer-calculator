#ifndef TOKEN_H_
#define TOKEN_H_

#include <cstdint>
#include <stdexcept>

class Token
{
public:
	bool is_digit() const { return is_digit_; }
	virtual ~Token() {}
protected:
	Token(bool is_digit): is_digit_(is_digit) {}
private:
	bool is_digit_;
};

class Number: public Token
{
public:
	using value_type = std::int64_t;
	value_type value() const { return value_; }
	void set_value(value_type value) { value_ = value; }

	Number(): Token(true), value_(0) {}
	explicit Number(value_type value): Token(true), value_(value) {}
	~Number() = default;

private:
	value_type value_;
};

class Operator: public Token
{
public:
	~Operator() = default;

	int InsideWeight() const;
	int OutsideWeight() const;

	Number Execute(const Number& lhs, const Number& rhs) const;

	int operation() const { return operation_; }

	static const Operator& None();
	static const Operator& Add();
	static const Operator& Subtract();
	static const Operator& Multiply();
	static const Operator& Divide();
	static const Operator& Power();
	static const Operator& LeftScope();
	static const Operator& RightScope();

private:
	static constexpr int NONE = 0;
	static constexpr int ADD = 1;
	static constexpr int SUBTRACT = 2;
	static constexpr int MULTIPLY = 3;
	static constexpr int DIVIDE = 4;
	static constexpr int POWER = 5;
	static constexpr int LEFT_SCOPE = 6;
	static constexpr int RIGHT_SCOPE = 7;

	Operator(): Token(false), operation_(NONE) {}
	Operator(int operation): Token(false), operation_(operation) {}

	static Number::value_type Power(Number::value_type, Number::value_type);

	int operation_;
};

bool operator==(const Token& lhs, const Token& rhs);

class PowerArgumentError: public std::runtime_error
{
public:
	PowerArgumentError(Number::value_type value, const char* message)
		: std::runtime_error(message), error_argument_(value) {}

	Number::value_type error_argument() const { return error_argument_; }

private:
	Number::value_type error_argument_;
};

#endif