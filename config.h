/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
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
	/* class      instance    title       tags mask     isfloating   monitor    float x,y,w,h         floatborderpx*/
	{ NULL,		  NULL,		  NULL,		  0,				 0,			  -1,			 0,0,0,0,				  0 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
#include "horizgrid.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",		tile },    /* first entry is default */
	{ "><>",		NULL },    /* no layout function means floating behavior */
 	{ "[@]",		spiral },
 	{ "[\\]",	dwindle },
	{ "|||",		col },
	{ "###",    horizgrid },
	{ "|M|",		centeredmaster },
	{ ">M>",    centeredfloatingmaster },
	{ "[M]",    monocle },
	{ NULL,		NULL },
};

/* key definitions */
#define SUPER	Mod4Mask
#define SHIFT	ShiftMask
#define ALT		Mod1Mask
#define CTRL	ControlMask
#define TAGKEYS(KEY,TAG) \
	{ SUPER,                KEY,      view,           {.ui = 1 << TAG} }, \
	{ SUPER|CTRL,				KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ SUPER|SHIFT,          KEY,      tag,            {.ui = 1 << TAG} }, \
	{ SUPER|CTRL|SHIFT,		KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "/bin/sh", "-c", "st", NULL };

static Key keys[] = {
	/* modifier								key			function				argument */
	{ SUPER,									XK_d,			spawn,				{.v = dmenucmd } },
	{ SUPER,									XK_Return,	spawn,				{.v = termcmd } },
	//{ SUPER,								XK_b,			togglebar,			{0} },
//	Go up & down the stack
	{ SUPER,									XK_j,			focusstack,			{.i = +1 } },
	{ SUPER,									XK_k,			focusstack,			{.i = -1 } },
//	swap focus between clients? tags?
	{ SUPER,									XK_Tab,		swapfocus,			{.i = -1 } },
//	switch between master and stack
	{ SUPER,									XK_g,			switchcol,			{0} },
//	Increase clients in master???
	{ SUPER,									XK_q,			incnmaster,			{.i = +1 } },
	{ SUPER,									XK_w,			incnmaster,			{.i = -1 } },
// Change size of master
	{ SUPER|SHIFT,							XK_h,			setmfact,			{.f = -0.05} },
	{ SUPER|SHIFT,							XK_l,			setmfact,			{.f = +0.05} },
// ?
	//{ SUPER,								XK_Return,	zoom,					{0} },
	//{ SUPER,								XK_Tab,		view,					{0} },
//	{ SUPER|SHIFT,					XK_c,			killclient,			{0} },
//	Change between layouts
	{ SUPER,									XK_F1,		setlayout,			{.v = &layouts[0]} }, // tile
	{ SUPER,									XK_F2,		setlayout,			{.v = &layouts[1]} }, // floating
	{ SUPER,									XK_F3,		setlayout,			{.v = &layouts[2]} }, // spiral
	{ SUPER,									XK_F4,		setlayout,			{.v = &layouts[3]} }, // dwindle
	{ SUPER,									XK_F6,		setlayout,			{.v = &layouts[4]} }, // col
	{ SUPER,									XK_F7,		setlayout,			{.v = &layouts[5]} }, // horizgrid
	{ SUPER,									XK_F8,		setlayout,			{.v = &layouts[6]} }, // centeredmaster
	{ SUPER,									XK_F9,		setlayout,			{.v = &layouts[7]} }, // centeredfloatingmaster
	{ SUPER,									XK_F10,		setlayout,			{.v = &layouts[8]} }, // monocle
	{ SUPER,									XK_comma,	cyclelayout,		{.i = -1 } },
	{ SUPER,									XK_period,	cyclelayout,		{.i = +1 } },
	{ SUPER,									XK_space,	setlayout,			{0} },
// Toggle floating/sticky/fullscr
	{ SUPER,									XK_u,			togglefloating,	{0} },
	{ SUPER|SHIFT,							XK_u,			togglesticky,		{0} },
	{ SUPER,									XK_F11,		togglefullscr,		{0} },
// ?
	//{ SUPER,								XK_0,			view,					{.ui = ~0 } },
	//{ SUPER|SHIFT,						XK_0,			tag,					{.ui = ~0 } },
// Move between monitors
	//{ SUPER,								XK_comma,	focusmon,			{.i = -1 } },
	//{ SUPER,								XK_period,	focusmon,			{.i = +1 } },
	//{ SUPER|SHIFT,						XK_comma,	tagmon,				{.i = -1 } },
	//{ SUPER|SHIFT,						XK_period,	tagmon,				{.i = +1 } },
//	Focus/Move Tags
	{ SUPER,									XK_z,			viewtoleft,			{0} },
	{ SUPER,									XK_x,			viewtoright,		{0} },
	{ SUPER|SHIFT,							XK_z,			tagtoleft,			{0} },
	{ SUPER|SHIFT,							XK_x,			tagtoright,			{0} },
//	Move floating window to spot 1-9 on screen
	{ SUPER|CTRL,							XK_q,			moveplace,			{.ui = WIN_NW }},
	{ SUPER|CTRL,							XK_w,			moveplace,			{.ui = WIN_N  }},
	{ SUPER|CTRL,							XK_e,			moveplace,			{.ui = WIN_NE }},
	{ SUPER|CTRL,							XK_a,			moveplace,			{.ui = WIN_W  }},
	{ SUPER|CTRL,							XK_s,			moveplace,			{.ui = WIN_C  }},
	{ SUPER|CTRL,							XK_d,			moveplace,			{.ui = WIN_E  }},
	{ SUPER|CTRL,							XK_z,			moveplace,			{.ui = WIN_SW }},
	{ SUPER|CTRL,							XK_x,			moveplace,			{.ui = WIN_S  }},
	{ SUPER|CTRL,							XK_c,			moveplace,			{.ui = WIN_SE }},
//	Go to tag
	TAGKEYS(									XK_1,									0)
	TAGKEYS(									XK_2,									1)
	TAGKEYS(									XK_3,									2)
	TAGKEYS(									XK_4,									3)
	TAGKEYS(									XK_5,									4)
	TAGKEYS(									XK_6,									5)
	TAGKEYS(									XK_7,									6)
	TAGKEYS(									XK_8,									7)
	TAGKEYS(									XK_9,									8)
// ?
	{ SUPER|SHIFT,							XK_F5,		quit,					{0} },
// Restart dwm
	{ SUPER,									XK_F5,      quit,					{1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask     button          function        argument */
	{ ClkLtSymbol,				0,             Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,             Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,             Button2,        zoom,           {0} },
	//{ ClkStatusText,      0,             Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         SUPER,			Button1,        movemouse,      {0} },
	{ ClkClientWin,         SUPER,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         SUPER,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,             Button1,        view,           {0} },
	{ ClkTagBar,            0,             Button3,        toggleview,     {0} },
	{ ClkTagBar,            SUPER,         Button1,        tag,            {0} },
	{ ClkTagBar,            SUPER,         Button3,        toggletag,      {0} },
};
