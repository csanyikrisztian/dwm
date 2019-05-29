/* See LICENSE file for copyright and license details.
 *
 * 2019. Krisztian CSANYI <csanyi.krisztian@sitedesign.hu>
 *
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"

/*
 * initialize data to default values
 */
void
init_parameters (struct config * parms)
{
  strncpy (parms->selfgcolor, "#eeeeee", COLORMAXLEN);
  strncpy (parms->selbgcolor, "#005577", COLORMAXLEN);
  strncpy (parms->selbordercolor, "#005577", COLORMAXLEN);
  strncpy (parms->normfgcolor, "#bbbbbb", COLORMAXLEN);
  strncpy (parms->normbgcolor, "#222222", COLORMAXLEN);
  strncpy (parms->normbordercolor, "#444444", COLORMAXLEN);
}

/*
 * trim: get rid of trailing and leading whitespace...
 *       ...including the annoying "\n" from fgets()
 */
char *
trim (char * s)
{
  /* Initialize start, end pointers */
  char *s1 = s, *s2 = &s[strlen (s) - 1];

  /* Trim and delimit right side */
  while ( (isspace (*s2)) && (s2 >= s1) )
    s2--;
  *(s2+1) = '\0';

  /* Trim left side */
  while ( (isspace (*s1)) && (s1 < s2) )
    s1++;

  /* Copy finished string */
  strcpy (s, s1);
  return s;
}

/*
 * parse external parameters file
 *
 * NOTES:
 * - There are millions of ways to do this, depending on your
 *   specific needs.
 *
 * - In general:
 *   a) The client will know which parameters it's expecting
 *      (hence the "struct", with a specific set of parameters).
 *   b) The client should NOT know any specifics about the
 *      configuration file itself (for example, the client
 *      shouldn't know or care about it's name, its location,
 *      its format ... or whether or not the "configuration
 *      file" is even a file ... or a database ... or something
 *      else entirely).
 *   c) The client should initialize the parameters to reasonable
 *      defaults
 *   d) The client is responsible for validating whether the
 *      pararmeters are complete, or correct.
 */
void
parse_config (struct config * parms)
{
  char *s, buff[256];
  FILE *fp = fopen (CONFIG_FILE, "r");
  if (fp == NULL)
  {
    die("Cant open configuration file");
  }

  /* Read next line */
  while ((s = fgets (buff, sizeof buff, fp)) != NULL)
  {
    /* Skip blank lines and comments */
    if (buff[0] == '\n' || buff[0] == '#')
      continue;

    /* Parse name/value pair from line */
    char name[MAXLEN], value[MAXLEN];
    s = strtok (buff, "=");
    if (s==NULL)
      continue;
    else
      strncpy (name, s, MAXLEN);
    s = strtok (NULL, "=");
    if (s==NULL)
      continue;
    else
      strncpy (value, s, MAXLEN);
    trim (value);

    /* Copy into correct entry in parameters struct */
    if (strcmp(name, "selfgcolor")==0)
      strncpy (parms->selfgcolor, value, COLORMAXLEN);
    else if (strcmp(name, "selbgcolor")==0)
      strncpy (parms->selbgcolor, value, COLORMAXLEN);
    else if (strcmp(name, "selbordercolor")==0)
      strncpy (parms->selbordercolor, value, COLORMAXLEN);
    else if (strcmp(name, "normfgcolor")==0)
      strncpy (parms->normfgcolor, value, COLORMAXLEN);
    else if (strcmp(name, "normbgcolor")==0)
      strncpy (parms->normbgcolor, value, COLORMAXLEN);
    else if (strcmp(name, "normbordercolor")==0)
      strncpy (parms->normbordercolor, value, COLORMAXLEN);
    else
      printf ("WARNING: %s/%s: Unknown name/value pair!\n", name, value);
  }

  /* Close file */
  fclose (fp);
}

void
setup_config(void)
{
	init_parameters(&configuration);
	parse_config(&configuration);
}

