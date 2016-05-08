/*
 * Argument Parser
 *
 * Contains function defintions for argument parsing in 2dx_extract.
 */

#include "2dx_structs.h"
#include "arg_parse.h"

void parse_argv(int argc, char** argv, INFO *DATA) {
    if (argc < 2) {
        //Obviously you have no idea what you are doing...
        fprintf(stderr, "Usage: 2dx_extract [options] [.2dx file]\nTry '2dx_extract -h' for more information.\n");
        exit(1);
    }

    ct_uint argt = 0;
    ct_byte eo   = 0;
    for (; argt < argc; argt++) {
        if (argv[argt][0] == '-') {
            //Option
            switch (argv[argt][1]) {
                case 'h':
                    //Help
                    fprintf(stderr, "2DX Extractor\nExtracts WAV files (And just about anything else) from beatmania IIDX AC .2dx Archives\n\n");
                    fprintf(stderr, "Options:\n    -h - Shows this help page\n    -i - Shows .2dx archive info (Without Extracting)\n    -v - Verbose\n    -v - Super Verbose (Shows more information)\n");
                    break;
                case 'i':
                    //Archive Info
                    DATA->info = 1;
                    break;
                case 'v':
                    //Verbose
                    DATA->verbose = 1;
                    break;
                case 'V':
                    //Super Verbose
                    DATA->super_verbose = 1;
                    break;
                default:
                    fprintf(stderr, "[WARNING] Invalid Option \"-%c\"\n", argv[argt][1]);
                    eo = (argt == argc - 1);
                    break;
            }
        }
    }

    if (eo == 1) {
        fprintf(stderr, "[ ERROR ] Last argument is not .2dx archive\n");
        exit(2); //An error(s) has occured.
    }

    if (argv[argt - 1][0] == '-')
        exit(0); //The user simply didn't specify a file
}
