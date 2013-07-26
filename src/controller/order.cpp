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
#include <model/orderdata.h>
#include <manager/ordermanager.h>

#include <cxxtools/log.h>

log_define("controller.order")

namespace
{
  class OrderController : public tnt::Component
  {
    public:
      unsigned operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam);
  };

  static tnt::ComponentFactoryImpl<OrderController> factory("controller/order");

  unsigned OrderController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
  {
    log_debug("order controller");

    if (qparam.arg<bool>("save"))
    {
      TNT_SESSION_SHARED_VAR(Orderdata, orderdata, ());
      orderdata.name(qparam.arg<std::string>("name"));
      orderdata.street(qparam.arg<std::string>("street"));
      orderdata.city(qparam.arg<std::string>("city"));
    }
    else if (qparam.arg<bool>("order"))
    {
      TNT_SESSION_SHARED_VAR(Orderdata, orderdata, ());
      TNT_SESSION_SHARED_VAR(Shoppingcart, shoppingcart, ());
      TNT_REQUEST_SHARED_VAR(std::string, feedback, ());

      orderdata.name(qparam.arg<std::string>("name"));
      orderdata.street(qparam.arg<std::string>("street"));
      orderdata.city(qparam.arg<std::string>("city"));

      OrderManager orderManager;
      orderManager.storeOrder(orderdata, shoppingcart);

      shoppingcart = Shoppingcart();
      feedback = "thank you for your order";
    }

    return DECLINED;
  }

}
