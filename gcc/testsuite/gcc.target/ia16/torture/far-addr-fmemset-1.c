/* { dg-options "-std=gnu11 --save-temps" } */
/* { dg-do assemble } */

/*
 * Compiling a memset (...)-type routine that works over far pointers used
 * to cause a compiler crash at some optimization levels.  Reported by Lino
 * Mastrodomenico --- https://github.com/tkchia/gcc-ia16/issues/86 .
 */

void test(char __far *buf) {
    for (int x = 0; x < 16; x++) {
        buf[x] = 0xf6;
    }
}

struct foo {
    long double x, y, z, w;
};

void test2(struct foo __far *buf)
{
    *buf = (struct foo){ 0, 0, 0, 0 };
}
