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
