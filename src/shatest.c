/*
 *  shatest.c
 *
 *  Copyright (C) 1998, 2009
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *****************************************************************************
 *  $Id: shatest.c 12 2009-06-22 19:34:25Z paulej $
 *****************************************************************************
 *
 *  Description:
 *      This file will exercise the SHA1 class and perform the three
 *      tests documented in FIPS PUB 180-1.
 *
 *  Portability Issues:
 *      None.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "sha1.h"
#include "sds_lib.h"

/*
 *  Define patterns for testing
 */
#define TESTA   "abcabcabca"
#define TESTB_1 "abcdbcdecd"
#define TESTB_2 "hijkijkljk"
#define TESTB   TESTB_1 TESTB_2
#define TESTC   "a"
#define BILLION 1000000000L
#define MILLION 1000000uL

int main()
{
    //SHA1Context sha;
	/*unsigned Message_Digest[5];*/
    unsigned * Message_Digest = (unsigned *)sds_alloc( 5 * sizeof(unsigned) );
    int i;

    /*uint64_t diff;*/
    double diff;
    struct timespec start, end;

    /*
     *  Perform test A
     */

    /*clock_gettime(CLOCK_MONOTONIC, &start);*/

    printf("\nTest A: 'abcabcabcabcabcabcabcabc'\n");
    char testa[24] = "abcabcabcabcabcabcabcabc";

    int t;
    /*unsigned int tin[6] = {0};*/
    unsigned int *tin = (unsigned int*)sds_alloc( 6 * sizeof(int));
    for(t = 0; t < 6; t++)
    {
        tin[t]  = ( ( (unsigned) testa[t * 4]     ) & 0xFF ) << 24;
        tin[t] |= ( ( (unsigned) testa[t * 4 + 1] ) & 0xFF ) << 16;
        tin[t] |= ( ( (unsigned) testa[t * 4 + 2] ) & 0xFF ) << 8;
        tin[t] |= ( ( (unsigned) testa[t * 4 + 3] ) & 0xFF );
    }


    int j ;
    clock_gettime(CLOCK_REALTIME, &start);
    for (j= 0; j < 1000; ++j) 
      SHA1Input(Message_Digest, (const unsigned int *) tin);
    clock_gettime(CLOCK_REALTIME, &end);
    diff = (double)(end.tv_sec - start.tv_sec) + ((double)(end.tv_nsec)*1e-9 - (double)(start.tv_nsec)*1e-9);
    printf("1000 average: time elapsed: %.2g us\n", diff*1e3);

    /*diff = MILLION * float(end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;*/
    /*diff = (double)(end.tv_sec - start.tv_sec) + ((double)(end.tv_nsec)*1e-9 - (double)(start.tv_nsec)*1e-9);*/
    /*printf("time elapsed: %.2g us\n", diff*1e6);*/

    printf("\t");
    for(i = 0; i < 5 ; i++)
    {
        printf("%08X ", Message_Digest[i]);
    }
    printf("\n");
    printf("Should match:\n");
    printf("\t6CF5348C D191B888 73BEB636 6ECFE5A3 D3DE00DD\n");


    /*
     *  Perform test B
     */
    printf("\nTest B: 'hijkijkljklmklmnlmnomnop'\n");
    char testb[24] = "hijkijkljklmklmnlmnomnop";

    for(t = 0; t < 6; t++)
    {
        tin[t]  = ( ( (unsigned) testb[t * 4]     ) & 0xFF ) << 24;
        tin[t] |= ( ( (unsigned) testb[t * 4 + 1] ) & 0xFF ) << 16;
        tin[t] |= ( ( (unsigned) testb[t * 4 + 2] ) & 0xFF ) << 8;
        tin[t] |= ( ( (unsigned) testb[t * 4 + 3] ) & 0xFF );
    }

    /*clock_gettime(CLOCK_MONOTONIC, &start);*/
    /*SHA1Input(Message_Digest, (const unsigned int *) tin);*/
    /*clock_gettime(CLOCK_MONOTONIC, &end);*/

    /*[>diff = MILLION * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;<]*/
    /*diff = (double)(end.tv_sec - start.tv_sec) + ((double)(end.tv_nsec)*1e-9 - (double)(start.tv_nsec)*1e-9);*/
    /*printf("time elapsed: %.2g us\n", diff*1e6);*/


    clock_gettime(CLOCK_REALTIME, &start);
    int k;
    for (k= 0; k < 1000; ++k) 
      SHA1Input(Message_Digest, (const unsigned int *) tin);
    clock_gettime(CLOCK_REALTIME, &end);
    diff = (double)(end.tv_sec - start.tv_sec) + ((double)(end.tv_nsec)*1e-9 - (double)(start.tv_nsec)*1e-9);
    printf("1000 loop:time elapsed: %.2g us\n", diff*1e3);

    printf("\t");
    for(i = 0; i < 5 ; i++)
    {
        printf("%08X ", Message_Digest[i]);
    }
    printf("\n");
    printf("Should match:\n");
    printf("\t0442E003 8A4F749F 97D0A7AB F428D4CD 411AB3B7\n");

    /*
     *  Perform test C
     *
    printf("\nTest C: One million 'a' characters\n");

    SHA1Reset(&sha);
    for(i = 1; i <= 1000000; i++) {
        SHA1Input(&sha, (const unsigned char *) TESTC);
    }

    if (!SHA1Result(&sha))
    {
        fprintf(stderr, "ERROR-- could not compute message digest\n");
    }
    else
    {
        printf("\t");
        for(i = 0; i < 5 ; i++)
        {
            printf("%X ", sha.Message_Digest[i]);
        }
        printf("\n");
        printf("Should match:\n");
        printf("\t34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F\n");
    }
*/
    return 0;
}
