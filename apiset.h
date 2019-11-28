/**
 * API Set Lookup
 * Copyright (c) 2018-2019 Aidan Khoury. All rights reserved.
 *
 * @file apiset.h
 * @author Aidan Khoury (ajkhoury)
 * @date 11/22/2018
 */

#ifndef _API_SET_H_
#define _API_SET_H_
#if defined(_MSC_VER)
#pragma once
#endif

#include "ntapi.h"

// API Set calling convention
#define APISETAPI NTAPI


//
// API schema definitions.
//

#define API_SET_SCHEMA_VERSION_V2       0x00000002
#define API_SET_SCHEMA_VERSION_V3       0x00000003 // No offline support.
#define API_SET_SCHEMA_VERSION_V4       0x00000004
#define API_SET_SCHEMA_VERSION_V6       0x00000006


//
// API Set data structures
//

typedef struct _API_SET_NAMESPACE {
    ULONG Version;
} API_SET_NAMESPACE, *PAPI_SET_NAMESPACE;


//
// API set schema version 6.
//

typedef struct _API_SET_NAMESPACE_V6 {
    ULONG Version;
    ULONG Size;
    ULONG Flags;
    ULONG Count;
    ULONG EntryOffset;  // API_SET_NAMESPACE_ENTRY_V6
    ULONG HashOffset;   // API_SET_NAMESPACE_HASH_ENTRY_V6
    ULONG HashFactor;
} API_SET_NAMESPACE_V6, *PAPI_SET_NAMESPACE_V6;

typedef struct _API_SET_NAMESPACE_ENTRY_V6 {
    ULONG Flags;
    ULONG NameOffset;
    ULONG NameLength;
    ULONG HashedLength;
    ULONG ValueOffset;
    ULONG ValueCount;
} API_SET_NAMESPACE_ENTRY_V6, *PAPI_SET_NAMESPACE_ENTRY_V6;

typedef struct _API_SET_HASH_ENTRY_V6 {
    ULONG Hash;
    ULONG Index;
} API_SET_HASH_ENTRY_V6, *PAPI_SET_HASH_ENTRY_V6;

typedef struct _API_SET_VALUE_ENTRY_V6 {
    ULONG Flags;
    ULONG NameOffset;
    ULONG NameLength;
    ULONG ValueOffset;
    ULONG ValueLength;
} API_SET_VALUE_ENTRY_V6, *PAPI_SET_VALUE_ENTRY_V6; 

typedef const API_SET_VALUE_ENTRY_V6 *PCAPI_SET_VALUE_ENTRY_V6;
typedef const API_SET_HASH_ENTRY_V6 *PCAPI_SET_HASH_ENTRY_V6;
typedef const API_SET_NAMESPACE_ENTRY_V6 *PCAPI_SET_NAMESPACE_ENTRY_V6;
typedef const API_SET_NAMESPACE_V6 *PCAPI_SET_NAMESPACE_V6;


//
// API set schema version 4.
//

typedef struct _API_SET_VALUE_ENTRY_V4 {
    ULONG Flags;        // 0x00
    ULONG NameOffset;   // 0x04
    ULONG NameLength;   // 0x08
    ULONG ValueOffset;  // 0x0C
    ULONG ValueLength;  // 0x10
} API_SET_VALUE_ENTRY_V4, *PAPI_SET_VALUE_ENTRY_V4;

typedef struct _API_SET_VALUE_ARRAY_V4 {
    ULONG Flags;        // 0x00
    ULONG Count;        // 0x04
    API_SET_VALUE_ENTRY_V4 Array[ANYSIZE_ARRAY];
} API_SET_VALUE_ARRAY_V4, *PAPI_SET_VALUE_ARRAY_V4;

typedef struct _API_SET_NAMESPACE_ENTRY_V4 {
    ULONG Flags;
    ULONG NameOffset;
    ULONG NameLength;
    ULONG AliasOffset;
    ULONG AliasLength;
    ULONG DataOffset;   // API_SET_VALUE_ARRAY_V4
} API_SET_NAMESPACE_ENTRY_V4, *PAPI_SET_NAMESPACE_ENTRY_V4;

typedef struct _API_SET_NAMESPACE_ARRAY_V4 {
    ULONG Version;      // 0x00
    ULONG Size;         // 0x04
    ULONG Flags;        // 0x08
    ULONG Count;        // 0x0C
    API_SET_NAMESPACE_ENTRY_V4 Array[ANYSIZE_ARRAY];
} API_SET_NAMESPACE_ARRAY_V4, *PAPI_SET_NAMESPACE_ARRAY_V4;

typedef const API_SET_VALUE_ENTRY_V4 *PCAPI_SET_VALUE_ENTRY_V4;
typedef const API_SET_VALUE_ARRAY_V4 *PCAPI_SET_VALUE_ARRAY_V4;
typedef const API_SET_NAMESPACE_ENTRY_V4 *PCAPI_SET_NAMESPACE_ENTRY_V4;
typedef const API_SET_NAMESPACE_ARRAY_V4 *PCAPI_SET_NAMESPACE_ARRAY_V4;

#define API_SET_SCHEMA_FLAGS_SEALED              0x00000001
#define API_SET_SCHEMA_FLAGS_HOST_EXTENSION      0x00000002

#define API_SET_SCHEMA_ENTRY_FLAGS_SEALED        0x00000001
#define API_SET_SCHEMA_ENTRY_FLAGS_EXTENSION     0x00000002

//
// API set schema version 3.
//

typedef struct _API_SET_VALUE_ENTRY_V3 {
    ULONG NameOffset;
    ULONG NameLength;
    ULONG ValueOffset;
    ULONG ValueLength;
} API_SET_VALUE_ENTRY_V3, *PAPI_SET_VALUE_ENTRY_V3;

typedef struct _API_SET_VALUE_ARRAY_V3 {
    ULONG Count;
    API_SET_VALUE_ENTRY_V3 Array[ANYSIZE_ARRAY];
} API_SET_VALUE_ARRAY_V3, *PAPI_SET_VALUE_ARRAY_V3;

typedef struct _API_SET_NAMESPACE_ENTRY_V3 {
    ULONG NameOffset;
    ULONG NameLength;
    ULONG DataOffset;   // API_SET_VALUE_ARRAY_V3
} API_SET_NAMESPACE_ENTRY_V3, *PAPI_SET_NAMESPACE_ENTRY_V3;

typedef struct _API_SET_NAMESPACE_ARRAY_V3 {
    ULONG Version;
    ULONG Count;
    API_SET_NAMESPACE_ENTRY_V3 Array[ANYSIZE_ARRAY];
} API_SET_NAMESPACE_ARRAY_V3, *PAPI_SET_NAMESPACE_ARRAY_V3;

typedef const API_SET_VALUE_ENTRY_V3 *PCAPI_SET_VALUE_ENTRY_V3;
typedef const API_SET_VALUE_ARRAY_V3 *PCAPI_SET_VALUE_ARRAY_V3;
typedef const API_SET_NAMESPACE_ENTRY_V3 *PCAPI_SET_NAMESPACE_ENTRY_V3;
typedef const API_SET_NAMESPACE_ARRAY_V3 *PCAPI_SET_NAMESPACE_ARRAY_V3;

//
// Support for downlevel API set schema version 2.
//

typedef struct _API_SET_VALUE_ENTRY_V2 {
    ULONG NameOffset;
    ULONG NameLength;
    ULONG ValueOffset;
    ULONG ValueLength;
} API_SET_VALUE_ENTRY_V2, *PAPI_SET_VALUE_ENTRY_V2;

typedef struct _API_SET_VALUE_ARRAY_V2 {
    ULONG Count;
    API_SET_VALUE_ENTRY_V2 Array[ANYSIZE_ARRAY];
} API_SET_VALUE_ARRAY_V2, *PAPI_SET_VALUE_ARRAY_V2;

typedef struct _API_SET_NAMESPACE_ENTRY_V2 {
    ULONG NameOffset;
    ULONG NameLength;
    ULONG DataOffset;   // API_SET_VALUE_ARRAY_V2
} API_SET_NAMESPACE_ENTRY_V2, *PAPI_SET_NAMESPACE_ENTRY_V2;

typedef struct _API_SET_NAMESPACE_ARRAY_V2 {
    ULONG Version;
    ULONG Count;
    API_SET_NAMESPACE_ENTRY_V2 Array[ANYSIZE_ARRAY];
} API_SET_NAMESPACE_ARRAY_V2, *PAPI_SET_NAMESPACE_ARRAY_V2;

typedef const API_SET_VALUE_ENTRY_V2 *PCAPI_SET_VALUE_ENTRY_V2;
typedef const API_SET_VALUE_ARRAY_V2 *PCAPI_SET_VALUE_ARRAY_V2;
typedef const API_SET_NAMESPACE_ENTRY_V2 *PCAPI_SET_NAMESPACE_ENTRY_V2;
typedef const API_SET_NAMESPACE_ARRAY_V2 *PCAPI_SET_NAMESPACE_ARRAY_V2;


//
// API Set Routines
//

NTSTATUS
APISETAPI
ApiSetResolveToHostV6(
    _In_ PAPI_SET_NAMESPACE ApiSetNamespace,
    _In_ PCUNICODE_STRING ApiSetNameToResolve,
    _In_opt_ PCUNICODE_STRING ParentName,
    _Out_ PBOOLEAN Resolved,
    _Out_ PUNICODE_STRING Output
    );

NTSTATUS
APISETAPI
ApiSetResolveToHostV4(
    _In_ PAPI_SET_NAMESPACE ApiSetNamespace,
    _In_ PCUNICODE_STRING ApiSetNameToResolve,
    _In_opt_ PCUNICODE_STRING ParentName,
    _Out_ PBOOLEAN Resolved,
    _Out_ PUNICODE_STRING Output
    );

NTSTATUS
APISETAPI
ApiSetResolveToHostV3(
    _In_ PAPI_SET_NAMESPACE ApiSetNamespace,
    _In_ PCUNICODE_STRING ApiSetNameToResolve,
    _In_opt_ PCUNICODE_STRING ParentName,
    _Out_ PBOOLEAN Resolved,
    _Out_ PUNICODE_STRING Output
    );

NTSTATUS
APISETAPI
ApiSetResolveToHostV2(
    _In_ PAPI_SET_NAMESPACE ApiSetNamespace,
    _In_ PCUNICODE_STRING ApiSetNameToResolve,
    _In_opt_ PCUNICODE_STRING ParentName,
    _Out_ PBOOLEAN Resolved,
    _Out_ PUNICODE_STRING Output
    );

BOOLEAN
APISETAPI
ApiSetResolve(
    _In_ PWCHAR ApiSetName,
    _Out_ PUNICODE_STRING ResolvedHostLibrary
    );

#endif // _ODIN_API_SET_H_