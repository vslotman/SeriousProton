#ifndef LOGGING_H
#define LOGGING_H

#include <SFML/System.hpp>
#include "stringImproved.h"

#define LOG(LEVEL) Logging(LOGLEVEL_ ## LEVEL, __FILE__, __LINE__, __PRETTY_FUNCTION__)

enum ELogLevel
{
    LOGLEVEL_DEBUG,
    LOGLEVEL_INFO,
    LOGLEVEL_WARNING,
    LOGLEVEL_ERROR
};

class Logging : sf::NonCopyable
{
    static ELogLevel global_level;
    bool do_logging;
public:
    Logging(ELogLevel level, string file, int line, string function_name);
    ~Logging();
    
    static void setLogLevel(ELogLevel level);
    
    friend const Logging& operator<<(const Logging& log, const char* str);
};

const Logging& operator<<(const Logging& log, const char* str);
inline const Logging& operator<<(const Logging& log, const std::string& s) { return log << (s.c_str()); }
inline const Logging& operator<<(const Logging& log, const int i) { return log << string(i).c_str(); }
inline const Logging& operator<<(const Logging& log, const unsigned int i) { return log << string(i).c_str(); }
inline const Logging& operator<<(const Logging& log, const long i) { return log << string(int(i)).c_str(); }
inline const Logging& operator<<(const Logging& log, const unsigned long i) { return log << string(int(i)).c_str(); }
inline const Logging& operator<<(const Logging& log, const float f) { return log << string(f).c_str(); }
template<typename T> inline const Logging& operator<<(const Logging& log, const sf::Vector2<T> v) { return log << v.x << "," << v.y; }

#endif//LOGGING_H
