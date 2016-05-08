/*
 * 2dx_structs
 *
 * Initializes Structs used in program to handle 2dx files.
 */

#ifndef __2DX_STRUCTS_H__
#define __2DX_STRUCTS_H__

//Declare Custom Types
typedef unsigned int  ct_uint;
typedef unsigned char ct_byte;

//Structs
typedef struct dx_arc {
    char*           fname;
    ct_uint         keysound_num;
    ct_uint         fsize;
    ct_byte*        byte;
    struct wavfile* export;
} DX_ARC;

typedef struct wavfile {
    char*           fname; //Name of .WAV file
    ct_uint         fsize; //Size of .WAV file
    ct_uint         pos;   //Position in .2dx file to start reading from
    struct dx_arc*  dx_f;  //File to extract from.
} WAVFILE;

typedef struct info {
    ct_byte verbose;
    ct_byte super_verbose;
    ct_byte info;
} INFO;

void initialize_info(INFO*);

#endif
