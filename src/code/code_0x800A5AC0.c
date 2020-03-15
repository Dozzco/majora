#include <ultra64.h>
#include <global.h>

// This file is most likely z_en_a_obj.c

void EnAObj_Init(ActorEnAObj* this, GlobalContext* ctxt) {
    ActorEnAObj* s0 = (ActorEnAObj*)this;
    s0->base.textId = ((s0->base.params >> 8) & 0xFF) | 0x300;
    s0->base.params = (s0->base.params & 0xFF) - 9;
    Actor_ProcessInitChain((Actor*)s0, (ActorInitVar*)&enAObjInitVar);
    Actor_SetDrawParams(&s0->base.shape, 0, (actor_shadow_draw_func)func_800B3FC0, 12);
    Collision_InitCylinder(ctxt, &s0->collision, (Actor*)s0, &enAObjCylinderInit);
    Collision_CylinderMoveToActor((Actor*)s0, &s0->collision);
    s0->base.unkA0.mass = 255;
    s0->update = (actor_func)EnAObj_Update1;
}

void EnAObj_Destroy(ActorEnAObj* this, GlobalContext* ctxt) {
    ColCylinder* a2 = &this->collision;
    Collision_FiniCylinder(ctxt, a2);
}

void EnAObj_Update1(ActorEnAObj* this, GlobalContext* ctxt) {
    s16 v0;
    s32 v1;
    if (func_800B84D0((Actor*)this, ctxt) != 0) {
        this->update = (actor_func)EnAObj_Update2;
    } else {
        v0 = this->base.rotTowardsLinkY - this->base.shape.rot.y;
        v1 = (v0 < 0)? -v0 : v0;
        if ((v1 < 10240) || ((this->base.params == 1) && (v1 > 22528))) {
            func_800B863C((Actor*)this, ctxt);
        }
    }
}

void EnAObj_Update2(ActorEnAObj* this, GlobalContext* ctxt) {
    if (func_800B867C((Actor*)this, ctxt) != 0) {
        this->update = (actor_func)EnAObj_Update1;
    }
}

void EnAObj_Update(ActorEnAObj* this, GlobalContext* ctxt) {
    (this->update)((Actor*)this, (GlobalContext*)ctxt);
    Actor_SetHeight((Actor*)this, 45.0f);
    Collision_AddOT(ctxt, &ctxt->colCheckCtx, (ColCommon*)&this->collision);
}

void EnAObj_Draw(ActorEnAObj* this, GlobalContext* ctxt) {
    func_800BDFC0(ctxt, enAObjDisplayLists[this->base.params]);
}
