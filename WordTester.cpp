#include <iostream>
#include <fstream>
using namespace std;
bool flag;
string filein, fileout, temp;
int main() {
	cin >> filein >> fileout;
	ifstream ifs;
	ofstream ofs;
	ifs.open(filein, ios::in);
	ofs.open(fileout, ios::out);
	if(!ifs.is_open()) return 1;
	if(!ofs.is_open()) return 2;
	while(true) {
		flag = true;
		getline(ifs, temp);
		string wd, mn;
		temp.erase(0, temp.find_first_not_of(" \t"));
		temp.erase(temp.find_last_not_of(" \t") + 1);
		for(int i = 0;i < temp.length();i++) {
			if(temp[i] == ' ') {
				wd = temp.substr(0, i);
				mn = temp.substr(i+1);
				break;
			}
		} 
		if(wd.length() <= 5 || wd.length() >= 16) {
			cout << wd << endl;
			flag = false;
		}
		for(char c : wd) {
			if(c != '-' && !isalpha(c)) {
				cout << temp << endl;
				flag = false;
				break;
			}
		}
		if(flag) {
			ofs << temp << endl;
		}
		if(ifs.eof()) break;
	}
	return 0;
}
