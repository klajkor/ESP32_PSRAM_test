#include <Arduino.h>
#include <ESP.h>
#include <Wire.h>

#define GPIO_LED1 2
#define GPIO_LED2 5

#define GPIO_SDA 21
#define GPIO_SCL 22

void i2c_scanner(void);
void setup(void);
void loop(void);

void setup(void)
{
    Serial.begin(115200);
    pinMode(GPIO_LED1, OUTPUT);
    pinMode(GPIO_LED2, OUTPUT);
    digitalWrite(GPIO_LED1, HIGH);
    digitalWrite(GPIO_LED2, HIGH);
    log_d("Total heap: %d", ESP.getHeapSize());
    log_d("Free heap: %d", ESP.getFreeHeap());
    log_d("Total PSRAM: %d", ESP.getPsramSize());
    log_d("Free PSRAM: %d\n", ESP.getFreePsram());
    delay(1000);
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    // get chip id
    uint64_t chipid;
    chipid = ESP.getEfuseMac();

    log_d("Hardware info");
    log_d("%d cores Wifi %s%s", chip_info.cores, (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "", (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
    log_d("Silicon revision: %d", chip_info.revision);
    log_d("ESP32 Chip model: %s Rev %d", ESP.getChipModel(), ESP.getChipRevision());
    log_d("ESP32 Chip ID: %04X%08X\n", (uint16_t)(chipid >> 32), (uint32_t)chipid);
    log_d("%dMB %s flash", spi_flash_get_chip_size() / (1024 * 1024), (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embeded" : "external");
    Wire.begin(GPIO_SDA, GPIO_SCL);
    i2c_scanner();
}

void i2c_scanner(void)
{
    Serial.println();
    Serial.println("I2C scanner. Scanning ...");
    byte count = 0;

    Wire.begin();
    for (byte i = 8; i < 120; i++)
    {
        Wire.beginTransmission(i);       // Begin I2C transmission Address (i)
        if (Wire.endTransmission() == 0) // Receive 0 = success (ACK response)
        {
            Serial.print("Found address: ");
            Serial.print(i, DEC);
            Serial.print(" (0x");
            Serial.print(i, HEX); // PCF8574 7 bit address
            Serial.println(")");
            count++;
        }
    }
    Serial.print("Found ");
    Serial.print(count, DEC); // numbers of devices
    Serial.println(" device(s).");
}

void loop(void)
{
    // put your main code here, to run repeatedly:
    digitalWrite(GPIO_LED1, HIGH);
    digitalWrite(GPIO_LED2, HIGH);
    delay(250);
    digitalWrite(GPIO_LED1, LOW);
    delay(250);
    digitalWrite(GPIO_LED1, HIGH);
    digitalWrite(GPIO_LED2, LOW);
    delay(250);
    digitalWrite(GPIO_LED1, LOW);
    delay(250);
}
