#include <Tails/Assets/Info.hpp>
#include <Tails/Assets/Texture.hpp>
#include <Tails/Assets/Sound.hpp>
#include <Tails/Assets/Font.hpp>

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
