/* See LICENSE file for copyright and license details. */
#define TERMINAL "alacritty"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",           NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox",        NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "Alacritty",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,             NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
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
};

/* key definitions */
#define MODKEYL Mod4Mask
#define MODKEYR Mod5Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEYL,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEYL|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEYL|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEYL|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]     = { TERMINAL, NULL };

#include "movestack.c"
static Key keys[] = {
    // Open Programs
	/* modifier                     key                  function        argument */
	{ MODKEYL,                       XK_r,               spawn,          {.v = dmenucmd } },
	{ MODKEYL,                       XK_Return,          spawn,          {.v = termcmd } },
	{ MODKEYL,                       XK_w,               spawn,          SHCMD("$BROWSER") },
	{ MODKEYL|ShiftMask,             XK_w,               spawn,          SHCMD("d_search") },
	{ MODKEYR,                       XK_c,               spawn,          SHCMD("YACReaderLibrary") },
	{ MODKEYL,                       XK_c,               spawn,          SHCMD("speedcrunch") },
	{ MODKEYR,                       XK_d,               spawn,          SHCMD("soulseekqt") },
	{ MODKEYL,                       XK_m,               spawn,          SHCMD(TERMINAL" -e ncmpcpp") },
	{ MODKEYL,                       XK_f,               spawn,          SHCMD("pcmanfm") },
	{ MODKEYL,                       XK_apostrophe,      spawn,          SHCMD("d_emoji") },

	{ MODKEYL,                       XK_F2,              spawn,          SHCMD("d_edit") },
	{ MODKEYL,                       XK_F3,              spawn,          SHCMD("d_rbw") },
	{ MODKEYL,                       XK_F10,             spawn,          SHCMD(TERMINAL" -e pulsemixer") },
	{ MODKEYL,                       XK_F11,             spawn,          SHCMD(TERMINAL" -e start-torrent") },

    //media
	{ MODKEYL,                       XK_minus,           spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -2500") },
	{ MODKEYL,                       XK_equal,           spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +2500") },
	{ MODKEYL|ShiftMask,             XK_equal,            spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },
	{ MODKEYL,                       XK_p,               spawn,          SHCMD("playerctl -p mpd play-pause") },

    // Client & Tag Manipulation
	{ MODKEYL,                       XK_b,               togglebar,      {0} },
	{ MODKEYL,                       XK_j,               focusstack,     {.i = +1 } },
	{ MODKEYL,                       XK_k,               focusstack,     {.i = -1 } },
	{ MODKEYL,                       XK_i,               incnmaster,     {.i = +1 } },
	{ MODKEYL,                       XK_d,               incnmaster,     {.i = -1 } },
	{ MODKEYL,                       XK_h,               setmfact,       {.f = -0.05} },
	{ MODKEYL,                       XK_l,               setmfact,       {.f = +0.05} },
	{ MODKEYL|ShiftMask,             XK_j,               movestack,      {.i = +1 } },
	{ MODKEYL|ShiftMask,             XK_k,               movestack,      {.i = -1 } },
	{ MODKEYL,                       XK_Tab,             view,           {0} },
	{ MODKEYL,                       XK_q,               killclient,     {0} },
	{ MODKEYL,                       XK_t,               setlayout,      {.v = &layouts[0]} },
	{ MODKEYL,                       XK_f,               setlayout,      {.v = &layouts[1]} },
	{ MODKEYL,                       XK_u,               setlayout,      {.v = &layouts[2]} },
	{ MODKEYL,                       XK_space,           zoom,           {0} },
	{ MODKEYL|ShiftMask,             XK_space,           togglefloating, {0} },
	{ MODKEYL,                       XK_0,               view,           {.ui = ~0 } },
	{ MODKEYL|ShiftMask,             XK_0,               tag,            {.ui = ~0 } },
	{ MODKEYL,                       XK_comma,           focusmon,       {.i = -1 } },
	{ MODKEYL,                       XK_period,          focusmon,       {.i = +1 } },
	{ MODKEYL|ShiftMask,             XK_comma,           tagmon,         {.i = -1 } },
	{ MODKEYL|ShiftMask,             XK_period,          tagmon,         {.i = +1 } },
	TAGKEYS(                         XK_1,                               0)
	TAGKEYS(                         XK_2,                               1)
	TAGKEYS(                         XK_3,                               2)
	TAGKEYS(                         XK_4,                               3)
	TAGKEYS(                         XK_5,                               4)
	TAGKEYS(                         XK_6,                               5) TAGKEYS(XK_7,6)
	TAGKEYS(                         XK_8,                               7)
	TAGKEYS(                         XK_9,                               8)
	{ MODKEYL|ShiftMask,             XK_q,               quit,           {1} },
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
	{ ClkClientWin,         MODKEYL,        Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEYL,        Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEYL,        Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEYL,        Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEYL,        Button3,        toggletag,      {0} },
};

