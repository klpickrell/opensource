SHELL=/bin/sh

# Here's where you add the modules that you want to build
# Just add the directory of a project that contains a makefile
# to the TARGETS variable


TARGETS:=$(shell find * -prune -type d)

.PHONY: $(TARGETS)

all: $(TARGETS)

$(TARGETS):
	for curdir in $@; do			   \
		$(MAKE) $(MAKEFLAGS) -C $$curdir;  \
	done

clean:
	for curdir in $(TARGETS); do			\
		$(MAKE) $(MAKEFLAGS) -C $$curdir clean;	\
	done