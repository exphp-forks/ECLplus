#include "pch.h"
#include "ins2200.h"
#include "ECLplus.h"

static std::map<DWORD, MESSAGELIST*> msgmap;

static VOID ChannelReset(MESSAGELIST* list) {
    for (auto itr = list->begin(); itr != list->end(); ++itr) {
        delete *itr;
    }
    list->clear();
}

static VOID MsgReset() {
    while (!msgmap.empty()) {
        auto itr = msgmap.begin();
        ChannelReset(itr->second);
        delete itr->second;
        msgmap.erase(itr);
    }
}

static VOID MsgReset(DWORD channel) {
    auto itr = msgmap.find(channel);
    if (itr != msgmap.end()) {
        ChannelReset(itr->second);
        delete itr->second;
        msgmap.erase(itr);
    }
}

static VOID MsgSend(DWORD channel, MESSAGE* msg) {
    if (msgmap.find(channel) == msgmap.end()) {
        msgmap.insert({channel, new MESSAGELIST});
    }
    auto list = msgmap.at(channel);
    list->push_back(msg);
}

static MESSAGE* MsgReceive(DWORD channel) {
    auto itr = msgmap.find(channel);
    if (itr != msgmap.end()) {
        if (!itr->second->empty()) {
            MESSAGE* msg = itr->second->front();
            itr->second->pop_front();
            return msg;
        }
    }
    return NULL;
}

BOOL ins_2200(ENEMY enm, INSTR* ins) {
    switch (ins->id - 2200) {
        case INS_MSG_RESET:
            MsgReset();
            break;
        case INS_MSG_RESET_CHANNEL:
            MsgReset(GetIntArg(enm, 0));
            break;
        case INS_MSG_SEND: {
            MESSAGE* msg = new MESSAGE;
            msg->a = GetFloatArg(enm, 0);
            msg->b = GetFloatArg(enm, 1);
            msg->c = GetFloatArg(enm, 2);
            msg->d = GetFloatArg(enm, 3);
            MsgSend(GetIntArg(enm, 4), msg);
            break;
        }
        case INS_MSG_RECEIVE: {
            MESSAGE* msg = MsgReceive(GetIntArg(enm, 5));
            
            DWORD* ptr = GetIntArgAddr(enm, 0);
            if (ptr != NULL) *ptr = msg == NULL ? 0 : 1;
            if (msg == NULL) break;

            FLOAT* fptr;
            fptr = GetFloatArgAddr(enm, 1);
            if (fptr != NULL) *fptr = msg->a;
            fptr = GetFloatArgAddr(enm, 2);
            if (fptr != NULL) *fptr = msg->b;
            fptr = GetFloatArgAddr(enm, 3);
            if (fptr != NULL) *fptr = msg->c;
            fptr = GetFloatArgAddr(enm, 4);
            if (fptr != NULL) *fptr = msg->d;

            delete msg;
            break;
        }
        default:
            return FALSE;
    }
    return TRUE;
}