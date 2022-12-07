/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int viewonrulestag 	= 1;		 /* 1 means when open applications view will move to tags defined in rules*/
static const char *fonts[]          = { "monospace:size=13" };
static const char dmenufont[]       = "monospace:size=13";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",      NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "librewolf", NULL,     NULL,           2,    0,          0,          -1,        -1 },
	{ "st",        NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,        NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	// { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *terminal[]  = { "st", NULL };
static const char *browser[]  = { "librewolf", NULL };

#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = terminal } },
	{ MODKEY,                       XK_b,      spawn,          {.v = browser } },
	{ MODKEY|ShiftMask,                       XK_b,      togglebar,      {0} },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_m,      spawn,		{.v = (const char*[]){ "st", "-e", "htop", NULL } } },
	{ MODKEY,                       XK_v,      spawn,		SHCMD("vpn-connect") },
	{ MODKEY,                       XK_f,      spawn,		{.v = (const char*[]){ "st", "-e", "lfub", NULL } } },
  // media keys
	{ 0, XF86XK_MonBrightnessUp,	spawn,		{.v = (const char*[]){ "light", "-A", "10", NULL } } },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		{.v = (const char*[]){ "light", "-U", "10", NULL } } },
	{ 0, XF86XK_AudioMute,		    spawn,		SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle && status-volume") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+ && status-volume") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%- && status-volume") },
	{ 0, XF86XK_AudioPrev,		    spawn,		{.v = (const char*[]){ "playerctl", "position", "10-", NULL } } },
	{ 0, XF86XK_AudioNext,		    spawn,		{.v = (const char*[]){  "playerctl", "position", "10+", NULL } } },
	{ 0, XF86XK_AudioPlay,		    spawn,		{.v = (const char*[]){ "playerctl", "play-pause", NULL } } },
	{ 0, XK_F7,                     spawn,		{.v = (const char*[]){ "st", "-e", "pulsemixer", NULL } } },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	{ 0, XF86XK_Display,      		spawn,		{.v = (const char*[]){ "displayselect", NULL } } },
	{ 0, XF86XK_Search,             spawn,		{.v = (const char*[]){ "passmenu", NULL } } },
	{ 0, XK_Insert,      		    spawn,	    SHCMD("theme reverse") },
	{ MODKEY, XK_Insert,      		spawn,	    SHCMD("theme change") },
	{ MODKEY, XK_Delete,      		spawn,	    SHCMD("theme comp-toggle") },
	{ ControlMask, XK_Delete,      		spawn,	    SHCMD("fillstuff") },
	{ MODKEY|ShiftMask,             XK_BackSpace, quit,        {0} },
	// keys for azerty keyboard
	{ MODKEY,                       XK_semicolon, focusmon,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_semicolon, tagmon,      {.i = +1 } },
	{ MODKEY,                       XK_agrave, view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_agrave, tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	TAGKEYS(                        XK_ampersand,              0)
	TAGKEYS(                        XK_eacute,                 1)
	TAGKEYS(                        XK_quotedbl,               2)
	TAGKEYS(                        XK_apostrophe,             3)
	TAGKEYS(                        XK_parenleft,              4)
	TAGKEYS(                        XK_minus,                  5)
	TAGKEYS(                        XK_egrave,                 6)
	TAGKEYS(                        XK_underscore,             7)
	TAGKEYS(                        XK_ccedilla,               8)
	{ MODKEY|Mod4Mask,              XK_k,      incrgaps,       {.i = +5 } },
	{ MODKEY|Mod4Mask,              XK_j,      incrgaps,       {.i = -5 } },
	{ MODKEY|Mod4Mask,              XK_t,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask,              XK_d,      defaultgaps,    {0} },
	// keys for us keyboard
	// { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	// { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	// { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	// { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	// TAGKEYS(                        XK_1,                      0)
	// TAGKEYS(                        XK_2,                      1)
	// TAGKEYS(                        XK_3,                      2)
	// TAGKEYS(                        XK_4,                      3)
	// TAGKEYS(                        XK_5,                      4)
	// TAGKEYS(                        XK_6,                      5)
	// TAGKEYS(                        XK_7,                      6)
	// TAGKEYS(                        XK_8,                      7)
	// TAGKEYS(                        XK_9,                      8)
	// keys not in use
	// { MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_minus,      incrihgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_minus,      incrihgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_egrave,      incrivgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_egrave,      incrivgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_underscore,      incrohgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_underscore,      incrohgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_ccedilla,      incrovgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_ccedilla,      incrovgaps,     {.i = -1 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = terminal } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

void
xrdb(const Arg *arg)
{
  loadxrdb();
  int i;
  for (i = 0; i < LENGTH(colors); i++)
                scheme[i] = drw_scm_create(drw, colors[i], 3);
  focus(NULL);
  arrange(NULL);
}


/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
	{ "xrdb",    xrdb },
};
