#include <a_samp>
#include <rustext>

/*
	Defines
*/

#if !defined RUSSIFIER_TEXT_BASE_X
	#define RUSSIFIER_TEXT_BASE_X (130.0)
#endif

#if !defined RUSSIFIER_TEXT_BASE_Y
	#define RUSSIFIER_TEXT_BASE_Y (200.0)
#endif

#if !defined RUSSIFIER_TEXT_Y_STEP
	#define RUSSIFIER_TEXT_Y_STEP (19.0)
#endif

#if !defined RUSSIFIER_TEXT_SIZE_X
	#define RUSSIFIER_TEXT_SIZE_X (505.0)
#endif

#if !defined RUSSIFIER_TEXT_SIZE_Y
	#define RUSSIFIER_TEXT_SIZE_Y (15.0)
#endif

#if !defined RUSSIFIER_SELECT_COLOR
	#define RUSSIFIER_SELECT_COLOR (0xAA3333FF)
#endif

#if !defined RUSSIFIER_BACKGROUND_PADDING
	#define RUSSIFIER_BACKGROUND_PADDING (5.0)
#endif

#if !defined RUSSIFIER_TEXT_LETTER_SIZE_X 
	#define RUSSIFIER_TEXT_LETTER_SIZE_X (0.4)
#endif

#if !defined RUSSIFIER_TEXT_LETTER_SIZE_Y
	#define RUSSIFIER_TEXT_LETTER_SIZE_Y (RUSSIFIER_TEXT_SIZE_Y / 10.0)
#endif

#if !defined RUSSIFIER_TEXT_LENGTH
	#define RUSSIFIER_TEXT_LENGTH (60)
#endif

/*
	Forwards
*/

forward OnPlayerRussifierSelect(playerid, bool:changed, RussifierType:type);

/*
	Vars
*/

static
	Text:TD_Background = Text:INVALID_TEXT_DRAW,
	Text:TD_Text[RussifierType] = {INVALID_TEXT_DRAW, ...},
	bool:IsSettingsShowed[MAX_PLAYERS char],
	RussifierType:gPlayerRussifier[MAX_PLAYERS char],
	gSettingsText[RUSSIFIER_TEXT_LENGTH char] = !"Я могу прочитать этот текст, это мой русификатор";

const
	RussifierType:TEXT_RUSSIFIERS_COUNT = RussifierType:7; // only Russian localizations

/*
	Create & Destroy Text Draws
*/

#if !defined RUSSIFIER_DISABLE_HOOKS
	#if defined FILTERSCRIPT
		public OnFilterScriptInit()
		{
			Russifier_CreateTextDraws();

			#if defined Russifier_OnFilterScriptInit
				return Russifier_OnFilterScriptInit();
			#else
				return 1;
			#endif
		}
		#if defined _ALS_OnFilterScriptInit
			#undef OnFilterScriptInit
		#else
			#define _ALS_OnFilterScriptInit
		#endif

		#define OnFilterScriptInit Russifier_OnFilterScriptInit
		#if defined Russifier_OnFilterScriptInit
			forward Russifier_OnFilterScriptInit();
		#endif

		public OnFilterScriptExit()
		{
			Russifier_DestroyTextDraws();

			#if defined Russifier_OnFilterScriptExit
				return Russifier_OnFilterScriptExit();
			#else
				return 1;
			#endif
		}
		#if defined _ALS_OnFilterScriptExit
			#undef OnFilterScriptExit
		#else
			#define _ALS_OnFilterScriptExit
		#endif

		#define OnFilterScriptExit Russifier_OnFilterScriptExit
		#if defined Russifier_OnFilterScriptExit
			forward Russifier_OnFilterScriptExit();
		#endif
	#else
		public OnGameModeInit()
		{
			Russifier_CreateTextDraws();

			#if defined Russifier_OnGameModeInit
				return Russifier_OnGameModeInit();
			#else
				return 1;
			#endif
		}
		#if defined _ALS_OnGameModeInit
			#undef OnGameModeInit
		#else
			#define _ALS_OnGameModeInit
		#endif

		#define OnGameModeInit Russifier_OnGameModeInit
		#if defined Russifier_OnGameModeInit
			forward Russifier_OnGameModeInit();
		#endif

		public OnGameModeExit()
		{
			Russifier_DestroyTextDraws();

			#if defined Russifier_OnGameModeExit
				return Russifier_OnGameModeExit();
			#else
				return 1;
			#endif
		}
		#if defined _ALS_OnGameModeExit
			#undef OnGameModeExit
		#else
			#define _ALS_OnGameModeExit
		#endif

		#define OnGameModeExit Russifier_OnGameModeExit
		#if defined Russifier_OnGameModeExit
			forward Russifier_OnGameModeExit();
		#endif
	#endif
#endif

stock Russifier_CreateTextDraws()
{
	new
		Float:bg_pos_x = RUSSIFIER_TEXT_BASE_X - RUSSIFIER_BACKGROUND_PADDING,
		Float:bg_pos_y = RUSSIFIER_TEXT_BASE_Y - RUSSIFIER_BACKGROUND_PADDING,
		Float:bg_width = RUSSIFIER_TEXT_SIZE_X + RUSSIFIER_BACKGROUND_PADDING,
		Float:bg_height = RUSSIFIER_TEXT_Y_STEP * (_:TEXT_RUSSIFIERS_COUNT - 1);

	TD_Background = TextDrawCreate(bg_pos_x, bg_pos_y, "_");
	TextDrawLetterSize(TD_Background, 0.0, bg_height * 0.135);
	TextDrawTextSize(TD_Background, bg_width, 0.0);
	TextDrawUseBox(TD_Background, 1);
	TextDrawBoxColor(TD_Background, 124);

	for (new RussifierType:type; type < TEXT_RUSSIFIERS_COUNT; type++) {
		TD_Text[type] = TextDrawCreate(RUSSIFIER_TEXT_BASE_X,
		                               RUSSIFIER_TEXT_BASE_Y + RUSSIFIER_TEXT_Y_STEP * _:type,
		                               gSettingsText);
		TextDrawSetSelectable(TD_Text[type], 1);
		TextDrawTextSize(TD_Text[type], RUSSIFIER_TEXT_SIZE_X, RUSSIFIER_TEXT_SIZE_Y);
		TextDrawLetterSize(TD_Text[type], RUSSIFIER_TEXT_LETTER_SIZE_X, RUSSIFIER_TEXT_LETTER_SIZE_Y);
	}
}

stock Russifier_DestroyTextDraws()
{
	if (TD_Background != Text:INVALID_TEXT_DRAW) {
		TextDrawDestroy(TD_Background);
	}

	for (new RussifierType:type; type < TEXT_RUSSIFIERS_COUNT; type++) {
		if (TD_Text[type] != Text:INVALID_TEXT_DRAW) {
			TextDrawDestroy(TD_Text[type]);
		}
	}
}

/*
	OnPlayerClickTextDraw
*/

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (clickedid == Text:INVALID_TEXT_DRAW && IsSettingsShowed{playerid}) {
		HidePlayerRussifierSettings(playerid);
		CallLocalFunction("OnPlayerRussifierSelect", "iii", playerid, false, -1);
		return 1;
	}

	for (new RussifierType:type; type < TEXT_RUSSIFIERS_COUNT; type++) {
		if (TD_Text[type] == clickedid) {
			gPlayerRussifier{playerid} = type;
			HidePlayerRussifierSettings(playerid);
			CallLocalFunction("OnPlayerRussifierSelect", "iii", playerid, true, _:type);
			return 1;
		}
	}

	#if defined Russifier_OnPlayerClickTextDraw
		return Russifier_OnPlayerClickTextDraw(playerid, clickedid);
	#else
		return 0;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif

#define OnPlayerClickTextDraw Russifier_OnPlayerClickTextDraw
#if defined Russifier_OnPlayerClickTextDraw
	forward Russifier_OnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

/*
	Functions
*/

stock Russifier_SetText(string[])
{
	strpack(gSettingsText, string, sizeof(gSettingsText));
	Russifier_DestroyTextDraws();
	Russifier_CreateTextDraws();

	#if defined foreach
		foreach (new playerid : Player) {
	#else
		for (new playerid = GetPlayerPoolSize(); playerid != -1; playerid--) {
	#endif
			if (IsSettingsShowed{playerid}) {
				ShowPlayerRussifierSettings(playerid);
			}
		}
}

stock ShowPlayerRussifierSettings(playerid)
{
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}

	gPlayerRussifier{playerid} = GetPlayerRussifierType(playerid);

	for (new RussifierType:type; type < TEXT_RUSSIFIERS_COUNT; type++) {
		SetPlayerRussifierType(playerid, type);
		TextDrawShowForPlayer(playerid, TD_Text[type]);
		TextDrawShowForPlayer(playerid, TD_Background);
	}

	SelectTextDraw(playerid, RUSSIFIER_SELECT_COLOR);
	IsSettingsShowed{playerid} = true;
	return 1;
}

stock HidePlayerRussifierSettings(playerid)
{
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}

	SetPlayerRussifierType(playerid, gPlayerRussifier{playerid});

	for (new RussifierType:type; type < TEXT_RUSSIFIERS_COUNT; type++) {
		TextDrawHideForPlayer(playerid, TD_Text[type]);
		TextDrawHideForPlayer(playerid, TD_Background);
	}

	CancelSelectTextDraw(playerid);
	IsSettingsShowed{playerid} = false;
	return 1;
}
