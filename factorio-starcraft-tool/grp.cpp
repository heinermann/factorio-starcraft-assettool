#include "grp.h"

#include <vector>
#include <cstdint>

#include "../simple-dds-image-reader/ddsreader.hpp"
#include "../CImg/CImg.h"

#define TEST(x) if(!(x)) throw std::exception(#x)

using CImg = cimg_library::CImg<std::uint8_t>;

std::vector<CImg> loadGrp(const std::vector<std::uint8_t>& data, const std::optional<std::vector<int>>& requested_indices) {
  thread_local static std::vector<std::uint8_t> dds_work_buffer;
  TEST(data.size() > sizeof(GROUP) + sizeof(FRAME) + 1);

  std::size_t read_offset = 0;
  auto read_ptr = [&]<typename T>(const T*) -> const T* {
    const T* result = reinterpret_cast<const T*>(&data[read_offset]);
    read_offset += sizeof(T);
    return result;
  };

  const GROUP* header = nullptr;
  const FRAME* frame = nullptr;

  header = read_ptr(header);
  TEST(header->dwFlesize > sizeof(GROUP) + sizeof(FRAME) + 1);
  TEST((header->wFlags & 0x0010) == 0);
  TEST(header->wFrames > 0);

  std::vector<CImg> result;

  for (int i = 0, r = 0; i < header->wFrames && read_offset < header->dwFlesize && (!requested_indices || r < requested_indices->size()); ++i) {
    frame = read_ptr(frame);
    
    const std::uint8_t* data_begin = &data[read_offset];
    read_offset += frame->size;

    if (requested_indices && i < requested_indices.value()[r]) continue;
    ++r;

    dds_work_buffer.clear();
    dds_work_buffer.assign(data_begin, &data[read_offset]);

    // Convert the DDS to CImg
    Image dds = read_dds(dds_work_buffer);
    FILE* ftmp = std::tmpfile();
    std::fwrite(dds.data.data(), 1, dds.data.size(), ftmp);
    std::fseek(ftmp, 0, SEEK_SET);

    CImg cimg(unsigned(dds.width), unsigned(dds.height), 1, 4);
    cimg.load_rgba(ftmp, dds.width, dds.height);
    std::fclose(ftmp);

    result.emplace_back(std::move(cimg));
  }
  return result;
}
