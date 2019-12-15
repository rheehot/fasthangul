#ifndef __FH_JAMO_H__
#define __FH_JAMO_H__

#include "PythonExtension.hh"
#include <string_view>
#include <unordered_map>

void initializeJamos();
std::wstring compose(std::wstring_view hangul);
std::wstring decompose(std::wstring_view hangul);

// utils
bool isHangul(const wchar_t character);
bool isJamo(const wchar_t character);
bool isChosung(const wchar_t character);
bool isJungsung(const wchar_t character);
bool isJongsung(const wchar_t character);
wchar_t getOneHangulFromJamo(wchar_t chosung, wchar_t jungsung);
wchar_t getOneHangulFromJamo(wchar_t chosung, wchar_t jungsung, wchar_t jongsung);

#endif /* __FH_JAMO_H__ */
