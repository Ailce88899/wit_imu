#ifndef HWT9073_h
#define HWT9073_h

#define SAVE 			0x00
#define CALSW 		        0x01
#define RSW 			0x02
#define RRATE			0x03
#define BAUD 			0x04
#define AXOFFSET	0x05
#define AYOFFSET	0x06
#define AZOFFSET	0x07
#define GXOFFSET	0x08
#define GYOFFSET	0x09
#define GZOFFSET	0x0a
#define HXOFFSET	0x0b
#define HYOFFSET	0x0c
#define HZOFFSET	0x0d

#define YYMM				0x30
#define DDHH				0x31
#define MMSS				0x32
#define MS					0x33
#define AX					0x34
#define AY					0x35
#define AZ					0x36
#define GX					0x37
#define GY					0x38
#define GZ					0x39
#define HX					0x3a
#define HY					0x3b
#define HZ					0x3c			
#define Roll				0x3d
#define Pitch				0x3f
#define Yaw			        0x41
#define TEMP				0x43	

struct STime
{
	unsigned char ucYear;
	unsigned char ucMonth;
	unsigned char ucDay;
	unsigned char ucHour;
	unsigned char ucMinute;
	unsigned char ucSecond;
	unsigned short usMiliSecond;
};
struct SAcc
{
	short a[3];
	short T;
};
struct SGyro
{
	short w[3];
	short T;
};
struct SAngle0
{
	short Angle0;
	//short T;
};
struct SAngle1
{
	short Angle1;
	//short T;
};
struct SAngle2
{
	short Angle2;
	//short T;
};
struct SMag
{
	short h[3];
	short T;
};

class CHWT9073 
{
public: 
	struct STime		stcTime;
	struct SAcc 		stcAcc;
	struct SGyro 		stcGyro;
	struct SAngle0 	stcAngle0;
	struct SAngle1 	stcAngle1;
	struct SAngle2 	stcAngle2;
	struct SMag 		stcMag;
	
    CHWT9073 (); 
    void CopeSerialData(unsigned char ucData[],unsigned short usLength);
    
};
extern CHWT9073 HWT9073;
#endif

