#include "convert.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>
#include <algorithm>
#include <cstdio>
#include <array>

#include "image_predefs.h"
#include "anim.h"

#include "../CImg/CImg.h"

using CImg = cimg_library::CImg<std::uint8_t>;
using CImgList = cimg_library::CImgList<std::uint8_t>;

struct supplement_info_t {
  unsigned framecount;
  unsigned dst_frame_width;
  unsigned dst_frame_height;
  int frame_offset_x;
  int frame_offset_y;
  unsigned dst_cells_per_row;

  // Turns stuff
  bool using_turns;
  unsigned num_frames_without_turns;
  unsigned num_frames_extra;
  unsigned rows_per_turn;
  unsigned rows_extra;
  unsigned extra_frames_index;
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
      png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, user_error_ptr, user_error_fn,
        user_warning_fn);
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
      const int color_type = PNG_COLOR_TYPE_RGB_ALPHA;
      const int interlace_type = PNG_INTERLACE_NONE;
      const int compression_type = PNG_COMPRESSION_TYPE_DEFAULT;
      const int filter_method = PNG_FILTER_TYPE_DEFAULT;
      png_set_IHDR(png_ptr, info_ptr, _width, _height, bit_depth, color_type, interlace_type, compression_type, filter_method);
      png_write_info(png_ptr, info_ptr);
      const int byte_depth = bit_depth >> 3;
      const int numChan = 4;
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

CImg get_rotate90(const CImg& img) {
  CImg result(img.height(), img.width(), 1, 4);
  int hm1 = img.height() - 1;
  for (int y = 0; y < img.height(); ++y) {
    for (int x = 0; x < img.width(); ++x) {
      for (int c = 0; c < 4; ++c) {
        result(hm1 - y, x, 0, c) = img(x, y, 0, c);
      }
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

void draw_image_flipped(CImg& dst, int dst_x, int dst_y, CImg& src, int src_x, int src_y, int width, int height) {
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      for (int c = 0; c < 4; ++c) {
        dst(dst_x + x, dst_y + y, 0, c) = src(src_x + width - 1 - x, src_y + height - 1 - y, 0, c);
      }
    }
  }
}

void BGRAtoRGBA(CImg& img) {
  for (int y = 0; y < img.height(); ++y) {
    for (int x = 0; x < img.width(); ++x) {
      std::swap(img(x, y, 0, 0), img(x, y, 0, 2));
    }
  }
}

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

// Zeroing out transparent pixels saves a lot of space on diffuse gfx
void zero_out_transparent(CImg& img) {
  for (int y = 0; y < img.height(); ++y) {
    for (int x = 0; x < img.width(); ++x) {
      if (img(x, y, 0, 3) == 0) {
        img(x, y, 0, 0) = 0;
        img(x, y, 0, 1) = 0;
        img(x, y, 0, 2) = 0;
      }
    }
  }
}

void display(const CImg& img) {
  CImg render(img.width(), img.height(), 1, 3, 0);
  render.draw_image(img, img.get_channel(3), 1, 255);
  render.display();
}

supplement_info_t generate_supplemental_info(const anim_t& anim, const imagedat_info_t& img_info) {
  supplement_info_t result = {};
  result.framecount = anim.framedata.size();
  result.dst_frame_width = anim.width;
  result.dst_frame_height = anim.height;
  result.frame_offset_x = 0;
  result.frame_offset_y = 0;

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
    // something something graphics card texture width limitation for Factorio
    result.dst_cells_per_row = std::min(2048 / result.dst_frame_width, result.framecount);
    if (result.dst_cells_per_row == 0) result.dst_cells_per_row = 1;
  }

  // Get rotation data
  result.using_turns = img_info.gfx_turns;
  if (result.using_turns) {
    result.num_frames_without_turns = result.framecount / 17;
    result.extra_frames_index = result.num_frames_without_turns * 17;
    result.num_frames_extra = result.framecount - result.extra_frames_index;
    result.rows_per_turn = unsigned(std::ceil(double(result.num_frames_without_turns) / result.dst_cells_per_row));
    result.rows_extra = unsigned(std::ceil(double(result.num_frames_extra) / result.dst_cells_per_row));
  }

  return result;
}

CImgList convert_to_img_list(const anim_t& anim, CImg& img, const supplement_info_t& info) {
  CImgList result{ info.framecount, info.dst_frame_width, info.dst_frame_height, 1, 4, 0 };

  for (int i = 0; i < info.framecount; ++i) {
    const frame_t& frame = anim.framedata[i];
    draw_image(result(i), frame.xoffs + info.frame_offset_x, frame.yoffs + info.frame_offset_y, img, frame);
  }

  return result;
}

CImg img_list_to_sheet(const CImgList& frames, const supplement_info_t& info) {
  unsigned new_img_width = info.dst_cells_per_row * info.dst_frame_width;
  unsigned new_img_height = unsigned(std::ceil(double(info.framecount) / info.dst_cells_per_row)) * info.dst_frame_height;

  CImg result{ new_img_width, new_img_height, 1, 4, 0 };
  for (int i = 0; i < frames.size(); ++i) {
    int x = (i % info.dst_cells_per_row) * info.dst_frame_width;
    int y = (i / info.dst_cells_per_row) * info.dst_frame_height;
    result.draw_image(x, y, frames(i));
  }
  return result;
}

CImg img_list_to_turns_sheet(const CImgList& frames, const supplement_info_t& info) {
  unsigned new_img_width = info.dst_cells_per_row * info.dst_frame_width;
  unsigned new_img_height = info.rows_per_turn * info.dst_frame_height * 32;

  CImg result{ new_img_width, new_img_height, 1, 4, 0 };
  for (int turn = 0; turn < 32; ++turn) {
    for (int i = 0; i < info.num_frames_without_turns; ++i) {
      int x = (i % info.dst_cells_per_row) * info.dst_frame_width;
      int y = (turn * info.rows_per_turn + i / info.dst_cells_per_row) * info.dst_frame_height;
      result.draw_image(x, y, frames(i + turn * info.num_frames_without_turns));
    }
  }
  return result;
}

void convert_to_gfxturns(CImgList& frames, CImgList& extras, const supplement_info_t& info) {
  // Create turns sheet
  CImgList newframes{ info.num_frames_without_turns * 32 };
  for (int i = 0; i < info.num_frames_without_turns; ++i) {
    for (int turn = 0; turn < 17; ++turn) {
      newframes(turn * info.num_frames_without_turns + i).swap(frames(i * 17 + turn));
    }

    // Mirror images for missing turns
    for (int turn = 17; turn < 32; ++turn) {
      newframes(turn * info.num_frames_without_turns + i) = newframes((32 - turn) * info.num_frames_without_turns + i).get_mirror("x");
    }
  }

  // Create extra sheet
  for (int i = info.num_frames_without_turns * 17; i < frames.size(); ++i) {
    extras.insert(CImg::empty());
    extras.back().swap(frames(i));
  }

  frames.swap(newframes);
}

CImgList create_shadows(const CImgList& input, const supplement_info_t& info) {
  CImgList result;
  for (int turn = 0; turn < 32; ++turn) {
    int shadow_turn = (turn - 8 + 32) % 32;
    for (int i = 0; i < info.num_frames_without_turns; ++i) {
      const CImg& input_img = input(shadow_turn * info.num_frames_without_turns + i);
      CImg shadow = get_rotate90(input_img);
      mask_to_black(shadow);
      shadow.resize(shadow.width() * 1.4, shadow.height() * 0.8);

      result.insert(std::move(shadow));
    }
  }
  return std::move(result);
}

void convert_anim(const std::vector<std::uint8_t>& anim_data, const imagedat_info_t& img_info) {
  anim_t anim = loadAnim(anim_data);
  supplement_info_t anim_info = generate_supplemental_info(anim, img_info);

  std::unordered_map<std::string, CImg> output_sheets;

  // Convert to lists
  for (auto& sheet : anim.sheets) {
    BGRAtoRGBA(sheet.second);

    //convert_to_uniform_sheet(anim, sheet.second, anim_info);
    CImgList frames = convert_to_img_list(anim, sheet.second, anim_info);

    if (anim_info.using_turns) {
      CImgList extras;
      convert_to_gfxturns(frames, extras, anim_info);

      if (sheet.first == "diffuse" && !img_info.draw_as_glow && !img_info.draw_as_shadow) {
        CImgList shadows = create_shadows(frames, anim_info);
        
        supplement_info_t shadow_info = anim_info;
        shadow_info.dst_frame_height = anim_info.dst_frame_width * 0.8;
        shadow_info.dst_frame_width = anim_info.dst_frame_height * 1.4;
        shadow_info.dst_cells_per_row = std::min(2048 / shadow_info.dst_frame_width, shadow_info.framecount);
        shadow_info.rows_per_turn = unsigned(std::ceil(double(shadow_info.num_frames_without_turns) / shadow_info.dst_cells_per_row));

        CImg shadow_sheet = img_list_to_turns_sheet(shadows, anim_info);
        output_sheets.emplace("shadow", std::move(shadow_sheet));
      }

      CImg result_sheet = img_list_to_turns_sheet(frames, anim_info);
      output_sheets.emplace(sheet.first, std::move(result_sheet));

      if (!extras.is_empty()) {
        supplement_info_t extra_info = anim_info;
        extra_info.framecount = extras.size();

        CImg extras_sheet = img_list_to_sheet(extras, extra_info);
        output_sheets.emplace("extra_" + sheet.first, std::move(extras_sheet));
      }
    }
    else {
      CImg result_sheet = img_list_to_sheet(frames, anim_info);
      output_sheets.emplace(sheet.first, std::move(result_sheet));
    }
  }

  if (output_sheets.contains("teamcolor")) {
    output_sheets["teamcolor"] = output_sheets["diffuse"] & output_sheets["teamcolor"];
  }

  // Write output PNGs
  std::array<char, 128> filename;
  std::cerr << "Writing ID " << img_info.id << ": ";
  for (auto& sheet : output_sheets) {
    std::cerr << sheet.first << ", ";
    std::snprintf(filename.data(), filename.size(), "main_%03d_%s.png", img_info.id, sheet.first.c_str());
    zero_out_transparent(sheet.second);
    cimg_library::save_png(sheet.second, filename.data());
    //sheet.second.save_png(filename.data());
  }
  std::cerr << std::endl;

}
