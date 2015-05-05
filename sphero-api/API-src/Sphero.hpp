/************************************************************************
    Sphero  -  description
                             -------------------
    début                : lun. 16 mars 2015
 *************************************************************************/

//---------- Interface de la classe <Sphero> (fichier Sphero.h) ------
#if ! defined ( SPHERO_H )
#define SPHERO_H

//--------------------------------------------------- Interfaces utilisées
#include <pthread.h>
#include <cstdint>

#include "bluetooth/bluetooth_connector.h"
#include "ClientCommandPacket.hpp"

class ClientCommandPacket;

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 
typedef int16_t spherocoord_t;

class sphero_listener;

//------------------------------------------------------------------------ 
//T est un connecteur bluetooth
class Sphero 
{
	//----------------------------------------------------------------- PUBLIC

public:


	//------------------------------------------------- Surcharge d'opérateurs
	//N'a pas de sens
	Sphero & operator = ( const Sphero & unSphero ) = delete;

	//-------------------------------------------- Constructeurs - destructeur
	//N'a pas de sens
	Sphero ( const Sphero & unSphero ) = delete;

	/*
	 * BT addres
	 * s (format : "XX:XX:XX:XX:XX:XX")
	 */
	Sphero(char const * const btaddr, bluetooth_connector* btcon);

	virtual ~Sphero ( );

	//----------------------------------------------------- Méthodes publiques

	void reconnect();

	void disconnect();

	void sendPacket(ClientCommandPacket& packet);

	void ping();

	void setColor(uint8_t red, uint8_t green, uint8_t blue, bool persist = false);
	//Changes the color with the given hex values, persist will set as user color

	void setBackLedOutput(uint8_t power);

	void setHeading(uint16_t heading);
	//Change the heading with and angle in ° (range from 0 to 359)

	void setStabilization(bool on = true);
	//Enable or disable stabilization

	void setRotationRate(uint8_t angspeed = 0xc8);
	//Change the rotation speed, as angspeed*0.784 degrees/sec
	//Warning = high value may become really uncontrollable

	void setSelfLevel(
			uint8_t options = 0, 
			uint8_t angle_limit = 3, 
			uint8_t timeout = 15, 
			uint8_t trueTime = 30
		);

	//void setDataStreaming(uint16_t N, uint16_t M, uint32_t MASK, uint8_t pcnt, uint32_t MASK2 = 0);

	void enableCollisionDetection(uint8_t Xt, uint8_t Xspd, uint8_t Yt, uint8_t Yspd, uint8_t Dead);

	void disableCollisionDetection();

	bool isConnected()
	{
		return _bt_adapter->isConnected();
	}

	void configureLocator(uint8_t flags, uint16_t X, uint16_t Y, uint16_t yaw);

	//getLocator : will have to discuss this...
	//getRGDLed : same

	void setAccelerometerRange(uint8_t range = 0x02);

	void roll(uint8_t speed, uint16_t heading, uint8_t state = 0);

	//setRawMotorValue : not needed ?

	void setMotionTimeout(uint16_t time);

	void setPermOptFlags(uint32_t flags);

	//getPermOptFlags : we'll see

	void setTmpOptFlags(uint32_t flags);

	//getTmpOptFlags : we'll see

	void setDeviceMode(uint8_t value = 0);
	//01h will set to user hack mode

	//getDeviceMode

	void runMacro(uint8_t id);

	//void saveMacro(Macro macro);

	void sleep(uint16_t time, uint8_t macro = 0,uint16_t orbbasic = 0);

	void setInactivityTimeout(uint16_t timeout);
	//------------------------------------------------------------------ PRIVE

protected:
	//---------- ------------------------------------------- Méthodes protégées
	static void* monitorStream(void* sphero_ptr);


private:
	//------------------------------------------------------- Méthodes privées

protected:
	//----------------------------------------------------- Attributs protégés

private:
	//------------------------------------------------------- Attributs privés
	
	bluetooth_connector* _bt_adapter;

	/*
	 * X accelerometer
	 */
	spherocoord_t accelerometer_x;

	/*
	 * Y accelerometer
	 */
	spherocoord_t accelerometer_y;

	/*
	 * Z accelerometer
	 */
	spherocoord_t accelerometer_z;

	//To be continued

	bool resetTimer = true;
	bool waitConfirm = false;

	int _bt_socket;
	pthread_t monitor;

	const char * address;

	//---------------------------------------------------------- Classes amies

	//-------------------------------------------------------- Classes privées

	//----------------------------------------------------------- Types privés
};

//----------------------------------------- Types dépendants de <sphero>

#endif // SPHERO_H

