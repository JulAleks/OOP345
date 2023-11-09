/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #5 (PART 1)
Book Module
File	Book.cpp
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Oct 9, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/


#include <iostream>
#include <iomanip>
#include <string>
#include "Book.h"
namespace sdds {


    //a constructor that receives a reference to an unmodifiable string that contains information about the book; this constructor extracts the information about the book from the string by parsing it and stores the tokens in the object's attributes
    Book::Book(const std::string& strBook)
    {
        std::string t_author;
        std::string t_title;
        std::string t_country;
        size_t t_year;
        double t_price;
        std::string t_desc;

        //finding the first comma
        size_t comma1 = strBook.find(",");
        if (comma1 != std::string::npos) {
            t_author = trimSpace(strBook.substr(0, comma1));

            size_t comma2 = strBook.find(",", comma1 + 1);
            if (comma2 != std::string::npos) {
                t_title = trimSpace(strBook.substr(comma1 + 1, comma2 - comma1 - 1));

                size_t comma3 = strBook.find(",", comma2 + 1);
                if (comma3 != std::string::npos) {
                    t_country = trimSpace(strBook.substr(comma2 + 1, comma3 - comma2 - 1));

                    size_t comma4 = strBook.find(",", comma3 + 1);
                    if (comma4 != std::string::npos) {
                        t_price = std::stod(trimSpace(strBook.substr(comma3 + 1, comma4 - comma3 - 1)));

                        size_t comma5 = strBook.find(",", comma4 + 1);
                        if (comma5 != std::string::npos) {
                            t_year = std::stoi(trimSpace(strBook.substr(comma4 + 1, comma5 - comma4 - 1)));
                            t_desc = trimSpace(strBook.substr(comma5 + 1));
                        }
                    }
                }
            }
        }

        setAuth(t_author);
        setTitle(t_title);
        setDesc(t_desc);
        setCount(t_country);
        setYear(t_year);
        setPrice(t_price);
    }

    void Book::setEmpty()
    {
        b_author.clear();
        b_title.clear();
        b_desc.clear();
        b_country.clear();
        b_year = 0;
        b_price = 0.0;
    }

    //setters
    void Book::setAuth(std::string a)
    {
        if (!a.empty()) {
            b_author = a;
        }
    }

    void Book::setTitle(std::string t)
    {
        if (!t.empty()) {
            b_title = t;
        }
    }

    void Book::setDesc(std::string d)
    {
        if (!d.empty()) {
            b_desc = d;
        }
    }

    void Book::setCount(std::string c)
    {
        if (!c.empty()) {
            b_country = c;
        }
    }

    void Book::setYear(size_t y)
    {
        if (y >= 0) {
            b_year = y;
        }
    }

    void Book::setPrice(double pr)
    {
        if (pr >=0) {
            b_price = pr;
        }
    }

    //getters
    const std::string& Book::Author() const
    {
        return b_author;
    }

    const std::string& Book::title() const
    {
        return b_title;
    }

    const std::string& Book::country() const
    {
        return b_country;
    }

    const std::string& Book::desc() const
    {
        return b_desc;
    }

    const size_t& Book::year() const
    {
        return b_year;
    }

    double& Book::price()
    {
        return b_price;
    }

    Book& Book::getBook() {
        return *this;
    }


    //rule of 5 (minus distructor no DMA)
    Book::Book(Book& rhs)
    {
        if (this != &rhs) {
            b_author = rhs.b_author;
            b_title = rhs.b_title;
            b_desc = rhs.b_desc;
            b_country = rhs.b_country;
            b_year = rhs.b_year;
            b_price = rhs.b_price;
        }
    }

    Book Book::operator=(Book& rhs)
    {
        if (this != &rhs) {
            b_author = rhs.b_author;
            b_title = rhs.b_title;
            b_desc = rhs.b_desc;
            b_country = rhs.b_country;
            b_year = rhs.b_year;
            b_price = rhs.b_price;
        }
        return *this;
    }
   

    Book::Book(Book&& rhs)noexcept
    {
        *this = std::move(rhs);
    }

    Book Book::operator=(Book&& rhs)noexcept
    {
        if (this != &rhs) {
            b_author = std::move(rhs.b_author);
            b_title = std::move(rhs.b_title);
            b_desc = std::move(rhs.b_desc);
            b_country = std::move(rhs.b_country);
            b_year = rhs.b_year;
            b_price = rhs.b_price;

            rhs.setEmpty();
        }
        return *this;
    }

    std::ostream& Book::display(std::ostream& os) const
    {
        os << std::right << std::setw(20) << b_author << " | " << std::setw(22) << b_title << " | " << std::setw(5) << b_country << " | "  << std::setw(4) <<b_year << " | " << std::fixed << std::setw(6) << std::setprecision(2) << b_price << " | " <<b_desc<<std::endl;
        return os;
    }


    //overload the insertion operator to insert the content of a book object into an ostream object,

    std::ostream& operator<<(std::ostream& os, const Book& book)
    {
        book.display(os);
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