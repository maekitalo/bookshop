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

#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <model/book.h>
#include <vector>

class ShoppingItem
{
  public:
    ShoppingItem()
    { }

    ShoppingItem(const Book& book, unsigned amount)
      : _book(book),
        _amount(amount)
    { }

    const Book& book() const
    { return _book; }

    unsigned amount() const
    { return _amount; }

    void amount(unsigned newAmount)
    { _amount = newAmount; }

    double priceSum() const
    { return _amount * _book.price(); }

  private:
    Book _book;
    unsigned _amount;
};

typedef std::vector<ShoppingItem> ShoppingItems;

class Shoppingcart
{
  public:
    Shoppingcart()
    { }

    const ShoppingItems& items() const
    { return _items; }

    const ShoppingItem& item(unsigned n) const
    { return _items[n]; }

    Books books() const;

    void addBook(const Book& book, unsigned amount = 1);

    void setBookAmount(const Book& book, unsigned amount);

    double priceSum() const;

    unsigned countProducts() const
    { return _items.size(); }

    bool empty() const
    { return _items.empty(); }

  private:
    ShoppingItems _items;
};

#endif // SHOPPINGCART_H

