#include<iostream>
#include<stack>
#include<cctype>
#include <string>

bool toPostfix(std::string infixOne, std::string& postfixOne);
int outPrior(char aChar);
int inPrior(char achar);
bool postfixValueCheck(std::string postfixOne);
bool strToDouble(std::string valStr, double& tobeResult);
int hexVal(char achar);

bool strToDouble(std::string valStr, double& tobeResult) {
	if (valStr.length() <= 2) { 
		tobeResult = stod(valStr);
		return true;
	}
	else {
		if (valStr.at(0) == '0' && valStr.at(1) == 'x') {
			int dotIndex;
			for (dotIndex=0; dotIndex < valStr.length(); dotIndex++) {
				if (valStr.at(dotIndex) == '.') {
					break;
				}
			}
			for (int i = 2; i < valStr.length(); i++) {
				if (isdigit(valStr.at(i)) | valStr.at(i) == '.' |
					(97 <= valStr.at(i) && valStr.at(i) <= 102)) {
					continue;
				}
				else {
					return false;
				}
			}
			int frontVal = 0;
			int posVal = 1;
			for (int i = dotIndex - 1; i >= 2; i--) {
				frontVal += posVal * hexVal(valStr.at(i));
				posVal *= 16;
			}
			double underVal = 0;
			double underPosVal = (double)1 / 16;
			for (int i = dotIndex + 1; i < valStr.length(); i++) {
				underVal += underPosVal * hexVal(valStr.at(i));;
				underPosVal /= 16;
			}
			tobeResult = (double)frontVal + underVal;
			return true;
		}
		else if (valStr.at(0) == '0' && valStr.at(1) == 'b') {
			int dotIndex;
			for (dotIndex = 0; dotIndex < valStr.length(); dotIndex++) {
				if (valStr.at(dotIndex) == '.') {
					break;
				}
			}
			for (int i = 2; i < valStr.length(); i++) {
				if (valStr.at(i)=='0' | valStr.at(i)=='1' | valStr.at(i) == '.') {
					continue;
				}
				else {
					return false;
				}
			}
			int frontVal = 0;
			int posVal = 1;
			for (int i = dotIndex - 1; i >= 2; i--) {
				frontVal += posVal * hexVal(valStr.at(i));
				posVal *= 2;
			}
			double underVal = 0;
			double underPosVal = (double)1 / 2;
			for (int i = dotIndex + 1; i < valStr.length(); i++) {
				underVal += underPosVal * hexVal(valStr.at(i));;
				underPosVal /= 2;
			}
			tobeResult = (double)frontVal + underVal;
			return true;
		}
		else {
			int dotIndex;
			for (dotIndex = 0; dotIndex < valStr.length(); dotIndex++) {
				if (valStr.at(dotIndex) == '.') {
					break;
				}
			}
			for (int i = 0; i < valStr.length(); i++) {
				if (isdigit(valStr.at(i)) | valStr.at(i) == '.') {
					continue;
				}
				else {
					return false;
				}
			}
			int frontVal = 0;
			int posVal = 1;
			for (int i = dotIndex - 1; i >= 0; i--) {
				frontVal += posVal * hexVal(valStr.at(i));
				posVal *= 10;
			}
			double underVal = 0;
			double underPosVal = (double)1 / 10;
			for (int i = dotIndex + 1; i < valStr.length(); i++) {
				underVal += underPosVal * hexVal(valStr.at(i));;
				underPosVal /= 10;
			}
			tobeResult = (double)frontVal + underVal;
			return true;
		}
	}
	return true;
}
int hexVal(char achar) {
	switch (achar) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return achar-48;
		break;
	case 'a':
		return 10;
		break;
	case 'b':
		return 11;
		break;
	case 'c':
		return 12;
		break;
	case 'd':
		return 13;
		break;
	case 'e':
		return 14;
		break;
	case 'f':
		return 15;
		break;
	default:
		return -1;
		break;
	}
}
bool postfixCal(std::string postfixOne, double& toBeResult) {
	std::string valStr = "";
	std::stack<double> valStack;
	for (int i = 0; i < postfixOne.length(); i++) {
		if (isdigit(postfixOne.at(i)) | postfixOne.at(i) == 'x' |
			postfixOne.at(i) == 'b' | postfixOne.at(i) == '.')
		{
			valStr += postfixOne.at(i);
		}
		else if(postfixOne.at(i) == ',') {
			double value = 0;
			bool valConverted = strToDouble(valStr, value);
			if (!valConverted) {
				return false;
			}
			valStack.push(value);
			valStr = "";
		}
		else {
			if (valStack.size() < 2) { return false; }
			char oper = postfixOne.at(i);
			double operand1 = valStack.top();
			valStack.pop();
			double operand2 = valStack.top();
			valStack.pop();
			double result = 0;

			switch (oper) {
			case '*':
				result = operand2 * operand1;
				break;
			case '/':
				if (operand1 == 0) {
					return false;
				}
				else {
					result = operand2 / operand1;
				}
				break;
			case '+':
				result = operand2 + operand1;
				break;
			case '-':
				result = operand2 - operand1;
				break;
			default:
				return false;
			}

			valStack.push(result);
		}
	}
	if (valStack.size() == 1) {
		toBeResult = valStack.top();
		valStack.pop();
		return true;
	}
	else {
		return false;
	}
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
					infixOne.at(i + 1) != 'b' && infixOne.at(i + 1) != '.')
				{
					postfixOne += ',';
					p++;
				}
			}
			else {
				postfixOne += ',';
				p++;
			}
		}
		else if (current == 'x' | current == 'b') {
			if (i == 0) {
				return false;
			}
			if (i != 0 && infixOne.at(i - 1) != '0') {
				return false;
			}
			if (i == infixOne.length() - 1) {
				return false;
			}
			if (i != infixOne.length() - 1 && 
				!(isdigit(infixOne.at(i + 1)) | islower(infixOne.at(i+1))) ) 
			{
				return false;
			}
			postfixOne += current;
			p++;
		}
		else if (current == '.') {
			if (i == 0) {
				return false;
			}
			else {
				if (!isdigit(infixOne.at(i - 1))) {
					return false;
				}
				if (i == infixOne.length() - 1) {
					return false;
				}
				if (i != infixOne.length() - 1 && 
					!(isdigit(infixOne.at(i + 1)) | islower(infixOne.at(i+1))) )
				{
					return false;
				}
				postfixOne += current;
				p++;
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
	std::string str = "0b11.01+0b111+15.75+0x2";
	std::string str2;
	toPostfix(str, str2);
	std::cout << str2 << std::endl;

	double result;
	postfixCal(str2, result);
	std::cout << result << std::endl;
}