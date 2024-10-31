#include "bmp_image.h"
#include "pack_defines.h"

#include <array>
#include <fstream>
#include <string_view>

using namespace std;

namespace img_lib {

PACKED_STRUCT_BEGIN BitmapFileHeader {   
    char symbols[2] = {'B', 'M'};
    uint32_t size;
    uint32_t space{};
    uint32_t indent_data = 54;
}
PACKED_STRUCT_END

PACKED_STRUCT_BEGIN BitmapInfoHeader {    
    uint32_t size_of_header = 40; 
    int32_t width; 
    int32_t height;
    uint8_t color_planes_num = 1;
    uint8_t bits_per_pixel = 24;
    uint32_t compression_type = 0;
    uint32_t num_bytes_of_data; 
    int32_t horDPI = 11811; // horizontal resolution
    int32_t verDPI = 11811; // Vertical resolution
    int32_t num_of_colors_used = 0; //The number of colors used
    int32_t num_of_colors = 0x1000000; //The number of significant colors 
}
PACKED_STRUCT_END

// Function of the computing of the margin by width
static int GetBMPStride(int w) {
    return 4 * ((w * 3 + 3) / 4);
}

bool SaveBMP(const Path& file, const Image& image) {
    ofstream out(file, ios::binary);
    BitmapFileHeader bf;
    BitmapInfoHeader bi;
    
    int stride = GetBMPStride(image.GetWidth());
    
    bf.size = stride * image.GetHeight() + 54;
    bi.width = image.GetWidth(); 
    bi.height = image.GetHeight();
    bi.num_bytes_of_data = stride * bi.height;
    
    out.write((char*)&bf, sizeof(bf));
    out.write((char*)&bi, sizeof(bi));
    
    const int w = image.GetWidth();
    const int h = image.GetHeight();
    std::vector<char> buff(stride);

    for (int y = h - 1; y > 0; --y) {
        const Color* line = image.GetLine(y);
        for (int x = 0; x < w; ++x) {
            buff[x * 3 + 0] = static_cast<char>(line[x].b);
            buff[x * 3 + 1] = static_cast<char>(line[x].g);
            buff[x * 3 + 2] = static_cast<char>(line[x].r);
        }
        out.write(buff.data(), stride);
    }
    return out.good();    
}
 
Image LoadBMP(const Path& file) {
    if (file.empty()) return {};
    ifstream ifs(file, ios::binary);
    BitmapFileHeader bf;
    ifs.read((char*)&bf, sizeof(bf));
    if (!ifs || 
        bf.symbols[0] != 'B' ||
        bf.symbols[1] != 'M' ||
        bf.space != 0 ||
        bf.indent_data != 54) {
        return {};
    }
   
    BitmapInfoHeader bi;
    
    ifs.read((char*)&bi, sizeof(bi));    
    if (!ifs) return {};
    
    int stride = GetBMPStride(bi.width);
    if (bf.size != stride * bi.height + 54) return {};
    
    Image result(bi.width, bi.height, Color::Black());
    std::vector<char> buff(stride);
    
    for (int y = bi.height - 1; y > 0; --y) {
        Color* line = result.GetLine(y);
        ifs.read(buff.data(), stride);

        for (int x = 0; x < bi.width; ++x) {
            line[x].r = static_cast<byte>(buff[x * 3 + 2]);
            line[x].g = static_cast<byte>(buff[x * 3 + 1]);
            line[x].b = static_cast<byte>(buff[x * 3 + 0]);
        }
    }
    return result;
}

}  // namespace img_lib