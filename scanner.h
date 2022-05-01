#ifndef SCANNER_H_
#define SCANNER_H_

#include "token.h"

#include <utility>
#include <string>
#include <cctype>
#include <cstring>
#include <stdexcept>

class Scanner
{
public:
	static constexpr uint32_t kNumberMaxLength = 5;

	explicit Scanner(const char* expression);
	explicit Scanner(const std::string& expression);
	explicit Scanner(std::string&& expression);
	
	Scanner(const Scanner& other) = default;
	Scanner(Scanner&& other) = delete;
	Scanner& operator=(const Scanner& other) = default;
	Scanner& operator=(Scanner&& other) = delete;

	const Token& NextToken();
	bool HasNextToken() const { return !fail_; }
private:
	void LocateNextToken();
	void ReadNumber();
	void ReadOperator();

	std::string expression_;
	std::string::size_type index_;
	bool fail_;
	bool end_;

	const Token* last_token_;
};

inline Scanner::Scanner(const char* expression)
	: Scanner(std::string(expression))
{}

inline Scanner::Scanner(const std::string& expression)
	: expression_(expression), index_(0), fail_(false), end_(false), last_token_(nullptr)
{
	LocateNextToken();
}

inline Scanner::Scanner(std::string&& expression)
	: expression_(std::move(expression)), index_(0), fail_(false), end_(false), last_token_(nullptr)
{
	LocateNextToken();
}

class NoNextToken: public std::runtime_error
{
public:
	NoNextToken(const char* message)
		: std::runtime_error(message) {}
};

#endif