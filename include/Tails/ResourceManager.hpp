#ifndef TAILS_RESOURCE_MANAGER_HPP
#define TAILS_RESOURCE_MANAGER_HPP

#include <Tails/Config.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Concepts.hpp>
#include <Tails/Maths.hpp>

#include <memory>
#include <unordered_map>
#include <string>
#include <exception>
#include <filesystem>

namespace sf
{
    class Texture;
    class SoundBuffer;
    class Font;
}

namespace tails
{
    /**
     * To be a resource type, it must have a constructor that takes a const-ref filesystem::path,
     * and must be movable
     */
    template<typename T>
    concept ResourceType =
        std::constructible_from<T, const std::filesystem::path&> &&
        std::movable<T>;
    
    /**
     * Owns resources for various classes to have pointers to.
     * This allows SFML classes to be used with it (raw pointers to the resources that are managed by this manager).
     * It implements a type-erased unique_ptr, so is 16 bits instead of 8 bits.
     */
    class TAILS_API CResourceManager final
    {
    public:
        CResourceManager();
        CResourceManager(const CResourceManager&) = delete;
        CResourceManager(CResourceManager&&) noexcept = default;
        CResourceManager& operator=(const CResourceManager&) = delete;
        CResourceManager& operator=(CResourceManager&&) noexcept = default;
        ~CResourceManager();
        
        using ResourcePtr = std::unique_ptr<void, void(*)(const void*)>;
        using ResourceMap = std::unordered_map<size_t, ResourcePtr>;

        sf::Texture* createTexture(std::string_view id, const std::filesystem::path& filename);
        [[nodiscard]] sf::Texture* getTexture(std::string_view id) const;

        sf::SoundBuffer* createSound(std::string_view id, const std::filesystem::path& filename);
        [[nodiscard]] sf::SoundBuffer* getSound(std::string_view id) const;

        sf::Font* createFont(std::string_view id, const std::filesystem::path& filename);
        [[nodiscard]] sf::Font* getFont(const std::string& id) const;

        template<ResourceType T>
        T* createResource(std::string_view id, const std::filesystem::path& filename)
        {
            if (!m_resources.contains(hash(id)))
            {
                try {m_resources.try_emplace(hash(id), makeResourcePtr<T>(filename));}
                catch (const std::exception& e)
                {
                    CDebug::exception("Failed to create ", id, " resource: ", e.what());
                    return nullptr;
                }
                catch (...)
                {
                    CDebug::exception("Unknown exception while creating resource ", id);
                    return nullptr;
                }

                CDebug::print("Created \"", id, "\" resource at ", filename);
            }
            else
                CDebug::print("Resource \"", id, "\" already exists, getting it");

            return static_cast<T*>(m_resources.at(hash(id)).get());
        }

        template<ResourceType T>
        [[nodiscard]] T* getResource(std::string_view id) const
        {
            if (!m_resources.contains(hash(id)))
            {
                CDebug::error("Failed to find \"", id, "\" resource");
                return nullptr;
            }

            return static_cast<T*>(m_resources.at(hash(id)).get());
        }

    private:
        template<ResourceType T, typename... ArgsT>
        requires ConstructibleUserType<T, ArgsT...>
        [[nodiscard]] ResourcePtr makeResourcePtr(ArgsT&&... args) const
        {
            return ResourcePtr(new T(std::forward<ArgsT>(args)...), [](const void* data)
            {
                delete static_cast<const T*>(data);
            });
        }

        ResourceMap m_resources;
    };
}

#endif // TAILS_RESOURCE_MANAGER_HPP
