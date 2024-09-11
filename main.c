/**
 * API Set Lookup
 * Copyright (c) 2018-2019 Aidan Khoury. All rights reserved.
 *
 * @file apiset.c
 * @authors Aidan Khoury (ajkhoury)
 *          lucasg
 * @date 11/22/2018
 */

#include "apiset.h"

#include <stdio.h>

void help()
{
    wprintf(L"ApiSet : resolve api set host library\n");
    wprintf(L"Usage:\n    apiset ext-some-api-set-library-l1-1-0.dll [base_dll_name]\n");
}

int wmain(int argc, wchar_t* argv[])
{
    PWCHAR ApiSetName;
    PWCHAR BaseDllName;
    UNICODE_STRING HostApi;
    WCHAR HostLibraryName[MAX_PATH];

    if (argc < 2) {
        help();
        return -1;
    }

    if (wcscmp(argv[1], L"-h") == 0 ||
        wcscmp(argv[1], L"/?") == 0 ||
        wcscmp(argv[1], L"-help") == 0 ||
        wcscmp(argv[1], L"--help") == 0) {
        help();
        return 0;
    }

    //
    // Process arguments.
    //
    ApiSetName = argv[1];

    if (argc > 2) {
        BaseDllName = argv[2];
    } else {
        BaseDllName = NULL;
    }

    //
    // Attempt to resolve API Set library.
    //
    if (!ApiSetResolve(ApiSetName, BaseDllName, &HostApi)) {
        wprintf(L"[x] Could not resolve Api set library : %s\n", ApiSetName);
        return -1;
    }

    //
    // Output the resolved host library.
    //
    if (wcsncpy_s(HostLibraryName, RTL_NUMBER_OF(HostLibraryName), HostApi.Buffer, HostApi.Length)) {
        wprintf(L"[x] Could not copy resolved host library name\n");
        return -1;
    }
    HostLibraryName[HostApi.Length / sizeof(WCHAR)] = '\0';

    wprintf(L"[!] Api set library resolved : %s -> %s\n", ApiSetName, HostLibraryName);

    return 0;
}
