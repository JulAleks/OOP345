/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #5 (PART 2)
Movie Module
File	Movie.cpp
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
#include <string>
#include "SpellChecker.h"
#include "Movie.h"


namespace sdds {
    void Movie::setEmpty()
    {
        m_title = "";
        m_year = 0;
        m_desc = "";
    }
    //receives the movie through a reference to a string. This constructor extracts the information about the movie from the string and stores the tokens in the attributes. 
    Movie::Movie(const std::string& strMovie)
    {
        std::string t_title{};
        int t_year{};
        std::string t_desc{};

        //finding the first comma
        size_t comma1 = strMovie.find(",");
        if (comma1 != std::string::npos) {
            t_title = trimSpace(strMovie.substr(0, comma1));

            size_t comma2 = strMovie.find(",", comma1 + 1);
            if (comma2 != std::string::npos) {
                t_year = std::stoi(trimSpace(strMovie.substr(comma1 + 1, comma2 - comma1 - 1)));
                t_desc = trimSpace(strMovie.substr(comma2 + 1));
            }
        }

        setTitle(t_title);
        setYear(t_year);
        setDesc(t_desc);
    }

    Movie::Movie(const Movie& rhs)
    {
        *this = rhs;
    }

    Movie& Movie::operator=(const Movie& rhs)
    {
        if (this != &rhs) {
            setTitle(rhs.m_title);
            setYear(rhs.m_year);
            setDesc(rhs.m_desc);
        }
        else {
            return *this;
        }
        return *this;
    }

    Movie::Movie(Movie&& rhs) noexcept
    {
        *this = std::move(rhs);
    }

    Movie& Movie::operator=(Movie&& rhs) noexcept
    {
        if (this != &rhs) {
            setTitle(std::move(rhs.m_title));
            setYear(std::move(rhs.m_year));
            setDesc(std::move(rhs.m_desc));
            rhs.setEmpty();
        }

        return *this;
    }

    void Movie::setTitle(const std::string n)
    {
        if (!n.empty()) {
            m_title = n;
        }
    }

    void Movie::setYear(const int y)
    {
        if (y > 0) {
            m_year = y;
        }
    }

    void Movie::setDesc(const std::string d)
    {
        if (!d.empty()) {
            m_desc = d;
        }
    }


    //a query that returns the title of the movie
    const std::string& Movie::title() const
    {
        return m_title;
    }

    //overload the insertion operator to insert the content of a movie object into an ostream object,
    std::ostream& Movie::display(std::ostream& os) const
    {
       os << std::setw(40) << m_title << " | " << std::setw(4) << m_year << " | " << std::setw(40) << m_desc<<std::endl;
       return os;
    }

    std::ostream& operator<<(std::ostream& os, const Movie& movie)
    {
        movie.display(os);
        return os; 
    }

}