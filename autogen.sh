#!/bin/sh
# Copyright (C) 2000, 2001, 2002, 2003, 2004 Shawn Betts <sabetts@vcn.bc.ca>
#
# This file is part of ratpoison.
#
# ratpoison is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# ratpoison is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#
# $Id: autogen.sh,v 1.8 2006/03/16 00:33:34 sabetts Exp $
#
# usage: ./autogen.sh [-f]
# option "-f" means forcefully create symlinks for missing files
#                   (by default: copies are made only if necessary)

if [ x"$1" = x-f ]
  then shift ; am_opt='--force'
  else         am_opt='--copy'
fi

aclocal && autoheader && automake -a $am_opt && autoconf
