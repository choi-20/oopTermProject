#include<iostream>
#include<stack>

int main() {
	std::stack<char> s;
	char top = s.top();
	std::cout << top << std::endl;

	return 0;
}