

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

/*
backtracking algo explanation:
each column is a worker
recurse at top left and go across the rows and then down
if you assigned them a max number of shifts, skip to next worker
get through all workers without being able to advanced to next row/column
recurison stops and then you return false
if you recurse to the non existent row, recursion has gone all the way through and you return true
*/

bool solveHelper(std::map<Worker_T, int>& workerspertype, const AvailabilityMatrix& avail, const size_t dailyNeed, DailySchedule& sched, size_t rday, size_t caval);


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
//fill the map based on workers per number

    map<Worker_T, int> workerspertype;
    for(unsigned int i = 0; i < avail[0].size(); i++){
      workerspertype.insert(make_pair(i, maxShifts));
    }

//fill the schedule, baesd on avalibility 
    vector<Worker_T> g(dailyNeed, INVALID_ID);
    for(unsigned int i = 0; i<avail.size();i++){
      sched.push_back(g);
    }

    //call the recursive function
    bool result = solveHelper(workerspertype, avail, dailyNeed, sched, 0, 0);
    return result;
}

bool solveHelper(std::map<Worker_T, int>& workerspertype, const AvailabilityMatrix& avail, const size_t dailyNeed, DailySchedule& sched, size_t rday, size_t caval) {
  if(rday == sched.size()) return true; //if you reached the end return true
  else{
    //backtracking algo
  for(unsigned int i = 0U; i < avail[rday].size(); i++){
    if(std::find(sched[rday].begin(), sched[rday].begin()+caval, i)!= sched[rday].begin()+caval){
      continue;
    }
    //if their avalible that day
    if(avail[rday][i] == true && workerspertype[i] > 0){
        bool z = false;
        workerspertype[i]-=1; //subtract that workers avalibility
        sched[rday][caval] = i; //set schedule accordingly 

        if(caval != sched[rday].size()-1){
          z = solveHelper(workerspertype, avail, dailyNeed,sched,rday,caval+1U); //recursive call through next column
        }
        else{
          z = solveHelper(workerspertype, avail, dailyNeed,sched,rday+1U,0U); //recursive call through next row and resetting column
        }
        if(z==true) return z;
        workerspertype[i]+=1;
        sched[rday][caval] = INVALID_ID;
    }
  }
  }
  //if you've not reached the end return false
    return false;

}
