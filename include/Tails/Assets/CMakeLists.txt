project(TailsEngine)

target_sources(
    TailsEngine
    PRIVATE
    AssetHandle.hpp
    AssetInfo.hpp
    Resource.hpp
    FontResource.hpp
    SoundResource.hpp
    TextureResource.hpp
)

add_subdirectory(Metadata)
