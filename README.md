# podlewaczka
![block schemat](https://raw.githubusercontent.com/radomirmazon/podlewaczka/master/podlewaczka_block_schema.PNG)
Potentiometer - was cut off from device.

features:
* 8 channels on/off executors 
* The choice to be which one is enabled or disabled.
* Working time from 5 minute to ... n*80 min per one executor. with 5 min step.
* Reduce the execution time in percent. (per executor).
* Merge one or more executors together.
* Full controll and configure by serial port.
* Automatic startup.
* Rain detection.
* Full diagnostic by serial port.


Commands via Serial:

A - go to auto mode

M - go to manual mode

N - run next executor (switch to manual mode)

E0 - switch on executor 0 (executor switch on independently and automaticaly off after normal time to run).

(...)  

E7 - switch on executor 7

E8 - switch off all

