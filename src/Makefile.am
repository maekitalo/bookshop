AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = bookshop

ecppSources = \
    index.ecpp \
	view/cart.ecpp \
	view/order.ecpp \
	view/products.ecpp \
    webmain.ecpp

staticSources = \
	resources/tntnet.css

bookshop_SOURCES = \
	configuration.cpp \
	controller/cart.cpp \
	controller/order.cpp \
	controller/products.cpp \
	main.cpp \
	manager/bookmanager.cpp \
	manager/ordermanager.cpp \
	model/shoppingcart.cpp \
	$(ecppSources)

nodist_bookshop_SOURCES = \
	resources.cpp

AM_INCLUDES = -I$(top_srcdir)/src

bookshop_LDFLAGS = -lcxxtools -ltntnet -ltntdb

CLEANFILES = $(ecppSources:.ecpp=.cpp) $(ecppSources:.ecpp=.deps) $(icoSources:.ico=.cpp)

#
# Rules for tntnet applications
#

# resources
resources.cpp: $(staticSources) Makefile.am
	$(ECPPC) -bb -z -n resources -p -o resources.cpp -I$(srcdir) $(staticSources)

SUFFIXES=.ecpp .ico .cpp

.ecpp.cpp:
	$(ECPPC) -I $(top_srcdir)/src -n $(basename $<) -o $@ $<
.ecpp.deps:
	$(ECPPC) -M -n $* -I $(srcdir) -I $(srcdir)/include $< | $(SED) '1s/\(.*\).cpp:/\1.cpp \1.deps:/' > $@
.ico.cpp:
	$(ECPPC) -b -m image/x-icon -o $@ $<

-include $(ecppSources:.ecpp=.deps)
