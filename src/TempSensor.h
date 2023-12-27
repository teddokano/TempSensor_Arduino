/** TempSensor operation library for Arduino
 *
 *  @class  TempSensor
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#ifndef ARDUINO_TEMP_SENSOR_H
#define ARDUINO_TEMP_SENSOR_H

#include <Arduino.h>
#include <stdint.h>

#include "I2C_device.h"

/** TempSensor class
 *	
 *  @class TempSensor
 *
 *	TempSensor class is a base class for all temperature sensors
 *	All actual device class will be inherited from this class
 */

class TempSensor : public I2C_device
{
public:
	enum mode {
		COMPARATOR,	/**< Comparator mode	*/
		INTERRUPT,	/**< Interrupt mode	*/
	};

	/*
	 *	Methods to define class fundamental features, overridden by sub-classes
	 */
	TempSensor( const uint8_t i2c_address );
	TempSensor( TwoWire& wire, const uint8_t i2c_address );
	virtual ~TempSensor();
	virtual float temp( void )	= 0;
	
	/** Get temperature value in degree Celsius [°C] 
	 *
	 *	This method simply calls "temp()" method	
	 *
	 * @return temperature value in degree Celsius [°C] 
	 */
	virtual float read( void );
};


/** LM75B class
 *	
 *  @class LM75B

 *  About LM75B:
 *		https://www.nxp.com/products/sensors/i3c-ic-digital-temp-sensors/digital-temperature-sensor-and-thermal-watchdog:LM75B?_gl=1*kd25ib*_ga*NTA5NDE1NDA0LjE2NzgzNDYyNzA.*_ga_WM5LE0KMSH*MTY4MjEyMjc1OC42Mi4wLjE2ODIxMjI3NTguMC4wLjA.
 */

class LM75B : public TempSensor
{
public:
	/** Name of the PCT2075 registers */
	enum reg_num {
		Temp,	/**< Temp register	*/
		Conf,	/**< Conf register	*/
		Thyst,	/**< Thyst register	*/
		Tos,	/**< Tos registe	*/
	};

	/** Create a PCT2075 instance connected to specified I2C pins with specified address
	 *
	 * @param i2c_address I2C-bus address (default: (0x90>>1))
	 */
	LM75B( const uint8_t i2c_address = (0x90 >> 1) );

	/** Create a PCT2075 instance connected to specified I2C pins with specified address
	 *
	 * @param wire TwoWire instance
	 * @param i2c_address I2C-bus address (default: (0x90>>1))
	 */
	LM75B( TwoWire& wire, const uint8_t i2c_address = (0x90 >> 1) );

	/** Destructor of PCT2075
	 */
	virtual ~LM75B();
	
	/** Get temperature value in degree Celsius [°C] 
	 *
	 * @return temperature value in degree Celsius [°C] 
	 */
	virtual float temp( void ) override;

	/** Set Overtemperature shutdown threshold (Tos) and hysteresis (Thyst) in degree Celsius [°C] 
	 *
	 *	This method takes 2 values and higher value will set as the threshold (Tos) and 
	 *	another will be the hysteresis (Thyst)
	 *
	 * @param v0 a value in degree Celsius
	 * @param v1 a value in degree Celsius
	 */	
	virtual void thresholds( const float v0, const float v1 );

	/** Set OS operation mode 
	 *
	 * @param flag use PCT2075::COMPARATOR or PCT2075::INTERRUPT values
	 */	
	virtual void os_mode( const mode flag );

#if DOXYGEN_ONLY
	/** Get temperature value in degree Celsius [°C] 
	 *
	 *	This method simply calls "temp()" method	
	 *
	 * @return temperature value in degree Celsius [°C] 
	 */
	virtual float read( void );

	/** Ping the device
	 *
	 * @return true when ACK 
	 */
	bool ping( void );
		
	/** Multiple register write
	 * 
	 * @param reg register index/address/pointer
	 * @param data pointer to data buffer
	 * @param size data size
	 * @return transferred data size
	 */
	int reg_w( const uint8_t reg_adr, uint8_t *data, const uint16_t size );

	/** Single register write
	 * 
	 * @param reg register index/address/pointer
	 * @param data pointer to data buffer
	 * @param size data size
	 * @return transferred data size
	 */
	int reg_w( const uint8_t reg_adr, const uint8_t data );

	/** Multiple register read
	 * 
	 * @param reg register index/address/pointer
	 * @param data pointer to data buffer
	 * @param size data size
	 * @return transferred data size
	 */
	int reg_r( const uint8_t reg_adr, uint8_t *data, const uint16_t size );

	/** Single register read
	 * 
	 * @param reg register index/address/pointer
	 * @return read data
	 */
	uint8_t	reg_r( const uint8_t reg_adr );

	/** Register write, 8 bit
	 *
	 * @param reg register index/address/pointer
	 * @param val data value
	 */
	void write_r8( const uint8_t reg, const uint8_t val );

	/** Register write, 16 bit
	 * 
	 *	This 16 bit access may ot be common but it's useful for sensor devices
	 *
	 * @param reg register index/address/pointer
	 * @param val data value
	 */
	void write_r16( const uint8_t reg, const uint16_t val );

	/** Register read, 8 bit
	 *
	 * @param reg register index/address/pointer
	 * @return data value
	 */
	uint8_t read_r8( const uint8_t reg );

	/** Register read, 16 bit
	 *	
	 *	This 16 bit access may ot be common but it's useful for sensor devices
	 *
	 * @param reg register index/address/pointer
	 * @return data value
	 */
	uint16_t read_r16( const uint8_t reg );

	/** Register overwriting with bit-mask
	 *	
	 *	Register can be updated by bit level
	 *
	 * @param reg register index/address/pointer
	 * @param mask bit-mask to protect overwriting
	 * @param value value to overwrite
	 */
	void bit_op8(  const uint8_t reg, const  uint8_t mask, const  uint8_t value );
	void bit_op16( const uint8_t reg, const uint16_t mask, const uint16_t value );
#endif	// DOXYGEN_ONLY
};


/** PCT2075 class
 *	
 *  @class PCT2075

 *  About PCT2075:
 *    https://www.nxp.com/products/sensors/i3c-ic-digital-temp-sensors/ic-bus-fm-plus-1-degree-c-accuracy-digital-temperature-sensor-and-thermal-watchdog:PCT2075
 */

class PCT2075 : public LM75B
{
public:
	/** Name of the PCT2075 registers */
	enum reg_num {
		Temp,	/**< Temp register	*/
		Conf,	/**< Conf register	*/
		Thyst,	/**< Thyst register	*/
		Tos,	/**< Tos registe	*/
		Tidle,	/**< Tidle register	*/
	};
	
	/** Create a PCT2075 instance connected to specified I2C pins with specified address
	 *
	 * @param i2c_address I2C-bus address (default: (0x90>>1))
	 */
	PCT2075( const uint8_t i2c_address = (0x90 >> 1) );

	/** Create a PCT2075 instance connected to specified I2C pins with specified address
	 *
	 * @param wire TwoWire instance
	 * @param i2c_address I2C-bus address (default: (0x90>>1))
	 */
	PCT2075( TwoWire& wire, const uint8_t i2c_address = (0x90 >> 1) );

    /** Destructor of PCT2075
     */
	virtual ~PCT2075();

#if DOXYGEN_ONLY
	/** Get temperature value in degree Celsius [°C] 
	 *
	 * @return temperature value in degree Celsius [°C] 
	 */
	virtual float temp( void );
	
	/** Get temperature value in degree Celsius [°C] 
	 *
	 *	This method simply calls "temp()" method	
	 *
	 * @return temperature value in degree Celsius [°C] 
	 */
	virtual float read( void );

	/** Set Overtemperature shutdown threshold (Tos) and hysteresis (Thyst) in degree Celsius [°C] 
	 *
	 *	This method takes 2 values and higher value will set as the threshold (Tos) and 
	 *	another will be the hysteresis (Thyst)
	 *
	 * @param v0 a value in degree Celsius
	 * @param v1 a value in degree Celsius
	 */	
	virtual void thresholds( const float v0, const float v1 );

	/** Set OS operation mode 
	 *
	 * @param flag use PCT2075::COMPARATOR or PCT2075::INTERRUPT values
	 */	
	virtual void os_mode( const mode flag );	

	/** Ping the device
	 *
	 * @return true when ACK 
	 */
	bool ping( void );
	/** Register write, 8 bit
	 *
	 * @param reg register index/address/pointer
	 * @param val data value
	 */
	void write_r8( const uint8_t reg, const uint8_t val );

	/** Register write, 16 bit
	 * 
	 *	This 16 bit access may ot be common but it's useful for sensor devices
	 *
	 * @param reg register index/address/pointer
	 * @param val data value
	 */
	void write_r16( const uint8_t reg, const uint16_t val );

	/** Register read, 8 bit
	 *
	 * @param reg register index/address/pointer
	 * @return data value
	 */
	uint8_t read_r8( uint8_t reg );

	/** Register read, 16 bit
	 *	
	 *	This 16 bit access may ot be common but it's useful for sensor devices
	 *
	 * @param reg register index/address/pointer
	 * @return data value
	 */
	uint16_t read_r16( const uint8_t reg );

	/** Register overwriting with bit-mask
	 *	
	 *	Register can be updated by bit level
	 *
	 * @param reg register index/address/pointer
	 * @param mask bit-mask to protect overwriting
	 * @param value value to overwrite
	 */
	void bit_op8(  const uint8_t reg, const  uint8_t mask, const  uint8_t value );
	void bit_op16( const uint8_t reg, const uint16_t mask, const uint16_t value );
#endif	// DOXYGEN_ONLY
};


/** P3T1755 class
 *	
 *  @class P3T1755

 *  About P3T1085:
 *		https://www.nxp.com/products/sensors/i3c-ic-digital-temp-sensors/i3c-ic-bus-0-5-c-accurate-digital-temperature-sensor:P3T1755DP
 */

class P3T1755 : public LM75B
{
public:
	/** Name of the PCT2075 registers */
	enum reg_num {
		Temp,	/**< Temp register	*/
		Conf,	/**< Conf register	*/
		T_LOW,	/**< Thyst register	*/
		T_HIGH,	/**< Tos registe	*/
	};
	
	/** Create a PCT2075 instance connected to specified I2C pins with specified address
	 *
	 * @param i2c_address I2C-bus address (default: (0x90>>1))
	 */
	P3T1755( const uint8_t i2c_address = (0x98 >> 1) );

	/** Create a PCT2075 instance connected to specified I2C pins with specified address
	 *
	 * @param wire TwoWire instance
	 * @param i2c_address I2C-bus address (default: (0x90>>1))
	 */
	P3T1755( TwoWire& wire, const uint8_t i2c_address = (0x90 >> 1) );

	/** Destructor of PCT2075
	 */
	virtual ~P3T1755();

	/** Set Overtemperature shutdown threshold (Tos) and hysteresis (Thyst) in degree Celsius [°C] 
	 *
	 *	This method takes 2 values and higher value will set as the threshold (Tos) and 
	 *	another will be the hysteresis (Thyst)
	 *
	 * @param v0 a value in degree Celsius
	 * @param v1 a value in degree Celsius
	 */	
	virtual void thresholds( const float v0, const float v1 ) override;

#if DOXYGEN_ONLY
	/** Get temperature value in degree Celsius [°C] 
	 *
	 * @return temperature value in degree Celsius [°C] 
	 */
	virtual float temp( void );
	
	/** Get temperature value in degree Celsius [°C] 
	 *
	 *	This method simply calls "temp()" method	
	 *
	 * @return temperature value in degree Celsius [°C] 
	 */
	virtual float read( void );

	/** Set OS operation mode 
	 *
	 * @param flag use PCT2075::COMPARATOR or PCT2075::INTERRUPT values
	 */	
	virtual void os_mode( const mode flag );	

	/** Ping the device
	 *
	 * @return true when ACK 
	 */
	bool ping( void );

	/** Register write, 8 bit
	 *
	 * @param reg register index/address/pointer
	 * @param val data value
	 */
	void write_r8( const uint8_t reg, const uint8_t val );

	/** Register write, 16 bit
	 * 
	 *	This 16 bit access may ot be common but it's useful for sensor devices
	 *
	 * @param reg register index/address/pointer
	 * @param val data value
	 */
	void write_r16( const uint8_t reg, const uint16_t val );

	/** Register read, 8 bit
	 *
	 * @param reg register index/address/pointer
	 * @return data value
	 */
	uint8_t read_r8( const uint8_t reg );

	/** Register read, 16 bit
	 *	
	 *	This 16 bit access may ot be common but it's useful for sensor devices
	 *
	 * @param reg register index/address/pointer
	 * @return data value
	 */
	uint16_t read_r16( const uint8_t reg );

	/** Register overwriting with bit-mask
	 *	
	 *	Register can be updated by bit level
	 *
	 * @param reg register index/address/pointer
	 * @param mask bit-mask to protect overwriting
	 * @param value value to overwrite
	 */
	void bit_op8(  const uint8_t reg, const  uint8_t mask, const  uint8_t value );
	void bit_op16( const uint8_t reg, const uint16_t mask, const uint16_t value );
#endif	// DOXYGEN_ONLY
};


/** P3T1085 class
 *	
 *  @class P3T1085

 *  About P3T1085:
 *    https://www.nxp.com/products/sensors/ic-digital-temperature-sensors/i3c-ic-bus-0-5-c-accurate-digital-temperature-sensor:P3T1085UK
 */

class P3T1085 : public P3T1755
{
public:
	/** Create a PCT2075 instance connected to specified I2C pins with specified address
	 *
	 * @param i2c_address I2C-bus address (default: (0x90>>1))
	 */
	P3T1085( uint8_t i2c_address = (0x90 >> 1) );

	/** Create a PCT2075 instance connected to specified I2C pins with specified address
	 *
	 * @param wire TwoWire instance
	 * @param i2c_address I2C-bus address (default: (0x90>>1))
	 */
	P3T1085( TwoWire& wire, const uint8_t i2c_address = (0x90 >> 1) );

	/** Destructor of PCT2075
	 */
	virtual ~P3T1085();

	/** Set OS operation mode 
	 *
	 * @param flag use PCT2075::COMPARATOR or PCT2075::INTERRUPT values
	 */	
	virtual void os_mode( const mode flag ) override;

	/** Clear ALERT (Clear interurpt)
	 * 
	 * @return true if FH flag in Congiguration register is set 
	 */	
	virtual bool clear( void );

#if DOXYGEN_ONLY
	/** Get temperature value in degree Celsius [°C] 
	 *
	 * @return temperature value in degree Celsius [°C] 
	 */
	virtual float temp( void );
	
	/** Get temperature value in degree Celsius [°C] 
	 *
	 *	This method simply calls "temp()" method	
	 *
	 * @return temperature value in degree Celsius [°C] 
	 */
	virtual float read( void );

	/** Set Overtemperature shutdown threshold (Tos) and hysteresis (Thyst) in degree Celsius [°C] 
	 *
	 *	This method takes 2 values and higher value will set as the threshold (Tos) and 
	 *	another will be the hysteresis (Thyst)
	 *
	 * @param v0 a value in degree Celsius
	 * @param v1 a value in degree Celsius
	 */	
	virtual void thresholds( const float v0, const float v1 );

	/** Ping the device
	 *
	 * @return true when ACK 
	 */
	bool ping( void );

	/** Register write, 16 bit
	 * 
	 *	This 16 bit access may ot be common but it's useful for sensor devices
	 *
	 * @param reg register index/address/pointer
	 * @param val data value
	 */
	void write_r16( const uint8_t reg, const uint16_t val );

	/** Register read, 16 bit
	 *	
	 *	This 16 bit access may ot be common but it's useful for sensor devices
	 *
	 * @param reg register index/address/pointer
	 * @return data value
	 */
	uint16_t read_r16( const uint8_t reg );

	/** Register overwriting with bit-mask
	 *	
	 *	Register can be updated by bit level
	 *
	 * @param reg register index/address/pointer
	 * @param mask bit-mask to protect overwriting
	 * @param value value to overwrite
	 */
	void bit_op8(  const uint8_t reg, const  uint8_t mask, const  uint8_t value );
	void bit_op16( const uint8_t reg, const uint16_t mask, const uint16_t value );
#endif	// DOXYGEN_ONLY
};

#endif //	ARDUINO_TEMP_SENSOR_H
