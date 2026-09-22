#include "header/structs.h"


// Text storage is generated in build/resource_text.c by build_text.py.
#define TEXT_RESOURCE(name) extern const u8 name[]

TEXT_RESOURCE(textButtonPrompt1);
TEXT_RESOURCE(textButtonPrompt2);
TEXT_RESOURCE(textButtonPrompt3);
TEXT_RESOURCE(textButtonPrompt4);

TEXT_RESOURCE(textMon);
TEXT_RESOURCE(textBag);
TEXT_RESOURCE(textOther);
TEXT_RESOURCE(textLevel);
TEXT_RESOURCE(textNatures);
TEXT_RESOURCE(textAbility);
TEXT_RESOURCE(textHappiness);
TEXT_RESOURCE(textShiny);
TEXT_RESOURCE(textGender);
TEXT_RESOURCE(textSure);
TEXT_RESOURCE(textCancel);
TEXT_RESOURCE(textUnknownAbility);
TEXT_RESOURCE(textNotShiny);
TEXT_RESOURCE(textGenderTable);
TEXT_RESOURCE(textHP);
TEXT_RESOURCE(textAttack);
TEXT_RESOURCE(textDefense);
TEXT_RESOURCE(textSpeed);
TEXT_RESOURCE(textSPAttack);
TEXT_RESOURCE(textSPDefense);
TEXT_RESOURCE(textIV);
TEXT_RESOURCE(textEV);
TEXT_RESOURCE(textMovePower);
TEXT_RESOURCE(textMoveType);
TEXT_RESOURCE(textMoveAccuracy);
TEXT_RESOURCE(textPP);
TEXT_RESOURCE(textNone);
TEXT_RESOURCE(textQuantity);
TEXT_RESOURCE(textAddItem);
TEXT_RESOURCE(textThrowKeyItem);
TEXT_RESOURCE(textCircleDot);
TEXT_RESOURCE(textAddSuccess);
TEXT_RESOURCE(textInsufficientSpace);
TEXT_RESOURCE(textEgg);
TEXT_RESOURCE(textHatchNow);
TEXT_RESOURCE(textPokedexUpgrade);
TEXT_RESOURCE(textPokerus);
TEXT_RESOURCE(textMirageShow);
TEXT_RESOURCE(textThroughWall);
TEXT_RESOURCE(textVisualRangeMax);
TEXT_RESOURCE(textSpray);
TEXT_RESOURCE(textlimit510);
TEXT_RESOURCE(textPageLock);
TEXT_RESOURCE(textDelete);
TEXT_RESOURCE(textInitials);
TEXT_RESOURCE(textBallType);
TEXT_RESOURCE(textCatchLocation);
TEXT_RESOURCE(textTeleport);
TEXT_RESOURCE(textComingSoon);
TEXT_RESOURCE(textSomewhere);
TEXT_RESOURCE(textFatefulEncounter);
TEXT_RESOURCE(textFlightPoint);
TEXT_RESOURCE(textTime);
TEXT_RESOURCE(textHour);
TEXT_RESOURCE(textMonCopy);
TEXT_RESOURCE(textCopySuccess);
TEXT_RESOURCE(textSendToPC);
TEXT_RESOURCE(textCopyFailed);
TEXT_RESOURCE(textMonObedience);
TEXT_RESOURCE(textVersion);
TEXT_RESOURCE(exit_text);

#undef TEXT_RESOURCE

const u8 textCursor[] = {0xEF, 0xFF};

// The author block remains fixed encrypted metadata.
#ifdef RUBY_SAPPHIRE
const u8 textAuthor[] = {0x57, 0xAA, 0xA5, 0x86, 0xA4, 0xDF, 0xA0, 0x90, 0x54};
#else
const u8 textAuthor[] = {0x57, 0xAA, 0xA4, 0x52, 0xBE, 0xA4, 0xDF, 0xA0, 0x90, 0x54};
#endif

const u8 sTrainerCardTextColors[] = {0, 2, 3};

const struct rbox_short rbox_table[] = {
        {0x00,0x01,0x01,0x1C,0xF,0x0F,0x57},
        {0xFF,0,0,0,0,0,0},
        {0,1,0x11,28,2,0xF,0}
};

const struct ListQuantityLimit gQuantityLimit = {
	.pokemonCount = 0,
	.moveCount = 0,
	.itemCount = 0,
	.abilityHook = FALSE
};

const struct NameLengthConfig gNameLengthConfig = {
	.pokemonNameLength = 11,
	.moveNameLength = 13,
	.itemNameLength = 14,
    .abilityNameLength = 13
};


const u8 mousePosInfoPage[] = {
	0x8C,0x14,//0
	0x6C,0x34,//1
	0xC6,0x34,//2
	0x6C,0x4C,//3
	0xC6,0x4C,//4
	0x6C,0x64,//5
	0xC6,0x64,//6
	0xE2,0x7C,//7
	0xC6,0x7C//8
};
const u8 mousePosMainPage[] = {
	0x2E,0x4C,
	0x7A,0x4C,
	0xC6,0x4C
};
const u8 mousePosAttack[] = {
	0x8C,0x14,//0
	0x66,0x28,//1
	0x66,0x3A,//2
	0x66,0x4C,//3
	0x66,0x5E,//4
	0xE2,0x7C,//5
	0xE2,0x7C,//6
	0xE2,0x7C,//7
	0xC6,0x7C//8
};
const u8 mousePosSpecie[] = {
	0x8C,0x14,//0
	0x86,0x5E,//1
	0x86,0x5E,//2
	0x86,0x5E,//3
	0x86,0x5E,//4
	0x86,0x5E,//5
	0x86,0x5E,//6
	0xE2,0x7C,//7
	0xC6,0x7C//8
};
const u8 mousePosItem[] = {
	0x00,0x00,//0
	0x5A,0x2C,//1
	0xBE,0x2C,//2
	0xBE,0x44,//3
	0xBE,0x5C,//4
	0xE2,0x7C,//5
	0xE2,0x7C,//6
	0xE2,0x7C,//7
	0xC6,0x7C//8
};
const u8 mousePosOther[] = {
	0x00,0x00,//0
	0x66,0x28,//1
	0xC6,0x28,//2
	0x66,0x44,//3
	0xC6,0x44,//4
	0x66,0x60,//5
	0xC6,0x60,//6
	0xE2,0x7C,//7
	0xC6,0x7C//8
};

const u8 *mouse_pos_table[] = {
	[MOUSE_POS_INFO] = mousePosInfoPage,
	[MOUSE_POS_MAIN] = mousePosMainPage,
	[MOUSE_POS_ATTACK] = mousePosAttack,
	[MOUSE_POS_SPECIE] = mousePosSpecie,
	[MOUSE_POS_ITEM] = mousePosItem,
	[MOUSE_POS_OTHER] = mousePosOther
};

const u8 *text_table[] = {
	[TEXT_BUTTON_PROMPT1] = textButtonPrompt1,
	[TEXT_BUTTON_PROMPT2] = textButtonPrompt2,
	[TEXT_BUTTON_PROMPT3] = textButtonPrompt3,
	[TEXT_BUTTON_PROMPT4] = textButtonPrompt4,
	[TEXT_MON] = textMon,
	[TEXT_BAG] = textBag,
	[TEXT_OTHER] = textOther,
	[TEXT_LEVEL] = textLevel,
	[TEXT_NATURES] = textNatures,
	[TEXT_ABILITY] = textAbility,
	[TEXT_HAPPINESS] = textHappiness,
	[TEXT_SHINY] = textShiny,
	[TEXT_GENDER] = textGender,
	[TEXT_SURE] = textSure,
	[TEXT_CANCEL] = textCancel,
	[TEXT_UNKNOWN_ABILITY] = textUnknownAbility,
	[TEXT_NATURES_TABLE] = 0,
	[TEXT_NOTSHINY] = textNotShiny,
	[TEXT_GENDER_TABLE] = textGenderTable,
	[TEXT_HP] = textHP,
	[TEXT_ATTACK] = textAttack,
	[TEXT_DEFENSE] = textDefense,
	[TEXT_SPEED] = textSpeed,
	[TEXT_SP_ATTACK] = textSPAttack,
	[TEXT_SP_DEFENSE] = textSPDefense,
	[TEXT_IV] = textIV,
	[TEXT_EV] = textEV,
	[TEXT_MOVE_POWER] = textMovePower,
	[TEXT_MOVE_TYPE] = textMoveType,
	[TEXT_MOVE_ACCURACY] = textMoveAccuracy,
	[TEXT_PP] = textPP,
	[TEXT_NONE] = textNone,
	[TEXT_QUANTITY] = textQuantity,
	[TEXT_ADD_ITEM] = textAddItem,
	[TEXT_THROW_KEYITEM] = textThrowKeyItem,
	[TEXT_CIRCLE_DOT] = textCircleDot,
	[TEXT_ADD_SUCCESS] = textAddSuccess,
	[TEXT_INSUFFICIENT_SPACE] = textInsufficientSpace,
	[TEXT_AUTHOR] = textAuthor,
	[TEXT_VERSION] = textVersion,
	[TEXT_EGG] = textEgg,
	[TEXT_HATCH_NOW] = textHatchNow,
	[TEXT_POKEDEX_UPGRADE] = textPokedexUpgrade,
	[TEXT_POKERUS] = textPokerus,
	[TEXT_MIRAGE_SHOW] = textMirageShow,
	[TEXT_THROUGH_WALL] = textThroughWall,
	[TEXT_VISUAL_RANGE_MAX] = textVisualRangeMax,
	[TEXT_SPRAY] = textSpray,
	[TEXT_LIMIT510] = textlimit510,
	[TEXT_PAGELOCK] = textPageLock,
	[TEXT_INITIALS] = textInitials,
	[TEXT_DELETE] = textDelete,
	[TEXT_BALL_TYPE] = textBallType,
	[TEXT_CATCH_LOCATION] = textCatchLocation,
	[TEXT_TELEPORT] = textTeleport,
	[TEXT_COMING_SOON] = textComingSoon,
	[TEXT_SOMEWHERE] = textSomewhere,
	[TEXT_FATEFUL_ENCOUNTER] = textFatefulEncounter,
	[TEXT_FLIGHT_POINT] = textFlightPoint,
	[TEXT_TIME] = textTime,
	[TEXT_HOUR] = textHour,
	[TEXT_MON_COPY] = textMonCopy,
	[TEXT_COPY_SUCCESS] = textCopySuccess,
	[TEXT_SEND_TO_PC] = textSendToPC,
	[TEXT_COPY_FAILED] = textCopyFailed,
	[TEXT_MON_OBEDIENCE] = textMonObedience,
	[TEXT_CURSOR] = textCursor
};



#ifndef EMERALD
const u8 mouse_tile[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
	0x00, 0x00, 0x00, 0x61, 0x00, 0x00, 0x00, 0x61, 0x00, 0x00, 0x10, 0xB6, 0x00, 0x00, 0x10, 0xB6,
	0x11, 0x00, 0x00, 0x00, 0x61, 0x01, 0x00, 0x00, 0xB6, 0x16, 0x00, 0x00, 0xB6, 0x6B, 0x01, 0x00,
	0x81, 0xBB, 0x16, 0x00, 0x18, 0xB8, 0x6B, 0x01, 0x8B, 0x81, 0xBB, 0x16, 0xBB, 0x18, 0x66, 0x11,
	0x00, 0x00, 0x61, 0xBB, 0x00, 0x00, 0x61, 0xBB, 0x00, 0x10, 0xB6, 0x66, 0x00, 0x10, 0x66, 0x11,
	0x00, 0x10, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xBB, 0x66, 0x11, 0x00, 0x66, 0x11, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const u8 mouse_pal[] = {
	0x00, 0x00, 0xFF, 0x7F, 0x39, 0x67, 0x94, 0x52, 0xEF, 0x3D, 0x8C, 0x39, 0xC7, 0x1C, 0xDC, 0x7F,
	0xAC, 0x20, 0x3F, 0x67, 0xDF, 0x39, 0x9F, 0x10, 0x8C, 0x6E, 0x2A, 0x62, 0xC9, 0x55, 0x89, 0x35
};
#endif
