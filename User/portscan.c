#include "main.h"



ScanInfoTypedef  ScanInfo;



void    Get_Usb_Ad(void)
{
	
   BatVoltage();
   BatInfo.Usb_Ad_Volt = GetADCValue(USB_CHANNEL);
	 
   BatInfo.Usb_Ad_Volt =  (u32)BatInfo.Bat_Volt*BatInfo.Usb_Ad_Volt>>12;

}

void   Out_Stop(void)
{

   if(OUTLOAD)
	 {
			ClrShortData();
	    Disp_Smok_Stop;

	 }

}

void Power_Reset_Port_Scan(void)
{
    if(MIC_IO)
      SET_MICSTART;

//    Get_Usb_Ad();
//	
//		if(BatInfo.Usb_Ad_Volt >= 700)	
//     SET_USBSTART;
//    else
//     CLR_USBSTART;

		ScanInfo.PortScan_Old  = ScanInfo.PortScan_New;
}

void    Port_Scan(void)
{

//	  if(SysInfo.Power_Rest){return;}

    if(MIC_IO)
      SET_MICSTART;
    else
      CLR_MICSTART;

#if 0
    if(USB_IO)
     SET_USBSTART;
    else
     CLR_USBSTART;			
#else
   Get_Usb_Ad();
	
		if(BatInfo.Usb_Ad_Volt >= 700)	
     SET_USBSTART;
    else
     CLR_USBSTART;		

#endif


#ifdef KEY_USE
		if(KEY_IO)
			SET_KEYSTART;
		else
			CLR_KEYSTART;
#endif

		if(ScanInfo.PortScan_New != ScanInfo.PortScan_Old)
		{
		   if(ScanInfo.PortScan_Cnt < 3){ScanInfo.PortScan_Cnt++;}
		   else
			 {

			    if(MICSTART&&!MICSTART_OLD)
					{
						SET_OUTSTART;
					}
					if(!MICSTART&&MICSTART_OLD) 
					{
						CLR_OUTSTART;

						if(Dispinfo.Disp_Smoke_Effect_Cnt < 22)
						{
							Dispinfo.Disp_Smoke_Stop_Effect_Flag = 1;
						}else{
							Dispinfo.Disp_Smoke_Stop_Effect_Flag = 0;
						}

						//SetLEDIcRunParam(0, DYNAMIC_LED_IC_NUM, 0,(u8*)GetWattGearsColorTab(swInfo.swGeras), DYNAMIC_LED_IC_NUM*3, 0,0);
						Out_Stop(); 
					}
				#ifdef KEY_USE	
					if(KEYSTART&&!KEYSTART_OLD) { ScanInfo.Clr_Key_Num_Cnt = 50;if(ScanInfo.Key_Num < 10){ScanInfo.Key_Num++; }}
					if(!KEYSTART&&KEYSTART_OLD) {  ScanInfo.Clr_Key_Num_Cnt = 30;}
				#endif

					if(USBSTART&&!USBSTART_OLD)
					{
						// 开充电电流
						CHRG_ENABLE;
					//	OutInfo.Out_Usb_In_Out_Smoke_Cnt = 2;
						if(OutInfo.Out_Enable_Flag == 0)
						{
							Disp_Power_Usb_In;
						}else if((Dispinfo.Disp_Task != LowRes) &&  (!OUTLOAD))
						{
							
						}

						if((Dispinfo.Disp_Task != LowRes) && (!OUTLOAD))
						{
							
						}

						OutInfo.Out_Enable_Flag = 1;
						BatInfo.Usb_In_Flag = 1;
						SET_USBIN;
					}

					if(!USBSTART&&USBSTART_OLD) 
					{
						CLR_USBIN;
						BatInfo.Usb_Full_Cnt = 0;
						BatInfo.Usb_In_Flag = 0;
						BatInfo.Usb_Full_Flag = 0;
						BatInfo.Usb_Led_Twinkle_Cnt = 0;		
						//OutInfo.Out_Usb_In_Out_Smoke_Cnt = 2;

					  if(BatInfo.Ovp_En == 0){Disp_Usb_Out;}
					  BatInfo.Ovp_En = 0;
					}

			    if(HEATSTART&&!HEATSTART_OLD) {SET_HEATIN;}
					if(!HEATSTART&&HEATSTART_OLD) {CLR_HEATIN;}

			   ScanInfo.PortScan_Cnt = 0;
			   ScanInfo.PortScan_Old  = ScanInfo.PortScan_New;
			 }
		}
		else{  ScanInfo.PortScan_Cnt = 0;}

	#ifdef KEY_USE
    if(ScanInfo.Clr_Key_Num_Cnt){ScanInfo.Clr_Key_Num_Cnt--;}
		else
		{
		   if(!KEYSTART_OLD)//松开的情况
			 {
			    if(ScanInfo.Key_Num == 2)
					{
					   if(OutInfo.Out_Gear_Leve == 1){OutInfo.Out_Gear_Leve = 2;  ScanInfo.Gear_Data_Map = DISP_OUT_GEAR2;  }
						 else{OutInfo.Out_Gear_Leve = 1;    ScanInfo.Gear_Data_Map = DISP_OUT_GEAR1;}
					   Disp_Gear;
					}			 
			 }
		ScanInfo.Key_Num = 0;
		}
	#endif


}


