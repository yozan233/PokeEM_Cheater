#include "types.h"
/*macroinstructions*/

/*structs*/
struct graphic
{
	u8 *img;
	u16 size;
	u16 tag;
};

struct pal_graphic
{
	u8 *pal_ptr;
	u16 tag;
	u16 filler;
};

struct rotscale
{
	s16 xscal;
	s16 yscal;
	s8 rotation;
	u8 duration;
	u16 filler;
};

struct image_frame
{
	u16 cmd;
	u16 parameter;
};

struct oam
{
	u16 attr0;
    u16 attr1;
    u16 attr2;
    s16 fill;
};

struct objtemplate
{
	u16 tiles_tag;
	u16 pal_tag;
	struct oam *oam_ptr;
	struct image_frame **anime_table;
	struct graphic *gfx_table;
	struct rotscale **rotscale_table;
	void (*callback)(void*);
};

struct obj
{
	struct oam oamdata;
	struct image_frame **anime_table;
	struct graphic *gfx_table;
	struct rotscale **rotscale_table;
	struct objtemplate *obj_template;
	u8 *npc_type_detail;
	void (*callback)(void*);
	u16 x1;
	u16 y1;
	s16 x2;
	s16 y2;
	s8 x3;
	s8 y3;
	u8 anime_index;
	u8 frame_index;
	u8 delay;
	u8 frame_cnt;
	u16 privatevars[8];
	u8 bitfield2;
	u8 bitfield;
	u16 base_tile;
	u8 npc_type_detail_index;
	u8 y_height_related;
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
/*0x24*/	u32 field_24;
/*0x28*/	u16 buttons0_held;
/*0x2A*/	u16 buttons1_new;
/*0x2C*/	u16 buttons2_held_remapped;
/*0x2E*/	u16 buttons3_new_remapped;
/*0x30*/	u16 buttons4_new_and_keyrepeat;
/*0x32*/	u16 keypad_countdown;
	u32 unused_apparently;
	struct oam sprites[128];
	u8 multi_purpose_state_tracker;
	u8 gpu_sprites_upload_skip;
};

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

struct Time
{
    s16 days;
    s8 hours;
    s8 minutes;
    s8 seconds;
};

struct fly
{
	u8 bank;
	u8 map;
	u16 pos_x;
	u16 pos_y;
	u16 fill;

};

struct Datastruct
{
	u8 mode;			//0x00
	u8 select;			//0x01
	u8 over;			//0x02
	u8 boxid;			//0x03
	u32 numTextBuff;	//0x04
	u8 maxLvl;			//0x08
	u8 attackSelect;	//0x09
	u8 poke_pic_id;		//0x0A
	u8 modebuffer;		//0x0B
	u32 pos_buffer;		//0x0C
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
	u8 item_pic_id;		//0x2E
	u8 aa;				//0x2F
	u8 party_2;			//0x30
	u8 egg_2;			//0x31
	u16 species_2;		//0x32
	u8 lvl_2;			//0x34
	u8 nature_2;		//0x35
	
};

struct mouse
{
	u16 pos_x;
	u16 pos_y;
};

struct AllPokemons
{
	u16 max;
};

struct get_a_u8
{
	u8 bit;
};

struct font
{
	u8 zi1;
	u8 zi2;
	u8 fill;
};

struct mybuffer
{
	u16 buffer0;
	u16 buffer1;
	u16 buffer2;
	u16 buffer3;
	u16 buffer4;
	u16 buffer5;
	u16 buffer6;
	u16 buffer7;
};
struct poke_basestats{
    u8 base_hp;
    u8 base_atk;
    u8 base_def;
    u8 base_spd;
    u8 base_spatk;
    u8 base_spdef;
    u8 type1;
    u8 type2;
    u8 catch_rate;
    u8 exp_yield;
    u16 evs_hp : 2; //0x1, 0x2
    u16 evs_atk : 2; //0x4, 0x8
    u16 evs_def : 2; //0x10, 0x20
    u16 evs_spd : 2; //0x40, 0x80
    u16 evs_spatk : 2;//0x100, 0x200
    u16 evs_spdef : 2; //0x400, 0x800
    u16 unused : 4; //0x1000, 0x2000, 0x4000, 0x8000
    u16 item1;
    u16 item2;
    u8 gender_ratio;
    u8 hatching;
    u8 friendship;
    u8 exp_curve;
    u8 egg_group1;
    u8 egg_group2;
    u8 ability1;
    u8 ability2;
    u8 safari_flee_rate;
    u8 dex_colour;
    u16 padding;
};




struct pokemon
{
	u32 personality_value;
	u32 OTID;
	u8 nickname[10];
	u16 language;
	u8 OT_name[7];
	u8 markings;
	u16 checksum;
	u16 padding;
	u8 enc_data[48];
	u32 status;
	u8 level;
	u8 pokerus;
	u16 cur_hp;
	u16 tot_hp;
	u16 attack;
	u16 defense;
	u16 speed;
	u16 sattack;
	u16 sdefense;
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

struct trainerdata
{
	u8 name[8];
	u8 gender;
	u8 centercheck;
	u16 TID;
	u16 SID;
	u16 hours;
	u8 mins;
	u8 secs;
	u8 frames;
	u8 options_button_style;
	u8 options_text_speed;
	u8 unk[19];
	u8 pokemon_flags_3[52];
	u8 pokemon_flags_4[52];
	u8 field_90[1044];
	u8 fourCharacters[4];
	u8 field_4A8[1008];
	u8 mapdata[1672];
	u32 obfuscation_xor_key;
	u8 field_F24[127];
	u8 last_byte_in_sav2;
};

struct bg_cfg
{
	u16 bg_id:2;
	u16 charbase:2; //0x6000000 + x * 0x4000
	u16 screenbase:5; //0x6000000 + x * 0x800
	u16 size:2;
	u16 color_mode:1;
	u16 priority:2;
	u16 filler:2;
	u16 filler2;
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