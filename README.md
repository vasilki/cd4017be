# stm_cd4017be
Connecting cd4017be to the Nucleo F401RE and migration libraries to HAL\Cubemx
GND = GND
VCC = +5V
MR = +5V (do not use reset)
OE = GND

PINOUT:
PC10-CN7.1 - DS
PC11-CN7.2 - STCP
PC12-CN7.3 - SHCP
Q0-Q3 - LED

Manuals was taken from the following webpages:
  STM32:https://www.rlocman.ru/shem/schematics.html?di=65110

Environment:
STM32 NUCLEO-F401RE
Linux Mint 18.2 Sonya
STM32Cube_1.0 version 4.24.0.Repository is STM32Cube_FW_F4_V1.21.0.
System Workbench for STM32 Version: Neon.3 Release (4.6.3) Build id: 20170314-1500
