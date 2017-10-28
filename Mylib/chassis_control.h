#ifndef _CHASSIS_CONTROL_H_
#define _CHASSIS_CONTROL_H_
#include "stdint.h"
//
typedef struct _RM35_DATA_
{
	short thisCurrent;
	short thisVelocity;
	long  thisPosition;
	char Online;
	char Ctl1_Value;
	char Ctl2_Value;
}RM35_DATA;
extern  RM35_DATA RM35_1;
extern  RM35_DATA RM35_2;
extern  RM35_DATA RM35_3;
extern  RM35_DATA RM35_4;

typedef struct _RM3510_DATA_
{
	//�ӵ��������������ֵ	
	int16_t thisPosition;//�����ķ����Ƕ�
	int16_t thisVelocity;//��������
	//Ŀ���趨��ֵ
	int16_t targetPosition;//Ŀ��Ƕ�
	int16_t targetVelocity;//Ŀ���ٶ�
	//PID
	float position_output;//λ�û������λ�û�����
	float velocity_output;//�ٶȻ����������������
	//���ֵ��Ŀǰ����
	uint8_t number;
	
}RM3510_DATA;

extern RM3510_DATA RM3510_1;
extern RM3510_DATA RM3510_2;
extern RM3510_DATA RM3510_3;
extern RM3510_DATA RM3510_4;

//3510�� 
void ChassisMotor_Velocity_Control(float vel1,float vel2,float vel3,float vel4);
void ChassisMotor_Position_Control(float pos1,float pos2,float pos3,float pos4);

extern int moveSpeed;
void TransMove(int x,int y,int z,long temp_speed);
void move_control(uint16_t ch0, uint16_t ch1, uint16_t ch2, uint8_t s1, uint16_t v,int16_t x);

#endif
