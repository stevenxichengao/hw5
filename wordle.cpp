#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(string& in, std::string& tempFloating, const std::string& floating, const std::set<std::string>& dict, int i, std::set<std::string>& res, int numberDashes);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
	std::set<std::string> res;
	string temp = in;
	string tempFloating = floating;
	int numberDashes = 0;
	for(int i = 0; i < temp.size(); i++){
		if(temp[i]=='-') numberDashes++;
	}
	wordleHelper(temp, tempFloating, floating, dict, 0, res, numberDashes);
	return res;
}

// Define any helper functions here
void wordleHelper(string& in, std::string& tempFloating, const std::string& floating, const std::set<std::string>& dict, int i, std::set<std::string>& res, int numberDashes){
	if(i==in.length()){
		if(dict.find(in)!=dict.end()) {
			res.insert(in);
			//cout<<in<<endl;
		}
		return;
	}

	if(in[i] == '-'){
		//if # '-' != number of floating left
		//cout << numberDashes << endl;
			if(numberDashes!=tempFloating.size()){
				for(int j = 0; j < 26; j++){
					in[i] = 'a'+j;
					//if a+j is afloating, remove it
					bool wasFloating = false;
					if(tempFloating.find('a'+j)!=string::npos) {
						tempFloating.erase(tempFloating.find('a'+j),1);
						wasFloating = true;
						//in[i]='-';
						//numberDashes++;
					}
					numberDashes--;
					
					wordleHelper(in, tempFloating, floating, dict, i+1, res, numberDashes);
					numberDashes++;
					//string temp = in[i];
					in[i] = '-';
					//if a+j was floating, reinsert it;
					if(wasFloating) {
						//tempFloating.insert(floating.find('a'+j), to_string(tempChar));
						tempFloating+='a'+j;
					}
				}
			}
			else{
				//cout << 0000000000000000<< endl;
				
				for(int j = 0; j < tempFloating.size(); j++){
						in[i] = tempFloating[j];
						char tempChar = tempFloating[j];
						int pos = tempFloating.find(tempChar);
						string tempString = tempFloating;
						tempFloating = tempFloating.erase(tempFloating.find(tempChar),1);
						numberDashes--;
						wordleHelper(in, tempFloating, floating, dict, i+1, res, numberDashes);
						numberDashes++;
						in[i]='-';
						tempFloating = tempString;
				}
				//tempFloating = floating;
			}
				//in[i] = '-';
	}
	else wordleHelper(in, tempFloating, floating, dict, i+1, res, numberDashes);
}