#ifndef _WORDGUESSEXCEPTION_H
#define _WORDGUESSEXCEPTION_H


#include <stdexcept>
#include <windows.h>
using namespace std;
class WordGuessException : public exception {
    private:
        string description;
    public:
        WordGuessException() {
            this->description = "Word-Guess Game Exception";
        }
        WordGuessException(string description) {
            this->description = description;
        }
        const char * what () const throw () {
            return description.c_str();
        }
};


#endif
