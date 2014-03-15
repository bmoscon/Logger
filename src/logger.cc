
/*
 * logger.cc
 *
 *
 * Logger Library
 *
 *
 * Copyright (C) 2013-2014  Bryant Moscon - bmoscon@gmail.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution, and in the same 
 *    place and form as other copyright, license and disclaimer information.
 *
 * 3. The end-user documentation included with the redistribution, if any, must 
 *    include the following acknowledgment: "This product includes software 
 *    developed by Bryant Moscon (http://www.bryantmoscon.org/)", in the same 
 *    place and form as other third-party acknowledgments. Alternately, this 
 *    acknowledgment may appear in the software itself, in the same form and 
 *    location as other such third-party acknowledgments.
 *
 * 4. Except as contained in this notice, the name of the author, Bryant Moscon,
 *    shall not be used in advertising or otherwise to promote the sale, use or 
 *    other dealings in this Software without prior written authorization from 
 *    the author.
 *
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 *
 */

#include "logger.hpp"


Logger::Logger(const char *f) : _file(f, std::ios::out | std::ios::app), 
				_log(_file),
				_level(INFO),
				_line_level(VERBOSE)
{
  assert(_file.is_open());
}


Logger::Logger(std::string f) : _file(f.c_str(), std::ios::out | std::ios::app), 
				_log(_file),
				_level(INFO),
				_line_level(VERBOSE)
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
 

void Logger::flush()
{
  if (_line_level >= _level) {
    _log << get_time() << " -- [" << level_str(_line_level) << "] -- " << str();
    _log.flush();
    str("");
  }
  _line_level = VERBOSE;
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


std::string Logger::get_time()
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
    return ("VERBOSE");
  case DEBUG:
    return ("DEBUG");
  case INFO:
    return ("INFO");
  case WARNING:
    return ("WARNING");
  case ERROR:
    return  ("ERROR");
  case CRITICAL:
    return  ("CRITICAL");
  default:
    assert(false);
  } 
}
