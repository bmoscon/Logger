/*
 * logger.cc
 *
 *
 * Logger Library
 *
 *
 * Copyright (C) 2013-2017  Bryant Moscon - bmoscon@gmail.com
 * 
 * Please see the LICENSE file for the terms and conditions 
 * associated with this software.
 *
 */

#include "logger.hpp"


Logger::Logger(const char *f) : _file(f, std::ios::out | std::ios::app), 
				_log(_file),
				_level(INFO),
				_line_level(VERBOSE),
				_default_line_level(VERBOSE)
{
    assert(_file.is_open());
}


Logger::Logger(const std::string& f) : _file(f.c_str(), std::ios::out | std::ios::app), 
				       _log(_file),
				       _level(INFO),
				       _line_level(VERBOSE),
				       _default_line_level(VERBOSE)
{
    assert(_file.is_open());
}


Logger::~Logger()
{
    if (_file.is_open()) {
	_log.flush();
	_file.close();
    }
}


void Logger::set_level(const logger_level& level)
{
    _level = level;
}  


void Logger::set_default_line_level(const logger_level& level)
{
    _default_line_level = level;
}


void Logger::flush()
{
    if (_line_level >= _level) {
	_log << get_time() << " -- [" << level_str(_line_level) << "] -- " << str();
	_log.flush();
    }
    
    str("");
    _line_level = _default_line_level;
}


Logger& Logger::operator<<(const logger_level& level)
{
    _line_level = level;
    return (*this);
}


Logger& Logger::operator<<(LoggerManip m)
{ 
    return m(*this);
}


std::string Logger::get_time() const
{
    struct tm *timeinfo;
    time_t rawtime;
    char *time_buf;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    time_buf = asctime(timeinfo);
    
    std::string ret(time_buf);
    if (!ret.empty() && ret[ret.length() - 1] == '\n') {
	ret.erase(ret.length()-1);
    }
    
    return (ret);
}


inline const char* Logger::level_str(const logger_level& level)
{
    switch (level) {
    case VERBOSE:
	return ("VRB");
    case DEBUG:
	return ("DBG");
    case INFO:
	return ("INF");
    case WARNING:
	return ("WRN");
    case ERROR:
	return ("ERR");
    case CRITICAL:
	return ("CRT");
    default:
	assert(false);
    }
}
