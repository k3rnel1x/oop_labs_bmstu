//
// Created by k3rnel1x on 02.05.2026.
//

#ifndef APPCONTEXT_H
#define APPCONTEXT_H

typedef struct AppContext {
    // UI between Backend
    const char* infix;
} AppContext;

typedef enum ResultCode {
    SUCCEED,
    ERROR,
} ResultCode;

typedef struct Params {
    const char* infix;
} Params;

#endif //APPCONTEXT_H
