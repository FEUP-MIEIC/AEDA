# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {

public:
	StackExt() {};
	bool empty() const;
	T& top();
	void pop();
	void push(const T& val);
	T& findMin();
};

template <class T>
bool StackExt<T>::empty() const {
	// a alterar
	return true;
}

template <class T>
T& StackExt<T>::top() {
	// a alterar
	T *novo = new T();
	return *novo;
}

template <class T>
void StackExt<T>::pop() {
	// a alterar
}

template <class T>
void StackExt<T>::push(const T& val) {
	// a alterar
}

template <class T>
T& StackExt<T>::findMin() {
	// a alterar
	return top();
}
