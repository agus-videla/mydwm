/* See LICENSE file for copyright and license details. */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono:size=10", "Symbols Nerd Font:size=9", "Noto Color Emoji:size=9" };
static const char dmenufont[]       = "monospace:size=10"; 
static const char col_gray1[]       = "#1A1D1F";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_green[]        ="#1B5C35";
static const char col_orange[]      = "#AC741C";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_green,  col_orange  },
};

/* scratchpads */
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "60x20",  NULL };
const char *calc1[] = {"speedcrunch", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"SpeedCrunch", calc1},
};

/* tagging */
static const char *tags[] = { "", "爵", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance        title           tags mask        isfloating  isterminal   noswallow monitor */
	{ "Gimp",           NULL,           NULL,           0,               1,          0,           0,        -1 },
	{ "qutebrowser",    NULL,           NULL,           2,               0,          0,          -1,        -1 },
	{ TERMCLASS,        NULL,           NULL,           0,               0,          1,           0,        -1 },
	{ TERMCLASS,        NULL,           "ncmpcpp",      4,               0,          1,           0,        -1 },
	{ "Pcmanfm",        NULL,           NULL,           8,               0,          0,           0,        -1 },
	{ "zoom",           NULL,           NULL,           0,               1,          0,           0,        -1 },
	{ "PacketTracer",   NULL,           NULL,           0,               1,          0,           0,        -1 },
	{ NULL,             NULL,           "Event Tester", 0,               1,          0,           1,        -1 }, /* xev */
	{ NULL,		        "spterm",		NULL,		    SPTAG(0),		 1,			 1,           0,        -1 },
	{ NULL,		        "SpeedCrunch",	NULL,		    SPTAG(1),		 0,			 0,           0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[D]",      deck },
};

/* key definitions */
#define SUPER Mod4Mask
#define CONTEXT Mod3Mask
#define TAGKEYS(KEY,TAG) \
	{ SUPER,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ SUPER|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ SUPER|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ SUPER|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_green, "-sf", col_gray4, NULL };
static const char *termcmd[]     = { TERMINAL, NULL };

#include <X11/XF86keysym.h>
#include "movestack.c"
static Key keys[] = {
    // Open Programs
	/* modifier                     key                  function        argument */
	{ SUPER,                       XK_r,               spawn,          {.v = dmenucmd } },
	{ SUPER,                       XK_Return,          spawn,          {.v = termcmd } },
	{ SUPER,                       XK_w,               spawn,          SHCMD("$BROWSER") },
	{ SUPER|ShiftMask,             XK_w,               spawn,          SHCMD("d_search") },
	{ CONTEXT,                     XK_c,               spawn,          SHCMD("YACReaderLibrary") },
	//{ SUPER,                     XK_c,               spawn,          SHCMD("speedcrunch") },
	{ SUPER,                       XK_m,               spawn,          SHCMD(TERMINAL" -t ncmpcpp -e ncmpcpp") },
	{ SUPER|ShiftMask,             XK_m,               spawn,          SHCMD("soulseekqt") },
	{ SUPER,                       XK_o,               spawn,          SHCMD("obsidian") },
	{ CONTEXT,                     XK_f,               spawn,          SHCMD("pcmanfm") },
	{ SUPER,                       XK_apostrophe,      spawn,          SHCMD("d_emoji") },
	{ SUPER,                       XK_n,               spawn,          SHCMD("note-capture") },

	{ SUPER,                       XK_F2,              spawn,          SHCMD("d_edit") },
	{ SUPER,                       XK_F3,              spawn,          SHCMD("d_rbw") },
	{ SUPER,                       XK_F10,             spawn,          SHCMD(TERMINAL" -e pulsemixer") },
	{ SUPER,                       XK_F11,             spawn,          SHCMD(TERMINAL" -e start-torrent") },
	{ SUPER,                       XK_Print,           spawn,          SHCMD("d_scrot") },

    //media
	{ SUPER,                       XK_minus,           spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -2500 && pkill -RTMIN+10 dwmblocks") },
	{ SUPER,                       XK_equal,           spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +2500 && pkill -RTMIN+10 dwmblocks") },
	{ SUPER|ShiftMask,             XK_equal,           spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle && pkill -RTMIN+10 dwmblocks") },
	{ 0,            XF86XK_AudioLowerVolume,           spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -2500 && pkill -RTMIN+10 dwmblocks") },
	{ 0,            XF86XK_AudioRaiseVolume,           spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +2500 && pkill -RTMIN+10 dwmblocks") },
	{ 0,                   XF86XK_AudioMute,           spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle && pkill -RTMIN+10 dwmblocks") },
	{ SUPER,                       XK_p,               spawn,          SHCMD("mpc toggle") },
	{ SUPER|ShiftMask,             XK_p,               spawn,          SHCMD("mpc stop") },
	{ SUPER,                       XK_comma,           spawn,          SHCMD("mpc prev") },
	{ SUPER,                       XK_period,          spawn,          SHCMD("mpc next") },

    //brightness
	{ SUPER,                       XK_bracketleft,     spawn,          SHCMD("light -U 5 && pkill -RTMIN+13 dwmblocks") },
	{ SUPER,                       XK_bracketright,    spawn,          SHCMD("light -A 5 && pkill -RTMIN+13 dwmblocks") },
	{ 0,                    XF86XK_MonBrightnessUp,    spawn,          SHCMD("light -A 5 && pkill -RTMIN+13 dwmblocks") },
	{ 0,                  XF86XK_MonBrightnessDown,    spawn,          SHCMD("light -U 5 && pkill -RTMIN+13 dwmblocks") },

	{ SUPER|ShiftMask,               XK_Return,  	   togglescratch,  {.ui = 0 } },
	{ SUPER,                         XK_c,  	       togglescratch,  {.ui = 1 } },

    // Client & Tag Manipulation
	{ SUPER,                       XK_b,               togglebar,      {0} },
	{ SUPER,                       XK_j,               focusstack,     {.i = +1 } },
	{ SUPER,                       XK_k,               focusstack,     {.i = -1 } },
	{ SUPER,                       XK_i,               incnmaster,     {.i = +1 } },
	{ SUPER,                       XK_d,               incnmaster,     {.i = -1 } },
	{ SUPER,                       XK_h,               setmfact,       {.f = -0.05} },
	{ SUPER,                       XK_l,               setmfact,       {.f = +0.05} },
	{ SUPER|ShiftMask,             XK_j,               movestack,      {.i = +1 } },
	{ SUPER|ShiftMask,             XK_k,               movestack,      {.i = -1 } },
	{ SUPER,                       XK_s,               togglesticky,   {0} },
	{ SUPER,                       XK_Tab,             view,           {0} },
	{ SUPER,                       XK_q,               killclient,     {0} },
	{ SUPER,                       XK_t,               setlayout,      {.v = &layouts[0]} },
	{ SUPER,                       XK_y,               setlayout,      {.v = &layouts[1]} },
	{ SUPER|ShiftMask,             XK_u,               setlayout,      {.v = &layouts[2]} },
	{ SUPER,                       XK_u,               setlayout,      {.v = &layouts[3]} },
	{ SUPER,                       XK_f,               togglefullscr,  {0} },
	{ SUPER,                       XK_space,           zoom,           {0} },
	{ SUPER|ShiftMask,             XK_space,           togglefloating, {0} },
	{ SUPER,                       XK_0,               view,           {.ui = ~0 } },
	{ SUPER|ShiftMask,             XK_0,               tag,            {.ui = ~0 } },
	//{ SUPER,                       XK_comma,           focusmon,       {.i = -1 } },
	//{ SUPER,                       XK_period,          focusmon,       {.i = +1 } },
	{ SUPER|ShiftMask,             XK_comma,           tagmon,         {.i = -1 } },
	{ SUPER|ShiftMask,             XK_period,          tagmon,         {.i = +1 } },
	TAGKEYS(                       XK_1,                               0)
	TAGKEYS(                       XK_2,                               1)
	TAGKEYS(                       XK_3,                               2)
	TAGKEYS(                       XK_4,                               3)
	{ SUPER|ShiftMask,             XK_q,               quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
 	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
 	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
 	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         SUPER,          Button1,        movemouse,      {0} },
	{ ClkClientWin,         SUPER,          Button2,        togglefloating, {0} },
	{ ClkClientWin,         SUPER,          Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            SUPER,          Button1,        tag,            {0} },
	{ ClkTagBar,            SUPER,          Button3,        toggletag,      {0} },
};

