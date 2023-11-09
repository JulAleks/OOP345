/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #6 (PART 2)
File Module
File	File.h
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  2023-11-04
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/
#ifndef SDDS_FILE_H
#define SDDS_FILE_H

#include <iostream>
#include "Resource.h"

namespace sdds
{
    class File : public Resource {
        std::string m_contents{}; //stores the contents of a file
    public:
        File() {}; //default
        File(const std::string name, const std::string text = "");
        ~File() {};

        void update_parent_path(const std::string&); // sets the parent path to the parameter.

        NodeType type() const;// a query that returns Flags::FILE

        std::string path() const;// a query that returns the full absolute path of the file(concatenates the absolute path locationand the file name).

        std::string name() const; //a query that returns the name of the file.

        int count() const; //a query that returns - 1

        size_t size() const; //a query that returns the size of the file in bytes.For simplicity, this is the number of characters in m_contents attribute.

    };



}

#endif
