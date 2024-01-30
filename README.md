# NXP Application Code Hub
[<img src="https://mcuxpresso.nxp.com/static/icon/nxp-logo-color.svg" width="100"/>](https://www.nxp.com)

## Vital Health Signal Monitor with display in MCXN9
*The demo emulates a vital sign monitor, uses a pulse-oximeter sensor that take the Spo2 value and the BPM.*

*The demo uses the LVGL graphics framework and use an LCD with a resolution of 480x320. In the display we can see the graphic of the values and the measure of the BPM value and the Spo2%.*





#### Boards: FRDM-MCXN947
#### Categories: Graphics, HMI, Sensor
#### Peripherals: DISPLAY, DMA, I2C
#### Toolchains: MCUXpresso IDE

## Table of Contents
1. [Software](#step1)
2. [Hardware](#step2)
3. [Setup](#step3)
4. [Results](#step4)
5. [FAQs](#step5) 
6. [Support](#step6)
7. [Release Notes](#step7)

## 1. Software<a name="step1"></a>
*This software was developed in MCUXpresso IDE, this demo is in baremetal but have integrated the LVGL graphics library that uses an internal rtos to manage the LCD image and the Touch, for the heart rate sensor we have an interuption that sample the signal every 20us, the sensor library make a filtration of the values and return a graphable value, after that we take the values and we use it to display de graphic. The application start when the user put the finger in the sensor, after that you can see a message in the display that indicate that the measurment start, afert a few seconds the graph appear. https://nxp.com/mcuxpresso.*

## 2. Hardware<a name="step2"></a>
*For this demo you will need the next hardware.*

- [MCX N9 FRD Boad.](https://nxp.com/FRDM-MCXN947.com)
![Alt text](images/frmBoard.png)
- [Low Cost NXP LCD.](https://nxp.com/nxp.com/LCD-PAR-S035.com) 
![Alt text](images/lowcost.png)
- [MicroE PulseOximeter Sensor.](https://www.mikroe.com/heart-rate-4-click) 
![Alt text](images/sensor.png)

## 3. Setup<a name="step3"></a>

### 3.1 Step 1 

*For the LCD Conection first you need to check the SW1 in the LCD the position of the switch should be 010 (16bits 8080) the next step is plugging the LCD in the board (use the next image like reference) you should connect the LCD in the J8 header with two pins free in the top of the header.*

![Alt text](images/freePINS.png)

### 3.2 Step 2 
*For the sensor you need to connect it in the MicroE header like the next image.*

![Alt text](images/sensorconected.png)
### 3.3 Step 3
*After cloning the repository and importing it to the workspace connect the board to the pc using a USB cable in the J17 header.*

*Use the button debug to build and compile the project, select the target and push play to run the application.*
![Alt text](images/MCUXpresso.png)

## 4. Results<a name="step4"></a>
*To start a measure you need to put your finger in the sensor and a warning mensage will appear in the LCD, after a few seconds the measure calibrations ends and the values are showed in the LCD.*
![Alt text](images/test.png)
## 6. Support<a name="step6"></a>

#### Project Metadata
<!----- Boards ----->
[![Board badge](https://img.shields.io/badge/Board-FRDM&ndash;MCXN947-blue)](https://github.com/search?q=org%3Anxp-appcodehub+FRDM-MCXN947+in%3Areadme&type=Repositories)

<!----- Categories ----->
[![Category badge](https://img.shields.io/badge/Category-GRAPHICS-yellowgreen)](https://github.com/search?q=org%3Anxp-appcodehub+graphics+in%3Areadme&type=Repositories) [![Category badge](https://img.shields.io/badge/Category-HMI-yellowgreen)](https://github.com/search?q=org%3Anxp-appcodehub+hmi+in%3Areadme&type=Repositories) [![Category badge](https://img.shields.io/badge/Category-SENSOR-yellowgreen)](https://github.com/search?q=org%3Anxp-appcodehub+sensor+in%3Areadme&type=Repositories)

<!----- Peripherals ----->
[![Peripheral badge](https://img.shields.io/badge/Peripheral-DISPLAY-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+display+in%3Areadme&type=Repositories) [![Peripheral badge](https://img.shields.io/badge/Peripheral-DMA-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+dma+in%3Areadme&type=Repositories) [![Peripheral badge](https://img.shields.io/badge/Peripheral-I2C-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+i2c+in%3Areadme&type=Repositories)

<!----- Toolchains ----->
[![Toolchain badge](https://img.shields.io/badge/Toolchain-MCUXPRESSO%20IDE-orange)](https://github.com/search?q=org%3Anxp-appcodehub+mcux+in%3Areadme&type=Repositories)

Questions regarding the content/correctness of this example can be entered as Issues within this GitHub repository.

>**Warning**: For more general technical questions regarding NXP Microcontrollers and the difference in expected funcionality, enter your questions on the [NXP Community Forum](https://community.nxp.com/)

[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/@NXP_Semiconductors)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/nxp-semiconductors)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/nxpsemi/)
[![Follow us on Twitter](https://img.shields.io/badge/Twitter-Follow%20us%20on%20Twitter-white.svg)](https://twitter.com/NXP)

## 7. Release Notes<a name="step7"></a>
| Version | Description / Update                           | Date                        |
|:-------:|------------------------------------------------|----------------------------:|
| 1.0     | Initial release on Application Code Hub        | January 4<sup>th</sup> 2024 |

