/********************************** WS 09_01 ******************************************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
 Date of completion: 2023-11-20

 I have done all the coding by myself and only copied the code that my professor
 provided to complete my workshops and assignments.
**************************************************************************************/


// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant
// 2023/11/17 - Cornel

#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <thread>
#include "process_data.h"

namespace sdds
{
	// The following function receives array (pointer) as the first argument, number of array
	//   elements (size) as second argument, divisor as the third argument, and avg as fourth argument.
	//   size and divisor are not necessarily same. When size and divisor hold same value, avg will
	//   hold average of the array elements. When they are different, avg will hold a value called
	// 	 as average-factor. For part 1, you will be using same value for size and double. Use of
	//   different values for size and divisor will be useful for multi-threaded implementation in part-2.
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++) {
			avg += arr[i];
		}
		avg /= divisor;
	}

	// The following function receives array (pointer) as the first argument, number of array elements
	//   (size) as second argument, divisor as the third argument, computed average value of the data items
	//   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the
	//   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of
	//   the array elements. When they are different, var will hold a value called as variance factor.
	//   For part 1, you will be using same value for size and double. Use of different values for size
	//   and divisor will be useful for multi-threaded implementation in part-2.
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++) {
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}

	// The following constructor of the functor receives name of the data file, opens it in
	//   binary mode for reading, reads first int data as total_items, allocate memory space
	//   to hold the data items, and reads the data items into the allocated memory space.
	//   It prints first five data items and the last three data items as data samples.
	//   
	ProcessData::ProcessData(const std::string& filename) {
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//opens the file in binary mode 
		std::ifstream in(filename, std::ios::binary);

		if (in.fail()) {
			std::cout << "Error reading file";
		}
		else {
			//reads the total number of data items (first 4 bytes
			in.read(reinterpret_cast<char*>(&total_items), sizeof(total_items));

			//make new data array
			data = new int[total_items];

			//read the data items
			in.read(reinterpret_cast<char*>(data), total_items * sizeof(int));	
		}
		//close
		in.close();
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::cout << "Item's count in file '"<< filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
		          << data[total_items - 3] << ", " << data[total_items - 2] << ", "
		          << data[total_items - 1] << "]" << std::endl;
	}

	ProcessData::~ProcessData() {
		delete[] data;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data != nullptr;
	}

	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// TODO You create implementation of function operator(). See workshop instructions for details.
	int ProcessData::operator()(const std::string& target_file, double& avg, double& var) {
		/*
		You compute the average value by calling computeAvgFactor with the following parameters: data, total_items as the size of the array, and again total_items as divisor.
		The fourth argument is going to be a variable in which the computed average value is to be stored (received as parameter by this operator).
		*/
		computeAvgFactor(data, total_items, total_items, avg);


		/*
		You compute variance value by calling computeVarFactor with first, second and third arguments same as before, i.e., in the case of computeAvgFactor.
		The fourth argument is the average value computed by computeAvgFactor and fifth argument is the variable in which the computed variance is to be stored (received as parameter by this operator).
		*/
		computeVarFactor(data, total_items, total_items, avg, var);


		//You open the target data file and write the data (total_items, and data) in the format of the input data file data_int.dat
		try {
			std::fstream out(target_file, std::ios::out | std::ios::binary);
			if (out.is_open()) {
				// Write the total_items first
				out.write(reinterpret_cast<const char*>(&total_items), sizeof(total_items));

				// Write the data array
				out.write(reinterpret_cast<const char*>(data), total_items * sizeof(int));

				// Close the file
				out.close();
			}
			else {
				throw std::string("Cannot open file");
			}
		}
		catch (...) {
			throw std::string("Cannot write to file");
		}
		return 0; //no errors 
	}



}	




