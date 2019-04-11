/*
    EPDlib.c
    Created by SKN CHIP (Grzegorz Orlicki)
    Based on the documentation for E-paper display USE0154BS01
    MIT License
*/

#include "main.h"
#include "stm32f0xx_hal.h"
#include "EPDlib.h"

//extern SPI_HandleTypeDef hspi1;

//Communication
void EPDlib_SendCommand(uint8_t command){
    uint8_t temp = command;

    HAL_GPIO_WritePin(EPD_CS_GPIO_Port, EPD_CS_Pin, 0);
	HAL_GPIO_WritePin(EPD_DC_GPIO_Port, EPD_DC_Pin, 0);
	HAL_SPI_Transmit(&hspi1, &temp, sizeof(temp), 10);
	HAL_GPIO_WritePin(EPD_CS_GPIO_Port, EPD_CS_Pin, 1);
}
void EPDlib_SendData(uint8_t data){
    uint8_t temp = data;

	HAL_GPIO_WritePin(EPD_CS_GPIO_Port, EPD_CS_Pin, 0);
	HAL_GPIO_WritePin(EPD_DC_GPIO_Port, EPD_DC_Pin, 1);
	HAL_SPI_Transmit(&hspi1, &temp, sizeof(temp), 10);
	HAL_GPIO_WritePin(EPD_CS_GPIO_Port, EPD_CS_Pin, 1);
}

//Basic
void EPDlib_HardwareReset(){
    HAL_GPIO_WritePin(EPD_RESET_GPIO_Port, EPD_RESET_Pin, 0);
	HAL_Delay(1);
	HAL_GPIO_WritePin(EPD_RESET_GPIO_Port, EPD_RESET_Pin, 1);
	HAL_Delay(1);
}
void EPDlib_SoftwareReset(){
    EPDlib_SendCommand(RESET);
}
void EPDlib_WaitforEPD(){
    while(1){
		if(!HAL_GPIO_ReadPin(EPD_BUSY_GPIO_Port, EPD_BUSY_Pin)) break;
	}
}

//Display
void EPDlib_Start(){
    //Power On
    EPDlib_HardwareReset();
    EPDlib_WaitforEPD();
    EPDlib_SoftwareReset();
    EPDlib_WaitforEPD();

    EPDlib_SendCommand(AnalogBlockControl);
    EPDlib_SendData(0x54);
    EPDlib_SendCommand(DigitalBlockControl);
    EPDlib_SendData(0x3B);

    EPDlib_SendCommand(DisplayOutputControl);
    EPDlib_SendData(0x97);
    EPDlib_SendData(0x00);
    EPDlib_SendData(0x00);

    EPDlib_SendCommand(RAMDataEntry);
    EPDlib_SendData(0x01);
    EPDlib_SendCommand(RAMX);
    EPDlib_SendData(0x00);
    EPDlib_SendData(0x12);
    EPDlib_SendCommand(RAMY);
    EPDlib_SendData(0x97);
    EPDlib_SendData(0x00);
    EPDlib_SendData(0x00);
    EPDlib_SendData(0x00);

    EPDlib_SendCommand(TemperatureSelection); //uwaga dodane
    EPDlib_SendData(0x80);
    EPDlib_SendCommand(Border);
    EPDlib_SendData(0x01);

    //Set voltage and load LUT
    EPDlib_SendCommand(VCOM);
    EPDlib_SendData(0x52);
    EPDlib_SendCommand(GateVoltage);
    EPDlib_SendData(0x17);
    EPDlib_SendCommand(SourceVoltage);
    EPDlib_SendData(0x41);
    EPDlib_SendData(0x00);
    EPDlib_SendData(0x32);

    EPDlib_SendCommand(Frame1);
    EPDlib_SendData(0x11);
    EPDlib_SendCommand(Frame2);
    EPDlib_SendData(0x0D);
    EPDlib_SendCommand(LoadLUT);
    for(int i = 0; i < 30; i++) EPDlib_SendData(LUTTable[i]);
}
void EPDlib_Image(const uint8_t* image){
    EPDlib_SendCommand(RAMXCounter);
    EPDlib_SendData(0x00);
    EPDlib_SendCommand(RAMYCounter);
    EPDlib_SendData(0x97);
    EPDlib_SendData(0x00);

    EPDlib_SendCommand(LoadImage);
    uint32_t counter = 0;
    for(uint8_t i = 0; i < COL; i++){
        for(uint8_t j = 0; j < ROW; j++){
            EPDlib_SendData(image[counter++]);
        }
    }
}
void EPDlib_White(){
    EPDlib_SendCommand(RAMXCounter);
    EPDlib_SendData(0x00);
    EPDlib_SendCommand(RAMYCounter);
    EPDlib_SendData(0x97);
    EPDlib_SendData(0x00);

    EPDlib_SendCommand(LoadImage);
    for(uint8_t i = 0; i < COL; i++){
        for(uint8_t j = 0; j < ROW; j++){
            EPDlib_SendData(0xFF);
        }
    }
}
void EPDlib_Black(){
    EPDlib_SendCommand(RAMXCounter);
    EPDlib_SendData(0x00);
    EPDlib_SendCommand(RAMYCounter);
    EPDlib_SendData(0x97);
    EPDlib_SendData(0x00);

    EPDlib_SendCommand(LoadImage);
    for(uint8_t i = 0; i < COL; i++){
        for(uint8_t j = 0; j < ROW; j++){
            EPDlib_SendData(0x00);
        }
    }
}
void EPDlib_Update(){
    EPDlib_SendCommand(Update1);
    EPDlib_SendData(0xC7);
    EPDlib_SendCommand(Update2);

    EPDlib_WaitforEPD();
    EPDlib_SendCommand(DeepSleepMode);
    EPDlib_SendData(0x01);
}

//RAM
void EPDlib_RAM_Address(uint8_t xh_s, uint8_t xh_e, uint8_t yh_s, uint8_t yl_s, uint8_t yh_e, uint8_t yl_e){
    
}

