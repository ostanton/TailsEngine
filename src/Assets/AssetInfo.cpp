#include <Tails/Assets/AssetInfo.hpp>
#include <Tails/Assets/TextureResource.hpp>
#include <Tails/Assets/SoundResource.hpp>
#include <Tails/Assets/FontResource.hpp>

namespace tails
{
    bool AssetInfo::load()
    {
        switch (m_resourceType)
        {
            default:
                return false;
            case ResourceType::Texture:
                m_resource = std::make_unique<Texture>();
                break;
            case ResourceType::Sound:
                m_resource = std::make_unique<Sound>();
                break;
            case ResourceType::Font:
                m_resource = std::make_unique<Font>();
                break;
        }

        return m_resource->load(m_path);
    }
}
