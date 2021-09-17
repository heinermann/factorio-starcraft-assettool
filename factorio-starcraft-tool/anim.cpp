#include "anim.h"

#include <stdexcept>
#include <cstdio>

#include "../simple-dds-image-reader/ddsreader.hpp"
#include "../CImg/CImg.h"

#define TEST(x) if(!(x)) throw std::exception(#x)

constexpr uint32_t MAKEFOURCC(char a, char b, char c, char d) {
  return a | (b << 8) | (c << 16) | (d << 24);
}

constexpr std::uint32_t ANIM_HDR = MAKEFOURCC('A', 'N', 'I', 'M');

using CImg = cimg_library::CImg<std::uint8_t>;

anim_t loadAnim(const std::vector<std::uint8_t>& data) {
  thread_local static std::vector<std::uint8_t> dds_work_buffer;
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
    // Skip the ones we don't care about
    if (std::strncmp(header->layernames[i], "diffuse", 32) != 0 &&
      std::strncmp(header->layernames[i], "teamcolor", 32) != 0 &&
      std::strncmp(header->layernames[i], "emissive", 32) != 0
      //&& std::strncmp(header->layernames[i], "ao_depth", 32) != 0
      //&& std::strncmp(header->layernames[i], "normal", 32) != 0
      ) {
      continue;
    }

    const anim_img_t& img = entry->imgs[i];
    if (img.ptr == 0) continue;

    if (img.texWidth != texw || img.texHeight != texh) {
      std::cerr << "Warning: Texture size mismatch: " << header->layernames[i] << std::endl;
    }

    dds_work_buffer.clear();
    dds_work_buffer.assign(&data[img.ptr], &data[img.ptr + img.size]);

    Image dds = read_dds(dds_work_buffer);
    FILE* ftmp = std::tmpfile();
    std::fwrite(dds.data.data(), 1, dds.data.size(), ftmp);
    std::fseek(ftmp, 0, SEEK_SET);

    CImg cimg(unsigned(dds.width), unsigned(dds.height), 1, 4);
    cimg.load_rgba(ftmp, dds.width, dds.height);
    std::fclose(ftmp);

    result.sheets.emplace_back(header->layernames[i], std::move(cimg));
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
