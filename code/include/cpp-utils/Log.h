#pragma once

#ifndef NDEBUG
#   define DB_MSG(message) \
    do { \
        std::cout << message << endl;
    } while (false)
#else
#   define DB_MSG(message) do { } while (false)
#endif