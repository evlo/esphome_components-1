#pragma once

#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>
#include "constants.h"

namespace esphome {
namespace sml {

using bytes = std::vector<uint8_t>;

class SmlBase {
 public:
  uint8_t type;
  uint8_t length;
  SmlBase(const bytes &buffer, unsigned int &pos);
  bool is_list();
  bool has_extended_length();

 protected:
  const bytes &buffer_;
  const unsigned int startpos_;
};

class SmlNode : public SmlBase {
 public:
  SmlNode(const bytes &buffer, unsigned int &pos);
  bytes value_bytes;
  std::vector<SmlNode> nodes;
};

class ObisInfo {
 public:
  ObisInfo(bytes server_id, SmlNode val_list_entry);
  bytes server_id;
  bytes code;
  bytes status;
  char unit;
  char scaler;
  bytes value;
  uint16_t value_type;
  std::string code_repr() const;
};

class SmlFile {
 public:
  SmlFile(bytes buffer);
  std::vector<SmlNode> messages;
  std::vector<ObisInfo> get_obis_info();

 protected:
  const bytes buffer_;
};

char check_sml_data(const bytes &buffer);

uint16_t calc_crc16_x25(const bytes &buffer);

uint16_t calc_crc16_kermit(const bytes &buffer);

std::string bytes_repr(const bytes &buffer);

uint64_t bytes_to_uint(const bytes &buffer);

int64_t bytes_to_int(const bytes &buffer);

std::string bytes_to_string(const bytes &buffer);
}  // namespace sml
}  // namespace esphome
