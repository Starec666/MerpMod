/*
	Copyright (C) 2012-2013 Merrill A. Myers III merrillamyersiii@gmail.com
	
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

//////////////////////////
//Enumerations
//////////////////////////
enum TableType3D
{
	UInt8Table3D = (unsigned long)0x04000000,
	UInt16Table3D = (unsigned long)0x08000000
};

enum TableType2D
{
	UInt8Table2D = (unsigned short)0x0400,
	UInt16Table2D = (unsigned short)0x0800,
	FloatTable2D = (unsigned short)0x0000
};

enum CruiseToggles
{
	ToggleCoast = (unsigned char)0x00,
	ToggleResume = (unsigned char)0x01,
	ToggleCancel = (unsigned char)0x02,
	ToggleCruise = (unsigned char)0x03,
	ToggleInit = (unsigned char)0xFF,
};

enum ValetModes
{
	ValetModeDisabled = (unsigned char)0x00,
	ValetModeEnabled = (unsigned char)0x01
};

enum MafModeValues
{
	MafModeUndefined = (unsigned char)0x00,
	MafModeSensor = (unsigned char)0x01,
	MafModeSpeedDensity = (unsigned char)0x02,
	MafModeBlending = (unsigned char)0x03,
};
enum RevLimModeValues
{
	RevLimModeUndefined = (unsigned char)0x00,
	RevLimModeFuelCut = (unsigned char)0x01,
	RevLimModeSparkCut = (unsigned char)0x02,
	RevLimModeComboCut = (unsigned char)0x03,
};
enum LCTimingModeValues
{
	LCTimingModeUndefined = (unsigned char)0x00,
	LCTimingModeDisabled = (unsigned char)0x01,
	LCTimingModeCompensated = (unsigned char)0x02,
	LCTimingModeLocked = (unsigned char)0x03,
};
enum LCFuelModeValues
{
	LCFuelModeUndefined = (unsigned char)0x00,
	LCFuelModeDisabled = (unsigned char)0x01,
	LCFuelModeCompensated = (unsigned char)0x02,
	LCFuelModeLocked = (unsigned char)0x03,
};
enum FlatFootShiftModeValues
{
	FlatFootShiftModeDisabled = (unsigned char)0x00,
	FlatFootShiftModeStatic = (unsigned char)0x01,
	FlatFootShiftModeAuto = (unsigned char)0x0,
};
enum MapBlendModeValues
{
	MapBlendingInputModeUndefined = (unsigned char)0x00,
	MapBlendingInputModeTGVLeft = (unsigned char)0x01,
	MapBlendingInputModeTGVRight = (unsigned char)0x02
};
enum MapSwitchModeValues
{
	MapSwitchingInputModeUndefined = (unsigned char)0x00,
	MapSwitchingInputModeTGVLeft = (unsigned char)0x01,
	MapSwitchingInputModeTGVRight = (unsigned char)0x02,
	MapSwitchingInputModeSiDrive = (unsigned char)0x03
};
enum HardResetFlagValues
{
	HardResetFlagDisabled = (unsigned char)0x00,
	HardResetFlagEnabled = (unsigned char)0x01,
};
enum MapSwitchValues
{
	MapSwitchUndefined = (unsigned char)0x00,
	MapSwitch1 = (unsigned char)0x01,
	MapSwitch2 = (unsigned char)0x02,
	MapSwitch3 = (unsigned char)0x03,
};
enum HackSwitch
{
	HackDisabled = (unsigned char)0x00,
	HackEnabled = (unsigned char)0x01,
};
//,1=S,2=S#,3=I,8=S#,16=I"
enum SiDriveModes
{
	SiDriveSS = (unsigned char)0x02,
	SiDriveSSAlt = (unsigned char)0x08,
	SiDriveS = (unsigned char)0x01,
};

enum ProgModeStatusValues
{
	ProgModeDisabled = (unsigned char)0x00,
	ProgModeEnabled = (unsigned char)0x01,
	ProgModeSelectMode = (unsigned char)0x02,
	ProgModeAdjustValue = (unsigned char)0x03,
};

//////////////////////////////
//Type Definitions for Tables
//////////////////////////////
typedef struct 
{
	short columnCount;
	short rowCount;
	float* columnHeaderArray;
	float* rowHeaderArray;
	void* tableCells;
	int tableType;
	float multiplier;
	float offset;
} ThreeDTable;

typedef struct 
{
	short columnCount;
	short tableType;
	float* columnHeaderArray;
	short* tableCells;
	float multiplier;
	float offset;
} TwoDTable;

typedef struct
{
	ThreeDTable* TableI;
	ThreeDTable* TableS;
	ThreeDTable* TableSS;
} TableSubSet;

typedef struct{
	TableSubSet Map1;
	TableSubSet Map2;
} TableGroup;

typedef struct
{
	long s1;
	long s2;
	char Vin[20];
	long e1;
	long e2;
} VinBlockStruct;

//////////////////////////////
//Type Definitions for CAN_HACKS
//////////////////////////////

//MailboxModeConfiguration
enum mcsModes
{
	mcsTrans = 0,
	mcsRemoteFrameRx = 1,
	mcsReceiveBase = 2,
	mcsReceive = 3,
	mcsTransRTR_RX = 4,
	mcdTransRTR = 5,
	mcsSettingProhibited = 6,
	mcsInactive = 7,
};

typedef struct 
{
	unsigned long id;	//11 or 29 bit ID
	unsigned long callback;//32Bit Callback Function
	char ext;			//0 = standard, 1= ext
	char dlc;			//0 to 8 bytes
	char bus;			//0 = HCAN1, 1 = HCAN2
	char mailBox;		//mb 0 to 31, 0 reserved for RX only, 
	char mcs;			//mode Control
	char nmc;			//nmc
	unsigned short rate;	//Rate to send from 1 to 65535 mSec
} CanMessageSetupStruct;


enum canDTtypes
{
	dtUndefined = 0,
	dtChar = 1,
	dtShort = 2,
	dtLong = 3,
	dtFloat = 4,
};

typedef struct 
{
	unsigned long addr;	//U32 Address 0xFFFF0000 and greater is allowed
	char type;	//enum canDTtypes, must be 1...4
	char ccm;	//linked ccm Message, must be 0...7
	char bytePos;	//data position, umust be 0..7, needs to be byte alligned if U16,U32, or float, 
} CanDataSendStuct;

#if RACEGRADE_KEYPAD_HACKS
enum buttonStateRG
{
	edgeNA = 0,
	edgeRising = 1,
	edgeFailing = 2,
};

typedef struct  
{
	unsigned char state;
	unsigned char led;
	unsigned char edgeDetect;	
}buttonRGStruct;
#endif
