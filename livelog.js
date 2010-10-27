// 
//  ircDDB livelog
// 
//  Copyright (C) 2010   Michael Dirska, DL1BFF (dl1bff@mdx.de)
// 
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 2 of the License, or
//  (at your option) any later version.
// 
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 

var lastNum = 0;

function ajaxSettings()
{
  return {
    url: "jj.yaws",
    data: "p=" + lastNum,
    success: showData
  };
}

$.ajax( ajaxSettings() );

setInterval( function() { $.ajax( ajaxSettings() ); }, 5000);

function showData(response)
{
  var responsePattern = /^([0-9]+:.*\n)*([0-9]+:.*)\n$/m ;
  if (response.match(responsePattern))
  {
    var lines = response.split("\n");
    var maxNum = 0;

    for (i=0; i < lines.length; i++)
    {
      if (lines[i].length > 10)
      {
	line = lines[i];
	lineNum = line.split(":")[0];
	num = parseInt(lineNum) ;
	pos = lineNum.length;

	if (num > lastNum)
	{
	  x_time = line.substr(12 + pos, 8);
	  x_mycall = line.substr(21 + pos, 8).replace(/0/g, "&Oslash;");
	  x_rpt1 = line.substr(30 + pos, 8).replace(/0/g, "&Oslash;");

	  if (line.length > (39 + pos))
	  {
	    x_urcall = line.substr(48 + pos, 8).replace(/0/g, "&Oslash;");
	    x_mycall = x_mycall + " " +  line.substr(66 + pos, 4).replace(/0/g, "&Oslash;");
	    x_rpt2 = line.substr(39 + pos, 8).replace(/0/g, "&Oslash;");
	    x_flags = line.substr(57 + pos, 8);
	  }
	  else
	  {
	    x_urcall = "&middot;";
	    x_rpt2 = "&middot;"
	    x_flags = "&middot;"
	  }

	  if (line.length > (80 + pos))
	  {
	    x_txmsg = line.substr(71 + pos, 20).replace(/_/g, " ");
	  }
	  else
	  {
	    x_txmsg = "&middot;"
	  }


	  p = num % 2;

	  var newNode = $("<li style=\"display:none\">" +
             	"<span class=\"xlist time linebg" + p + "\">" + x_time + "</span>" + 
		"<span class=\"xlist mycall linebg" + p + "\">" + x_mycall + "</span>" + 
		"<span class=\"xlist urcall linebg" + p + "\">" + x_urcall + "</span>" +
		"<span class=\"xlist rpt1 linebg" + p + "\">" + x_rpt1 + "</span>" +
		"<span class=\"xlist rpt2 linebg" + p + "\">" + x_rpt2 + "</span>" +
		"<span class=\"xlist txmsg linebg" + p + "\">" + x_txmsg + "</span>" +
		"<span class=\"xlist flags linebg" + p + "\">" + x_flags + "</span>" +
			"</li>");
	  $("#stream").append(newNode);
	  newNode.slideDown();
	  deleteOldest();
	}
	if (num > maxNum)
	{
	  maxNum = num;
	}
      }
    }
    lastNum = maxNum;
  }
}

function deleteOldest()
{
  if($("#stream").children().length > 110)
    deleteOldest = function() { $("#stream").find("li:first").remove(); };
}
