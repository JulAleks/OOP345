/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #4 (PART 1)
Cheese Module
File	Cheese.cpp
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Oct 02, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#include <iomanip>
#include <iostream>
#include <string>
#include "Cheese.h"


namespace sdds {
    //constructor that receives the cheese's details as a string; this constructor is responsible for extracting information about the cheese from the string and storing the tokens in the instance's attributes
    Cheese::Cheese(const std::string& str)
    {
        //temp veriables 
        std::string name, desc;
        int weight;
        double price;

        //finding the first comma
        size_t comma1 = str.find(",");
        if (comma1 != std::string::npos) { //if its not the end of string
            name = trimSpace(str.substr(0, comma1)); //call trimmer to remove the spaces up to comma position and assign it to name of Cheese

            size_t comma2 = str.find(",", comma1 + 1); //finding the second comma
            if (comma2 != std::string::npos) {//if its not the end of string
                weight = std::stoi(trimSpace(str.substr(comma1 + 1, comma2 - comma1 - 1))); //call trimmer, first location is the end of previous+1, minus the current comma location from previous-1, to remove the spaces up to comma position and assign it to weight

                size_t comma3 = str.find(",", comma2 + 1); //3d comma
                if (comma3 != std::string::npos) {
                    price = std::stod(trimSpace(str.substr(comma2 + 1, comma3 - comma2 - 1))); //assign price

                    size_t start = comma3 + 1; //getting the begining of the desc position 3d commas position+1
                    while (start < str.size()) { //looping until the end of string 
                        size_t comma4 = str.find(",", start);  //finding 4th comma 
                        if (comma4 != std::string::npos) {  //checking that the end of the strign is not where the comma is 
                            desc += trimSpace(str.substr(start, comma4 - start)) + " "; //calling trimmer to remove extra space and add it to separate desc words
                            start = comma4 + 1; //assign a new startign position
                        }
                        else {  //if it is the end of string 
                            desc += trimSpace(str.substr(start));  //tring the spaces
                            start = str.size(); //break out of the while loop 
                        }
                    }
                }
            }
        }
        //assign the values 
        m_name = name;
        m_weight = weight;
        m_price = price;
        m_desc = desc;
    }


    //Rule of 5
    Cheese::Cheese(Cheese& c)
    {
        *this = c;
    }


    Cheese& Cheese::operator=(Cheese& c)
    {
        if (this != &c && !c.m_name.empty()) { 
            m_name = c.getName();
            m_price = c.getPrice();
            m_weight = c.getWeight();
            m_desc = c.getDesc();
        }
        return *this;
    }


    //setters 
    void Cheese::setName(const std::string& na) 
    {
        if (!na.empty()) {
            m_name = na;
        }
    }
    void Cheese::setWeight(int gr)
    {
        if (gr > 0) {
            m_weight = gr;
        }

    }
    void Cheese::setPrice(double pr)
    {
        if (pr > 0) {
            m_price = pr;
        }
    }
    void Cheese::setDesc(const std::string& dc)
    {
        if (!dc.empty()) {
            m_desc = dc;
        }
    }

    //getters
    std::string Cheese::getName()
    {
        return  m_name;
    }
    int Cheese::getWeight()
    {
        return m_weight;
    }
    double Cheese::getPrice()
    {
        return m_price;
    }
    std::string Cheese::getDesc()
    {
        return m_desc;
    }


    //modifier that receives as a parameter a weight/amount of cheese to slice from the current cheese object.
    Cheese Cheese::slice(size_t weight)
    {
        Cheese t_cheese;
        //if there is enough cheese to make this slice (weight <= weight of the cheese in current object)
        int tot = m_weight - static_cast<int>(weight); //casting to avoid possible loss of data warning 
        if (tot >= 0) {
            // then return a copy of current cheese with the desired weight. Update the current object's weight after slicing.
            t_cheese = *this; 
            t_cheese.setWeight(weight);
            setWeight(tot);
        }
       //If there isn't enough cheese, then return a cheese object that is in an empty state instead.
        return  t_cheese;
    }

    //printing fucntion
    std::ostream& Cheese::print(std::ostream& os) const
    {
        std::cout <<"|"<< std::setw(21)<<std::left<< m_name << "|" << std::setw(5)<< m_weight <<"|" << std::fixed << std::setprecision(2) <<std::setw(5)<< m_price<< "|"<< std::setw(33) << std::right<< m_desc << " |" <<std::endl;
        return os;
    }

    //overload the insertion operator to insert the contents of a Cheese object into an ostream 
    std::ostream& operator<<(std::ostream& os, const Cheese& c)
    {
        c.print(os);
        return os;
    }


    //trimming helper
    std::string trimSpace(const std::string& str)
    {
        size_t firstSpace = str.find_first_not_of(' ');
        if (std::string::npos == firstSpace) {
            return str;
        }
        size_t lastSpace = str.find_last_not_of(' ');
        return str.substr(firstSpace, (lastSpace - firstSpace + 1));
    }

}
