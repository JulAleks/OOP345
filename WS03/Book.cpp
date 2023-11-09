
/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #3 (PART 1)
Book Module
File	Book.cpp
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Sep 25, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/
#include <iostream>
#include <iomanip>
#include "Book.h"
#include <string>


namespace sdds {

    //3 arg constructor
    Book::Book(const std::string& title, unsigned nChapters, unsigned nPages) 
        : m_title(title), m_numChapters(nChapters), m_numPages(nPages)
    {
    }

   
    bool Book::operator>(const Book& rhs) const
    {
        return m_numPages/m_numChapters > rhs.m_numPages / rhs.m_numChapters;
    }

    bool Book::operator<(const Book& rhs) const
    {
        return m_numPages / m_numChapters < rhs.m_numPages / rhs.m_numChapters;
    }


    //print ostream function
    std::ostream& Book::print(std::ostream& os) const
    {
        if (!m_title.empty()){
        std::string books = m_title + "," + std::to_string(m_numChapters) + "," + std::to_string(m_numPages);
        std::string test=" (" + std::to_string(static_cast<double>(m_numPages) / m_numChapters) + ") ";
        os << std::setw(56) << std::right << books<<std::setw(2)<<"|" << std::setw(16) << std::left << test;
        }
        else {
            os << "|" << " Invalid book data";
        }
        return os;
    }

    //overload operator for ostream
   std::ostream& operator<<(std::ostream& os, const Book& bk)
  {
       bk.print(os);
       return os;
  }




}