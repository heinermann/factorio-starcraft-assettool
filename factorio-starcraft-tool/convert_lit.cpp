#include "convert_lit.h"
#include <vector>
#include <cstdint>
#include <sstream>
#include <fstream>

struct lit_header_t {
  std::uint32_t count;
  std::uint32_t unk1;
  std::uint32_t unk2;
  std::uint32_t offsets[1];
};

struct lit_frame_t {
  std::int32_t x, y;
  std::uint32_t color;
  std::uint32_t intensity;
  std::uint32_t radius;
};

struct lit_entry_t {
  std::uint32_t framecount;
  lit_frame_t frames[1];
};

void convert_litfile(const std::vector<std::uint8_t>& data) {
  const lit_header_t* header = reinterpret_cast<const lit_header_t*>(data.data());

  std::ofstream outfile("main.lit.yaml");

  for (int i = 0; i < header->count; ++i) {
    const lit_entry_t* entry = (const lit_entry_t*)&data.data()[header->offsets[i]];

    std::ostringstream entrystr;

    entrystr << i << ":\n";

    bool hasAny = false;
    for (int frameno = 0; frameno < entry->framecount; ++frameno) {
      const lit_frame_t& frame = entry->frames[frameno];

      if (frame.color == 0 && frame.intensity == 0 && frame.radius == 0) continue;

      entrystr << "  " << frameno << ":\n";
      entrystr << "    pos: [" << frame.x << ", " << frame.y << "]\n";
      entrystr << "    color: [" << (frame.color & 0xFF) << ", " << (frame.color >> 8 & 0xFF) << ", " << (frame.color >> 16 & 0xFF) << ", " << (frame.color >> 24 & 0xFF) << "]\n";
      entrystr << "    intensity: " << frame.intensity << "\n";
      entrystr << "    radius: " << frame.radius << "\n";
      hasAny = true;
    }
    if (hasAny) {
      outfile << entrystr.str();
    }
  }
}
