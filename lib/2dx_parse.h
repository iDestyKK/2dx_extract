/*
 * 2dx_parse
 *
 * Initializes functions to parse 2DX files.
 */

#ifndef __2DX_PARSE_H__
#define __2DX_PARSE_H__

#include <stdio.h>
#include <stdlib.h>

#include "2dx_structs.h"

void    read_2DX      (char*   , DX_ARC*);
ct_byte SDX9_CHECK    (ct_byte*, ct_uint);
void    print_2dx_info(int     , char** , DX_ARC*);
void    parse_data    (DX_ARC* , INFO*);
void    extract_data  (DX_ARC*);

#endif
