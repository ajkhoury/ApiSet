#include "ntrtl.h"

/**
 * Compares two counted Unicode strings. The return value indicates if the
 * strings are equal or String1 is less than String2 or String1 is greater
 * than String2.
 *
 * The CaseInSensitive parameter specifies if case is to be ignored when
 * doing the comparison.
 *
 * @param[in] String1           Pointer to the first string.
 * @param[in] Length1           Length of the first string.
 * @param[in] String2           Pointer to the second string.
 * @param[in] Length2           Length of the second string.
 * @param[in] CaseInSensitive   If TRUE, case should be ignored when doing
 *                              the comparison.
 *
 * @return  Signed value that gives the results of the comparison:
 *                Zero - String1 equals String2
 *              < Zero - String1 less than String2
 *              > Zero - String1 greater than String2
 */
LONG
NTAPI
RtlCompareUnicodeStrings(
    IN CONST WCHAR* String1,
    IN SIZE_T Length1,
    IN CONST WCHAR* String2,
    IN SIZE_T Length2,
    IN BOOLEAN CaseInSensitive
)
{
    CONST WCHAR* s1, * s2, * Limit;
    LONG n1, n2;
    UINT32 c1, c2;

    if (Length1 > LONG_MAX || Length2 > LONG_MAX) {
        return STATUS_INVALID_BUFFER_SIZE;
    }

    s1 = String1;
    s2 = String2;
    n1 = (LONG)Length1;
    n2 = (LONG)Length2;

    Limit = (WCHAR*)((CHAR*)s1 + (n1 <= n2 ? n1 : n2));
    if (CaseInSensitive) {
        while (s1 < Limit) {
            c1 = *s1;
            c2 = *s2;
            if (c1 != c2) {

                //
                // Note that this needs to reference the translation table!
                //
                c1 = RTL_UPCASE(c1);
                c2 = RTL_UPCASE(c2);
                if (c1 != c2) {
                    return (INT32)(c1)-(INT32)(c2);
                }
            }
            s1 += 1;
            s2 += 1;
        }

    } else {

        while (s1 < Limit) {
            c1 = *s1;
            c2 = *s2;
            if (c1 != c2) {
                return (LONG)(c1)-(LONG)(c2);
            }
            s1 += 1;
            s2 += 1;
        }
    }

    return n1 - n2;
}