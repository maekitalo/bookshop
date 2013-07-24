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

#include <manager/bookmanager.h>
#include <tntdb/connect.h>
#include <tntdb/statement.h>
#include <configuration.h>

BookManager::BookManager()
  : _conn(tntdb::connectCached(Configuration::it().dburl()))
{ }

Book BookManager::getBookByIsbn(const std::string& isbn)
{
  tntdb::Statement sel = _conn.prepare(
      "select isbn, title, author, price"
      "  from book"
      " where isbn = :isbn");

  sel.set("isbn", isbn);

  tntdb::Row r = sel.selectRow();

  Book book;
  r[0].get(book._isbn);
  r[1].get(book._title);
  r[2].get(book._author);
  r[3].get(book._price);

  return book;
}

Books BookManager::getBooksByTitle(const std::string& title)
{
  tntdb::Statement sel = _conn.prepare(
      "select isbn, title, author, price"
      "  from book"
      " where title like :title");

  sel.set("title", '%' + title + '%');

  Books books;

  for (tntdb::Statement::const_iterator cur = sel.begin(); cur != sel.end(); ++cur)
  {
    tntdb::Row r = *cur;

    Book book;
    r[0].get(book._isbn);
    r[1].get(book._title);
    r[2].get(book._author);
    r[3].get(book._price);

    books.push_back(book);
  }

  return books;
}

Books BookManager::getBooksByAuthor(const std::string& author)
{
  tntdb::Statement sel = _conn.prepare(
      "select isbn, title, author, price"
      "  from book"
      " where author like :author");

  sel.set("author", '%' + author + '%');

  Books books;

  for (tntdb::Statement::const_iterator cur = sel.begin(); cur != sel.end(); ++cur)
  {
    tntdb::Row r = *cur;

    Book book;
    r[0].get(book._isbn);
    r[1].get(book._title);
    r[2].get(book._author);
    r[3].get(book._price);

    books.push_back(book);
  }

  return books;
}
