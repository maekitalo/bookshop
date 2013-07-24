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

#include <tnt/component.h>
#include <tnt/componentfactory.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <model/shoppingcart.h>
#include <cxxtools/log.h>

log_define("controller.cart")

namespace
{
  class CartController : public tnt::Component
  {
    public:
      unsigned operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam);
  };

  static tnt::ComponentFactoryImpl<CartController> factory("controller/cart");

  unsigned CartController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
  {
    TNT_SESSION_SHARED_VAR(Shoppingcart, shoppingcart, ());

    log_debug("cart controller");

    if (qparam.arg<bool>("updateAmount"))
    {
      std::vector<unsigned> amounts = qparam.args<unsigned>("amount");
      Books books = shoppingcart.books();

      log_debug(amounts.size() << " amounts " << books.size() << " books");

      for (unsigned n = 0; n < books.size() && n < amounts.size(); ++n)
      {
        log_debug(n << ": set amount of " << books[n].title() << " to " << amounts[n]);
        shoppingcart.setBookAmount(books[n], amounts[n]);
      }
    }


    return DECLINED;
  }

}
