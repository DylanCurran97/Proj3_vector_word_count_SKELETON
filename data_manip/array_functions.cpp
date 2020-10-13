
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include "../includes/array_functions.h"
#include "../includes/fileio.h"
#include "../includes/utilities.h"
/*============================================================================
 * The following are declarations for functions that I will test
 * Please provide the definitions in the
 * included cpp file, do not erase the stuff I put in there please
 * DO NOT MODIFY THIS FILE, I WILL USE MY OWN COPY
/============================================================================*/


	//zero out vector that tracks words and their occurrences
void KP::clear(std::vector<constants::entry>  &entries){
	entries.clear();

}

	//how many unique words are in the vector
int KP::getSize(std::vector<constants::entry>  &entries){
	int get = entries.size();
	return get;
}

	//get data at a particular location, if i>size() then get the last value in the vector
	//(this is lazy, should throw an exception instead)
	std::string KP::getWordAt(std::vector<constants::entry>  &entries, int i){

		if (i > entries.size()){
			return entries[entries.size()-1].word;
		}
		else {
			return entries[i].word;
		}
	}

int KP::getNumbOccurAt(std::vector<constants::entry>  &entries,int i){
	return entries[i].number_occurences;

}

	/*loop through whole file, one line at a time
	 * call processLine on each line from the file
	 * returns false: myfstream is not open
	 *         true: otherwise*/
bool KP::processFile(std::vector<constants::entry>  &entries,std::fstream &myfstream){
	// openFile function in fileio.cpp

	if(!myfstream.is_open()){
		return false;

	}
	std::string temp;
	while(getline(myfstream, temp)) {
		processLine(entries, temp);
		//possible KP
	}
	return true;

}

	/*take 1 line and extract all the tokens from it
	feed each token to processToken for recording*/
void KP::processLine(std::vector<constants::entry>  &entries,std::string &myString){
	std::stringstream ss(myString);
	std::string tempToken = "";
	while(getline(ss, tempToken, constants::CHAR_TO_SEARCH_FOR)) {
		processToken(entries, tempToken);
	}

}

	/*Keep track of how many times each token seen*/
void KP::processToken(std::vector<constants::entry>  &entries,std::string &token){

	std::string temp = token;
	strip_unwanted_chars(temp);
	std::string tempUncapped = temp;
	toUpper(temp);

	if(temp.size() == 0 ){
		return;
	}
	for (int i = 0; i<entries.size(); i++) {
		if (entries[i].word_uppercase == temp) {
			entries[i].number_occurences++;
			return;
		}
	}
	constants::entry newEntry = constants::entry();
	newEntry.number_occurences = 1;
	newEntry.word = tempUncapped;
	newEntry.word_uppercase = temp;
	entries.push_back(newEntry);
	return;
}

	bool occurrences(constants::entry entry1, constants:: entry entry2){
			return (entry1.number_occurences < entry2.number_occurences);
	}
	bool ascending(constants::entry entry1, constants:: entry entry2){
			return (entry1.word_uppercase < entry2.word_uppercase);

	}
	bool descending(constants::entry entry1, constants:: entry entry2){
			return (entry1.word_uppercase < entry2.word_uppercase);
	}
	/*
	 * Sort myEntryArray based on so enum value.
	 * Please provide a solution that sorts according to the enum
	 * The presence of the enum implies a switch statement based on its value
	 * See the course lectures and demo project for how to sort a vector of structs
	 */
void KP::sort(std::vector<constants::entry>  &entries, constants::sortOrder so){
	switch(so) {
	case constants::NONE:
		return;
		break;
	case constants::NUMBER_OCCURRENCES:
		std::sort(entries.begin(),entries.end(), occurrences);
		return;
		break;
	case constants::ASCENDING:
		std::sort(entries.begin(),entries.end(),ascending );
		return;
		break;
	case constants::DESCENDING:
		std::sort(entries.begin(),entries.end(), descending );

	}

}


