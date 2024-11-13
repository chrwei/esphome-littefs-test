#pragma once
#include <FS.h>
#include <LittleFS.h>
#include "esphome/core/automation.h"
#include "esphome/core/component.h"

namespace esphome {
namespace littlefs {

class littlefs : public Component {
public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  bool put(const char *path, String &message);

  bool get(const char *path, String &message);

  Trigger<> *get_connect_trigger() const { return this->on_setup_trigger_; };

protected:
  Trigger<> *on_setup_trigger_{new Trigger<>()};

private:
    void listDir();
};



} // namespace i2c_eeprom
} // namespace esphome