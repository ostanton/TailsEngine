#ifndef TAILS_CONFIG_HPP
#define TAILS_CONFIG_HPP

#include <SFML/Config.hpp>

// tails current version numbers
#define TAILS_VERSION_MAJOR 0
#define TAILS_VERSION_MINOR 0
#define TAILS_VERSION_PATCH 0

// tails export/import macros
#define TAILS_API_EXPORT SFML_API_EXPORT
#define TAILS_API_IMPORT SFML_API_IMPORT

// general tails api macro
// TODO::
// is this how it should be done? via CMake definitions??
// I can't find where SFML does it, and it's hard to find good
// information on this! Too bad!
/*
#if defined(TAILS_API_EXPORTS)
    #define TAILS_API TAILS_API_EXPORT
#else
    #define TAILS_API TAILS_API_IMPORT
#endif
*/

#define TAILS_API

#endif // TAILS_CONFIG_HPP
