/* { dg-do assemble } */
/* { dg-options "-mrtd -Os -fno-optimize-sibling-calls --save-temps" } */

/* Test for a bug where the `-mrtd' switch was not actually honoured.  Issue
   found by Bart Oldeman --- https://github.com/tkchia/gcc-ia16/issues/20.  */

extern char *strdup (const char *);

char *
Estrdup (const char * const str)
{
  return strdup(str);
}

/* Estrdup (.) should _not_ adjust the stack after calling strdup (.): */
/* { dg-final { scan-assembler-not "addw\[ \\t\]\\$.*,\[ \\t\]%sp" } } */

/* Estrdup (.) _should_ pop one shortword: */
/* { dg-final { scan-assembler "ret\[ \\t\]\\\$2" } } */
