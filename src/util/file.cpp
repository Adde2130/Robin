#include "file.h"
#include <fstream>
#include <sstream>
#include "renderer.h"

std::string readfile(const std::string& filename) {
    std::ifstream fs(filename);

    if(fs.is_open()){
        std::stringstream ss;
        ss << fs.rdbuf();
        fs.close();
        return ss.str();
    } else {
        std::cerr << "Could not open file '" << filename << "'" << std::endl;
        return "";
    }
}