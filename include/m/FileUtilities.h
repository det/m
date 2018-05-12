#pragma once
#include <fstream>

namespace m {
    // Returns a string with the contents of an entire file. May throw std::ios_base::failure.
    inline std::string readFile(const char* filename) {
        auto file = std::ifstream{};
        file.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        file.open(filename, std::ifstream::ate | std::ifstream::binary);

        auto length = file.tellg();
        auto buffer = std::string(static_cast<std::string::size_type>(length), '\0');
        file.seekg(0, std::ios::beg);
        file.read(&buffer.front(), static_cast<std::streamsize>(length));

        return buffer;
    }

    inline std::string readFile (const std::string& filename) { return readFile(filename.c_str()); }
}
