#pragma once

#include "../CImg/CImg.h"

using CImg = cimg_library::CImg<std::uint8_t>;
using CImgList = cimg_library::CImgList<std::uint8_t>;

CImg get_rotate90_black(const CImg& img);
void draw_image(CImg& dst, int dst_x, int dst_y, CImg& src, int src_x, int src_y, int width, int height);
void BGRAtoRGBA(CImg& img);
void zero_out_transparent(CImg& img);
