#include "level.h"
#include "util.h"
#include <fstream>
#include <iostream>

// A function to check if character is one of the valid game entities or not?

static bool isValidEntity(char ch)
{
    if (ch == ENT_MASTER_KEY || ch == ENT_ENERGY_PACK || ch == ENT_EMERGENCY_TOOLKIT || ch == ENT_CLUE_4 || ch == ENT_FUSE || ch == ENT_CAT || ch == ENT_CONTROL_PANEL || ch == ENT_LIFT_PASS || ch == ENT_PASSENGER || ch == ENT_MEDICAL_KIT || ch == ENT_EMERGENCY_CARD || ch == ENT_CLUE_2 || ch == ENT_CLUE_7 || ch == ENT_CABINET_TRAIN_KEY || ch == ENT_CAT_CARRIER || ch == ENT_OBSERVATION_TOKEN)
    {
        return true;
    }
    return false;
}
