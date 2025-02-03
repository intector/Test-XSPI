# XSPI example for the STM32H7R3L8H6H MCU
This project is an example of using external memory on the XSPI interface of an STM32H7R3L8H6H MCU. It was created using the STM32CubeIDE with only minimal code manipulations afterward. The following hardware is used in this example:

* **STM32H7R3L8H6H**
	* *MCU High-performance & DSP DP-FPU Arm Cortex-M7 MCU 64KB Flash 620KB SRAM 550MHz CPU*
* **MX25UW25645GXDI00**
	* *NOR Flash Serial NOR 1.8V 256Mbit x8 I/O BGA-24 RWW*
* **APS256XXN-OBR-BG**
	* *DRAM IoT RAM 256Mb OPI (x8,x16) DDR 200MHz, 1.8V, Ind. Temp., BGA24*

The schematics are in [doc](/../../tree/main/doc).

I made a board with this memory layout that I needed for one of my projects. I ran into several issues with the memory configuration and learned that working examples don't exist. However, I got inspiration and support from the STM32 Community, an excellent source of help. I probably would not have been able to find a solution without those guys.

This example is free for anyone to use for whatever they need it for. Unfortunately, I can't take any responsibility for anything that happens while using this software. 


Guys, stay tired and never forget:
> "Always be yourself unless you can be a pirate. Then always be a pirate."
