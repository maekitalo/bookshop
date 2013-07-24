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

#include <model/shoppingcart.h>
#include <stdexcept>

Books Shoppingcart::books() const
{
  Books ret;
  for (ShoppingItems::const_iterator it = _items.begin(); it != _items.end(); ++it)
    ret.push_back(it->book());
  return ret;
}

void Shoppingcart::addBook(const Book& book, unsigned amount)
{
  for (ShoppingItems::iterator it = _items.begin(); it != _items.end(); ++it)
  {
    if (it->book() == book)
    {
      it->amount(it->amount() + amount);
      return;
    }
  }

  _items.push_back(ShoppingItem(book, amount));
}

void Shoppingcart::setBookAmount(const Book& book, unsigned amount)
{
  for (ShoppingItems::iterator it = _items.begin(); it != _items.end(); ++it)
  {
    if (it->book() == book)
    {
      if (amount == 0)
        _items.erase(it);
      else
        it->amount(amount);

      return;
    }
  }

  if (amount != 0)
    throw std::runtime_error("book " + book.isbn() + " not found");

}

double Shoppingcart::priceSum() const
{
  double p = 0;
  for (unsigned n = 0; n < _items.size(); ++n)
    p += _items[n].amount() * _items[n].book().price();
  return p;
}

