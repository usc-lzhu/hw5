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


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> valid;
    std::string inTemp = in;
    std::string floatingTemp = floating;

    std::cout << "here " << std::endl;

    wordleHelper(inTemp, floatingTemp, dict, 0, valid);
    std::cout << "here " << std::endl;
    return valid;
}

// Define any helper functions here
void wordleHelper(
    std::string& in,
    std::string& floating,
    const std::set<std::string>& dict,
    int pos,
    std::set<std::string>& valid) {

    // std::cout << "\n\nhere 0" << std::endl;
    // std::cout << "\tpos: " << pos << std::endl;
    // std::cout << "\tin: " << in << std::endl;
    // if (floating.length() != 0) {
    //     std::cout << "here 00" << std::endl;
    //     std::cout << "\tfl: " << floating << std::endl;
    // }


    // base case 1: if string is completed and a valid word
    if (pos == in.length() && dict.find(in) != dict.end()) {
        // std::cout << "here 1" << std::endl;

        // add valid word to set
        valid.insert(in);
        // std::cout << "inserted " << in << std::endl;
        
        // std::cout << "here 2" << std::endl;

        return;
        // std::cout << "here 22" << std::endl;
    }

    // std::cout << "here 10" << std::endl;


    // base case 2: if string is complete but not valid
    if (pos == in.length()) {
        // std::cout << "here 3" << std::endl;
        return;
    }

    // std::cout << "here 20" << std::endl;

    // recursive case: string isn't complete

    // if there are any floating characters, place them in unique combinations
    if (floating.length() != 0) {
        // std::cout << "here 4" << std::endl;

        for (int i = 0; i < in.length(); ++i) {
            // std::cout << "here 41" << std::endl;
            if (in[i] == '-') {
                // std::cout << "here 411" << std::endl;
                // set current string pos to first floating character
                in[i] = floating[0];
                // remove first floating character from string
                // std::cout << "here 42" << std::endl;
                std::string updatedFloating = floating.substr(1, floating.length() - 1);
                // std::cout << "updatedFloating: " << updatedFloating << std::endl;

                // std::cout << "here 43" << std::endl;
                // recursive call with updated in and floating strings
                // std::cout << "recursive call 1" << std::endl;
                wordleHelper(in, updatedFloating, dict, 0, valid);
                // std::cout << "here 44" << std::endl;

                // revert changes
                in[i] = '-';
                // floating = originalFloating;
            }
        }

    }
    // if there aren't any floating characters, place a - z in remaining empty positions
    else {
        if (in[pos] == '-') {
            for (int i = 0; i < 26; ++i) {
                in[pos] = 'a' + i;

                wordleHelper(in, floating, dict, pos + 1, valid);

                in[pos] = '-';
            }
        }
        else {
            wordleHelper(in, floating, dict, pos + 1, valid);
        }
    }
}
