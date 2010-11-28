/*

rcDDB livelog

Copyright (C) 2010   Michael Dirska, DL1BFF (dl1bff@mdx.de)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_BUF  400
#define NUM_MATCH 20
#define NUM_MPATTERN 9

struct update_pattern
{
  char pattern[MAX_BUF];
  int print_cmd[NUM_MATCH];
};


#define SPECIAL1 -1
#define SPECIAL2 -2
#define SPECIAL3 -3
#define SPECIAL4 -4

struct update_pattern up[NUM_MPATTERN] =
 {
  { "^(20[0-2][0-9])-([01][0-9])-([0-3][0-9])"
  " ([0-2][0-9]):([0-5][0-9]):([0-5][0-9]) ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8})$",
    { 1, 2, 3, 4, 5, 6, 7, 8, SPECIAL1, 0 }
  },

  { "^(20[0-2][0-9])-([01][0-9])-([0-3][0-9])"
  " ([0-2][0-9]):([0-5][0-9]):([0-5][0-9]) ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8})"
  " ([0-9A-F]{1})$",
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 }
  },

  { "^(20[0-2][0-9])-([01][0-9])-([0-3][0-9])"
  " ([0-2][0-9]):([0-5][0-9]):([0-5][0-9]) ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8})"
  " ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8}) ([0-9A-F]{2}) ([0-9A-F]{2})"
  " ([0-9A-F]{2}) ([A-Z0-9/_]{4})$",
    { 1, 2, 3, 4, 5, 6, 7, 8, SPECIAL1, 9, 10, 11, 12, 13, 14, SPECIAL2, 0 }
  },

  { "^(20[0-2][0-9])-([01][0-9])-([0-3][0-9])"
  " ([0-2][0-9]):([0-5][0-9]):([0-5][0-9]) ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8})"
  " ([0-9A-F]{1}) ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8}) ([0-9A-F]{2}) ([0-9A-F]{2})"
  " ([0-9A-F]{2}) ([A-Z0-9/_]{4})$",
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, SPECIAL2, 0 }
  },

  { "^(20[0-2][0-9])-([01][0-9])-([0-3][0-9])"
  " ([0-2][0-9]):([0-5][0-9]):([0-5][0-9]) ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8})"
  " ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8}) ([0-9A-F]{2}) ([0-9A-F]{2})"
  " ([0-9A-F]{2}) ([A-Z0-9/_]{4}) ([[:graph:]]{20})$",
    { 1, 2, 3, 4, 5, 6, 7, 8, SPECIAL1, 9, 10, 11, 12, 13, 14, SPECIAL2, 15, 0 }
  },

  { "^(20[0-2][0-9])-([01][0-9])-([0-3][0-9])"
  " ([0-2][0-9]):([0-5][0-9]):([0-5][0-9]) ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8})"
  " ([0-9A-F]{1}) ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8}) ([0-9A-F]{2}) ([0-9A-F]{2})"
  " ([0-9A-F]{2}) ([A-Z0-9/_]{4}) ([[:graph:]]{20})$",
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, SPECIAL2, 16, 0 }
  },

  { "^(20[0-2][0-9])-([01][0-9])-([0-3][0-9])"
  " ([0-2][0-9]):([0-5][0-9]):([0-5][0-9]) ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8})"
  " ([0-9A-F]{1}) ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8}) ([0-9A-F]{2}) ([0-9A-F]{2})"
  " ([0-9A-F]{2}) ([A-Z0-9/_]{4}) ([0-9A-F]{2}) ([A-Z0-9/_]{8})$",
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 0 }
  },

  { "^(20[0-2][0-9])-([01][0-9])-([0-3][0-9])"
  " ([0-2][0-9]):([0-5][0-9]):([0-5][0-9]) ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8})"
  " ([0-9A-F]{1}) ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8}) ([0-9A-F]{2}) ([0-9A-F]{2})"
  " ([0-9A-F]{2}) ([A-Z0-9/_]{4}) ([0-9A-F]{2}) ([A-Z0-9/_]{8})"
  " ([[:graph:]]{20})$",
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 0 }
  },

  { "^(20[0-2][0-9])-([01][0-9])-([0-3][0-9])"
  " ([0-2][0-9]):([0-5][0-9]):([0-5][0-9]) ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8})"
  " ([A-Z0-9/_]{8}) ([A-Z0-9/_]{8}) ([0-9A-F]{2}) ([0-9A-F]{2})"
  " ([0-9A-F]{2}) ([A-Z0-9/_]{4}) # ([[:graph:]]{20})$",
    { 1, 2, 3, 4, 5, 6, 7, 8, SPECIAL3, 9, 10, 11, 12, 13, 14, SPECIAL2, SPECIAL4, 0 }
  }


 };


regex_t rp[NUM_MPATTERN];



void output_substr ( char * output_buf, const char * s, int start, int stop )
{
  int i;

  if ((start >= 0) && (stop >= 0))
  {
    int pos = strlen(output_buf);

    for (i=start; i < stop; i++)
    {
      output_buf[pos] =  s[i];
      pos ++;
    }
    output_buf[pos] = 0;
  }
}

int is_hex_string (const char * s, int start, int stop)
{
  int i;
  for (i=start; i < stop; i++)
  {
    if (!isxdigit(s[i]))
    {
      return 0;
    }
  }

  return 1;
}

int get_hexchar_value (int c)
{
  int nibble = c & 0x0f;

  if ((c >= '0') && (c <= '9'))
  {
    return nibble;
  }

  return nibble + 9;
}

int get_hex_number (const char * s, int start, int stop)
{
  int val = 0;
  int i;
  for (i=start; i < stop; i++)
  {
    val = (val << 4) | get_hexchar_value(s[i]);
  }

  return val;
}


void parse_stats ( char * output_buf, const char * s, int start, int stop )
{
  char buf[100];
  char buf2[20];
  int num_frames = 0;
  int percent_silent_frames = 255;
  int permille_BER = 255;

  if ((stop - start) >= 8)
  {
    if (is_hex_string(s, start, start + 4))
    {
      num_frames = get_hex_number(s, start, start + 4);
    }

    if (is_hex_string(s, start + 4, start + 6))
    {
      percent_silent_frames = get_hex_number(s, start + 4, start + 6);
    }

    if (is_hex_string(s, start + 6, start + 8))
    {
      permille_BER = get_hex_number(s, start + 6, start + 8);
    }
  }

  sprintf(buf, "%.1fs", (num_frames * 0.02));

  if (percent_silent_frames <= 100)
  {
    sprintf(buf2, "_S:%d%%", percent_silent_frames);
    strcat(buf, buf2);
  }

  if (permille_BER < 255)
  {
    sprintf(buf2, "_E:%.1f%%", (permille_BER * 0.1));
    strcat(buf, buf2);
  }

  int pos = strlen(buf);

  while (pos < 20)
  {
    buf[pos] = '_';
    pos ++;
  }

  buf[pos] = 0;

  strcat(output_buf, buf);
}



int main (int argc, char *argv[])
{
  char buf[MAX_BUF];
  char output_buf[MAX_BUF];
  char last_output_buf[MAX_BUF];
  regex_t r1;
  regmatch_t m[NUM_MATCH];
  int i;

  int r = regcomp( &r1, "[TR] \\[[[:graph:]]*\\] \\[PRIVMSG\\] \\[#mheard\\]"
    " \\[((d-[a-z0-9]{3,8})|([a-z0-9]{4,6}-[1-4])): UPDATE OK: UPDATE"
    " ([[:print:]]+)\\]" , REG_EXTENDED );


  if (r != 0)
  {
   buf[0] = 0;
   regerror(r, &r1, buf, sizeof buf);
   fprintf(stderr, "regex error: %s\n", buf);
   return 1;
  }

  for (i=0; i < NUM_MPATTERN; i++)
  {
    r = regcomp( rp + i, up[i].pattern, REG_EXTENDED );
    if (r != 0)
    {
      buf[0] = 0;
      regerror(r, rp + i, buf, sizeof buf);
      fprintf(stderr, "regex #i error: %s\n", buf);
      return 1;
    }
  }


  last_output_buf[0] = 0;

  while (!feof(stdin))
  {
    char * s = fgets(buf, sizeof buf, stdin);

    if (!s) break;

    if (regexec( &r1, s, NUM_MATCH, m, 0) == 0)
    {
      if (m[4].rm_so >= 0)
      {
	s[m[4].rm_eo] = 0;
	char * s2 =  s + m[4].rm_so;
	int j;

	for (j=0; j < NUM_MPATTERN; j++)
	{
	  if (regexec( rp + j, s2, NUM_MATCH, m, 0) == 0)
	  {
	    output_buf[0] = 0;

	    for (i=0; i < NUM_MATCH; i++)
	    {
	      int p = up[j].print_cmd[i];

	      if (p == 0)
	      {
		int pos = strlen(output_buf);

		while (pos < 99)
		{
		  output_buf[pos] = 0x20;
		  pos ++;
		}
		output_buf[pos] = 0;

		if (strcmp(output_buf, last_output_buf) != 0)
		{
		  printf ("%s\n", output_buf);
		  fflush(stdout);
		}
		strcpy (last_output_buf, output_buf);
		break;
	      }

	      switch (p)
	      {
		case SPECIAL1:
		  strcat(output_buf, "0");
		  break;

		case SPECIAL2:
		  strcat(output_buf, "00________");
		  break;

		case SPECIAL3:
		  strcat(output_buf, "1");
		  break;

		case SPECIAL4:
		  parse_stats(output_buf, s2, m[15].rm_so, m[15].rm_eo);
		  break;

		default:
		  output_substr(output_buf, s2, m[p].rm_so, m[p].rm_eo);
		  break;
	      }
	    }
	    break;
	  }
	}
      }
    }
  }

  return 0;

}
