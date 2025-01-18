#pragma once

template <typename T> class stack
{
public:
	struct node
	{
		T data;
		node* next;
	};

	stack();
	~stack();
	T get_data();
	void pop();
	void push(const T& variable);
	int get_size();
	bool is_empty();
private:
	node* top;
	int size;
};


template <typename T>
int stack<T>::get_size()
{
	return this->size;
}


template <typename T>
void stack<T>::push(const T& variable)
{
	node* temp = new node;
	temp->data = variable;
	temp->next = this->top;
	this->top = temp;
	this->size++;
}


template <typename T>
stack<T>::stack()
{
	this->top = nullptr;
	this->size = 0;
}


//Precondition: The stack should be non-empty
template <typename T>
T stack<T>::get_data()
{
	return (this->top)->data;
}


//Precondition: The stack should be non-empty
template <typename T>
void stack<T>::pop()
{
	node* temp;
	temp = (this->top)->next;
	delete this->top;
	this->top = temp;
	this->size--;
}


template <typename T>
bool stack<T>::is_empty()
{
	if (this->top == nullptr) return true;
	else return false;
}

template <typename T>
stack<T>::~stack()
{
	while (this->top != nullptr)
	{
		node* temp = (this->top)->next;
		delete this->top;
		this->top = temp;
	}
}

