#include "cimg_extensions.h"

#include <cstdint>
#include "../CImg/CImg.h"

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
