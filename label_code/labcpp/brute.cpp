#if _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define  _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

//#define USE_PRIME
#define USE_CHAINING
//#define STORE_32

#define _CRT_SECURE_NO_DEPRECATE
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <intrin.h>
#if _MSC_VER
#include <nmmintrin.h>
#endif


#define NUM_OF(A) (sizeof(A)/sizeof((A)[0]))
#ifndef _MSC_VER
#define _rotl(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#define _rotr(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#define __forceinline inline
#endif



UINT HashFletcher(const CHAR * key, SIZE_T len)
{
	const USHORT * data = (const USHORT *)key;
	len /= 2;
	UINT32 sum1 = 0xFFFF, sum2 = 0xFFFF;
	while (len) {
		SIZE_T tlen = len > 360 ? 360 : len;
		len -= tlen;
		do {
			sum1 += *data++;
			sum2 += sum1;
		} while (--tlen);
		sum1 = (sum1 & 0xffff) + (sum1 >> 16);
		sum2 = (sum2 & 0xffff) + (sum2 >> 16);
	}
	/* Second reduction step to reduce sums to 16 bits */
	sum1 = (sum1 & 0xffff) + (sum1 >> 16);
	sum2 = (sum2 & 0xffff) + (sum2 >> 16);
	return sum2 << 16 | sum1;
}