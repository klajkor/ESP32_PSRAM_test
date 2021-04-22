#include <Arduino.h>
#include <ESP.h>

void setup() {
  log_d("Total heap: %d", ESP.getHeapSize());
  log_d("Free heap: %d", ESP.getFreeHeap());
  log_d("Total PSRAM: %d", ESP.getPsramSize());
  log_d("Free PSRAM: %d", ESP.getFreePsram());
  delay(2000);
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  
  log_d("\n");
  log_d("Hardware info");
  log_d("%d cores Wifi %s%s", chip_info.cores, (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "", (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
  log_d("Silicon revision: %d", chip_info.revision);
  log_d("%dMB %s flash", spi_flash_get_chip_size()/(1024*1024), (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embeded" : "external");
  
  //get chip id
  String chipId;
  chipId = String((uint32_t)ESP.getEfuseMac(), HEX);
  chipId.toUpperCase();
  
  log_d("Chip id: %s", chipId.c_str());
}

void loop() {
  // put your main code here, to run repeatedly:
}