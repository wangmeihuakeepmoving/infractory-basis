#include "stm32f4xx_hal.h"
#include "stdint.h"

#ifndef __GIMBAL_CONTROL_H__
#define __GIMBAL_CONTROL_H__

typedef struct _M6623_
{
	int16_t minAngle;//��С�Ƕ�
	int16_t maxAngle;//���Ƕ�
	int16_t defualtAngle;//��ʼ�Ƕ�
	
	//����̨�ж�������ֵ
	int16_t thisAngle_Raw;//ԭ���ķ����Ƕ�
	int16_t thisAngle;//�����ķ����Ƕ�
	int16_t thisCurrent;//��������
	int16_t targetCurrent;//Ŀ�����
	
	int16_t targetAngle;//Ŀ��Ƕ�
	
	float position_output;//λ�û������λ�û�����
	float velocity_output;//�ٶȻ����������������

}M6623;

extern M6623 yaw,pitch;

void Gimbal_Control(void);
void Trigger_Control(int16_t x,int16_t y,uint16_t ch3);

#endif
