/*  ____ _____  */
/* |  _ \_   _|  Derek Taylor (DistroTube) */
/* | | | || |  	http://www.youtube.com/c/DistroTube */
/* | |_| || |  	http://www.gitlab.com/dwt1/ */
/* |____/ |_|  	*/ 

#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx = 2;   /* border pixel of windows */
static const unsigned int snap     = 32;  /* snap pixel */
static const unsigned int gappx    = 6;   /* pixel gap between clients */
static const int showbar           = 1;   /* 0 means no bar */
static const int topbar            = 1;   /* 0 means bottom bar */
static const int horizpadbar       = 6;   /* horizontal padding for statusbar */
static const int vertpadbar        = 7;   /* vertical padding for statusbar */
/* Mononoki Nerd Font must be installed from AUR nerd-fonts-complete.
 * Otherwise, your default font will be Hack which is found in the standard
 * Arch repos and is listed as a dependency for this build. JoyPixels is also
 * a hard dependency and makes colored fonts and emojis possible.
 */
static const char *fonts[]     = {"Mononoki Nerd Font:size=9:antialias=true:autohint=true",
                                  "Hack:size=8:antialias=true:autohint=true",
                                  "JoyPixels:size=10:antialias=true:autohint=true"
						     	};
static const char col_1[]  = "#282c34"; /* background color of bar */
static const char col_2[]  = "#282c34"; /* border color unfocused windows */
static const char col_3[]  = "#d7d7d7";
static const char col_4[]  = "#924441"; /* border color focused windows and tags */
/* bar opacity 
 * 0xff is no transparency.
 * 0xee adds wee bit of transparency.
 * 0xdd adds adds a bit more transparency.
 * Play with the value to get desired transparency.
 */
static const unsigned int baralpha    = 0xff; 
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]        = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_3, col_1, col_2 },
	[SchemeSel]  = { col_3, col_4, col_4 },
};
static const unsigned int alphas[][3] = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "", "", "", "ﴬ", "", "", "", "", "" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Planner",  NULL,       NULL,       1 << 3,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "Tile",      tile },    /* first entry is default */
	{ "Float",      NULL },    /* no layout function means floating behavior */
	{ "Monocle",      monocle },
	{ "Grid",      grid },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                       CHAIN,    KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           CHAIN,    KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             CHAIN,    KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, CHAIN,    KEY,      toggletag,      {.ui = 1 << TAG} },
#define CMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* dmenu */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* If you are using the standard dmenu program, use the following. */
static const char *dmenucmd[]    = { "dmenu_run", "-p", "Run: ", NULL };
/* If you are using the dmenu-distrotube-git program, use the following for a cooler dmenu! */
/* static const char *dmenucmd[]    = { "dmenu_run", "-g", "10", "-l", "48", "-p", "Run: ", NULL }; */

/* the st terminal with tabbed */
static const char *termcmd[]     = { "st", NULL };
/* An alternative way to launch st along with the fish shell */
/* static const char *termcmd[]     = { "st", "-e fish", NULL }; */
static const char *tabtermcmd[]  = { "tabbed", "-r", "2", "st", "-w", "''", NULL };

/* volume keys*/
static const char *upvol[] = { "amixer", "sset", "'Master'", "+5%", NULL };
static const char *downvol[] = { "amixer", "sset", "Master", "-5%", NULL };
static const char *mutevol[] = { "amixer",  "-D", "pulse", "set", "Master", "1+", "toggle", NULL };
 
/* backlight */
static const char *brightnessup[] = { "lux", "-a" "5%", NULL };
static const char *brightnessdown[] = { "lux", "-s", "5%", NULL };

static Key keys[] = {
	/* modifier             chain key  key        function        argument */
	{ MODKEY,               -1,        XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,               -1,        XK_Return, spawn,          {.v = termcmd } },
	{ Mod1Mask,             -1,        XK_Return, spawn,          {.v = tabtermcmd } },
	{ MODKEY,               -1,        XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,     -1,        XK_Left,   rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,     -1,        XK_Right,  rotatestack,    {.i = -1 } },
	{ MODKEY,               -1,        XK_Left,   focusstack,     {.i = +1 } },
	{ MODKEY,               -1,        XK_Right,  focusstack,     {.i = -1 } },
	{ MODKEY,               -1,        XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,               -1,        XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,               -1,        XK_Up,     setmfact,       {.f = -0.05} },
	{ MODKEY,               -1,        XK_Down,   setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,   -1,        XK_Return, zoom,           {0} },
	{ MODKEY,               -1,        XK_Tab,    view,           {0} },
	{ MODKEY,     			-1,        XK_q,      killclient,     {0} },

    /* Layout manipulation */
	{ MODKEY,               -1,        XK_backslash,    cyclelayout,    {.i = -1 } },
	{ MODKEY|ShiftMask,     -1,        XK_backslash,    cyclelayout,    {.i = +1 } },
	//{ MODKEY,               -1,        XK_space,  setlayout,      {0} },
	//{ MODKEY|ShiftMask,     -1,        XK_space,  togglefloating, {0} },

    /* Switch to specific layouts */
	{ MODKEY,               -1,        XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,               -1,        XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,               -1,        XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,               -1,        XK_g,      setlayout,      {.v = &layouts[3]} },

	{ MODKEY,               -1,        XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,     -1,        XK_0,      tag,            {.ui = ~0 } },

    /* Switching between monitors */
	{ MODKEY,               -1,        XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,               -1,        XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,     -1,        XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     -1,        XK_period, tagmon,         {.i = +1 } },
	
    /* Keybindings for programs using the format SUPER + ALT + "key" */
	{ MODKEY|Mod1Mask,      -1,        XK_s,      spawn,          CMD("tabbed -r 2 surf -pe x '.surf/html/homepage.html'") },
	{ MODKEY|Mod1Mask,      -1,        XK_f,      spawn,          CMD("firefox") },
	{ MODKEY|Mod1Mask,      -1,        XK_m,      spawn,          CMD("mailspring") },
  // { MODKEY|Mod1Mask,      -1,        XK_f,      spawn,          CMD("pcmanfm") },
	{ MODKEY|Mod1Mask,      -1,        XK_b,      spawn,          CMD("blueman-manager") },
	
	/* Utility Keys (volume, brightness, microphone, currently playing media) */
	{ 0,                    -1, XF86XK_AudioLowerVolume,   spawn, CMD("amixer sset Master 5%- && kill -49 $(pidof dwmblocks)") },
  { 0,                    -1, XF86XK_AudioMute,          spawn, CMD("amixer -D pulse set Master 1+ toggle && kill -49 $(pidof dwmblocks)")},
  { 0,                    -1, XF86XK_AudioRaiseVolume,   spawn, CMD("amixer sset Master 5%+ && kill -49 $(pidof dwmblocks)") },
	{ 0,                    -1, XF86XK_AudioMicMute,       spawn, CMD("amixer set Capture toggle | gawk 'match($0, /Front Left.*\[(.*)\]/, a) {print a[1]}' | xargs notify-send --hint=int:transient:1 -i \"audio-input-microphone\" \"Mic switched: $1\"") },
  { 0,                    -1, XF86XK_MonBrightnessUp,    spawn, {.v = brightnessup} },
  { 0,                    -1, XF86XK_MonBrightnessDown,  spawn, {.v = brightnessdown} },
  { MODKEY,               -1, XF86XK_AudioRaiseVolume,   spawn, CMD("playerctl next")},
	{ MODKEY,               -1, XF86XK_AudioLowerVolume,   spawn, CMD("playerctl previous") },
	{ MODKEY,               -1, XF86XK_AudioMute,          spawn, CMD("playerctl play-pause") },

	/* Toggle picom */
	{ MODKEY,               -1, XF86XK_Favorites,          spawn, CMD("/home/zaedus/.local/bin/togglepicom") },
    /* Dmenu scripts launched with emacs-style keychords SUPER + p followed by "key" */
	{ MODKEY,               XK_p,      XK_e,      spawn,          CMD("/home/zaedus/.dmscripts/dmconf") },
	{ MODKEY,               XK_p,      XK_i,      spawn,          CMD("/home/zaedus/.dmscripts/dmscrot") },
	{ MODKEY,               XK_p,      XK_k,      spawn,          CMD("/home/zaedus/.dmscripts/dmkill") },
	{ MODKEY,               XK_p,      XK_l,      spawn,          CMD("/home/zaedus/.dmscripts/dmlogout") },
	{ MODKEY,               XK_p,      XK_m,      spawn,          CMD("/home/zaedus/.dmscripts/dman") },
	{ MODKEY,               XK_p,      XK_r,      spawn,          CMD("/home/zaedus/.dmscripts/dmred") },
	{ MODKEY,               XK_p,      XK_s,      spawn,          CMD("/home/zaedus/.dmscripts/dmsearch") },
	{ MODKEY,               XK_p,      XK_p,      spawn,          CMD("passmenu") },
	{ MODKEY,               XK_p,      XK_j,      spawn,          CMD("dmenu-emoji") },

	TAGKEYS(                -1,        XK_1,                      0)
	TAGKEYS(                -1,        XK_2,                      1)
	TAGKEYS(                -1,        XK_3,                      2)
	TAGKEYS(                -1,        XK_4,                      3)
	TAGKEYS(                -1,        XK_5,                      4)
	TAGKEYS(                -1,        XK_6,                      5)
	TAGKEYS(                -1,        XK_7,                      6)
	TAGKEYS(                -1,        XK_8,                      7)
	TAGKEYS(                -1,        XK_9,                      8)
	{ MODKEY|ShiftMask,     -1,        XK_q,	  quit,		      {0} },
    { MODKEY|ShiftMask,     -1,        XK_r,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click           event mask   button          function        argument */
	{ ClkLtSymbol,     0,           Button1,        setlayout,      {0} },
	{ ClkLtSymbol,     0,           Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,     0,           Button2,        zoom,           {0} },
	{ ClkStatusText,   0,           Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,    MODKEY,      Button1,        movemouse,      {0} },
	{ ClkClientWin,    MODKEY,      Button2,        togglefloating, {0} },
	{ ClkClientWin,    MODKEY,      Button3,        resizemouse,    {0} },
	{ ClkTagBar,       0,           Button1,        view,           {0} },
	{ ClkTagBar,       0,           Button3,        toggleview,     {0} },
	{ ClkTagBar,       MODKEY,      Button1,        tag,            {0} },
	{ ClkTagBar,       MODKEY,      Button3,        toggletag,      {0} },
};


