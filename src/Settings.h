#include <iostream>
using namespace std;
unordered_map<string, int> stInt;
unordered_map<string, string> stStr;
int getstInt(string key) {
	return stInt[key];
}
string getstStr(string key) {
	return stStr[key];
}
