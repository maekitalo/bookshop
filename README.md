Bookshop
========

This is a demo application, which shows how to create a web application with
Tntnet using the model view controller pattern.

The application uses the application mode of Tntnet. That means, that we create
a stand alone application. Our application is the server itself. No separate
Tntnet application server is needed.

There are a bunch of technologies, we can demonstrate here. Own applications may
follow this guide more or less strict. You may also pick just parts of the
technologies and solve other problems differently. Tntnet do not demand to
create applications in any specific way but gives the developer the full freedom
and responsibility to structure his code.

Needed software
---------------

The most important software we need is of course Tntnet. It uses cxxtools as its
base library. For database access we choose Tntdb.

In this demo application we use the git version of Tntnet which have some nifty
features for supporting MVC. Tntnet 2.2 lacks one features, we will use in this
example.

Build system
------------

When we set up a project, one of the major things is a suitable build system. We
need a build system which is reliable and easy to maintain.

Tntnet as well as cxxtools and tntdb are all built using the GNU autotools.
Easiness is not what people think about autotools but it is really not that hard
once set up.

To set up autotools, we have to create a file called `configure.ac` in our top
level directory. If you look at the bookshop project, only a few lines are needed
in `configure.ac`.

To build the bookshop demo, run the following commands in the source directory:

    autoreconf -i
    ./configure
    make

`autoreconf -i` will create the `configure` script, which then checks the
system and creates Makefiles. `make` builds the software. You will have a
process `bookshop` in the src directory. To run the software, set up a database,
configure the dburl in src/bookshop.conf and run the bookshop process in the src
directory.

Setting up the database
-----------------------

You should consult your administration guide of your database system, how to set
up a database. You find a sql script db/bookshop.sql, which creates the needed
tables. The script works at least with postgresql and sqlite. The sql script
db/data.sql inserts some test records.

### Sqlite

With sqlite you do not need to run a server or even create a database. The
database is a file, which is created when accessed first.

To create the database enter these commands:

    sqlite3 bookshop.db <db/bookshop.sql
    sqlite3 bookshop.db <db/data.sql

The dburl is `sqlite:bookshop.db`.

### Postgresql

To create the database enter these commands:

    createdb bookshop
    psql bookshop -f db/bookshop.sql
    psql bookshop -f db/data.sql

You have to make sure, you have enough permissions to create the database.
Consult the postgresql administration guide for that.

The dburl is `postgresql:dbname=bookshop`

### Mysql

To create the database enter these commands:

    mysqladmin create bookshop
    mysql bookshop <db/bookshop.sql
    mysql bookshop <db/data.sql

The dburl is `mysql:dbname=bookshop`

Directory structure
-------------------

The sources of the application can be found in the src subdirectory.

The directory itself has just a few files. The `main.cpp` contains the famous
main function where all C++ programs start. Here we instantiate the application
server class `tnt::Tntnet` and configure it. The most important part is the url
mapping, which tells the application, which components to call when a request
from the browser arrives. Here we take care, that for normal requests, the
controller gets the chance to handle user input and after that the corresponding
view is called.

The view is actually called indirectly via the second important file
`webmain.ecpp`. It gets a parameter with the name `next` from the mapping, which
tells him, what the actual view component is. The `webmain.ecpp` implements the
html frame around the view and calls the view component at a suitable place. In
`webmain.ecpp` we implement the overall layout for the application.

The files `configuration.h` and `configuration.cpp` we implement the
configuration for our application in form of a class `Configuration`. It is a
singleton with a static method `it` to make sure, we can access the
configuration easily in our application.

Since the application uses a database, it is important to tell the application,
how to connect to the database without hardcoding that. Also the listen ip and
port as well as the logging configuration are set up there.

We use the `cxxtools` serialization framework to read the file into memory and
use the properties deserialization. The properties is a simple list of name
values which is sufficient for our use. `cxxtools` adds the possibility to read
complex classes from properties also but we do not use it yet.

Using the serialization framework makes it easy to switch to xml or json later
if we want to by just changing the deserializer in the method
Configuration::readConfiguration.

The configuration is read in our main function before starting our web
application server.

Static resources
----------------

Every web application needs at least some static files like logos or small
icons or maybe some javascript code. In our case we have currently only the css
file `tntnet.css`.

Tntnet has a feature called multi binary components. Using that, we can collect
all static files into a single component. Since every component has a small
overhead, this reduces the memory footprint of our application. Also it makes
handling static files quite easy. We need some rules in our `src/Makefile.am` to
add this single component. We have a subdirectory src/resources, which collects
all those static files. To add new files, we create one in the resources
directory and add it to our Makefile.am to the `staticSources` list.

The application class has a suitable mapping, so that each request is first
looked up in those resources.

MMVC pattern
------------

Our application adds one component to the MVC pattern: the manager. It is
actually a MMVC pattern.

Lets look at the 4 parts. Each has its own subdirectory below our `src`
directory.

Model
-----

The model describes the data objects of our application. The model is maintained
as business objects in session scoped variables. Business objects are the
building blocks of our data.

In our bookshop demo one of those building blocks is a class Book, which
describes all the attributes of a book, which can be purchased in our demo
application. A typical data object is quite simple. If you look at the
declaration in `src/model/book.h` you can see, that it actually contains more or
less just some attributes. You can make just a struct with public members out of
it if you want but we choose a little more sophisticated model here. It is
always wise to hide the actual attributes behind getter and setter methods.

Manager
-------

You may have already noticed a friend declaration in our `Book` class. The
friend of the `Book` is his `BookManager` class. The manager implements all
methods to read books from the database or store them back.

A manager class holds typically a connection to the database. It has 2
constructors. One empty constructor, which connects to the database and one,
which receives the connection from the outside. We use tntdb here of course. The
`tntdb::Connection` class is actually a wrapper class, which holds a reference
to the actual connection implementation. A copy of the class holds just a
reference to the same implementation. The connection is closed when the last
reference is dropped.

The reason why we can pass a connection from outside is, that we sometimes need
more that one manager to do a transaction. For example we may want to extend our
bookshop to held a number of available items in our database. Then we need the
BookManager to reduce the number of items when the OrderManager adds a new
order. Both actions must be made in the same transaction. So we can just create
a connection, start a transaction, let both managers to do the database action
on this connection with our transaction and then commit both.

It is a matter of taste if you really want to have a empty constructor.
Sometimes it is just convenient, so that for simple stuff you do not need to
care about connections at all.

Note that we actually use the function `tntdb::connectCached` to create a
connections. This maintains a connection pool, so that our application won't
connect and disconnect for each request but reuse connections from previous
requests.

View
----

The view implements all the visible screens of our application. It displays data
and implements forms, where users can enter data into. The views are all
implemented as ecpp pages.

The views access the model in the mentioned scoped variables.

All views can be found in the directory `src/view`.

Controller
----------

The controller defines the interactions with the user. If the user presses a
button, the controller will react on that and modify the model or maybe issue
redirects to move to another screen.

The controller classes can be found in the directory `src/controller`. They can
be implemented either as ecpp, where we define just a section `<%cpp>` without
any output or without ecpp as a controller class which is derived from
`tnt::Component`, so that it can be called from the url mappings defined in our
application class.
