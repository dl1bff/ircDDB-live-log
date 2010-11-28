#
# ircDDB livelog
#
# Copyright (C) 2010   Michael Dirska, DL1BFF (dl1bff@mdx.de)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

CFLAGS=-Wall

all: /var/www/livelog/jj3.yaws /var/www/livelog/ircddblive3.html /var/www/livelog/livelog3.js \
  filter_log


/var/www/livelog/jj3.yaws: jj3.yaws
	cp jj3.yaws /var/www/livelog/jj3.yaws

/var/www/livelog/ircddblive3.html: ircddblive3.html
	cp ircddblive3.html /var/www/livelog/ircddblive3.html

/var/www/livelog/livelog3.js: livelog3.js
	cp livelog3.js /var/www/livelog/livelog3.js

