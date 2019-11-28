#ifndef _NTAPI_
#define _NTAPI_

#include <windows.h>
#include <sal.h>

#include "ntstatus.h"

//
// Counted String
//

typedef USHORT RTL_STRING_LENGTH_TYPE;

typedef struct _STRING {
    USHORT Length;
    USHORT MaximumLength;
#ifdef MIDL_PASS
    [size_is(MaximumLength), length_is(Length)]
#endif // MIDL_PASS
    _Field_size_bytes_part_opt_(MaximumLength, Length) PCHAR Buffer;
} STRING;
typedef STRING* PSTRING;
typedef STRING ANSI_STRING;
typedef PSTRING PANSI_STRING;

// end_sdfwdm
// end_wudfwdm

typedef STRING OEM_STRING;
typedef PSTRING POEM_STRING;
typedef CONST STRING* PCOEM_STRING;

//
// CONSTCounted String
//

typedef struct _CSTRING {
    USHORT Length;
    USHORT MaximumLength;
    CONST char* Buffer;
} CSTRING;
typedef CSTRING* PCSTRING;
#ifndef ANSI_NULL
#define ANSI_NULL ((CHAR)0)
#endif

// begin_wudfwdm
// begin_sdfwdm

typedef STRING CANSI_STRING;
typedef PSTRING PCANSI_STRING;

//
// Unicode strings are counted 16-bit character strings. If they are
// NULL terminated, Length does not include trailing NULL.
//

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
#ifdef MIDL_PASS
    [size_is(MaximumLength / 2), length_is((Length) / 2)] USHORT* Buffer;
#else // MIDL_PASS
    _Field_size_bytes_part_opt_(MaximumLength, Length) PWCH   Buffer;
#endif // MIDL_PASS
} UNICODE_STRING;
typedef UNICODE_STRING* PUNICODE_STRING;
typedef const UNICODE_STRING* PCUNICODE_STRING;

#ifndef UNICODE_NULL
#define UNICODE_NULL ((WCHAR)0)
#endif

#if _WIN32_WINNT >= 0x0500

#ifndef UNICODE_STRING_MAX_BYTES
#define UNICODE_STRING_MAX_BYTES ((USHORT) 65534) // winnt
#endif
#ifndef UNICODE_STRING_MAX_CHARS
#define UNICODE_STRING_MAX_CHARS (32767) // winnt
#endif

#define DECLARE_CONST_UNICODE_STRING(_var, _string) \
const WCHAR _var ## _buffer[] = _string; \
__pragma(warning(push)) \
__pragma(warning(disable:4221)) __pragma(warning(disable:4204)) \
const UNICODE_STRING _var = { sizeof(_string) - sizeof(WCHAR), sizeof(_string), (PWCH) _var ## _buffer } \
__pragma(warning(pop))

#define DECLARE_GLOBAL_CONST_UNICODE_STRING(_var, _str) \
extern const __declspec(selectany) UNICODE_STRING _var = RTL_CONSTANT_STRING(_str)

#define DECLARE_UNICODE_STRING_SIZE(_var, _size) \
WCHAR _var ## _buffer[_size]; \
__pragma(warning(push)) \
__pragma(warning(disable:4221)) __pragma(warning(disable:4204)) \
UNICODE_STRING _var = { 0, (_size) * sizeof(WCHAR) , _var ## _buffer } \
__pragma(warning(pop))

#endif // _WIN32_WINNT >= 0x0500

//
// This is the maximum MaximumLength for a UNICODE_STRING.
//
#ifndef MAX_USTRING
#define MAX_USTRING ( sizeof(WCHAR) * (MAXUSHORT/sizeof(WCHAR)) )
#endif


//
// Balanced tree node (AVL or RB) structure definition.
//
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4214)
#endif
typedef struct _RTL_BALANCED_NODE {
    union {
        struct _RTL_BALANCED_NODE* Children[2];
        struct {
            struct _RTL_BALANCED_NODE* Left;
            struct _RTL_BALANCED_NODE* Right;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

#define RTL_BALANCED_NODE_RESERVED_PARENT_MASK 3

    union {
        UCHAR Red : 1;
        UCHAR Balance : 2;
        ULONG_PTR ParentValue;
    } DUMMYUNIONNAME2;
} RTL_BALANCED_NODE, * PRTL_BALANCED_NODE;
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#define RTL_BALANCED_NODE_GET_PARENT_POINTER(Node) \
    ((PRTL_BALANCED_NODE)((Node)->ParentValue & \
                          ~RTL_BALANCED_NODE_RESERVED_PARENT_MASK))


typedef struct _STRING32 {
    USHORT   Length;
    USHORT   MaximumLength;
    ULONG  Buffer;
} STRING32;
typedef STRING32* PSTRING32;

typedef STRING32 UNICODE_STRING32;
typedef UNICODE_STRING32* PUNICODE_STRING32;

typedef STRING32 ANSI_STRING32;
typedef ANSI_STRING32* PANSI_STRING32;


typedef struct _STRING64 {
    USHORT   Length;
    USHORT   MaximumLength;
    ULONGLONG  Buffer;
} STRING64;
typedef STRING64* PSTRING64;

typedef STRING64 UNICODE_STRING64;
typedef UNICODE_STRING64* PUNICODE_STRING64;

typedef STRING64 ANSI_STRING64;
typedef ANSI_STRING64* PANSI_STRING64;

//
// Valid values for the Attributes field
//

#ifndef OBJ_INHERIT
#define OBJ_INHERIT                         0x00000002L
#endif
#ifndef OBJ_PERMANENT
#define OBJ_PERMANENT                       0x00000010L
#endif
#ifndef OBJ_EXCLUSIVE
#define OBJ_EXCLUSIVE                       0x00000020L
#endif
#ifndef OBJ_CASE_INSENSITIVE
#define OBJ_CASE_INSENSITIVE                0x00000040L
#endif
#ifndef OBJ_OPENIF
#define OBJ_OPENIF                          0x00000080L
#endif
#ifndef OBJ_OPENLINK
#define OBJ_OPENLINK                        0x00000100L
#endif
#ifndef OBJ_KERNEL_HANDLE
#define OBJ_KERNEL_HANDLE                   0x00000200L
#endif
#ifndef OBJ_FORCE_ACCESS_CHECK
#define OBJ_FORCE_ACCESS_CHECK              0x00000400L
#endif
#ifndef OBJ_IGNORE_IMPERSONATED_DEVICEMAP
#define OBJ_IGNORE_IMPERSONATED_DEVICEMAP   0x00000800L
#endif
#ifndef OBJ_DONT_REPARSE
#define OBJ_DONT_REPARSE                    0x00001000L
#endif
#ifndef OBJ_VALID_ATTRIBUTES
#define OBJ_VALID_ATTRIBUTES                0x00001FF2L
#endif

//
// Object Attributes structure
//

typedef struct _OBJECT_ATTRIBUTES64 {
    ULONG Length;
    ULONG64 RootDirectory;
    ULONG64 ObjectName;
    ULONG Attributes;
    ULONG64 SecurityDescriptor;
    ULONG64 SecurityQualityOfService;
} OBJECT_ATTRIBUTES64;
typedef OBJECT_ATTRIBUTES64* POBJECT_ATTRIBUTES64;
typedef CONST OBJECT_ATTRIBUTES64* PCOBJECT_ATTRIBUTES64;

typedef struct _OBJECT_ATTRIBUTES32 {
    ULONG Length;
    ULONG RootDirectory;
    ULONG ObjectName;
    ULONG Attributes;
    ULONG SecurityDescriptor;
    ULONG SecurityQualityOfService;
} OBJECT_ATTRIBUTES32;
typedef OBJECT_ATTRIBUTES32* POBJECT_ATTRIBUTES32;
typedef CONST OBJECT_ATTRIBUTES32* PCOBJECT_ATTRIBUTES32;


typedef struct _OBJECT_ATTRIBUTES {
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
    PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES* POBJECT_ATTRIBUTES;
typedef CONST OBJECT_ATTRIBUTES* PCOBJECT_ATTRIBUTES;

//++
//
// VOID
// InitializeObjectAttributes(
//     _Out_ POBJECT_ATTRIBUTES p,
//     _In_ PUNICODE_STRING n,
//     _In_ ULONG a,
//     _In_ HANDLE r,
//     _In_ PSECURITY_DESCRIPTOR s
//     )
//
//--

#define InitializeObjectAttributes( p, n, a, r, s ) { \
    (p)->Length = sizeof( OBJECT_ATTRIBUTES );          \
    (p)->RootDirectory = r;                             \
    (p)->Attributes = a;                                \
    (p)->ObjectName = n;                                \
    (p)->SecurityDescriptor = s;                        \
    (p)->SecurityQualityOfService = NULL;               \
    }


// RTL_ to avoid collisions in the global namespace.
// I don't believe there are possible/likely constant RootDirectory
// or SecurityDescriptor values other than NULL, so they are hardcoded.
// As well, the string will generally be const, so we cast that away.
#define RTL_CONSTANT_OBJECT_ATTRIBUTES(n, a) \
    { sizeof(OBJECT_ATTRIBUTES), NULL, RTL_CONST_CAST(PUNICODE_STRING)(n), a, NULL, NULL }

// This synonym is more appropriate for initializing what isn't actually const.
#define RTL_INIT_OBJECT_ATTRIBUTES(n, a) RTL_CONSTANT_OBJECT_ATTRIBUTES(n, a)


#include <guiddef.h>

#ifndef __OBJECTID_DEFINED
#define __OBJECTID_DEFINED

typedef struct  _OBJECTID {     // size is 20
    GUID Lineage;
    ULONG Uniquifier;
} OBJECTID;
#endif // !_OBJECTID_DEFINED

#ifndef MINCHAR
#define MINCHAR     0x80
#endif
#ifndef MAXCHAR
#define MAXCHAR     0x7f
#endif
#ifndef MINSHORT
#define MINSHORT    0x8000
#endif
#ifndef MAXSHORT
#define MAXSHORT    0x7fff
#endif
#ifndef MINLONG
#define MINLONG     0x80000000
#endif
#ifndef MAXLONG
#define MAXLONG     0x7fffffff
#endif
#ifndef MAXUCHAR
#define MAXUCHAR    0xff
#endif
#ifndef MAXUSHORT
#define MAXUSHORT   0xffff
#endif
#ifndef MAXULONG
#define MAXULONG    0xffffffff
#endif

//
// Determine if an argument is present by testing the value of the pointer
// to the argument value.
//

#ifndef ARGUMENT_PRESENT
#define ARGUMENT_PRESENT(ArgumentPointer)    (\
    (CHAR *)((ULONG_PTR)(ArgumentPointer)) != (CHAR *)(NULL) )
#endif


#define LOW_PRIORITY 0              // Lowest thread priority level
#define LOW_REALTIME_PRIORITY 16    // Lowest realtime priority level
#define HIGH_PRIORITY 31            // Highest thread priority level
#define MAXIMUM_PRIORITY 32         // Number of thread priority levels

#define MAXIMUM_WAIT_OBJECTS 64     // Maximum number of wait objects

#define MAXIMUM_SUSPEND_COUNT MAXCHAR // Maximum times thread can be suspended

//
// Event type
//

typedef enum _EVENT_TYPE {
    NotificationEvent,
    SynchronizationEvent
} EVENT_TYPE;

//
// Timer type
//

typedef enum _TIMER_TYPE {
    NotificationTimer,
    SynchronizationTimer
} TIMER_TYPE;

//
// Wait type
//

typedef enum _WAIT_TYPE {
    WaitAll,
    WaitAny,
    WaitNotification,
    WaitDequeue
} WAIT_TYPE;

//
// Processor modes.
//

typedef enum _MODE {
    KernelMode,
    UserMode,
    MaximumMode
} MODE;

typedef INT8 KPROCESSOR_MODE;

//
// Define system time structure.
//

typedef struct _KSYSTEM_TIME {
    ULONG LowPart;
    LONG High1Time;
    LONG High2Time;
} KSYSTEM_TIME, * PKSYSTEM_TIME;


//
// Thread priority
//

typedef LONG KPRIORITY;

//
// Spin Lock
//

typedef ULONG_PTR KSPIN_LOCK;
typedef KSPIN_LOCK* PKSPIN_LOCK;

//
// Update Sequence Number
//

typedef LONGLONG USN;


//
// Client ID
//

typedef struct _CLIENT_ID {
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID;
typedef CLIENT_ID* PCLIENT_ID;


#ifndef _PHYSICAL_ADDRESS_T
#define _PHYSICAL_ADDRESS_T

//
// Physical address.
//

typedef LARGE_INTEGER PHYSICAL_ADDRESS, * PPHYSICAL_ADDRESS;

#endif // _PHYSICAL_ADDRESS_T


//
// Profile source types
//

typedef enum _KPROFILE_SOURCE {
    ProfileTime,
    ProfileAlignmentFixup,
    ProfileTotalIssues,
    ProfilePipelineDry,
    ProfileLoadInstructions,
    ProfilePipelineFrozen,
    ProfileBranchInstructions,
    ProfileTotalNonissues,
    ProfileDcacheMisses,
    ProfileIcacheMisses,
    ProfileCacheMisses,
    ProfileBranchMispredictions,
    ProfileStoreInstructions,
    ProfileFpInstructions,
    ProfileIntegerInstructions,
    Profile2Issue,
    Profile3Issue,
    Profile4Issue,
    ProfileSpecialInstructions,
    ProfileTotalCycles,
    ProfileIcacheIssues,
    ProfileDcacheAccesses,
    ProfileMemoryBarrierCycles,
    ProfileLoadLinkedIssues,
    ProfileMaximum
} KPROFILE_SOURCE;

#include "ntpsapi.h"

#endif // _NTAPI_
