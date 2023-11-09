/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #5 (PART 2)
SpellChecker Module
File	SpellChecker.h
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Oct 15, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H



#include <iostream>
#include <string>
#include "Book.h" //adding to use trimmer

#define SSIZE 6

namespace sdds {
    class SpellChecker {
        std::string m_badWords[SSIZE]{""};
        std::string m_goodWords[SSIZE]{""};
        int count[SSIZE]{0};

    public:
        SpellChecker() {};
        SpellChecker(const char* filename);

        const std::string* good() const;
        const std::string* bad() const;
        int* getCount();

        void operator()(std::string& text);

        void showStatistics(std::ostream& out) const;
    };
}
#endif
