/* 
 * File:   lcd.c
 * Author: user
 *
 * Created on 2025. studenoga 07, 12:32
 */

#include "lcd.h"
#include <stdint.h>
/*
 * 
 */
static void lcd_pulseEnable(void){
    LCD_EN = 1;
    __delay_us(1);
    LCD_EN = 0;
    __delay_us(50);
}

static void lcd_send4bits(uint8_t nibble){
    LCD_D4 = (nibble >> 0) & 1;
    LCD_D5 = (nibble >> 1) & 1;
    LCD_D6 = (nibble >> 2) & 1;
    LCD_D7 = (nibble >> 3) & 1;
    lcd_pulseEnable();
}

static void lcd_write(uint8_t value, uint8_t rs){
    LCD_RS = rs ? 1 : 0;
    lcd_send4bits(value >> 4);
    lcd_send4bits(value & 0x0F);
    
    if(!rs && (value == 0x01 ||value == 0x02)){
        __delay_ms(2);
    } else {
        __delay_us(50);
    }
}

void lcd_cmd(uint8_t cmd){
    lcd_write(cmd, 0);
}

void lcd_char(char c){
    lcd_write((uint8_t)c, 1);
}

void lcd_string(const char *s){
    while(*s) lcd_char(*s++);
}

void lcd_clear(void){
    lcd_cmd(0x01);
}

void lcd_setCursor(uint8_t row, uint8_t col){ //row 0-3, col 0-19, radi i za 16x2
    static const uint8_t row_addr[] = {0x00, 0x40, 0x14, 0x54};
    
    if(row > 3) row = 3;
    
    uint8_t addr = row_addr[row] + col;
    lcd_cmd(0x80 | addr);
}

void lcd_init(void){
    LCD_RS_TRIS = 0;
    LCD_EN_TRIS = 0;
    LCD_D4_TRIS = 0;
    LCD_D5_TRIS = 0;
    LCD_D6_TRIS = 0;
    LCD_D7_TRIS = 0;
    
    LCD_RS = 0;
    LCD_EN = 0;
    LCD_D4 = 0;
    LCD_D5 = 0;
    LCD_D6 = 0;
    LCD_D7 = 0;
    
    __delay_ms(20);
    //sekvenca za 4-bit mode
    lcd_send4bits(0x03); __delay_ms(5);
    lcd_send4bits(0x03); __delay_us(150);
    lcd_send4bits(0x03); __delay_us(150);
    lcd_send4bits(0x02); __delay_us(150);
    
    lcd_cmd(0x28); //2 linije, 4 bit
    lcd_cmd(0x0C); //display ON, cursor OFF
    lcd_cmd(0x01); //clear display
    lcd_cmd(0x06); //autoinkrement
}
