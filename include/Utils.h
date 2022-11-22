#pragma once

#include <iostream>
#include <string.h>

#include "TString.h"

#include "LEAF/Analyzer/include/useful_functions.h"

inline const TString BoolToTString(bool b) { return b ? "true" : "false";}


void PrintHeader(TString header, int max_lenght = 40, TString color="blue");


const float Z_mass_reco = 91;
const float Z_width_reco = 15;
const float Z_mass_offshell_reco = 25;
const float Z_width_offshell_reco = 20;
const float H_mass_reco = 125;
const float H_width_reco = 10;
