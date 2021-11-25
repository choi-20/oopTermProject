#include<iostream>
#include<stack>
#include<cctype>

bool toPostfix(std::string infixOne, std::string& postfixOne);
int outPrior(char aChar);
int inPrior(char achar);
bool postfixValueCheck(std::string postfixOne);

bool postfixValueCheck(std::string postfixOne) {
	return false;
}

bool toPostfix(std::string infixOne, std::string& postfixOne) {
	postfixOne = "";
	char current, popped, top;
	std::stack<char> operatorStack;
	int p = 0;
	for (int i = 0; i < infixOne.length(); i++) {
		current = infixOne.at(i);
		if (isdigit(current)) {
			postfixOne += current;
			p++;
			if (i != infixOne.length() - 1) {
				if (!isdigit(infixOne.at(i + 1)) && infixOne.at(i + 1) != 'x' && 
					infixOne.at(i + 1) != 'b')
				{
					postfixOne += ',';
					p++;
				}
			}
		}
		else if (current == 'x' | current == 'b') {
			if (i == 0) {
				return false;
			}
			else {
				if (infixOne.at(i - 1) != '0') {
					return false;
				}
				else {
					postfixOne += current;
					p++;
				}
			}
		}
		else {
			if (current == ')') {
				if (operatorStack.empty()) {
					return false;
				}
				else {
					char popped = operatorStack.top();
					operatorStack.pop();
					while (popped != '(') {
						postfixOne += popped;
						p++;
						if (!operatorStack.empty()) {
							popped = operatorStack.top();
							operatorStack.pop();
						}
						else {
							return false;
						}
					}
				}
			}
			else {
				int currentPrior = outPrior(current);
				if (currentPrior < 0) {
					return false;
				}
				else {
					if (!operatorStack.empty()) {
						top = operatorStack.top();
						while (currentPrior <= inPrior(top)) {
							popped = top;
							operatorStack.pop();
							postfixOne += popped;
							p++;
							if (!operatorStack.empty()) {
								top = operatorStack.top();
							}
							else {
								break;
							}
						}
					}
					operatorStack.push(current);
				}
			}
		}
	}
	while (!operatorStack.empty()) {
		popped = operatorStack.top();
		operatorStack.pop();
		if (popped == '(') {
			return false;
		}
		postfixOne += popped;
		p++;
	}
	return true;
}
int outPrior(char aChar) {
	switch (aChar) {
	case '(': return 20;
	case ')': return 19;
	case '*': return 13;
	case '/': return 13;
	case '+': return 12;
	case '-': return 12;
	default: return -1;
	}
}
int inPrior(char achar) {
	switch (achar) {
	case '(': return 0;
	case ')': return 19;
	case '*': return 13;
	case '/': return 13;
	case '+': return 12;
	case '-': return 12;
	default: return -1;
	}
}

void main() {
	std::string str = "15+0x32*(0b1-0x8)/2";
	std::string str2;
	toPostfix(str, str2);
	std::cout << str2 << std::endl;
}