#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>

#ifdef RES_ROOT_DIR
#define RESOURCES_ROOT RES_ROOT_DIR
#else
#define RESOURCES_ROOT "Resources/"
#endif

#define ASSETS_SHADER_DIR RESOURCES_ROOT "Shader/"
#define ASSETS_TEXTURE_DIR RESOURCES_ROOT "Texture/"
#define ASSETS_MODEL_DIR RESOURCES_ROOT "Model/"
#define ASSETS_JSON_DIR RESOURCES_ROOT "Json/"

namespace Airwave
{
    class FileUtils
    {
    public:
        static std::string ReadFile(const std::string &filepath);

    private:
        FileUtils() = delete;
    };
} // namespace Airwave

#endif // FILE_UTILS_H