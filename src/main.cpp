#include <Arduino.h>
#include <ESP.h>

void setup() {
  log_d("Total heap: %d", ESP.getHeapSize());
  log_d("Free heap: %d", ESP.getFreeHeap());
  log_d("Total PSRAM: %d", ESP.getPsramSize());
  log_d("Free PSRAM: %d\n", ESP.getFreePsram());
  delay(1000);
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  //get chip id
  uint64_t chipid;
  chipid=ESP.getEfuseMac();
  
  log_d("Hardware info");
  log_d("%d cores Wifi %s%s", chip_info.cores, (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "", (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
  log_d("Silicon revision: %d", chip_info.revision);
  log_d("ESP32 Chip model: %s Rev %d", ESP.getChipModel(), ESP.getChipRevision());
  log_d("ESP32 Chip ID: %04X%08X\n",(uint16_t)(chipid>>32),(uint32_t)chipid);  
  log_d("%dMB %s flash", spi_flash_get_chip_size()/(1024*1024), (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embeded" : "external");
}

void loop() {
  // put your main code here, to run repeatedly:
}