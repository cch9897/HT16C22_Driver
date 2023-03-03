//
// Created by cch on 2023/3/2.
//

#include "HT16C22.h"

uint8_t Display_RAM[22] = {0};

void (*i2c_write)(uint8_t dev_addr, uint8_t *data, uint8_t size);

void (*i2c_read)(uint8_t, uint8_t, uint8_t *, uint8_t);

int HT16C22_Init(void *i2c_write_fc(uint8_t dev_addr, uint8_t *data, uint8_t size),
                 void *i2c_read_fc(uint8_t, uint8_t, uint8_t *, uint8_t),
                 HT16C22_InitTypeDef *HT16C22_InitTypeStruct) {
    i2c_write = (void (*)(uint8_t, uint8_t *, uint8_t)) i2c_write_fc;
    i2c_read = (void (*)(uint8_t, uint8_t, uint8_t *, uint8_t)) i2c_read_fc;
    uint8_t HT16C22_Driver_Mode;
    HT16C22_Driver_Mode = HT16C22_InitTypeStruct->Bias;
    HT16C22_Driver_Mode |= (HT16C22_InitTypeStruct->WorkMode < 2);
    HT16C22_Driver_Mode |= (HT16C22_InitTypeStruct->FPS < 4);
    HT16C22_Driver_Mode |= (0x1 << 7);
    //写驱动模式指令的头3位为100
    //完整写驱动模式的指令为100 XXX 1X

    uint8_t HT16C22_IVA_Mode = 0x40;
    HT16C22_IVA_Mode |= HT16C22_InitTypeStruct->SharePin << 4;
    HT16C22_IVA_Mode |= HT16C22_InitTypeStruct->IVA;
    //写IVA头两位为01
    //完整指令为 01 XX XXXX


    i2c_write(HT16C22_I2C_Addr, &HT16C22_Driver_Mode, 1);
    i2c_write(HT16C22_I2C_Addr, &HT16C22_IVA_Mode, 1);

    //TODO 异常抛出

    return 0;
}

int HT16C22_Write(uint8_t addr, const uint8_t *data, uint8_t size) {
    uint8_t display_data[size + 1];
    for (int i = 0; i < size; ++i) {
        display_data[i + 1] = data[i];
    }
    display_data[0] = 0x1f & addr;
    i2c_write(HT16C22_I2C_Addr, display_data, size + 1);
    return 0;
}

int HT16C22_Clear() {
    uint8_t clear_data[23] = {0};
    i2c_write(HT16C22_I2C_Addr, clear_data, 23);
    return 0;
}

int HT16C22_Write_Bit(uint8_t COM, uint8_t SEG) {
    if (SEG % 2 == 0) {
        //右侧
        Display_RAM[SEG / 2] |= 1 << COM;
    } else {
        //左侧
        Display_RAM[SEG / 2] |= 1 << COM << 4;
    }
    return 0;
}

int HT16C22_Clear_Bit(uint8_t COM, uint8_t SEG) {
    if (SEG % 2 == 0) {
        //右侧
        Display_RAM[SEG / 2] &= (0xff ^ (0x1 << COM));
    } else {
        //左侧
        Display_RAM[SEG / 2] &= (0xff ^ (0x1 << COM << 4));
    }
    return 0;
}

int HT16C22_Update(void) {
    HT16C22_Write(0x0, Display_RAM, 22);
    return 0;
}


