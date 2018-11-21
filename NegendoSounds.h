#ifndef NegendoSounds_h
#define NegendoSounds_h

#include "Sounds.h"

#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class NegendoSounds
{
public:
	NegendoSounds(){}
	void _tone (float noteFrequency, long noteDuration, int silentDuration);
    void bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration);
    void sing(int songName);
	void playNote(float noteFrequency, long noteDuration);
	void playMusic(int name);
    NegendoSounds(int _pinBuzzer);
private:

protected:
	int Buzzer_pin;
	
};
#endif