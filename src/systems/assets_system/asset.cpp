#include "asset.hpp"

namespace aiko
{
    Asset::Asset(const AssetType type)
        : m_type(type)
    {

    }

    AssetType Asset::getType() const
    {
        return m_type;
    }

}
