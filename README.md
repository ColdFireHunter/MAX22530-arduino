# MAX22530-Arduino
Arduino libary for MAX22530
Please use the datasheet for additional reference to the different registers
https://www.analog.com/en/products/max22530.html

Please see usage examples! 

Documentation of functions:

```C++
MAX22530 example_name (10);
```
This is the class constructor you can give it any name you want in this case example_name, it also needs the CS (chip select) pin of the device, here the standard SPI bus is used.

```C++
MAX22530 example_name (10,&SPI);
```
This is the class constructor you can give it any name you want in this case example_name, it also needs the CS (chip select) pin of the device, in this case, you also pass a different SPI Class for another SPI bus (for example with stm32duino https://github.com/stm32duino/Arduino_Core_STM32/wiki/API#spi) 

```C++
bool begin(int frequency);
```
Start the communication with the max22530 with the specified frequency **max 10 MHz**. The function accepts input in hertz so 1MHz is 1000000 Hz.
Returns if the operation was successful.

```C++
readADC(int channel);
```
Reads the channel (0-3) and returns the count 0-4096 as uint16_t if value -1 read was not successful.

```C++
readFiltered(int channel);
```
Reads the filtered channel (0-3) and returns the count 0-4096 as uint16_t if value -1 read was not successful.

```C++
CNVTVoltage(int count);
```
Converts the input count to a voltage, returns a float

```C++
setComp(int channel, uint16_t up_value, uint16_t down_value, bool source, bool mode);
```
Sets the comparator for the selected channel, with the upper threshold (0-4096) and the lower threshold (0-4096), the source (0 -> unfiltered 1-> filtered), and the mode (0 -> digital status mode 1-> digital input mode).
**DIGITAL INPUT MODE**
![image](https://github.com/ColdFireHunter/MAX22530-arduino/assets/53087752/218aa9f1-d2db-43de-9b6a-e16135969a97)
**DIGITAL STATUS MODE**
![image](https://github.com/ColdFireHunter/MAX22530-arduino/assets/53087752/a43e706e-1dd6-4f47-9edf-45a9c6d9313f)

Taken from the datasheet.

```C++
readCompReg(int channel, bool highlow);
readCompStat(void);
readInterrupt(void);
```
Reads the selected register and returns its value.
**If you read the interrupt register it is cleared**

COMP STATUS
![image](https://github.com/ColdFireHunter/MAX22530-arduino/assets/53087752/6704d784-08cb-42d2-9f71-1c1afa07f9a1)

INTERRUPT STATUS
![image](https://github.com/ColdFireHunter/MAX22530-arduino/assets/53087752/2940fe6e-d261-4a0f-a69c-15250e1d72ee)

```C++
setInterruptEnable(uint16_t data);
```
Sets the interrupt register to enable the corresponding interrupts.
![image](https://github.com/ColdFireHunter/MAX22530-arduino/assets/53087752/3b9e3686-f99a-4b35-ba9d-2ebdd52b0207)

```C++
SPI_CRC (bool enable);
```
Enables or disables the SPI_CRC function. **Default: disabled**

```C++
COMTThreshold(bool enable);
```
For all 4 channels, the comparator thresholds from channel 1 are used. **Default: disabled**

```C++
CLEARFilter(int channel);
```
Clears the averaging filter for the specified channel

```C++
VDDF(bool enable);
```
Enables or disables the isolated supply voltage (1 is off) default: activated

```C++
SoftwareReset(void);
```
Software Reset

```C++
HardwareReset(void);
```
Hardware Reset

```C++
clearPOR(void);
```
Clears the POR (Power on Reset) bit in the 0x00 register (bit cannot be set)
