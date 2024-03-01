//ID Program
/* Aghniya Qinthara Rahmah Suherman
 * NIM : 191311033
 * Selasa, 06 Juli 2021
 * Prodi D-III Teknik Elektronika 
 * Politeknik Negeri Bandung
 * Mata Kuliah Sistem Kendali Lanjut
 * Program Pengujian LCD
*/
//-------------------------------- -------------------------------------\\

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//Library LCD I2C
LiquidCrystal_I2C lcd (0x27,16,2);

void setup() {
  lcd.init();
  lcd.init();
  
  // Turn on the backlight and print a message.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print ("Aghniya Qinthara");
  lcd.setCursor(0,1);
  lcd.print ("191311033");
}

void loop() {
}
