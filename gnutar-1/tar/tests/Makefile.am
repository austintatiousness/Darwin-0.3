# Makefile for GNU tar regression tests.
# Copyright ? 1996, 1997 Free Software Foundation, Inc.
# Fran?ois Pinard <pinard@iro.umontreal.ca>, 1988.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

AUTOMAKE_OPTIONS = gnits ../src/ansi2knr
check_PROGRAMS = genfile
BUILT_SOURCES = preset

TESTS = version.sh ignfail.sh extrac01.sh extrac02.sh extrac03.sh \
old.sh volume.sh gzip.sh append.sh delete01.sh incremen.sh

# Postponed until after the 1.12 release.
POSTPONED_TESTS = delete02.sh

genfile_SOURCES = genfile.c
EXTRA_DIST = after before preset.in $(TESTS) $(POSTPONED_TESTS)

DEFS = -DLOCALEDIR=\"$(localedir)\" @DEFS@
INCLUDES = -I.. -I../intl -I$(top_srcdir)/src -I$(top_srcdir)/lib
LDADD = ../lib/libtar.a @INTLLIBS@
localedir = $(prefix)/@DATADIRNAME@/locale

mostlyclean:
	rm -rf tmp-*

$(TESTS): genfile
