#ifndef   _PORTSCAN_H
#define   _PORTSCAN_H




typedef struct
{
   u8   PortScan_New;
	 u8   PortScan_Old;
	 u8   PortScan_Cnt;
   u8   PorsScan_Task;
	 u8   Key_Num;
	 u8   Clr_Key_Num_Cnt;
	 u32  Gear_Data_Map;

}ScanInfoTypedef;



extern    ScanInfoTypedef  ScanInfo;











/***************************************************************************扫描IO状态只为清零标志***********************************************************************************************************/
#define     SET_MICSTART                (ScanInfo.PortScan_New |= 0X01)
#define     CLR_MICSTART                (ScanInfo.PortScan_New &= 0XFE) 
#define     MICSTART                    (ScanInfo.PortScan_New &  0X01)  
#define     MICSTART_OLD                (ScanInfo.PortScan_Old &  0X01)  
 



#define    SET_KEYSTART                 (ScanInfo.PortScan_New |= 0X02)
#define    CLR_KEYSTART                 (ScanInfo.PortScan_New &= 0XFD)
#define    KEYSTART                     (ScanInfo.PortScan_New &  0X02)
#define    KEYSTART_OLD                 (ScanInfo.PortScan_Old &  0X02)



#define    SET_USBSTART                 (ScanInfo.PortScan_New |= 0X04)
#define    CLR_USBSTART                 (ScanInfo.PortScan_New &= 0XFB)
#define    USBSTART                     (ScanInfo.PortScan_New &  0X04)
#define    USBSTART_OLD                 (ScanInfo.PortScan_Old &  0X04)



#define    SET_HEATSTART                (ScanInfo.PortScan_New |= 0X08)
#define    CLR_HEATSTART                (ScanInfo.PortScan_New &= 0XF7) 
#define    HEATSTART                    (ScanInfo.PortScan_New &  0X08) 
#define    HEATSTART_OLD                (ScanInfo.PortScan_Old &  0X08) 

/************************************************************************设置状态标志******************************************************************************************************************************/


#define   SET_OUTSTART                 (ScanInfo.PorsScan_Task |= 0X01)
#define   CLR_OUTSTART                 (ScanInfo.PorsScan_Task &= 0XFE)
#define   OUTSTART                     (ScanInfo.PorsScan_Task &  0X01)



#define   SET_OUTLOAD                  (ScanInfo.PorsScan_Task |= 0X02)
#define   CLR_OUTLOAD                  (ScanInfo.PorsScan_Task &= 0XFD)
#define   OUTLOAD                      (ScanInfo.PorsScan_Task &  0X02)




#define   SET_USBIN                    (ScanInfo.PorsScan_Task |= 0X04)
#define   CLR_USBIN                    (ScanInfo.PorsScan_Task &= 0XFB)
#define   USBIN                        (ScanInfo.PorsScan_Task &  0X04)

#define   SET_HEATIN                   (ScanInfo.PorsScan_Task |= 0X08)
#define   CLR_HEATIN                   (ScanInfo.PorsScan_Task &= 0XF7)
#define   HEATIN                       (ScanInfo.PorsScan_Task &  0X08)


void    Port_Scan(void);
void 		Power_Reset_Port_Scan(void);
void    Get_Usb_Ad(void);
#endif


