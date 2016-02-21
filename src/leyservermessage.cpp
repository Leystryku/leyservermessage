#pragma once

#include "leyservermessage.h"
#include "Lua/Interface.h"
#include "igameevents.h"
#include "inetchannel.h"
#include <cbase.h>

IVEngineServer *server = 0;


GarrysMod::Lua::ILuaBase *Lua = 0;


int ServerMessage(lua_State *state)
{
	LUA->CheckType(1, GarrysMod::Lua::Type::NUMBER);
	LUA->CheckType(2, GarrysMod::Lua::Type::STRING);
	LUA->CheckType(3, GarrysMod::Lua::Type::STRING);

	char chitler[2048];

	bf_write hitler(chitler, sizeof(chitler));


	INetChannel *chan = (INetChannel*)server->GetPlayerNetInfo(LUA->GetNumber(1));
	if (!chan)
		return 1;


	char pck[500];
	bf_write setcv(pck, sizeof(pck));
	setcv.WriteUBitLong(5, 6);
	setcv.WriteByte(0x1);
	setcv.WriteString(LUA->GetString(2));
	setcv.WriteString(LUA->GetString(3));
	chan->SendData(setcv);

	LUA->PushBool(true);

	return 1;
}


GMOD_MODULE_OPEN()
{

	HMODULE  engine = GetModuleHandleA("engine.dll");
	CreateInterfaceFn engineinterface = (CreateInterfaceFn)GetProcAddress(engine, "CreateInterface");
	server = (IVEngineServer*)engineinterface("VEngineServer021", 0);

	if (!server)
	{
		Msg("NO ENGINESERVER!\n");
		return 0;
	}


	Lua = LUA;


	Msg("Loaded leyservermessage\n");

	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	LUA->PushString("ServerMessage");
	LUA->PushCFunction(ServerMessage);
	LUA->SetTable(-3);

	

	return 1;
}

GMOD_MODULE_CLOSE()
{
	Msg("Unloading leyservermessage!\n");

	return 1;
}
