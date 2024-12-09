#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int lcd_Columns = 16; // Number of columns in display
int lcd_Rows = 2;     // Number of Rows in display

LiquidCrystal_I2C lcd(0x27, lcd_Columns, lcd_Rows); // set the LCD address and number of Rows and Columns

String text = "Sayandip Bera";  // Put your required Text here
int speed_Adjust = 300;   // Speed of moving Text
int rest_Time = 400;      // Resting time of Text animation at the edges of display

int text_Len;             // Variable to save text length

void setup()
{
  lcd.init();                      // initialize the lcd
  lcd.backlight();                 // Turn on the LCD backlight
  lcd.clear();                     // Clear the display

  text_Len = text.length(); // Finding the number of characters in the Text
}

void bounceAnimation() {
  for (int j = 0; j < lcd_Rows; j++) {
    for (int i = 0; i < (lcd_Columns - text_Len + 1); i++) {
      lcd.clear();
      lcd.setCursor(i, j);
      lcd.print(text);
      delay(speed_Adjust);
    }

    for (int i = (lcd_Columns - text_Len); i >= 0; i--) {
      lcd.clear();
      lcd.setCursor(i, j);
      lcd.print(text);
      delay(speed_Adjust);
    }
  }
}

void zigzagAnimation() {
  for (int i = 0; i < (lcd_Columns - text_Len + 1); i++) {
    for (int j = 0; j < lcd_Rows; j++) {
      lcd.clear();
      lcd.setCursor(i, j);
      lcd.print(text);
      delay(speed_Adjust);
      if (j < lcd_Rows - 1) {
        lcd.clear();
      }
    }
  }

  for (int i = (lcd_Columns - text_Len); i >= 0; i--) {
    for (int j = lcd_Rows - 1; j >= 0; j--) {
      lcd.clear();
      lcd.setCursor(i, j);
      lcd.print(text);
      delay(speed_Adjust);
      if (j > 0) {
        lcd.clear();
      }
    }
  }
}

void scrollingAnimation() {
  for (int i = 0; i < text_Len + lcd_Columns; i++) {
    lcd.clear();
    int start = i - lcd_Columns + 1;
    if (start < 0) start = 0;
    lcd.setCursor(0, 0);
    lcd.print(text.substring(start, start + lcd_Columns));
    delay(speed_Adjust);
  }

  delay(rest_Time);
}

void loop() {
  bounceAnimation();
  delay(rest_Time);
  zigzagAnimation();
  delay(rest_Time);
  scrollingAnimation();
  delay(rest_Time);
}