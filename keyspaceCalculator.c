/******************************************************************************
from : www.onlinegdb.com/online_c_compiler
                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////

typedef struct data
{
    int n;  // length of password
    int d;  // characterspace depth
    int c;  // consectutive repeats filter
    int r;  // repeats filter
}DATA;

////////////////////////////////////////////////////////////////////////////////

void printHelp(void)
{
// ruler.. 00000000001111111111222222222233333333334444444444555555555566666666667777777777
                printf("\n");
                printf("keyspaceCalculator\n");
                printf("(c) bl4krat 2018\n");
                printf("\n");
                printf("Written to obtain some test data to solve the following problem:\n");
                printf("\n");
                printf("How big is the keyspace for a password:\n");
                printf("  a) Consisting of n (length) characters, each from d (depth) possible\n");
                printf("     characters?\n");
                printf("  b) What if c identical consecutive characters  are prohibited?\n");
                printf("  c) What if you can't have r of the same character anywhere? (repeated letters)\n");
                printf("\n");
                printf("Useage:\n");
                printf("keyCal [options] n\n");
                printf("\n");
                printf("Options:\n");
                printf("  -d={value}  depth   - how many values to choose from. (default = 6)\n");
                printf("  -c={value}  doubles - disallow passwords with any character appearing c times\n");
                printf("                        in a row. (default = 0 = off)\n");
                printf("  -r={value}  repeats - disallow password with any charater repeated r times.\n");
                printf("                        (default = 0 = off)\n");
                printf("\n");
                printf("Note: -c1 or -d1 are both valid, but block all possible passwords.....\n");
                printf("\n");
                printf("Example:\n");
                printf("  keycal 8            (character depth 26, length 8)\n");
                printf("  keycal -d5 7        (character depth  5, length 7)\n");
                printf("  keycal -c2 -d10 10  (character depth 10, length 10, no double characters)\n");
}

////////////////////////////////////////////////////////////////////////////////

void printValues(DATA params)
{
                printf("length exactly                  n = %d\n", params.n);
                printf("characterset depth              d = %d\n", params.d);
                printf("disallow consecutive repeats of c = %d or more\n", params.c);
                printf("disallow             repeats of r = %d or more\n", params.r);
}

////////////////////////////////////////////////////////////////////////////////

// print an error message, the values, then quit()
void printError(char *text, DATA params)         
{
                printf("Error: ");
                printf("%s\n", text);
                printValues(params);
                printf("\n");
                exit(1);
}

////////////////////////////////////////////////////////////////////////////////

// Gets (but doesnt check) the values. 
// We could crash here if non-numerical values are typed.

DATA parseCommandLine(int argc, char *argv[])
{
                
                DATA params;
                params.n = 0; //initialise some trash values
                params.d = 0;
                params.c = 0;
                params.r = 0;
                
                if argc == 1:             // no parameters passsed
                                printError("You must supply a length. (try --help to see useage.)", params)
    
    int i
                for (i = 1; i < argc; i++)
                {
                    switch(argv[i])
                    {
            case "--help":      // print help
                printHelp();    // The printHelp() fn terminates execution...
                break;          // so this line never gets called.
                                    case "-d":          // set d(epth)
                                                    d = atoi(argv[i]);
                                                    break;
                        case "-c":          // set c(onsecutive)
                                                    c = atoi(argv[i]);
                                                    break;
                                case "-r":          // set r(epeats)
                                        r = atoi(argv[i]);
                        default:            // set (le)n(gth)
                                                    n = atoi(arg)
                    }
                }
                
                //validate()                                                                                         # sanity check values
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    
    // test data: (override any command line params)
    argc = 4
    argv = [8, 26, 4, 6]
    char *text = "Sorry, there is a fault.";

    // place to store the pramaters passed in command line
    DATA params;
    params = parseCommandLine(argc, argv);
    
    //printf("Hello World\n");
    //printHelp();
    //printValues(my_params);
    //printError(text, my_params);
    
    return 0;
}
