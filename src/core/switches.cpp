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
    bool validTo = (toFloor == 2 || toFloor == 4 || toFloor == 5);
    if (!validFrom || !validTo || fromFloor == toFloor) return false;
    if (lift2operational || emergencyTripsleft > 0) return true;
    return false;
}

//Floor three locked door. Required master key '<' to access floor 3.
bool unlockFloor3Door(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount)
{
    return hasItem(inventory, inventoryCount, ENT_MASTER_KEY);
}

//This Function is for Fuse '*'
bool installFuseControlPanel(char inventory[MAX_INVENTORY_CAPACITY], int &inventoryCount, bool objectives[NUM_OBJECTIVES], int& score)
{
   if (objectives[OBJ_FUSE_INSTALLED]) 
   {
        return false; 
   }
   if (!hasItem(inventory, inventoryCount, ENT_FUSE))
   {
    return false; 
   }
   removeItem(inventory, inventoryCount, ENT_FUSE);
   objectives[OBJ_FUSE_INSTALLED] = true;
   applyScoreDelta(score, SCORE_INSTALL_FUSE);

   if (objectives[OBJ_LIFT_PASS])
   {
    objectives[OBJ_LIFT2_ACTIVE] = true;
   }
   return true;
}

bool verifyCabinetCode(const char* enteredCode, const bool objectives[NUM_OBJECTIVES])
{
    if (!objectives[OBJ_CLUE_4] || !objectives[OBJ_CLUE_2] || !objectives[OBJ_CLUE_7])
    {
        return false;
    }
    
    return stringEquals(enteredCode, "427");
}


