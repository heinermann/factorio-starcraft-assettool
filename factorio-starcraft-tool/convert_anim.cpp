#include "convert_anim.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <array>
#include <cassert>
#include <any>
#include <fstream>
#include <future>

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

void frames_convert_unprocessed(const std::string& name, const CImgList& frames, const supplement_info_t& info, std::unordered_map<std::string, CImg>& output_sheets) {
  output_sheets.emplace(name, img_list_to_sheet(frames, info));

  if (name == "teamcolor") {
    output_sheets["teamcolor"] = output_sheets["diffuse"] & output_sheets["teamcolor"];
  }
}

// Function to split the sheets that are too large
void split_sheet_result(std::unordered_map<std::string, CImg>& sheets, const supplement_info_t& info) {
  for (auto& [name, sheet] : sheets) {
    if (sheet.height() <= 8192) continue;

    int vframes_per_page = 8192 / info.dst_frame_height;
    int page_height = vframes_per_page * info.dst_frame_height;
    int width = sheet.width();

    for (int y = 0, i = 1; y < sheet.height(); y += page_height, ++i) {
      int new_height = std::min(sheet.height() - y, page_height);
      CImg new_img(width, new_height, 1, sheet.spectrum(), 0);

      draw_image(new_img, 0, 0, sheet, 0, y, width, new_height);
      sheets.emplace(name + "_" + std::to_string(i), std::move(new_img));
    }

    sheets.erase(name);
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

void create_depth_normal(anim_t &anim) {
  std::unordered_map<std::string, CImg> sheet_lookup(anim.sheets.begin(), anim.sheets.end());
  if (!sheet_lookup.contains("ao_depth") || !sheet_lookup.contains("normal")) return;

  const CImg& ao_depth = sheet_lookup.at("ao_depth");
  const CImg& diffuse = sheet_lookup.at("diffuse");
  CImg& normal = sheet_lookup.at("normal");

  // Combine the depth with normal and diffuse alpha
  cimg_forXY(ao_depth, x, y) {
    if (diffuse(x, y, 0, 3) < 32) {
      normal(x, y, 0, 0) = 0;
      normal(x, y, 0, 1) = 0;
      normal(x, y, 0, 2) = 0;
      normal(x, y, 0, 3) = 0;
    }
    else {
      normal(x, y, 0, 1) = ao_depth(x, y, 0, 3);
      normal(x, y, 0, 2) = normal(x, y, 0, 3);
      normal(x, y, 0, 3) = diffuse(x, y, 0, 3);
    }
  }

  anim.sheets.push_back(std::make_pair(std::string("depth_normal"), normal));
}

std::promise<CImgList> warp_texture_promise[2];
std::shared_future<CImgList> warp_texture_future[2] = {
  warp_texture_promise[0].get_future(),
  warp_texture_promise[1].get_future()
};

void create_warp_anim(const std::string& name, const CImgList& frames, const supplement_info_t& info, std::unordered_map<std::string, CImg>& output_sheets, bool is_low) {
  CImg target = frames(0);
  CImgList warp_texture_frames = warp_texture_future[is_low].get();

  CImgList warp_anim;

  // Create warp-texture part of animation
  //constexpr double step = 1.0 / 14;
  constexpr double step = 1.0 / 20;
  double fade_amount = 0.1;
  for (CImg& warp_frame : warp_texture_frames) {
    //int new_size = std::max({ target.width(), target.height() });
    warp_frame.resize(target.width(), target.height(), 1, 3, 1);

    CImg new_frame = target;
    cimg_forXY(new_frame, x, y) {
      std::uint8_t& r = warp_frame(x, y, 0, 0);
      std::uint8_t& g = warp_frame(x, y, 0, 1);
      std::uint8_t& b = warp_frame(x, y, 0, 2);
      std::uint8_t& a = new_frame(x, y, 0, 3);

      new_frame(x, y, 0, 0) = std::min(64 * fade_amount + r * fade_amount, 255.0);
      new_frame(x, y, 0, 1) = std::min(64 * fade_amount + g * fade_amount, 255.0);
      new_frame(x, y, 0, 2) = std::min(64 * fade_amount + b * fade_amount, 255.0);
      if (a > 128)
        new_frame(x, y, 0, 3) = std::min(128 * fade_amount + a * fade_amount, 255.0);
    }
    fade_amount += step;
    warp_anim.push_back(new_frame);
  }

  // Create fade-in part of animation
  for (int i = 16; i > 0; i--) {
    CImg new_frame = target;
    double scale = std::pow(std::log(i) / std::log(16), 1.5);
    cimg_forXY(new_frame, x, y) {
      std::uint8_t& r = new_frame(x, y, 0, 0);
      std::uint8_t& g = new_frame(x, y, 0, 1);
      std::uint8_t& b = new_frame(x, y, 0, 2);
      std::uint8_t& a = new_frame(x, y, 0, 3);

      r = 255;
      g = 255;
      b = 255;
      if (a > 0) {
        a = std::min(a * scale, 255.0);
      }
    }
    warp_anim.push_back(new_frame);
  }

  supplement_info_t new_info = info;
  new_info.framecount = warp_anim.size();
  new_info.dst_cells_per_row = get_cells_per_row(warp_anim);
  output_sheets.emplace(name + "_warp_in", img_list_to_sheet(warp_anim, new_info));
}

std::unordered_map<std::string, CImg> convert_to_output(anim_t& anim, const imagedat_info_t& img_info, const supplement_info_t& anim_info, bool is_low) {
  std::unordered_map<std::string, CImg> output_sheets;
  for (auto& sheet : anim.sheets) {
    BGRAtoRGBA(sheet.second);

    if (sheet.first == "ao_depth" || sheet.first == "normal") {
      continue;
    }

    CImgList frames = convert_to_img_list(anim, sheet.second, anim_info);

    if (img_info.flipped) {
      for (auto& frame : frames) {
        flip_horizontal(frame);
      }
    }

    if (img_info.id == 210 && sheet.first == "diffuse") { // Warp texture
      warp_texture_promise[is_low].set_value(frames);
    }
    if (img_info.warp_overlay && sheet.first == "diffuse") {  // Has warp overlay
      create_warp_anim(sheet.first, frames, anim_info, output_sheets, is_low);
    }

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

  split_sheet_result(output_sheets, anim_info);

  return output_sheets;
}

void convert_anim(const std::vector<std::uint8_t>& anim_data, const imagedat_info_t& img_info, const std::string& out_dir, bool is_low) {
  anim_t anim = loadAnim(anim_data);
  if (is_low) {
    anim.make_lowdef();
  }

  supplement_info_t anim_info = generate_supplemental_info(anim, img_info, 0, anim.framedata.size() - 1);

  create_depth_normal(anim);

  // Convert to lists
  std::unordered_map<std::string, CImg> output_sheets = convert_to_output(anim, img_info, anim_info, is_low);

  // Write output PNGs
  std::array<char, 128> filename;
  for (auto& sheet : output_sheets) {
    std::snprintf(filename.data(), filename.size(), "%s/main_%03d%s_%s.png", out_dir.c_str(), img_info.id, img_info.flipped ? "_flipped" : "", sheet.first.c_str());
    zero_out_transparent(sheet.second);
    cimg_library::save_png(sheet.second, filename.data());
  }

  if (img_info.flipped) return;

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
