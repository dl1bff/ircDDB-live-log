#!/bin/sh

#
#  ircDDB livelog
#
#  Copyright (C) 2012   Michael Dirska, DL1BFF (dl1bff@mdx.de)
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#

OUTPUTFILE=livelog3.txt

rm -f $OUTPUTFILE

tail --pid=$$ -F ../dstardb/stdout.txt | ./filter_log >> $OUTPUTFILE


