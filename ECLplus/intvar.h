#pragma once
#include "pch.h"
#include "ECLplus.h"

enum {
    INTVAR_INPUT,
    INTVAR_SCORE,
    INTVAR_HISCORE,
    INTVAR_BOMBING,
    INTVAR_LIVES,
    INTVAR_BOMBS,
    INTVAR_GRAZE,
    INTVAR_PIV,
    INTVAR_CONTINUES,
    INTVAR_CREDITS,
    INTVAR_GI4,
    INTVAR_GI5,
    INTVAR_GI6,
    INTVAR_GI7,
    INTVAR_IFRAMES,
    INTVAR_PLAYER_STATE,
    INTVAR_HYPERTIMER,
    INTVAR_ISDIALOG
};
#define INTVAR_INPUT_LOC (DWORD*)0x004B3448
#define INTVAR_SCORE_LOC (DWORD*)0x004B59FC
#define INTVAR_HISCORE_LOC (DWORD*)0x004B59C0
#define INTVAR_BOMBING_VAL GetDwordField(Deref(0x004B7688), 0x30)
#define INTVAR_GRAZE_LOC (DWORD*)0x004B5A0C
#define INTVAR_PIV_LOC (DWORD*)0x004B5A24
#define INTVAR_CONTINUES_LOC (DWORD*)0x004B5A04
#define INTVAR_CREDITS_LOC (DWORD*)0x004B59D0
#define INTVAR_HYPERTIMER_LOC (DWORD*)0x004B5AA8
#define INTVAR_ISDIALOG_LOC (DWORD*)((*(DWORD*)0x004B76AC) + 0x1C0)

DWORD IntVarGetVal(ENEMY* enm, DWORD var);

DWORD* IntVarGetAddr(ENEMY* enm, DWORD var);
