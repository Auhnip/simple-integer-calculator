#ifndef STACK_H_
#define STACK_H_

#include <cstdint>
#include <utility>
#include <stdexcept>
#include <string>

template <typename Type>
class Stack
{
public:
	using value_type = Type;
	using size_type = std::uint64_t;

	Stack(): top_(nullptr), size_(0) {}
	Stack(const Stack& other);
	Stack(Stack&& other) noexcept;
	~Stack();

	Stack& operator=(Stack other);

	void swap(Stack& other);

	void push(const value_type& value);
	void pop();

	const value_type& top() const;

	size_type size() const { return size_; }
	bool empty() const { return !size_; }

	template <typename Compiler>
	std::string ToString(const Compiler& compiler) const;

private:
	struct Node
	{
		Stack::value_type value_;
		Node* next_;

		Node(const Stack::value_type& value, Node* next)
			: value_(value), next_(next) {}
	};

	static Node* CopyLinkedList(Node* root);
	
	Node* top_;
	size_type size_;
};

class StackEmptyError: public std::runtime_error
{
public:
	StackEmptyError(const char* message): std::runtime_error(message) {}
};

template <typename Type>
typename Stack<Type>::Node* Stack<Type>::CopyLinkedList(Node* root)
{
	Node* head = nullptr, tail = nullptr;
	Node* current;

	while (root)
	{
		current = new Node(root->value_, nullptr);

		if (!head)
			head = current;
		else
			tail->next_ = current;
		
		root = root->next_;
		tail = current;
	}

	return head;
}

template <typename Type>
Stack<Type>::Stack(const Stack& other)
	: top_(CopyLinkedList(other.top_)), size_(other.size_)
{}

template <typename Type>
Stack<Type>::Stack(Stack&& other) noexcept: Stack()
{
	swap(other);
}

template <typename Type>
Stack<Type>::~Stack()
{
	Node* current = top_, * previous;

	while (current)
	{
		previous = current;
		current = current->next_;
		delete previous;
	}
}

template <typename Type>
Stack<Type>& Stack<Type>::operator=(Stack other)
{
	swap(other);

	return *this;
}

template <typename Type>
void Stack<Type>::swap(Stack& other)
{
	using std::swap;

	swap(top_, other.top_);
	swap(size_, other.size_);
}

template <typename Type>
void Stack<Type>::push(const value_type& value)
{
	Node* new_top = new Node(value, top_);

	top_ = new_top;
	++size_;
}

template <typename Type>
void Stack<Type>::pop()
{
	if (empty())
		throw StackEmptyError("Stack is empty when call pop()");
	
	Node* old = top_;
	top_ = top_->next_;
	delete old;

	--size_;
}

template <typename Type>
const typename Stack<Type>::value_type& Stack<Type>::top() const
{
	if (empty())
		throw StackEmptyError("Stack is empty when call top()");
	
	return top_->value_;
}

template <typename Type>
	template <typename Compiler>
std::string Stack<Type>::ToString(const Compiler& compiler) const
{
	std::string message = "[";

	const Node* current = top_;

	while (current)
	{
		message += compiler(current->value_);

		if (current->next_)
			message += ",";

		current = current->next_;
	}
	message += "]";

	return message;
}

#endif