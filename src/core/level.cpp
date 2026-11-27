#include "level.h"
#include "util.h"
#include <fstream>
#include <iostream>
using namespace std;

// A function to check if character is one of the valid game entities or not?

static bool isValidEntity(char ch)
{
    if (ch == ENT_MASTER_KEY || ch == ENT_ENERGY_PACK || ch == ENT_EMERGENCY_TOOLKIT || ch == ENT_CLUE_4 || ch == ENT_FUSE || ch == ENT_CAT || ch == ENT_CONTROL_PANEL || ch == ENT_LIFT_PASS || ch == ENT_PASSENGER || ch == ENT_MEDICAL_KIT || ch == ENT_EMERGENCY_CARD || ch == ENT_CLUE_2 || ch == ENT_CLUE_7 || ch == ENT_CABINET_TRAIN_KEY || ch == ENT_CAT_CARRIER || ch == ENT_OBSERVATION_TOKEN)
    {
        return true;
    }
    return false;
}

//Checking that is line start with valid given prefix or not.

static bool startsWith(const char* line, const char* prefix)
{
    int a = 0;
    while (prefix[a] != '\0')
    {
        if (line[a] != prefix[a])
        {
            return false;
        }
        a++;
    }
    return true;
}

// A function to find integer value after : in a line. i.i(energy: 10)

static int readIntAfterColon(const char* line, int defaultVal)
{
    int a = 0;
    while (line[a] != '\0' && line[a] != ':')  a++;
    if (line[a] == '\0')   return defaultVal;

    a++; 

    while (line[a] == ' ' || line[a] == '\t') 
    {
        a++;
    }

    int sum = 0;
    bool foundDigit = false;
    while (line[a] >= '0'  &&  line[a] <= '9') 
    {
        sum = sum * 10 + (line[a] - '0');
        foundDigit = true;
        a++;
    }

    if (!foundDigit) 
    {
        return defaultVal;
    }
    return sum;

}

//THis is used to build ascii buliding map from building.txt

bool loadBuildingMap(const char* filename, char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1], char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM], int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR])
{

    //initialization of all arrays :
    for (int a = 0; a < NUM_FLOORS; a++) 
    {
        for (int b = 0; b < ROOMS_PER_FLOOR - 1; b++) 
        {
            horizontalConn[a][b] = CONN_NONE;
        }
        for (int b = 0; b < ROOMS_PER_FLOOR; b++) 
        {
            entityCounts[a][b] = 0;
            for (int c = 0; c < MAX_ENTITIES_PER_ROOM; c++) 
            {
                roomEntities[a][b][c] = ENT_NONE;
            }
        }
    }

    ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }
    char line[MAX_LINE_LEN];
    char entityLine[MAX_LINE_LEN];
    int floorLoaded = 0;

    while (file.getline(line, MAX_LINE_LEN))
    {
        int foundFloor = -1;
        int pos = 0;
        while (line[pos] != '\0') 
        {
                    if (line[pos] == 'F' && line[pos + 1] >= '1' && line[pos + 1] <= '5' && line[pos + 2] == '-' && line[pos + 3] == 'R' && line[pos + 4] == '1') 

        }
    }
        
    


}