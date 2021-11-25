#include <iostream>
#include <string>

using std::string;

std::string myTrim(std::string& tobeTrim) {
	std::string newString = "";
	for (int i = 0; i < tobeTrim.length(); i++) {
		if (tobeTrim.at(i) != ' ') {
			newString += tobeTrim.at(i);
		}
	}
	tobeTrim = newString;
	return tobeTrim;
}

// trim from left 
inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}
// trim from right 
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}
// trim from left & right 
inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
	return ltrim(rtrim(s, t), t);
}

int main()
{
	string str = "             가나다 라마 바사   ";
	std::cout << str << std::endl;
	trim(str);
	std::cout << str << std::endl;

	string str1 = "    hello my world. ";
	std::cout << str1 << std::endl;
	myTrim(str1);
	std::cout << str1 << std::endl;

	string str2 = "  ( 5 + 4 ) - 2 * 15 ";
	std::cout << str2 << std::endl;
	myTrim(str2);
	std::cout << str2 << std::endl;
}