# russifier
Russifer settings TextDraw window

# Dependencies
- [rustext](https://github.com/Open-GTO/rustext)

# Screenshot

![russifier](https://user-images.githubusercontent.com/1020099/42131621-c1bde476-7d0e-11e8-821c-595a6a7a5f32.png)

# Usage

```Pawn
#include <a_samp>
#include "russifier"

public OnPlayerCommandText(playerid, cmdtext[])
{
	if (!strcmp(cmdtext, "/russifier", true, 10)) {
		ShowPlayerRussifierSettings(playerid);
		return 1;
	}
	return 0;
}

public OnPlayerRussifierSelect(playerid, bool:changed, RussifierType:type)
{
	new string[144];
	format(string, sizeof(string), "changed = %d | type = %d", _:changed, _:type);
	SendClientMessage(playerid, -1, string);
	return 1;
}
```

# Functions

```Pawn
ShowPlayerRussifierSettings(playerid);
HidePlayerRussifierSettings(playerid);
Russifier_SetText(string[]);
```

# Callbacks

```Pawn
forward OnPlayerRussifierSelect(playerid, bool:changed, RussifierType:type);
```

# Directives

Directive | Default value | Can be redefined
----------|---------------|-----------------
RUSSIFIER_TEXT_BASE_X | 130.0 | yes
RUSSIFIER_TEXT_BASE_Y | 200.0 | yes
RUSSIFIER_TEXT_Y_STEP | 19.0 | yes
RUSSIFIER_TEXT_SIZE_X | 505.0 | yes
RUSSIFIER_TEXT_SIZE_Y | 15.0 | yes
RUSSIFIER_SELECT_COLOR | 0xAA3333FF | yes
RUSSIFIER_BACKGROUND_PADDING | 5.0 | yes
RUSSIFIER_TEXT_LETTER_SIZE_X | 0.4 | yes
RUSSIFIER_TEXT_LETTER_SIZE_Y | RUSSIFIER_TEXT_SIZE_Y / 10.0 | yes
RUSSIFIER_TEXT_LENGTH | 60 | yes
