/*************** WS 07_02 - CovidCollection Module -  CovidCollection.cpp ********************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
 Date of completion: 2023-11-11

 I have done all the coding by myself and only copied the code that my professor
 provided to complete my workshops and assignments.
**************************************************************************************/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
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
    void CovidCollection::display(std::ostream& out, const std::string& country) const {
        if (country != "ALL") {
            out << "Displaying information of country = " << country << std::endl;
        }

        //algorithms

       //getting all deaths
       //T accumulate(InputIterator f, InputIterator l, T init)
        int deathCounter = accumulate(corona.begin(), corona.end(), 0, [](const int& sum, const Covid& c) {
            return sum + c.c_numDeath;
            });

        //getting all cases 
        //T accumulate(InputIterator f, InputIterator l, T init)
        int caseCounter = accumulate(corona.begin(), corona.end(), 0, [](const int& sum, const Covid& c) {
            return sum + c.c_numCase;
            });

        //country total death
        int c_deathCounter = accumulate(corona.begin(), corona.end(), 0, [country](const int& sum, const Covid& c) {
            return (c.c_county == country) ? sum + c.c_numDeath : sum;
            });

        //country total cases
        int c_caseCounter = accumulate(corona.begin(), corona.end(), 0, [country](const int& sum, const Covid& c) {
            return (c.c_county == country) ? sum + c.c_numCase : sum;
            });


        //OutputIterator copy_if(InputIterator f, InputIterator l, OutputIterator o, Fn predicate)                      //I AM SORRY BUT THIS IS STILL BETTER... LOOK AT ALL THE EXTRA LINES AND LOGIC :( BOO NO FUN 
          //  std::copy_if(corona.begin(), corona.end(), std::ostream_iterator<Covid>(std::cout, "\n"),
         //   [country](const Covid& c) { return (country == "ALL" || c.c_county == country);
         //   });
         
        //making temp corona
        std::vector<Covid> temmp_corona;
    
        //lambda for a condition 
        auto coutry_all = [country](const Covid& c) { return (country != "ALL" && c.c_county != country); };

        //using remove copy if to filter
        //OutputIterator remove_copy_if(InputIterator f, InputIterator l, OutputIterator o, Fn predicate);
        std::remove_copy_if(corona.begin(), corona.end(), std::back_inserter(temmp_corona), coutry_all);

        //copying to ostream 
        std::copy(temmp_corona.begin(), temmp_corona.end(), std::ostream_iterator<Covid>(std::cout, "\n"));

        //output
        if (country == "ALL") {
            std::cout << "| " << std::setw(79) << std::setfill(' ') << std::right << "Total cases around the world: " << caseCounter << " |" << std::endl;
            std::cout << "| " << std::setw(79) << std::setfill(' ') << std::right << "Total deaths around the world: " << deathCounter << " |" << std::endl;

        }
        else {
            printbar();
            std::cout << "| " << std::setw(80) << std::setfill(' ') << std::right << "Total cases in " + country + ": " << c_caseCounter << " |" << std::endl;
            std::cout << "| " << std::setw(80) << std::setfill(' ') << std::right << "Total deaths in " + country + ": " << c_deathCounter << " |" << std::endl;

            //get statistics 
            double deathStat = static_cast<double>(c_deathCounter) / deathCounter * 100;
            double caseStat = static_cast<double>(c_caseCounter) / caseCounter * 100;

            std::string case_death = country + " has " + std::to_string(caseStat) + "% of global cases and " + std::to_string(deathStat) + "% of global deaths";
            std::cout << "| " << std::setw(84) << std::setfill(' ') << std::right << case_death << " |" << std::endl;
        }
    }

    void CovidCollection::sort(const std::string& field)
    {
        // Sort the collection of Covid objects in ascending order based on the field received as parameter.
         //void sort(RandomAccessIterator f, RandomAccessIterator l, Fn compare) 
        std::sort(corona.begin(), corona.end(), [field](const Covid& c1, const Covid& c2) {
            //If two Covid objects have the same value for the specified field, then the object with lower deaths is considered smaller.
            bool comp = true;
        if (field == "country") {
            if (c1.c_county == c2.c_county) {
                if (c1.c_numDeath == c2.c_numDeath) {
                    //if it is the same country and the death cases are the same, sort by the date rate in compersion to cases 
                    double death1 = static_cast<double>(c1.c_numDeath) / c1.c_numCase * 100;
                    double death2 = static_cast<double>(c2.c_numDeath) / c2.c_numCase * 100;

                    comp = (death1 < death2);
                }
                else {
                    comp = c1.c_numDeath < c2.c_numDeath;
                }
            }
            else {
                comp = c1.c_county < c2.c_county;
            }
        }
        else if (field == "cases") {
            if (c1.c_numCase == c2.c_numCase) {
                comp = c1.c_numDeath < c2.c_numDeath;
            }
            else {
                comp = c1.c_numCase < c2.c_numCase;
            }
        }
        else if (field == "variant") {
            if (c1.c_variant == c2.c_variant) {
                comp = c1.c_numDeath < c2.c_numDeath;
            }
            else {
                comp = c1.c_variant < c2.c_variant;
            }
        }
        else if (field == "year") {
            if (c1.c_year == c2.c_year) {
                comp = c1.c_numDeath < c2.c_numDeath;
            }
            else {
                comp = c1.c_year < c2.c_year;
            }
        }
        else {
            comp = c1.c_numDeath < c2.c_numDeath; //death is the ultimate sorter... like in life... :P 
        }
        return comp;
            });
    }


    //Search in the collection for a city in the specified country where the variant from the first parameter has caused more deaths than the last parameter.
    bool CovidCollection::inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const
    {
        //InputIterator find_if(InputIterator f, InputIterator l, Fn predicate)
        auto itr = std::find_if(corona.begin(), corona.end(), [variant, country, deaths](const Covid& c) {
            return c.c_variant == variant && c.c_county == country && c.c_numDeath > deaths;
         });

        return itr != corona.end(); //return true if such an object exists, false otherwise.
    }


    //Create and return a collection of Covid objects from the current instance where the number of deaths is at least as the value specified as parameter.
    std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const
    {
        // filter the list
        std::list<Covid> c_list;

        std::copy_if(corona.begin(), corona.end(), std::back_inserter(c_list), [deaths](const Covid& c) {  
            return c.c_numDeath >= deaths;
            });

        //sort by death if same country sort by # of cases 
        c_list.sort([deaths](const Covid& c1, const Covid& c2) {
            bool comp = true;
        if (c1.c_county == c2.c_county && c1.c_variant == c2.c_variant) {
            if (c1.c_numDeath == c2.c_numDeath) {
                comp = c1.c_year < c2.c_year;
            }
            else {
                comp = c1.c_numDeath < c2.c_numDeath;
            }
        }
        else {
            comp = c1.c_variant < c2.c_variant;
        }
        return comp;
            });

        return c_list;
    }

    //updates the status of each city. If the number of deaths is greater than 300, the status should be EPIDEMIC, if it is less than 50, it should be EARLY; for anything else, the status should be MILD.
    void CovidCollection::updateStatus()
    {
        //updates the status of each city. If the number of deaths is greater than 300, the status should be EPIDEMIC, if it is less than 50, it should be EARLY; for anything else, the status should be MILD.
        std::for_each(corona.begin(), corona.end(), [](Covid& c) {
            if (c.c_numDeath > 300) {
                c.c_severty = "EPIDEMIC";
            }
            else if (c.c_numDeath < 50) {
                c.c_severty = "EARLY";
            }
            else {
                c.c_severty = "MILD";
            }
            });
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
        out <<" | "<< std::setw(8) << theCovid.c_severty << " |";
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

    //printing the bar
    void printbar()
    {
        std::cout << std::setw(89) << std::setfill('-') << '\n' << std::setfill(' ');
    }
}


