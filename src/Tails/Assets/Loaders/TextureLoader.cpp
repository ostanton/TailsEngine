#include <Tails/Assets/Loaders/TextureLoader.hpp>
#include <Tails/Assets/Texture.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>
#include <Tails/Log.hpp>
#include <Tails/String.hpp>
#include <Tails/Filesystem.hpp>

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_error.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)
#define STBI_MALLOC(sz) SDL_malloc(sz)
#define STBI_REALLOC(p, newsz) SDL_realloc(p, newsz)
#define STBI_FREE(p) SDL_free(p)
#define STBI_FAILURE_USERMSG
#include <stb_image.h>

namespace tails
{
    std::shared_ptr<IAsset> CTextureLoader::load(const CString& path)
    {
        usize dataSize {0};
        auto const fileData {fs::loadFile(path, &dataSize)};
        
        if (!fileData)
        {
            TAILS_LOG_VA(AssetSubsystem, Error, "Failed to load texture file '%s', '%s'", path.getData(), SDL_GetError());
            return nullptr;
        }
        
        int w, h, channels;
        auto data = stbi_load_from_memory(fileData, static_cast<int>(dataSize), &w, &h, &channels, 4);
        //auto data = stbi_load(path, &w, &h, &channels, 4);
        
        if (!data)
        {
            TAILS_LOG_VA(AssetSubsystem, Error, "Failed to read texture data '%s', '%s'", path.getData(), stbi_failure_reason());
            stbi_image_free(data);
            return nullptr;
        }

        const auto result = assets::allocateAsset<CTexture>(
            path,
            SVector2u {static_cast<unsigned int>(w), static_cast<unsigned int>(h)},
            static_cast<unsigned int>(channels),
            data
        );
        return result;
    }
}
