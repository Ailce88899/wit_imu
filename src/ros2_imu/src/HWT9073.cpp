#include <HWT9073.h>
#include "string.h"

int angle_tip;
CHWT9073 ::CHWT9073 ()
{
}

void CHWT9073 ::CopeSerialData(unsigned char ucData[],unsigned short usLength)
{
	static unsigned char chrTemp[2000];
	static unsigned char ucRxCnt = 0;	
	static unsigned short usRxLength = 0;


    memcpy(chrTemp,ucData,usLength);
	usRxLength += usLength;
    while (usRxLength >= 11)
    {
        if (chrTemp[0] != 0x55)
        {
			usRxLength--;
			memcpy(&chrTemp[0],&chrTemp[1],usRxLength);                        
            continue;
        }
        else if (chrTemp[1] == 0x51)
        {
            memcpy(&stcAcc,&chrTemp[2],8);
        }
        else if (chrTemp[1] == 0x52)
        {
            memcpy(&stcGyro,&chrTemp[2],8);
        }
        else if (chrTemp[1] == 0x53)
        {
            if(chrTemp[2] == 0x01)
            {
              memcpy(&stcAngle0,&chrTemp[4],8);
              angle_tip = angle_tip+1;
            }
            else if (chrTemp[2] == 0x02)
            {
              memcpy(&stcAngle1,&chrTemp[4],8);
              angle_tip = angle_tip+1;
            }
            else if (chrTemp[2] == 0x03)
            {
              memcpy(&stcAngle2,&chrTemp[4],8);
              angle_tip = angle_tip+1;
            }
        }
        else if (chrTemp[1] == 0x54)
        {
           memcpy(&stcMag,&chrTemp[2],8);
        }
		/*switch(chrTemp[1])
		{
			case 0x50:	memcpy(&stcTime,&chrTemp[2],8);break;
			case 0x51:	memcpy(&stcAcc,&chrTemp[2],8);break;
			case 0x52:	memcpy(&stcGyro,&chrTemp[2],8);break;
			case 0x53:	memcpy(&stcAngle,&chrTemp[2],8);break;
			case 0x54:	memcpy(&stcMag,&chrTemp[2],8);break;
			case 0x55:	memcpy(&stcDStatus,&chrTemp[2],8);break;
			case 0x56:	memcpy(&stcPress,&chrTemp[2],8);break;
			case 0x57:	memcpy(&stcLonLat,&chrTemp[2],8);break;
			case 0x58:	memcpy(&stcGPSV,&chrTemp[2],8);break;
                       case 0x59:	memcpy(&stcQ,&chrTemp[2],8);break;
		}*/
	usRxLength -= 11;
	memcpy(&chrTemp[0],&chrTemp[11],usRxLength);                     
    }
}
CHWT9073 HWT9073 = CHWT9073();

