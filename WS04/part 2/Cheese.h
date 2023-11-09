/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #4 (PART 2)
Cheese Module
File	Cheese.h
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Oct 07, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

#include <iostream>
#include <string>

namespace sdds {

    class Cheese {
        //the name of the cheese, defaults to NaC - "Not a Cheese"
        std::string m_name{ "NaC" };
        //the weight/amount in grams of the cheese
        int m_weight{};
        //he price per gram of the cheese
        double m_price{};
        //description of the features/qualities of the cheese
        std::string m_desc{};

    public:
        Cheese() {};//a default constructor
        //1 arg constructor
        Cheese(const std::string& str);

        //copy constructor and copy assigment
        Cheese(const Cheese&);
        Cheese& operator=(const Cheese&);
       
        //setters and setter
        void setWeight(int);
        int getWeight()const;
        std::string getName()const;
        std::string getDesc() const;
        double getPrice() const;

        //modifier that receives as a parameter a weight/amount of cheese to slice from the current cheese object.
        Cheese slice(size_t weight);

        //print the cheese
        std::ostream& print(std::ostream& os) const;

    };
    //overload <<
    std::ostream& operator<<(std::ostream& os, const Cheese& cheese);
    
    //helper to trim
    std::string trimSpace(const std::string& str);





}

#endif 