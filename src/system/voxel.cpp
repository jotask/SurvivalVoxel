#include "voxel.hpp"

namespace engine
{

    Voxel::Voxel(const VoxelInfo::VoxelType type, const VoxelInfo::VoxelId id)
        : m_type(type)
        , m_id(id)
    {

    }

    const VoxelInfo::VoxelType Voxel::getVoxelType() const
    {
        return m_type;
    }

    const VoxelInfo::VoxelId Voxel::getVoxelId() const
    {
        return m_id;
    }

}
