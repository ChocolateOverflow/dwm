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
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
	{ "|||",      col },
	{ "###",      horizgrid },
	{ "[M]",      monocle },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
//static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier								key			function				argument */
	//{ MODKEY,								XK_p,			spawn,				{.v = dmenucmd } },
	//{ MODKEY|ShiftMask,					XK_Return,	spawn,				{.v = termcmd } },
	//{ MODKEY,								XK_b,			togglebar,			{0} },
//	Go up & down the stack
	{ MODKEY,								XK_j,			focusstack,			{.i = +1 } },
	{ MODKEY,								XK_k,			focusstack,			{.i = -1 } },
//	swap focus between clients? tags?
	{ MODKEY,								XK_Tab,		swapfocus,			{.i = -1 } },
//	switch between master and stack
	{	MODKEY,								XK_g,			switchcol,			{0} },
//	Increase clients in master???
	{ MODKEY,								XK_i,			incnmaster,			{.i = +1 } },
	{ MODKEY,								XK_d,			incnmaster,			{.i = -1 } },
// Change size of master
	{ MODKEY|ShiftMask,					XK_h,			setmfact,			{.f = -0.05} },
	{ MODKEY|ShiftMask,					XK_l,			setmfact,			{.f = +0.05} },
// ?
	//{ MODKEY,								XK_Return,	zoom,					{0} },
	//{ MODKEY,								XK_Tab,		view,					{0} },
//	{ MODKEY|ShiftMask,					XK_c,			killclient,			{0} },
//	Change between layouts
	{ MODKEY,								XK_F1,		setlayout,			{.v = &layouts[0]} }, // tile
	{ MODKEY,								XK_F2,		setlayout,			{.v = &layouts[1]} }, // floating
	{ MODKEY,								XK_F3,		setlayout,			{.v = &layouts[2]} }, // spiral
	{ MODKEY,								XK_F4,		setlayout,			{.v = &layouts[3]} }, // dwindle
	{ MODKEY,								XK_F6,		setlayout,			{.v = &layouts[4]} }, // col
	{ MODKEY,								XK_F7,		setlayout,			{.v = &layouts[5]} }, // horizgrid
	{ MODKEY,								XK_F8,		setlayout,			{.v = &layouts[6]} }, // monocle
	{ MODKEY,								XK_comma,	cyclelayout,		{.i = -1 } },
	{ MODKEY,								XK_period,	cyclelayout,		{.i = +1 } },
	{ MODKEY,								XK_space,	setlayout,			{0} },
// Toggle floating/sticky/fullscr
	{ MODKEY,								XK_u,			togglefloating,	{0} },
	{ MODKEY|ShiftMask,					XK_u,			togglesticky,		{0} },
	{ MODKEY,								XK_F11,		togglefullscr,		{0} },
// ?
	//{ MODKEY,								XK_0,			view,					{.ui = ~0 } },
	//{ MODKEY|ShiftMask,				XK_0,			tag,					{.ui = ~0 } },
// Move between monitors
	//{ MODKEY,								XK_comma,	focusmon,			{.i = -1 } },
	//{ MODKEY,								XK_period,	focusmon,			{.i = +1 } },
	//{ MODKEY|ShiftMask,				XK_comma,	tagmon,				{.i = -1 } },
	//{ MODKEY|ShiftMask,				XK_period,	tagmon,				{.i = +1 } },
//	Focus/Move Tags
	{ MODKEY,								XK_z,			viewtoleft,			{0} },
	{ MODKEY,								XK_x,			viewtoright,		{0} },
	{ MODKEY|ShiftMask,					XK_z,			tagtoleft,			{0} },
	{ MODKEY|ShiftMask,					XK_x,			tagtoright,			{0} },
//	Move floating window to spot 1-9 on screen
	{ MODKEY|ControlMask,				XK_q,			moveplace,			{.ui = WIN_NW }},
	{ MODKEY|ControlMask,				XK_w,			moveplace,			{.ui = WIN_N  }},
	{ MODKEY|ControlMask,				XK_e,			moveplace,			{.ui = WIN_NE }},
	{ MODKEY|ControlMask,				XK_a,			moveplace,			{.ui = WIN_W  }},
	{ MODKEY|ControlMask,				XK_s,			moveplace,			{.ui = WIN_C  }},
	{ MODKEY|ControlMask,				XK_d,			moveplace,			{.ui = WIN_E  }},
	{ MODKEY|ControlMask,				XK_z,			moveplace,			{.ui = WIN_SW }},
	{ MODKEY|ControlMask,				XK_x,			moveplace,			{.ui = WIN_S  }},
	{ MODKEY|ControlMask,				XK_c,			moveplace,			{.ui = WIN_SE }},
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
	{ MODKEY|ShiftMask,					XK_F5,		quit,					{0} },
// Restart dwm
	{ MODKEY,								XK_F5,      quit,					{1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	//{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
