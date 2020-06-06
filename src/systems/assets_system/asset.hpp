#pragma once

#include "systems/assets_system/asset_type.hpp"

namespace aiko
{

    class Asset
    {
    public:

        Asset(const AssetType type);
        virtual ~Asset() = default;

        virtual bool load() = 0;

        AssetType getType() const;

    private:
        const AssetType m_type;

    };

}
