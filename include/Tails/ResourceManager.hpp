#ifndef TAILS_RESOURCE_MANAGER_HPP
#define TAILS_RESOURCE_MANAGER_HPP

#include <Tails/Config.hpp>
#include <Tails/Concepts.hpp>
#include <Tails/Maths.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Resources/Resource.hpp>

#include <memory>
#include <unordered_map>
#include <functional>

namespace tails
{
    class TAILS_API CResourceManager final
    {
    public:
        CResourceManager(const CResourceManager&) = delete;
        CResourceManager(CResourceManager&&) = delete;
        CResourceManager& operator=(const CResourceManager&) = delete;
        CResourceManager& operator=(CResourceManager&&) = delete;
        ~CResourceManager() = default;
        
        template<Derives<IResource> ResT, typename... ArgsT>
        requires ConstructibleUserType<ResT, ArgsT...>
        [[nodiscard]] static std::shared_ptr<ResT> loadResource(const std::filesystem::path& path, ArgsT&&... args)
        {
            auto deleter = [](const std::size_t id)
            {
                if (get().m_resources[id].expired())
                {
                    CDebug::print("Deleting resource with ID: ", id);
                    get().m_resources.erase(id);
                }
            };
            
            const std::size_t id {hash(path.string())};
            std::shared_ptr<IResource> res {new ResT(std::forward<ArgsT>(args)...), std::bind(deleter, id)};
            get().m_resources.try_emplace(id, res);
            
            if (!res->load(path))
            {
                CDebug::error("Failed to load resource at path ", path);
                return nullptr;
            }
            
            // other load things
            res->postLoad();
            return std::static_pointer_cast<ResT>(res);
        }

        template<Derives<IResource> ResT>
        [[nodiscard]] static std::shared_ptr<ResT> getResource(const std::filesystem::path& path)
        {
            if (get().m_resources.contains(hash(path.string())))
                return std::static_pointer_cast<ResT>(get().m_resources[hash(path.string())].lock());

            CDebug::error("Failed to get resource at path ", path);
            return nullptr;
        }

        template<Derives<IResource> ResT, typename... ArgsT>
        requires ConstructibleUserType<ResT, ArgsT...>
        [[nodiscard]] static std::shared_ptr<ResT> getOrLoadResource(const std::filesystem::path& path, ArgsT&&... args)
        {
            if (const auto res = getResource<ResT>(path))
                return res;

            CDebug::print("Couldn't find resource at path ", path, ", so loading it instead");
            return loadResource<ResT>(path, std::forward<ArgsT>(args)...);
        }

    private:
        CResourceManager() = default;

        static CResourceManager& get();

        std::unordered_map<std::size_t, std::weak_ptr<IResource>> m_resources;
    };
}

#endif // TAILS_RESOURCE_MANAGER_HPP
