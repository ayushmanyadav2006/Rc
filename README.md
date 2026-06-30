Prototype project
Remote controlled car with a range of 1km (NRF24L01 with external antenna). 
It has a temperature sensor (DHT 11) and smoke sensors (MQ-2). 
If ESP32 is used instead of Arduino UNO it can transmit data of temperature, humidity and smoke via IoT to consoles like Blynk. 
It can be used where multiple locations temperature/humidity and smoke levels needs to be monitored. 

Problem Solved: No need to install sensors at every location. 
And fetching data of each individually. 
Instead send a mobile object (drone, etc) which can go to multiple locations and fetch data, which can be easily observed on IoT consoles like Blynk. 

Currently the project lacks the IoT part, rest everything is complete. 
The only upgrade required is an ESP32 which has both wifi and bluetooth modules. 
Currently used is Arduino UNO which lacks these modules.

Working video link: https://www.youtube.com/watch?v=tiGqe8D3GXA
