#ifndef TAILS_LEVEL_LOADER_HPP
#define TAILS_LEVEL_LOADER_HPP

#include <Tails/Core.hpp>
#include <Tails/String.hpp>

#include <memory>

namespace tails
{
    class IAsset;
}

namespace tails::assets::level
{
    TAILS_API std::shared_ptr<IAsset> load(const CString& path);
    TAILS_API std::shared_ptr<IAsset> load(u8* memory, usize size);
}

#endif // TAILS_LEVEL_LOADER_HPP
