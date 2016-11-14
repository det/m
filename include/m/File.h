#pragma once
#include <fstream>

namespace m {
    std::string ReadFile(const char* filename) {
        auto file = std::ifstream{filename, std::ifstream::ate | std::ifstream::binary};
        auto length = file.tellg();

        if (!file || length <= 0)
            return "";

        auto buffer = std::string(static_cast<std::string::size_type>(length), ' ');
        file.seekg(0, std::ios::beg);
        file.read(&buffer.front(), length);

        return buffer;
    }

    std::string ReadFile (const std::string& filename) { return ReadFile(filename.c_str()); }
}
