//
// Created by 龚喜 on 2024/8/23.
//

#ifndef ASSIMPDEMO_GL_FUNCTIONS_H
#define ASSIMPDEMO_GL_FUNCTIONS_H


#include <cstddef>

#ifdef DEBUG
#define GLCall(cmd) ([&]() { struct __ROAMGL_CHECK_ERROR { ~__ROAMGL_CHECK_ERROR() noexcept(false) { GLClearError(); cmd; GLLogCall(#cmd, __FILE__, __LINE__); } } __ROAMGL_CHECK_ERROR; return cmd; }())
#else
#define GLCall(cmd) (cmd)
#endif

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);


#endif //ASSIMPDEMO_GL_FUNCTIONS_H
