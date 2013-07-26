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

#include <manager/ordermanager.h>
#include <model/orderdata.h>
#include <model/shoppingcart.h>
#include <configuration.h>
#include <tntdb/connect.h>
#include <tntdb/transaction.h>
#include <tntdb/statement.h>


OrderManager::OrderManager()
  : _conn(tntdb::connectCached(Configuration::it().dburl()))
{ }

unsigned OrderManager::storeOrder(const Orderdata& orderdata, const Shoppingcart& shoppingcart)
{
  tntdb::Transaction trans(_conn);

  tntdb::Statement insOrder = _conn.prepare(
      "insert into custorder (name, street, city)"
      "  values (:name, :street, :city)");

  insOrder.set("name", orderdata.name())
          .set("street", orderdata.street())
          .set("city", orderdata.city())
          .execute();

  unsigned custorderid = _conn.lastInsertId();

  tntdb::Statement insItem = _conn.prepare(
      "insert into custorderitem (custorderid, isbn, amount)"
      "  values (:custorderid, :isbn, :amount)");

  insItem.set("custorderid", custorderid);

  for (ShoppingItems::const_iterator it = shoppingcart.items().begin();
      it != shoppingcart.items().end();
      ++it)
  {
    insItem.set("isbn", it->book().isbn())
           .set("amount", it->amount())
           .execute();
  }

  trans.commit();

  return custorderid;
}
