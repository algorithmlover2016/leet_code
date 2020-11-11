// 10 ways to convert a char to a string in C++
// https://www.techiedelight.com/convert-char-to-string-cpp/

#include "../head.h"

/*
   1. std::string constructor
*/

int constructor() {
	char c = 'A';

	// using string class fill constructor

	std::string s(1, c);
	std::cout << s << '\n';

	return 0;
}

/*
   2. using std::stringstream
*/

int sstream() {
	char c = 'A';

	// using stringstream

	std::string s;
	std::stringstream ss;
	ss << c;
	ss >> s;				  // or s = ss.str();
	std::cout << s << '\n';

	return 0;
}


/*
   3. std::string::push_back
*/

int pushBack() {
	char c = 'A';

	// using string::push_back

	std::string s;
	s.push_back(c);
	std::cout << s << '\n';

	return 0;
}

/*
   4. std::string::operator+=
 */

int strPlusAssignOperator() {
	char c = 'A';

	// using std::string::operator+=

	std::string s;
	s += c;
	std::cout << s << '\n';

	return 0;
}

/*
   5. std::string::operator=
 */

int strAssignOperator() {
	char c = 'A';

	// using std::string::operator=

	std::string s;
	s = c;
	std::cout << s << '\n';

	return 0;
}

/*
   6. std::string::append
 */
int strAppend() {
	char c = 'A';

	// using std::string::append

	std::string s;
	s.append(1, c);
	std::cout << s << '\n';

	return 0;
}

/*
  7. std::string::assign
*/
int strAssign() {
	char c = 'A';

	// using std::string::assign

	std::string s;
	s.assign(1, c);
	std::cout << s << '\n';

	return 0;
}

/*
  8. std::string::insert
*/

int strInsert() {
	char c = 'A';

	// using std::string::insert

	std::string s;
	s.insert(0, 1, c);
	std::cout << s << '\n';

	return 0;
}

/*
   9. std::string::replace
 */
int strReplace() {
	char c = 'A';

	// using std::string::replace

	std::string s;
	s.replace(0, 1, 1, c);
	std::cout << s << '\n';

	return 0;
}

/*
   10. convert char to string
 */

int convert() {
	char c = 'A';

	// converting char to c-string
	const char* str = &c;

	// using std::string fill constructor
	std::string s(str, 1);
	std::cout << s << '\n';

	// using std::string::append
	std::string S;
	S.append(str, 1);
	S.append(str, 1);
	std::cout << S << '\n';

	// using std::string::assign
	S.assign(str, 1);
	std::cout << S << '\n';

	return 0;
}

int main() {
    constructor();
    sstream();
    pushBack();
    strPlusAssignOperator();
    strAssignOperator();

    strAppend();
    strAssign();
    strInsert();
    strReplace();
    convert();
    return 0;
}
