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

#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

class BookManager;

class Book
{
    friend class BookManager;

  public:
    Book()
    { }

    Book(const std::string& isbn, const std::string& title, const std::string& author, double price)
      : _isbn(isbn),
        _title(title),
        _author(author),
        _price(price)
    { }

    const std::string& isbn() const
    { return _isbn; }

    const std::string& title() const
    { return _title; }

    const std::string& author() const
    { return _author; }

    double price() const
    { return _price; }

  private:
    std::string _isbn;
    std::string _title;
    std::string _author;
    double _price;
};

inline bool operator== (const Book& b1, const Book& b2)
{
  return b1.isbn() == b2.isbn();
}

typedef std::vector<Book> Books;

#endif // MODEL_BOOK_H

