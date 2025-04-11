/* Test file for simple #define processor */

// Basic defines and usage
#define MAX 100
#define MIN 0
#define PI 3.14159
int max = MAX;  // should be 100
float pi = PI;  // should be 3.14159
int min = MIN;  // should be 0

// Multiple defines for same name (should use last one)
#define TEST abc
#define TEST xyz
char *test = TEST;  // should be xyz

// Defines in various contexts - should NOT be processed
char *str = "MAX MIN #define TEST foo";  // should stay as is
/* MAX MIN PI TEST */ // should stay as is
// MAX MIN PI TEST    // should stay as is

// TODO not processing
// Weird spacing - should still work
#   define    SPACE     hello    world
char *space = SPACE;  // should be hello    world

// Comments between # and define - should NOT work
# /* comment */ define INVALID 123

// Case sensitivity test
#define lowercase small
#define LOWERCASE LARGE
char *a = lowercase;  // should be small
char *b = LOWERCASE;  // should be LARGE

// TODO only being assigned start of each digit
// Hash collision test (carefully chosen to hit same bucket)
#define AAA 111
#define BBB 222
#define CCC 333
int aa = AAA;  // should be 111
int bb = BBB;  // should be 222
int cc = CCC;  // should be 333

// Identifiers containing defined names - should NOT be replaced
int MAX_VALUE = 200;  // MAX should not be replaced
char *MIN_str = "hi"; // MIN should not be replaced

// Special characters in definitions
#define QUOTE "hello"
#define APOS 'x'
#define SYMBOLS !@#$% // TODO value not fully processed
char *quote = QUOTE;    // should be "hello"
char apos = APOS;       // should be 'x'
char *syms = SYMBOLS;   // should be !@#$% // TODO only assigned !

// End of file tests
#define EOF_TEST last
char *eof = EOF_TEST;   // should be last
#define IGNORED never_seen  // should be ignored due to no newline at end
