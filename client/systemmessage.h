#ifndef SYSTEMMESSAGE_H
#define SYSTEMMESSAGE_H

#include <QtGlobal>

enum SystemMessage : quint16 {
    ChatMessage = 0,
    Login = 1,
    Registration = 2,
    Fail = 3,
    Success = 4
};

#endif // SYSTEMMESSAGE_H
