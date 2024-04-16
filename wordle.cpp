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

    wordleHelper(inTemp, floatingTemp, dict, 0, valid);
    return valid;
}

// Define any helper functions here
void wordleHelper(
    std::string& in,
    std::string& floating,
    const std::set<std::string>& dict,
    int pos,
    std::set<std::string>& valid) {

    // base case 1: if string is completed and a valid word
    if (pos == in.length() && dict.find(in) != dict.end()) {

        // add valid word to set
        valid.insert(in);       
        return;
    }


    // base case 2: if string is complete but not valid
    if (pos == in.length()) {
        return;
    }

    // recursive case: string isn't complete

    // if there are any floating characters, place them in unique combinations
    if (floating.length() != 0) {
        for (int i = 0; i < in.length(); ++i) {
            if (in[i] == '-') {
                // set current string pos to first floating character
                in[i] = floating[0];
                // remove first floating character from string
                std::string updatedFloating = floating.substr(1, floating.length() - 1);

                // recursive call with updated in and floating strings
                wordleHelper(in, updatedFloating, dict, 0, valid);

                // revert changes
                in[i] = '-';
            }
        }

    }
    // if there aren't any floating characters, place a - z in remaining empty positions
    else {
        // skip to next position if current position is filled
        if (in[pos] == '-') {
            // iterate through each letter
            for (int i = 0; i < 26; ++i) {
                // update in
                in[pos] = 'a' + i;

                // further recurse next letter position 
                wordleHelper(in, floating, dict, pos + 1, valid);

                // revert in
                in[pos] = '-';
            }
        }
        else {
            // recurse to next position without making any changes
            wordleHelper(in, floating, dict, pos + 1, valid);
        }
    }
}
