#include <MAX22530.h>
#include <SPI.h>

MAX22530::MAX22530(uint8_t cspin, SPIClass *theSPI)
{
  _SPI = theSPI;
  _cs = cspin;
  pinMode(_cs, OUTPUT);
  digitalWrite(_cs, HIGH);
}
bool MAX22530::begin(int frequency)
{
  _frequency = frequency;
  _SPI->begin();
  return MAX22530::MAX22530_INIT();
}
int MAX22530::readADC(int channel)
{
  int temp = 0;
  switch (channel)
  {
  case 0:
    temp = MAX22530::MAX22530_read_register(ADC1_REG);
    break;
  case 1:
    temp = MAX22530::MAX22530_read_register(ADC2_REG);
    break;
  case 2:
    temp = MAX22530::MAX22530_read_register(ADC3_REG);
    break;
  case 3:
    temp = MAX22530::MAX22530_read_register(ADC4_REG);
    break;
  default:
    break;
  }
  if (temp > 4096)
  {
    temp = -1;
  }
  return temp;
}
int MAX22530::readFiltered(int channel)
{
  int temp = 0;
  switch (channel)
  {
  case 0:
    temp = MAX22530::MAX22530_read_register(FADC1);
    break;
  case 1:
    temp = MAX22530::MAX22530_read_register(FADC2);
    break;
  case 2:
    temp = MAX22530::MAX22530_read_register(FADC3);
    break;
  case 3:
    temp = MAX22530::MAX22530_read_register(FADC4);
    break;
  default:
    break;
  }
  if (temp > 4096)
  {
    temp = -1;
  }
  return temp;
}
float MAX22530::CNVTVoltage(int count)
{
  return (float)VREF * count / 4096;
}
void MAX22530::setComp(int channel, uint16_t up_value, uint16_t down_value, bool source, bool mode)
{
  uint16_t temp_up = 0;
  uint16_t temp_down = 0;
  if (up_value > 4096)
  {
    up_value = 4096;
  }
  if (up_value < 0)
  {
    up_value = 0;
  }
  if (down_value > 4096)
  {
    down_value = 4096;
  }
  if (down_value < 0)
  {
    down_value = 0;
  }

  temp_up = up_value;
  temp_up = temp_up | (source << 14);
  temp_up = temp_up | (mode << 15);

  temp_down = down_value;

  switch (channel)
  {
  case 0:
    MAX22530::MAX22530_write_register(COUTHI1, temp_up);
    MAX22530::MAX22530_write_register(COUTLO1, temp_down);
    break;
  case 1:
    MAX22530::MAX22530_write_register(COUTHI2, temp_up);
    MAX22530::MAX22530_write_register(COUTLO2, temp_down);
    break;
  case 2:
    MAX22530::MAX22530_write_register(COUTHI3, temp_up);
    MAX22530::MAX22530_write_register(COUTLO3, temp_down);
    break;
  case 3:
    MAX22530::MAX22530_write_register(COUTHI4, temp_up);
    MAX22530::MAX22530_write_register(COUTLO4, temp_down);
    break;

  default:
    break;
  }
}
uint16_t MAX22530::readCompReg(int channel, bool highlow)
{
  uint16_t temp = 0;
  switch (channel)
  {
  case 0:
    if (highlow == 0)
    {
      temp = MAX22530::MAX22530_read_register(COUTLO1);
    }
    if (highlow == 1)
    {
      temp = MAX22530::MAX22530_read_register(COUTHI1);
    }
    break;
  case 1:
    if (highlow == 0)
    {
      temp = MAX22530::MAX22530_read_register(COUTLO2);
    }
    if (highlow == 1)
    {
      temp = MAX22530::MAX22530_read_register(COUTHI2);
    }
    break;
  case 2:
    if (highlow == 0)
    {
      temp = MAX22530::MAX22530_read_register(COUTLO3);
    }
    if (highlow == 1)
    {
      temp = MAX22530::MAX22530_read_register(COUTHI3);
    }
    break;
  case 3:
    if (highlow == 0)
    {
      temp = MAX22530::MAX22530_read_register(COUTLO4);
    }
    if (highlow == 1)
    {
      temp = MAX22530::MAX22530_read_register(COUTHI4);
    }
    break;
  default:
    break;
  }
  return temp;
}
uint16_t MAX22530::readCompStat()
{
  return MAX22530::MAX22530_read_register(COUT_STATUS);
}
uint16_t MAX22530::readInterrupt()
{
  return MAX22530::MAX22530_read_register(INTERRUPT_STATUS);
}
void MAX22530::setInterruptEnable(uint16_t data)
{
  if (data < 4096)
  {
    MAX22530::MAX22530_write_register(INTERRUPT_ENABLE, data);
  }
}
void MAX22530::SPI_CRC(bool enable)
{
  if (enable == 1)
  {
    MAX22530::MAX22530_EN_CRC();
  }
  if (enable == 0)
  {
    MAX22530::MAX22530_DIS_CRC();
  }
}
void MAX22530::COMTThreshold(bool enable)
{
  uint16_t register_value = MAX22530::MAX22530_read_register(CONTROL);
  if (enable == 1)
  {
    register_value = register_value | 16384;
  }
  if (enable == 0)
  {
    register_value = register_value & 49151;
  }

  MAX22530::MAX22530_write_register(CONTROL, register_value);
}
void MAX22530::CLEARFilter(int channel)
{
  uint16_t register_value = 0;
  switch (channel)
  {
  case 0:
    register_value = MAX22530::MAX22530_read_register(CONTROL);
    register_value = register_value | 16;
    MAX22530::MAX22530_write_register(CONTROL, register_value);
    delay(5);
    register_value = MAX22530::MAX22530_read_register(CONTROL);
    register_value = register_value & 65519;
    MAX22530::MAX22530_write_register(CONTROL, register_value);
    break;
  case 1:
    register_value = MAX22530::MAX22530_read_register(CONTROL);
    register_value = register_value | 32;
    MAX22530::MAX22530_write_register(CONTROL, register_value);
    delay(5);
    register_value = MAX22530::MAX22530_read_register(CONTROL);
    register_value = register_value & 65503;
    MAX22530::MAX22530_write_register(CONTROL, register_value);
    break;
  case 2:
    register_value = MAX22530::MAX22530_read_register(CONTROL);
    register_value = register_value | 64;
    MAX22530::MAX22530_write_register(CONTROL, register_value);
    delay(5);
    register_value = MAX22530::MAX22530_read_register(CONTROL);
    register_value = register_value & 65471;
    MAX22530::MAX22530_write_register(CONTROL, register_value);
    break;
  case 3:
    register_value = MAX22530::MAX22530_read_register(CONTROL);
    register_value = register_value | 128;
    MAX22530::MAX22530_write_register(CONTROL, register_value);
    delay(5);
    register_value = MAX22530::MAX22530_read_register(CONTROL);
    register_value = register_value & 65407;
    MAX22530::MAX22530_write_register(CONTROL, register_value);
    break;
  default:
    break;
  }
}
void MAX22530::VDDF(bool enable)
{
  uint16_t register_value = MAX22530::MAX22530_read_register(CONTROL);
  if (enable == 1)
  {
    register_value = register_value | 8;
  }
  if (enable == 0)
  {
    register_value = register_value & 65527;
  }

  MAX22530::MAX22530_write_register(CONTROL, register_value);
}
void MAX22530::SoftwareReset()
{
  MAX22530::MAX22530_softReset();
}
void MAX22530::HardwareReset()
{
  MAX22530::MAX22530_Reset();
}
void MAX22530::clearPOR()
{
  uint16_t register_value = 0;
  register_value = MAX22530::MAX22530_read_register(CONTROL);
  register_value = register_value | 4;
  MAX22530::MAX22530_write_register(CONTROL, register_value);
  delay(5);
  register_value = MAX22530::MAX22530_read_register(CONTROL);
  register_value = register_value & 65531;
  MAX22530::MAX22530_write_register(CONTROL, register_value);
}

long MAX22530::MAX22530_read_register(uint8_t regAddress)
{
  uint16_t result = 0;
  uint8_t crc_read = 0;
  uint32_t frame = (uint32_t)(regAddress << 2);
  if (!crc_enable) // Read/ Write bit set to 0 and burst bit set to 0.(b'18 is 0 and b'17 is 0)
  {
    _SPI->beginTransaction(SPISettings(_frequency, MSBFIRST, SPI_MODE0));
    // delayMicroseconds(1);
    digitalWrite(_cs, LOW);
    _SPI->transfer(frame);
    result = _SPI->transfer16(0);
    digitalWrite(_cs, HIGH);
    _SPI->endTransaction();
    return result;
  }
  else
  {
    uint8_t crc = crc_compute_2(frame << 16);
    _SPI->beginTransaction(SPISettings(_frequency, MSBFIRST, SPI_MODE0));
    // delayMicroseconds(1);
    digitalWrite(_cs, LOW);
    _SPI->transfer(frame);
    result = _SPI->transfer16(0);
    crc_read = _SPI->transfer(crc);
    digitalWrite(_cs, HIGH);
    _SPI->endTransaction();
    crc = crc_compute_2((frame << 16) + (result));
    if (crc == crc_read)
    {
      return result;
    }
  }
  return 0;
}
void MAX22530::MAX22530_write_register(uint8_t regAddress, uint16_t regValue)
{
  uint32_t data_frame1 = 0x0000;
  uint8_t crc_code = 0;

  if ((!crc_enable)) /// Read/ Write bit set to 1, burst bit set to 0.
  {
    data_frame1 = (uint32_t)((regAddress << 2) + (1 << 1));
  }
  else /// crc enabled, construct frame + compute crc.
  {
    data_frame1 = (uint32_t)((regAddress << 2) + (1 << 1));
    crc_code = crc_compute_2((data_frame1 << 16) + (regValue << 0));
  }

  _SPI->beginTransaction(SPISettings(_frequency, MSBFIRST, SPI_MODE0));
  digitalWrite(_cs, LOW);
  // delayMicroseconds(1);
  _SPI->transfer(data_frame1);
  if (crc_enable)
  {
    _SPI->transfer16(regValue);
    _SPI->transfer(crc_code);
  }
  else
  {
    _SPI->transfer16(regValue);
  }
  digitalWrite(_cs, HIGH);
  _SPI->endTransaction();
}
void MAX22530::MAX22530_Register_bit_toggle(uint8_t regAddress, uint8_t bit_position)
{
  int n = bit_position;
  uint16_t current_data = MAX22530_read_register(regAddress);
  uint16_t new_data = current_data ^ (1UL << n);
  MAX22530_write_register(regAddress, new_data);
}
void MAX22530::MAX22530_Reset()
{
  MAX22530_write_register(CONTROL, 1);
  crc_enable = false;
}
void MAX22530::MAX22530_softReset()
{
  MAX22530_write_register(CONTROL, 2);
}
void MAX22530::MAX22530_EN_CRC()
{
  uint16_t register_value = MAX22530_read_register(CONTROL);
  /*set EN CRC bit in Control Register*/
  if (register_value < 32768)
  {
    register_value |= 32768; // if register value = 0x8000
    MAX22530_write_register(CONTROL, register_value);
    crc_enable = true;
  }
}
void MAX22530::MAX22530_DIS_CRC()
{
  uint16_t register_value = MAX22530_read_register(CONTROL);
  /*disable CRC bit in Control Register*/
  register_value &= 32767; // if register value = 0x7FFF
  MAX22530_write_register(CONTROL, register_value);
  crc_enable = false;
}
bool MAX22530::MAX22530_INIT()
{
  uint8_t status = 0x1;
  if ((MAX22530_read_register(PROD_ID) != MAX22530_ID))
  {
    status = 0x0;
  }
  uint16_t temp = MAX22530_read_register(CONTROL);
  if (temp > 32767)
  {
    crc_enable = true;
    MAX22530_DIS_CRC();
  }
  return (status);
}

uint8_t MAX22530::crc_compute_2(uint32_t frame)
{
  uint8_t frame_high = (uint8_t)((frame & 0x00FF0000) >> 16);
  uint8_t frame_mid = (uint8_t)((frame & 0x0000FF00) >> 8);
  uint8_t frame_low = (uint8_t)(frame & 0x000000FF);
  uint8_t message[] = {frame_high, frame_mid, frame_low, 0x00};
  message[3] = getCRC(message, 3);
  return (message[3]);
}
uint8_t MAX22530::getCRC(uint8_t message[], unsigned int length)
{
  uint8_t i, crc = 0;

  for (i = 0; i < length; i++)
    crc = CRCTable[crc ^ message[i]];
  return crc;
}
