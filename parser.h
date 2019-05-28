#define MAXLEN 80
#define CONFIG_FILE ".config/dwm/config"

struct config
{
  char selfgcolor[MAXLEN];
}
  config;

struct config configuration;

void setup_config(void);
