#include <Wire.h>

#define SECOND_MILLIS 1000
#define MINUTE_MILLIS 60 * SECOND_MILLIS

#define BPM_START_PIN 13

byte numWritings;
String sys;
String dia;
int hr;

void setup()
{
    pinMode(BPM_START_PIN, OUTPUT);
    Serial.begin(115200);
    Wire.begin(0x50, 21, 22, 400000); // I2C fast mode
    Wire.onReceive(receiveEvent);
}

void pushBpmStartButton() // Emulates a push on start button
{
    digitalWrite(BPM_START_PIN, HIGH);
    delay(100);
    digitalWrite(BPM_START_PIN, LOW);
}

void startBpm() // The start button must be pressed twice to begin the measurement
{
    pushBpmStartButton();
    delay(200);
    pushBpmStartButton();
}

void loop()
{
    startBpm();
    delay(2 * MINUTE_MILLIS); // Runs every 2 minutes
}

int readData()
{
    Wire.read(); // Discards the memory address
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
            sys += hexToString(data);
            break;
        }
        case 8:
        {
            int data = readData();
            dia += hexToString(data);
            break;
        }
        case 9:
            hr = readData();
            break;
        case 10:
            Serial.printf("Pressão sistólca: %s\n", sys);
            Serial.printf("Pressão diastólica: %s\n", dia);
            Serial.printf("Frequência cardíaca: %d\n", hr);
            numWritings = 0;
            break;
        }
    }
}
