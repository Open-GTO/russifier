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
