/*
    EPDlib.h
    Created by SKN CHIP (Grzegorz Orlicki)
    Based on the documentation for E-paper display USE0154BS01
    MIT License 
*/

#ifndef EPDlib_H_
#define EPDlib_H_

#ifndef EPD_SPI_PORT
#define EPD_SPI_PORT        hspi1
#endif

//Constants
#define RESET 0x12
#define COL 152
#define ROW 19 //152/8
//-Begin
#define AnalogBlockControl 0x74
#define DigitalBlockControl 0x7E
#define DisplayOutputControl 0x01
#define RAMDataEntry 0x11
#define RAMX 0x44
#define RAMY 0x45
#define TemperatureSelection 0x18
#define Border 0x3C

#define VCOM 0x2C
#define GateVoltage 0x03
#define SourceVoltage 0x04
#define Frame1 0x3A
#define Frame2 0x3B
#define LoadLUT 0x32

#define RAMXCounter 0x4E
#define RAMYCounter 0x4F
#define LoadImage 0x24

#define Update1 0x22
#define Update2 0x20
#define DeepSleepMode 0x10

const uint8_t LUTTable[]={
		0x00,
		0xA5,
		0x66,
		0x66,
		0x6A,
		0x66,
		0x9A,
		0x18,
		0x24,
		0x66,
		0x00,
		0x55,
		0x99,
		0x11,
		0x88,
		0x11,
		0x88,
		0x88,
		0x11,
		0x88,
		0xF0,
		0xFF,
		0xFF,
		0xFF,
		0xFF,
		0xF2,
		0xFF,
		0xFF,
		0xAF,
		0x5F,
                     // VGH  VSH1  VSH2 VSL   0X3A 0X3B(Ƶ��)
};

//Declarations
//-Communication
void EPDlib_SendCommand(uint8_t command);
void EPDlib_SendData(uint8_t data);
//-Basic
void EPDlib_HardwareReset();
void EPDlib_SoftwareReset();
void EPDlib_WaitforEPD();
    //void EPDlib_Begin();
//-Display
void EPDlib_Start();

void EPDlib_Image(const uint8_t* image);
void EPDlib_White();
void EPDlib_Black();

void EPDlib_Update();
#endif