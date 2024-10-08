//
// Created by 2333 xiang on 2024/9/1.
//

#ifndef GLOBALSCREENLIBRARY_KEYMAPS_H
#define GLOBALSCREENLIBRARY_KEYMAPS_H

#include "unordered_map"
#include "string"

using namespace std;

// 定义键码的枚举类型，包含功能键和修饰键
enum class KeyType : int {
    KEY_A = 0, KEY_B = 11, KEY_C = 8, KEY_D = 2,
    KEY_E = 14, KEY_F = 3, KEY_G = 5, KEY_H = 4,
    KEY_I = 34, KEY_J = 38, KEY_K = 40, KEY_L = 37,
    KEY_M = 46, KEY_N = 45, KEY_O = 31, KEY_P = 35,
    KEY_Q = 12, KEY_R = 15, KEY_S = 1, KEY_T = 17,
    KEY_U = 32, KEY_V = 9, KEY_W = 13, KEY_X = 7,
    KEY_Y = 16, KEY_Z = 6, KEY_0 = 29, KEY_1 = 18,
    KEY_2 = 19, KEY_3 = 20, KEY_4 = 21, KEY_5 = 23,
    KEY_6 = 22, KEY_7 = 26, KEY_8 = 28, KEY_9 = 25,
    // 特殊键
    KEY_SPACE = 49, KEY_RETURN = 36, KEY_TAB = 48, KEY_L_SHIFT = 56,
    KEY_L_CTRL = 59, KEY_L_ALT = 58, KEY_L_CMD = 55, KEY_R_SHIFT = 60,
    KEY_R_CTRL = 257, KEY_R_ALT = 61, KEY_R_CMD = 54, KEY_ESC = 53,
    KEY_CAPS_LOCK = 57, KEY_FN = 179, KEY_BACKSPACE = 51,

    // 功能键
    KEY_F1 = 122, KEY_F2 = 120, KEY_F3 = 99, KEY_F4 = 118,
    KEY_F5 = 96, KEY_F6 = 97, KEY_F7 = 98, KEY_F8 = 100,
    KEY_F9 = 101, KEY_F10 = 109, KEY_F11 = 103, KEY_F12 = 111,

    // 符号键
    KEY_TILDE = 50, KEY_MINUS = 27, KEY_EQUALS = 24, KEY_LEFT_BRACKET = 33,
    KEY_RIGHT_BRACKET = 30, KEY_BACKSLASH = 42, KEY_SEMICOLON = 41,
    KEY_QUOTE = 39, KEY_COMMA = 43, KEY_DOT = 47, KEY_SLASH = 44,
    KEY_GRAVE = 50, // 波浪号 (~)

    // 方向键
    KEY_ARROW_LEFT = 123, KEY_ARROW_RIGHT = 124, KEY_ARROW_UP = 126, KEY_ARROW_DOWN = 125
};
namespace keyMap {
    // 字符到键码枚举的映射
    [[maybe_unused]] const std::unordered_map<string, KeyType> keyMap = {
            {"a",         KeyType::KEY_A},
            {"b",         KeyType::KEY_B},
            {"c",         KeyType::KEY_C},
            {"d",         KeyType::KEY_D},
            {"e",         KeyType::KEY_E},
            {"f",         KeyType::KEY_F},
            {"g",         KeyType::KEY_G},
            {"h",         KeyType::KEY_H},
            {"i",         KeyType::KEY_I},
            {"j",         KeyType::KEY_J},
            {"k",         KeyType::KEY_K},
            {"l",         KeyType::KEY_L},
            {"m",         KeyType::KEY_M},
            {"n",         KeyType::KEY_N},
            {"o",         KeyType::KEY_O},
            {"p",         KeyType::KEY_P},
            {"q",         KeyType::KEY_Q},
            {"r",         KeyType::KEY_R},
            {"s",         KeyType::KEY_S},
            {"t",         KeyType::KEY_T},
            {"u",         KeyType::KEY_U},
            {"v",         KeyType::KEY_V},
            {"w",         KeyType::KEY_W},
            {"x",         KeyType::KEY_X},
            {"y",         KeyType::KEY_Y},
            {"z",         KeyType::KEY_Z},
            {"A",         KeyType::KEY_A},
            {"B",         KeyType::KEY_B},
            {"C",         KeyType::KEY_C},
            {"D",         KeyType::KEY_D},
            {"E",         KeyType::KEY_E},
            {"F",         KeyType::KEY_F},
            {"G",         KeyType::KEY_G},
            {"H",         KeyType::KEY_H},
            {"I",         KeyType::KEY_I},
            {"J",         KeyType::KEY_J},
            {"K",         KeyType::KEY_K},
            {"L",         KeyType::KEY_L},
            {"M",         KeyType::KEY_M},
            {"N",         KeyType::KEY_N},
            {"O",         KeyType::KEY_O},
            {"P",         KeyType::KEY_P},
            {"Q",         KeyType::KEY_Q},
            {"R",         KeyType::KEY_R},
            {"S",         KeyType::KEY_S},
            {"T",         KeyType::KEY_T},
            {"U",         KeyType::KEY_U},
            {"V",         KeyType::KEY_V},
            {"W",         KeyType::KEY_W},
            {"X",         KeyType::KEY_X},
            {"Y",         KeyType::KEY_Y},
            {"Z",         KeyType::KEY_Z},
            {"0",         KeyType::KEY_0},
            {"1",         KeyType::KEY_1},
            {"2",         KeyType::KEY_2},
            {"3",         KeyType::KEY_3},
            {"4",         KeyType::KEY_4},
            {"5",         KeyType::KEY_5},
            {"6",         KeyType::KEY_6},
            {"7",         KeyType::KEY_7},
            {"8",         KeyType::KEY_8},
            {"9",         KeyType::KEY_9},
            {"Space",     KeyType::KEY_SPACE},
            {"Enter",     KeyType::KEY_RETURN},
            {"Table",     KeyType::KEY_TAB},
            {"LShift",    KeyType::KEY_L_SHIFT},
            {"RShift",    KeyType::KEY_R_SHIFT},
            {"LControl",  KeyType::KEY_L_CTRL},
            {"RControl",  KeyType::KEY_R_CTRL},
            {"LAlt",      KeyType::KEY_L_ALT},
            {"RAlt",      KeyType::KEY_R_ALT},
            {"LCommand",  KeyType::KEY_L_CMD},
            {"RCommand",  KeyType::KEY_R_CMD},
            {"Esc",       KeyType::KEY_ESC},
            {"CapsLock",  KeyType::KEY_CAPS_LOCK},
            {"BackSpace", KeyType::KEY_BACKSPACE},
            {"FN",        KeyType::KEY_FN},
            {"F1",        KeyType::KEY_F1},
            {"F2",        KeyType::KEY_F2},
            {"F3",        KeyType::KEY_F3},
            {"F4",        KeyType::KEY_F4},
            {"F5",        KeyType::KEY_F5},
            {"F6",        KeyType::KEY_F6},
            {"F7",        KeyType::KEY_F7},
            {"F8",        KeyType::KEY_F8},
            {"F9",        KeyType::KEY_F9},
            {"F10",       KeyType::KEY_F10},
            {"F11",       KeyType::KEY_F11},
            {"F12",       KeyType::KEY_F12},
            {"-",         KeyType::KEY_MINUS},
            {"=",         KeyType::KEY_EQUALS},
            {"[",         KeyType::KEY_LEFT_BRACKET},
            {"]",         KeyType::KEY_RIGHT_BRACKET},
            {"\\",        KeyType::KEY_BACKSLASH},
            {";",         KeyType::KEY_SEMICOLON},
            {"\'",        KeyType::KEY_QUOTE},
            {",",         KeyType::KEY_COMMA},
            {".",         KeyType::KEY_DOT},
            {"/",         KeyType::KEY_SLASH},
            {"`",         KeyType::KEY_GRAVE},
            {"<",         KeyType::KEY_ARROW_LEFT},
            {">",         KeyType::KEY_ARROW_RIGHT},
            {"^",         KeyType::KEY_ARROW_UP},
            {"v",         KeyType::KEY_ARROW_DOWN}
    };

    // 定义keyCode到 KeyType 枚举的映射
    const std::unordered_map<int, KeyType> KeyTypeMap = {
            {0,   KeyType::KEY_A},
            {11,  KeyType::KEY_B},
            {8,   KeyType::KEY_C},
            {2,   KeyType::KEY_D},
            {14,  KeyType::KEY_E},
            {3,   KeyType::KEY_F},
            {5,   KeyType::KEY_G},
            {4,   KeyType::KEY_H},
            {34,  KeyType::KEY_I},
            {38,  KeyType::KEY_J},
            {40,  KeyType::KEY_K},
            {37,  KeyType::KEY_L},
            {46,  KeyType::KEY_M},
            {45,  KeyType::KEY_N},
            {31,  KeyType::KEY_O},
            {35,  KeyType::KEY_P},
            {12,  KeyType::KEY_Q},
            {15,  KeyType::KEY_R},
            {1,   KeyType::KEY_S},
            {17,  KeyType::KEY_T},
            {32,  KeyType::KEY_U},
            {9,   KeyType::KEY_V},
            {13,  KeyType::KEY_W},
            {7,   KeyType::KEY_X},
            {16,  KeyType::KEY_Y},
            {6,   KeyType::KEY_Z},
            {29,  KeyType::KEY_0},
            {18,  KeyType::KEY_1},
            {19,  KeyType::KEY_2},
            {20,  KeyType::KEY_3},
            {21,  KeyType::KEY_4},
            {23,  KeyType::KEY_5},
            {22,  KeyType::KEY_6},
            {26,  KeyType::KEY_7},
            {28,  KeyType::KEY_8},
            {25,  KeyType::KEY_9},
            {49,  KeyType::KEY_SPACE},
            {36,  KeyType::KEY_RETURN},
            {48,  KeyType::KEY_TAB},
            {56,  KeyType::KEY_L_SHIFT},
            {60,  KeyType::KEY_R_SHIFT},
            {59,  KeyType::KEY_L_CTRL},
            {257, KeyType::KEY_R_CTRL},
            {58,  KeyType::KEY_L_ALT},
            {61,  KeyType::KEY_R_ALT},
            {55,  KeyType::KEY_L_CMD},
            {54,  KeyType::KEY_R_CMD},
            {53,  KeyType::KEY_ESC},
            {57,  KeyType::KEY_CAPS_LOCK},
            {51,  KeyType::KEY_BACKSPACE},
            {179, KeyType::KEY_FN},
            {122, KeyType::KEY_F1},
            {120, KeyType::KEY_F2},
            {99,  KeyType::KEY_F3},
            {118, KeyType::KEY_F4},
            {96,  KeyType::KEY_F5},
            {97,  KeyType::KEY_F6},
            {98,  KeyType::KEY_F7},
            {100, KeyType::KEY_F8},
            {101, KeyType::KEY_F9},
            {109, KeyType::KEY_F10},
            {103, KeyType::KEY_F11},
            {111, KeyType::KEY_F12},
            {50,  KeyType::KEY_TILDE},
            {27,  KeyType::KEY_MINUS},
            {24,  KeyType::KEY_EQUALS},
            {33,  KeyType::KEY_LEFT_BRACKET},
            {30,  KeyType::KEY_RIGHT_BRACKET},
            {42,  KeyType::KEY_BACKSLASH},
            {41,  KeyType::KEY_SEMICOLON},
            {39,  KeyType::KEY_QUOTE},
            {43,  KeyType::KEY_COMMA},
            {47,  KeyType::KEY_DOT},
            {44,  KeyType::KEY_SLASH},
            {50,  KeyType::KEY_GRAVE}, // 波浪号 (~)
            {123, KeyType::KEY_ARROW_LEFT},
            {124, KeyType::KEY_ARROW_RIGHT},
            {126, KeyType::KEY_ARROW_UP},
            {125, KeyType::KEY_ARROW_DOWN}
    };

    // 反向映射，从 KeyType 到字符
    const std::unordered_map<KeyType, string> reverseKeyMap = {
            {KeyType::KEY_A,             "a"},
            {KeyType::KEY_B,             "b"},
            {KeyType::KEY_C,             "c"},
            {KeyType::KEY_D,             "d"},
            {KeyType::KEY_E,             "e"},
            {KeyType::KEY_F,             "f"},
            {KeyType::KEY_G,             "g"},
            {KeyType::KEY_H,             "h"},
            {KeyType::KEY_I,             "i"},
            {KeyType::KEY_J,             "j"},
            {KeyType::KEY_K,             "k"},
            {KeyType::KEY_L,             "l"},
            {KeyType::KEY_M,             "m"},
            {KeyType::KEY_N,             "n"},
            {KeyType::KEY_O,             "o"},
            {KeyType::KEY_P,             "p"},
            {KeyType::KEY_Q,             "q"},
            {KeyType::KEY_R,             "r"},
            {KeyType::KEY_S,             "s"},
            {KeyType::KEY_T,             "t"},
            {KeyType::KEY_U,             "u"},
            {KeyType::KEY_V,             "v"},
            {KeyType::KEY_W,             "w"},
            {KeyType::KEY_X,             "x"},
            {KeyType::KEY_Y,             "y"},
            {KeyType::KEY_Z,             "z"},
            {KeyType::KEY_0,             "0"},
            {KeyType::KEY_1,             "1"},
            {KeyType::KEY_2,             "2"},
            {KeyType::KEY_3,             "3"},
            {KeyType::KEY_4,             "4"},
            {KeyType::KEY_5,             "5"},
            {KeyType::KEY_6,             "6"},
            {KeyType::KEY_7,             "7"},
            {KeyType::KEY_8,             "8"},
            {KeyType::KEY_9,             "9"},
            {KeyType::KEY_SPACE,         "Space"},
            {KeyType::KEY_RETURN,        "Enter"},
            {KeyType::KEY_TAB,           "Table"},
            {KeyType::KEY_L_SHIFT,       "LShift"},
            {KeyType::KEY_R_SHIFT,       "RShift"},
            {KeyType::KEY_L_CTRL,        "LControl"},
            {KeyType::KEY_R_CTRL,        "RControl"},
            {KeyType::KEY_L_ALT,         "LAlt"},
            {KeyType::KEY_R_ALT,         "RAlt"},
            {KeyType::KEY_L_CMD,         "LCommand"},
            {KeyType::KEY_R_CMD,         "RCommand"},
            {KeyType::KEY_ESC,           "Esc"},
            {KeyType::KEY_CAPS_LOCK,     "CapsLock"},
            {KeyType::KEY_BACKSPACE,     "BackSpace"},
            {KeyType::KEY_FN,            "FN"},
            {KeyType::KEY_F1,            "F1"},
            {KeyType::KEY_F2,            "F2"},
            {KeyType::KEY_F3,            "F3"},
            {KeyType::KEY_F4,            "F4"},
            {KeyType::KEY_F5,            "F5"},
            {KeyType::KEY_F6,            "F6"},
            {KeyType::KEY_F7,            "F7"},
            {KeyType::KEY_F8,            "F8"},
            {KeyType::KEY_F9,            "F9"},
            {KeyType::KEY_F10,           "F10"},
            {KeyType::KEY_F11,           "F11"},
            {KeyType::KEY_F12,           "F12"},
            {KeyType::KEY_MINUS,         "-"},
            {KeyType::KEY_EQUALS,        "="},
            {KeyType::KEY_LEFT_BRACKET,  "["},
            {KeyType::KEY_RIGHT_BRACKET, "]"},
            {KeyType::KEY_BACKSLASH,     "\\"},
            {KeyType::KEY_SEMICOLON,     ";"},
            {KeyType::KEY_QUOTE,         "\'"},
            {KeyType::KEY_COMMA,         ","},
            {KeyType::KEY_DOT,           "."},
            {KeyType::KEY_SLASH,         "/"},
            {KeyType::KEY_GRAVE,         "`"},
            {KeyType::KEY_ARROW_LEFT,    "⬅"},
            {KeyType::KEY_ARROW_RIGHT,   "➡"},
            {KeyType::KEY_ARROW_UP,      "⬆"},
            {KeyType::KEY_ARROW_DOWN,    "⬇"}
    };

}
#endif //GLOBALSCREENLIBRARY_KEYMAPS_H
