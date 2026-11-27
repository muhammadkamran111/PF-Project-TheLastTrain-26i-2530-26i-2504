#include "logger.h"
#include <fstream>
#include <iostream>
using namespace std;

// Saving the current gamestate to an external file out/savegame.txt
bool saveGameStateToFile( const char* filename , int playerFloor , int playerRoom , int energy , int time , int score ,
                          const char inventory[MAX_INVENTORY_CAPACITY] , int inventoryCount , const bool objectives[NUM_OBJECTIVES] , int emergencyTripsLeft , 
                          const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM] , 
                          const int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR] ) {

ofstream out( filename );
if (!out.is_open())
   {
    return false;
   }

out << playerFloor << " " << playerRoom << "\n";
out << energy << " " << time << " " << score << " " << emergencyTripsLeft << "\n";

// Inventory Saving
out << inventoryCount << "\n";
for ( int a = 0 ; a < inventoryCount ; a++ )
    {
        out << (int)inventory[a] << " "; 
    }
out << "\n";

// Objectives Saving
for ( int a = 0 ; a < NUM_OBJECTIVES ; a++ )
    {
        out << (objectives[a] ? 1 : 0 ) << " ";
    }   
 out << "\n";

 // Room Entities Saving
 for ( int a = 0 ; a < NUM_FLOORS ; a++ )
    {
    for ( int b = 0 ; b < ROOMS_PER_FLOOR ; b++ )
        {
            out << entityCounts[a][b];
            for ( int c = 0 ; c < entityCounts[a][b] ; c++ )
                {
                    out << " " << (int)roomEntities[a][b][c];
                }
                out << "\n";
        }
    }

out.close();
return true;

}

// Loading Saved data from out/savegame.txt
bool loadGameStateFromFile( const char* filename , int& playerFloor , int& playerRoom , int& energy , int& time , int& score ,
                            char inventory[MAX_INVENTORY_CAPACITY] , int& inventoryCount , bool objectives[NUM_OBJECTIVES] , int& emergencyTripsLeft , 
                            char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM] , 
                            int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR] ) {

ifstream in(filename);
if ( !in.is_open())
   {
        return false;
   }

if (!( in >> playerFloor >> playerRoom))
    {
        return false;
    }

if (!( in >> energy >> time >> score >> emergencyTripsLeft))
    {
        return false;
    }

if (!( in >> inventoryCount))
    {
        return false;
    }

if ( inventoryCount < 0 ) inventoryCount = 0;
if ( inventoryCount > MAX_INVENTORY_CAPACITY ) inventoryCount = MAX_INVENTORY_CAPACITY;

for ( int a = 0 ; a < inventoryCount ; a++ )
    {
        int code = 0;
        in >> code;
        inventory[a] = (char)code;
    }

for ( int a = 0 ; a < NUM_OBJECTIVES ; a++ )
    {
        int flag = 0;
        in >> flag;
        objectives[a] = (flag == 1);
    }    

for ( int a = 0 ; a < NUM_FLOORS ; a++ ){
    for ( int b = 0 ; b < ROOMS_PER_FLOOR ; b++ ){
        int count = 0;
        in >> count;
        if ( count < 0 ) count = 0;
        if ( count > MAX_ENTITIES_PER_ROOM ) count = MAX_ENTITIES_PER_ROOM;
        entityCounts[a][b] = count;

        for ( int c = 0 ; c < count ; c++ ){
            int code = 0;
            in >> code;
            roomEntities[a][b][c]  = (char)code;
        }
    }
}

in.close();
return true;
                
}

// Final report of game to out/game_summary.txt
void writeGameSummaryReport ( const char* filename , int score , int remainingEnergy , int remainingTime , const bool objectives[NUM_OBJECTIVES] ,
                              bool victory ) {

ofstream out(filename);
if ( !out.is_open()) {
    cerr << "Error: Could not write summary report to " << filename << "\n";
    return;
}

out << "=================================================\n";
out << "        THE LAST TRAIN - GAME SUMMARY REPORT     \n";
out << "=================================================\n";
out << "Mission Outcome   : " << ( victory ? "VICTORY ( Train Departed! )" : "DEFEAT / ENDED" ) << "\n";
out << "Final Score       : " << score << " / 520\n";
out << "Remaining Energy  : " << remainingEnergy << " / " << MAX_ENERGY << "\n";
out << "Remaining Time    : " << remainingTime << "\n\n";

out << "--- OBJECTIVE CHECKLIST ---\n";
out << "[" << ( objectives[OBJ_MASTER_KEY]          ? "X" : " " ) << "] Master Key Collected (+10)\n"; 
out << "[" << ( objectives[OBJ_CLUE_4]              ? "X" : " " ) << "] Clue Digit 4 Found in F3-R2 (+10)\n";
out << "[" << ( objectives[OBJ_CLUE_2]              ? "X" : " " ) << "] Clue Digit 2 Found in F4-R3 (+10)\n";
out << "[" << ( objectives[OBJ_CLUE_7]              ? "X" : " " ) << "] Clue Digit 7 Found in F5-R1 (+10)\n";
out << "[" << ( objectives[OBJ_CABINET_UNLOCKED]    ? "X" : " " ) << "] Cabinet Unlocked with Code 427 (+30)\n";
out << "[" << ( objectives[OBJ_TRAIN_KEY]           ? "X" : " " ) << "] Train Key Acquired (+10)\n";
out << "[" << ( objectives[OBJ_FUSE_INSTALLED]      ? "X" : " " ) << "] Fuse Installed at Control Panel (+20)\n";
out << "[" << ( objectives[OBJ_LIFT_PASS]           ? "X" : " " ) << "] Lift Pass Collected (+20)\n";
out << "[" << ( objectives[OBJ_PASSENGER_RESCUED]   ? "X" : " " ) << "] Injured Passenger Rescued in F4-R1 (+100)\n";
out << "[" << ( objectives[OBJ_CAT_SECURED]         ? "X" : " " ) << "] Stranded Cat Secured in F3-R3 (+100)\n";
out << "[" << ( objectives[OBJ_TRAIN_PREPARED]      ? "X" : " " ) << "] Train Prepared & Boarded in F5-R2 (+100)\n";
out << "[" << ( objectives[OBJ_MISSION_WON]         ? "X" : " " ) << "] Full Mission Victory Bonus (+100)\n";
out << "=================================================\n";

out.close();

}
