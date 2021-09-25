#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "../CImg/CImg.h"


// ----- .anim File Data -----
typedef struct {
  std::uint32_t filetype;  // 0x4D494E41, "ANIM"
  std::uint16_t version;   // SD = 0x0101, HD2 = 0x0202, HD = 0x0204
  std::uint16_t unk2;      // null? more bytes for version?
  std::uint16_t layers;
  std::uint16_t entries;   // 999
  char layernames[10][32];
  // int entryptrs[entries] // for version 0x0101, pointers to anim_entry/anim_ref's
} anim_header_t;

typedef struct {
  std::uint32_t ptr;
  std::uint32_t size;
  std::uint16_t texWidth; // width/height of texture image
  std::uint16_t texHeight;
} anim_img_t;

typedef struct {
  std::uint16_t frames; // if == 0 use anim_ref

  std::uint16_t unk2; // 0xFFFF?
  std::uint16_t grpWidth;  // width/height of whole GRP frame -- 0 in SD images, to be retrieved from existing GRP's?
  std::uint16_t grpHeight;

  std::uint32_t frameptr; // pointer to frame data

  anim_img_t imgs[10]; // 1 per layer in the header
} anim_entry_t;

typedef struct {
  std::uint16_t frames; // if != 0 use anim_entry

  std::uint16_t refid; // image ID to refer to
  std::uint32_t unk0;
  std::uint32_t unk1; // always 0?
  std::uint16_t unk2; // who knows
} anim_ref_t;

struct frame_t {
  std::uint16_t x;
  std::uint16_t y;
  std::int16_t xoffs;
  std::int16_t yoffs;
  std::uint16_t width;
  std::uint16_t height;
  std::uint16_t unk1; // 0?
  std::uint16_t unk2; // 0?

  void halve() {
    x /= 2;
    y /= 2;
    xoffs /= 2;
    yoffs /= 2;
    width /= 2;
    height /= 2;
  }
};



// ----- anim memory data -----

#define ANIM_TEX_COUNT 2

struct anim_t {
  std::uint32_t width;      // grp width
  std::uint32_t height;     // grp height

  std::vector<std::pair<std::string, cimg_library::CImg<std::uint8_t>>> sheets;

  std::vector<frame_t> framedata;

  void make_lowdef() {
    for (frame_t& frame : framedata) {
      frame.halve();
    }
    width /= 2;
    height /= 2;
  }
};

//anim_t loadAnim(std::istream& is);
anim_t loadAnim(const std::vector<std::uint8_t>& data);
