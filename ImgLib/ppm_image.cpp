#include "ppm_image.h"

#include <array>
#include <fstream>
#include <string_view>

using namespace std;

namespace img_lib {

static const string_view PPM_SIG = "P6"sv;
static const int PPM_MAX = 255;

bool SavePPM(const Path& file, const Image& image) {
    ofstream out(file, ios::binary);

    out << PPM_SIG << '\n' << image.GetWidth() << ' ' << image.GetHeight() << '\n' << PPM_MAX << '\n';

    const int w = image.GetWidth();
    const int h = image.GetHeight();
    std::vector<char> buff(w * 3);

    for (int y = 0; y < h; ++y) {
        const Color* line = image.GetLine(y);
        for (int x = 0; x < w; ++x) {
            buff[x * 3 + 0] = static_cast<char>(line[x].r);
            buff[x * 3 + 1] = static_cast<char>(line[x].g);
            buff[x * 3 + 2] = static_cast<char>(line[x].b);
        }
        out.write(buff.data(), w * 3);
    }

    return out.good();
}

Image LoadPPM(const Path& file) {
    // Open a stream with an flag binary
    // since we will read data in binary format
    ifstream ifs(file, ios::binary);
    std::string sign;
    int w, h, color_max;

   // read the headline: it contains the format, image sizes
    // and maximum color value
    ifs >> sign >> w >> h >> color_max;

    // We support images only P6 format
    // with the maximum color value 255
    if (sign != PPM_SIG || color_max != PPM_MAX) {
        return {};
    }

    // skip one byte - this is the end of the line
    const char next = ifs.get();
    if (next != '\n') {
        return {};
    }

    Image result(w, h, Color::Black());
    std::vector<char> buff(w * 3);

    for (int y = 0; y < h; ++y) {
        Color* line = result.GetLine(y);
        ifs.read(buff.data(), w * 3);

        for (int x = 0; x < w; ++x) {
            line[x].r = static_cast<byte>(buff[x * 3 + 0]);
            line[x].g = static_cast<byte>(buff[x * 3 + 1]);
            line[x].b = static_cast<byte>(buff[x * 3 + 2]);
        }
    }

    return result;
}

}  // namespace img_lib