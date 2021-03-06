#pragma once

#include <iostream>
#include <string.h>

#include "TString.h"

#include "LEAF/Analyzer/include/useful_functions.h"

inline const TString BoolToTString(bool b) { return b ? "true" : "false";}


void PrintHeader(TString header, int max_lenght = 40, TString color="blue");
