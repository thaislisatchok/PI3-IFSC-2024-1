# test of hx711 

from hx711 import HX711 # Importing HX711 class from hx711 module


# Define the data pin (DT) and serial clock pin (SCK) for the HX711
DATA_PIN = 2  # Pin connected to DT
SCK_PIN = 4   # Pin connected to SCK

# Create an instance of the HX711 object
hx = HX711(DATA_PIN, SCK_PIN)
hx.set_scale(10)  # Set the scale
xvar = 0  # Initialize variable to store the known tare weight

# Main function
while True:
    hx.tare() # Request known tare weight
    read=hx.read() #Read raw data
    average=hx.read_average() # Read the weight avarege 
    value=hx.make_average() # Read the weight avarege another way with division 
    
    if xvar == 0:  # If tare weight is not yet stored
        xvar = value  # Store the tare weight
    
    output = float(value) - float(xvar)  # Calculate net weight
    
    print('loop raw: ', read) # Print the raw version 
    print('loop x samples: ', average) # Print the avarege of x samples
    print('kg: ', value, '->', output) # Print weight in kilograms
    print('---------------')

