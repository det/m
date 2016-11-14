#pragma once
#include <fstream>

namespace m {
    // Returns a string buffer with the contents of an entire file. Throws std::ios_base::failure
    // on i/o failures.
    inline std::string ReadFile(const char* filename) {
        auto file = std::ifstream{};
        file.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        file.open(filename, std::ifstream::ate | std::ifstream::binary);

        auto length = file.tellg();
        auto buffer = std::string(static_cast<std::string::size_type>(length), ' ');
        file.seekg(0, std::ios::beg);
        file.read(&buffer.front(), length);

        return buffer;
    }

    inline std::string ReadFile (const std::string& filename) { return ReadFile(filename.c_str()); }
}
