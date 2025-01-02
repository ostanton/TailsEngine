#ifndef TAILS_RESOURCE_HPP
#define TAILS_RESOURCE_HPP

#include <Tails/Config.hpp>

#include <filesystem>

namespace tails
{
    class CResourceManager;
    
    class TAILS_API IResource
    {
        friend CResourceManager;
        
    public:
        IResource() = default;
        IResource(const IResource&) = default;
        IResource(IResource&&) = default;
        IResource& operator=(const IResource&) = default;
        IResource& operator=(IResource&&) = default;
        virtual ~IResource() = default;

        template<typename T>
        [[nodiscard]] const T* getUnderlying() const
        {
            if (auto const result = getUnderlyingImpl())
                return static_cast<const T*>(result);

            return nullptr;
        }

    protected:
        /**
         * Loads the file's data into engine-useable resource data
         * @param path File path
         * @return Successful
         */
        virtual bool load(const std::filesystem::path& path) = 0;

        /**
         * Manages any dependent resources or likewise
         */
        virtual void postLoad() {}

        /**
         * Gets the underlying memory this resource is based on (if any).
         * E.g.:
         * - SFML's sf::Texture/sf::Font/sf::SoundBuffer/etc.
         * @return Underlying memory
         */
        [[nodiscard]] virtual const void* getUnderlyingImpl() const = 0;
    };
}

#endif // TAILS_RESOURCE_HPP
