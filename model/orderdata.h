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

#ifndef ORDERDATA_H
#define ORDERDATA_H

class Orderdata
{
  public:
    Orderdata()
    { }

    const std::string& name() const { return _name; }

    const std::string& street() const { return _street; }

    const std::string& city() const { return _city; }

    void name(const std::string& v)  { _name = v; }

    void street(const std::string& v)  { _street = v; }

    void city(const std::string& v)  { _city = v; }


  private:
    std::string _name;
    std::string _street;
    std::string _city;
};

#endif // ORDERDATA_H

