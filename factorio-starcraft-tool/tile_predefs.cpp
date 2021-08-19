#include "tile_predefs.h"

#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

//--------------------------------------------------
// Full tiles
std::vector<int> vr4_creep_tiles = {
  1, 2, 3, 4, 5, 6, 7, 8, 9, 2643, 2644, 2645, 2646
};

std::vector<int> icon_indices = {
  0, 1, 2, 3, 4, 5, 6, 7
};

std::vector<int> excluded_cmdicons = {
  4, 6, 18, 24, 26, 27, 31, 87, 97, 98, 102, 105, 121, 153, 158, 161, 179, 180, 181, 182, 183, 184, 185, 186, 187, 191,
  192, 193, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229,
  230, 231, 233, 254, 255, 279, 282, 283, 309, 367, 386, 387, 388, 389
};

std::vector<int> get_cmdicons() {
  std::vector<int> all_cmdicons(390);
  std::iota(all_cmdicons.begin(), all_cmdicons.end(), 0);
  
  std::vector<int> result;
  std::set_difference(all_cmdicons.begin(), all_cmdicons.end(), excluded_cmdicons.begin(), excluded_cmdicons.end(), std::back_inserter(result));
  
  return result;
}

std::vector<int> cmdicon_indices = get_cmdicons();
