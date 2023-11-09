/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #5 (PART 2)
Movie Module
File	Movie.h
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Oct 15, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H

#include <iostream>
#include <string>
#include "Book.h" //adding to use trimmer

namespace sdds {

    class Movie {
        std::string m_title{};
        int m_year{};
        std::string m_desc{};
    public:
        void setEmpty();
        Movie() {};
        Movie(const std::string& strMovie);

        //rule of 5
        Movie(const Movie&);
        Movie& operator=(const Movie&);
        Movie(Movie&&) noexcept;
        Movie& operator=(Movie&&) noexcept;
        //~Movie() no need because no DMA 

        void setTitle(const std::string);
        void setYear(const int);
        void setDesc(const std::string);

        const std::string& title() const;

        //void fixSpelling(T& spellChecker): a templated function. This function calls the overloaded operator() on instance spellChecker, passing to it the movie title and description
        template <typename T>
        void fixSpelling(T& spellChecker) {
            spellChecker(m_title);
            spellChecker(m_desc);
        }

        std::ostream& display(std::ostream& os) const; //display fucntion 

    };

    //overload the insertion operator to insert the content of a book object into an ostream object
    std::ostream& operator<<(std::ostream& os, const Movie& movie);



}
#endif
