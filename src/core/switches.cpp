#include "switches.h"
#include "util.h"
#include "physics.h"
using namespace std;

//This function is for functionality of lift one. Which goes from floor one to floor 2 : 

bool canUseLift1(int fromFloor , int toFloor)
{
    if ((fromFloor == 1 || fromFloor == 2) && (toFloor == 1 || toFloor == 2))
    {
        return true;
    }
    return false;
}

//This function is for functionality of lift two. Which goes between floor 2,4,5 and lift pass or emergency trip is required : 

bool canUseLift2(int fromFloor, int toFloor, bool lift2operational, int emergencyTripsleft)
{
    bool validFrom = (fromFloor == 2 || fromFloor == 4 || fromFloor == 5);
    bool validTo = (toFloor == 2 || fromFloor == 4 || fromFloor == 5);
    if (!validFrom || !validTo || fromFloor == toFloor) return false;
    if (lift2operational || emergencyTripsleft > 0) return true;
    return false;
}


