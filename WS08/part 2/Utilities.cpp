/*************** WS 08_02 ********************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
 Date of completion: 2023-11-18

 I have done all the coding by myself and only copied the code that my professor
 provided to complete my workshops and assignments.
**************************************************************************************/

// Workshop 8 - Smart Pointers
// 2019/11 - Cornel

#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
        // TODO: Add your code here to build a collection of Profiles.
        //         The result should contain only profiles from `allProfiles`
        //         which are not in `bannedProfiles` using Raw Pointers.
        for (size_t i = 0; i < allProfiles.size(); ++i) { //looping through good
            bool isBanned = false;

            for (size_t j = 0; j < bannedProfiles.size() && !isBanned; ++j) { //looping through bad
                //For each profile from the first parameter that is not banned,  Two profiles are considered same if they have same age and name.
                      //same age                                                   //same first name
                if ((allProfiles[i].m_age == bannedProfiles[j].m_age) && ((allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name) &&
                    //same last name
                    (allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name))) {
                    isBanned = true;
                }
            }


            //For each profile from the first parameter that is not banned,
            if (!isBanned) {
                // allocates dynamic memory of Profile typeand copies the profile.
                Profile* t_person = new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);
                bool ok = true;

                //Your function then validates the Profile object (using validateAddress() you created above) and adds it to result.
                try {
                    t_person->validateAddress(); //checkign if address is good
                }
                catch (const std::string& err) {  //if not 
                    ok = false;  //not good
                    delete t_person; //delete person
                    throw; //throw
                }
                if (ok) {  //if good add person
                    result += t_person;
                }
                //delete the temp
               delete t_person;
            }
        }
        // Your function returns a copy of result.
        return result;
    }


	DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		// TODO: Add your code here to build a collection of Profiles.
		//		   The result should contain only profiles from `allProfiles`
		//         which are not in `bannedProfiles` using Smart Pointers.
        for (size_t i = 0; i < allProfiles.size(); ++i) { //looping through good
            bool isBanned = false;

            for (size_t j = 0; j < bannedProfiles.size() && !isBanned; ++j) { //looping through bad
                //For each profile from the first parameter that is not banned,  Two profiles are considered same if they have same age and name.
                      //same age                                                   //same first name
                if ((allProfiles[i].m_age == bannedProfiles[j].m_age) && ((allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name) &&
                    //same last name
                    (allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name))) {
                    isBanned = true;
                }
            }


            //For each profile from the first parameter that is not banned,
            if (!isBanned) {
                // allocates dynamic memory of Profile typeand copies the profile.
                unique_ptr<Profile> t_person(new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age));

                bool ok = true;

                //Your function then validates the Profile object (using validateAddress() you created above) and adds it to result.
                try {
                    t_person->validateAddress(); //checkign if address is good
                }
                catch (const std::string& err) {  //if not 
                    ok = false;  //not good
                    throw; //throw
                }
                if (ok) {  //if good add person
                    result += t_person;
                }
            
            }
        }
        // Your function returns a copy of result.
        return result;
	}
}
