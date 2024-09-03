#include "types.h"

//// 红宝石 axve0:              ; @$(MAKE) GAME_VERSION=AXVE0 EMERALD=0 RUBY=1 RUBY_SAPPHIRE=1
//#define RUBY 1
//#define RUBY_SAPPHIRE 1



/* define */
#define BUTTONS_A 1
#define BUTTONS_B 2
#define BUTTONS_SELECT 4
#define BUTTONS_START 8
#define BUTTONS_RIGHT 0x10
#define BUTTONS_LEFT 0x20
#define BUTTONS_UP 0x40
#define BUTTONS_DOWN 0x80
#define BUTTONS_R 0x100
#define BUTTONS_L 0x200

#define TRUE 1
#define FALSE 0

#define NULL 0

#define PAGE_MAIN 0 //主页
#define PAGE_POKE_INFO 0x10 //精灵信息
#define PAGE_POKE_INFO2 0x11 //精灵信息2
#define PAGE_IVS 0x12 //个体值
#define PAGE_EVS 0x13 //努力值
#define PAGE_MOVES 0x14 //招式
#define PAGE_SPECIE 0x15 //物种
#define PAGE_POKE_NAME 0x16 //精灵名字
#define PAGE_ITEMS 0x20 //物品
#define PAGE_OTHER 0x30 //其他
#define PAGE_PLAYER_NAME 0x31 //玩家名字

#define PAGETYPE_MAIN 0 //主页面
#define PAGETYPE_POKEMON 1 //子页面-精灵
#define PAGETYPE_BAG 2 //子页面-背包
#define PAGETYPE_OTHER 3 //子页面-其他

#define SELECT_PARTY 0 //选中精灵名字
#define SELECT_CANCEL 7 //选中取消键
#define SELECT_SURE 8 //选中确定键

#define FONT_UPPERCASE 0    //大写字母
#define FONT_LOWERCASE 1    //小写字母
#define FONT_CHINESE 2      //中文

#define GENDER_FEMALE 0 //雌性
#define GENDER_MALE 1 //雄性
#define GENDER_ALL_FEMALE 2 //全雌性
#define GENDER_ALL_MALE 3 //全雄性
#define GENDER_NONE 4 //无性别

#define	TEXT_BUTTON_PROMPT1	0
#define	TEXT_BUTTON_PROMPT2	1
#define	TEXT_BUTTON_PROMPT3	2
#define	TEXT_BUTTON_PROMPT4	3
#define	TEXT_MON	4
#define	TEXT_BAG	5
#define	TEXT_OTHER	6
#define	TEXT_LEVEL	7
#define	TEXT_NATURES	8
#define	TEXT_ABILITY	9
#define	TEXT_HAPPINESS	10
#define	TEXT_SHINY	11
#define	TEXT_GENDER	12
#define	TEXT_SURE	13
#define	TEXT_CANCEL	14
#define	TEXT_UNKNOWN_ABILITY 	15
#define	TEXT_NATURES_TABLE	16
#define	TEXT_NOTSHINY	17
#define	TEXT_GENDER_TABLE	18
#define	TEXT_HP	19
#define	TEXT_ATTACK	20
#define	TEXT_DEFENSE	21
#define	TEXT_SPEED	22
#define	TEXT_SP_ATTACK	23
#define	TEXT_SP_DEFENSE	24
#define	TEXT_IV             25
#define	TEXT_EV         	26
#define	TEXT_MOVE_POWER	27
#define	TEXT_MOVE_TYPE	28
#define	TEXT_MOVE_ACCURACY	29
#define	TEXT_PP         	30
#define	TEXT_NONE	31
#define	TEXT_QUANTITY	32
#define	TEXT_ADD_ITEM	33
#define	TEXT_THROW_KEYITEM	34
#define	TEXT_CIRCLE_DOT	35
#define	TEXT_ADD_SUCCESS	36
#define	TEXT_INSUFFICIENT_SPACE	37
#define	TEXT_AUTHOR	38
#define	TEXT_VERSION	39
#define	TEXT_EGG	40
#define	TEXT_HATCH_NOW      	41
#define	TEXT_POKEDEX_UPGRADE	42
#define	TEXT_POKERUS	43
#define	TEXT_MIRAGE_SHOW	44
#define	TEXT_THROUGH_WALL	45
#define	TEXT_VISUAL_RANGE_MAX	46
#define	TEXT_SPRAY	47
#define	TEXT_LIMIT510	48
#define	TEXT_PAGELOCK	49
#define	TEXT_INITIALS	50
#define	TEXT_DELETE	51
#define	TEXT_BALL_TYPE	52
#define	TEXT_CATCH_LOCATION	53
#define	TEXT_TELEPORT	54
#define	TEXT_COMING_SOON	55 //敬请期待
#define	TEXT_SOMEWHERE	56
#define	TEXT_FATEFUL_ENCOUNTER	57
#define	TEXT_FLIGHT_POINT	58
#define	TEXT_TIME	59
#define	TEXT_HOUR	60
#define	TEXT_MON_COPY	61
#define	TEXT_COPY_SUCCESS	62
#define	TEXT_SEND_TO_PC	63
#define	TEXT_COPY_FAILED	64
#define	TEXT_MON_OBEDIENCE	65
#define	TEXT_CURSOR	66

#define MOUSE_POS_INFO 0
#define MOUSE_POS_MAIN 1
#define MOUSE_POS_ATTACK 2
#define MOUSE_POS_SPECIE 3
#define MOUSE_POS_ITEM 4
#define MOUSE_POS_OTHER 5

#ifdef FIRE_RED_LEAF_GREEN
#define BALLS_POCKET       2
#define KEYITEMS_POCKET    1
#elif RUBY_SAPPHIRE
#define BALLS_POCKET       1
#define KEYITEMS_POCKET    4
#else
#define BALLS_POCKET       1
#define KEYITEMS_POCKET    4
#endif

#define ITEM_TEXT_CURSOR_INDEX 7

#define SOUND_DELETE 3 
#define SOUND_SELECT 5
#define SOUND_PAGE 6

#define ITEM_NAME_NONE 0
#define ITEM_NAME_TEMP 1

#define ARRAY_COUNT(array) (size_t)(sizeof(array) / sizeof((array)[0]))

/* structs */
struct SpriteFrameImage
{
    const void *data;
    u16 size;
};

struct pal_graphic
{
	u8 *pal_ptr;
	u16 tag;
	u16 filler;
};

union AffineAnimCmd
{
    s16 type;
    u32* frame;
    u32* loop;
    u32* jump;
    u32* end;
};

union AnimCmd
{
	u16 type;
	u32* frame;
    u32* loop;
    u32* jump;
};

struct OamData
{
    /*0x00*/ u32 y:8;
    /*0x01*/ u32 affineMode:2;  // 0x1, 0x2 -> 0x4
             u32 objMode:2;     // 0x4, 0x8 -> 0xC
             u32 mosaic:1;      // 0x10
             u32 bpp:1;         // 0x20
             u32 shape:2;       // 0x40, 0x80 -> 0xC0

    /*0x02*/ u32 x:9;
             u32 matrixNum:5; // bits 3/4 are h-flip/v-flip if not in affine mode
             u32 size:2;

    /*0x04*/ u16 tileNum:10;    // 0x3FF
             u16 priority:2;    // 0x400, 0x800 -> 0xC00
             u16 paletteNum:4;
    /*0x06*/ u16 affineParam;
};

struct SpriteTemplate
{
    /*0x00*/ u16 tileTag;
    /*0x02*/ u16 paletteTag;
    /*0x04*/ struct OamData *oam;
    /*0x08*/ union AnimCmd **anims;
    /*0x0C*/ struct SpriteFrameImage *images;
    /*0x10*/ union AffineAnimCmd **affineAnims;
    /*0x14*/ void (*callback)(void*);
};

struct MonIconSpriteTemplate
{
    const struct OamData *oam;
    const u8 *image;
    const union AnimCmd *const *anims;
    const union AffineAnimCmd *const *affineAnims;
    void (*callback)(struct Sprite *);
    u16 paletteTag;
};

struct Coords16
{
    s16 x;
    s16 y;
};

struct Sprite
{
    /*0x00*/ struct OamData oam;
    /*0x08*/ union AnimCmd **anims;
    /*0x0C*/ struct SpriteFrameImage *images;
    /*0x10*/ union AffineAnimCmd **affineAnims;
    /*0x14*/ struct SpriteTemplate *template;
    /*0x18*/ struct SubspriteTable *subspriteTables;
    /*0x1C*/ void (*callback)(void*);

    /*0x20*/ s16 posX1;
    /*0x22*/ s16 posY1;
    /*0x24*/ s16 posX2;
    /*0x26*/ s16 posY2;
    /*0x28*/ s8 centerToCornerVecX;
    /*0x29*/ s8 centerToCornerVecY;

    /*0x2A*/ u8 animNum;
    /*0x2B*/ u8 animCmdIndex;
    /*0x2C*/ u8 animDelayCounter:6;
             bool8 animPaused:1;
             bool8 affineAnimPaused:1;
    /*0x2D*/ u8 animLoopCounter;

    // general purpose data fields
    /*0x2E*/ s16 data[8];

    /*0x3E*/ bool16 inUse:1;               //1
             bool16 coordOffsetEnabled:1;  //2
             bool16 invisible:1;           //4
             bool16 flags_3:1;             //8
             bool16 flags_4:1;             //0x10
             bool16 flags_5:1;             //0x20
             bool16 flags_6:1;             //0x40
             bool16 flags_7:1;             //0x80
    /*0x3F*/ bool16 hFlip:1;               //1
             bool16 vFlip:1;               //2
             bool16 animBeginning:1;       //4
             bool16 affineAnimBeginning:1; //8
             bool16 animEnded:1;           //0x10
             bool16 affineAnimEnded:1;     //0x20
             bool16 usingSheet:1;          //0x40
             bool16 flags_f:1;             //0x80

    /*0x40*/ u16 sheetTileStart;

    /*0x42*/ u8 subspriteTableNum:6;
             u8 subspriteMode:2;

    /*0x43*/ u8 subpriority;
};

struct UCoords16
{
    u16 x;
    u16 y;
};

struct rbox_short
{
	u8 bg_id;
	u8 x;
	u8 y;
	u8 w;
	u8 h;
	u8 pal;
	u16 vram_tileset_offset;
};

struct rbox
{
	struct rbox_short rs;
	void * pixels;
};

struct WindowTemplate
{
    u8 bg;
    u8 tilemapLeft;
    u8 tilemapTop;
    u8 width;
    u8 height;
    u8 paletteNum;
    u16 baseBlock;
};

struct superstate
{
/*0x00*/	void(*callback1)(void);
/*0x04*/	void(*callback2)(void);
/*0x08*/	void(*callback2backup)(void);
/*0x0C*/	void(*callback5_vblank)(void);
/*0x10*/	void(*hblank_callback)(void);
/*0x14*/	u32 field_14;
/*0x18*/	u32 field_18;
/*0x1C*/	u32 bits_to_wait_for;
/*0x20*/	u32 ptr_vblank_counter;
/*0x24*/	u32 ptr_vblank_counter2;
/*0x28*/	u16 buttons0_held;
/*0x2A*/	u16 buttons1_new;
/*0x2C*/	u16 buttons2_held_remapped;
/*0x2E*/	u16 buttons3_new_remapped;
/*0x30*/	u16 buttons4_new_and_keyrepeat;
/*0x32*/	u16 keypad_countdown;
	u32 unused_apparently;
	struct OamData sprites[128];
	u8 multi_purpose_state_tracker;
	u8 gpu_sprites_upload_skip;
};

struct Time
{
    s16 days;
    s8 hours;
    s8 minutes;
    s8 seconds;
};

struct HealLocation
{
    s8 group;
    s8 map;
    u16 x;
    u16 y;
};

struct MySaveblock
{
	u32 malloc; 	//0x00
	u8 task_id;     //0x04
    u8 boxId;       //0x05
	u8 cursorPicId; //0x06
	u8 monIconId;	//0x07
    u8 monPicId;    //0x08
    u8 itemPicId;   //0x09
};

struct TextBuffer{
    u8 monName[0x20];
    u8 newName[0x20];
    u8 temp[0x20];
    u8 wordList[0x100];
    u8 format[0x20];
};

struct MyDatastruct
{
	u8 page;			//0x00
	u8 select;			//0x01
	u8 cursorState;		//0x02
	bool8 pageLock;		//0x03
	u32 numTextBuff;	//0x04
	u8 maxLvl;			//0x08
	u8 attackSelect;	//0x09
	u8 mouseMode;		//0x0A
	u8 soundMute;		//0x0B
	s16 posBuffer[2];	//0x0C
	u8 party;			//0x10
	u8 egg;				//0x11
	u16 species;		//0x12
	u8 lvl;				//0x14
	u8 nature;			//0x15
	u8 ability;			//0x16
	u8 happiness;		//0x17
	u8 shiny;			//0x18
	u8 sex;				//0x19
	u8 hp;				//0x1A
	u8 attack;			//0x1B
	u8 defence;			//0x1C
	u8 speed;			//0x1D
	u8 SP_attack;		//0x1E
	u8 SP_defence;		//0x1F
	u32 PID;			//0x20
	u32 TID;			//0x24
	u16 Num;			//0x28
	u16 attackN;		//0x2A
	u16 attackBuffer;	//0x2C
	u8 fontType;		//0x2E
	u8 obedience;		//0x2F //精灵听话
	u8 party_2;			//0x30
	u8 egg_2;			//0x31
	u16 species_2;		//0x32
	u8 lvl_2;			//0x34
	u8 nature_2;		//0x35
	u8 ability_2;		//0x36
	u8 happiness_2;		//0x37
	u8 shiny_2;			//0x38
	u8 sex_2;			//0x39
    u8 location;        //0x3A
    u8 obedienceTemp;   //0x3B
    u8 time;           //0x3C
    bool8 limit510;     //0x3D
    u8 optionsButtonMode;//0x3E
    u8 selectedflightPoint;//0x3F
    u16 ballCount;     //0x40
    u8 selectedBall;    //0x42
    bool8 monCopy;      //0x43
    u16 itemBuffer;     //0x44
    bool8 addItemEnable:1; //0x46
    bool8 throwKeyItemEnable:1;
    bool8 pokedexUpgrade:1;
    bool8 pokerus:1;
    bool8 visualRangeMax:1;
    bool8 mirageShow:1;
    bool8 throughWall:1;
    bool8 field_46_7:1;
    bool8 field_47;
    u8 fontBit1;        //0x48
    u8 fontBit2;        //0x49
    u8 fontPage[2];     //0x4A
    u8 inputCursorIndex;//0x4C
	u8 field_B3[0xB3];
	struct TextBuffer textBuffer; //0x100
};

struct font
{
	u8 zi1;
	u8 zi2;
	u8 fill;
};

struct Pokemon
{
    u8 unknown[0x54];


};

struct task
{
	void (*fptr) (u8);
	u8 inuse;
	u8 prev;
	u8 next;
	u8 priority;
	u16 priv[16];
};

struct fade_ctrl
{
	u16 bg_pal_bitfield;
	u16 obj_pal_bitfield;
	u16 scale;
	u16 mix_color;
	u8 field_8;
	u8 field_9;
	u8 field_A;
	u8 field_B;
};



struct DMACNT
{
    u16 Count;              // Transfer Count
    u16 Dummy_21_16:5;
    u16 DestpCnt:2;         // Destination Address Control
    u16 SrcpCnt:2;          // Source Address Control
    u16 ContinuousON:1;     // Continuous Mode
    u16 BusSize:1;          // Bus Size 16/32Bit Select
    u16 DataRequest:1;      // Data Request Synchronize Mode
    u16 Timming:2;          // Timing Select
    u16 IF_Enable:1;        // Interrupt Request Enable
    u16 Enable:1;           // DMA Enable
};

struct DISPCNT{
    u16 BgMode:3;           // BG Mode Select
    u16 CgbMode:1;          // CGB Mode Select
    u16 Bmp_FrameNo:1;      // Bitmap Mode Display Frame Select
    u16 Obj_H_Off:1;        // OBJ Processing in H Blank OFF
    u16 ObjCharMapType:1;   // OBJ Character Data Mapping Type
    u16 Lcdc_Off:1;         // LCDC OFF
    u16 Bg0_On:1;           // BG 0 ON
    u16 Bg1_On:1;           // BG 1 ON
    u16 Bg2_On:1;           // BG 2 ON
    u16 Bg3_On:1;           // BG 3 ON
    u16 Obj_On:1;           // OBJ ON
    u16 Win0_On:1;          // Window 0 ON
    u16 Win1_On:1;          // Window 1 ON
    u16 ObjWin_On:1;        // OBJ Window ON
};

union DMACNT_CON
{
	u32 DMACNT_D;
	struct DMACNT DMACNT_S;
};

union DISPCNT_CON
{
	u16 DISPCNT_D;
	struct DISPCNT DISPCNT_S;
};

struct BaseStats
{
 /* 0x00 */ u8 unknown
};

struct MapHeader
{
    /* 0x00 */ struct MapLayout *mapLayout;
    /* 0x04 */ struct MapEvents *events;
    /* 0x08 */ u8 *mapScripts;
    /* 0x0C */ u32 *connections;
    /* 0x10 */ u16 music;
    /* 0x12 */ u16 mapLayoutId;
    /* 0x14 */ u8 regionMapSectionId;
    /* 0x15 */ u8 cave;
    /* 0x16 */ u8 weather;
    /* 0x17 */ u8 mapType;
    /* 0x18 */ u8 filler_18;
    /* 0x19 */ u8 escapeRope;
    /* 0x1A */ u8 flags;
    /* 0x1B */ u8 battleType;
};

struct MapLayout
{
    /*0x00*/ s32 width;
    /*0x04*/ s32 height;
    /*0x08*/ u16 *border;
    /*0x0c*/ u16 *map;
    /*0x10*/ u32 *primaryTileset;
    /*0x14*/ u32 *secondaryTileset;
};

struct MapEvents
{
    u8 eventObjectCount;
    u8 warpCount;
    u8 coordEventCount;
    u8 bgEventCount;

    u32 *eventObjects;
    u32 *warps;
    u32 *coordEvents;
    u32 *bgEvents;
};

struct WarpData
{
    s8 mapGroup;
    s8 mapNum;
    s8 warpId;
    s16 x, y;
};

struct SaveBlock1
{
    /*0x00*/ struct Coords16 pos;
    /*0x04*/ struct WarpData location;
    /*0x0C*/ struct WarpData continueGameWarp;
    /*0x14*/ struct WarpData dynamicWarp;
    /*0x1C*/ struct WarpData lastHealLocation; // used by white-out and teleport
    /*0x24*/ struct WarpData escapeWarp; // used by Dig and Escape Rope
    /*0x2C*/ u16 savedMusic;
    /*0x2E*/ u8 weather;
    /*0x2F*/ u8 weatherCycleStage;
    /*0x30*/ u8 flashLevel;
    /*0x32*/ u16 mapLayoutId;
};

struct SaveBlock2
{
    /*0x00*/ u8 playerName[8];
    /*0x08*/ u8 playerGender; // MALE, FEMALE
    /*0x09*/ u8 specialSaveWarp;
    /*0x0A*/ u8 playerTrainerId[4];
    /*0x0E*/ u16 playTimeHours;
    /*0x10*/ u8 playTimeMinutes;
    /*0x11*/ u8 playTimeSeconds;
    /*0x12*/ u8 playTimeVBlanks;
    /*0x13*/ u8 optionsButtonMode;         // OPTIONS_BUTTON_MODE_[NORMAL/LR/L_EQUALS_A]
    /*0x14*/ u16 optionsTextSpeed:3;       // OPTIONS_TEXT_SPEED_[SLOW/MID/FAST]
    u16 optionsWindowFrameType:5; // Specifies one of the 20 decorative borders for text boxes
    u16 optionsSound:1;           // OPTIONS_SOUND_[MONO/STEREO]
    u16 optionsBattleStyle:1;     // OPTIONS_BATTLE_STYLE_[SHIFT/SET]
    u16 optionsBattleSceneOff:1;  // whether battle animations are disabled
    u16 regionMapZoom:1;          // whether the map is zoomed in
    /*0x18*/ u8 *pokedex;
    /*0x90*/ u8 filler_90[0x8];
    /*0x98*/ u8 *localTimeOffset;
    /*0xA0*/ u8 *lastBerryTreeUpdate;
    /*0xA8*/ u32 *battleTower;
};

struct BagPocket
{
    struct ItemSlot *itemSlots;
    u8 capacity;
};

struct ItemSlot
{
    u16 itemId;
    u16 quantity;
};

struct ItemIcon
{
    struct LZData *tiles;
    struct LZData *pal;
};

struct LZData
{
    u32 flag:8;
    u32 size:24;
    u8 *data;
};

struct CompressedSpriteSheet
{
    struct LZData *data;  // LZ77 compressed pixel data
    u16 size;        // Uncompressed size of pixel data
    u16 tag;
};

struct CompressedSpritePalette
{
    struct LZData *data;  // LZ77 compressed palette data
    u16 tag;
};

struct Item
{
    u8 name[14];
    u16 itemId;
    u16 price;
    u8 holdEffect;
    u8 holdEffectParam;
    u8 *description;
    u8 importance;
    u8 unk19;
    u8 pocket;
    u8 type;
    u32 *fieldUseFunc;
    u8 battleUsage;
    u32 *battleUseFunc;
    u8 secondaryId;
};

struct TilesPal
{
    const u8 *tiles;
    const u16 *pal;
};

struct ListQuantityLimit
{
    u32 pokemonCount;
    u32 moveCount;
    u32 itemCount;
};

struct NameLengthConfig
{
    u8 pokemonNameLength;
    u8 moveNameLength;
    u8 itemNameLength;
    u8 abilityNameLength;
};

struct DataSizeConfig
{
    u8 monDataSize;
    u8 speciesDataSize;
    u8 moveDataSize;
    u8 moveDataDiff;
};





