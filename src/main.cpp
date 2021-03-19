#include <CRC.h>
#include <Arduino.h>

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        delay(100);
    }

    crc_init();
}

void loop()
{
    uint16_t data = 10;
    Serial.printf("data: %d\n", crc_generate(data));

    delay(1000);
}
