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
	while(getline(ifs, temp)) {
		flag = true;
		if(temp.length() <= 4 || temp.length() >= 16) {
			cout << temp << endl;
			flag = false;
		}
		for(char c : temp) {
			if(c != '-' && c != '\'' && !isalpha(c)) {
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
