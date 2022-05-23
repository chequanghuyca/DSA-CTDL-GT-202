/*
	Hiện thực hàm bool isValidParentheses (string s) để kiểm tra xem chuỗi đầu vào có hợp lệ hay không dựa trên các quy tắc sau:

	Các dấu ngoặc mở phải được đóng bằng cùng một loại dấu đóng ngoặc tương ứng. 
	Các dấu ngoặc mở phải được đóng theo đúng thứ tự.
	Lưu ý: Chuỗi s chỉ chứa các ký tự '(', ')', '[', ']', '{', và '}'. 

	Ví dụ:

	Chuỗi "[]()", "[()]" là chuỗi hợp lệ
	Chuỗi "[])" là chuỗi không hợp lệ.
	Chương trình đã được include sẵn các thư viện <iostream>, <fstream>, <string>, <stack>, <vector>
	For example:
	TEST									RESULT
	cout << isValidParentheses("[]");		1
	cout << isValidParentheses("[]()");		1
	cout << isValidParentheses("[)");		0
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

bool isValidParentheses(string s) {
	std::vector<char> str;
	for (char c : s) {
		switch (c) {
		case '(':
		case '{':
		case '[':
			str.push_back(c);
			break;
		case ')':
			if (str.empty() || str.back() != '(') {
				return false;
			}
			str.pop_back();
			break;
		case '}':
			if (str.empty() || str.back() != '{') {
				return false;
			}
			str.pop_back();
			break;
		case ']':
			if (str.empty() || str.back() != '[') {
				return false;
			}
			str.pop_back();
			break;
		}
	}
	return str.empty();
}

int main() {
	cout << isValidParentheses("[]()");
	return 0;
}