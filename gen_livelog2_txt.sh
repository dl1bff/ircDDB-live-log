#!/bin/sh

#
#  ircDDB livelog
#
#  Copyright (C) 2010   Michael Dirska, DL1BFF (dl1bff@mdx.de)
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



tail -F ../dstardb/stdout.txt | awk -F '[' '

BEGIN {
	last_update = ""
	leerzeichen = "                                                                          "
	}

$3 == "PRIVMSG] " && $4 == "#mheard] " && $5 ~ /UPDATE 20/ {

	numfield = split($5, a, ":")

	if ((a[2] == " UPDATE OK") && ($5 != last_update))
	{
		b = a[3]
		gsub(" UPDATE ", "", b)
		e = ""
		for (i=5; i <= numfield; i++) {
			e = e ":" a[i]
		}
		gsub("].*$", "", e)
		k = sprintf("%s:%s%s", b , a[4] , e)
		l = 99 - length(k) 
		if (l > 0) {
		  printf "%s%s\n", k, substr(leerzeichen,1,l)
		}
		fflush()
		last_update = $5
	}
}

' > livelog2.txt


