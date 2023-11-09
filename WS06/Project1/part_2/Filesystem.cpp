/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #6 (PART 2)
Fielsystem Module
File	Filesystem.cpp
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  2023-11-04
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/
#include <fstream>
#include "Filesystem.h"
namespace sdds
{
    //a custom constructor that receives the name of a file as its first argument, and an optional string containing the name of the root directory (defaults to an empty string). 
    Filesystem::Filesystem(std::string f_name, std::string r_name)
    {
        std::ifstream file(f_name);  
        if (file) {  //validating before doing anything 
            //alocate memory
            m_root = new Directory(r_name);
            m_current = m_root;

            std::string line;
            while (std::getline(file, line)) {
                if (!line.empty()) {

                    std::string path, contents, dirName;
                    size_t pos = line.find('|');  //splitting the line into path and content 
                    if (pos != std::string::npos) {
                        path = trimSpace(line.substr(0, pos));  //first path
                        contents = trimSpace(line.substr(pos + 1)); //then content 
                    }
                    else {
                        path = trimSpace(line); //no contant just path
                    }

                    std::vector<std::string> pathParts; // vector of all path parts 
                    size_t start = 0;
                    while (start < path.length()) {
                        size_t end = path.find('/', start); // splitting with /
                        if (end == start) {
                            // No '/' found, add the entire path as a single part
                            pathParts.push_back(path);

                        }
                        if (end == std::string::npos) {
                            end = path.length();
                        }
                        if (path.substr(start, end - start).find('.') != std::string::npos) {
                            pathParts.push_back(path.substr(start, end - start));
                        }
                        else {
                            pathParts.push_back(path.substr(start, end - start) + "/");
                        }
                        start = end + 1;
                    }


                    Directory* currDir = m_root;  //starting at the root 

                    for (const std::string& comp : pathParts) {
                        if (comp.find('.') != std::string::npos) {  //checking if it is a file 
                            //if it's a file creating a new file
                            File* newFile = new File(pathParts.back(), contents);
                            currDir->operator+=(newFile);
                        }
                        else {
                            //if we have this dir, it is our current dir 
                            if (currDir->find(comp) && currDir->find(comp)->type() == NodeType::DIR) {
                                currDir = dynamic_cast<Directory*>(currDir->find(comp));
                            }
                            else {
                                //if we didn't find it, create new dir
                                Directory* newDirectory = new Directory(comp);
                                currDir->operator+=(newDirectory);
                                currDir = newDirectory;
                            }
                        }
                    }
                }
            }
        }   
        else {
            throw std::runtime_error("Error");
        }
    }
 
    //distructor
    Filesystem::~Filesystem()
    {
        delete m_root;
    }

    Filesystem::Filesystem(Filesystem&& rhs) noexcept
    {
        *this = std::move(rhs);
    }

    Filesystem& Filesystem::operator=(Filesystem&& rhs) noexcept
    {
        if (this != &rhs) {                                     
            m_root = rhs.m_root;
            m_current = rhs.m_current;

            rhs.m_root = nullptr;
            rhs.m_current=nullptr;
        }
        return *this;
    }

    //adds a resource to the current directory.
    Filesystem& Filesystem::operator+=(Resource* src)
    {
       
        m_current->operator+=(std::move(src));
        return *this;
    }

    //changes the current directory to the directory (located in the current directory) whose name matches argument.
    Directory* Filesystem::change_directory(const std::string& dir_name) {
        //if an empty string is passed, change the current directory to the root directory
        if (dir_name.empty()) {
            m_current = m_root;
            return m_current;
        }
       
        // Use m_current->find() to locate the directory by name
        Resource* targetDir = m_current->find(dir_name);

        //check if dir exists and is a directory
        if (targetDir && targetDir->type() == NodeType::DIR) {
            m_current = dynamic_cast<Directory*>(targetDir);
            return m_current;
        }

  
            //if no directory with the specified name exists report an std::invalid_argument exception with the message Cannot change directory! DIR_NAME not found!".
            throw std::invalid_argument("Cannot change directory! " + dir_name + " not found.");
        
    }

    //a query that returns the current directory
    Directory* Filesystem::get_current_directory() const
    {
        return m_current;
    }

  
    //trimmer
    std::string trimSpace(const std::string& str)
    {
        size_t start = str.find_first_not_of(" \t");
        if (start == std::string::npos) {
            return "";
        }

        size_t end = str.find_last_not_of(" \t");
        return str.substr(start, end - start + 1);
    }
}