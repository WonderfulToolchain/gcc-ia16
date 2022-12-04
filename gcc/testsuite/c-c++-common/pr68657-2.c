/* PR c/68657 */
/* { dg-do compile } */
/* { dg-options "-Werror=larger-than=8192" } */

int a[16384/sizeof (int)];	/* { dg-error "size of 'a' is \[1-9]\[0-9]* bytes" } */
int b[1024];	/* { dg-bogus "size of 'b' is \[1-9]\[0-9]* bytes" } */

/* { dg-prune-output "treated as errors" } */
