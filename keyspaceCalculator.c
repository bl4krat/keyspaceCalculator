// keyspaceCalculator
//
// Written to obtain some test data to solve the
// following problem:
//
// How big is the keyspace for a password:
// a) Consisting of l characters, each from n possible charaters?
// b) What if d identical characters in a row are prohibited? or (not and)
// c) What if you can't have r of the same character anywhere?
//
// (c) bl4krat 2018
//
// The numbers involved rapidly become impractical to brute-force.
// so for sanity, we set the following maximum values (see validate() ):
//
// Max password length = 15, Max depth = 26
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
  
////////////////////////////////////////////////////////////////////////////////

#define MAX_N 15  // Password length (required)
#define MIN_N  1

#define MAX_D 26	// characterSpace: so we only use [A...Z] (chr(65)...chr(90))
#define MIN_D  1	// (d = depth) (any value less than n will block all passwords)

#define MAX_C  params.n	// max value is the password length
#define MIN_C  0		    // Dont blacklist based on the 'double letter' rule

#define MAX_R  params.n    // max value is the password length
#define MIN_R  0           //Dont blacklist based on 'repeated' letters

typedef struct 
{
  int n;			// length of password
  int d;			// characterspace depth
  int c;			// consectutive repeats filter
  int r;			// repeats filter
} DATA;

typedef struct
{
  int candidate;    // how many possible passwords
  int valid;        // how many valid passwords
} COUNTERS;

typedef struct
{
  bool isValid;     // is this password valid?
  char *message;    // validation message (reason it was passed or failed)
} VALIDATION
////////////////////////////////////////////////////////////////////////////////
  
void printHelp (void) 
{
// ruler..00000000001111111111222222222233333333334444444444555555555566666666667777777777
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
  
  exit(2);
} 

////////////////////////////////////////////////////////////////////////////////
  
void
printValues (DATA params) 
{
  printf ("length exactly                  n = %d\n", params.n);
  printf ("characterset depth              d = %d\n", params.d);
  printf ("disallow consecutive repeats of c = %d or more\n", params.c);
  printf ("disallow             repeats of r = %d or more\n", params.r);
} 
 
////////////////////////////////////////////////////////////////////////////////
  
// print an error message, the values, then quit()
  void
printError (char *text, DATA params) 
{
  printf("Error: ");
  printf("%s\n", text);
  printValues (params);
  printf("\n");
  exit(1);
} 

////////////////////////////////////////////////////////////////////////////////

DATA validate(DATA params)		// Checks values are in range (if we got this far)
{
  char * message;
  
  if ((params.n < MIN_N) || (params.n > MAX_N))     // n out of range
  {
    snprintf(message, 100, "Length must be between %d & %d", MIN_N, MAX_N);
    printError(message, params);
  }  
  if ((params.d < MIN_D) || (params.d > MAX_D))     // d out of range
  {
    snprintf(message, 100, "Character depth must be between %d & %d", MIN_D, MAX_D);
    printError(message, params);
  } 
  if ((params.c < MIN_C) || (params.c > MAX_C))     // c out of range
  {
    snprintf(message, 100, "Consecutive repeats must be between %d & %d", MIN_C, MAX_C);
    printError(message, params);
  } 
  if ((params.r < MIN_R) || (params.r > MAX_R))     // r out of range
  {
    snprintf(message, 100, "Repeats must be between %d & %d", MIN_R, MAX_R);
    printError(message, params);
  }
  
  return(params);
}

////////////////////////////////////////////////////////////////////////////////
  
// Gets (but doesnt check) the values. 
// We could crash here if a malicious command line is passed....
  
DATA parseCommandLine (int argc, char *argv[]) 
{
  DATA params;      // initialise default values:
  params.n = 0;		// do nothing and quit.
  params.d = 0;     // default depth (ie choose from [ABCDEF] only
  params.c = 0;     // default consecutive repeat = off
  params.r = 0;     // default             repeat = off
  
  if (argc == 1)	// no parameters passsed
    printError ("You must supply a length. (try --help to see useage.)", params);
                    //printError() also terminates execution. 
    
  int i; 
  for (i = 1; i < argc; i++)
  {
	if (strcmp(argv[i], "--help") == 0)     // print help
	  printHelp ();                         // The printHelp() fn terminates execution...
	    
	if (strcmp(argv[i], "-d") == 0)         // set d(epth)
	{
	  params.d = atoi(argv[i + 1]);
	  i++;
	}
	
	else if (strcmp(argv[i], "-c") == 0)	// set c(onsecutive)
    {
      params.c = atoi(argv[i + 1]);
	  i++;
    }
    
    else if (strcmp(argv[i], "-r") == 0)    // set r(epeats)
    {
	  params.r = atoi(argv[i + 1]);
	  i++;
    }
    
    else                  		// set (le)n(gth)
    {
	  params.n = atoi(argv[i]); 
    }
  }
 
  printValues(params);
  return(validate(params));   // sanity check values & return
}
 
////////////////////////////////////////////////////////////////////////////////

COUNTERS checkForPasswords(COUNTERS counters, DATA params, char *password)
{
    char base = 'A';
    VALIDATION checkResult;
	
	if (params.n == 0)			# nothing to add, so we validate the password here
	{
		counters.candidate += 1;
		checkResult.isValid = true;
		checkResult.message = "No filter failures";
		
		if c > 0 or r > 0 :		#then we must validate
			????? = validatePassword(c, r, password)
			
		if valid:
			validPasswordCount += 1
			
		#print(password + ": " + str(valid) + " - " + reason)
											#you REALLY dont want to print each
											#possible password unless you are
											#debugging. For n=4, d=26, (456976 passwords)
											#this changes execution time from 0.4 seconds
											#to 26 seconds on a 49 row high cmd prompt
											#or 17 seconds on an 8 row high cmd prompt
											#on windows10 with a core i7-7700.
	} else
	{
		for letter in range(d):	# recursively add the next letter
			checkForPasswords(n-1, d, c, r, password + chr(letter + base))
	}
}

////////////////////////////////////////////////////////////////////////////////
  
int
main (int argc, char *argv[]) 
{

  char *text = "Sorry, there is a fault.";
  
  // place to store the pramaters passed in command line
  DATA params;
  params = parseCommandLine (argc, argv);
  
  //printf("Hello World\n");
  //printHelp();
  //printValues(my_params);
  //printError(text, my_params);
  
  COUNTERS counters;
  counters->valid     = 0;
  counters->candidate = 0;
 
  counters = checkForPasswords(counters, params, '');
  
  return 0;
}


