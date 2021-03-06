#ifndef __CONSOLE_CONTROL__
#define __CONSOLE_CONTROL__

#include "Arduino.h"

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	#include "ArduinoSTL.h"
#endif

#include "map"
#include "vector"

#define LOGIN_COMMAND "login"
#define LOGOUT_COMMAND "logout"
#define RESET_COMMAND "reset"

class ConsoleControl
{
	typedef void(*CommandFunction)(const String, std::vector<String>);

	public:
		bool SilenceMode;

		typedef std::vector<String> CommandArgs;

		ConsoleControl(HardwareSerial &hs, uint32_t baud, String pw);
		ConsoleControl(HardwareSerial &hs, uint32_t baud, String pw, bool sm);
		
		void loop(void);
		void on(String command, CommandFunction function);
		void remove(String command);
		void log(String line);

	private:
		//Properties
		bool authorized = false;
		HardwareSerial *serial;
		String password;
		std::map<String, CommandFunction> _commands;
		
		//Methods
		void compile(String command);
		void login(String command, CommandArgs args);
		void logout(String command);
		void reset(String command);
		std::vector<String> explode(String string);
};

#endif