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



/*
void convert_to_uniform_sheet(const anim_t& anim, CImg& img, const supplement_info_t& info) {
  unsigned new_img_width = info.dst_cells_per_row * info.dst_frame_width;
  unsigned new_img_height = unsigned(std::ceil(double(info.framecount) / info.dst_cells_per_row)) * info.dst_frame_height;

  CImg newImg{ new_img_width, new_img_height, 1, 4, 0};
  for (int i = 0; i < info.framecount; ++i) {
    const frame_t& frame = anim.framedata[i];

    int dstx = (i % info.dst_cells_per_row) * info.dst_frame_width + frame.xoffs + info.frame_offset_x;
    int dsty = (i / info.dst_cells_per_row) * info.dst_frame_height + frame.yoffs + info.frame_offset_y;

    draw_image(newImg, dstx, dsty, img, frame);
  }

  img.swap(newImg);
}
*/

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
      CImg shadow = input(shadow_turn * info.num_frames_without_turns + i).get_rotate(90);
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

      if (sheet.first == "diffuse") {
        CImgList shadows = create_shadows(frames, anim_info);
        
        supplement_info_t shadow_info = anim_info;
        shadow_info.dst_frame_height *= 0.8;
        shadow_info.dst_frame_width *= 1.4;
        shadow_info.dst_cells_per_row = std::min(2048 / shadow_info.dst_frame_width, shadow_info.framecount);


        CImg shadow_sheet = img_list_to_turns_sheet(shadows, anim_info);
        output_sheets.emplace("shadow", std::move(shadow_sheet));
      }

      CImg result_sheet = img_list_to_turns_sheet(frames, anim_info);
      output_sheets.emplace(sheet.first, std::move(result_sheet));

      if (!extras.is_empty()) {
        CImg extras_sheet = img_list_to_sheet(extras, anim_info);
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
  for (auto& sheet : output_sheets) {
    std::snprintf(filename.data(), filename.size(), "main_%03d_%s.png", img_info.id, sheet.first.c_str());
    zero_out_transparent(sheet.second);
    sheet.second.save_png(filename.data());
  }
}
