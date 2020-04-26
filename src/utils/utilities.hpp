#pragma once

#include <string>
#include <fstream>
#include <filesystem>

namespace engine
{
    namespace utils
    {

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
