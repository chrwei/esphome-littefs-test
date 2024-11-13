#include "littlefs.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace littlefs {

static const char *const TAG = "littlefs";

void littlefs::setup() {
  ESP_LOGCONFIG(TAG, "Setting up LittleFS...");

  if (!LittleFS.begin()) {
    LittleFS.format();
    if (!LittleFS.begin()) {
        ESP_LOGE(TAG, "LittleFS mount failed");
        return;
    }
  }

  ESP_LOGCONFIG(TAG, "OK");

  this->on_setup_trigger_->trigger();
}

void littlefs::dump_config() {
  ESP_LOGCONFIG(TAG, "Files:");
  listDir();
}

bool littlefs::put(const char *path, String &message) {
  bool res = false;
  File file = LittleFS.open(path, "w");
  if (!file) {
    ESP_LOGE(TAG, "Failed to open file for writing: %s", path);
    return false;
  }
  res = file.print(message.c_str());
  file.close();
  return res;
}

bool littlefs::get(const char *path, String &message) {
  File file = LittleFS.open(path, "r");
  if (!file) {
    ESP_LOGE(TAG, "Failed to open file for reading: %s", path);
    return false;
  }

  message = file.readString();
  file.close();

  return true;
}

void littlefs::listDir() {
  ESP_LOGCONFIG(TAG, "Listing directory: /");

  Dir root = LittleFS.openDir("/");

  while (root.next()) {
    File file = root.openFile("r");
    ESP_LOGCONFIG(TAG, "  FILE: %s %d", root.fileName(), file.size());
    file.close();
  }
}

} // namespace i2c_eeprom
} // namespace esphome