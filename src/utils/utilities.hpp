#pragma once

#include "SOIL2.h"

#include <string>
#include <fstream>
#include <filesystem>

namespace aiko
{
    namespace utils
    {

        template<class T>
        static T map(T value, T inFrom, T inTo, T outFrom, T outTo)
        {
            return (value - inFrom) * (outTo - outFrom) / (inTo - inFrom) + outFrom;
        }

        static unsigned int loadBMPTexture(const std::string& fileName)
        {
            auto fullPathToFile = std::filesystem::current_path() / ("../assets/" + fileName);
            return SOIL_load_OGL_texture(fullPathToFile.string().c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
        }

        static std::string readFile(const std::string& fileName)
        {

            // TODO : Not happy with this, find other solution
            auto fullPathToFile = std::filesystem::current_path() / ("../assets/" + fileName);

            std::string shaderCode;
            std::ifstream file(fullPathToFile, std::ios::in);

            if (file.good() == false)
            {
                printf("Cannot read shader file %s\n", fileName.c_str());
                std::terminate();
            }

            file.seekg(0, std::ios::end);
            shaderCode.resize(static_cast<unsigned int>(file.tellg()));
            file.seekg(0, std::ios::beg);
            file.read(&shaderCode[0], shaderCode.size());
            file.close();
            return shaderCode;
        }

    }

}
