#pragma once
#include <string>
#include <fstream>

namespace GraphicsAssetHelper {

    static bool fileExists(const std::string& path) {
        std::ifstream f(path.c_str());
        return f.good();
    }

    static std::string resolveAssetPath(const std::string& relativePath, const std::string& fallbackPrefix) {
        if (fileExists(relativePath)) {
            return relativePath;
        }

        std::string stripped = relativePath;
        std::string prefix1 = "25i-0817_E_A2_P1/";
        std::string prefix2 = "25i-0817_E_A2_P2/";

        if (stripped.find(prefix1) == 0) {
            stripped = stripped.substr(prefix1.length());
        } else if (stripped.find(prefix2) == 0) {
            stripped = stripped.substr(prefix2.length());
        }

        if (fileExists(stripped)) {
            return stripped;
        }

        std::string prefixed = fallbackPrefix + "/" + stripped;
        if (fileExists(prefixed)) {
            return prefixed;
        }

        return relativePath;
    }

}
