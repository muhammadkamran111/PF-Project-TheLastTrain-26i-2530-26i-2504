#include "physics.h"
#include "switches.h"
using namespace std;

bool isDirectlyconnected(int fromF, int fromR, int toF, int toR,const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],char& outConnType)
{
    outConnType = CONN_NONE;

    if ( fromF < 1 || fromF > NUM_FLOORS || toF < 1 || toF > NUM_FLOORS || fromR < 1 || fromR > ROOMS_PER_FLOOR || toR < 1 || toR > ROOMS_PER_FLOOR )
    {
        return false;
    }

    if ( fromF == toF && fromR == toR )
    {
        return false;
    }

    //Lift 1 functionality
    if ((fromF == 1 || fromF == 2) && (toF == 1 || toF == 2) && (fromR == 2 || fromR == 3) && (toR == 2 || toR == 3))
    {
        outConnType = '1';
        return true;
    }

    //Horizontal Movements : 
    if (fromF == toF && (toR == fromR + 1 || toR == fromR - 1))
    {
        int leftRoom = (fromR < toR) ? fromR : toR;
        char conn = horizontalConn[fromF - 1][leftRoom - 1];
        outConnType = conn;
        if (conn == CONN_DOOR || conn == CONN_WINDOW || conn == CONN_LOCKED_DOOR) 
        {
            return true;
        }
        return false;

    }

    //Stairs movements : S1,S2,S3

    if (fromR == 1 && toR == 1) 
    {
        bool isS1 = (fromF == 1 && toF == 2) || (fromF == 2 && toF == 1);
        bool isS2 = (fromF == 2 && toF == 3) || (fromF == 3 && toF == 2);
        bool isS3 = (fromF == 4 && toF == 5) || (fromF == 5 && toF == 4);

        if (isS1 || isS2 || isS3) 
        {
            outConnType = 'S';
            return true;
        }
    }

    //Lift 2 functionality : 

    if (fromR == 4 && toR == 4) 
    {
        bool validFrom = (fromF == 2 || fromF == 4 || fromF == 5);
        bool validTo = (toF == 2 || toF == 4 || toF == 5);
        if (validFrom && validTo) 
        {
            outConnType = '2';
            return true;
        }
    }

    return false;

}

// Function to check if the player can traverse to a target room based on connection type and inventory : 

bool canTraverse(int targetFloor, int targetRoom, char connType, const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, int emergencyTripsLeft, bool lift2Operational) 
{
    if (targetFloor < 1 || targetFloor > NUM_FLOORS || targetRoom < 1 || targetRoom > ROOMS_PER_FLOOR) 
    {
        return false;
    }

    if (connType == CONN_DOOR || connType == CONN_WINDOW || connType == 'S' || connType == '1') 
    {
        return true;
    }

    if (connType == CONN_LOCKED_DOOR) 
    {
        return unlockFloor3Door(inventory, inventoryCount);
    }

    if (connType == '2') 
    {
        return (lift2Operational || emergencyTripsLeft > 0);
    }

    return false;
}

// Update Energy and Time based on delta values, ensuring they remain within valid bounds

void applyResourceDelta(int& energy, int& time, int deltaEnergy, int deltaTime) 
{
    energy = energy + deltaEnergy;
    if (energy < 0) energy = 0;
    if (energy > MAX_ENERGY) energy = MAX_ENERGY;

    time = time + deltaTime;
    if (time < 0) time = 0;
    if (time > 100) time = 100;
}

//Apply points to score :

void applyScoreDelta(int& score, int deltaScore) 
{
    score = score + deltaScore;
}

//Checking the availability of an item in the inventory based on its symbol representation

bool hasItem(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, char itemSymbol) 
{
    for (int a = 0; a < inventoryCount; a++) 
    {
        if (inventory[a] == itemSymbol) 
        {
            return true;
        }
    }
    return false;
}

//This function adds an item to inventory :

bool addItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol) 
{
    if (inventoryCount >= MAX_INVENTORY_CAPACITY) 
    {
        return false;
    }
    inventory[inventoryCount] = itemSymbol;
    inventoryCount++;
    return true;
}

//This function removes an item from inventory :(if matching)

bool removeItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol) 
{
    int foundIndex = -1;
    for (int a = 0; a < inventoryCount; a++) 
    {
        if (inventory[a] == itemSymbol) 
        {
            foundIndex = a;
            break;
        }
    }

    if (foundIndex == -1) 
    {
        return false;
    }

    for (int a = foundIndex; a < inventoryCount - 1; a++) 
    {
        inventory[a] = inventory[a + 1];
    }
    inventoryCount--;
    inventory[inventoryCount] = ENT_NONE;
    return true;
}








