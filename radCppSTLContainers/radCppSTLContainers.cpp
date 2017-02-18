
/*START OF SPECIFICATIONS***************************************************
*
* Projec Name:  radCppSTLContainers - Sample code showing use of C++ Standard Template Library
*                                     classes and functions.
*
* File Name: radCppSTLContainers.cpp
*
* RandomDataFill                    - Function to fill in a Data structure with random data.
* PrintData                         - Function to output to screen the data in a Data structure.
* TestVectors                       - Function to test the use of vector template
* TestDblLinkList                   - Function to test the use of doubly linked list template
*
* DESCRIPTION: This file contains code to to create and use STL container classes
*
* Copyright (C) <2017> <Robert A. Davis>
* All rights reserved.
*
* This software may be modified and distributed under the terms
* of the RAD license.  See the LICENSE,TXT file for details.
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

//using namespace std;

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
/* function to sort Data using field d*/
bool DataSortd(const Data &Data1, const Data &Data2) { return (Data1.d < Data2.d); }
/* function to sort Data using field s*/
bool DataSorts(const Data &Data1, const Data &Data2) { return (Data1.s < Data2.s); }
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
	Data.d = (rand() % 100) + 1 / ((rand() % 100) + 1); // keep numbers to reasonable size.
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
** PrintData - Function to output to screen the data in a Data structure.
**
**   Parameters:
**      Data - reference to a data structure to fill in.
**
** - Return value: none.
*/
void PrintData(Data &Data) {
	std::cout << "s = " << Data.s << "," << "i = " << Data.i << "," << "d = " << Data.d << std::endl;
}

/*
** TestVectors - Function to test the use of vector template
**
**   Parameters: None.
**
** - Return value: none.
*/
void TestVectors() {
	std::vector <Data> array(5);  // start out with 5 elements
	Data Data;
	unsigned int i;

	/*
	* fill in the vector with some random generated data and print it using the array notation method of access.
	*/
	for (i = 0; i < array.size(); i++) 
		RandomDataFill(array[i]);
	for (i = 0; i < array.size(); i++)
		PrintData(array[i]);
	std::cout << std::endl;

	/* add another element to the array letting vector template handle resizing */
	RandomDataFill(Data);
	array.push_back(Data);
	for (i = 0; i < array.size(); i++) // should now print 6 elements
		PrintData(array[i]);
	std::cout << std::endl;

	/* remove last element and print again*/
	array.pop_back();
	for (i = 0; i < array.size(); i++) // should now print 5 elements again
		PrintData(array[i]);
	std::cout << std::endl;

	/* manually increase vector size and add element with array notation */
	array.resize(array.size() + 1);
	RandomDataFill(array[array.size() - 1]);
	for (i = 0; i < array.size(); i++) // should now print 6 elements again
		PrintData(array[i]);
	std::cout << std::endl;

	/* insert a new item into a random location and print */
	array.insert(array.begin() + (rand() % (array.begin() - array.end() - 1)), Data);
	for (i = 0; i < array.size(); i++) // should now print 7 elements again
		PrintData(array[i]);
	std::cout << std::endl;

	/* delete an item at a random location */
	array.erase(array.begin() + (rand() % (array.size() - 1)));
	for (i = 0; i < array.size(); i++) // should now print 6 elements again
		PrintData(array[i]);
	std::cout << std::endl;

	/* delete 2 items at a random location */
	i = rand() % (array.size() - 1);
	array.erase(array.begin() + i, array.begin() + i + 2);
	for (i = 0; i < array.size(); i++) // should now print 6 elements again
		PrintData(array[i]);
	std::cout << std::endl;

	/* time to sort the vector in ascending order of i values (uses operator < override */
	std::sort(array.begin(), array.end());
	for (i = 0; i < array.size(); i++) // should now print 6 elements again
		PrintData(array[i]);
	std::cout << std::endl;

	/* sort the vector in descending order of i values (uses operator < override */
	std::sort(array.rbegin(), array.rend());
	for (i = 0; i < array.size(); i++) // should now print 6 elements again
		PrintData(array[i]);
	std::cout << std::endl;

	/* to sort on the d or s fields we have to use a comparison function for those fields 
	* first sort on d */
	std::sort(array.begin(), array.end(), DataSortd);
	for (i = 0; i < array.size(); i++) // should now print 6 elements again
		PrintData(array[i]);
	std::cout << std::endl;

	/* sort the vector in descending order of d */
	std::sort(array.rbegin(), array.rend(), DataSortd);
	for (i = 0; i < array.size(); i++) // should now print 6 elements again
		PrintData(array[i]);
	std::cout << std::endl;

	/* sort on the s fields  */
	std::sort(array.begin(), array.end(), DataSorts);
	for (i = 0; i < array.size(); i++) // should now print 6 elements again
		PrintData(array[i]);
	std::cout << std::endl;

	/* sort the vector in descending order of s */
	std::sort(array.rbegin(), array.rend(), DataSorts);
	for (i = 0; i < array.size(); i++) // should now print 6 elements again
		PrintData(array[i]);
	std::cout << std::endl;

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
	std::list<Data> DataList;
	std::list<Data>::iterator it;
	Data Data;
	int i, j;

	/* show list is empty */
	std::cout << "list is " << (DataList.empty() ? "empty" : "not empty") << std::endl;

	/*
	* put 5 items with some random generated data into the list and print it out
	*/
	for (i = 0; i < 5; i++) {
		RandomDataFill(Data);
		DataList.push_back(Data);
	}
	/* there is no random access into the list as there is with the vector so we have to work from one end to the other */
	for (it = DataList.begin(); it != DataList.end(); it++)
		PrintData(*it);
	std::cout << std::endl;

	/* add another element to the front of the list */
	RandomDataFill(Data);
	DataList.push_front(Data);
	/* insert an element randomly into the list */
	RandomDataFill(Data);
	it = DataList.begin(); 
	it++;
	j = (int)(rand() % DataList.size());
	std::cout << "size of list = " << DataList.size() << " j = " << j << std::endl;

//	for(i = 0, it = DataList.begin(); i < j; it++);  // move the iterator forward to our random spot
	DataList.insert(it, Data);
	for (it = DataList.begin(); it != DataList.end(); it++)
		PrintData(*it);
	std::cout << std::endl;
}

int main()
{
	srand((unsigned int)time(NULL)); // seed the random number generator

	TestVectors();
	TestDblLinkList();
    return 0;
}

