import serial
import pyttsx3
import time
# Initialize serial communication with the Arduino
serial_port = 'COM6'  # Update this with your actual COM port
baud_rate = 9600
ser = serial.Serial(serial_port, baud_rate, timeout=1)
# Initialize text-to-speech engine
engine = pyttsx3.init()
# Read and vocalize each line from the serial output
try:
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()  # Read and decode the line
            if line:  # Check if the line is not empty
                print(f"Received: {line}")
                engine.say(line)  # Vocalize the received text
                engine.runAndWait()  # Process the speech output

except KeyboardInterrupt:
    print("Program stopped.")
finally:
    ser.close()
