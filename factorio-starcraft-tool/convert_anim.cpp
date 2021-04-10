#include "convert_anim.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <cstdint>
#include <algorithm>
#include <cstdio>
#include <array>
#include <cassert>

#include "image_predefs.h"
#include "anim.h"

#include "../CImg/CImg.h"

using CImg = cimg_library::CImg<std::uint8_t>;
using CImgList = cimg_library::CImgList<std::uint8_t>;

struct supplement_info_t {
  imagedat_info_t img;

  unsigned framecount;
  unsigned dst_frame_width;
  unsigned dst_frame_height;
  int frame_offset_x;
  int frame_offset_y;
  unsigned dst_cells_per_row;

  // Turns stuff
  bool using_turns;
  unsigned rows_per_turn;
};

struct rect_t {
  int left, top, right, bottom;
};

namespace cimg_library {
  extern "C" {
    void save_png(const CImg<std::uint8_t> img, const char* const filename) {
      int _width = img.width();
      int _height = img.height();
      int _depth = img.depth();   // expected to be 1
      int _spectrum = img.spectrum();
      const uint8_t* _data = img.data();
      bool _is_shared = img.is_shared();

      auto pixel_type = []() { return "uint8_t"; };

      if (!filename)
        throw std::exception("save_png(): Specified filename is (null).");

      if (img.is_empty()) { cimg::fempty(0, filename); return; }

      const char* nfilename = filename;
      std::FILE* nfile = cimg::fopen(nfilename, "wb");

      // Setup PNG structures for write
      png_voidp user_error_ptr = 0;
      png_error_ptr user_error_fn = 0, user_warning_fn = 0;
      png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, user_error_ptr, user_error_fn, user_warning_fn);
      if (!png_ptr) {
        cimg::fclose(nfile);
        throw CImgIOException(_cimg_instance
          "save_png(): Failed to initialize 'png_ptr' structure when saving file '%s'.",
          cimg_instance,
          nfilename ? nfilename : "(FILE*)");
      }
      png_infop info_ptr = png_create_info_struct(png_ptr);
      if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, (png_infopp)0);
        cimg::fclose(nfile);
        throw CImgIOException(_cimg_instance
          "save_png(): Failed to initialize 'info_ptr' structure when saving file '%s'.",
          cimg_instance,
          nfilename ? nfilename : "(FILE*)");
      }
      png_init_io(png_ptr, nfile);

      const int bit_depth = 8;
      int color_type;
      switch (img.spectrum()) {
      case 1: color_type = PNG_COLOR_TYPE_GRAY; break;
      case 2: color_type = PNG_COLOR_TYPE_GRAY_ALPHA; break;
      case 3: color_type = PNG_COLOR_TYPE_RGB; break;
      default: color_type = PNG_COLOR_TYPE_RGB_ALPHA;
      }

      const int interlace_type = PNG_INTERLACE_NONE;
      const int compression_type = PNG_COMPRESSION_TYPE_DEFAULT;
      const int filter_method = PNG_FILTER_TYPE_DEFAULT;
      png_set_IHDR(png_ptr, info_ptr, _width, _height, bit_depth, color_type, interlace_type, compression_type, filter_method);
      png_write_info(png_ptr, info_ptr);
      const int byte_depth = bit_depth >> 3;
      const int numChan = img.spectrum() > 4 ? 4 : img.spectrum();
      const int pixel_bit_depth_flag = numChan * (bit_depth - 1);

      // Allocate Memory for Image Save and Fill pixel data
      png_bytep* const imgData = new png_byte * [_height];
      for (unsigned int row = 0; row < _height; ++row) imgData[row] = new png_byte[byte_depth * numChan * _width];
      const std::uint8_t* pC0 = img.data(0, 0, 0, 0);
      switch (pixel_bit_depth_flag) {
      case 7: { // Gray 8-bit
        cimg_forY(img, y) {
          unsigned char* ptrd = imgData[y];
          cimg_forX(img, x)* (ptrd++) = (unsigned char)*(pC0++);
        }
      } break;
      case 14: { // Gray w/ Alpha 8-bit
        const std::uint8_t* pC1 = img.data(0, 0, 0, 1);
        cimg_forY(img, y) {
          unsigned char* ptrd = imgData[y];
          cimg_forX(img, x) {
            *(ptrd++) = (unsigned char)*(pC0++);
            *(ptrd++) = (unsigned char)*(pC1++);
          }
        }
      } break;
      case 21: { // RGB 8-bit
        const std::uint8_t* pC1 = img.data(0, 0, 0, 1), * pC2 = img.data(0, 0, 0, 2);
        cimg_forY(img, y) {
          unsigned char* ptrd = imgData[y];
          cimg_forX(img, x) {
            *(ptrd++) = (unsigned char)*(pC0++);
            *(ptrd++) = (unsigned char)*(pC1++);
            *(ptrd++) = (unsigned char)*(pC2++);
          }
        }
      } break;
      case 28: { // RGB x/ Alpha 8-bit
        const std::uint8_t* pC1 = img.data(0, 0, 0, 1), * pC2 = img.data(0, 0, 0, 2), * pC3 = img.data(0, 0, 0, 3);
        cimg_forY(img, y) {
          unsigned char* ptrd = imgData[y];
          cimg_forX(img, x) {
            *(ptrd++) = (unsigned char)*(pC0++);
            *(ptrd++) = (unsigned char)*(pC1++);
            *(ptrd++) = (unsigned char)*(pC2++);
            *(ptrd++) = (unsigned char)*(pC3++);
          }
        }
      } break;
      default:
        cimg::fclose(nfile);
        throw CImgIOException(_cimg_instance
          "save_png(): Encountered unknown fatal error in libpng when saving file '%s'.",
          cimg_instance,
          nfilename ? nfilename : "(FILE*)");
      }
      png_set_compression_level(png_ptr, 1);
      png_set_compression_buffer_size(png_ptr, 32768);
      png_set_filter(png_ptr, PNG_FILTER_TYPE_BASE, PNG_FILTER_NONE);
      png_write_image(png_ptr, imgData);
      png_write_end(png_ptr, info_ptr);
      png_destroy_write_struct(&png_ptr, &info_ptr);

      // Deallocate Image Write Memory
      cimg_forY(img, n) delete[] imgData[n];
      delete[] imgData;

      cimg::fclose(nfile);
    }
  }
}

CImg get_rotate90_black(const CImg& img) {
  CImg result(img.height(), img.width(), 1, 2);
  int hm1 = img.height() - 1;
  for (int y = 0; y < img.height(); ++y) {
    for (int x = 0; x < img.width(); ++x) {
      result(hm1 - y, x, 0, 0) = 0;
      result(hm1 - y, x, 0, 1) = img(x, y, 0, 3);
    }
  }
  return result;
}

void draw_image(CImg& dst, int dst_x, int dst_y, CImg& src, int src_x, int src_y, int width, int height) {
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      for (int c = 0; c < 4; ++c) {
        dst(dst_x + x, dst_y + y, 0, c) = src(src_x + x, src_y + y, 0, c);
      }
    }
  }
}

void draw_image(CImg& dst, int dst_x, int dst_y, CImg& src, const frame_t& src_frame) {
  draw_image(dst, dst_x, dst_y, src, src_frame.x, src_frame.y, src_frame.width, src_frame.height);
}

void BGRAtoRGBA(CImg& img) {
  cimg_forXY(img, x, y) {
    std::swap(img(x, y, 0, 0), img(x, y, 0, 2));
  }
}

/*
void mask_to_black(CImg& img) {
  for (int y = 0; y < img.height(); ++y) {
    for (int x = 0; x < img.width(); ++x) {
      img(x, y, 0, 0) = 0;
      img(x, y, 0, 1) = 0;
      img(x, y, 0, 2) = 0;
      //img(x, y, 0, 3) = img(x, y, 0, 3) ? 255 : 0; // outputs should have transparency still
    }
  }
}
*/
// Zeroing out transparent pixels saves a lot of space on all sheets
void zero_out_transparent(CImg& img) {
  cimg_forXY(img, x, y) {
    if (img(x, y, 0, img.spectrum() - 1) != 0) continue;

    for (int c = 0; c < img.spectrum() - 1; ++c)
      img(x, y, 0, c) = 0;
  }
}

unsigned get_cells_per_row(const CImgList& imglist) {
  // something something graphics card texture width limitation for Factorio
  return std::clamp(2048 / imglist(0).width(), 1, int(imglist.size()));
}

unsigned get_cells_per_row(const supplement_info_t& info) {
  // something something graphics card texture width limitation for Factorio
  unsigned framecount = info.using_turns ? info.framecount / 17 : info.framecount;
  return std::clamp(2048 / info.dst_frame_width, 1U, framecount);
}

supplement_info_t generate_supplemental_info(const anim_t& anim, const imagedat_info_t& img_info) {
  supplement_info_t result = {};
  result.img = img_info;
  result.framecount = anim.framedata.size();
  result.dst_frame_width = anim.width;
  result.dst_frame_height = anim.height;
  result.frame_offset_x = 0;
  result.frame_offset_y = 0;
  result.using_turns = img_info.gfx_turns_frames > 0;

  // Fixup graphic for negative offsets
  for (const frame_t& f : anim.framedata) {
    result.dst_frame_width = std::max(result.dst_frame_width, unsigned(f.xoffs + f.width));
    result.dst_frame_height = std::max(result.dst_frame_height, unsigned(f.yoffs + f.height));
    result.frame_offset_x = std::max(result.frame_offset_x, -f.xoffs);
    result.frame_offset_y = std::max(result.frame_offset_y, -f.yoffs);
  }
  result.dst_frame_width += result.frame_offset_x;
  result.dst_frame_height += result.frame_offset_y;

  if (img_info.vertical_frames) {
    result.dst_cells_per_row = 1;
  }
  else {
    result.dst_cells_per_row = get_cells_per_row(result);
  }

  // Get rotation data
  if (result.using_turns) {
    result.rows_per_turn = unsigned(std::ceil(double(result.img.gfx_turns_frames) / result.dst_cells_per_row));
  }

  return result;
}

CImgList convert_to_img_list(const anim_t& anim, CImg& img, const supplement_info_t& info) {
  CImgList result(info.framecount, info.dst_frame_width, info.dst_frame_height, 1, 4, 0);

  for (int i = 0; i < info.framecount; ++i) {
    const frame_t& frame = anim.framedata[i];
    draw_image(result(i), frame.xoffs + info.frame_offset_x, frame.yoffs + info.frame_offset_y, img, frame);
  }

  return result;
}

CImg img_list_to_sheet(const CImgList& frames, bool draw_indexes = false) {
  unsigned cells_per_row = get_cells_per_row(frames);
  int frame_width = frames(0).width();
  int frame_height = frames(0).height();

  unsigned new_img_width = cells_per_row * frame_width;
  unsigned new_img_height = unsigned(std::ceil(double(frames.size()) / cells_per_row)) * frame_height;

  CImg result(new_img_width, new_img_height, 1, 4, 0);
  for (int i = 0; i < frames.size(); ++i) {
    int x = (i % cells_per_row) * frame_width;
    int y = (i / cells_per_row) * frame_height;
    result.draw_image(x, y, frames(i));
    
    if (draw_indexes) {
      std::string txt = std::to_string(i);
      constexpr std::uint8_t foreground[4] = { 255, 255, 255, 255 };
      constexpr std::uint8_t background[4] = { 0, 0, 0, 0 };
      result.draw_text(x, y, txt.c_str(), foreground, background, 1, 22);
    }
  }
  return result;
}

CImg img_list_to_turns_sheet(const CImgList& frames, const supplement_info_t& info) {
  unsigned new_img_width = info.dst_cells_per_row * info.dst_frame_width;
  unsigned new_img_height = info.rows_per_turn * info.dst_frame_height * 32;

  CImg result(new_img_width, new_img_height, 1, unsigned(frames(0).spectrum()), 0);
  for (int turn = 0; turn < 32; ++turn) {
    for (int i = 0; i < info.img.gfx_turns_frames; ++i) {
      int x = (i % info.dst_cells_per_row) * info.dst_frame_width;
      int y = (turn * info.rows_per_turn + i / info.dst_cells_per_row) * info.dst_frame_height;
      result.draw_image(x, y, frames(i + turn * info.img.gfx_turns_frames));
    }
  }
  return result;
}

CImgList convert_to_gfxturns(const CImgList& frames, const supplement_info_t& info) {
  // Create turns sheet
  CImgList newframes(info.img.gfx_turns_frames * 32);
  for (int i = 0; i < info.img.gfx_turns_frames; ++i) {
    for (int turn = 0; turn < 17; ++turn) {
      newframes(turn * info.img.gfx_turns_frames + i) = frames(i * 17 + turn);
    }

    // Mirror images for missing turns
    for (int turn = 17; turn < 32; ++turn) {
      newframes(turn * info.img.gfx_turns_frames + i) = newframes((32 - turn) * info.img.gfx_turns_frames + i).get_mirror("x");
    }
  }
  return newframes;
}

CImgList create_shadows(const CImgList& input, const supplement_info_t& info) {
  CImgList result;
  for (int turn = 0; turn < 32; ++turn) {
    int shadow_turn = (turn - 8 + 32) % 32;
    for (int i = 0; i < info.img.gfx_turns_frames; ++i) {
      const CImg& input_img = input(shadow_turn * info.img.gfx_turns_frames + i);
      CImg shadow = get_rotate90_black(input_img);
      //mask_to_black(shadow);
      shadow.resize(shadow.width() * 1.4, shadow.height() * 0.8);

      result.insert(std::move(shadow));
    }
  }
  return std::move(result);
}


void frames_convert_unprocessed(const std::string& name, const CImgList& frames, const supplement_info_t& info, std::unordered_map<std::string, CImg>& output_sheets) {
  output_sheets.emplace(name, img_list_to_sheet(frames));
}

void frames_convert_gfxturns(const std::string& name, const CImgList& frames, const supplement_info_t& info, std::unordered_map<std::string, CImg>& output_sheets) {
  CImgList turn_frames = convert_to_gfxturns(frames, info);
  output_sheets.emplace(name, img_list_to_turns_sheet(turn_frames, info));

  if (name == "diffuse" && !info.img.draw_as_glow && !info.img.draw_as_shadow) {
    CImgList shadows = create_shadows(turn_frames, info);

    supplement_info_t shadow_info = info;
    shadow_info.dst_frame_width = info.dst_frame_height * 1.4;
    shadow_info.dst_frame_height = info.dst_frame_width * 0.8;
    shadow_info.dst_cells_per_row = get_cells_per_row(shadow_info);
    shadow_info.rows_per_turn = unsigned(std::ceil(double(shadow_info.img.gfx_turns_frames) / shadow_info.dst_cells_per_row));

    output_sheets.emplace("shadow", img_list_to_turns_sheet(shadows, shadow_info));
  }
  else if (name == "teamcolor") {
    output_sheets["teamcolor"] = output_sheets["diffuse"] & output_sheets["teamcolor"];
  }
}

struct frames_convert_extra  {
  const std::vector<unsigned> frame_ids;
  const std::string prefix;

  frames_convert_extra(const std::vector<unsigned>& frame_ids, const std::string& prefix)
    : frame_ids(frame_ids)
    , prefix(prefix)
  {}

  void operator ()(const std::string& name, const CImgList& frames, const supplement_info_t& info, std::unordered_map<std::string, CImg>& output_sheets) {
    CImgList extra_frames{};
    for (unsigned id : frame_ids) {
      extra_frames.push_back(frames(id));
    }

    output_sheets.emplace(prefix + "_" + name, img_list_to_sheet(extra_frames));
    if (name == "teamcolor") {
      output_sheets[prefix + "_teamcolor"] = output_sheets[prefix + "_diffuse"] & output_sheets[prefix + "_teamcolor"];
    }
  }
};

frames_convert_extra frames_convert_extra_turns(const std::vector<unsigned>& frame_ids, const std::string& prefix) {
  std::vector<unsigned> ids_with_turns;
  for (unsigned id : frame_ids) {
    ids_with_turns.push_back(id * 17);
  }
  return frames_convert_extra{ ids_with_turns, prefix };
}

std::unordered_map<int, std::vector<std::function<decltype(frames_convert_unprocessed)>>> extra_processes{
  {8, {frames_convert_extra_turns({ 8, 9, 10, 11, 12, 13 }, "burrow"), frames_convert_extra({238, 239, 240, 241, 242, 243, 244, 245}, "death")} },
  {13, {frames_convert_extra_turns({ 8, 9, 10, 11 }, "death"), frames_convert_extra_turns({12, 13, 14, 15, 16}, "burrow")} },
  {17, {frames_convert_extra_turns({ 10, 11, 12, 13, 14, 15, 16, 17 }, "death"), frames_convert_extra_turns({18, 19, 20, 21, 22}, "burrow")} },
  {29, {frames_convert_extra({ 204, 205, 206, 207, 208, 209, 210, 211 }, "death"), frames_convert_extra_turns({13, 14, 15, 16, 17}, "burrow")} },
  {50, {frames_convert_extra({255, 256, 257, 258, 259, 260, 261, 262, 263, 264}, "death")} },
  {54, {frames_convert_extra_turns({ 12, 13, 14, 15, 16 }, "burrow"), frames_convert_extra({289, 290, 291, 292, 293, 294, 295}, "death")} },
  {122, {frames_convert_extra({408, 409, 410, 411, 412, 413, 414}, "death")} },
  {126, {frames_convert_extra({289, 290, 291, 292, 293, 294, 295}, "death")} },
  {151, {frames_convert_extra({221, 222, 223, 224, 225, 226, 227}, "death")} },
  {228, {frames_convert_extra({221, 222, 223, 224, 225, 226, 227, 228}, "death")} },
  {239, {frames_convert_extra({221, 222, 223, 224, 225, 226, 227, 228}, "death")} },
  {239, {frames_convert_extra({221, 222, 223, 224, 225, 226, 227, 228}, "death")} },
  {338, {frames_convert_extra({153, 154, 155, 156, 157, 158, 159, 160}, "death")} },
  {340, {frames_convert_extra({187, 188, 189, 190, 191, 192, 193, 194}, "death")} },
  {342, {frames_convert_extra({204, 205, 206, 207, 208, 209, 210, 211}, "death")} },
  {944, {frames_convert_extra({222, 223, 224, 225, 226, 227, 228, 229}, "death")} },
  {952, {frames_convert_extra({204, 205, 206, 207, 208, 209, 210, 211}, "death")} },
  {954, {frames_convert_extra({205, 206, 207, 208, 209, 210, 211, 212, 213}, "death")} },
  {956, {frames_convert_extra({136, 137, 138, 139, 140, 141, 142, 143}, "death")} }
};

void convert_anim(const std::vector<std::uint8_t>& anim_data, const imagedat_info_t& img_info) {
  anim_t anim = loadAnim(anim_data);
  supplement_info_t anim_info = generate_supplemental_info(anim, img_info);

  std::unordered_map<std::string, CImg> output_sheets;

  // Convert to lists
  for (auto& sheet : anim.sheets) {
    BGRAtoRGBA(sheet.second);

    CImgList frames = convert_to_img_list(anim, sheet.second, anim_info);

    if (anim_info.using_turns) {
      //if (sheet.first == "diffuse") {
      //  output_sheets.emplace("frame_map", img_list_to_sheet(frames, true));
      //}

      frames_convert_gfxturns(sheet.first, frames, anim_info, output_sheets);
    }
    else {
      frames_convert_unprocessed(sheet.first, frames, anim_info, output_sheets);
    }

    if (extra_processes.contains(img_info.id)) {
      for (const auto& fn : extra_processes[img_info.id]) {
        fn(sheet.first, frames, anim_info, output_sheets);
      }
    }
  }

  // Write output PNGs
  std::array<char, 128> filename;
  std::cerr << "Writing ID " << img_info.id << ": ";
  for (auto& sheet : output_sheets) {
    std::cerr << sheet.first << ", ";
    std::snprintf(filename.data(), filename.size(), "graphics/main_%03d_%s.png", img_info.id, sheet.first.c_str());
    zero_out_transparent(sheet.second);
    cimg_library::save_png(sheet.second, filename.data());
    //sheet.second.save_png(filename.data());
  }
  std::cerr << std::endl;

}
