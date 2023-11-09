/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #5 (PART 2)
SpellChecker Module
File	SpellChecker.cpp
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Oct 15, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <string>
#include "SpellChecker.h"


namespace sdds {
  
    SpellChecker::SpellChecker(const char* filename)
    {
        try {
            //receives the address of a C-style null-terminated string that holds the name of the file that contains the misspelled words.
            std::ifstream file(filename);

            if (!file.is_open()) {
                throw std::runtime_error("Bad file name!");
            }
            else { //If the file exists, this constructor loads its contents. 
                std::string line;
                int i = 0;
                //each line in the file has the format BAD_WORD  GOOD_WORD; the two fields can be separated by any number of spaces
                while (i < SSIZE && std::getline(file, line)) {
                    size_t spacePos = line.find(' ');
                    if (spacePos != std::string::npos) {
                        m_badWords[i] = trimSpace(line.substr(0, spacePos));
                        m_goodWords[i] = trimSpace(line.substr(spacePos + 1));
                        i++;
                    }
                }
                file.close();
            }
        }
        catch (const char* err) {//If the file is missing, this constructor throws an exception of type const char*, 
            std::cerr << "** EXCEPTION:" << err << std::endl;
        }
    }

    const std::string* SpellChecker::good() const
    {
        return m_goodWords;
    }

    const std::string* SpellChecker::bad() const
    {
        return m_badWords;
    }

    int* SpellChecker::getCount()
    {
        return count;
    }

    //this operator searches text and replaces any misspelled word with the correct version. It should also count how many times each misspelled word has been replaced.
    void SpellChecker::operator()(std::string& text)
    {
        for (size_t i = 0; i < SSIZE; ++i) {
            size_t found = text.find(m_badWords[i]); //looking to see if there is a bad word in i loc
            int replaceCount = 0;

            while (found != std::string::npos) { //if it was found and its not the end of the file
                text.replace(found, m_badWords[i].length(), m_goodWords[i]); //replaces the bad word with good word
                found = text.find(m_badWords[i], found + m_goodWords[i].length()); //finds the next bad word
                ++replaceCount; //increase replace
            }
            if (replaceCount > 0) {
                count[i] += replaceCount; 
            }
        }
    }

    //inserts into the parameter how many times each misspelled word has been replaced by the correct word using the current instance. 
    void SpellChecker::showStatistics(std::ostream& out) const {
        out << "Spellchecker Statistics" << std::endl;
        for (auto i = 0u; i < SSIZE; i++) {
            out << std::setw(15) << std::right << m_badWords[i] << ": " << count[i] << " replacements" << std::endl;
        }
    }

}
