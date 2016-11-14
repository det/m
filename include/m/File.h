#pragma once
#include <fstream>

namespace m {
    std::string ReadFile(const char* filename) {
        auto file = std::ifstream{filename, std::ifstream::ate | std::ios::binary};
        auto length = f.tellg();

        if (!file || length <= 0)
            return "";

        auto buffer = std::string{length, ' '};
        file.seekg(0, std::ios::beg);
        file.read(&buffer.front(), length);

        return buffer;
    }
}
