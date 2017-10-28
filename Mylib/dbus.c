/*�����main.h˵��*/
#include "dbus.h"

DBUS dbus;

void DBUS_Enc(const DBUS* pdbus,unsigned char* pbuf)//dbus����
{  
    pbuf[0] = pdbus->rc.ch0&0xff;
    pbuf[1] = (pdbus->rc.ch1<<3) | (pdbus->rc.ch0>>8);
    pbuf[2] = (pdbus->rc.ch2<<6) | (pdbus->rc.ch1>>5);
    pbuf[3] = pdbus->rc.ch2;
    pbuf[4] = (pdbus->rc.ch3<<1) | (pdbus->rc.ch2>>10);
    pbuf[5] = (pdbus->rc.s2<<6) | (pdbus->rc.s1<<4) | (pdbus->rc.ch3>>7);
    pbuf[6] = pdbus->mouse.x;
    pbuf[7] = pdbus->mouse.x>>8;
    pbuf[8] = pdbus->mouse.y;
    pbuf[9] = pdbus->mouse.y>>8;
    pbuf[10] = pdbus->mouse.z;
    pbuf[11] = pdbus->mouse.z>>8;
    pbuf[12] = pdbus->mouse.l;
    pbuf[13] = pdbus->mouse.r;
    pbuf[14] = pdbus->key.v;
    pbuf[15] = pdbus->key.v>>8;
    pbuf[16] = pdbus->res;
    pbuf[17] = pdbus->res>>8;
}

void DBUS_Dec(DBUS* pdbus,uint8_t* pbuf)//dbus����
{  
    pdbus->rc.ch0 = (pbuf[0] | (pbuf[1] << 8)) & 0x07ff;          //!< Channel 0  
    pdbus->rc.ch1 = ((pbuf[1] >> 3) | (pbuf[2] << 5)) & 0x07ff;   //!< Channel 1         
    pdbus->rc.ch2 = ((pbuf[2] >> 6) | (pbuf[3] << 2) |     //!< Channel 2                          
        (pbuf[4] << 10)) & 0x07ff;
    pdbus->rc.ch3 = ((pbuf[4] >> 1) | (pbuf[5] << 7)) & 0x07ff;   //!< Channel 3   
    pdbus->rc.s1 = ((pbuf[5] >> 4) & 0x000C) >> 2;                    //!< Switch left         
    pdbus->rc.s2 = ((pbuf[5] >> 4) & 0x0003);                         //!< Switch right  
    pdbus->mouse.x = pbuf[6] | (pbuf[7] << 8);                    //!< Mouse X axis 
    pdbus->mouse.y = pbuf[8] | (pbuf[9] << 8);                    //!< Mouse Y axis 
    pdbus->mouse.z = pbuf[10] | (pbuf[11] << 8);                  //!< Mouse Z axis 
    pdbus->mouse.l = pbuf[12];                                        //!< Mouse Left Is Press ?
    pdbus->mouse.r = pbuf[13];                                        //!< Mouse Right Is Press ? 
    pdbus->key.v = pbuf[14] | (pbuf[15] << 8);                    //!< KeyBoard value   
    pdbus->res = pbuf[16] | (pbuf[17] << 8);                      //!< Reserve 

}
int DBUS_Det(DBUS dbus_detect)//����s1��s2���������ж��Ƿ���dbus���ݴ���
{	
	if(dbus_detect.rc.s1 != 0 && dbus_detect.rc.s2 != 0)
	{ return 1;}
	else 
		return 0;
}

