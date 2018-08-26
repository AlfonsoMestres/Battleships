#pragma once

enum class seaState { GUESS, WATER, HIT, SHIP };

int RandomizeBetween(int min, int max);

bool is_number(const std::string& s);

int  inputNumberBetween(std::string prompt, int min, int max);

std::string ToLowerCase(std::string strToConvert);

bool Same(const std::string& a, const std::string& b);