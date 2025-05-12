# Temperature Controlled Laptop Fan using ESP32-S3-Mini
 
A simple Arduino project that uses a temperature sensor to control two fans to help cool down a laptop on a laptop stand. Power is supplied by any 5V source and a mosfet switch is used to switch the fans on/off based on the current temperature under the laptop. I was able to see the fans reduce the temparate under the laptop from 32.8 – 30.8*C within 2 minutes. If the fans don't need to be on, the device will switch them off and go into deep sleep for 10 seconds, then check the tempeature again.


Hardware:
 - ESP32-C3 Super Mini
 - SHT31 temperature sensor
 - N-Channel Mosfet (16A 60V TO-220)
 - 5V 0.2Amp Cooler Fans (30 x 30 x 7mm)
 - 220 Ohm Resistor

--------------------------------

![Components](https://github.com/ClaudeMarais/TempControlledLaptopFan_ESP32-S3-Mini/blob/main/Images/Components.jpg?raw=true)

![WireDiagram](https://github.com/ClaudeMarais/TempControlledLaptopFan_ESP32-S3-Mini/blob/main/Images/WireDiagram.jpg?raw=true)

![Components2](https://github.com/ClaudeMarais/TempControlledLaptopFan_ESP32-S3-Mini/blob/main/Images/Components2.jpg?raw=true)

![Installed](https://github.com/ClaudeMarais/TempControlledLaptopFan_ESP32-S3-Mini/blob/main/Images/Installed.jpg?raw=true)

![Design1](https://github.com/ClaudeMarais/TempControlledLaptopFan_ESP32-S3-Mini/blob/main/Images/Design1.jpg?raw=true)

![Design2](https://github.com/ClaudeMarais/TempControlledLaptopFan_ESP32-S3-Mini/blob/main/Images/Design2.jpg?raw=true)
