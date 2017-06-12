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

/*
 *  Define patterns for testing
 */
#define TESTA   "abcabcabca"
#define TESTB_1 "abcdbcdecd"
#define TESTB_2 "hijkijkljk"
#define TESTB   TESTB_1 TESTB_2
#define TESTC   "a"
#define BILLION 1000000000L

int main()
{
    //SHA1Context sha;
	unsigned Message_Digest[5];
    int i;

    uint64_t diff;
    struct timespec start, end;

    /*
     *  Perform test A
     */

    clock_gettime(CLOCK_MONOTONIC, &start);

    printf("\nTest A: 'abcabcabcabcabcabcabcabc'\n");
    char testa[24] = "abcabcabcabcabcabcabcabc";

    int t;
    unsigned int tin[6] = {0};
    for(t = 0; t < 6; t++)
    {
        tin[t]  = ( ( (unsigned) testa[t * 4]     ) & 0xFF ) << 24;
        tin[t] |= ( ( (unsigned) testa[t * 4 + 1] ) & 0xFF ) << 16;
        tin[t] |= ( ( (unsigned) testa[t * 4 + 2] ) & 0xFF ) << 8;
        tin[t] |= ( ( (unsigned) testa[t * 4 + 3] ) & 0xFF );
    }

    SHA1Input(Message_Digest, (const unsigned int *) tin);

    clock_gettime(CLOCK_MONOTONIC, &end);

    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("time elapsed: %llu ns\n", (long long unsigned) diff);
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

    SHA1Input(Message_Digest, (const unsigned int *) tin);

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
