/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * is provided AS IS, WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, and
 * NON-INFRINGEMENT.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *
 */

#include <configuration.h>
#include <cxxtools/properties.h>
#include <cxxtools/serializationinfo.h>
#include <fstream>

/*

   Note about multithreading
   -------------------------

   Applications written with tntnet are multithreaded so we do have to think
   about proper locking. Here locking is actually not necessary since the
   configuration is read before the threads start and not modified afterwords.

 */

void operator>>= (const cxxtools::SerializationInfo& si, Configuration& config)
{
  si.getMember("listen.ip", config._listenIp);
  si.getMember("listen.port") >>= config._listenPort;
  si.getMember("sessiontimeout") >>= config._sessionTimeout;
  si.getMember("accessLog", config._accessLog);
  si.getMember("dburl") >>= config._dburl;
  si >>= config._loggingConfiguration;
}

void Configuration::readConfiguration(const std::string& file)
{
  std::ifstream in(file.c_str());
  in >> cxxtools::Properties(Configuration::it());
}

Configuration& Configuration::it()
{
  static Configuration theConfiguration;
  return theConfiguration;
}
