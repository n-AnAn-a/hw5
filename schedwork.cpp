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
bool backtrack(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, std::vector<size_t>& shiftCount, size_t day, size_t slot);

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
    size_t n = avail.size();
    size_t k = avail[0].size();
    sched.resize(n);
    vector<size_t> shiftCount(k, 0);
    return backtrack(avail, dailyNeed, maxShifts, sched, shiftCount, 0, 0);
}

bool backtrack(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftCount, size_t day, size_t slot
)
{
    size_t n = avail.size();
    size_t x = avail[0].size();

    if(day == n) {
        return true; // schedule completed
    }

    if(slot == dailyNeed) {
        return backtrack(avail, dailyNeed, maxShifts, sched, shiftCount, day + 1, 0);
    }

    for(Worker_T w = 0; w < x; ++w) {
        if(avail[day][w] && shiftCount[w] < maxShifts) {
            // check if already assigned on this day
            bool alreadyAssigned = false;
            for(Worker_T assigned : sched[day]) {
                if(assigned == w) {
                    alreadyAssigned = true;
                    break;
                }
            }
            if(alreadyAssigned) continue;

            sched[day].push_back(w);
            shiftCount[w]++;

            if(backtrack(avail, dailyNeed, maxShifts, sched, shiftCount, day, slot + 1)) {
                return true;
            }

            sched[day].pop_back(); // undo
            shiftCount[w]--;       // undo
        }
    }
  return false;
}
