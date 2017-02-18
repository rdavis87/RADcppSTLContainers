
/*START OF SPECIFICATIONS***************************************************
*
* Projec Name:  radCppSTLContainers - Sample code showing use of C++ Standard Template Library
*                                     classes and functions.
*
* File Name: radCppSTLContainers.cpp
*
* RandomDataFill                    - Function to fill in a Data structure with random data.
* PrintElement                      - Function to output to screen the data in a Data structure.
* Note: PrintData are overloaded functions.
* PrintData                         - Function to output to screen the entire list of data.
* PrintData                         - Function to output to screen the entire vector of data. 
* TestVectors                       - Function to test the use of vector template
* TestDblLinkList                   - Function to test the use of doubly linked list template
*
* DESCRIPTION: This file contains code to to create and use STL container classes
*
* Copyright (C) <2017> <Robert A. Davis>
* All rights reserved.
*
* This software may be modified and distributed under the terms
* of the MIT license.  See the LICENSE.TXT file for details.
*
* FUNCTIONS/ACTIONS IN
* THIS FILE:
*
*
* CHANGE LOG:
*
* DATE       FLAG	       Ref. No.	    CHANGE DESCRIPTION
* ----       ----------    --------	    -------------------------------------
* 02/14/17   V10RAD00 	                Initial coding
*
*END OF SPECIFICATIONS*******************************************************/


#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iomanip>

/*
* Data structure used with example container code 
*/
typedef struct data {
	std::string s;
	int i;
	double d;
} Data;

/* define int min and max length of string randomly generated for Data.s field */
#define MAX_S_SIZE 8
#define MIN_S_SIZE 3

/* override < operator to provide a default sort by the i field */
bool operator<(const Data &Data1, const Data &Data2) {
	return Data1.i < Data2.i;
}
/* descending sort function for i field needed for list sorting*/
bool DataSortDesci(const Data &Data1, const Data &Data2) { return (Data2.i < Data1.i); }
/* functions to sort Data using field d*/
bool DataSortd(const Data &Data1, const Data &Data2) { return (Data1.d < Data2.d); }
bool DataSortDescd(const Data &Data1, const Data &Data2) { return (Data2.d < Data1.d); }

/* function to sort Data using field s*/
bool DataSorts(const Data &Data1, const Data &Data2) { return (Data1.s < Data2.s); }
bool DataSortDescs(const Data &Data1, const Data &Data2) { return (Data2.s < Data1.s); }

/*
** RandomDataFill - Function to fill in a Data structure with random data.
**
**   Parameters:
**      Data - reference to a data structure to fill in.
**
** - Return value: none.
*/
void RandomDataFill(Data &Data) {
	int i, j;
	char Buffer[20];

	Data.i = rand() % 100; // keep numbers to reasonable size.
	Data.d = (rand() % 100) + 1 / ((rand() % 10) + .1); // keep numbers to reasonable size.
	/* create a random null terminated string of various sizes */
	j = rand() % (MAX_S_SIZE + 1);
	if(j < MIN_S_SIZE) 
		j = MIN_S_SIZE;
	for (i = 0; i < j; i++)
		Buffer[i] = 'a' + (rand() % 26);
	Buffer[i] = '\0';
	Data.s = Buffer;
	return;
}

/*
** PrintElement - Function to output to screen the data in a Data structure.
**
**   Parameters:
**      Data - reference to a data structure to fill in.
**
** - Return value: none.
*/
void PrintElement(Data &Data) {
	std::cout << "s = " << Data.s << "," << "i = " << Data.i << "," << "d = " << Data.d << std::endl;
}

/*
** PrintData - Function to output to screen the entire list of data.
**
**   Parameters:
**      List - reference to a list container.
**
** - Return value: none.
*/
void PrintData(std::list<Data> &List) {
    std::list<Data>::iterator it;

	for (it = List.begin(); it != List.end(); it++)
		PrintElement(*it);
	std::cout << std::endl;
}

/*
** PrintData - Function to output to screen the entire vector of data.
**
**   Parameters:
**      Array - reference to a Array container.
**
** - Return value: none.
*/
void PrintData(std::vector <Data> &Array) {
	for (unsigned int i = 0; i < Array.size(); i++)
		PrintElement(Array[i]);
	std::cout << std::endl;
}

/*
** TestVectors - Function to test the use of vector template
**
**   Parameters: None.
**
** - Return value: none.
*/
void TestVectors() {
	std::vector <Data> Array(5);  // start out with 5 elements
	Data Data;
	unsigned int i;

	/*
	* fill in the vector with some random generated data and print it using the Array notation method of access.
	*/
	std::cout << "Initial vector data" << std::endl;
	for (i = 0; i < Array.size(); i++) 
		RandomDataFill(Array[i]);
	PrintData(Array);

	/* add another element to the Array letting vector template handle resizing */
	std::cout << "element pushed on the back" << std::endl;
	RandomDataFill(Data);
	Array.push_back(Data);
	PrintData(Array);

	/* remove last element and print again*/
	std::cout << "last element popped off" << std::endl;
	Array.pop_back();
	PrintData(Array);

	/* manually increase vector size and add element with Array notation */
	std::cout << "element added to the end using Array notation" << std::endl;
	Array.resize(Array.size() + 1);
	RandomDataFill(Array[Array.size() - 1]);
	PrintData(Array);

	/* insert a new item into a random location and print */
	std::cout << "element randomly inserted" << std::endl;
	Array.insert(Array.begin() + (rand() % (Array.begin() - Array.end() - 1)), Data);
	PrintData(Array);

	/* delete an item at a random location */
	std::cout << "random element deleted" << std::endl;
	Array.erase(Array.begin() + (rand() % (Array.size() - 1)));
	PrintData(Array);

	/* delete 2 items at a random location */
	std::cout << "two sequential elements from a random position deleted" << std::endl;
	i = rand() % (Array.size() - 1);
	Array.erase(Array.begin() + i, Array.begin() + i + 2);
	PrintData(Array);

	/* time to sort the vector in ascending order of i values (uses operator < override */
	std::cout << "sort ascending by i field" << std::endl;	
	std::sort(Array.begin(), Array.end());
	PrintData(Array);

	/* sort the vector in descending order of i values (uses operator < override */
	std::cout << "sort descending by i field" << std::endl;
	std::sort(Array.rbegin(), Array.rend()); 
	PrintData(Array);

	/* to sort on the d or s fields we have to use a comparison function for those fields 
	* first sort on d */
	std::cout << "sort ascending by d field" << std::endl;
	std::sort(Array.begin(), Array.end(), DataSortd);
	PrintData(Array);

	/* sort the vector in descending order of d */
	std::cout << "sort descending by d field" << std::endl;
	std::sort(Array.rbegin(), Array.rend(), DataSortd);
	PrintData(Array);;

	/* sort ascemdomg on the s fields  */
	std::cout << "sort ascending by s field" << std::endl;
	std::sort(Array.begin(), Array.end(), DataSorts);
	PrintData(Array);

	/* sort the vector in descending order of s */
	std::cout << "sort descending by s field" << std::endl;
	std::sort(Array.rbegin(), Array.rend(), DataSorts);
	PrintData(Array);

	/* that should take care of the majority of common uses of vectors */
}

/*
** TestDblLinkList - Function to test the use of doubly linked list template
**
**   Parameters: None.
**
** - Return value: none.
*/
void TestDblLinkList() {
	std::list<Data> DataList, TempList;
	std::list<Data>::iterator it;
	Data Data;
	int i;

	/* show list is empty */
	std::cout << "DataList is " << (DataList.empty() ? "empty" : "not empty") << std::endl;

	/* put 5 items with some random generated data into the list */
	for (i = 0; i < 5; i++) {
		RandomDataFill(Data);
		DataList.push_back(Data);
	}
	/* show list is not empty */
	std::cout << "DataList is " << (DataList.empty() ? "empty" : "not empty") << std::endl;

	/* there is no random access into the list as there is with the vector so we have to work from one end to the other */
	std::cout << "initial list of data" << std::endl;
	PrintData(DataList);

	/* add another element to the front of the list */
	std::cout << "element added to front of list" << std::endl;
	RandomDataFill(Data);
	DataList.push_front(Data);
	PrintData(DataList);

	/* insert an element randomly into the list */
	std::cout << "element added randomly to list by iterating through the list to a random location" << std::endl;
	RandomDataFill(Data);
	it = DataList.begin();
	std::advance(it, (int)(rand() % DataList.size()));  // move the iterator forward to our random spot
	DataList.insert(it, Data);
	PrintData(DataList);

	/* delete an element randomly from the list */
	std::cout << "element deleted randomly from the list by iterating through the list to a random location" << std::endl;
	it = DataList.begin();
	std::advance(it, (int)(rand() % DataList.size()));  // move the iterator forward to our random spot
	DataList.erase(it);
	PrintData(DataList);

	/* time to sort the list in ascending order of i values (uses operator < override */
	std::cout << "sort ascending by i field" << std::endl;
	DataList.sort(operator<);
	PrintData(DataList);

	/*sort the list in descending order of i values */
	std::cout << "sort descending by i field" << std::endl;
	DataList.sort(DataSortDesci);
	PrintData(DataList);

	/* sort the list in ascending order of d values  */
	std::cout << "sort ascending by d field" << std::endl;
	DataList.sort(DataSortd);
	PrintData(DataList);

	/*sort the list in descending order of d values */
	std::cout << "sort descending by d field" << std::endl;
	DataList.sort(DataSortDescd);
	PrintData(DataList);

	/* sort the list in ascending order of s values  */
	std::cout << "sort ascending by s field" << std::endl;
	DataList.sort(DataSorts);
	PrintData(DataList);
	
	/*sort the list in descending order of s */
	std::cout << "sort descending by s field" << std::endl;
	DataList.sort(DataSortDescs);
	PrintData(DataList);

	/* reverse the list */
	std::cout << "reverse the list" << std::endl;
	DataList.reverse();
	PrintData(DataList);

	/* put 3 items with some random generated data into the TempList */
	std::cout << "create a temporary list" << std::endl;
	for (i = 0; i < 3; i++) {
		RandomDataFill(Data);
		TempList.push_back(Data);
	}
	PrintData(TempList);

	/* splice the temp list into the main list at a random location */
	std::cout << "splice the temp list into the main list at random location" << std::endl;
	it = DataList.begin();
	std::advance(it, (int)(rand() % DataList.size()));  // move the iterator forward to our random spot
	DataList.splice(it, TempList);
	PrintData(DataList);

	/* create another temp list and sort both ascending on d then merge temp into the main list */
	std::cout << "create a temporary list to add to the main list after sorting them on d" << std::endl;
	for (i = 0; i < 3; i++) {
		RandomDataFill(Data);
		TempList.push_back(Data);
	}
	TempList.sort(DataSortd);
	PrintData(TempList);
    DataList.sort(DataSortd);
	DataList.merge(TempList, DataSortd);
	PrintData(DataList);

	/* that should take care of the majority of common uses of doubly linked lists */
}

int main()
{
	srand((unsigned int)time(NULL)); // seed the random number generator
	std::cout << std::fixed << std::setprecision(2); // set precision to only output to two decimal places
	TestVectors();
	TestDblLinkList();
    return 0;
}

