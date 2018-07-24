/*
 * algo_sensor_processing.h
 *
 *  Created on: 28 févr. 2018
 *      Author: Raph
 */

#include <SI_EFM8BB1_Register_Enums.h>                  // SFR declarations

#ifndef INC_ALGO_SENSOR_PROCESSING_H_
#define INC_ALGO_SENSOR_PROCESSING_H_


//PARAMETRES GLOBAL
#define ADC_RES_MV 0.003223

sbit SONAR_ECHO_PIN = P1^0;			// Configuration de la pin ECHO ultrasons
sbit SONAR_TRIG_PIN = P1^1;			// Configuration de la pin de trigger ultrasons
sbit DIG_IN_1 = P1^2;			// Configuration de la pin de trigger ultrasons
sbit DIG_IN_2 = P0^3;			// Configuration de la pin de trigger ultrasons
sbit DIG_HYS_2 = P0^4;			// Configuration de la pin de trigger ultrasons
sbit DIG_HYS_1 = P0^5;			// Configuration de la pin de trigger ultrasons

// COMMUNICATION I2C AVEC L'HOTE
// DEFINITION DES COMMANDES (REGISTRE)

#define	BOARD_TYPE		 0x00
#define	MCU_FIRMWARE	 0x01

#define CTRL_REG		 0x02

#define DIN_STATE		 0x04

#define	SONAR_L		 	 0x06
#define	SONAR_H		 	 0x07
#define	SONAR_MEAN_L     0x08
#define	SONAR_MEAN_H	 0x09
#define	SONAR_MEAN_CNT 	 0x0A

#define	BATT_L		 	 0x0C
#define	BATT_H		 	 0x0D
#define	BATT_MEAN_L	 	 0x0E
#define	BATT_MEAN_H	 	 0x0F
#define	BATT_MEAN_CNT 	 0x10

#define FRQ_1			 0x12
#define CNT_1_L			 0x14
#define CNT_1_H			 0x15

#define FRQ_2			 0x16
#define CNT_2_L			 0x18
#define CNT_2_H			 0x19
#define CNT_1_CLEAR		 0x24
#define CNT_2_CLEAR		 0x28
// DEFINITION POUR BUS I2C
#define  SLAVE_ADDR               0x14 // Device addresses (7 bits, LSB don't care)
                                       //

#define  WRITE                    0x00 // SMBus WRITE command
#define  READ                     0x01 // SMBus READ command

// Status vector - top 4 bits only
#define  SMB_SRADD                0x20 // (SR) slave address received
                                       //    (also could be a lost
                                       //    arbitration)
#define  SMB_SRSTO                0x10 // (SR) STOP detected while SR or ST,
                                       //    or lost arbitration
#define  SMB_SRDB                 0x00 // (SR) data byte received, or
                                       //    lost arbitration
#define  SMB_STDB                 0x40 // (ST) data byte transmitted
#define  SMB_STSTO                0x50 // (ST) STOP detected during a
                                       //    transaction; bus error
// End status vector definition

//#define  NUM_BYTES_WR                1 // Number of bytes to write
                                       // Slave <- Master
//#define  NUM_BYTES_RD                1 // Number of bytes to read

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
// Global holder for SMBus data.
// All receive data is written here
// NUM_BYTES_WR used because an SMBus write is Master->Slave
extern uint8_t xdata SMB_DATA_IN[20];

// Global holder for SMBus data.
// All transmit data is read from here
// NUM_BYTES_RD used because an SMBus read is Slave->Master
extern uint8_t xdata SMB_DATA_OUT[20];

extern bool I2C_SET_REGISTER;
extern bool I2C_DATA_READY;             // Set to '1' by the SMBus ISR
                                        // when a new data byte has been
                                       	// received.

extern bool I2C_SET_REGISTER;					// Master Write requeste

extern bool TICK_100MS;					// Flag timer cadencé à 100mS

extern bool StartSonarMeasure;			// Initie la mesure ultrasons

extern struct din DIN0;					// p.e. Capteur Avant gauche
extern struct din DIN1;					// p.e. capteur IR avant
extern struct din DIN2;					// p.e. Capteur Avant droit
extern struct din DIN3;					// p.e. capteur IR arrière

extern struct counter CNT_IN_3;			// p.e. Capteur roue droit
extern struct counter CNT_IN_4;			// p.e. Capteur roue gauche
extern struct ain BATTERY;				// p.e. Batterie système
extern struct sonar SONAR;				// p.e. Capteur ultrasons



// Structure des données pour les compteurs
struct counter{
	unsigned char enable;					// Activation/désactivation du compteur
	unsigned int pulses;			// Comptabilisation du nombre de pulses
	unsigned int frequency;			// Fréquence instantanée

};

// Structure des données pour le sonar
struct sonar{
	unsigned char enable;					// Activation, désactivation de la mesure
	unsigned int  dist_inst_mm;			// Distance mesure au sonar en mm
	unsigned int  dist_mean_mm;			// Distance mesure au sonar en mm
	unsigned int  data_valid;		// Fréquence instantanée
	unsigned char mean_count;		// Nombre de mesure à effectuer
};

// Structure des données pour les entrées numérique
struct din{
	unsigned char enable;					// Activation, désactivation de la mesure
	unsigned char value;						// Valeur actuelle
};

// Structure des données pour les entrées analogique
struct ain{
	unsigned char enable;					// Activation, désactivation de la mesure
	unsigned int voltage_inst_mV;				// Valeur actuelle de la tension en mv
	unsigned int voltage_mean_mV;				// Valeur actuelle de la tension en mv
	unsigned char mean_count;				//
};


#endif /* INC_ALGO_SENSOR_PROCESSING_H_ */
