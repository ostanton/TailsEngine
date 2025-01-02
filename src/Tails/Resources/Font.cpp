#include <Tails/Resources/Font.hpp>

namespace tails
{
    bool CFont::load(const std::filesystem::path& path)
    {
        return m_font.openFromFile(path);
    }

    const void* CFont::getUnderlyingImpl() const
    {
        return &m_font;
    }
}
