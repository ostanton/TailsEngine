project(Tails)

target_sources(
    Tails
    PRIVATE
        Optional.hpp
        Variant.hpp
        Bitset.hpp
        Expected.hpp
        SharedRef.hpp
        StaticArray.hpp
        Array.hpp
        UniquePtr.hpp
        Slice.hpp
)
