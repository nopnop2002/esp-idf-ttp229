# esp-idf-ttp229
TTP229 Capacitive Touch Driver for esp-idf.

I ported from [here](https://github.com/arduino12/ttp229b-arduino).   

# Software requirements
ESP-IDF V5.0 or later.   
ESP-IDF V4.4 release branch reached EOL in July 2024.   

# Hardware requirements   
TTP229 Capacitive Touch switch.

![TTP229-1](https://user-images.githubusercontent.com/6020549/147397270-528ae5b6-ee00-49ac-8a9c-99e44d544ce1.JPG)

The TTP229 has 8 keys input mode and 16 keys input mode.   
These modes are selected via high-value resistor connected to the TP2(KYSEL) pin to VSS, or not.   
In order to use 16 keys, it is necessary to short TTP229 TP2.   
![TTP229-2](https://user-images.githubusercontent.com/6020549/147397273-09b752ab-0a95-4e2c-8d36-345d37ac2ddb.JPG)

# Installation

```Shell
git clone https://github.com/nopnop2002/esp-idf-ttp229
cd esp-idf-ttp229
idf.py menuconfig
idf.py flash
```

# Configuration   
![config-top](https://user-images.githubusercontent.com/6020549/147397305-0ce3e49a-64a9-49eb-9528-470562ebca64.jpg)
![config-ttp229](https://user-images.githubusercontent.com/6020549/147397307-7217bbbc-a97a-4712-a599-887ac2752938.jpg)

# Wiring

|TTP229||ESP32|ESP32-S2/S3|ESP32-Cx/Hx|
|:-:|:-:|:-:|:-:|:-:|
|SCL|--|GPIO4|GPIO17|GPIO0|
|SDA|--|GPIO5|GPIO18|GPIO1|
|GND|--|GND|GND|GND|
|VCC|--|3.3V|3.3V|3.3V|

__You can change it to any pin using menuconfig.__   

__The markings on the board are SCL and SDA, but not the i2c interface.__   

# Screen Shot   
![TTP229-3](https://user-images.githubusercontent.com/6020549/147401025-867f5b12-f2e4-4268-9a5f-30dcd786020b.jpg)

# How to use this component in your project   
Create idf_component.yml in the same directory as main.c.   
```
YourProject --+-- CMakeLists.txt
              +-- main --+-- main.c
                         +-- CMakeLists.txt
                         +-- idf_component.yml
```

Contents of idf_component.yml.
```
dependencies:
  nopnop2002/ttp229:
    path: components/ttp229
    git: https://github.com/nopnop2002/esp-idf-ttp229.git
```

When you build a projects esp-idf will automaticly fetch repository to managed_components dir and link with your code.   
```
YourProject --+-- CMakeLists.txt
              +-- main --+-- main.c
              |          +-- CMakeLists.txt
              |          +-- idf_component.yml
              +-- managed_components ----- nopnop2002__ttp229
```

# Reference   
https://github.com/nopnop2002/esp-idf-mpr121
