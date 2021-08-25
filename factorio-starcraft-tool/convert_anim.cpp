#include "convert_anim.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <cstdint>
#include <cmath>
#include <numbers>
#include <algorithm>
#include <cstdio>
#include <array>
#include <cassert>
#include <any>
#include <fstream>

#include "image_predefs.h"
#include "anim.h"
#include "lua_writer.h"

#include "../CImg/CImg.h"
#include "cimg_extensions.h"
#include "cimg_utils.h"

struct rect_t {
  int left, top, right, bottom;
};

struct supplement_info_t {
  imagedat_info_t img;

  unsigned framecount;
  unsigned dst_frame_width;
  unsigned dst_frame_height;
  unsigned dst_cells_per_row;
  int margin_x, margin_y;

  // Turns stuff
  bool using_turns;
  unsigned rows_per_turn;

  bool use_depth;
};

void draw_image(CImg& dst, int dst_x, int dst_y, CImg& src, const frame_t& src_frame) {
  draw_image(dst, dst_x, dst_y, src, src_frame.x, src_frame.y, src_frame.width, src_frame.height);
}

unsigned get_cells_per_row(const CImgList& imglist) {
  // something something graphics card texture width limitation for Factorio
  return std::clamp(4096 / imglist(0).width(), 1, int(imglist.size()));
}

unsigned get_cells_per_row(const supplement_info_t& info) {
  // something something graphics card texture width limitation for Factorio
  unsigned framecount = info.using_turns ? info.framecount / 17 : info.framecount;
  return std::clamp(4096 / info.dst_frame_width, 1U, framecount);
}

supplement_info_t generate_supplemental_info(const anim_t& anim, const imagedat_info_t& img_info, int first_frame, int last_frame) {
  supplement_info_t result = {};
  result.img = img_info;
  result.framecount = unsigned(anim.framedata.size());
  result.dst_frame_width = anim.width;
  result.dst_frame_height = anim.height;

  constexpr int max_int = std::numeric_limits<int>::max();
  rect_t margins = { max_int, max_int, max_int, max_int };
  for (int i = first_frame; i <= last_frame; ++i) {
    const frame_t& f = anim.framedata[i];
    margins.left = std::min(margins.left, int(f.xoffs));    // Note: can be negative
    margins.top = std::min(margins.top, int(f.yoffs));
    margins.right = std::min(margins.right, int(anim.width - (f.xoffs + f.width)));
    margins.bottom = std::min(margins.bottom, int(anim.height - (f.yoffs + f.height)));
  }

  result.margin_x = std::min(margins.left, margins.right);
  result.margin_y = std::min(margins.top, margins.bottom);

  // *2 because extending the gfx to the left by an amount without balancing it on the right will misalign the graphic
  result.dst_frame_width -= result.margin_x * 2;
  result.dst_frame_height -= result.margin_y * 2;

  result.using_turns = img_info.gfx_turns_frames > 0;

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

  result.use_depth = img_info.draw_real_shadow;
  return result;
}

CImgList convert_to_img_list(const anim_t& anim, CImg& img, const supplement_info_t& info) {
  CImgList result(info.framecount, info.dst_frame_width, info.dst_frame_height, 1, 4, 0);

  for (unsigned i = 0; i < info.framecount; ++i) {
    const frame_t& frame = anim.framedata[i];
    draw_image(result(i), frame.xoffs - info.margin_x, frame.yoffs - info.margin_y, img, frame);
  }

  return result;
}

CImg img_list_to_sheet(const CImgList& frames, const supplement_info_t& info, bool draw_indexes = false) {
  unsigned cells_per_row = info.dst_cells_per_row; // get_cells_per_row(frames);
  int frame_width = frames(0).width();
  int frame_height = frames(0).height();

  unsigned new_img_width = cells_per_row * frame_width;
  unsigned new_img_height = unsigned(std::ceil(double(frames.size()) / cells_per_row)) * frame_height;

  CImg result(new_img_width, new_img_height, 1, 4, 0);
  for (unsigned i = 0; i < frames.size(); ++i) {
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
    for (unsigned i = 0; i < info.img.gfx_turns_frames; ++i) {
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
  for (unsigned i = 0; i < info.img.gfx_turns_frames; ++i) {
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
    for (unsigned i = 0; i < info.img.gfx_turns_frames; ++i) {
      const CImg& input_img = input(shadow_turn * info.img.gfx_turns_frames + i);
      CImg shadow = get_rotate90_black(input_img);
      //mask_to_black(shadow);
      shadow.resize(int(shadow.width() * 1.4), int(shadow.height() * 0.8));

      result.insert(std::move(shadow));
    }
  }
  return std::move(result);
}

CImgList create_depth_shadows(const CImgList& input, const supplement_info_t& info) {
  const double sin45 = std::sin(std::numbers::pi / 4);
  const double tan1 = std::tan(1);

  CImgList result;
  for (const CImg& img : input) {
    CImg shadow(img.width()*3, img.height(), 1, 4, 0);

    // Get the bottom of the sprite
    int final_y = 0;
    for (int y = img.height() - 1; y > 0 && final_y == 0; y--) {
      cimg_forX(img, x) {
        if (img(x, y, 0, 3) != 0) {
          final_y = y;
          break;
        }
      }
    }

    // Arbitrary scale, literally no idea how this is determined.
    const double dist_scale = std::max(final_y, img.width());// img.width() / 256.0;

    cimg_forXY(img, x, y) {
      // Project pixel onto real space (x, y, z) using depth map, assuming viewport is 45deg
      int a = img(x, y, 0, 3);
      if (a == 0) continue;
      //if (a <= 52) continue;

      int spr_y = final_y - y;

      double d = (255.0 - a)/255.0 * dist_scale;
      double d_inv = 1.0 * dist_scale - d;
      double y_calc = spr_y - final_y / 2.0;
      //double d_corrected = std::sqrt(d * d - y_calc * y_calc);

      double px = x;
      double py = (spr_y + d) * sin45;
      double pz = std::sqrt(d_inv * d_inv + 1.0 * spr_y * spr_y);

      // Project shadow in real space from the west (z = 0)
      int sx = pz + px;// (pz * tan1) + px;
      int sy = py;
      //int num_px_x = std::ceil(pz * 1.4) - std::floor((pz - 1) * 1.4);

      // Convert back to 2D
      int fx = sx;
      // py = (y + d) * sin45
      // py = y * sin45 + d * sin45
      // y * sin45 = d * sin45 - py
      // y = d - py / sin45
      int fy = shadow.height() - 1 - sy * sin45;

      // Fill the spaces the pixel probably would have covered with shadow
      for (int ix = std::floor(pz - 1) + px; ix <= std::ceil(pz) + px; ++ix) {
        add_alpha_px(shadow, ix, fy, 255);
        add_alpha_px(shadow, ix - 1, fy, 64);
        add_alpha_px(shadow, ix + 1, fy, 64);
        add_alpha_px(shadow, ix, fy - 1, 64);
        add_alpha_px(shadow, ix, fy + 1, 64);
      }
    }
    result.insert(std::move(shadow));
  }
  return std::move(result);
}


void frames_convert_unprocessed(const std::string& name, const CImgList& frames, const supplement_info_t& info, std::unordered_map<std::string, CImg>& output_sheets) {
  output_sheets.emplace(name, img_list_to_sheet(frames, info));

  if (name == "teamcolor") {
    output_sheets["teamcolor"] = output_sheets["diffuse"] & output_sheets["teamcolor"];
  }
  else if (name == "ao_depth" && info.use_depth) {
    CImgList shadow_frames = create_depth_shadows(frames, info);
    output_sheets["dshadow"] = img_list_to_sheet(shadow_frames, info);
  }
}

void frames_convert_gfxturns(const std::string& name, const CImgList& frames, const supplement_info_t& info, std::unordered_map<std::string, CImg>& output_sheets) {
  CImgList turn_frames = convert_to_gfxturns(frames, info);
  output_sheets.emplace(name, img_list_to_turns_sheet(turn_frames, info));

  if (name == "diffuse" && !info.img.draw_as_glow && !info.img.draw_as_shadow) {
    CImgList shadows = create_shadows(turn_frames, info);

    supplement_info_t shadow_info = info;
    shadow_info.dst_frame_width = unsigned(info.dst_frame_height * 1.4);
    shadow_info.dst_frame_height = unsigned(info.dst_frame_width * 0.8);
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

    output_sheets.emplace(prefix + "_" + name, img_list_to_sheet(extra_frames, info));
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

using anymap = std::map<std::string, std::any>;
using anyvector = std::vector<std::any>;

void convert_anim(const std::vector<std::uint8_t>& anim_data, const imagedat_info_t& img_info, const std::string& out_dir, bool is_low) {
  anim_t anim = loadAnim(anim_data);
  if (is_low) {
    for (frame_t& frame : anim.framedata) {
      frame.height /= 2;
      frame.width /= 2;
      frame.x /= 2;
      frame.y /= 2;
      frame.xoffs /= 2;
      frame.yoffs /= 2;
    }
    anim.width /= 2;
    anim.height /= 2;
  }

  supplement_info_t anim_info = generate_supplemental_info(anim, img_info, 0, anim.framedata.size() - 1);

  std::unordered_map<std::string, CImg> output_sheets;

  // Convert to lists
  for (auto& sheet : anim.sheets) {
    BGRAtoRGBA(sheet.second);

    if (sheet.first == "ao_depth") {
      const CImg& diffuse = std::find_if(anim.sheets.begin(), anim.sheets.end(), [](const auto& it) { return it.first == "diffuse"; })->second;
      cimg_forXY(diffuse, x, y) {
        sheet.second(x, y, 0, 3) = std::min(sheet.second(x, y, 0, 3), diffuse(x, y, 0, 3));
      }
    }

    CImgList frames = convert_to_img_list(anim, sheet.second, anim_info);

    if (anim_info.using_turns) {
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
  for (auto& sheet : output_sheets) {
    //if (sheet.first == "ao_depth") continue;

    std::snprintf(filename.data(), filename.size(), "%s/main_%03d_%s.png", out_dir.c_str(), img_info.id, sheet.first.c_str());
    zero_out_transparent(sheet.second);
    cimg_library::save_png(sheet.second, filename.data());
  }

  // Write lua info
  std::snprintf(filename.data(), filename.size(), "__starcraft__/%s/main_%03d_diffuse.png", out_dir.c_str(), img_info.id);
  
  anymap lua_data = {
    {"filename", std::string(filename.data())},
    {"size", anyvector{ anim_info.dst_frame_width, anim_info.dst_frame_height }},
    {"frame_count", anim_info.framecount},
    {"line_length", anim_info.dst_cells_per_row}
  };

  if (!is_low) lua_data["scale"] = 0.5;

  std::snprintf(filename.data(), filename.size(), "%s/main_%03d.lua", out_dir.c_str(), img_info.id);
  write_lua_file(filename.data(), lua_data);
}
