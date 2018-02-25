#ifndef _LCD_H_
#define _LCD_H_
void LCD_cmd(char cmd);
void LCD_Init(void);
void LCD_char(char ch);
void LCD_str(char *ptr);
void LCD_int(signed int);
void Store_CGRAM(void);

#endif
