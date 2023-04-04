#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, map<int,int>& mapShifts, int row, int col);

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

		map<int, int> mapShifts;
		// for(int i = 0; i < avail[0].size(); i++){
		// 	mapShifts[i] = 0;
		// }
		sched.resize(avail.size());
		for(int i = 0; i < sched.size(); i++){
			sched[i].resize(dailyNeed);
			for(int j = 0; j < dailyNeed; j++){
				sched[i][j] = -1;
			}
		}
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, mapShifts, 0, 0);
    

}


bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, map<int,int>& mapShifts, int row, int col){
    if(row==sched.size()){
        return true;
    }
    if(col==dailyNeed){
        return scheduleHelper(avail,dailyNeed,maxShifts,sched,mapShifts,row+1,0);
    }
		if(sched[row][col]==-1){
			for(int i = 0; i < avail[0].size(); i++){
				 bool notFound = true;
				 if(find(sched[row].begin(),sched[row].end(),i)!=sched[row].end()) notFound = false;
        sched[row][col] = i;
				mapShifts[i]++;
        if(avail[row][i]==1 && mapShifts[i]<=maxShifts && notFound){
            bool status = scheduleHelper(avail,dailyNeed,maxShifts,sched,mapShifts,row, col+1);
            if(status) return true;
        }
				mapShifts[i]--;
				
    	}
			sched[row][col] = -1;
			return false;
		}
    else return scheduleHelper(avail,dailyNeed,maxShifts,sched,mapShifts,row,col+1);
}

