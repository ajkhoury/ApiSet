/**
 * API Set Lookup
 * Copyright (c) 2018-2019 Aidan Khoury. All rights reserved.
 *
 * @file apiset.c
 * @authors Aidan Khoury (ajkhoury)
 * @date 11/22/2018
 */

#include "apiset.h"
#include "ntrtl.h"

//
// ApiSet DLL prefixes.
//

#define API_SET_PREFIX_API_     (ULONGLONG)0x002D004900500041 /* L"api-" */
#define API_SET_PREFIX_EXT_     (ULONGLONG)0x002D005400580045 /* L"ext-" */
#define API_SET_DLL_EXTENSTION  (ULONGLONG)0x004C004C0044002E /* L".DLL" */

//
// Useful macros for ApiSet api.
//

#define API_SET_CHAR_TO_LOWER(c) \
    (((WCHAR)((c) - L'A') <= (L'a' - L'A' - 1)) ? ((c) + 0x20) : (c))


//
// API set schema version 6.
//

#define GET_API_SET_NAMESPACE_ENTRY_V6(ApiSetNamespace, Index) \
    ((PAPI_SET_NAMESPACE_ENTRY_V6)((ULONG_PTR)(ApiSetNamespace) + \
                                ((PAPI_SET_NAMESPACE_V6)(ApiSetNamespace))->EntryOffset + \
                                    ((Index) * sizeof(API_SET_NAMESPACE_ENTRY_V6))))

#define GET_API_SET_NAMESPACE_VALUE_ENTRY_V6(ApiSetNamespace, Entry, Index) \
    ((PAPI_SET_VALUE_ENTRY_V6)((ULONG_PTR)(ApiSetNamespace) + \
                                ((PAPI_SET_NAMESPACE_ENTRY_V6)(Entry))->ValueOffset + \
                                    ((Index) * sizeof(API_SET_VALUE_ENTRY_V6))))

#define GET_API_SET_NAMESPACE_ENTRY_NAME_V6(ApiSetNamespace, Entry) \
    ((PWCHAR)((ULONG_PTR)(ApiSetNamespace) + ((PAPI_SET_NAMESPACE_ENTRY_V6)(Entry))->NameOffset))

#define GET_API_SET_NAMESPACE_ENTRY_VALUE_V6(ApiSetNamespace, Entry) \
    ((PWCHAR)((ULONG_PTR)(ApiSetNamespace) + ((PAPI_SET_NAMESPACE_ENTRY_V6)(Entry))->ValueOffset))

#define GET_API_SET_VALUE_ENTRY_NAME_V6(ApiSetNamespace, Entry) \
    ((PWCHAR)((ULONG_PTR)(ApiSetNamespace) + ((PAPI_SET_VALUE_ENTRY_V6)(Entry))->NameOffset))

#define GET_API_SET_VALUE_ENTRY_VALUE_V6(ApiSetNamespace, Entry) \
    ((PWCHAR)((ULONG_PTR)(ApiSetNamespace) + ((PAPI_SET_VALUE_ENTRY_V6)(Entry))->ValueOffset))

#define GET_API_SET_HASH_ENTRY_V6(ApiSetNamespace, Middle) \
    ((PAPI_SET_HASH_ENTRY_V6)((ULONG_PTR)(ApiSetNamespace) + \
                            ((PAPI_SET_NAMESPACE_V6)(ApiSetNamespace))->HashOffset + \
                                ((Middle) * sizeof(API_SET_HASH_ENTRY_V6))))

static
PAPI_SET_NAMESPACE_ENTRY_V6
ApiSetpSearchForApiSetV6(
    _In_ PAPI_SET_NAMESPACE_V6 ApiSetNamespace,
    _In_ PWCHAR ApiSetNameToResolve,
    _In_ USHORT ApiSetNameToResolveLength
)
{
    WCHAR *pwc;
    USHORT Count;
    ULONG HashKey;
    LONG Low;
    LONG Middle;
    LONG High;
    PAPI_SET_HASH_ENTRY_V6 HashEntry;
    PAPI_SET_NAMESPACE_ENTRY_V6 FoundEntry;

    if (!ApiSetNameToResolveLength) {
        return NULL;
    }

    //
    // Calculate hash key for this ApiSet name.
    //
    HashKey = 0;
    pwc = ApiSetNameToResolve;
    Count = ApiSetNameToResolveLength;
    do {
        HashKey = HashKey * ApiSetNamespace->HashFactor + (USHORT)API_SET_CHAR_TO_LOWER(*pwc);
        ++pwc;
        --Count;
    } while (Count);

    //
    // Lookup the matching hash in the ApiSet namespace using a binary search.
    //
    FoundEntry = NULL;
    Low = 0;
    Middle = 0;
    High = (LONG)ApiSetNamespace->Count - 1;

    while (High >= Low) {
        Middle = (Low + High) >> 1;

        HashEntry = GET_API_SET_HASH_ENTRY_V6(ApiSetNamespace, Middle);

        if (HashKey < HashEntry->Hash) {
            High = Middle - 1;
        } else if (HashKey > HashEntry->Hash) {
            Low = Middle + 1;
        } else {
            //
            // Get the namespace entry from the hash entry index.
            //
            FoundEntry = GET_API_SET_NAMESPACE_ENTRY_V6(ApiSetNamespace, HashEntry->Index);
            break;
        }
    }

    //
    // If the high index is less than the low index, then a matching hash entry was not found.
    // Otherwise, get the found namespace entry.
    //
    if (High < Low) {
        return NULL;
    }

    //
    // Final check on apiset library name in order to make sure we didn't collide with
    // another hash bucket.
    //
    if (RtlCompareUnicodeStrings(ApiSetNameToResolve,
                                 ApiSetNameToResolveLength,
                                 GET_API_SET_NAMESPACE_ENTRY_NAME_V6(ApiSetNamespace, FoundEntry),
                                 FoundEntry->HashedLength / sizeof(WCHAR),
                                 TRUE) == 0) {
        return FoundEntry;
    }

    return NULL;
}

static
PAPI_SET_VALUE_ENTRY_V6
ApiSetpSearchForApiSetHostV6(
    _In_ PAPI_SET_NAMESPACE_ENTRY_V6 Entry,
    _In_ WCHAR *ApiSetNameToResolve,
    _In_ USHORT ApiSetNameToResolveLength,
    _In_ PAPI_SET_NAMESPACE_V6 ApiSetNamespace
)
{
    LONG Low;
    LONG Middle;
    LONG High;
    LONG Result;
    PAPI_SET_VALUE_ENTRY_V6 FoundEntry;
    PAPI_SET_VALUE_ENTRY_V6 ApiSetHostEntry;

    //
    // If there is no alias, don't bother checking each one.
    //
    FoundEntry = GET_API_SET_NAMESPACE_VALUE_ENTRY_V6(ApiSetNamespace, Entry, 0);

    High = (LONG)(Entry->ValueCount - 1);
    if (!High) {
        return FoundEntry;
    }

    Low = 1; // skip the first entry.

    while (Low <= High) {
        Middle = (Low + High) >> 1;

        ApiSetHostEntry = GET_API_SET_NAMESPACE_VALUE_ENTRY_V6(ApiSetNamespace, Entry, Middle);

        //
        // Compare API names.
        //
        Result = RtlCompareUnicodeStrings(ApiSetNameToResolve,
                                          ApiSetNameToResolveLength,
                                          GET_API_SET_VALUE_ENTRY_NAME_V6(ApiSetNamespace, ApiSetHostEntry),
                                          ApiSetHostEntry->NameLength / sizeof(WCHAR),
                                          TRUE);
        if (Result < 0) {
            High = Middle - 1;
        } else if (Result > 0) {
            Low = Middle + 1;
        } else {
            FoundEntry = GET_API_SET_NAMESPACE_VALUE_ENTRY_V6(ApiSetNamespace, Entry, Middle);
            break;
        }
    }

    return FoundEntry;
}

NTSTATUS
APISETAPI
ApiSetResolveToHostV6(
    _In_ PAPI_SET_NAMESPACE ApiSetNamespace,
    _In_ PCUNICODE_STRING ApiSetNameToResolve,
    _In_opt_ PCUNICODE_STRING ParentName,
    _Out_ PBOOLEAN Resolved,
    _Out_ PUNICODE_STRING Output
)
{
    NTSTATUS Status;
    BOOLEAN IsResolved;
    WCHAR *ApiSetNameBuffer;
    WCHAR *pwc;
    ULONG ApiSetNameBufferLength;
    USHORT ApiSetNameNoExtLength;
    PAPI_SET_NAMESPACE_ENTRY_V6 ResolvedNamespaceEntry;
    PAPI_SET_VALUE_ENTRY_V6 HostLibraryEntry;
    ULONGLONG ApiSetNameBufferPrefix;

    IsResolved = FALSE;
    RtlInitEmptyUnicodeString(Output, NULL, 0);

    //
    // Make sure the API Set name is a valid length.
    //
    if (ApiSetNameToResolve->Length < sizeof(API_SET_PREFIX_API_)) {
        goto Exit;
    }

    ApiSetNameBuffer = ApiSetNameToResolve->Buffer;

    //
    // Check library name starts with "api-" or "ext-"
    //
    ApiSetNameBufferPrefix = *(ULONGLONG*)ApiSetNameBuffer;
    ApiSetNameBufferPrefix &= ~(ULONGLONG)0x0000002000200020; // Trick to convert the chars to lowercase.
    if ((ApiSetNameBufferPrefix != API_SET_PREFIX_API_) &&
        (ApiSetNameBufferPrefix != API_SET_PREFIX_EXT_)) {
        goto Exit;
    }

    //
    // Compute word count of apiset library name without the dll suffix and anything
    // beyond the last hyphen. Example: 
    //     api-ms-win-core-apiquery-l1-1-0.dll -> wordlen(api-ms-win-core-apiquery-l1-1)
    //
    ApiSetNameBufferLength = (ULONG)ApiSetNameToResolve->Length;
    pwc = (WCHAR*)((ULONG_PTR)ApiSetNameBuffer + ApiSetNameBufferLength);
    do {
        if (ApiSetNameBufferLength <= 1)
            break;
        ApiSetNameBufferLength -= sizeof(WCHAR);
        --pwc;
    } while (*pwc != L'-');

    ApiSetNameNoExtLength = (USHORT)(ApiSetNameBufferLength / sizeof(WCHAR));
    if (!ApiSetNameNoExtLength) {
        goto Exit;
    }

    //
    // Hash table lookup.
    //
    ResolvedNamespaceEntry = ApiSetpSearchForApiSetV6((PAPI_SET_NAMESPACE_V6)ApiSetNamespace,
                                                      ApiSetNameBuffer,
                                                      ApiSetNameNoExtLength
                                                      );
    if (!ResolvedNamespaceEntry) {
        goto Exit;
    }

    //
    // Look for aliases in hosts libraries if necessary.
    //
    if (ResolvedNamespaceEntry->ValueCount > 1 && ParentName) {

        HostLibraryEntry = ApiSetpSearchForApiSetHostV6(ResolvedNamespaceEntry,
                                                        ParentName->Buffer,
                                                        ParentName->Length / sizeof(WCHAR),
                                                        (PAPI_SET_NAMESPACE_V6)ApiSetNamespace
                                                        );

    } else if (ResolvedNamespaceEntry->ValueCount > 0) {

        HostLibraryEntry = GET_API_SET_NAMESPACE_VALUE_ENTRY_V6(ApiSetNamespace,
                                                                ResolvedNamespaceEntry,
                                                                0);
    } else {
        goto Exit;
    }

    //
    // Output resolved host library.
    //
    Output->Length = (USHORT)HostLibraryEntry->ValueLength;
    Output->MaximumLength = Output->Length;
    Output->Buffer = GET_API_SET_VALUE_ENTRY_VALUE_V6(ApiSetNamespace, HostLibraryEntry);

    IsResolved = TRUE;

Exit:
    Status = STATUS_SUCCESS;
    *Resolved = IsResolved;

    return Status;
}



//
// API set schema version 4.
//

#define GET_API_SET_NAMESPACE_ENTRY_V4(ApiSetNamespace, Index) \
    ((PAPI_SET_NAMESPACE_ENTRY_V4)(((PAPI_SET_NAMESPACE_ARRAY_V4)(ApiSetNamespace))->Array + \
                                        Index))

#define GET_API_SET_NAMESPACE_ENTRY_NAME_V4(ApiSetNamespace, NamespaceEntry) \
    ((PWCHAR)((ULONG_PTR)(ApiSetNamespace) + \
                ((PAPI_SET_NAMESPACE_ENTRY_V4)(NamespaceEntry))->NameOffset))

#define GET_API_SET_NAMESPACE_ENTRY_DATA_V4(ApiSetNamespace, NamespaceEntry) \
    ((PAPI_SET_VALUE_ARRAY_V4)((ULONG_PTR)(ApiSetNamespace) + \
                                ((PAPI_SET_NAMESPACE_ENTRY_V4)(NamespaceEntry))->DataOffset))

#define GET_API_SET_VALUE_ENTRY_V4(ApiSetNamespace, ResolvedValueArray, Index) \
    ((PAPI_SET_VALUE_ENTRY_V4)(((PAPI_SET_VALUE_ARRAY_V4)(ResolvedValueArray))->Array + \
                                        Index))

#define GET_API_SET_VALUE_ENTRY_NAME_V4(ApiSetNamespace, ApiSetValueEntry) \
    ((WCHAR*)((ULONG_PTR)(ApiSetNamespace) + \
                ((PAPI_SET_VALUE_ENTRY_V4)(ApiSetValueEntry))->NameOffset))

#define GET_API_SET_VALUE_ENTRY_VALUE_V4(ApiSetNamespace, ApiSetValueEntry) \
    ((WCHAR*)((ULONG_PTR)(ApiSetNamespace) + \
                ((PAPI_SET_VALUE_ENTRY_V4)(ApiSetValueEntry))->ValueOffset))

static
PAPI_SET_NAMESPACE_ENTRY_V4
ApiSetpSearchForApiSetV4(
    _In_ PAPI_SET_NAMESPACE ApiSetNamespace,
    _In_ PWCHAR ApiSetNameToResolve,
    _In_ USHORT ApiSetNameToResolveLength
)
{
    LONG Low;
    LONG Middle;
    LONG High;
    LONG Result;
    PAPI_SET_NAMESPACE_ARRAY_V4 ApiSetNamespaceArray;
    PAPI_SET_NAMESPACE_ENTRY_V4 ApiSetNamespaceEntry;

    ApiSetNamespaceArray = (PAPI_SET_NAMESPACE_ARRAY_V4)ApiSetNamespace;

    Low = 0;
    High = (LONG)(ApiSetNamespaceArray->Count - 1);

    while (High >= Low) {
        Middle = (High + Low) >> 1;

        ApiSetNamespaceEntry = GET_API_SET_NAMESPACE_ENTRY_V4(ApiSetNamespace, Middle);

        Result = RtlCompareUnicodeStrings(ApiSetNameToResolve,
                                          ApiSetNameToResolveLength,
                                          GET_API_SET_NAMESPACE_ENTRY_NAME_V4(ApiSetNamespace, ApiSetNamespaceEntry),
                                          ApiSetNamespaceEntry->NameLength,
                                          TRUE
                                          );
        if (Result < 0) {
            High = Middle - 1;
        } else if (Result > 0) {
            Low = Middle + 1;
        } else {
            return ApiSetNamespaceEntry;
        }
    }

    return NULL;
}

static
PAPI_SET_VALUE_ENTRY_V4
ApiSetpSearchForApiSetHostV4(
    _In_ PAPI_SET_VALUE_ARRAY_V4 ApiSetValueArray,
    _In_ WCHAR *ApiSetNameToResolve,
    _In_ USHORT ApiSetNameToResolveLength,
    _In_ PAPI_SET_NAMESPACE_ARRAY_V4 ApiSetNamespace
)
{
    LONG Low;
    LONG Middle;
    LONG High;
    LONG Result;
    PAPI_SET_VALUE_ENTRY_V4 ApiSetHostEntry;

    Low = 1; // skip first entry.
    High = (LONG)(ApiSetValueArray->Count - 1);

    while (High >= Low) {
        Middle = (High + Low) >> 1;

        ApiSetHostEntry = GET_API_SET_VALUE_ENTRY_V4(ApiSetNamespace, ApiSetValueArray, Middle);

        Result = RtlCompareUnicodeStrings(ApiSetNameToResolve,
                                          ApiSetNameToResolveLength,
                                          GET_API_SET_VALUE_ENTRY_NAME_V4(ApiSetNamespace, ApiSetHostEntry),
                                          ApiSetHostEntry->NameLength,
                                          TRUE
                                          );
        if (Result < 0) {
            High = Middle - 1;
        } else if (Result > 0) {
            Low = Middle + 1;
        } else {
            return ApiSetHostEntry;
        }
    }

    return NULL;
}

NTSTATUS
APISETAPI
ApiSetResolveToHostV4(
    _In_ PAPI_SET_NAMESPACE ApiSetNamespace,
    _In_ PCUNICODE_STRING ApiSetNameToResolve,
    _In_opt_ PCUNICODE_STRING ParentName,
    _Out_ PBOOLEAN Resolved,
    _Out_ PUNICODE_STRING Output
)
{
    NTSTATUS Status;
    BOOLEAN IsResolved;
    ULONGLONG ApiSetNameBufferPrefix;
    PAPI_SET_NAMESPACE_ENTRY_V4 ResolvedNamespaceEntry;
    PAPI_SET_VALUE_ARRAY_V4 ResolvedValueArray;
    PAPI_SET_VALUE_ENTRY_V4 HostLibraryEntry;
    UNICODE_STRING ApiSetNameNoExtString;

    IsResolved = FALSE;
    RtlInitEmptyUnicodeString(Output, NULL, 0);

    //
    // Make sure the API Set name is a valid length.
    //
    if (ApiSetNameToResolve->Length < sizeof(API_SET_PREFIX_API_)) {
        goto Exit;
    }

    //
    // Check library name starts with "api-" or "ext-"
    //
    ApiSetNameBufferPrefix = *(ULONGLONG*)ApiSetNameToResolve->Buffer;
    ApiSetNameBufferPrefix &= ~(ULONGLONG)0x0000002000200020; // Trick to convert the chars to lowercase.
    if (ApiSetNameBufferPrefix != API_SET_PREFIX_API_ &&
        ApiSetNameBufferPrefix != API_SET_PREFIX_EXT_) {
        goto Exit;
    }

    //
    // Skip the prefix.
    //
    ApiSetNameNoExtString.Length = ApiSetNameToResolve->Length - sizeof(API_SET_PREFIX_API_);
    ApiSetNameNoExtString.MaximumLength = ApiSetNameNoExtString.Length;
    ApiSetNameNoExtString.Buffer = (WCHAR*)((ULONG_PTR)ApiSetNameToResolve->Buffer +
                                                            sizeof(API_SET_PREFIX_API_));

    //
    // Cut off the '.DLL' extension.
    //
    if (ApiSetNameNoExtString.Length >= sizeof(API_SET_DLL_EXTENSTION) &&
        ApiSetNameNoExtString.Buffer[(ApiSetNameNoExtString.Length -
                                      sizeof(API_SET_DLL_EXTENSTION)) / sizeof(WCHAR)] == L'.') {
        ApiSetNameNoExtString.Length -= sizeof(API_SET_DLL_EXTENSTION);
    }

    ResolvedNamespaceEntry = ApiSetpSearchForApiSetV4(ApiSetNamespace,
                                                      ApiSetNameNoExtString.Buffer,
                                                      ApiSetNameNoExtString.Length / sizeof(WCHAR)
                                                      );
    if (!ResolvedNamespaceEntry) {
        goto Exit;
    }

    //
    // Get the namspace value array.
    //
    ResolvedValueArray = GET_API_SET_NAMESPACE_ENTRY_DATA_V4(ApiSetNamespace,
                                                             ResolvedNamespaceEntry);

    //
    // Look for aliases in hosts libraries if necessary.
    //
    if (ResolvedValueArray->Count > 1 && ParentName) {

        HostLibraryEntry = ApiSetpSearchForApiSetHostV4(ResolvedValueArray,
                                                        ParentName->Buffer,
                                                        ParentName->Length / sizeof(WCHAR),
                                                        (PAPI_SET_NAMESPACE_ARRAY_V4)ApiSetNamespace
                                                        );

    } else if (ResolvedValueArray->Count > 0) {

        HostLibraryEntry = GET_API_SET_VALUE_ENTRY_V4(ApiSetNamespace, ResolvedValueArray, 0);

    } else {
        goto Exit;
    }

    Output->Length = (USHORT)HostLibraryEntry->ValueLength;
    Output->MaximumLength = Output->Length;
    Output->Buffer = GET_API_SET_VALUE_ENTRY_VALUE_V4(ApiSetNamespace, HostLibraryEntry);

    IsResolved = TRUE;

Exit:
    Status = STATUS_SUCCESS;
    *Resolved = IsResolved;

    return Status;
}



//
// API Set Schema Version 3
//

#define GET_API_SET_NAMESPACE_ENTRY_V3(ApiSetNamespace, Index) \
    ((PAPI_SET_NAMESPACE_ENTRY_V3)(((PAPI_SET_NAMESPACE_ARRAY_V3)(ApiSetNamespace))->Array + \
                                        Index))

#define GET_API_SET_NAMESPACE_ENTRY_NAME_V3(ApiSetNamespace, NamespaceEntry) \
    ((PWCHAR)((ULONG_PTR)(ApiSetNamespace) + \
                ((PAPI_SET_NAMESPACE_ENTRY_V3)(NamespaceEntry))->NameOffset))

#define GET_API_SET_NAMESPACE_ENTRY_DATA_V3(ApiSetNamespace, NamespaceEntry) \
    ((PAPI_SET_VALUE_ARRAY_V3)((ULONG_PTR)(ApiSetNamespace) + \
                                ((PAPI_SET_NAMESPACE_ENTRY_V3)(NamespaceEntry))->DataOffset))

#define GET_API_SET_VALUE_ENTRY_V3(ApiSetNamespace, ResolvedValueArray, Index) \
    ((PAPI_SET_VALUE_ENTRY_V3)(((PAPI_SET_VALUE_ARRAY_V3)(ResolvedValueArray))->Array + \
                                        Index))

#define GET_API_SET_VALUE_ENTRY_NAME_V3(ApiSetNamespace, ApiSetValueEntry) \
    ((WCHAR*)((ULONG_PTR)(ApiSetNamespace) + \
                ((PAPI_SET_VALUE_ENTRY_V3)(ApiSetValueEntry))->NameOffset))

#define GET_API_SET_VALUE_ENTRY_VALUE_V3(ApiSetNamespace, ApiSetValueEntry) \
    ((WCHAR*)((ULONG_PTR)(ApiSetNamespace) + \
                ((PAPI_SET_VALUE_ENTRY_V3)(ApiSetValueEntry))->ValueOffset))

static
PAPI_SET_VALUE_ENTRY_V3
ApiSetpSearchForApiSetHostV3(
    _In_ PAPI_SET_VALUE_ARRAY_V3 ApiSetValueArray,
    _In_ WCHAR *ApiSetNameToResolve,
    _In_ USHORT ApiSetNameToResolveLength,
    _In_ PAPI_SET_NAMESPACE_ARRAY_V3 ApiSetNamespace
)
{
    LONG Low;
    LONG Middle;
    LONG High;
    LONG Result;
    PAPI_SET_VALUE_ENTRY_V3 ApiSetValueEntry;

    Low = 1; // skip first entry.
    High = ApiSetValueArray->Count - 1;

    while (High >= Low) {
        Middle = (High + Low) >> 1;

        ApiSetValueEntry = GET_API_SET_VALUE_ENTRY_V3(ApiSetNamespace, ApiSetValueArray, Middle);

        Result = RtlCompareUnicodeStrings(ApiSetNameToResolve,
                                          ApiSetNameToResolveLength,
                                          GET_API_SET_VALUE_ENTRY_NAME_V3(ApiSetNamespace,
                                                                          ApiSetValueEntry),
                                          ApiSetValueEntry->NameLength,
                                          TRUE);
        if (Result < 0) {
            High = Middle - 1;
        } else if (Result > 0) {
            Low = Middle + 1;
        } else {
            return ApiSetValueEntry;
        }
    }

    return NULL;
}

NTSTATUS
APISETAPI
ApiSetResolveToHostV3(
    _In_ PAPI_SET_NAMESPACE ApiSetNamespace,
    _In_ PCUNICODE_STRING ApiSetNameToResolve,
    _In_opt_ PCUNICODE_STRING ParentName,
    _Out_ PBOOLEAN Resolved,
    _Out_ PUNICODE_STRING Output
)
{
    NTSTATUS Status;
    BOOLEAN IsResolved;
    ULONGLONG ApiSetNameBufferPrefix;
    LONG Low;
    LONG Middle;
    LONG High;
    LONG Result;
    PAPI_SET_NAMESPACE_ARRAY_V3 ApiSetNamespaceArray;
    PAPI_SET_NAMESPACE_ENTRY_V3 ResolvedNamespaceEntry;
    PAPI_SET_VALUE_ARRAY_V3 ResolvedValueArray;
    PAPI_SET_VALUE_ENTRY_V3 HostLibraryEntry;
    UNICODE_STRING ApiSetNameNoExtString;

    IsResolved = FALSE;
    RtlInitEmptyUnicodeString(Output, NULL, 0);

    //
    // Make sure the API Set name is a valid length.
    //
    if (ApiSetNameToResolve->Length < sizeof(API_SET_PREFIX_API_)) {
        goto Exit;
    }

    //
    // Check library name starts with "api-" or "ext-"
    //
    ApiSetNameBufferPrefix = *(ULONGLONG*)ApiSetNameToResolve->Buffer;
    ApiSetNameBufferPrefix &= ~(ULONGLONG)0x0000002000200020; // Trick to convert the chars to lowercase.
    if (ApiSetNameBufferPrefix != API_SET_PREFIX_API_ &&
        ApiSetNameBufferPrefix != API_SET_PREFIX_EXT_) {
        goto Exit;
    }

    //
    // Skip the prefix.
    //
    ApiSetNameNoExtString.Length = ApiSetNameToResolve->Length - sizeof(API_SET_PREFIX_API_);
    ApiSetNameNoExtString.MaximumLength = ApiSetNameNoExtString.Length;
    ApiSetNameNoExtString.Buffer = (WCHAR*)((ULONG_PTR)ApiSetNameToResolve->Buffer +
                                                            sizeof(API_SET_PREFIX_API_));

    //
    // Cut off the '.DLL' extension.
    //
    if (ApiSetNameNoExtString.Length >= sizeof(API_SET_DLL_EXTENSTION) &&
        ApiSetNameNoExtString.Buffer[(ApiSetNameNoExtString.Length -
                                      sizeof(API_SET_DLL_EXTENSTION)) / sizeof(WCHAR)] == L'.') {
        ApiSetNameNoExtString.Length -= sizeof(API_SET_DLL_EXTENSTION);
    }

    ApiSetNamespaceArray = (PAPI_SET_NAMESPACE_ARRAY_V3)ApiSetNamespace;
    ResolvedNamespaceEntry = NULL;

    Low = 0;
    High = (LONG)(ApiSetNamespaceArray->Count - 1);

    while (High >= Low) {
        Middle = (Low + High) >> 1;

        ResolvedNamespaceEntry = GET_API_SET_NAMESPACE_ENTRY_V3(ApiSetNamespace, Middle);

        Result = RtlCompareUnicodeStrings(ApiSetNameNoExtString.Buffer,
                                          ApiSetNameNoExtString.Length / sizeof(WCHAR),
                                          GET_API_SET_NAMESPACE_ENTRY_NAME_V3(ApiSetNamespace,
                                                                              ResolvedNamespaceEntry),
                                          ResolvedNamespaceEntry->NameLength / sizeof(WCHAR),
                                          TRUE
                                          );
        if (Result < 0) {
            High = Middle - 1;
        } else if (Result > 0) {
            Low = Middle + 1;
        } else {
            break;
        }
    }

    //
    // If the high index is less than the low index, then a matching namespace
    // entry was not found.
    //
    if (High < Low) {
        goto Exit;
    }

    //
    // Get the namspace value array.
    //
    ResolvedValueArray = GET_API_SET_NAMESPACE_ENTRY_DATA_V3(ApiSetNamespace, ResolvedNamespaceEntry);

    //
    // Look for aliases in hosts libraries if necessary.
    //
    if (ResolvedValueArray->Count > 1 && ParentName) {

        HostLibraryEntry = ApiSetpSearchForApiSetHostV3(ResolvedValueArray,
                                                        ParentName->Buffer,
                                                        ParentName->Length / sizeof(WCHAR),
                                                        (PAPI_SET_NAMESPACE_ARRAY_V3)ApiSetNamespace
                                                        );
    } else {
        HostLibraryEntry = NULL;
    }

    //
    // Default to the first value entry.
    //
    if (!HostLibraryEntry) {
        HostLibraryEntry = GET_API_SET_VALUE_ENTRY_V3(ApiSetNamespace, ResolvedValueArray, 0);
    }

    //
    // Output resolved host library.
    //
    Output->Length = (USHORT)HostLibraryEntry->ValueLength;
    Output->MaximumLength = Output->Length;
    Output->Buffer = GET_API_SET_VALUE_ENTRY_VALUE_V3(ApiSetNamespace, HostLibraryEntry);

    IsResolved = TRUE;

Exit:
    Status = STATUS_SUCCESS;
    *Resolved = IsResolved;

    return Status;
}



//
// API Set Schema Version 2
//

#define GET_API_SET_NAMESPACE_ENTRY_V2(ApiSetNamespace, Index) \
    ((PAPI_SET_NAMESPACE_ENTRY_V2)((ULONG_PTR)(ApiSetNamespace) + \
                                    ((PAPI_SET_NAMESPACE_ARRAY_V2)(ApiSetNamespace))->Array + \
                                        Index))

static
PAPI_SET_VALUE_ENTRY_V2
ApiSetpSearchForApiSetHostV2(
    _In_ PAPI_SET_VALUE_ARRAY_V2 ApiSetValueArray,
    _In_ PCUNICODE_STRING ApiToResolve,
    _In_ PAPI_SET_NAMESPACE ApiSetNamespace
)
{
    LONG Low;
    LONG Middle;
    LONG High;
    LONG Result;
    UNICODE_STRING ApiSetHostString;
    PAPI_SET_VALUE_ENTRY_V2 ApiSetValueEntry;

    Low = 1; // skip first entry.
    High = ApiSetValueArray->Count - 1;

    while (High >= Low) {
        Middle = (High + Low) >> 1;

        ApiSetValueEntry = &ApiSetValueArray->Array[Middle];
        ApiSetHostString.Length = (USHORT)ApiSetValueEntry->NameLength;
        ApiSetHostString.MaximumLength = ApiSetHostString.Length;
        ApiSetHostString.Buffer = (WCHAR*)((ULONG_PTR)ApiSetNamespace + ApiSetValueEntry->NameOffset);

        Result = RtlCompareUnicodeString(ApiToResolve, &ApiSetHostString, TRUE);

        if (Result < 0) {
            High = Middle - 1;
        } else if (Result > 0) {
            Low = Middle + 1;
        } else {
            return ApiSetValueEntry;
        }
    }

    return NULL;
}

NTSTATUS
APISETAPI
ApiSetResolveToHostV2(
    _In_ PAPI_SET_NAMESPACE ApiSetNamespace,
    _In_ PCUNICODE_STRING ApiSetNameToResolve,
    _In_opt_ PCUNICODE_STRING ParentName,
    _Out_ PBOOLEAN Resolved,
    _Out_ PUNICODE_STRING Output
)
{
    NTSTATUS Status;
    BOOLEAN IsResolved;
    ULONGLONG ApiSetNameBufferPrefix;
    LONG Low;
    LONG Middle;
    LONG High;
    LONG Result;
    PAPI_SET_NAMESPACE_ARRAY_V2 ApiSetNamespaceArray;
    PAPI_SET_NAMESPACE_ENTRY_V2 ApiSetNamespaceEntry;
    PAPI_SET_VALUE_ARRAY_V2 ApiSetValueArray;
    PAPI_SET_VALUE_ENTRY_V2 HostLibraryEntry;
    UNICODE_STRING ApiSetNamespaceString;
    UNICODE_STRING ApiSetNameNoExtString;

    IsResolved = FALSE;
    RtlInitEmptyUnicodeString(Output, NULL, 0);

    //
    // Make sure the API Set name is a valid length.
    //
    if (ApiSetNameToResolve->Length < sizeof(API_SET_PREFIX_API_)) {
        goto Exit;
    }

    //
    // Check library name starts with "api-"
    //
    ApiSetNameBufferPrefix = *(ULONGLONG*)ApiSetNameToResolve->Buffer;
    ApiSetNameBufferPrefix &= ~(ULONGLONG)0x0000002000200020; // Trick to convert the chars to lowercase.
    if (ApiSetNameBufferPrefix != API_SET_PREFIX_API_) {
        goto Exit;
    }

    //
    // Skip the prefix.
    //
    ApiSetNameNoExtString.Length = ApiSetNameToResolve->Length - sizeof(API_SET_PREFIX_API_);
    ApiSetNameNoExtString.MaximumLength = ApiSetNameNoExtString.Length;
    ApiSetNameNoExtString.Buffer = (WCHAR*)((ULONG_PTR)ApiSetNameToResolve->Buffer +
                                                                sizeof(API_SET_PREFIX_API_));

    //
    // Cut off the '.DLL' extension.
    //
    if (ApiSetNameNoExtString.Length >= sizeof(API_SET_DLL_EXTENSTION) &&
        ApiSetNameNoExtString.Buffer[(ApiSetNameNoExtString.Length -
                                      sizeof(API_SET_DLL_EXTENSTION)) / sizeof(WCHAR)] == L'.') {
        ApiSetNameNoExtString.Length -= sizeof(API_SET_DLL_EXTENSTION);
    }

    ApiSetNamespaceArray = (PAPI_SET_NAMESPACE_ARRAY_V2)ApiSetNamespace;
    ApiSetNamespaceEntry = NULL;

    Low = 0;
    High = (LONG)(ApiSetNamespaceArray->Count - 1);

    while (High >= Low) {
        Middle = (Low + High) >> 1;

        ApiSetNamespaceEntry = GET_API_SET_NAMESPACE_ENTRY_V2(ApiSetNamespace, Middle);
        ApiSetNamespaceString.Length = (USHORT)ApiSetNamespaceEntry->NameLength;
        ApiSetNamespaceString.MaximumLength = ApiSetNamespaceString.Length;
        ApiSetNamespaceString.Buffer = (WCHAR*)((ULONG_PTR)ApiSetNamespace +
                                                ApiSetNamespaceEntry->NameOffset);

        Result = RtlCompareUnicodeString(&ApiSetNameNoExtString, &ApiSetNamespaceString, TRUE);

        if (Result < 0) {
            High = Middle - 1;
        } else if (Result > 0) {
            Low = Middle + 1;
        } else {
            break;
        }
    }

    //
    // If the high index is less than the low index, then a matching namespace
    // entry was not found.
    //
    if (High < Low) {
        goto Exit;
    }

    //
    // Get the namspace value array.
    //
    ApiSetValueArray = (PAPI_SET_VALUE_ARRAY_V2)((ULONG_PTR)ApiSetNamespace +
                                                            ApiSetNamespaceEntry->DataOffset);

    //
    // Look for aliases in hosts libraries if necessary.
    //
    if (ApiSetValueArray->Count > 1 && ParentName) {

        HostLibraryEntry = ApiSetpSearchForApiSetHostV2(ApiSetValueArray,
                                                        ParentName,
                                                        ApiSetNamespace
                                                        );
    } else {
        HostLibraryEntry = NULL;
    }

    //
    // Default to the first value entry.
    //
    if (!HostLibraryEntry) {
        HostLibraryEntry = ApiSetValueArray->Array;
    }

    //
    // Output resolved host library.
    //
    Output->Length = (USHORT)HostLibraryEntry->ValueLength;
    Output->MaximumLength = Output->Length;
    Output->Buffer = (WCHAR*)((ULONG_PTR)ApiSetNamespace + HostLibraryEntry->ValueOffset);

    IsResolved = TRUE;

Exit:
    Status = STATUS_SUCCESS;
    *Resolved = IsResolved;

    return Status;
}
