# esp-idf-ttp229
TTP229 Capacitive Touch Driver for esp-idf.

I ported from [here](https://github.com/arduino12/ttp229b-arduino).   

# Hardware requirements   
TTP229 Capacitive Touch switch.

![TTP229-1](https://user-images.githubusercontent.com/6020549/147397270-528ae5b6-ee00-49ac-8a9c-99e44d544ce1.JPG)

In order to use 16key, it is necessary to short TTP229 TP2.
![TTP229-2](https://user-images.githubusercontent.com/6020549/147397273-09b752ab-0a95-4e2c-8d36-345d37ac2ddb.JPG)


# Software requirements
esp-idf v4.4 or later.   
This is because this version supports ESP32-C3.   

# Installation for ESP32

```Shell
git clone https://github.com/nopnop2002/esp-idf-ttp229
cd esp-idf-ttp229
idf.py set-target esp32
idf.py menuconfig
idf.py flash
```

# Installation for ESP32-S2

```Shell
git clone https://github.com/nopnop2002/esp-idf-ttp229
cd esp-idf-ttp229
idf.py set-target esp32s2
idf.py menuconfig
idf.py flash
```

# Installation for ESP32-C3

```Shell
git clone https://github.com/nopnop2002/esp-idf-ttp229
cd esp-idf-ttp229
idf.py set-target esp32c3
idf.py menuconfig
idf.py flash
```


# Configuration   

![config-top](https://user-images.githubusercontent.com/6020549/147397305-0ce3e49a-64a9-49eb-9528-470562ebca64.jpg)

![config-ttp229](https://user-images.githubusercontent.com/6020549/147397307-7217bbbc-a97a-4712-a599-887ac2752938.jpg)


# Wirering

|TTP229||ESP32|ESP32-S2|ESP32-C3|
|:-:|:-:|:-:|:-:|:-:|
|SCL|--|GPIO4|GPIO17|GPIO7|
|SDA|--|GPIO5|GPIO18|GPIO8|
|GND|--|GND|GND|GND|
|VCC|--|3.3V|3.3V|3.3V|

__You can change it to any pin using menuconfig.__   


