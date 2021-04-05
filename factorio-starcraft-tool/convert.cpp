#include "convert.h"

#include <vector>
#include <cstdint>

#include "image_predefs.h"
#include "anim.h"

void convert_anim(const std::vector<std::uint8_t>& anim_data, const imagedat_info_t& img_info) {
  loadAnim(anim_data);

}
