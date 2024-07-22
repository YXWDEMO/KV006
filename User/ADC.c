#include "ADC.h"
#include "main.h"

#define HAL_VREF_INT    (*(uint8_t *)(0x1fff0023))
#define HAL_VREF_DEC    (*(uint8_t *)(0x1fff0022))

//#define vref_int        (*(uint8_t *)(HAL_VREF_INT))        //存放参考电压整数部分
//#define vref_dec        (*(uint8_t *)(HAL_VREF_DEC))        //存放参考电压小数部分
float vref;               //参考电压值
uint16_t	vref_LDO;

uint8_t Bcd2ToByte(uint8_t Value)
{
    uint32_t tmp = 0U;

    tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10U;
    return (tmp + (Value & (uint8_t)0x0F));
}

uint16_t Adc_CalBatRef(void)
{
	uint8_t data_vref_int,data_vref_dec;

    data_vref_int = Bcd2ToByte(HAL_VREF_INT);
    data_vref_dec = Bcd2ToByte(HAL_VREF_DEC);
	//初始化所有外设，flash接口，systick
    vref = data_vref_int/10;     //计算参考电压
    vref = vref + ((data_vref_int%10)*0.1 + data_vref_dec*0.001);
		vref = vref*1000;
		vref_LDO = (uint16_t)vref;

	if (vref_LDO<1100 || vref_LDO> 1300)
	{
		vref_LDO=1200;
	}
	return vref_LDO;
}

void delay_us(uint16_t us)
{
	uint16_t i,j;
	for(j=0;j<us;j++)
	{
		for(i=0;i<32;i++)
		{
		__NOP();
		}
	}
}


void adc_init(void)
{
		SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_ADCRST); // ADC复位
		CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_ADCRST); // ADC 释放复位

    //使能ADC时钟
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_ADC1);
  
    LL_ADC_InitTypeDef ADC_Init= {0};
    LL_ADC_REG_InitTypeDef LL_ADC_REG_InitType= {0};
    ADC_Common_TypeDef ADC_Common_Type= {0};

    //设置ADC频率（24M/4）,右对齐，无低功耗模式，12位精度
    ADC_Init.Clock=LL_ADC_CLOCK_SYNC_PCLK_DIV2;
    ADC_Init.DataAlignment=LL_ADC_DATA_ALIGN_RIGHT;
    ADC_Init.LowPowerMode=LL_ADC_LP_MODE_NONE;
    ADC_Init.Resolution=LL_ADC_RESOLUTION_12B;
    LL_ADC_Init(ADC1,&ADC_Init);
    //采样转化周期
    LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_239CYCLES_5);
    //采样模式
    LL_ADC_REG_InitType.ContinuousMode=LL_ADC_REG_CONV_SINGLE;
    LL_ADC_REG_InitType.Overrun=LL_ADC_REG_OVR_DATA_OVERWRITTEN;
    LL_ADC_REG_InitType.SequencerDiscont=LL_ADC_REG_SEQ_DISCONT_DISABLE;
    LL_ADC_REG_InitType.TriggerSource=LL_ADC_REG_TRIG_SOFTWARE;
    LL_ADC_REG_Init(ADC1,&LL_ADC_REG_InitType);
#if 0
	__IO uint32_t wait_loop_index = 0; //开启ADC调压器
    //选择1.5V作为ADC参考源
    LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1),LL_ADC_PATH_INTERNAL_VREFINT);
    LL_ADC_SetVrefBufferVoltage(ADC1,LL_ADC_VREFBUF_1P5V);
    LL_ADC_EnableVrefBufferVoltage(ADC1);
    wait_loop_index = ((LL_ADC_DELAY_VREFINT_STAB_US * (SystemCoreClock / (100000 * 2))) / 10);
    while(wait_loop_index != 0)
    {
        wait_loop_index--;
    }
#endif

	//ADC校准
    if (LL_ADC_IsEnabled(ADC1) == 0)
    {
        LL_ADC_StartCalibration(ADC1);
        while (LL_ADC_IsCalibrationOnGoing(ADC1) != 0)
        {
        }
        LL_mDelay(1);
    }

}


void adc_enable(void)
{
    //使能ADC
    LL_ADC_Enable(ADC1);
    delay_us(8);
}

//单通道，配置通道前不能使能ADC
void adc_channel_config(uint8_t channel)
{
    switch (channel)
    {
    case 0:
        ADC_0_GPIO;
        LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_0);
        break;
    case 1:
        ADC_1_GPIO;
        LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_1);
        break;
    case 2:
        ADC_2_GPIO;
        LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_2);
        break;
    case 3:
        ADC_3_GPIO;
        LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_3);
        break;
    case 4:
        ADC_4_GPIO;
        LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_4);
        break;
    case 5:
        ADC_5_GPIO;
        LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_5);
        break;
    case 6:
        ADC_6_GPIO;
        LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_6);
        break;
    case 7:
        ADC_7_GPIO;
        LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_7);
        break;
		case 8:
        LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_TEMPSENSOR);
        break;
		case 9:
        LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_VREFINT);
				LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1),LL_ADC_PATH_INTERNAL_VREFINT);
        break;
    default:
        break;
    }

}
//开启转换
void adc_start(void)
{
    LL_ADC_REG_StartConversion(ADC1);
}
void adc_disable(void)
{
    LL_ADC_Disable(ADC1);
}

//多通道
void adc_channels_config(uint8_t *channel,uint8_t num)
{
    ADC1->CHSELR=0;
    for(uint8_t i=0; i<num; i++)
	{
			switch (*(channel+i))
    {
    case 0:
        ADC_0_GPIO;
        LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_0);
        break;
    case 1:
        ADC_1_GPIO;
        LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_1);
        break;
    case 2:
        ADC_2_GPIO;
        LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_2);
        break;
    case 3:
        ADC_3_GPIO;
        LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_3);
        break;
    case 4:
        ADC_4_GPIO;
        LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_4);
        break;
    case 5:
        ADC_5_GPIO;
        LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_5);
        break;
    case 6:
        ADC_6_GPIO;
        LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_6);
        break;
    case 7:
        ADC_7_GPIO;
        LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_7);
        break;
    default:
        break;
    }
	}       
}
//获取AD值
uint16_t adc_dr(void)
{
    uint16_t dr=0;
    while(!LL_ADC_IsActiveFlag_EOC(ADC1));
    LL_ADC_ClearFlag_EOC(ADC1);
    dr=	LL_ADC_REG_ReadConversionData12(ADC1);
    return dr;
}
//选择通道12，通过1.2V反推VCC
uint16_t adc_vcc(void)
{
    uint16_t vcc=0;
    vcc=adc_dr();
    return __LL_ADC_CALC_VREFANALOG_VOLTAGE(vcc,LL_ADC_RESOLUTION_12B);
}

uint16_t GetADCValue(uint32_t ADC_Channel)//
{
	uint16_t return_adValue=0;

	adc_disable();
	/* 设定ADC的采样通道*/

	adc_channel_config(ADC_Channel);
	/* ADC使能*/
	adc_enable();
	/* ADC 开始转换 */
	LL_ADC_REG_StartConversion(ADC1);

	while(LL_ADC_IsActiveFlag_EOC(ADC1) != 1);

	LL_ADC_ClearFlag_EOC(ADC1);

	return_adValue = LL_ADC_REG_ReadConversionData12(ADC1);

	return return_adValue;
}

uint16_t GetAverageADCValue(uint32_t ADC_Channel,uint8_t ADC_SampleNum)
{
	uint16_t return_adValue=0;
	uint32_t sumAdValue=0;
//	uint16_t preAdcValue = 0;
//	uint16_t CurrtAdcValue = 0;
//	uint16_t AdcSampleCnt = 0;

	for(uint8_t i = 0; i < ADC_SampleNum; i++)
	{

//		CurrtAdcValue = GetADCValue(ADC_Channel);

//		if(abs(CurrtAdcValue-preAdcValue) <= 100)
//		{
			sumAdValue += GetADCValue(ADC_Channel);
//		}

//		preAdcValue = CurrtAdcValue;
	}

	return_adValue = sumAdValue/ADC_SampleNum;

	return return_adValue;
}
