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
    int pos = 0;
    std::string inTemp = in;
    std::string floatingTemp = floating;

    wordleHelper(inTemp, floatingTemp, dict, pos, valid);

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
        std::string originalFloating = floating;

        for (int i = 0; i < in.length(); ++i) {
            if (in[i] == '-') {
                // set current string pos to first floating character
                in[pos] == floating[0];
                // remove first floating character from string
                floating.substr(1, floating.length() - 1);

                // recursive call with updated in and floating strings
                wordleHelper(in, floating, dict, 0, valid);

                // revert changes
                in[i] = '-';
                floating = originalFloating;
            }
        }

    }
    // if there aren't any floating characters, place a - z in remaining empty positions
    else {
        bool changed = false;
        for (int i = 0; i < 26; i++) {
            if (in[pos] == '-') {
                // update in
                in[pos] == 'a' + i;
                changed = true;
            }
            
            // recursive call with updated in and pos variables
            wordleHelper(in, floating, dict, pos + 1, valid);

            // revert changes if any were made
            if (changed) {
                in[i] = '-';
            }
        }
    }





    // std::string originalFloating = floating;

    // // iterate through each floating letter
    // for (int i = 0; i < floating.length(); ++i) {

    //     if (in[pos] == "-") {
    //             // update in and floating
    //             in[pos] == floating[i];
    //             floating.substr(floating.begin() + 1);
    //     }

    //     // add valid word to set
    //     if (wordleHelper(in, floating, dict, ++pos, valid) == true) {
    //         valid.append(in);
    //     }
    //     // otherwise revert changes
    //     else {
    //         in[j] = "-";
    //         floating = originalFloating;
    //     }
    //     // // loop through all the letters in the string
    //     // for (int j = 0; j < in.length(); ++j) {

    //     //     // if the letter is currently unfilled
    //     //     if (in[j] == '-') {
    //     //         // update in and floating
    //     //         in[j] == floating[i];
    //     //         floating.substr(floating.begin() + 1);

    //     //         if (wordleHelper(in, floating, dict) != "-") {
    //     //             valid.append(in);
    //     //         }
    //     //         else {
    //     //             in[j] = "-";
    //     //         }
    //     //     }

    //     // }
    // }

    // bool changed = false;
    // for (int i = 0; i < 26; i++) {
    //     if (in[pos] == "-") {
    //         // update in
    //         in[pos] == 'a' + i;
    //         changed = true;
    //     }
        
    //     wordleHelper(in, floating, dict, pos + 1, valid);
    //     // revert changes if any were made
    //     if (changed) {
    //         in[j] = "-";
    //     }
    // }


}