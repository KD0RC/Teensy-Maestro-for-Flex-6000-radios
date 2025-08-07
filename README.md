# Teensy-Maestro-for-Flex-6000-radios
The TeensyMaestro is a Teensy (Arduino work-alike) based set of controls for the FlexRadio 6000, 8000 and Aurora series.  It provides knobs, buttons, display and a keyer.  It is designed to augment SmartSDR (SSDR), not replace it.  There are many functions that the TeensyMaestro cannot perform that still need to be done using SSDR or a real Maestro.
The TeensyMaestro uses a USB cable for power and an ethernet cable to connect with the radio.  All communication with the radio is via TCP/IP, not the USB cable.
The primary design goal was to provide the most used controls in the form of knobs and buttons while retaining all the power and convenience of the computer-based SSDR.  It uses the extensive TCP/IP Application Programming Interface (API) provided by FlexRadio.  It also leverages the Flex Arduino library built by Enzo, IW7DMH.  Without this library, the TeensyMaestro would not have been built.
While the TeensyMaestro has a color touch screen, it does not display a panadapter or waterfall.  It does show basic slice information in a similar way as the “flag” does in SSDR.  The touch screen is a rudimentary resistive type, so it does not have cell phone like capabilities but provides some simple functions.  There are no functions that rely solely on the touch screen; the physical controls cover all touch screen functions.  

August 2025 - Version 2 of the software is available!  It continues to support the original hardware (HW V1) using the HX8357 display and discrete address-line multiplexers.  It now also supports the PC board designed by Simon, NV0E (HW V2) using the ST7796S display and MCP 23008 and 23016 I2C addressed multiplexers.  You can build V2 hardware with point-to-point wiring or using Sinom's board.  V2 will be significantly cheaper and give you a slightly larger display.  Operationally, they are indistinguishable.  At least for now, there will be two load images available, one for V1 hardware and one for V2.  There will continue to be one source code file using compiler directives to generate V1 or V2.

Using the Teensy.exe Loader to program the Teensy board

1. Make sure the Teensy 4.1 is plugged in to a USB port
2. Download the appropriate .hex file for the hardware that you have
3. Download Teensy.exe if it is not already on your computer
4. Run Teensy.exe
5. Click File, Open HEX File
6. Navigate to the file saved in step 2 and select it
7. Click the Program button on the Teensy board to start the download

![Image text](https://github.com/KD0RC/Teensy-Maestro-for-Flex-6000-radios/blob/master/images/TeensyMaestro.JPG)
![Image text](https://github.com/KD0RC/Teensy-Maestro-for-Flex-6000-radios/blob/master/images/IMG_20201115_213850789_HDR.jpg)
