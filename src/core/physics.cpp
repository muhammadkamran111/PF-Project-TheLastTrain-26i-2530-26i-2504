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
    if (fromR == 1 && toR == 1) 
    {
        bool isS1 = (fromF == 1 && toF == 2) || (fromF == 2 && toF == 1);
        bool isS2 = (fromF == 2 && toF == 3) || (fromF == 3 && toF == 2);
        bool isS3 = (fromF == 4 && toF == 5) || (fromF == 5 && toF == 4);

        if (isS1 || isS2 || isS3) {
            outConnType = 'S';
            return true;
        }
    }



}

