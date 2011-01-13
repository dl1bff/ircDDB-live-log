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
    url: "jj3.yaws",
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
	pos = lineNum.length + 1;

	if (num > lastNum)
	{
	  x_time = line.substr(8 + pos, 2) + ":" + line.substr(10 + pos, 2) + ":" +
	      line.substr(12 + pos, 2) ;
	  x_mycall = line.substr(14 + pos, 8).replace(/0/g, "&Oslash;");
	  x_rpt1 = line.substr(22 + pos, 8).replace(/0/g, "&Oslash;");

	  if (line.length >= (67 + pos))
	  {
	    x_urcall = line.substr(39 + pos, 8).replace(/0/g, "&Oslash;");
	    x_mycall = x_mycall + " " +  line.substr(53 + pos, 4).replace(/0/g, "&Oslash;");
	    x_rpt2 = line.substr(31 + pos, 8).replace(/0/g, "&Oslash;");
	    x_flags = line.substr(47 + pos, 2) + " " +  line.substr(49 + pos, 2) + " " +
	       line.substr(51 + pos, 2);
	    x_dest = line.substr(59 + pos, 8).replace(/0/g, "&Oslash;");

	    if (x_dest == "________")
	    {
	      x_dest = "&middot;"
	    }
	  }
	  else
	  {
	    x_urcall = "&middot;";
	    x_rpt2 = "&middot;"
	    x_flags = "&middot;"
	    x_dest = "&middot;"
	  }

	  if (line.length >= (87 + pos))
	  {
	    x_txmsg = line.substr(67 + pos, 20).replace(/_/g, " ").replace(/\&/g, "&amp;").replace(/</g, "&#60;");
	  }
	  else
	  {
	    x_txmsg = "&middot;"
	  }

	  type_flag = line.substr(30 + pos, 1);
	  type_flag2 = line.substr(57 + pos, 2);

	  txstats = "";
	  mycall_err = "";
	  urcall_err = "";

	  if (type_flag == "1")
	  {
	    txstats = " txstats";
	  }
	  else if (type_flag == "2")
	  {
	    mycall_err = " err";
	  }

	  if (type_flag2 == "01")
	  {
	    urcall_err = " err";
	  }


	  p = num % 2;

	  var newNode = $("<li style=\"display:none\">" +
             	"<span class=\"xlist time linebg" + p + "\">" + x_time + "</span>" + 
		"<span class=\"xlist mycall linebg" + p + mycall_err + "\">" + x_mycall + "</span>" + 
		"<span class=\"xlist urcall linebg" + p + urcall_err + "\">" + x_urcall + "</span>" +
		"<span class=\"xlist rpt1 linebg" + p + "\">" + x_rpt1 + "</span>" +
		"<span class=\"xlist rpt2 linebg" + p + "\">" + x_rpt2 + "</span>" +
		"<span class=\"xlist dest linebg" + p + "\">" + x_dest + "</span>" +
		"<span class=\"xlist txmsg linebg" + p + txstats + "\">" + x_txmsg + "</span>" +
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
