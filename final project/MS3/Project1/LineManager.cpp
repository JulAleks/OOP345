/*************** MS 3 - Line Manager Module - LineManager.cpp ********************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
 Date of completion: 2023-11-21

 I confirm that I am the only author of this file
 and the content was created entirely by me.
*************************************************************************/
/*
The LineManager class manages an assembly line of active stations
*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<algorithm>
#include "Workstation.h"
#include "LineManager.h"
#include "Utilities.h"
namespace sdds {


	//this constructor receives the name of the file that identifies the active stations on the assembly line (example: AssemblyLine.txt) and the collection of workstations available for configuring the assembly line.
    sdds::LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        if (!file.empty()) {
            try {
                std::ifstream fin(file);

                if (fin.fail()) {
                    throw std::string("Cannot open file"); //file cannot be opened
                }

                std::string line, current="", next = "";
                while (std::getline(fin, line)) {
                    if (!line.empty()) {
                        bool more = true;
                        size_t startPos = 0u;

                        current = extractToken(line, startPos, more); // get current workstation
                        
                        //if more extract next
                        if (more) {
                            next = extractToken(line, startPos, more);
                        }

                        //is current station exist
                        auto cStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* stat) { 
                            return stat->getItemName() == current; 
                            });

                        //if it does
                        if (cStation != stations.end()) {
                            //and next station avalible
                            if (!next.empty()) {
                                //look for next station existance
                                auto nStation = std::find_if(stations.begin(), stations.end(),[&](Workstation* nStat) { 
                                    return nStat->getItemName() == next;
                                    });

                                //if it does assign it to be the next station
                                if (nStation != stations.end() && current != next) {
                                    (*cStation)->setNextStation(*nStation);
                                }
                            }
                            //store the stations in m_activeLine
                            m_activeLine.push_back(*cStation);
                        }
                    }
                }

                fin.close(); // close the file

                // find first stat without next stat
                auto find = std::find_if(stations.begin(), stations.end(), [&](Workstation* st) {
                    // check if no next stat exist
                    auto n_find = std::find_if(stations.begin(), stations.end(), [&](Workstation* st2) {
                        // if it is found than next stat is not the last one
                        return st2->getNextStation() == st;
                        });
                //if it is not found than there is no next stat
                return n_find == stations.end();
                    });

                //if the fist find is not the end of station assign first stat
                if (find != stations.end()) {
                    m_firstStation = *find;
                }

                //update the attribute that holds the total number of orders in the g_pending queue 
                m_cntCustomerOrder = g_pending.size();
            }
            catch (...) { //If something goes wrong, this constructor reports an error. 
                throw std::string("Something went wrong");//If something goes wrong, this constructor reports an error. 
            }
        }
        else {
            throw std::string("bad file name"); // throw an error for a bad file name.
        }
    }

  
    
    

    /*this modifier reorders the workstations present in the instance variable m_activeLine (loaded by the constructor) and stores the reordered collection in the same instance variable.
    The elements in the reordered collection start with the first station, proceeds to the next, and so forth until the end of the line. */
	void LineManager::reorderStations()
	{
        if (!m_activeLine.empty() || m_firstStation != nullptr) {
            
            std::vector<Workstation*> tempLine; //temp vector to sort the line

           //make current station the fisr station 
            Workstation* currentStation = m_firstStation;

            //orgenize until no more 
            while (currentStation != nullptr) {
                //push back cuttentStation 
                tempLine.push_back(currentStation);

                //move next station
                currentStation = currentStation->getNextStation();
            }

            //update active line to the reorgnized vector
            m_activeLine = std::move(tempLine);
        }
	}

    //this modifier performs one iteration of operations on all of the workstations in the current assembly line 
	bool LineManager::run(std::ostream& os)
	{
        //keeps track of the current iteration number (use a local variable)
        static size_t i = 0u;

        //inserts into stream os the iteration number (how many times this function has been called by the client) in the format Line Manager Iteration: COUNT<endl>
        os << "Line Manager Iteration: " << ++i << std::endl;

        //moves the order at the front of the g_pending queue to the m_firstStation and remove it from the queue. This function moves only one order to the line on a single iteration.
        if (!g_pending.empty()) {
          *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        //for each station on the line, executes one fill operation
        for (const auto &item : m_activeLine) {
            item->fill(os);   
        }
        //attempts to move an order down the line
        for (const auto& item : m_activeLine) {
            item->attemptToMoveOrder();
        }

        //return true if all customer orders have been filled or cannot be filled, otherwise returns false
        bool ok;
        ok = (m_cntCustomerOrder == (g_completed.size() + g_incomplete.size()));
        return ok;
	}

	void LineManager::display(std::ostream& os) const
	{
        //this query displays all active stations on the assembly line in their current order
        for (const auto& station : m_activeLine) {
            station->display(os);
        }
	}

}