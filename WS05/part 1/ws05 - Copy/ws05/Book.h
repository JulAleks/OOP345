/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #5 (PART 1)
Book Module
File	Book.h
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Oct 9, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/
#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>
#include <string>
namespace sdds {

 
    class Book {
        std::string b_author{};
        std::string b_title{};
        std::string b_country{};
        size_t b_year{};
        double b_price{};
        std::string b_desc{};

    public:
        //constructors
        Book() {};
        Book(const std::string& strBook); // a constructor that receives a reference to an unmodifiable string that contains information about the book;


        //setters/getters
        void setEmpty();
        void setAuth(std::string);
        void setTitle(std::string);
        void setDesc(std::string);
        void setCount(std::string);
        void setYear(size_t);
        void setPrice(double);

        Book& getBook();
        const std::string& Author() const; //get authot
        const std::string& title() const; //a query that returns the title of the book
        const std::string& country() const; // a query that returns the publication country
        const std::string& desc() const; // a query that returns the description country
        const size_t& year() const; // a query that returns the publication year
        double& price(); // a function that returns the price by reference, allowing the client code to update the price

        //rule of 5
        Book(Book&);
        Book operator=(Book&);
        Book(Book&&) noexcept;;
        Book operator=(Book&&) noexcept;;
        //~Book() no need because no DMA 


        std::ostream& display(std::ostream& os) const; //display fucntion 


    };
    //overload the insertion operator to insert the content of a book object into an ostream object
    std::ostream& operator<<(std::ostream& os, const Book& book);

    //helper to trim
    std::string trimSpace(const std::string& str);




}
#endif;
