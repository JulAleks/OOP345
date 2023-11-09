/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #6 (PART 2)
File Module
File	File.cpp
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  2023-11-04
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include "File.h"
#include "Flags.h"
namespace sdds
{

    // text representation of the contents of a file (optional, with empty string as a default value).
    File::File(const std::string name, const std::string text) : m_contents(text) {
        m_name = name; //the name of the file
    }

    // sets the parent path to the parameter
    void File::update_parent_path(const std::string& path)
    {
        m_parent_path = path;
    }

    //a query that returns Flags::FILE
    NodeType File::type() const
    {
        return NodeType::FILE;
    }

    //a query that returns the full absolute path of the file(concatenates the absolute path locationand the file name).
    std::string File::path() const
    {
        return m_parent_path+m_name;
    }

    //a query that returns the name of the file.
    std::string File::name() const
    {
        return m_name;
    }
    //a query that returns - 1
    int File::count() const
    {
        return -1;
    }

    //a query that returns the size of the file in bytes. For simplicity, this is the number of characters in m_contents attribute.
    size_t File::size() const
    {
        return m_contents.length();
    }



}


