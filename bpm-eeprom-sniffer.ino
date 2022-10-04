#include <Wire.h>

void setup()
{
    Serial.begin(115200);
    Wire.begin(0x50, 21, 22, 400000);
    Wire.onReceive(receiveEvent);
}

void loop()
{
}

void receiveEvent(int numBytes)
{
    for (byte i = 1; i <= numBytes; i++)
    {
        Serial.printf("%u/%d\t", i, numBytes);

        byte b = Wire.read();
        Serial.print(b, DEC);

        Serial.print("\t\t");
        Serial.print(b, HEX);

        Serial.print("\t\t");
        Serial.println(b, BIN);
    }
    Serial.println();
}
