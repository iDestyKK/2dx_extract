/*
 * 2dx_parse
 *
 * Initializes functions to parse 2DX files.
 */

#include "2dx_parse.h"

void read_2DX(char* fname, DX_ARC* ARC) {
    FILE* fp = fopen(fname, "rb");
    if (fp == NULL) {
        perror("[ ERROR ] Failed to open 2DX Archive");
        exit(2);
    }

    //Get File Size
    fseek(fp, (size_t)0, SEEK_END);
    ARC->fsize = ftell(fp);
    rewind(fp);

    //Read bytes into struct
    ARC->byte = (ct_byte*) malloc(sizeof(ct_byte) * ARC->fsize);
    fread(ARC->byte, sizeof(ct_byte), ARC->fsize, fp);

    fclose(fp);

    //Prepare memory for Keysounds
    ARC->keysound_num = ARC->byte[0x14] + ((ct_uint)ARC->byte[0x15] << 8);
    ARC->export       = (WAVFILE*) malloc(sizeof(WAVFILE) * ARC->keysound_num);
}

ct_byte SDX9_CHECK(ct_byte* byte, ct_uint pos) {
    //All audio files have SDX9 and 0x14 additional bytes before the actual file begins.
    return (byte[pos    ] == 0x32 &&
            byte[pos + 1] == 0x44 &&
            byte[pos + 2] == 0x58 &&
            byte[pos + 3] == 0x39);
}

void print_2dx_info(int argc, char** argv, DX_ARC* ARC) {
    printf("'%s' Archive Information\n\n", argv[argc - 1]);
    printf("    Filename: %s\n", argv[argc - 1]);
    printf("    Files   : %d\n", ARC->keysound_num);
    printf("    Size    : %d bytes\n", ARC->fsize);
    printf("\nType '%s %s' to extract the contents of this archive.\n", argv[0], argv[argc - 1]);
}

void parse_data(DX_ARC* ARC, INFO* DATA) {
    //Find where the keysounds are in the file.
    ct_uint i = 0,
            c = 0;

    for (; i < ARC->fsize; i++) {
        if (SDX9_CHECK(ARC->byte, i)) {
            //Get WAV filesize.
            ARC->export[c].fsize = ARC->byte[i + 0x8] +
                        ((ct_uint) ARC->byte[i + 0x9] <<  8) +
                        ((ct_uint) ARC->byte[i + 0xA] << 16) +
                        ((ct_uint) ARC->byte[i + 0xB] << 24);
            i += 0x18;
            ARC->export[c].pos = i;
            i += ARC->export[c].fsize - 1;
            if (DATA->verbose)
                printf("Found %d.wav\n", c + 1, ARC->export[c].pos);
            if (DATA->super_verbose)
                printf("Found %d.wav\n    Address: 0x%08x ~ 0x%08x\n    Size: 0x%x (%d bytes)\n\n",
                       c + 1, ARC->export[c].pos, ARC->export[c].pos + ARC->export[c].fsize, ARC->export[c].fsize, ARC->export[c].fsize);
            c++; //You should get this joke...
        }
    }
}

void extract_data(DX_ARC* ARC) {
    //Get character count for filename
    //e.g. 1000 = 4 characters
    ct_uint fsc    = 0,
            fs_tmp = ARC->keysound_num,
            i      = 0;

    while (fs_tmp > 0) {
        fs_tmp /= 10;
        fsc++;
    }

    //Extract the data
    char fex[15];
    FILE* fp;
    for (i = 0; i < ARC->keysound_num; i++) {
        sprintf(fex, "%0*d.wav", fsc, i + 1);
        printf("Extracting %s... ", fex);

        fp = fopen(fex, "wb");
        fwrite(ARC->byte + ARC->export[i].pos, sizeof(ct_byte), ARC->export[i].fsize, fp);
        fclose(fp);

        printf("Done\n");
    }
}
