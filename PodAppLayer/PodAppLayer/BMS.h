#include <stdint.h>

#pragma once

//We have on our PCB charge disconnect relay and charge volt and charge current as well as pack voltage.
//We will have an external IF to the charger but for now that is only a contactor.Because of the
//issues with buying the chg.I decided to put all chg control on our PCB.

//For the actual charge, we need to balance the cells while charging as well as manage heat during chg.


//ATA6870 Datasheet: http://www.atmel.com/Images/Atmel-9317-Li-Ion-Battery-Management-ATA6870N_Datasheet.pdf
//Register Definitions: PG 37



