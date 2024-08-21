#Test LCD

# Importing necessary modules for the LCD test
import machine # Importing the machine module for hardware control
from machine import Pin, SoftI2C # Importing specific classes and functions from machine module
from lcd_api import LcdApi # Importing LCD API for LCD display control
from i2c_lcd import I2cLcd # Importing I2C LCD module for I2C communication with the LCD
from time import sleep # Importing the sleep function from time module for time delays

# I2C address of the LCD
I2C_ADDR = 0x27

# Total number of rows and columns of the LCD
totalRows = 2
totalColumns = 16

# Initialize I2C method for ESP32
i2c = SoftI2C(scl=Pin(22), sda=Pin(21), freq=10000)  # Initializing the I2C method for ESP32

# Initialize LCD object
lcd = I2cLcd(i2c, I2C_ADDR, totalRows, totalColumns)

# Continuous loop for LCD testing
while True:
    lcd.putstr("SUZUKI e ERIC")  # Displaying a string on the LCD
    sleep(2)  # Pause for 2 seconds
    lcd.move_to(1,1)  # Moving cursor to a specific position on the LCD
    lcd.putstr("Lets Count 0-10")  # Displaying a string on the LCD
    sleep(2)  # Pause for 2 seconds
    lcd.clear()  # Clearing the LCD
    for i in range(11):  # Loop from 0 to 10
        lcd.putstr(str(i))  # Displaying the current number on the LCD
        sleep(1)  # Pause for 1 second
        lcd.clear()  # Clearing the LCD for the next number
