/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #4 (PART 2)
Cheese Shop Module
File	CheeseShop.cpp
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Oct 07, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#include <iomanip>
#include <iostream>
#include <string>
#include "CheeseShop.h"


namespace sdds {
 

    //CheeseShop(const std::string& name): a constructor that receives as a parameter the name of the shop. The default value for the parameter is "No Name".
    CheeseShop::CheeseShop(const std::string& name): s_name(name) {}

    void CheeseShop::setEmpty() //set an empty cheese
    {
        delete[] s_cheese;
        s_cheese = nullptr;
    }

    //copy shop constructor
    CheeseShop::CheeseShop(CheeseShop& rhs)
    {
        *this = rhs;
    }

    //equal shop assignment 
    CheeseShop& CheeseShop::operator=(const CheeseShop& rhs)
    {
        if (this != &rhs && rhs.s_num >0) {
            if (s_cheese != nullptr)
                for (auto i = 0u; i < s_num; ++i) {
                    delete s_cheese[i];
                    s_cheese[i] = nullptr;
                }

            setEmpty(); //clearing DMA and setting to empty

            s_num = rhs.s_num; //setting num lhs cheese to rhs 

            s_cheese = new const Cheese * [s_num]; //setting DMA loc to new cheese ptr a size of cheeseNum

            for (auto i = 0u; i < s_num; ++i) { //looping and calling copy construcor from cheese
                if (rhs.s_cheese[i] != nullptr) {
                    s_cheese[i] = new Cheese(*rhs.s_cheese[i]); 
                }
            }
            s_name = rhs.s_name;
        }
        return *this;
    }

    //move constructor
    CheeseShop::CheeseShop(CheeseShop&& rhs) noexcept
    {
        *this = std::move(rhs);
    }

    //equal move shop assignment 
    CheeseShop& CheeseShop::operator=(CheeseShop&& rhs) noexcept
    {
        if (this != &rhs && rhs.s_num > 0) {
            for (auto i = 0u; i < s_num; ++i) {
                delete s_cheese[i];
                s_cheese[i] = nullptr;
            }
            if (s_cheese != nullptr)
                for (auto i = 0u; i < s_num; ++i) {
                    delete s_cheese[i];
                    s_cheese[i] = nullptr;
                }

            setEmpty(); //clearing DMA and setting to empty
            s_num = std::move(rhs.s_num);

            //moving rhs to lhs
            s_cheese = std::move(rhs.s_cheese);
            s_name = std::move(rhs.s_name);
          
            //cleaning 
            rhs.s_num = 0;
            rhs.s_cheese = nullptr;
        }
        return *this;
    }


    //distructor
    CheeseShop::~CheeseShop()
    {
        for (auto i = 0u; i < s_num; ++i) {
            delete s_cheese[i];
            s_cheese[i] = nullptr;
        }     
        setEmpty();
    }

    //In order to add another cheese, this class should resize the array of pointers using DMA (dynamic memory allocation). 
    //The CheeseShop will be adding/storing copies of the Cheese passed through the parameter.
    CheeseShop& CheeseShop::addCheese(const Cheese& rhs)
    {
        const Cheese** t_shop = new const Cheese * [s_num + 1];  //creating temp cheese
        
        //copy current cheese to temp
        for (auto i = 0u; i < s_num; ++i) {
            t_shop[i] = s_cheese[i];
        }

        //add rhs cheese to temp, and increase tot cheeses 
        t_shop[s_num] = new Cheese(rhs);
        
        s_num++;

        // empty current cheese if not empty
      
            setEmpty();
        

        // update lhs cheese to temp
        s_cheese = t_shop;
        return *this;
    }


    std::ostream& CheeseShop::print(std::ostream& os) const
    {
        div(1,26, s_name);
       
        if (s_num == 0) {
           
            os<<"This shop is out of cheese!"<<std::endl;
            
        }
        else {
            for (auto i = 0u; i < s_num; i++) {
               
               os<< *s_cheese[i];
            }
        }
        div(2, 26, "");

        return os;
    }

    std::ostream& operator<<(std::ostream& os, const CheeseShop& s)
    {
        s.print(os);
        return os;
    }

    void div(size_t choice, size_t cnt, const std::string heading)
    {
        switch (choice) {
        case 1:
            for (auto i = 0u; i < cnt; ++i) {
                std::cout << "-";
            }
            std::cout << std::endl;
            if (heading != "") {
                std::cout << heading << std::endl;
            }
            else {
                std::cout << std::endl;
            }
            for (auto i = 0u; i < cnt; ++i) {
                std::cout << "-";
            }
            
            std::cout << std::endl;
            break;
        case 2:
           for (auto i = 0u; i < cnt; ++i) {
                std::cout << "-";
            }
            std::cout << std::endl;
            break;
           
        }
    }
}