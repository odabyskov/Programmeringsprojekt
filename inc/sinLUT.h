// =====================================================================
//
//	Exported by Cearn's excellut v1.0
//	(comments, kudos, flames to daytshen@hotmail.com)
//
// =====================================================================

#include <stdio.h>
#include "stm32f30x_conf.h"

#ifndef SINLUT_H
#define SINLUT_H

#include "calc.h"
#include "timing.h"
#include "objects.h"
#include "ansi.h"

// === LUT SIZES ===
#define SIN_SIZE 512
#define DIV_SIZE 160

// === LUT DECLARATIONS ===
extern const signed short SIN[512];
extern const signed int DIV[160];




#endif	// SINUS_H


