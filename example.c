#include "HT16C22.h"
#include "i2c.h"

void I2C_Write(uint8_t Address, uint8_t *Data, uint8_t Length) {
    HAL_I2C_Master_Transmit(&hi2c1, Address, Data, Length, 100);
}

void DA2400_Display_Init(void) {
    HT16C22_InitTypeStruct = (HT16C22_InitTypeDef) {
            .Bias = HT16C22_Bias_13,
            .WorkMode = HT16C22_WorkMode_All_Work,
            .FPS = HT16C22_FPS_80,
            .SharePin = HT16C22_SharePin_SEG_IVA_ON,
            .IVA =HT16C22_IVA_Bias13_Full
    };
    HT16C22_Init((void *(*)(uint8_t, uint8_t *, uint8_t)) I2C_Write, NULL, &HT16C22_InitTypeStruct);
    HT16C22_Write_All();
    HT16C22_Update_Global();
//    HT16C22_All_Clear();
}