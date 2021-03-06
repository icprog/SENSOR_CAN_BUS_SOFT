/***********************************************************
*
*双CAN总线，
*
*
************************************************************/


#include "led.h"
#include "delay.h"
#include "sensor.h"
#include "sys.h"
#include "can.h" 
#include "can2.h"
#include "rs232.h"
#include "usart.h"
#include "at24cxx.h"
 
#define ExtendID_1   0xA000000a   //CAN 1 
#define ExtendID_2   0xB000000a   //CAN 2

 
 int main(void)
 {	 	
	u8 i=0,j=0;
	u8 value=0;
	u8 trig_canbuf[8]={0x50,1,1,1,0,0,0,0};  //传感器1 ,触发发送信号 2017.11.25
	u8 trig_canbuf2[8]={0x50,2,2,2,0,0,0,0}; //传感器2, 触发发送信号
	u8 trig_canbuf3[8]={0x50,3,3,3,0,0,0,0}; //传感器3,
	u8 notrig_canbuf[8]={0x0A};   //没有触发的，发送的信号
	u8 mode=CAN_Mode_Normal;//CAN工作模式;CAN_Mode_Normal(0)：普通模式，CAN_Mode_LoopBack(1)：环回模式
     RS232_init();//串口1初始化
	delay_init();	    	 //延时函数初始化	  
  LED_Init();	
  I2C_INIT();		 //IIC初始化
	SENSOR_Init();
 
  CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,16,mode);//CAN初始化环回模式,波特率125Kbps     
  CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,16,mode);//CAN初始化环回模式,波特率125Kbps    
	
 while(1)
 {
       
		AT24Cxx_WriteOneByte(0,0x5);	  //24c02写数据
		value=AT24Cxx_ReadOneByte(0);
		trig_canbuf[7]=value;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0)  //触发传感器 1
    {
		  delay_ms(10);
		  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0)   //
			{
				Can1_Send_Msg(trig_canbuf,ExtendID_1,CAN_RTR_Data);//发送8个字节 
				delay_ms(10);
				Can2_Send_Msg(trig_canbuf,ExtendID_2,CAN_RTR_Data);//发送8个字�
				delay_ms(10);
				LED1=1;		//  smd led 闪烁
				LED0=1;
				delay_ms(100);
				LED1=0;
				LED0=0;
				delay_ms(100);
				LED1=1;
				 LED0=1;			
				delay_ms(100);
				LED1=0;
				LED0=0;	
				delay_ms(100);
				LED1=1;
				LED0=1;		
     				
				}
	 }
	/**************************触发传感器2*******************************/
	 else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0)
	 {
			delay_ms(10);
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0)
			{
			  Can1_Send_Msg(trig_canbuf2,ExtendID_1,CAN_RTR_Data);//发送8个字节 
		      delay_ms(10);
		      Can2_Send_Msg(trig_canbuf2,ExtendID_2,CAN_RTR_Data);//发送8个字�
				    delay_ms(10);
					LED1=1;		//  smd led 闪烁
					LED0=1;
					delay_ms(50);
					LED1=0;
					LED0=0;
					delay_ms(50);
					LED1=1;
					LED0=1;			
					delay_ms(50);
					LED1=0;
				    LED0=0;
				    delay_ms(50);
					LED1=1;
					LED0=1;
			}
		}
	 /**************************触发传感器3***********************************************/
		else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
		{
			   delay_ms(10);
			   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
			   {
				 Can1_Send_Msg(trig_canbuf3,ExtendID_1,CAN_RTR_Data);//发送8个字节 
		         delay_ms(10);
		         Can2_Send_Msg(trig_canbuf3,ExtendID_2,CAN_RTR_Data);//发送8个字�
				 delay_ms(10);
					LED1=1;		//  smd led 闪烁
					LED0=1;
					delay_ms(50);
					LED1=0;
					LED0=0;
					delay_ms(50);
					LED1=1;
					LED0=1;			
					delay_ms(50);
					LED1=0;
				    LED0=0;
				 	delay_ms(50);
					LED1=1;
					LED0=1;	
			 }
		}
		
	  /*******************************没有触发传感器器************************************************/
		else 
		{
			   for(i=0;i<101;i++)
			        {
          			      delay_ms(10);
						  if(i==100)
							{
								notrig_canbuf[1]=0x01;
								Can1_Send_Msg(notrig_canbuf,ExtendID_1,CAN_RTR_Data);//发送8个字节 
								delay_ms(5);
								Can2_Send_Msg(notrig_canbuf,ExtendID_2,CAN_RTR_Data);//发送8个字�
								delay_ms(5);
			                    notrig_canbuf[1]=0x02;
			                    Can1_Send_Msg(notrig_canbuf,ExtendID_1,CAN_RTR_Data);//发送8个字节
                 	             delay_ms(5);									
								 Can2_Send_Msg(notrig_canbuf,ExtendID_2,CAN_RTR_Data);//发送8个字�
			           	         delay_ms(5);
								 notrig_canbuf[1]=0x03;
								 Can1_Send_Msg(notrig_canbuf,ExtendID_1,CAN_RTR_Data);//发送8个字节 
								 delay_ms(5);
								 Can2_Send_Msg(notrig_canbuf,ExtendID_2,CAN_RTR_Data);//发送8个字�
								 delay_ms(5);
					
							  }
								for(j=0;j<200;j++)
								{
								  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0)
								{
								 delay_ms(10);
								 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0)
								{
									Can1_Send_Msg(trig_canbuf,ExtendID_1,CAN_RTR_Data);//发送8个字节 
									delay_ms(10);
									Can2_Send_Msg(trig_canbuf,ExtendID_2,CAN_RTR_Data);//发送8个字�
									delay_ms(500);
									delay_ms(500);
									LED1=1;		//  smd led 闪烁
									LED0=1;
									delay_ms(100);
									LED1=0;
									LED0=0;
									delay_ms(100);
									LED1=1;
									LED0=1;			
									delay_ms(100);
									LED1=0;
									LED0=0;	
								}
							}	
							
						 
						
						else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0)
						{
								 delay_ms(5);
							   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0)
										{
											delay_ms(10);
											Can1_Send_Msg(trig_canbuf2,ExtendID_1,CAN_RTR_Data);//发送8个字节 
											 delay_ms(10);
											 Can2_Send_Msg(trig_canbuf2,ExtendID_2,CAN_RTR_Data);//发送8个字�
											 delay_ms(500);
									         delay_ms(500);
												LED1=1;		//  smd led 闪烁
												LED0=1;
												delay_ms(100);
												LED1=0;
												LED0=0;
												delay_ms(100);
												LED1=1;
												LED0=1;			
												delay_ms(100);
												LED1=0;
											  LED0=0;
										}
							  
						     }
					       else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
						     {
								  delay_ms(5);
							      if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
									 {
										delay_ms(10);
										 Can1_Send_Msg(trig_canbuf3,ExtendID_1,CAN_RTR_Data);//发送8个字节 
										 delay_ms(10);
										 Can2_Send_Msg(trig_canbuf3,ExtendID_2,CAN_RTR_Data);//发送8个字�
										 delay_ms(500);
									   delay_ms(500);
											LED1=1;		//  smd led 闪烁
											LED0=1;
											delay_ms(100);
											LED1=0;
											LED0=0;
											delay_ms(100);
											LED1=1;
											LED0=1;			
											delay_ms(100);
											LED1=0;
										  LED0=0;
									 }
							  }
					
                }  //end for(j=0;)
		     }
	    }
    
  } //end while(1)
}
		








