#ifndef RELOC_H
#define RELOC_H

#include "z64.h"
#include "z64actor.h"

typedef struct {
    /* 0x00 */ void* loadedRamAddr;
    /* 0x04 */ u32 vromStart;
    /* 0x08 */ u32 vromEnd;
    /* 0x0C */ u32 vramStart;
    /* 0x10 */ u32 vramEnd;
    /* 0x14 */ UNK_TYPE1 pad14[0x4];
    /* 0x18 */ char* filename;
} PlayerOverlay; // size = 0x1C

struct ResolveInfo {
    void* ram;
    u32 virtStart;
    u32 virtEnd;
};

#define CreateInfo(Ram, Start, End) { .ram = (Ram), .virtStart = (u32)(Start), .virtEnd = (u32)(End), }

static void* Resolve(struct ResolveInfo info, u32 vram) {
    if (info.ram && info.virtStart <= vram && vram < info.virtEnd) {
        u32 offset = vram - info.virtStart;
        return (void*)((char*)info.ram + offset);
    } else {
        return NULL;
    }
}

void* Reloc_ResolveActorOverlay(ActorOverlay* ovl, u32 vram) {
    struct ResolveInfo info = CreateInfo(ovl->loadedRamAddr, ovl->vramStart, ovl->vramEnd);
    return Resolve(info, vram);
}

Actor* Reloc_ResolveActorInit(ActorOverlay* ovl) {
    struct ResolveInfo initInfo = CreateInfo(ovl->loadedRamAddr, ovl->vramStart, ovl->vramEnd);
    return Resolve(initInfo, (u32)((ActorProfile*)ovl->profile)->init);
}

void* Reloc_ResolveGameStateOverlay(GameStateOverlay* ovl, u32 vram) {
    struct ResolveInfo info = CreateInfo(ovl->loadedRamAddr, ovl->vramStart, ovl->vramEnd);
    return Resolve(info, vram);
}

void* Reloc_ResolvePlayerOverlay(PlayerOverlay* ovl, u32 vram) {
    struct ResolveInfo info = CreateInfo(ovl->loadedRamAddr, ovl->vramStart, ovl->vramEnd);
    return Resolve(info, vram);
}

// Macros for resolving functions present in PlayerOverlay memory regions.
#define Reloc_ResolvePlayerOverlayData(Type, Name, Ovl) ((Type*)Reloc_ResolvePlayerOverlay(&Ovl, Name##_VRAM))
#define Reloc_ResolvePlayerOverlayFunc(Type, Name, Ovl) ((Type)Reloc_ResolvePlayerOverlay(&Ovl, Name##_VRAM))
#define Reloc_ResolvePlayerActorFunc(Name) Reloc_ResolvePlayerOverlayFunc(Name##_Func, Name, s801D0B70.playerActor)
#define Reloc_ResolvePlayerActorData(Type, Name) Reloc_ResolvePlayerOverlayData(Type, Name, s801D0B70.playerActor)
#define Reloc_ResolveKaleidoScopeFunc(Name) Reloc_ResolvePlayerOverlayFunc(Name##_Func, Name, s801D0B70.kaleidoScope)
#define Reloc_ResolvePlayerUpperActionFunc(Name) Reloc_ResolvePlayerOverlayFunc(PlayerUpperActionFunc, Name, s801D0B70.playerActor)
#define Reloc_ResolvePlayerActionFunc(Name) Reloc_ResolvePlayerOverlayFunc(PlayerActionFunc, Name, s801D0B70.playerActor)

// Macros for resolving types present in GameStateOverlay memory regions.
#define Reloc_ResolveGameStateRelocType(Type, Vram, Gs) ((Type*)Reloc_ResolveGameStateOverlay(&(Gs), (Vram)))
#define Reloc_ResolveFileChooseData() Reloc_ResolveGameStateRelocType(FileChooseData, FileChooseDataVRAM, gGameStateInfo.fileSelect)

// Relocatable PlayerActor functions.
#define z2_LinkDamage               Reloc_ResolvePlayerActorFunc(z2_LinkDamage)
#define z2_LinkInvincibility        Reloc_ResolvePlayerActorFunc(z2_LinkInvincibility)
#define z2_PerformEnterWaterEffects Reloc_ResolvePlayerActorFunc(z2_PerformEnterWaterEffects)
#define z2_PlayerHandleBuoyancy     Reloc_ResolvePlayerActorFunc(z2_PlayerHandleBuoyancy)
#define z2_UseItem                  Reloc_ResolvePlayerActorFunc(z2_UseItem)
#define z2_PlayerWaitForGiantMask   Reloc_ResolvePlayerActorFunc(z2_PlayerWaitForGiantMask)
#define z2_Player_ItemToActionParam Reloc_ResolvePlayerActorFunc(z2_Player_ItemToActionParam)
#define z2_Player_func_8083692C     Reloc_ResolvePlayerActorFunc(z2_Player_func_8083692C)
#define z2_Player_func_80838A90     Reloc_ResolvePlayerActorFunc(z2_Player_func_80838A90)
#define z2_Player_func_8083B930     Reloc_ResolvePlayerActorFunc(z2_Player_func_8083B930)
#define z2_Player_PlayAnimationOnce Reloc_ResolvePlayerActorFunc(z2_Player_PlayAnimationOnce)
#define z2_Player_PlayAnimationLoop Reloc_ResolvePlayerActorFunc(z2_Player_PlayAnimationLoop)
#define z2_Player_InflictDamage     Reloc_ResolvePlayerActorFunc(z2_Player_InflictDamage)
#define z2_Player_StopCutscene      Reloc_ResolvePlayerActorFunc(z2_Player_StopCutscene)

// Relocatable PlayerActionFunc functions.
#define z2_Player_Action_0          Reloc_ResolvePlayerActionFunc(z2_Player_Action_0)
#define z2_Player_Action_1          Reloc_ResolvePlayerActionFunc(z2_Player_Action_1)
#define z2_Player_Action_2          Reloc_ResolvePlayerActionFunc(z2_Player_Action_2)
#define z2_Player_Action_3          Reloc_ResolvePlayerActionFunc(z2_Player_Action_3)
#define z2_Player_Action_4          Reloc_ResolvePlayerActionFunc(z2_Player_Action_4)
#define z2_Player_Action_5          Reloc_ResolvePlayerActionFunc(z2_Player_Action_5)
#define z2_Player_Action_6          Reloc_ResolvePlayerActionFunc(z2_Player_Action_6)
#define z2_Player_Action_7          Reloc_ResolvePlayerActionFunc(z2_Player_Action_7)
#define z2_Player_Action_8          Reloc_ResolvePlayerActionFunc(z2_Player_Action_8)
#define z2_Player_Action_9          Reloc_ResolvePlayerActionFunc(z2_Player_Action_9)
#define z2_Player_Action_10         Reloc_ResolvePlayerActionFunc(z2_Player_Action_10)
#define z2_Player_Action_11         Reloc_ResolvePlayerActionFunc(z2_Player_Action_11)
#define z2_Player_Action_12         Reloc_ResolvePlayerActionFunc(z2_Player_Action_12)
#define z2_Player_Action_13         Reloc_ResolvePlayerActionFunc(z2_Player_Action_13)
#define z2_Player_Action_14         Reloc_ResolvePlayerActionFunc(z2_Player_Action_14)
#define z2_Player_Action_15         Reloc_ResolvePlayerActionFunc(z2_Player_Action_15)
#define z2_Player_Action_16         Reloc_ResolvePlayerActionFunc(z2_Player_Action_16)
#define z2_Player_Action_17         Reloc_ResolvePlayerActionFunc(z2_Player_Action_17)
#define z2_Player_Action_18         Reloc_ResolvePlayerActionFunc(z2_Player_Action_18)
#define z2_Player_Action_19         Reloc_ResolvePlayerActionFunc(z2_Player_Action_19)
#define z2_Player_Action_20         Reloc_ResolvePlayerActionFunc(z2_Player_Action_20)
#define z2_Player_Action_21         Reloc_ResolvePlayerActionFunc(z2_Player_Action_21)
#define z2_Player_Action_22         Reloc_ResolvePlayerActionFunc(z2_Player_Action_22)
#define z2_Player_Action_23         Reloc_ResolvePlayerActionFunc(z2_Player_Action_23)
#define z2_Player_Action_24         Reloc_ResolvePlayerActionFunc(z2_Player_Action_24)
#define z2_Player_Action_25         Reloc_ResolvePlayerActionFunc(z2_Player_Action_25)
#define z2_Player_Action_26         Reloc_ResolvePlayerActionFunc(z2_Player_Action_26)
#define z2_Player_Action_27         Reloc_ResolvePlayerActionFunc(z2_Player_Action_27)
#define z2_Player_Action_28         Reloc_ResolvePlayerActionFunc(z2_Player_Action_28)
#define z2_Player_Action_29         Reloc_ResolvePlayerActionFunc(z2_Player_Action_29)
#define z2_Player_Action_30         Reloc_ResolvePlayerActionFunc(z2_Player_Action_30)
#define z2_Player_Action_31         Reloc_ResolvePlayerActionFunc(z2_Player_Action_31)
#define z2_Player_Action_32         Reloc_ResolvePlayerActionFunc(z2_Player_Action_32)
#define z2_Player_Action_33         Reloc_ResolvePlayerActionFunc(z2_Player_Action_33)
#define z2_Player_Action_34         Reloc_ResolvePlayerActionFunc(z2_Player_Action_34)
#define z2_Player_Action_35         Reloc_ResolvePlayerActionFunc(z2_Player_Action_35)
#define z2_Player_Action_36         Reloc_ResolvePlayerActionFunc(z2_Player_Action_36)
#define z2_Player_Action_37         Reloc_ResolvePlayerActionFunc(z2_Player_Action_37)
#define z2_Player_Action_38         Reloc_ResolvePlayerActionFunc(z2_Player_Action_38)
#define z2_Player_Action_39         Reloc_ResolvePlayerActionFunc(z2_Player_Action_39)
#define z2_Player_Action_40         Reloc_ResolvePlayerActionFunc(z2_Player_Action_40)
#define z2_Player_Action_41         Reloc_ResolvePlayerActionFunc(z2_Player_Action_41)
#define z2_Player_Action_42         Reloc_ResolvePlayerActionFunc(z2_Player_Action_42)
#define z2_Player_Action_43         Reloc_ResolvePlayerActionFunc(z2_Player_Action_43)
#define z2_Player_Action_44         Reloc_ResolvePlayerActionFunc(z2_Player_Action_44)
#define z2_Player_Action_45         Reloc_ResolvePlayerActionFunc(z2_Player_Action_45)
#define z2_Player_Action_46         Reloc_ResolvePlayerActionFunc(z2_Player_Action_46)
#define z2_Player_Action_47         Reloc_ResolvePlayerActionFunc(z2_Player_Action_47)
#define z2_Player_Action_48         Reloc_ResolvePlayerActionFunc(z2_Player_Action_48)
#define z2_Player_Action_49         Reloc_ResolvePlayerActionFunc(z2_Player_Action_49)
#define z2_Player_Action_50         Reloc_ResolvePlayerActionFunc(z2_Player_Action_50)
#define z2_Player_Action_51         Reloc_ResolvePlayerActionFunc(z2_Player_Action_51)
#define z2_Player_Action_52         Reloc_ResolvePlayerActionFunc(z2_Player_Action_52)
#define z2_Player_Action_53         Reloc_ResolvePlayerActionFunc(z2_Player_Action_53)
#define z2_Player_Action_54         Reloc_ResolvePlayerActionFunc(z2_Player_Action_54)
#define z2_Player_Action_55         Reloc_ResolvePlayerActionFunc(z2_Player_Action_55)
#define z2_Player_Action_56         Reloc_ResolvePlayerActionFunc(z2_Player_Action_56)
#define z2_Player_Action_57         Reloc_ResolvePlayerActionFunc(z2_Player_Action_57)
#define z2_Player_Action_58         Reloc_ResolvePlayerActionFunc(z2_Player_Action_58)
#define z2_Player_Action_59         Reloc_ResolvePlayerActionFunc(z2_Player_Action_59)
#define z2_Player_Action_60         Reloc_ResolvePlayerActionFunc(z2_Player_Action_60)
#define z2_Player_Action_61         Reloc_ResolvePlayerActionFunc(z2_Player_Action_61)
#define z2_Player_Action_62         Reloc_ResolvePlayerActionFunc(z2_Player_Action_62)
#define z2_Player_Action_63         Reloc_ResolvePlayerActionFunc(z2_Player_Action_63)
#define z2_Player_Action_64         Reloc_ResolvePlayerActionFunc(z2_Player_Action_64)
#define z2_Player_Action_65         Reloc_ResolvePlayerActionFunc(z2_Player_Action_65)
#define z2_Player_Action_66         Reloc_ResolvePlayerActionFunc(z2_Player_Action_66)
#define z2_Player_Action_67         Reloc_ResolvePlayerActionFunc(z2_Player_Action_67)
#define z2_Player_Action_68         Reloc_ResolvePlayerActionFunc(z2_Player_Action_68)
#define z2_Player_Action_69         Reloc_ResolvePlayerActionFunc(z2_Player_Action_69)
#define z2_Player_Action_70         Reloc_ResolvePlayerActionFunc(z2_Player_Action_70)
#define z2_Player_Action_71         Reloc_ResolvePlayerActionFunc(z2_Player_Action_71)
#define z2_Player_Action_72         Reloc_ResolvePlayerActionFunc(z2_Player_Action_72)
#define z2_Player_Action_73         Reloc_ResolvePlayerActionFunc(z2_Player_Action_73)
#define z2_Player_Action_74         Reloc_ResolvePlayerActionFunc(z2_Player_Action_74)
#define z2_Player_Action_75         Reloc_ResolvePlayerActionFunc(z2_Player_Action_75)
#define z2_Player_Action_76         Reloc_ResolvePlayerActionFunc(z2_Player_Action_76)
#define z2_Player_Action_77         Reloc_ResolvePlayerActionFunc(z2_Player_Action_77)
#define z2_Player_Action_78         Reloc_ResolvePlayerActionFunc(z2_Player_Action_78)
#define z2_Player_Action_79         Reloc_ResolvePlayerActionFunc(z2_Player_Action_79)
#define z2_Player_Action_80         Reloc_ResolvePlayerActionFunc(z2_Player_Action_80)
#define z2_Player_Action_81         Reloc_ResolvePlayerActionFunc(z2_Player_Action_81)
#define z2_Player_Action_82         Reloc_ResolvePlayerActionFunc(z2_Player_Action_82)
#define z2_Player_Action_83         Reloc_ResolvePlayerActionFunc(z2_Player_Action_83)
#define z2_Player_Action_84         Reloc_ResolvePlayerActionFunc(z2_Player_Action_84)
#define z2_Player_Action_85         Reloc_ResolvePlayerActionFunc(z2_Player_Action_85)
#define z2_Player_Action_86         Reloc_ResolvePlayerActionFunc(z2_Player_Action_86)
#define z2_Player_Action_87         Reloc_ResolvePlayerActionFunc(z2_Player_Action_87)
#define z2_Player_Action_88         Reloc_ResolvePlayerActionFunc(z2_Player_Action_88)
#define z2_Player_Action_89         Reloc_ResolvePlayerActionFunc(z2_Player_Action_89)
#define z2_Player_Action_90         Reloc_ResolvePlayerActionFunc(z2_Player_Action_90)
#define z2_Player_Action_91         Reloc_ResolvePlayerActionFunc(z2_Player_Action_91)
#define z2_Player_Action_92         Reloc_ResolvePlayerActionFunc(z2_Player_Action_92)
#define z2_Player_Action_93         Reloc_ResolvePlayerActionFunc(z2_Player_Action_93)
#define z2_Player_Action_94         Reloc_ResolvePlayerActionFunc(z2_Player_Action_94)
#define z2_Player_Action_95         Reloc_ResolvePlayerActionFunc(z2_Player_Action_95)
#define z2_Player_Action_96         Reloc_ResolvePlayerActionFunc(z2_Player_Action_96)

// Relocatable PlayerUpperActionFunc functions.
#define z2_Player_UpperAction_CarryAboveHead    Reloc_ResolvePlayerUpperActionFunc(z2_Player_UpperAction_CarryAboveHead)

// Relocatable PlayerActor data
#define z2_D_80862B4C               Reloc_ResolvePlayerActorData(s32, z2_D_80862B4C)

// Relocatable KaleidoScope functions.
#define z2_PauseDrawItemIcon        Reloc_ResolveKaleidoScopeFunc(z2_PauseDrawItemIcon)

void* Reloc_ResolveActorOverlay(ActorOverlay* ovl, u32 vram);
Actor* Reloc_ResolveActorInit(ActorOverlay* ovl);
void* Reloc_ResolveGameStateOverlay(GameStateOverlay* ovl, u32 vram);
void* Reloc_ResolvePlayerOverlay(PlayerOverlay* ovl, u32 vram);

#endif // RELOC_H
