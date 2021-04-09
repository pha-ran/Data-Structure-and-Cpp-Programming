#include <iostream>

template<class T>
class Stack {
  private:
	  T* stack;
	  int top;
	  int capacity;
  public:
	  Stack(int stackCapacity = 10);
	  ~Stack();
	  bool isEmpty();
	  T& Top() const;
	  void Push(const T& item);
	  void Pop();
};

int main() {


	return 0;
}