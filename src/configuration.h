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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <cxxtools/serializationinfo.h>

class Configuration
{
    friend void operator>>= (const cxxtools::SerializationInfo& si, Configuration& config);

  public:
    static Configuration& it();

    void readConfiguration(const std::string& file);

    const std::string& listenIp() const
    { return _listenIp; }

    unsigned short     listenPort() const
    { return _listenPort; }

    const std::string& dburl() const
    { return _dburl; }

    const cxxtools::SerializationInfo& loggingConfiguration() const
    { return _loggingConfiguration; }

  private:
    Configuration() { }
    Configuration(const Configuration&);
    const Configuration& operator=(const Configuration&);

    std::string    _listenIp;
    unsigned short _listenPort;
    std::string    _dburl;
    cxxtools::SerializationInfo _loggingConfiguration;
};

#endif // CONFIGURATION_H

