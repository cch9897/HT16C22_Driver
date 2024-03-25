//
// Created by cch on 2023/3/2.
//

#include <stdint.h>

#define HT16C22_I2C_Addr    0x3F


typedef enum {
    HT16C22_Bias_13 = 0,
    HT16C22_Bias_14 = 1
} HT16C22_Bias;

typedef enum {
    HT16C22_WorkMode_OFF = 0,
    HT16C22_WorkMode_NO_Display = 2,
    HT16C22_WorkMode_All_Work = 3
} HT16C22_WorkMode;

typedef enum {
    HT16C22_FPS_80 = 0,
    HT16C22_FPS_160 = 1
} HT16C22_FPS;

typedef enum {
    HT16C22_SharePin_VLCD_IVA_OFF = 0,
    HT16C22_SharePin_VLCD_IVA_ON = 1,
    HT16C22_SharePin_SEG_IVA_OFF = 2,
    HT16C22_SharePin_SEG_IVA_ON = 3,
} HT16C22_SharePin;

//不同偏压乘以VDD的倍率不同
typedef enum {
    HT16C22_IVA_Bias13_Full,
    HT16C22_IVA_Bias13_0975,
    HT16C22_IVA_Bias13_0918,
    HT16C22_IVA_Bias13_0882,
    HT16C22_IVA_Bias13_0849,
    HT16C22_IVA_Bias13_0818,
    HT16C22_IVA_Bias13_0789,
    HT16C22_IVA_Bias13_0763,
    HT16C22_IVA_Bias13_0738,
    HT16C22_IVA_Bias13_0714,
    HT16C22_IVA_Bias13_0692,
    HT16C22_IVA_Bias13_0672,
    HT16C22_IVA_Bias13_0652,
    HT16C22_IVA_Bias13_0634,
    HT16C22_IVA_Bias13_0616,
    HT16C22_IVA_Bias13_0600,
    //Bias13
    HT16C22_IVA_Bias12_Full = 0,
    HT16C22_IVA_Bias12_0937 = 1,
    HT16C22_IVA_Bias12_0882 = 2,
    HT16C22_IVA_Bias12_0833 = 3,
    HT16C22_IVA_Bias12_0789 = 4,
    HT16C22_IVA_Bias12_0750 = 5,
    HT16C22_IVA_Bias12_0714 = 6,
    HT16C22_IVA_Bias12_0682 = 7,
    HT16C22_IVA_Bias12_0652 = 8,
    HT16C22_IVA_Bias12_0625 = 9,
    HT16C22_IVA_Bias12_0600 = 10,
    HT16C22_IVA_Bias12_0577 = 11,
    HT16C22_IVA_Bias12_0556 = 12,
    HT16C22_IVA_Bias12_0536 = 13,
    HT16C22_IVA_Bias12_0517 = 14,
    HT16C22_IVA_Bias12_0500 = 15
} HT16C22_IVA;

typedef struct {
    HT16C22_Bias Bias: 1;
    HT16C22_WorkMode WorkMode: 2;
    HT16C22_FPS FPS: 1;
    HT16C22_SharePin SharePin: 2;
    HT16C22_IVA IVA: 4;
} HT16C22_InitTypeDef;

//Please Init I2C Before Use This Init Function
//Use 7Bit Address mode
//Return 0 Init Success Other Return are error
int HT16C22_Init(void *i2c_write_fc(uint8_t dev_addr, uint8_t *data, uint8_t size),
                 void *i2c_read_fc(uint8_t, uint8_t, uint8_t *, uint8_t),
                 HT16C22_InitTypeDef *HT16C22_InitTypeStruct);

//直接写入
int HT16C22_Write(uint8_t addr, const uint8_t *data, uint8_t size);

int HT16C22_All_Clear(void);

//函数写入模式，请调用Update函数更新屏幕

int HT16C22_Write_Bit(uint8_t COM, uint8_t SEG);

int HT16C22_Clear_Bit(uint8_t COM, uint8_t SEG);

int HT16C22_Update_Partial(void);

int HT16C22_Update_Global(void);

void HT16C22_Write_All(void);

//TODO 需要做读取?

//void i2c_write(uint8_t dev_addr, uint8_t dev_reg_addr, uint8_t *data, uint8_t size);
//void i2c_read(uint8_t dev_addr, uint8_t dev_reg_addr, uint8_t *data, uint8_t size);

