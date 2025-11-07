/* 
 * File:   lcd.h
 * Author: user
 *
 * Created on 2025. studenoga 07, 10:00
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000UL
#endif

#define LCD_RS PORTBbits.RB6
#define LCD_EN PORTBbits.RB1
#define LCD_D4 PORTBbits.RB2
#define LCD_D5 PORTBbits.RB3
#define LCD_D6 PORTBbits.RB4
#define LCD_D7 PORTBbits.RB5
    
#define LCD_RS_TRIS TRISBbits.TRISB6
#define LCD_EN_TRIS TRISBbits.TRISB1
#define LCD_D4_TRIS TRISBbits.TRISB2
#define LCD_D5_TRIS TRISBbits.TRISB3
#define LCD_D6_TRIS TRISBbits.TRISB4
#define LCD_D7_TRIS TRISBbits.TRISB5
 
void lcd_init(void); //incijijalizacija lcd-a
    
void lcd_clear(void); //brisanje sadrzaja sa lcd-a
    
void lcd_cmd(uint8_t cmd); //slanje naredbe lcd-u, display on, cursor off..

void lcd_char(char c); //slanje jednog znaka

void lcd_string(const char *s); //slanje stringa do \0

void lcd_setCursor(uint8_t row, uint8_t col); //postavljanje cursora na odredeni row ili col
#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

