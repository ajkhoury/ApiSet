/**
 * API Set Lookup
 * Copyright (c) 2018-2019 Aidan Khoury. All rights reserved.
 *
 * @file resolve.c
 * @authors Aidan Khoury (ajkhoury)
 * @date 11/22/2018
 */

#include "apiset.h"

#include "ntrtl.h"

static
NTSTATUS
ApiSetpResolve(
    _In_ HANDLE Process,
    _In_ PCUNICODE_STRING Name,
    _In_opt_ PCUNICODE_STRING BaseName,
    _Out_ PUNICODE_STRING ResolvedName
)
{
    NTSTATUS Status;
    PROCESS_BASIC_INFORMATION BasicInfo;
    ULONG ReturnLength;
    PPEB Peb;
    PVOID PebWow64;
    BOOLEAN Resolved;
    PAPI_SET_NAMESPACE ApiSetMap;

    //
    // Retrieve PEB address for given process.
    //
    Status = NtQueryInformationProcess(Process,
                                       ProcessBasicInformation,
                                       &BasicInfo,
                                       sizeof(BasicInfo),
                                       &ReturnLength);
    if (!NT_SUCCESS(Status)) {
        return Status;
    }

    Peb = (PPEB)BasicInfo.PebBaseAddress;

    Status = NtQueryInformationProcess(Process,
                                       ProcessWow64Information,
                                       &PebWow64,
                                       sizeof(PebWow64),
                                       &ReturnLength);
    if (!NT_SUCCESS(Status)) {
        return Status;
    }

    if (PebWow64 != NULL) {
        ApiSetMap = (PAPI_SET_NAMESPACE)(ULONG_PTR)((PPEB32)PebWow64)->ApiSetMap;
    } else {
        ApiSetMap = (PAPI_SET_NAMESPACE)Peb->ApiSetMap;
    }

    if (!ApiSetMap) {
        return STATUS_NOT_FOUND;
    }

    switch (ApiSetMap->Version) {

        //
        // API set schema version 2
        //
    case API_SET_SCHEMA_VERSION_V2:
        Status = ApiSetResolveToHostV2(ApiSetMap, Name, BaseName, &Resolved, ResolvedName);
        if (NT_SUCCESS(Status) && !Resolved) {
            Status = STATUS_NOT_FOUND;
        }
        break;

        //
        // API set schema version 3
        //
    case API_SET_SCHEMA_VERSION_V3:
        Status = ApiSetResolveToHostV3(ApiSetMap, Name, BaseName, &Resolved, ResolvedName);
        if (NT_SUCCESS(Status) && !Resolved) {
            Status = STATUS_NOT_FOUND;
        }
        break;

        //
        // API set schema version 4
        //
    case API_SET_SCHEMA_VERSION_V4:
        Status = ApiSetResolveToHostV4(ApiSetMap, Name, BaseName, &Resolved, ResolvedName);
        if (NT_SUCCESS(Status) && !Resolved) {
            Status = STATUS_NOT_FOUND;
        }
        break;

        //
        // API set schema version 6
        //
    case API_SET_SCHEMA_VERSION_V6:
        Status = ApiSetResolveToHostV6(ApiSetMap, Name, BaseName, &Resolved, ResolvedName);
        if (NT_SUCCESS(Status) && !Resolved) {
            Status = STATUS_NOT_FOUND;
        }
        break;

    default:
        Status = STATUS_NOT_SUPPORTED;
        break;
    }

    return Status;
}

BOOLEAN
APISETAPI
ApiSetResolve(
    _In_ PWCHAR ApiSetName,
    _Out_ PUNICODE_STRING ResolvedHostLibrary
)
{
    UNICODE_STRING ApiToResolve;
    RtlInitUnicodeString(&ApiToResolve, ApiSetName);

    NTSTATUS Status = ApiSetpResolve(GetCurrentProcess(),
                                     &ApiToResolve,
                                     NULL,
                                     ResolvedHostLibrary
                                     );
    if (NT_SUCCESS(Status)) {
        return TRUE;
    }

    return FALSE;
}
