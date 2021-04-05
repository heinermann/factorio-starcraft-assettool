#include "anim.h"

#include <stdexcept>

#include "../simple-dds-image-reader/ddsreader.hpp"

#define TEST(x) if(!(x)) throw std::exception(#x)

constexpr uint32_t MAKEFOURCC(char a, char b, char c, char d) {
  return a | (b << 8) | (c << 16) | (d << 24);
}

constexpr std::uint32_t ANIM_HDR = MAKEFOURCC('A', 'N', 'I', 'M');

anim_t loadAnim(const std::vector<std::uint8_t>& data) {
  static std::vector<std::uint8_t> dds_work_buffer;
  TEST(data.size() > sizeof(anim_header_t) + sizeof(anim_entry_t) + 1);

  std::size_t read_offset = 0;
  auto read_ptr = [&]<typename T>(const T*) -> const T* {
    const T* result = reinterpret_cast<const T*>(&data[read_offset]);
    read_offset += sizeof(T);
    return result;
  };

  anim_t result;
  const anim_header_t* header = nullptr;
  const anim_entry_t* entry = nullptr;

  header = read_ptr(header);
  TEST(header->filetype == ANIM_HDR);
  TEST(header->version != 0x0101);
  TEST(header->entries == 1);

  entry = read_ptr(entry);
  TEST(entry->frames > 0);

  result.width = entry->grpWidth;
  result.height = entry->grpHeight;

  std::uint16_t texw = entry->imgs[0].texWidth;
  std::uint16_t texh = entry->imgs[0].texHeight;

  // Load DDS files
  for (int i = 0; i < header->layers; ++i) {
    const anim_img_t& img = entry->imgs[i];
    if (img.ptr == 0) continue;

    if (img.texWidth != texw || img.texHeight != texh) {
      std::cerr << "Warning: Texture size mismatch: " << header->layernames[i] << std::endl;
    }

    dds_work_buffer.clear();
    dds_work_buffer.assign(&data[img.ptr], &data[img.ptr + img.size]);

    Image dds = read_dds(dds_work_buffer);
    dds_img_t dds2{ {}, dds.width, dds.height, dds.bpp };
    dds2.data.swap(dds.data); // avoid copy

    result.data.emplace(header->layernames[i], dds2);
  }

  // Load frame data
  result.framedata.reserve(entry->frames);
  read_offset = entry->frameptr;
  for (int i = 0; i < entry->frames; ++i) {
    const frame_t* frameentry = nullptr;
    frameentry = read_ptr(frameentry);
    result.framedata.push_back(*frameentry);
  }
  return result;
}

/*
template <typename T>
std::istream& read(std::istream& is, T& data) {
  return is.read(reinterpret_cast<char*>(&data), sizeof(T));
}*/

/*
// Old version
anim_t loadAnim(std::istream& is) {
  static std::vector<std::uint8_t> dds_work_buffer;

  if (!is.binary) throw std::invalid_argument("Input stream must be binary");

  anim_t result;
  anim_header_t header;
  anim_entry_t entry;

  TEST(read(is, header));

  TEST(header.filetype == ANIM_HDR);
  TEST(header.version != 0x0101);
  TEST(header.entries == 1);

  TEST(read(is, entry));
  TEST(entry.frames > 0);

  result.width = entry.grpWidth;
  result.height = entry.grpHeight;

  std::uint16_t texw = entry.imgs[0].texWidth;
  std::uint16_t texh = entry.imgs[0].texHeight;

  // Load DDS files
  for (int i = 0; i < header.layers; ++i) {
    anim_img_t& img = entry.imgs[i];
    if (img.ptr == 0) continue;

    if (img.texWidth != texw || img.texHeight != texh) {
      std::cerr << "Warning: Texture size mismatch: " << header.layernames[i] << std::endl;
    }

    TEST(is.seekg(img.ptr));

    dds_work_buffer.clear();
    dds_work_buffer.resize(img.size);
    TEST(is.read(reinterpret_cast<char*>(dds_work_buffer.data()), dds_work_buffer.size()));

    Image dds = read_dds(dds_work_buffer);
    dds_img_t dds2{ {}, dds.width, dds.height, dds.bpp };
    dds2.data.swap(dds.data); // avoid copy

    result.data.emplace(header.layernames[i], dds2);
  }

  // Load frame data
  result.framedata.reserve(entry.frames);
  TEST(is.seekg(entry.frameptr));
  for (int i = 0; i < entry.frames; ++i) {
    frame_t frameentry;
    TEST(read(is, frameentry));
    result.framedata.push_back(frameentry);
  }
  return result;
}
*/
