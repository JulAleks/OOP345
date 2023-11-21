/*************** WS 07_01 - CovidCollection Module -  CovidCollection.cpp ********************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
 Date of completion: 2023-11-06

 I have done all the coding by myself and only copied the code that my professor
 provided to complete my workshops and assignments.
**************************************************************************************/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

#include "CovidCollection.h"

namespace sdds {
    enum AppErrors
    {
        CannotOpenFile = 1, // can't open file
        BadFileName = 2,  // bad file name
    };

    CovidCollection::CovidCollection(const std::string fileName)
    {
        // A custom constructor that receives the name of the file containing the information about the covid details of various cities to be added to the collection.
        // This function should load the covid details from the file into the attributes.

        if (!fileName.empty()) {
            std::ifstream fin(fileName); // open file
            if (fin.fail()) {
                throw AppErrors::CannotOpenFile; // if can't open
            }
            else {
                std::string line;  //input line
                while (std::getline(fin, line)) {
                    if (!line.empty()) {
                        Covid temp; //temp struct
                        //The fields are not separated by delimiters; each field has a fixed size: COUNTRY, CITY and VARIANT have exactly 25 characters; while YEAR, CASES and DEATHS have exactly 5 characters.
                        int s_25 = 25, s_5 = 5;  
                        std::string t_line = trimSpace(line);

                        //assigning the extract values
                        temp.c_county = trimSpace(t_line.substr(0, s_25));
                        temp.c_city = trimSpace(t_line.substr(s_25, s_25));
                        temp.c_variant = trimSpace(t_line.substr(s_25 * 2, s_25));
                        temp.c_year = std::stoi(trimSpace(t_line.substr(s_25 * 3, s_5)));
                        temp.c_numCase = std::stoi(trimSpace(t_line.substr(s_25 * 3 + s_5, s_5)));
                        temp.c_numDeath = std::stoi(trimSpace(t_line.substr(s_25 * 3 + 2 * s_5, s_5)));

                        //if extraction was good push to vector 
                        if (!temp.c_county.empty() && !temp.c_city.empty()) {
                            corona.push_back(temp);
                        }
                    }
                }
            }
            fin.close(); //close the file 
        }
        else {
            throw AppErrors::BadFileName; //throw error.
        }
    }

    //print the content of the collection into the parameter. Use the insertion operator (see below). DO NOT USE MANUAL LOOPS!
    void CovidCollection::display(std::ostream& out) const {
        for (const Covid& item : corona) {
            out << item << std::endl;
        }
    }

    //inserts one Covid object into the first parameter,
    std::ostream& operator<<(std::ostream& out, const Covid& theCovid) {
        out << "| " << std::setw(22) << std::left << theCovid.c_county
            << "| " << std::setw(15) << std::left << theCovid.c_city
            << " | " << std::setw(20) << std::left << theCovid.c_variant;

        out << " | " << std::setw(6);
        if (theCovid.c_year > 0) {
           out << std::right << theCovid.c_year;
        }
        else {
            out << std::setfill(' ') << " ";
        }

        out << " | " << std::setw(4) << std::right<<theCovid.c_numCase << " | " << std::setw(3) << std::right << theCovid.c_numDeath << " |";

        return out;
    }

    //space trimmer
    std::string trimSpace(const std::string& str) {
        size_t firstSpace = str.find_first_not_of(' ');
        if (std::string::npos == firstSpace) {
            return str;
        }
        size_t lastSpace = str.find_last_not_of(' ');
        return str.substr(firstSpace, (lastSpace - firstSpace + 1));
    }
}


