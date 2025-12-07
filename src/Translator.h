#ifndef _TRANSLATOR_H_
#define _TRANSLATOR_H_


#include <iostream>
#include <windows.h>
#include <unordered_map>
using namespace std;
class Translator {
    private:
        string language;
        unordered_map<string, bool> languages;
        unordered_map<string, unordered_map<string, string> > translations;
    public:
        Translator() {
            this->language = "zh_cn";
        }
        Translator(string language) {
            if(languages[language]) {
                this->language = language;
            }
            else this->language = "zh_cn";
        }
        void add_language(string language) {
            if(languages.count(language) && languages[language]) return;
            languages[language] = true;
        }
        void add_message(string language, string id, string message, bool NewLineIfDuplicated = true) {
            if(!languages.count(language) || !languages[language]) return;
            if(translations[language].count(id) == 1) {
                if(NewLineIfDuplicated) translations[language][id] += '\n';
                translations[language][id] += message;
            }
            else translations[language][id] = message;
        }
        int select(string language) {
            if(languages.count(language) && languages[language]) {
                this->language = language;
                return 0;
            }
            else {
                return 1;
            }
        }
        string translate(string id, bool NewLine = true) {
            if(translations[this->language].count(id) == 0) {
                if(NewLine) return id + '\n';
                else return id;
            }
            if(NewLine) return translations[this->language][id] + '\n';
            return translations[this->language][id];
        }
        string translate(string language, string id, bool NewLine) {
            if(translations[language].count(id) == 0) {
                if(NewLine) return id + '\n';
                else return id;
            }
            if(NewLine) return translations[language][id] + '\n';
            return translations[language][id];
        }
};


#endif
