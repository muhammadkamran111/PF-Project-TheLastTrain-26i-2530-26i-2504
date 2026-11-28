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

// A function to find integer value after : in a line. i.e(energy:  10)

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
    int floorsLoaded = 0;

    while (file.getline(line, MAX_LINE_LEN))
    {
        int foundFloor = -1;
        int pos = 0;
        while (line[pos] != '\0') //This loop is used to find exact floor number:
        {
            if (line[pos] == 'F' && line[pos + 1] >= '1' && line[pos + 1] <= '5' && line[pos + 2] == '-' && line[pos + 3] == 'R' && line[pos + 4] == '1') 
            {
                foundFloor = line[pos + 1] - '1'; 
                break;
            }
            pos++;
        }

        if (foundFloor == -1) 
        {
            continue;
        }

        int roomStartPos[ROOMS_PER_FLOOR];
        int foundRooms = 0;

        for (int a = 0; line[a] != '\0' && foundRooms < ROOMS_PER_FLOOR; a++) //A loop to find the starting position of each room in the line
        {
            if (line[a] == 'F' && line[a + 1] == (char)('1' + foundFloor) &&
                line[a + 2] == '-' && line[a + 3] == 'R') 
            {
                roomStartPos[foundRooms] = a;
                foundRooms++;
            }
        }

        if (foundRooms != ROOMS_PER_FLOOR) 
        {
            continue;
        }

        // Checking Horizontal Conection between them:

        for (int a = 0; a < ROOMS_PER_FLOOR - 1; a++) 
        {
            int startScan = roomStartPos[a] + 5;
            int endScan = roomStartPos[a + 1];
            char conn = CONN_NONE;

            for (int b = startScan; b < endScan; b++) 
            {
                if (line[b] == 'L' && line[b + 1] == '1') //L1 is not a connection:
                {
                   
                    conn = CONN_NONE;
                    break;
                }
                if (line[b] == CONN_DOOR || line[b] == CONN_WINDOW || line[b] == CONN_LOCKED_DOOR || line[b] == CONN_SOLID_WALL) 
                {
                    conn = line[b];
                    break;
                }
            }
            horizontalConn[foundFloor][a] = conn;
        }

        if (file.getline(entityLine, MAX_LINE_LEN)) 
        {
            // Find the 5 '|' room borders starting from column 7 (skip left staircase border)
            int bars[ROOMS_PER_FLOOR + 1];
            int barCount = 0;
            for (int a = 7; entityLine[a] != '\0' && barCount <= ROOMS_PER_FLOOR; a++) 
            {
                if (entityLine[a] == '|') 
                {
                    bars[barCount] = a;
                    barCount++;
                }
            }

            if (barCount == ROOMS_PER_FLOOR + 1) 
            {
                for (int a = 0; a < ROOMS_PER_FLOOR; a++) 
                {
                    for (int b = bars[a] + 1; b < bars[a + 1]; b++) 
                    {
                        char ch = entityLine[b];
                        if (isValidEntity(ch) && entityCounts[foundFloor][a] < MAX_ENTITIES_PER_ROOM) 
                        {
                            roomEntities[foundFloor][a][entityCounts[foundFloor][a]] = ch;
                            entityCounts[foundFloor][a]++;

                            if (foundFloor == 0 && a == 3 && ch == ENT_ENERGY_PACK &&
                                entityCounts[foundFloor][a] < MAX_ENTITIES_PER_ROOM) 
                                {
                                roomEntities[foundFloor][a][entityCounts[foundFloor][a]] = ENT_ENERGY_PACK;
                                entityCounts[foundFloor][a]++;
                            }
                        }
                    }
                }
            }
        }

        floorsLoaded++;
    }

    file.close();
    return (floorsLoaded == NUM_FLOORS);
}
//This function is used to load initial values from initial-state.txt:

bool loadInitialState(const char* filename, int& playerFloor, int& playerRoom, int& energy, int& time, int& score, char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft) 
{
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    // Set default values first
    playerFloor = 1;
    playerRoom = 1;
    energy = INITIAL_ENERGY;
    time = INITIAL_TIME;
    score = INITIAL_SCORE;
    inventoryCount = 0;
    emergencyTripsLeft = 0;

    for (int a = 0; a < MAX_INVENTORY_CAPACITY; a++) {
        inventory[a] = ENT_NONE;
    }
    for (int a = 0; a < NUM_OBJECTIVES; a++) {
        objectives[a] = false;
    }

    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN)) 
    {
        trimWhitespace(line);
        if (line[0] == '\0') 
        {
            continue;
        }
        if (startsWith(line, "INITIAL_ENERGY:")) 
        {
            energy = readIntAfterColon(line, INITIAL_ENERGY);
        } else if (startsWith(line, "INITIAL_TIME:")) 
        {
            time = readIntAfterColon(line, INITIAL_TIME);
        } else if (startsWith(line, "INITIAL_SCORE:")) 
        {
            score = readIntAfterColon(line, INITIAL_SCORE);
        }
    }

    file.close();
    return true;
}


        
    


