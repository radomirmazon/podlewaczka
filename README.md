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

User Guide:

* One click button - enter to manual mode (all LEDs blinking every secend), and start first Executor. Executors switch on one by one like normal auto mode. Every click on button, switch next executon on.

* Long click button to LEDs blink once - enter to auto mode. All LEDs are off. Device running auto mode algorithm.

* Long click button to LEDs blink twice - LEDs show you level of how long Executor will be on. One LED means 5 min (you can set 5 to 40 min witch 5min steps). To exit in this mode, do nothing. After 3 seconds device automaticaly back.

- LEDs - all dead - that is auto mode.
- LEDs - blinking every seconds - that is manual mode.


Commands via Serial:

* A - go to auto mode
* M - go to manual mode
* N - run next executor (switch to manual mode)
* E0 - switch on executor 0 (executor switch on independently and automaticaly off after normal time to run).

(...)  

E7 - switch on executor 7

* E8 - switch off all
* P0 - set pr value to 1, atomic execution time 1*5min

(...)

P7 - set pr value to 8, atomic execution time 8*5min


* R0 - enabled runWith for Executor 0

(...)

R7 - enabled runWith for Executor 7

* T0 - disable runWith for Executor 0

(...)

T7 - disable runWith for Executor 7

* D123 - secondAfterDark (max 24h) [in seconds]
* G123 - rainForget (max 48h) [in seconds]
* T123 - rainTreshold (max 8h) [in seconds]




todo:

F050 - Fill Executor 0 to 50% atomic execution time 



info:

Time execution = cycle * fill * pr
