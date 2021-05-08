/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cpu_perc            cpu usage in percent            NULL
 * cpu_freq            cpu frequency in MHz            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/")
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * separator           string to echo                  NULL
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 *                                                     NULL on OpenBSD
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 */

#define BGCOLOR "#3f4452"
#define BG "^b"BGCOLOR"^" 
#define FG "^c"BGCOLOR"^" 
#define D "^d^"

#define opening  " "FG"^d^"BG""
#define closing  "^d^"FG"^d^ "

static const struct arg args[] = {
	/* function format          argument */
	{separator, "%s", opening},
	{ datetime, "^c#d19a66^ ^d^"BG"%s ","%a %d/%m/%y %H:%M" },
	{separator, "%s", closing},
	{separator, "%s", opening},
	{brightness, "^c#56b6c2^ ^d^"BG"%s%%", " "},
	{run_command, " | ^c#98c379^ ^d^"BG"%s%%", "pamixer --get-volume"},
//{vol_perc, " %s", "/dev/mixer"},
	{separator, "%s", closing},
	{separator, "%s", opening},
	{ cpu_perc,  "^c#61afef^ ^d^"BG"%s%% ", ""},
	{ram_used, "| ^c#98c379^ ^d^"BG"%s ", ""},
	{separator, "%s", closing},
	{separator, "%s", opening},
	{wifi_essid, "^c#e5c07b^  ^d^"BG"%s ", "wlp3s0"},
	{ipv4, "%s |", "wlp3s0"},
	{netspeed_rx, " ^c#98c379^ ^d^"BG" %s", "wlp3s0"},
	{netspeed_tx, "^c#e06c75^  ^d^"BG"%s| ", "wlp3s0"},
	{netstat, "^c#98c379^  ^d^"BG"%s ", ""},
  {wireguard, "| ^c#98c379^廬 ^d^"BG"%s ", ""},
	{wifi_perc, "|  %s%%", "wlp3s0"},
	{separator, "%s", closing},
};
