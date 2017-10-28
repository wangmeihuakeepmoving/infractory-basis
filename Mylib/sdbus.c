#include "sdbus.h"
#include "dbus.h"
#include "gimbal_control.h"

int SDFlag=0;//Ĭ��Ϊ�ֶ�
int LastQKey=0;//��һ��Q
int LastEKey=0;
int BlueFlag=0;//Ĭ��Ϊ��ɫ

void SDState_Set(uint16_t v)
{
	int key_Q = KEY_PRESSED_OFFSET_Q & v; 
  int key_E = KEY_PRESSED_OFFSET_E & v; 
	if (key_Q!=0) key_Q=1;
	if (key_E!=0) key_E=1;
	if (LastQKey==0&&key_Q==1)
		{		
			SDFlag=1-SDFlag;
			if(SDFlag==0)
			{
				yaw.targetAngle=YAW_MID;
				pitch.targetAngle=PITCH_MID;	
			}
		}
	if (LastQKey==0&&key_Q==1)
	{
		yaw.targetAngle=YAW_MID;
		pitch.targetAngle=PITCH_MID;	
	}
	LastQKey=key_Q;
	LastEKey=key_E;
}


void SD_TriggerControl(void)
{
			//Pitch��
			pitch.targetAngle += ((double)sdbus.PitchAngle/360.)*8192; 
			if (pitch.targetAngle < pitch.minAngle){pitch.targetAngle=pitch.minAngle;}
			if (pitch.targetAngle > pitch.maxAngle){pitch.targetAngle=pitch.maxAngle;}		
			//Yaw��
			yaw.targetAngle += ((double)sdbus.YawAngle/360.)*8192;
			if (yaw.targetAngle < yaw.minAngle){yaw.targetAngle=yaw.minAngle;}
			if (yaw.targetAngle > yaw.maxAngle){yaw.targetAngle=yaw.maxAngle;}
				
}

SDBUS sdbus;
void SDBUS_Enc(const SDBUS* sdbus,unsigned char* sdbuf)//sdbus����
{
    sdbuf[0] = (sdbus->PitchAngle > 0)+'0';
    sdbuf[1] =  abs(sdbus->PitchAngle)/10+'0';
		sdbuf[2] = abs(sdbus->PitchAngle)%10+'0';
		sdbuf[3] = (sdbus->YawAngle > 0)+'0';
		sdbuf[4] = abs(sdbus->YawAngle)/10+'0';
		sdbuf[5] = abs(sdbus->YawAngle)%10+'0';
}

void SDBUS_Dec(SDBUS* sdbus,const unsigned char* sdbuf)//sdbus����
{
    sdbus->PitchAngle = (2*(sdbuf[0]-'0')-1)*((sdbuf[1]-'0')*10+(sdbuf[2]-'0'));
    sdbus->YawAngle= (2*(sdbuf[3]-'0')-1)*((sdbuf[4]-'0')*10+(sdbuf[5]-'0'));
}
