#pragma once

#include "systems/chunk_system/voxel_info.hpp"

namespace aiko
{

    class Voxel
    {
    public:
        Voxel(const VoxelInfo::VoxelType type = VoxelInfo::VoxelType::SOLID, const VoxelInfo::VoxelId id = VoxelInfo::VoxelId::DIRT);
        const VoxelInfo::VoxelType getVoxelType() const;
        const VoxelInfo::VoxelId getVoxelId() const;
    private:
        const VoxelInfo::VoxelType m_type;
        const VoxelInfo::VoxelId m_id;
    };

}