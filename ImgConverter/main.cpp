#include <img_lib.h>
#include <jpeg_image.h>
#include <ppm_image.h>
#include <bmp_image.h>

#include <filesystem>
#include <string_view>
#include <iostream>

using namespace std;

enum class FORMAT {
    JPEG,
    PPM, 
    BMP,
    UNKNOWN
};

class ImageFormatInterface {
public:
    virtual bool SaveImage(const img_lib::Path& file, const img_lib::Image& image) const = 0;
    virtual img_lib::Image LoadImage(const img_lib::Path& file) const = 0;
};

class BMPInterface: public ImageFormatInterface {
    bool SaveImage(const img_lib::Path& file, const img_lib::Image& image) const override {
        return img_lib::SaveBMP(file, image);        
    }
    img_lib::Image LoadImage(const img_lib::Path& file) const override {
        return img_lib::LoadBMP(file);
    }
};

class PPMInterface: public ImageFormatInterface {
    bool SaveImage(const img_lib::Path& file, const img_lib::Image& image) const override {
        return SavePPM(file, image);        
    }
    img_lib::Image LoadImage(const img_lib::Path& file) const override {
        return img_lib::LoadPPM(file);
    }
};

class JPEGInterface: public ImageFormatInterface {
    bool SaveImage(const img_lib::Path& file, const img_lib::Image& image) const override {
        return SaveJPEG(file, image);        
    }
    img_lib::Image LoadImage(const img_lib::Path& file) const override {
        return img_lib::LoadJPEG(file);
    }
};

static const PPMInterface ppmInterface;
static const JPEGInterface jpegInterface;
static const BMPInterface bmpInterface;

FORMAT GetFormatByExtension(const img_lib::Path& input_file) {
    const string ext = input_file.extension().string();
    if (ext == ".jpg"sv || ext == ".jpeg"sv) {
        return FORMAT::JPEG;
    }

    if (ext == ".ppm"sv) {
        return FORMAT::PPM;
    }
    
    if (ext == ".bmp"sv) {
        return FORMAT::BMP;
    }

    return FORMAT::UNKNOWN;
}

 const ImageFormatInterface* GetFormatInterface(const img_lib::Path& path) {
    switch(GetFormatByExtension(path)) {
        case FORMAT::PPM: return &ppmInterface;
        case FORMAT::JPEG: return &jpegInterface;
        case FORMAT::BMP: return &bmpInterface;
        default: return nullptr;
    }
}

int main(int argc, const char** argv) {
    if (argc != 3) {
        cerr << "Usage: "sv << argv[0] << " <in_file> <out_file>"sv << endl;
        return 1;
    }

    img_lib::Path in_path = argv[1];
    img_lib::Path out_path = argv[2];
    
    auto in_interface = GetFormatInterface(in_path);
    if (!in_interface) {
        cerr << "Unknown format of the input file"sv << endl;        
        return 2;
    }
    auto out_interface = GetFormatInterface(out_path);
     if (!in_interface) {
        cerr << "Unknown format of the output file"sv << endl;        
        return 3;
    }
    
    
    img_lib::Image image = in_interface->LoadImage(in_path);
    if (!image) {
        cerr << "Loading failed"sv << endl;
        return 4;
    }

    if (!out_interface->SaveImage(out_path, image)) {
        cerr << "Saving failed"sv << endl;
        return 5;
    }

    cout << "Successfully converted"sv << endl;
}