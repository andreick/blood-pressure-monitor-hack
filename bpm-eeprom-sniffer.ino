#include <Wire.h>

#define BPM_POWER_PIN 13

byte numWritings;
String systolic;
String diastolic;
int heartRate;

void setup()
{
    pinMode(BPM_POWER_PIN, OUTPUT);
    Serial.begin(115200);
    Wire.begin(0x50, 21, 22, 400000); // I2C fast mode
    Wire.onReceive(receiveEvent);
}

void pushBpmPowerButton() // Emulate a push on power button
{
    digitalWrite(BPM_POWER_PIN, HIGH);
    delay(100);
    digitalWrite(BPM_POWER_PIN, LOW);
}

void startBpm() // The power button must be pressed twice to begin the measurement
{
    pushBpmPowerButton();
    delay(200);
    pushBpmPowerButton();
}

void loop()
{
    startBpm();
    delay(2 * 60 * 1000); // Run every 2 minutes
}

int readData()
{
    Wire.read(); // Discard the memory address
    return Wire.read();
}

String hexToString(int hex)
{
    String str = String(hex, HEX);
    if (str.length() == 1)
    {
        return '0' + str;
    }
    return str;
}

void receiveEvent(int numBytes)
{
    if (numBytes == 2) // Receiving a writing
    {
        switch (++numWritings)
        {
        case 1:
        {
            int memAddress = Wire.read();
            if (memAddress == 0xF) // Measurement error
            {
                Serial.println("Erro na medição");
                numWritings = 0;
            }
            break;
        }
        case 6:
        {
            int data = readData();
            switch (data)
            {
            case 0x10:
                sys = "1";
                dia = "";
                break;
            case 0x11:
                sys = "1";
                dia = "1";
                break;
            case 0x01:
                sys = "";
                dia = "1";
                break;
            case 0x00:
                sys = "";
                dia = "";
                break;
            }
            break;
        }
        case 7:
        {
            int data = readData();
            systolic += hexToString(data);
            break;
        }
        case 8:
        {
            int data = readData();
            diastolic += hexToString(data);
            break;
        }
        case 9:
            heartRate = readData();
            break;
        case 10:
            Serial.printf("Pressão sistólca: %s mmHg\n", systolic);
            Serial.printf("Pressão diastólica: %s mmHg\n", diastolic);
            Serial.printf("Frequência cardíaca: %d bpm\n", heartRate);
            numWritings = 0;
            break;
        }
    }
}
