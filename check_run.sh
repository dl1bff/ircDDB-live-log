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


START_RUNSH=no
PIDFILE_PID=""

if [ -s run.pid ]
then
   PIDFILE_PID=` cat run.pid | tr -c -d '[0-9]' `
fi

if [ -n "$PIDFILE_PID" ]
then

   ps --pid $PIDFILE_PID >/dev/null

   if [ $? != 0 ]
   then
     # run.sh not running, kill old worker process
     WORKER_PID=`ps auxwww | grep "PPID${PIDFILE_PID}\$" | awk 'NR==1 { print $2 }' | tr -c -d '[0-9]' `
     if [ -n "$WORKER_PID" ]
     then
        kill "$WORKER_PID"
     fi
     START_RUNSH=yes
   fi

else
   START_RUNSH=yes
fi

if [ "$START_RUNSH" = "yes" ]
then
   nohup ./run.sh "(cwd: `pwd`)" 1>>stdout.txt 2>>stderr.txt &
fi
