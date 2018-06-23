#include <Arduino.h>
#include <Keyboard.h>

bool buttonStates[]{ false, false, false, false, false, false };

const int buttonPins[] = { 11, 10, 9, A0, A1, A2 };
const int buttonKeysLayer1[] = { KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18 };
const int buttonKeysLayer2[] = { '1', '2', '3', '4', '5', '6' };

const int size = sizeof(buttonPins) / sizeof(int);
const int pollRate = 10;
long m = millis();

void setup() {
	// Turn off built-in LED
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

	for (int i = 0; i < size; i++)
		pinMode(buttonPins[i], INPUT_PULLUP);

	m = millis();

	Keyboard.begin();
}

void loop() {
	auto isSecondaryLayer = Keyboard.getLedStatus(LED_SCROLL_LOCK);
    digitalWrite(LED_BUILTIN, isSecondaryLayer ? LOW : HIGH);
	
	if (millis() - m > pollRate)
	{
		m = millis();

	    auto buttonKeys = isSecondaryLayer ? buttonKeysLayer2 : buttonKeysLayer1;
		for (int i = 0; i < size; i++)
		{
			int state = digitalRead(buttonPins[i]);

			if (state == LOW && !buttonStates[i])
			{
				buttonStates[i] = true;
				Keyboard.press(buttonKeys[i]);
			}
			else if (state == HIGH && buttonStates[i])
			{
				buttonStates[i] = false;
				Keyboard.release(buttonKeys[i]);
			}
		}
	}
}