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

#include <iostream>
#include <configuration.h>
#include <tnt/tntnet.h>
#include <tnt/configurator.h>
#include <cxxtools/log.h>

int main(int argc, char* argv[])
{
  try
  {
    Configuration& configuration = Configuration::it();

    if (argc > 1)
      configuration.readConfiguration(argv[1]);
    else
      configuration.readConfiguration("bookshop.conf");

    log_init(configuration.loggingConfiguration());

    tnt::Tntnet app;
    app.listen(configuration.listenIp(), configuration.listenPort());

    tnt::Configurator configurator(app);
    configurator.setSessionTimeout(configuration.sessionTimeout());

    // configure static stuff - lookup files in static resources first
    app.mapUrl("^/(.*)", "resources")
       .setPathInfo("resources/$1");

    // index page
    app.mapUrl("^/$", "webmain")
       .setArg("next", "index");

    // json calls
    app.mapUrl("^/(.*)\\.json$", "$1Json");

    // controller
    app.mapUrl("^/(.*)$", "controller/$1");

    // view
    app.mapUrl("^/(.*)$", "webmain")
       .setArg("next", "view/$1");

    app.run();
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

