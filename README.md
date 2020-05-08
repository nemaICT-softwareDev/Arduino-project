# Sensor Readings (Arduino IDE)

This is a simple project aim for testing purpose, using MQTT technologie.

For this project I use the D1 Mini WIFI Internet Of Things Development Board Based ESP8266 4MB, a Mini IR Pyroelectric Infrared PIR Motion Human Body Sensor Detector Module and two leds, a green and a red one.
- the Mini IR Pyroelectric Infrared PIR motion sensor is connected at port D7
- the red led is connected to port D0 and will light every 60 seconds while senting signal to the broker
- the green one is connected to port D5 and will sent signal to the broker every time the mini IR Pyroelectric Infrared PIR motion sensor sense motion with close distance.
