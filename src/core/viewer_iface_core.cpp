#include "viewer_iface.h"
#include "level.h"
#include "util.h"

#include <iostream>
using namespace std;

// Get the Room name for any floor and room
static const char* getRoomName (int floor , int room)
 {
    const char* names[NUM_FLOORS][ROOMS_PER_FLOOR] = 
    {
        {"Enterance Lobby" , "Reception" , "Waiting Area" , "Utility Room" } ,
        {"Lounge" , "Archive" , "Lab" , "Meeting Room" } ,
        {"Stairwell Annex" , "Security Vestibule" , "Animal Room" , "Control Room" } ,
        {"First Aid Station" , "Medical Room" , "Maintenance Corridor" , "Office" } ,
        {"Security Room" , "Train Boarding Platform" , "Storage Room" , "Observation Deck" } ,

    };

    if ( floor >=1 && floor <= NUM_FLOORS && room >= 1 && room <=ROOMS_PER_FLOOR )
    {
        return names[floor - 1][room - 1];
    }

    return "Unknown Room";
 }

 // Stats and Inventory Display
 void renderDashboard ( int playerFloor , int playerRoom , int energy , int time , int score , const char inventory[MAX_INVENTORY_CAPACITY] , int inventoryCount ,
 int emergencyTripsLeft )
 {
      cout << "\n------------------------------------------------------------\n";
      cout << " Location : F" << playerFloor << "-R" << playerRoom
           << " (" << getRoomName ( playerFloor , playerRoom ) << ")\n";
      cout << " Energy   : " << energy << "/" <<MAX_ENERGY
           << "  |  Time : " << time
           << "  |  Score : " << score << "/520\n";
      cout << " Lift 2 Emergency Trips Left: " << emergencyTripsLeft << "\n";
      cout << " Inventory (" << inventoryCount << "): ";

      if ( inventoryCount == 0 ) cout << "Empty";
      else
      {
         for ( int a = 0 ; a < inventoryCount ; a++ )
           { 
            cout << "[" << inventory[a] << " " << getEntityName(inventory[a]) << "]";           
             if ( a < inventoryCount - 1 )
                {
                    cout << ", ";
                }      

<<<<<<< HEAD
           }
          cout << "\n------------------------------------------------------------\n";
      }
 }

// Room Entity Display
void renderRoomDetails( int floor , int room , const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM] , int entityCount )
{
=======
          }
          cout << "\n------------------------------------------------------------\n";
      }
    }

// Room Entity Display
void renderRoomDetails( int floor , int room , const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM] , int entityCount ){
>>>>>>> 104d6a7ac046474bfbce926fb532d11e18582c18

    cout << "\nItems / Entities in F" << floor << "-R" << room
         << " (" << getRoomName( floor , room ) << "):\n";

    if ( entityCount <=0 ) 
    {
        cout << "  (Nothing left in this room.)\n";
        return;
    }

    for ( int a = 0 ; a < entityCount ; a++ )
    {
        char sym = roomEntities[floor - 1][room - 1][a];
        cout << "  - [" << sym << "] " << getEntityName(sym) << "\n";
    }

}

// Draw a 5-floor map ASCII map
void renderAsciiBuilding( int playerFloor , int playerRoom )
{
    const char* items[NUM_FLOORS][ROOMS_PER_FLOOR] = 
    {
        { "         " , "    <    " , "         " , "    )    " }, //F1
        { "         " , "         " , "    \\    " , "         " },//F2
        { "         " , "  4   *  " , "    ~    " , "  :   (  " }, //F3
        { "    !    " , "  %   $  " , "    2    " , "         " }, //F4
        { "  7   ^  " , "  TRAIN  " , "    @    " , "    &    " }, //F5
    };

    cout << "\n==================== The Last Train - Full Map ====================\n";
    cout << "         +-----------+-----------+-----------+-----------+         L2\n";

    for ( int a =NUM_FLOORS; a >=1 ; a-- )
    {
        cout << "     |  |";

        for ( int b = 1 ; b <= ROOMS_PER_FLOOR ; b++ )
          {
              bool isL1Edge = ( b == 2 && ( a == 1 || a ==2 ));
              
              if ( a == playerFloor && b == playerRoom ) 
              {
                if ( isL1Edge )
                {
                    cout << " *F" << a << "-R" << b << "*  ";   
                }
                else 
                {
                    cout << " *F" << a << "-R" << b << "*   "; 
                }
              }
              else
              {
                if ( isL1Edge )
                {
                    cout << " F" << a << "-R" << b << "    ";   
                }
                else
                {
                    cout << " F" << a << "-R" << b << "     "; 
                }
              } 

<<<<<<< HEAD
              if ( b == 1 ) 
              {
=======
              if ( b == 1 ) {
>>>>>>> 104d6a7ac046474bfbce926fb532d11e18582c18
                 
                if ( a == 5 )      cout << "D";
                else if ( a == 4 ) cout << "W";
                else if ( a == 3 ) cout << "L";
                else if ( a == 2 ) cout << "D";
                else               cout << "W";
              }

<<<<<<< HEAD
              else if ( b== 2 ) 
              {
=======
              else if ( b== 2 ) {
>>>>>>> 104d6a7ac046474bfbce926fb532d11e18582c18

                if ( a == 5 )      cout << "D";
                else if ( a == 4 ) cout << "#";
                else if ( a == 3 ) cout << "W";
                else               cout << "L1";
              }

<<<<<<< HEAD
              else if ( b == 3 )
              {
=======
              else if ( b == 3 ){
>>>>>>> 104d6a7ac046474bfbce926fb532d11e18582c18

                if ( a == 5 )      cout << "W";
                else               cout << "D";
              }

<<<<<<< HEAD
              else 
              {
=======
              else {
>>>>>>> 104d6a7ac046474bfbce926fb532d11e18582c18

                cout << "|";
              }

          }

          if  ( a == 5 )        cout << "          |\n";
          else if ( a == 4 )    cout << "          L2\n";
          else if ( a == 3 )    cout << "          .\n";
          else if ( a == 2 )    cout << "==========L2\n";
          else                  cout << "\n";

          if ( a == 4 )   cout << "        |";
          else            cout << "     |  |";

<<<<<<< HEAD
          for ( int b = 1 ; b <= ROOMS_PER_FLOOR ; b++ ) 
          {

            if ( a == playerFloor && b == playerRoom ) 
            {
                cout << "   [YOU]   |";
            }
            else 
            {
=======
          for ( int b = 1 ; b <= ROOMS_PER_FLOOR ; b++ ) {

            if ( a == playerFloor && b == playerRoom ) {
                cout << "   [YOU]   |";
            }
            else {
>>>>>>> 104d6a7ac046474bfbce926fb532d11e18582c18
                cout << " " << items[a-1][b-1] << " |";
            }
          }

          if ( a == 5 )         cout << "          |\n";
          else if ( a == 4 )    cout << "          .\n";
          else if ( a == 3 )    cout << "          .\n";
          else                  cout << "\n";


          if ( a == 5 )         cout << "S3---|  +-----------+-----------+-----------+-----------+          |\n";
          else if ( a == 4 )    cout << "        +-----------+-----------+-----------+-----------+          .\n";
          else if ( a == 3 )    cout << "S2---|  +-----------+-----------+-----------+-----------+          .\n";
          else if ( a == 2 )    cout << "S1---|  +-----------+-----------+-----------+-----------+\n";
          else                  cout << "     |  +-----------+-----------+-----------+-----------+\n";

<<<<<<< HEAD
    }

          cout << "Legend: *Fx-Ry* / [YOU]=Player | D=Door | W=Window | L=Locked | #=Wall | L1/L2=Lifts\n";
=======
          }

          cout << "Legent: *Fx-Ry* / [YOU]=Player | D=Door | W=Window | L=Locked | #=Wall | L1/L2=Lifts\n";
>>>>>>> 104d6a7ac046474bfbce926fb532d11e18582c18
          cout << "Items : <=Key )=Pack \\=Kit 4,2,7=Clues *=Fuse ~=Cat ;=Panel (=Pass %=Med $=Card ^=Train @=Carrier &=Token\n";
          cout << "===================================================================\n"; 
          
 }


          // Show OBjective List
<<<<<<< HEAD
          void renderObjectivesChecklist( const bool objectives[NUM_OBJECTIVES]) 
          {
=======
          void renderObjectivesChecklist( const bool objectives[NUM_OBJECTIVES]) {
>>>>>>> 104d6a7ac046474bfbce926fb532d11e18582c18
            cout << "\n--- MISSION OBJECTIVES ---\n";
            cout << (objectives[OBJ_MASTER_KEY]              ? "[DONE] " : "[    ] ") << "Collect Master Ket (<) in F1-R2 (+10)\n";
            cout << (objectives[OBJ_CLUE_4]                  ? "[DONE] " : "[    ] ") << "Discover Clues 4 in F3-R2 (+10)\n";
            cout << (objectives[OBJ_CLUE_2]                  ? "[DONE] " : "[    ] ") << "Discover Clues 2 in F4-R3 (+10)\n";
            cout << (objectives[OBJ_CLUE_7]                  ? "[DONE] " : "[    ] ") << "Discover Clues 7 in F5-R1 (+10)\n";
            cout << (objectives[OBJ_CABINET_UNLOCKED]        ? "[DONE] " : "[    ] ") << "Unlock Cabinet (427) in F5-R1 (+30)\n";
            cout << (objectives[OBJ_TRAIN_KEY]               ? "[DONE] " : "[    ] ") << "Collect Train Key (^) in F5-R1 (+10)\n";
            cout << (objectives[OBJ_FUSE_INSTALLED]          ? "[DONE] " : "[    ] ") << "Install Fuse (*) at F3-R4 Panel (+20)\n";
            cout << (objectives[OBJ_LIFT_PASS]               ? "[DONE] " : "[    ] ") << "Collect Lift Pass (() in F3-R4 (+20)\n";
            cout << (objectives[OBJ_PASSENGER_RESCUED]       ? "[DONE] " : "[    ] ") << "Rescue Injured Passenger (!) in F4-R1(+100)\n";
            cout << (objectives[OBJ_CAT_SECURED]             ? "[DONE] " : "[    ] ") << "Secure Stranded Cat (~) in F3-R3 (+100)\n";
            cout << (objectives[OBJ_TRAIN_PREPARED]          ? "[DONE] " : "[    ] ") << "Prepare & Board Train in F5-R2 (+100 + 100 Bonus)\n";
          }









          


















    





 
