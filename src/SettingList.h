#ifndef _SETTINGLIST_H
#define _SETTINGLIST_H


#include <unordered_map>
#include "WordGuessException.h"
using namespace std;
template <class T>
class SettingList {
	private:
		unordered_map<string, T> setlist;
	public:
		SettingList(){}
		SettingList(unordered_map<string, T> st) {
			setlist = st;
		}
		T get(string key) {
			if(setlist.count(key) == 0)
				throw WordGuessException("Specified setting not found.");
			return setlist[key];
		}
		int set(string key, T value) {
			setlist[key] = value;
			return 0;
		}
		int size() {
			return setlist.size();
		}
		bool empty() {
			return setlist.empty();
		}
		int clear() {
			if(setlist.empty()) return 1;
			setlist.clear();
			return 0;
		}
		string getkeys() {
			string result;
			for(pair<string, T> s : setlist) result += s.first + '\n';
			return result;
		}
};


#endif
