#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }

    sched.clear();
    // Add your code below

    // create a vector filled with default -1 values with a size of n days x d daily workers
    for (int i = 0; i < avail.size(); ++i) {
        sched.push_back(std::vector<Worker_T>(dailyNeed, 0));
    }

    // create a vector filled with default 0 with size of k workers
    std::vector<int> occurences(avail[0].size(), 0);
    
    // call helper function
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, occurences, 0, 0);
}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<int>& occurences,
    int row,
    int col
)
{

    // base case 1: traversed through entire sched matrix without backtracking
    if (row == sched.size()) {
        return true;
    }

    // base case 2: traversed through an entire day
    if (col == sched[0].size()) {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, occurences, row + 1, 0);
    }

    // recursive case: traversing through a day

    // iterate through each worker's availability for one day
    for (int i = 0; i <= avail[0].size(); ++i) {
        // update schedule and occurences
        sched[row][col] = i;
        ++occurences[i];

        // check if worker won't go over max shifts and is available
        if (occurences[i] <= maxShifts && avail[row][i]) {
            // recurse further if current state is valid
            if (scheduleHelper(avail, dailyNeed, maxShifts, sched, occurences, row, col + 1)) {
                // return true if recursed to end
                return true;
            }
        }

        // revert occurences
        --occurences[i];
    }

    sched[row][col] = 0;

    // return false if previous recursive calls weren't true
    return false;

}
