/*
 * func.c
 *
 *  Created on: 13 mars 2018
 *      Author: Raph
 */

#include"algo_sensor_processing.h"


unsigned char getRegisterValue(unsigned char regAdress){
	unsigned char temp=0;
	unsigned char regValue=0;


	switch(regAdress){

					  case BOARD_TYPE : regValue = 0x11; break;
					  case MCU_FIRMWARE : regValue = 0x0A; break;
					  case CTRL_REG :	regValue=0;
										temp = temp + ((CNT_IN_4.enable & 0x01)<<7);
										temp = temp + ((CNT_IN_3.enable & 0x01)<<6);
										temp = temp + ((BATTERY.enable & 0x01)<<5);
										temp = temp + ((SONAR.enable & 0x01)<<4);
										temp = temp + ((DIN3.enable & 0x01)<<3);
										temp = temp + ((DIN2.enable & 0x01)<<2);
										temp = temp + ((DIN1.enable & 0x01)<<1);
										temp = temp + (DIN0.enable & 0x01);
										regValue = temp;
										break;
					  case DIN_STATE : 	  temp=0;
										  temp = temp +(DIN3.value & 0x01)<<3;
										  temp = temp + ((DIN2.value & 0x01)<<2);
										  temp = temp + ((DIN1.value & 0x01)<<1);
										  temp = temp + ((DIN0.value & 0x01));
										  regValue = temp;
										  break;
					  case SONAR_L : regValue = SONAR.dist_inst_mm & 0x00FF;
					  	  	  	  	  break;
					  case SONAR_H : regValue = (SONAR.dist_inst_mm & 0xFF00)>>8;
					  	  	  	  	  break;
					  case SONAR_MEAN_L : regValue = SONAR.dist_mean_mm & 0x00FF;
					  	  	  	  	  	  break;
					  case SONAR_MEAN_H : regValue = (SONAR.dist_mean_mm & 0xFF00)>>8;
					  	  	  	  	  	  break;
					  case BATT_L : regValue = BATTERY.voltage_inst_mV & 0x00FF;
					  	  	  	  	  break;
					  case BATT_H : regValue = (BATTERY.voltage_inst_mV & 0xFF00)>>8;
					  	  	  	  	  break;
					  case BATT_MEAN_L : regValue = BATTERY.voltage_mean_mV & 0x00FF;
					  	  	  	  	  break;
					  case BATT_MEAN_H : regValue = (BATTERY.voltage_mean_mV & 0xFF00)>>8;
					  	  	  	  	  	  break;
					  case FRQ_1 : regValue = CNT_IN_3.frequency;
					  	  	  	  break;
					  case FRQ_2 : regValue = CNT_IN_4.frequency;
					  	  	  	  break;
					  case CNT_1_L : regValue = CNT_IN_3.pulses & 0x00FF;
					  	  	  	  	  break;
					  case CNT_1_H : regValue = (CNT_IN_3.pulses & 0xFF00)>>8;
					  	  	  	  	  break;
					  case CNT_2_L : regValue = CNT_IN_4.pulses & 0x00FF;
					  	  	  	  	  break;
					  case CNT_2_H : regValue = (CNT_IN_4.pulses & 0xFF00)>>8;
					  	  	  	  	  break;
					  case CNT_1_CLEAR : TH0=TL0=0; break;
					  case CNT_2_CLEAR : TH1=TL1=0; break;

					  default	:	regValue = 0xDD; break;
				  }
	  return (regValue);
}
