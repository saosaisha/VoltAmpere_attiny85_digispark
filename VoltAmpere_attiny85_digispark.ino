/* ---- Volt AmpereMeter Attiny85 Digispark ------
 *  ATtiny85 as an I2C Master   Ex2        BroHogan                           1/21/11
 * Modified for Digistump - Digispark LCD Shield by Erik Kettenburg 11/2012
 * SETUP:
 * ATtiny Pin 1 = PB5 =(RESET) N/U                      ATtiny Pin 2 = PB3 = (D3) N/U
 * ATtiny Pin 3 = PB4 =(D4) to LED1                     ATtiny Pin 4 =  GND
 * ATtiny Pin 5 = PB0 = SDA on DS1621  & GPIO           ATtiny Pin 6 = PB1 = (D1) to LED2
 * ATtiny Pin 7 = PB2 = SCK on DS1621  & GPIO           ATtiny Pin 8 = VCC (2.7-5.5V)
 * NOTE! - It's very important to use pullups on the SDA & SCL lines!
 * PCA8574A GPIO was used wired per instructions in "info" folder in the LiquidCrystal_I2C lib.
 * This ex assumes A0-A2 are set HIGH for an addeess of 0x3F
 * LiquidCrystal_I2C lib was modified for ATtiny - on Playground with TinyWireM lib.
 * TinyWireM USAGE & CREDITS: - see TinyWireM.h
 * https://www.youtube.com/c/Radal05/videos
 * revisi 03 Januari 2022
 * 
 */

//#define DEBUG
#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI - comment this out to use with standard arduinos
#include <LiquidCrystal_I2C.h>          // for LCD w/ GPIO MODIFIED for the ATtiny85
int hold,daya,dayaTotal,koma;
#define GPIO_ADDR     0x27             // (PCA8574A A0-A2 @5V) typ. A0-A3 Gnd 0x20 / 0x38 for A - 0x27 is the address of the Digispark LCD modules.


LiquidCrystal_I2C lcd(GPIO_ADDR,16,2);  // set address & 16 chars / 2 lines


void setup(){
  TinyWireM.begin();                    // initialize I2C lib - comment this out to use with standard arduinos
  lcd.init();                           // initialize the lcd 
  lcd.backlight();                      // Print a message to the LCD.
    
}


void loop(){
 int vin=(analogRead(A2));// Membaca data Analog
 /* ---set tegangan dan arus ---
  * Karena tegangan uc tidak sampai 5V
  * maka saya buat saja tegangan input maksimum
  * yang dapat dibaca sekitar 4,5V.
  * Dengan toleransi pembacaan 4,5/1023=4.4mV
  */
  float voltage = vin * (4.5/1023.0);
  /* Agar tegangan input terbaca sesuai
   * Bila menginginkan pembacaan maksimum 50V 
   * Maka pada input 50V diberi resistor pembagi tegangan
   * agar mendekati 50V...pembaginya 50/4,5=11.11 , kita buat 1:12
   * Kita misalkan pembagi tegangan Vinput---R120K--analogRead--Pot50K--Gnd
   * Atur Pot50K. sampai 4,5V dengan Vin maksimum (contoh disini 50V)
   * Agar pembacaan 1V terbaca 10V, maka voltage=voltage*10
   */
  voltage=voltage*10;
  /*----Baca Arus----
   * Karena menggunakan attiny85 Digispark
   * Maka tegangan di pin 2=PB3, maksimum sekitar 2,9V
   * Karena pengaruh Zener
   * Jadi
   * Misal menggunakan R shunt 0,01 ohm
   * maka bila mengalir arus 1A...terbaca 0,01V atau 10mV
   * maka arus=arus*15.3;
   * Bila menggunakan ACS712 20A
   * yang mempunyai spesifikasi 100mv/A
   * maka
   */
  int iin=(analogRead(A3));
  float arus = iin * (2.9/ 1023.0);
  arus=arus*15.6;
 
 /*
  * Mwnghitubg Daya P=VxI
  */
  float daya=voltage*arus*arus;
  
  lcd.setCursor(0,0);
  lcd.print(" ");
  lcd.print(voltage);
  lcd.print("V  ");
  
  lcd.print(arus);
  lcd.print("A   ");

  lcd.setCursor(0,1);
  lcd.print("");
  lcd.print(daya);
  lcd.print("W  Radal05  ");
  

 /* 
  
  if (digitalRead(8)==0){
    hold=1;
    lcd.setCursor(0,1);
    lcd.print("hold on");
    delay(1000);
    do{
      if (digitalRead(8)==0){
        lcd.setCursor(0,1);
        lcd.print("          ");
        delay(1000);
        hold=0;
      }
    }
    while(hold);
  }
  *  
  */
  delay(500);

}
