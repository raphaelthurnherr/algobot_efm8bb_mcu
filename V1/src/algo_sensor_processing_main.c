//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB1_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
// $[Generated Includes]
// [Generated Includes]$

#include"algo_sensor_processing.h"


//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
// Global holder for SMBus data.
// All receive data is written here
// NUM_BYTES_WR used because an SMBus write is Master->Slave
uint8_t xdata SMB_DATA_IN[20];

// Global holder for SMBus data.
// All transmit data is read from here
// NUM_BYTES_RD used because an SMBus read is Slave->Master
uint8_t xdata SMB_DATA_OUT[20];

bool I2C_DATA_READY = 0;                    // Set to '1' by the SMBus ISR
                                       	    // when a new data byte has been
											// received.
bool I2C_SET_REGISTER =0;
bool TICK_100MS = 0;						// Flag timer cadencé à 100mS = 0;


bool StartSonarMeasure=0;					// Initie la mesure ultrasons

// Définition des variables propre au hardware

struct din DIN3;				// p.e. capteur IR arrière
struct din DIN1;				// p.e. capteur IR avant
struct counter CNT_IN_3;			// p.e. Capteur roue droit
struct counter CNT_IN_4;			// p.e. Capteur roue gauche
struct din DIN2;				// p.e. Capteur Avant droit
struct din DIN0;				// p.e. Capteur Avant gauche
struct ain BATTERY;					// p.e. Batterie système
struct sonar SONAR;					// p.e. Capteur ultrasons


//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main (void)
{
	int i;
	unsigned char temp;
	/*
	unsigned int CAP0;
	unsigned int CAP1;
*/

	// INITIALISATION DES PARAMETRE DE PERIPHERIQUE
	DIN3.enable=1;			// activation de la lecture de l'entrée
	DIN1.enable=1;			// activation de la lecture de l'entrée
	DIN2.enable=1;			// activation de la lecture de l'entrée
	DIN0.enable=1;

	CNT_IN_3.enable=1;			// activation de la lecture de l'entrée
	CNT_IN_3.pulses=0;

	CNT_IN_4.enable=1;			// activation de la lecture de l'entrée
	CNT_IN_4.pulses=0;


	BATTERY.enable=1;			// activation de la lecture de l'entrée
	BATTERY.mean_count=10;		// moyennage sur 10 mesure

	SONAR.enable=1;				// activation de la mesure ultrasons
	SONAR.mean_count=5;			// moyennage sur 5 mesures

	// Call hardware initialization routine
	enter_DefaultMode_from_RESET();


  // Initialize the outgoing data array in case a read is done before a
   // write

   for (i = 0; i < 10; i++)
   {
	  SMB_DATA_OUT[i] = 0xEE;
   }

   while(1)
   {

	   // RECEPTION D'UNE REQUETE EN PROVENANCE DU MASTER I2C
	  if(I2C_DATA_READY){

		  if(I2C_SET_REGISTER){
			  switch(SMB_DATA_IN[0]){
			  	case CTRL_REG : DIN0.enable = SMB_DATA_IN[1] & 0x01;
			  					DIN1.enable = SMB_DATA_IN[1] & 0x02;
			  					DIN2.enable = SMB_DATA_IN[1] & 0x04;
			  					DIN3.enable = SMB_DATA_IN[1] & 0x08;
			  					SONAR.enable = SMB_DATA_IN[1] & 0x10;
			  					BATTERY.enable = SMB_DATA_IN[1] & 0x20;
			  					CNT_IN_3.enable = SMB_DATA_IN[1] & 0x40;
			  					CNT_IN_4.enable = SMB_DATA_IN[1] & 0x80;
			  					break;
			  	default: break;
			  }
		  }
		  else{
			  // lecture des registres
			  switch(SMB_DATA_IN[0]){

				  case BOARD_TYPE : SMB_DATA_OUT[0] = 0x11; break;
				  case MCU_FIRMWARE : SMB_DATA_OUT[0] = 0x0B; break;

				  case CTRL_REG :	temp=0;
									temp = temp + ((CNT_IN_4.enable & 0x01)<<7);
									temp = temp + ((CNT_IN_3.enable & 0x01)<<6);
									temp = temp + ((BATTERY.enable & 0x01)<<5);
									temp = temp + ((SONAR.enable & 0x01)<<4);
									temp = temp + ((DIN3.enable & 0x01)<<3);
									temp = temp + ((DIN2.enable & 0x01)<<2);
									temp = temp + ((DIN1.enable & 0x01)<<1);
									temp = temp + ((DIN0.enable & 0x01));
									SMB_DATA_OUT[0] = temp; break;

				  case DIN_STATE : 	  temp=0;
									  temp = temp +(DIN3.value & 0x01)<<3;
									  temp = temp + ((DIN2.value & 0x01)<<2);
									  temp = temp + ((DIN1.value & 0x01)<<1);
									  temp = temp + ((DIN0.value & 0x01));
									  SMB_DATA_OUT[0] = temp; break;

				  case SONAR_L : SMB_DATA_OUT[0] = SONAR.dist_inst_mm & 0x00FF; break;
				  case SONAR_H : SMB_DATA_OUT[0] = (SONAR.dist_inst_mm & 0xFF00)>>8;  break;
				  case SONAR_MEAN_L : SMB_DATA_OUT[0] = SONAR.dist_mean_mm & 0x00FF; break;
				  case SONAR_MEAN_H : SMB_DATA_OUT[0] = (SONAR.dist_mean_mm & 0xFF00)>>8;  break;

				  case BATT_L : SMB_DATA_OUT[0] = BATTERY.voltage_inst_mV & 0x00FF; break;
				  case BATT_H : SMB_DATA_OUT[0] = (BATTERY.voltage_inst_mV & 0xFF00)>>8; break;
				  case BATT_MEAN_L : SMB_DATA_OUT[0] = BATTERY.voltage_mean_mV & 0x00FF; break;
				  case BATT_MEAN_H : SMB_DATA_OUT[0] = (BATTERY.voltage_mean_mV & 0xFF00)>>8; break;


				  case FRQ_1 : SMB_DATA_OUT[0] = CNT_IN_3.frequency; break;
				  case FRQ_2 : SMB_DATA_OUT[0] = CNT_IN_4.frequency; break;

				  case CNT_1_L : SMB_DATA_OUT[0] = CNT_IN_3.pulses & 0x00FF; break;
				  case CNT_1_H : SMB_DATA_OUT[0] = (CNT_IN_3.pulses & 0xFF00)>>8; break;

				  case CNT_2_L : SMB_DATA_OUT[0] = CNT_IN_4.pulses & 0x00FF; break;
				  case CNT_2_H : SMB_DATA_OUT[0] = (CNT_IN_4.pulses & 0xFF00)>>8; break;

				  case CNT_1_CLEAR : TH0=TL0=0; break;
				  case CNT_2_CLEAR : TH1=TL1=0; break;

				  default	:	SMB_DATA_OUT[0] = 0xDD; break;
			  }
		  }
		  I2C_DATA_READY = 0;
	  }

	  if(TICK_100MS){

		  // Capteur actif à l'état bas

		  if(DIN0.enable)
			  DIN0.value=DIG_HYS_2;
		  if(DIN1.enable)
			  DIN1.value=!DIG_IN_2;
		  if(DIN2.enable)
			  DIN2.value=DIG_HYS_1;
		  if(DIN3.enable)
			  DIN3.value=!DIG_IN_1;

		  // Démarre une mesure ultrasons
		  if(SONAR.enable)
			  StartSonarMeasure = 1;

		  // Démarre une conversion AD si activée
		  if(BATTERY.enable==1)
			  ADC0CN0_ADBUSY=1;		// Démarre la conversion¨

		  // Mise à jour des registre compteurs
		  CNT_IN_3.pulses = 0;
		  CNT_IN_3.pulses = TH0;
		  CNT_IN_3.pulses = (CNT_IN_3.pulses << 8) + TL0;

		  CNT_IN_4.pulses = 0;
		  CNT_IN_4.pulses = TH1;
		  CNT_IN_4.pulses = (CNT_IN_4.pulses << 8) + TL1;

		  TICK_100MS=0;			// Reset 100mS
	  }
   }
}
