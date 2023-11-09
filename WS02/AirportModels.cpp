/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #2 (PART 2)
Student Name: Julia Alekseev
Student ID#:  051292134
Email      :  jalekseev@myseneca.ca
Section    :  NFF
Date       :  Sep 23, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <iomanip> 
#include <fstream>
#include <string>
#include <cstring>
#include "AirportModels.h"

using namespace std;

namespace sdds
{   
   
    //Overload the insertion operator to output an Airport object to an output stream
    ostream& operator<<(ostream& os, const Airport& a)
    {
        if(!a.a_code.empty()) {
            os << right << setw(20)<< setfill('.') << "Airport Code" << " : " << left << setw(30) << a.a_code << endl;          
            os << right << setw(20) << "Airport Name" << " : " << left << setw(30) << a.a_name << endl;
            os << right << setw(20) << "City" << " : " << left << setw(30) << a.a_city << endl;
            os << right << setw(20) << "State" << " : " << left << setw(30) << a.a_state << endl;
            os << right << setw(20) << "Country" << " : " << left << setw(30) << a.a_country << endl;
            os << right << setw(20) << "Latitude" << " : " << left << setw(30) << a.a_latitude << endl;
            os << right << setw(20) << "Longitude" << " : " << left << setw(30) << a.a_longitude << endl;
        }
        else {
            os<<"Empty Airport";
        }
        return os;
    }

    void AirportLog::setToDefault()
    {
        delete[] airports;
        airports = nullptr;
    }

    //A one argument constructor that receives a filename as a parameter from which we will populate the current object.
    AirportLog::AirportLog(const char * fileName):airports(nullptr),numAir(0){
        ifstream in(fileName);
        if (in.is_open() == false) {
            std::cout << "Cannot open file [" << fileName << "]. Ignoring it!\n";
        }
        else {
            string line;
            if (in.good()) {
                while (in) {
                    //read the file to count the number of airports in the file (note the heading line in the file is not describing an actual airport so do not count that line)
                    getline(in, line); //ignoring first line
                    while (getline(in, line)) { numAir++; } //counting the number of airports
                }
                //allocate dynamic memory for the array of airports based on the number found
                airports = new Airport[numAir];

                //rewind the file
                in.clear();
                in.seekg(0, ios::beg);

                //reread the file from the beginning to load the actual airport data into the array
                while (in) {
                    char del = ',';
                    getline(in, line); //ignoring first line
                    for (auto i = 0u; i < numAir; ++i) {
                        getline(in, airports[i].a_code, del);
                        getline(in, airports[i].a_name, del);
                        getline(in, airports[i].a_city, del);
                        getline(in, airports[i].a_state, del);
                        getline(in, airports[i].a_country, del);
                        in >> airports[i].a_latitude;
                        in.ignore();
                        in >> airports[i].a_longitude;
                        in.ignore();
                    }
                }
            }
        }
    }

    //destrcutor
    AirportLog::~AirportLog()
    {
        setToDefault();
    }

    //copy constructor
    AirportLog::AirportLog(const AirportLog& rhs) {
        *this = rhs; //using equal assigment 
    }

    //copy assigment 
    AirportLog& AirportLog::operator=(const AirportLog& rhs) {
        if (this != &rhs) { //checking that it isn'ts self assigment 
            setToDefault();
            numAir = rhs.numAir;

            if (rhs.airports) {
                airports = new Airport[rhs.numAir];  //set a new airport
                for (unsigned int i = 0; i < rhs.numAir; ++i) { //copy all the airports
                    airports[i] = rhs.airports[i];
                }
            }
           
        }
        return *this;
    }

    AirportLog::AirportLog(AirportLog&& rhs)noexcept
    {
        *this = move(rhs);   //changing ownership
    }

    AirportLog& AirportLog::operator=(AirportLog&& rhs)noexcept
    {
        if (this != &rhs) {//checking that it isn'ts self assigment 

            setToDefault();
            numAir = rhs.numAir;

            if (rhs.airports) {
                airports = rhs.airports;//set a new airport
                rhs.airports = nullptr; //setting old airport to default
                rhs.numAir = 0;
            }
        }
        return *this;
    }

    //addAirport() is a modifier that receives a constant reference to an Airport object
    void AirportLog::addAirport(const Airport& rhs) {
          
        //temp object with the new size of airports
        Airport* t{};
        t=new Airport[numAir + 1];

        // Copy the existing airports
        for (auto i = 0u; i < numAir ; i++) {
            t[i] = airports[i];
        }

        //add the rhs airport
        t[numAir] = rhs;
        numAir++; //add one more airport to the counter

        //delete the current airport and copy t
        setToDefault();

        airports = t; //copy temp obj to airports
    }

    //is a query that receives two C-style strings as paramenters representing the state name and the country name
    AirportLog AirportLog::findAirport(const char* state, const char* country) {
        AirportLog t{}; //temp obj

        for (auto i = 0u; i < numAir; i++) {
            if (state == airports[i].a_state && country == airports[i].a_country) {
                t.addAirport(airports[i]);
            }
        }
        return t;  //return temp
    }

    //a query that will return the Airport in the dynamic array at the index provided
    const Airport& AirportLog::operator[](size_t index) const {
        if (index < static_cast<size_t>(numAir)){
            return airports[index];
        }
        else {
            static Airport t{};//making a static temp obj
            return t;//if there is a valid index return it, if not return an empty obj
        }
    }

    //casting operator that will convert the current object to a size_t value.
    AirportLog::operator size_t() const {
        return numAir;
    }



   











}


