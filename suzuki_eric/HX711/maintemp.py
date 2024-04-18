# Import necessary modules
from machine import Pin, SoftI2C  # Importing Pin and SoftI2C modules from machine
from lcd_api import LcdApi  # Importing LcdApi module from lcd_api
from i2c_lcd import I2cLcd  # Importing I2cLcd module from i2c_lcd
from time import sleep  # Importing sleep function from time module
from hx711 import HX711  # Importing HX711 class from hx711 module

# I2C address of the LCD
I2C_ADDR = 0x27

# Total number of rows and columns of the LCD
totalRows = 2
totalColumns = 16

# Initialize I2C method for ESP32
i2c = SoftI2C(scl=Pin(22), sda=Pin(21), freq=10000)

# Initialize LCD object
lcd = I2cLcd(i2c, I2C_ADDR, totalRows, totalColumns)

# Define the data pin (DT) and serial clock pin (SCK) for the HX711
DATA_PIN = 2  # Pin connected to DT
SCK_PIN = 4   # Pin connected to SCK

# Create an instance of the HX711 object
hx = HX711(DATA_PIN, SCK_PIN)
hx.set_scale(10)  # Set the scale
xvar = 0  # Initialize variable to store the known tare weight

# Continuous loop for weight reading and display
while True:
    hx.tare()  # Request known tare weight
    value = hx.make_average()  # Read the weight

    if xvar == 0:  # If tare weight is not yet stored
        xvar = value  # Store the tare weight

    output = float(value) - float(xvar)  # Calculate net weight
    print('kg: ', value, '->', output)  # Print weight in kilograms

    # Format text to display on LCD
    linha_superior = "SUZUKI  ERIC"
    linha_inferior = "Peso: %.2f g" % output

    # Clear LCD and write lines
    lcd.clear()
    lcd.putstr(linha_superior)
    lcd.move_to(0, 1)
    lcd.putstr(linha_inferior)

    sleep(1)  # Wait before the next reading and LCD update

