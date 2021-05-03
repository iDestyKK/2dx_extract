/*
 * Beatmania IIDX AC 2DX Extractor
 *
 * Description:
 *     Extracts audio (and just about everything else) from .2dx archives.
 *     The extraction assumes WAV format. Every file tested has "RIFF" header.
 *     Tested on Beatmania IIDX 22 PENDUAL .2dx archives.
 *
 * To Compile:
 *     LINUX  : Type "make" in the terminal.
 *     WINDOWS: Open Visual Studio 2015 and make an new project. Drag this file and all files in "lib/" in.
 *              Compile it. Or, since I was feeling generous, I compiled it for you. Look in "bin/". :)
 *
 * Author:
 *     Clara Van Nguyen (iDestyKK)
 */

//C Include
#include <stdio.h>
#include <stdlib.h>

//Self-made Libraries for this program
#include "lib/arg_parse.h"
#include "lib/2dx_structs.h"
#include "lib/2dx_parse.h"

int main(int argc, char** argv /*, char** envp*/) {
    //Argument Parse
    INFO DATA;
    initialize_info(&DATA);
    parse_argv(argc, argv, &DATA);

    //Read 2DX data
    DX_ARC ARC;
    read_2DX(argv[argc - 1], &ARC);

    //Process the information we want.
    if (DATA.info)
        print_2dx_info(argc, argv, &ARC);
    else {
        parse_data  (&ARC, &DATA);
        extract_data(&ARC);
    }
    arc_free(&ARC);

    //Have a nice day
    return 0;
}
