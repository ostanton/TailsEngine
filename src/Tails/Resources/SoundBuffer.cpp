#include <Tails/Resources/SoundBuffer.hpp>

namespace tails
{
    bool CSoundBuffer::load(const std::filesystem::path& path)
    {
        return m_buffer.loadFromFile(path);
    }

    const void* CSoundBuffer::getUnderlyingImpl() const
    {
        return &m_buffer;
    }
}
