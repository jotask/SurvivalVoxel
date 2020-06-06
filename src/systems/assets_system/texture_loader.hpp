#pragma once

#include "systems/assets_system/texture.hpp"

#include <assimp/texture.h>
#include <assimp/material.h>
#include <SOIL2.h>

#include <vector>
#include <string>
#include <iostream>

namespace aiko
{
    namespace loader
    {
        namespace texture
        {

            static GLint textureFromFile(const char* path, std::string directory)
            {
                std::string fileName = std::string(path);
                fileName = directory + '/' + fileName;

                GLuint textureId;
                glGenTextures(1, &textureId);

                int width;
                int height;
                int nComponents;

                auto* image = SOIL_load_image(fileName.c_str(), &width, &height, &nComponents, SOIL_LOAD_AUTO);

                if (image != nullptr)
                {

                    GLenum format;
                    if (nComponents == 1)
                    {
                        format = GL_RED;
                    }
                    else if (nComponents == 3)
                    {
                        format = GL_RGB;
                    }
                    else if (nComponents == 4)
                    {
                        format = GL_RGBA;
                    }

                    glBindTexture(GL_TEXTURE_2D, textureId);
                    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
                    glGenerateMipmap(GL_TEXTURE_2D);

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                    glBindTexture(GL_TEXTURE_2D, 0);

                    SOIL_free_image_data(image);
                }
                else
                {
                    std::cout << "Texture failed to load at path: " << path << std::endl;
                }

                return textureId;

            }

            static std::vector<aiko::Texture*> loadMaterialTextures(AssetsSystem* sys, aiMaterial* material, aiTextureType type, std::string typeName, std::string directory)
            {

                std::vector<aiko::Texture*> textures;
                const auto tmp = material->GetTextureCount(type);
                for (GLuint i = 0; i < tmp; i++)
                {
                    aiString str;
                    material->GetTexture(type, i, &str);

                    GLboolean skip = false;

                    auto& textureLoaded = sys->getAssets(AssetType::Texture);

                    for (GLuint j = 0; j < textureLoaded.size(); j++)
                    {

                        auto* texture = static_cast<Texture*>(textureLoaded[j].get());

                        aiString path = aiString(texture->getPath());
                        if (path == str)
                        {
                            textures.push_back(texture);
                            skip = true;
                            break;
                        }
                    }

                    if (skip == false)
                    {
                        const auto id = textureFromFile(str.C_Str(), directory);
                        auto texture = std::make_unique<aiko::Texture>(id, typeName, str.C_Str());

                        textures.push_back(texture.get());
                        textureLoaded.emplace_back(std::move(texture));
                    }

                }
                return textures;
            }

        }
    }
}

