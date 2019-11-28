#include "ntrtl.h"

/**
 * The RtlInitUnicodeString function initializes an NT counted
 * unicode string. The DestinationString is initialized to point to
 * the SourceString and the Length and MaximumLength fields of
 * DestinationString are initialized to the length of the SourceString,
 * which is zero if SourceString is not specified.
 *
 * @param[out] DestinationString Pointer to the counted string to initialize.
 * @param[in] SourceString       Optional pointer to a null terminated unicode
 *                               string that the counted string is to point to.
 */
VOID
NTAPI
RtlInitUnicodeString(
    _Out_ PUNICODE_STRING DestinationString,
    _In_opt_z_ PCWSTR SourceString
)
{
    SIZE_T Length;

    DestinationString->MaximumLength = 0;
    DestinationString->Length = 0;
    DestinationString->Buffer = (PWCH)SourceString;

    if (ARGUMENT_PRESENT(SourceString)) {
        Length = wcslen(SourceString) * sizeof(WCHAR);
        if (Length >= MAX_USTRING) {
            Length = MAX_USTRING - sizeof(UNICODE_NULL);
        }

        DestinationString->Length = (USHORT)Length;
        DestinationString->MaximumLength = (USHORT)(Length + sizeof(UNICODE_NULL));
    }

    return;
}
