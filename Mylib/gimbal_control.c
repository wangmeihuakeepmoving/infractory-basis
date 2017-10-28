/************************************************************************************
  File Name     :  gimbal_control.c 
  cpu           :  STM32F405RGT6
  Create Date   :  2016/6/29
  Author        :  yf
  Description   :  ���6623��̨pithc��yaw���˶������¶��ϵĿ��ơ�
									 ����������������̨��2DOF����PIDλ�û��Ŀ��ƣ�
									 Ȼ������̨Զ�̿��ƺ�����ң�����ͼ��󣩣��������ȼ�����һЩ��
									 

-------------------------------Revision Histroy-----------------------------------
No   Version    Date     Revised By       Item       Description   
1     1.1       6/28       yf   			  ������̨����	
2     1.2       6/29       gyf 
3     1.3       6/29       yf 					  ע��			   
************************************************************************************/
//#include "i2c_mpu6050.h"
#include "gimbal_control.h"
#include "pid_algorithm.h"
#include "test_imu.h"
#include "delay.h"
#include "i2c_mpu6050.h"

//��ʼ����̨�Ƕ�
M6623 yaw = {YAW_LEFT,YAW_RIGHT,YAW_MID,0,0,0,0,YAW_MID,0,0};
M6623 pitch = {PITCH_DOWN,PITCH_UP,PITCH_MID,0,0,0,0,PITCH_MID,0,0};

/*********************************************************************
Name��          void Gimbal_Control(void)  

Description��  ��̨���Ƴ���
               �����˶�����Ϊ��ֵ
*********************************************************************/
void Gimbal_Control(void)  
{
	//�⻷PID����
	//����λ�ñջ������
	yaw.position_output = Position_Control_205(yaw.thisAngle,yaw.targetAngle);
	//�ڻ�PID����
  //Yaw.velocity_output = Velocity_Control_205(-MPU6050_Real_Data.Gyro_Z ,Yaw.position_output);
  yaw.velocity_output = Velocity_Control_205(-mpu_data.gz ,yaw.position_output);
	//����λ�ñջ������
	pitch.position_output = Position_Control_206(pitch.thisAngle,pitch.targetAngle);
	//�ڻ�PID����
  //Pitch.velocity_output = Velocity_Control_206(-MPU6050_Real_Data.Gyro_Y ,Pitch.position_output);
	pitch.velocity_output = Velocity_Control_206(-mpu_data.gy ,pitch.position_output);
	//can1�������������д��can1��can2����Ҫ����
	//Cmd_ESC(Yaw.velocity_output,Pitch.velocity_output);
	
}

/*********************************************************************
Name��         void Trigger_Control(int16_t x, int16_t y, uint16_t ch3)

Description��  ��̨Զ�̿��Ƴ���ң�����ͼ��̣�            
*********************************************************************/

void Trigger_Control(int16_t x, int16_t y, uint16_t ch3)
{
				//��ʱ����yaw��
				if (yaw.targetAngle < yaw.minAngle){yaw.targetAngle=yaw.minAngle;}
				if (yaw.targetAngle > yaw.maxAngle){yaw.targetAngle=yaw.maxAngle;}

			
				if (y>3) {pitch.targetAngle += -15;}
        if (y<-3) {pitch.targetAngle += 15;}
				pitch.targetAngle += (ch3-1024)/33;
			
				if (pitch.targetAngle < pitch.minAngle){pitch.targetAngle=pitch.minAngle;}
				if (pitch.targetAngle > pitch.maxAngle){pitch.targetAngle=pitch.maxAngle;}		
			
}
