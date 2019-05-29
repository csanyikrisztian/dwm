#define MAXLEN 80
#define COLORMAXLEN 8
#define CONFIG_FILE ".config/dwm/config"

struct config
{
  char normbordercolor[COLORMAXLEN];
  char normbgcolor[COLORMAXLEN];
  char normfgcolor[COLORMAXLEN];
  char selbordercolor[COLORMAXLEN];
  char selbgcolor[COLORMAXLEN];
  char selfgcolor[COLORMAXLEN];
}
  config;

struct config configuration;

void setup_config(void);
