#include <stdint.h>

#pragma once

//We have on our PCB charge disconnect relay and charge volt and charge current as well as pack voltage.
//We will have an external IF to the charger but for now that is only a contactor.Because of the
//issues with buying the chg.I decided to put all chg control on our PCB.

//For the actual charge, we need to balance the cells while charging as well as manage heat during chg.


//ATA6870 Datasheet: http://www.atmel.com/Images/Atmel-9317-Li-Ion-Battery-Management-ATA6870N_Datasheet.pdf
//Register Definitions: PG 37

//TOTALLY MADE UP DOUBLE CHECK THESE!!!!!!!!
#define CELL_UNDER_VOLTAGE 3.6F //In volts
#define CELL_OVER_VOLTAGE 4.8F //In volts
#define CELL_TAB_TEMPERATURE_WARNING 0F //In celsius
#define CELL_TAB_TEMPERATURE_ERROR 0F //In celsius
#define CELL_PCM_TEMPERAUTRE_WARNING 0F //In celsius
#define CELL_PCM_TEMPERATURE_ERROR 0F //In celsius
#define CELL_CHARGING_DISCHARGE_THRESHOLD 4.3F //In volts

//The battery packs are wired 18s6p
float BatteryCellVoltages[18];

//Each set of paralleled cells has a discharge transistor
//that discharges those cells or lets charging current bypess them
CellDischarge BatteryCellDischargeTransistor[18];

typedef enum CellDischarge {
	CellDischargeDisabled = 0,
	CellDischargeEnabled = 1
};