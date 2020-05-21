# Sensor Readings (Arduino IDE)

### This is a simple project aim for testing purpose, using MQTT technologie.

#### For this project I use a D1 Mini WIFI IoT Development Board Based ESP8266 4MB, a Mini IR Pyroelectric Infrared PIR Motion Human Body Sensor Detector Module, 3x Jumper wires, 3x 220R resistor's, 3x Female-to-male Dupont Wire and 2x leds.
- the Mini IR Pyroelectric Infrared PIR motion sensor is connected to port D7
- the red led is connected to port D0 and will light every 60 seconds while senting signal to the broker
- the green one is connected to port D5 and will sent signal to the broker every time the PIR motion sensor senses motion with close distance.
