//
// Declarations of PEB and TEB, and some types contained in them.
//
// Address the maintenance problem that resulted from PEB and TEB being
// defined three times, once "native" in ntpsapi.w, and twice, 32bit and 64bit
// in wow64t.w.
//

//
// This file deliberately lacks #pragma once or #ifndef guards.
// It is only included by ntpsapi.h and wow64t.h and ntapi.h, never directly.
//

//
// This file is #included three times.
//
// 1) by ntpsapi.h, with no "unusual" macros defined, to declare
//    PEB and TEB, and some types contained in them
// 2) by wow64t.h to declare PEB32 and TEB32, and some types contained in them
// 3) by wow64t.h to declare PEB64 and TEB64, and some types contained in them
//
// wow64t.h #defines the macro PEBTEB_BITS to guide the declarations.
//

#define PEBTEB_PRIVATE_PASTE(x, y)       x##y
#define PEBTEB_PASTE(x, y)               PEBTEB_PRIVATE_PASTE(x,y)

#if defined(PEBTEB_BITS) /* This is defined by wow64t.h. */

#if PEBTEB_BITS == 32

#define PEBTEB_STRUCT(x)    PEBTEB_PASTE(x, 32) /* FOO32 */
#define PEBTEB_POINTER(x)   TYPE32(x) /* ULONG, defined in wow64t.h */

#elif PEBTEB_BITS == 64

#define PEBTEB_STRUCT(x)    PEBTEB_PASTE(x, 64) /* FOO64 */
#define PEBTEB_POINTER(x)   TYPE64(x) /* ULONG64, defined in wow64t.h */

#else

#error Unknown value for pebteb_bits (PEBTEB_BITS).

#endif

#else

//
// Declare and use regular native types.
//
#define PEBTEB_POINTER(x) x
#define PEBTEB_STRUCT(x)  x

#endif


typedef struct PEBTEB_STRUCT(_PEB_LDR_DATA) {
    ULONG Length;
    BOOLEAN Initialized;
    ULONG SsHandle;
    PEBTEB_STRUCT(LIST_ENTRY) InLoadOrderModuleList;
    PEBTEB_STRUCT(LIST_ENTRY) InMemoryOrderModuleList;
    PEBTEB_STRUCT(LIST_ENTRY) InInitializationOrderModuleList;
    ULONG EntryInProgress;
    BOOLEAN ShutdownInProgress;
    ULONG ShutdownThreadId;
} PEBTEB_STRUCT(PEB_LDR_DATA), *PEBTEB_STRUCT(PPEB_LDR_DATA);


/* for searching
typedef struct _PEB
typedef struct _PEB32
typedef struct _PEB64
*/
typedef struct PEBTEB_STRUCT(_PEB) {
    BOOLEAN InheritedAddressSpace;      // These four fields cannot change unless the
    BOOLEAN ReadImageFileExecOptions;   // ..
    BOOLEAN BeingDebugged;              // ..
    union {
        BOOLEAN BitField;               // ..
        struct {
            BOOLEAN ImageUsesLargePages : 1;
            BOOLEAN IsProtectedProcess : 1;
            BOOLEAN IsImageDynamicallyRelocated : 1;
            BOOLEAN SkipPatchingUser32Forwarders : 1;
            BOOLEAN IsPackagedProcess : 1;
            BOOLEAN IsAppContainer : 1;
            BOOLEAN IsProtectedProcessLight : 1;
            BOOLEAN IsLongPathAwareProcess : 1;
        };
    };

    PEBTEB_POINTER(HANDLE) Mutant;      // INITIAL_PEB structure is also updated.

    PEBTEB_POINTER(PVOID) ImageBaseAddress;
    PEBTEB_POINTER(PPEB_LDR_DATA) Ldr;
    PEBTEB_POINTER(struct _RTL_USER_PROCESS_PARAMETERS*)ProcessParameters;
    PEBTEB_POINTER(PVOID) SubSystemData;
    PEBTEB_POINTER(PVOID) ProcessHeap;
    PEBTEB_POINTER(struct _RTL_CRITICAL_SECTION*)FastPebLock;
    PEBTEB_POINTER(PVOID) IFEOKey;
    PEBTEB_POINTER(PVOID) AtlThunkSListPtr; // Used only for AMD64 PSLIST_HEADER
    union {
        ULONG CrossProcessFlags;
        struct {
            ULONG ProcessInJob : 1;
            ULONG ProcessInitializing : 1;
            ULONG ProcessUsingVEH : 1;
            ULONG ProcessUsingVCH : 1;
            ULONG ProcessUsingFTH : 1;
            ULONG ProcessPreviouslyThrottled : 1;
            ULONG ProcessCurrentlyThrottled : 1;
            ULONG ReservedBits0 : 25;
        };
    };
    union {
        PEBTEB_POINTER(PVOID) KernelCallbackTable;
        PEBTEB_POINTER(PVOID) UserSharedInfoPtr;
    };
    ULONG SystemReserved[1];
    ULONG AtlThunkSListPtr32;
    PEBTEB_POINTER(PVOID) ApiSetMap; // PAPI_SET_NAMESPACE
    ULONG TlsExpansionCounter;
    PEBTEB_POINTER(PVOID) TlsBitmap;
    ULONG TlsBitmapBits[2]; // TLS_MINIMUM_AVAILABLE bits
    PEBTEB_POINTER(PVOID) ReadOnlySharedMemoryBase;
    PEBTEB_POINTER(PVOID) SharedData; // HotpatchInformation
    PEBTEB_POINTER(PPVOID) ReadOnlyStaticServerData;
    PEBTEB_POINTER(PVOID) AnsiCodePageData; // PCPTABLEINFO
    PEBTEB_POINTER(PVOID) OemCodePageData; // PCPTABLEINFO
    PEBTEB_POINTER(PVOID) UnicodeCaseTableData; // PNLSTABLEINFO

    //
    // Useful information for LdrpInitialize
    ULONG NumberOfProcessors;
    ULONG NtGlobalFlag;

    //
    // Passed up from MmCreatePeb from Session Manager registry key
    //

    LARGE_INTEGER CriticalSectionTimeout;
    PEBTEB_POINTER(SIZE_T) HeapSegmentReserve;
    PEBTEB_POINTER(SIZE_T) HeapSegmentCommit;
    PEBTEB_POINTER(SIZE_T) HeapDeCommitTotalFreeThreshold;
    PEBTEB_POINTER(SIZE_T) HeapDeCommitFreeBlockThreshold;

    //
    // Where heap manager keeps track of all heaps created for a process
    // Fields initialized by MmCreatePeb.  ProcessHeaps is initialized
    // to point to the first free byte after the PEB and MaximumNumberOfHeaps
    // is computed from the page size used to hold the PEB, less the fixed
    // size of this data structure.
    //

    ULONG NumberOfHeaps;
    ULONG MaximumNumberOfHeaps;
    PEBTEB_POINTER(PPVOID) ProcessHeaps; // PHEAP*

    //
    //
    PEBTEB_POINTER(PVOID) GdiSharedHandleTable;
    PEBTEB_POINTER(PVOID) ProcessStarterHelper;
    ULONG GdiDCAttributeList;
    PEBTEB_POINTER(struct _RTL_CRITICAL_SECTION*)LoaderLock;

    //
    // Following fields filled in by MmCreatePeb from system values and/or
    // image header.
    //

    ULONG OSMajorVersion;
    ULONG OSMinorVersion;
    USHORT OSBuildNumber;
    USHORT OSCSDVersion;
    ULONG OSPlatformId;
    ULONG ImageSubsystem;
    ULONG ImageSubsystemMajorVersion;
    ULONG ImageSubsystemMinorVersion;
    PEBTEB_POINTER(UINT_PTR) ActiveProcessAffinityMask;
    PEBTEB_STRUCT(GDI_HANDLE_BUFFER) GdiHandleBuffer;
    PEBTEB_POINTER(PPS_POST_PROCESS_INIT_ROUTINE) PostProcessInitRoutine;

    PEBTEB_POINTER(PVOID) TlsExpansionBitmap;
    ULONG TlsExpansionBitmapBits[32]; // TLS_EXPANSION_SLOTS bits

    //
    // Id of the Hydra session in which this process is running
    //
    ULONG SessionId;

    //
    // Filled in by LdrpInstallAppcompatBackend
    //
    ULARGE_INTEGER AppCompatFlags;

    //
    // ntuser appcompat flags
    //
    ULARGE_INTEGER AppCompatFlagsUser;

    //
    // Filled in by LdrpInstallAppcompatBackend
    //
    PEBTEB_POINTER(PVOID) pShimData;

    //
    // Filled in by LdrQueryImageFileExecutionOptions
    //
    PEBTEB_POINTER(PVOID) AppCompatInfo; // APPCOMPAT_EXE_DATA

    //
    // Used by GetVersionExW as the szCSDVersion string
    //
    PEBTEB_STRUCT(UNICODE_STRING) CSDVersion;

    //
    // Fusion stuff
    //
    PEBTEB_POINTER(const struct _ACTIVATION_CONTEXT_DATA *)ActivationContextData; // ACTIVATION_CONTEXT_DATA
    PEBTEB_POINTER(struct _ASSEMBLY_STORAGE_MAP *)ProcessAssemblyStorageMap; // ASSEMBLY_STORAGE_MAP
    PEBTEB_POINTER(const struct _ACTIVATION_CONTEXT_DATA *)SystemDefaultActivationContextData; // ACTIVATION_CONTEXT_DATA
    PEBTEB_POINTER(struct _ASSEMBLY_STORAGE_MAP *)SystemAssemblyStorageMap; // ASSEMBLY_STORAGE_MAP

    //
    // Enforced minimum initial commit stack
    //
    PEBTEB_POINTER(SIZE_T) MinimumStackCommit;

    //
    // Fiber local storage.
    //

    PEBTEB_POINTER(PPVOID) FlsCallback;
    PEBTEB_STRUCT(LIST_ENTRY) FlsListHead;
    PEBTEB_POINTER(PVOID) FlsBitmap;
    ULONG FlsBitmapBits[FLS_MAXIMUM_AVAILABLE / (sizeof(ULONG) * 8)];
    ULONG FlsHighIndex;

    PEBTEB_POINTER(PVOID) WerRegistrationData;
    PEBTEB_POINTER(PVOID) WerShipAssertPtr;
    PEBTEB_POINTER(PVOID) pUnused; // pContextData
    PEBTEB_POINTER(PVOID) pImageHeaderHash;

    union {
        ULONG TracingFlags;
        struct {
            ULONG HeapTracingEnabled : 1;
            ULONG CritSecTracingEnabled : 1;
            ULONG LibLoaderTracingEnabled : 1;
            ULONG SpareTracingBits : 29;
        };
    };

    ULONG64 CsrServerReadOnlySharedMemoryBase;

    PEBTEB_POINTER(struct _RTL_CRITICAL_SECTION*)TppWorkerpListLock;
    PEBTEB_STRUCT(LIST_ENTRY) TppWorkerpList;

    PEBTEB_POINTER(PVOID) WaitOnAddressHashTable[128];

    // winver >= rs3
    PEBTEB_POINTER(PVOID) TelemetryCoverageHeader;
    ULONG CloudFileFlags;

    // winver >= rs4
    ULONG CloudFileDiagFlags;

    CHAR PlaceholderCompatibilityMode;
    CHAR PlaceholderCompatibilityModeReserved[7];

} PEBTEB_STRUCT(PEB), *PEBTEB_STRUCT(PPEB);


typedef struct PEBTEB_STRUCT(_RTL_ACTIVATION_CONTEXT_STACK_FRAME) {
//  PEBTEB_POINTER(SIZE_T) Size;                                                // -0x10
//  ULONG Format;                                                              // -0x08
    PEBTEB_POINTER(struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME *)Previous;     //  0x00
    PEBTEB_POINTER(struct _ACTIVATION_CONTEXT *)ActivationContext;           // +0x08
    ULONG Flags;                                                               // +0x10
} PEBTEB_STRUCT(RTL_ACTIVATION_CONTEXT_STACK_FRAME),
    *PEBTEB_STRUCT(PRTL_ACTIVATION_CONTEXT_STACK_FRAME);

typedef struct PEBTEB_STRUCT(_RTL_ACTIVATION_CONTEXT_STACK_FRAME_EXTENDED) {
//  PEBTEB_POINTER(SIZE_T) Size;                                                // -0x10
//  ULONG Format;                                                              // -0x08
    PEBTEB_POINTER(struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME *)Previous;     //  0x00
    PEBTEB_POINTER(struct _ACTIVATION_CONTEXT *)ActivationContext;           // +0x08
    ULONG Flags;                                                               // +0x10
    PEBTEB_POINTER(SIZE_T) Extra1;                                            // +0x18
    PEBTEB_POINTER(SIZE_T) Extra2;                                            // +0x20
    PEBTEB_POINTER(SIZE_T) Extra3;                                            // +0x28
    PEBTEB_POINTER(SIZE_T) Extra4;                                            // +0x30
} PEBTEB_STRUCT(RTL_ACTIVATION_CONTEXT_STACK_FRAME_EXTENDED),
    *PEBTEB_STRUCT(PRTL_ACTIVATION_CONTEXT_STACK_FRAME_EXTENDED);

typedef struct PEBTEB_STRUCT(_ACTIVATION_CONTEXT_STACK) {
    PEBTEB_POINTER(struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME *)ActiveFrame;
    PEBTEB_STRUCT(LIST_ENTRY) FrameListCache;
    ULONG Flags;
    ULONG NextCookieSequenceNumber;
    ULONG StackId;
} PEBTEB_STRUCT(ACTIVATION_CONTEXT_STACK),
    *PEBTEB_STRUCT(PACTIVATION_CONTEXT_STACK);

typedef const PEBTEB_STRUCT(ACTIVATION_CONTEXT_STACK) *PEBTEB_STRUCT(PCACTIVATION_CONTEXT_STACK);

#define TEB_ACTIVE_FRAME_CONTEXT_FLAG_EXTENDED (0x00000001)

typedef struct PEBTEB_STRUCT(_TEB_ACTIVE_FRAME_CONTEXT) {
    ULONG Flags;
    PEBTEB_POINTER(CHAR*)FrameName;
} PEBTEB_STRUCT(TEB_ACTIVE_FRAME_CONTEXT),
    *PEBTEB_STRUCT(PTEB_ACTIVE_FRAME_CONTEXT);

typedef const PEBTEB_STRUCT(TEB_ACTIVE_FRAME_CONTEXT) *PEBTEB_STRUCT(PCTEB_ACTIVE_FRAME_CONTEXT);

typedef struct PEBTEB_STRUCT(_TEB_ACTIVE_FRAME_CONTEXT_EX) {
    PEBTEB_STRUCT(TEB_ACTIVE_FRAME_CONTEXT) BasicContext;
    PEBTEB_POINTER(const CHAR*)SourceLocation; // e.g. "Z:\foo\bar\baz.c"
} PEBTEB_STRUCT(TEB_ACTIVE_FRAME_CONTEXT_EX),
    *PEBTEB_STRUCT(PTEB_ACTIVE_FRAME_CONTEXT_EX);

typedef const PEBTEB_STRUCT(TEB_ACTIVE_FRAME_CONTEXT_EX) *PEBTEB_STRUCT(
    PCTEB_ACTIVE_FRAME_CONTEXT_EX);

#define TEB_ACTIVE_FRAME_FLAG_EXTENDED (0x00000001)

typedef struct PEBTEB_STRUCT(_TEB_ACTIVE_FRAME) {
    ULONG Flags;
    PEBTEB_POINTER(struct _TEB_ACTIVE_FRAME*)Previous;
    PEBTEB_POINTER(PCTEB_ACTIVE_FRAME_CONTEXT) Context;
} PEBTEB_STRUCT(TEB_ACTIVE_FRAME),
    *PEBTEB_STRUCT(PTEB_ACTIVE_FRAME);

typedef const PEBTEB_STRUCT(TEB_ACTIVE_FRAME) *PEBTEB_STRUCT(PCTEB_ACTIVE_FRAME);

typedef struct PEBTEB_STRUCT(_TEB_ACTIVE_FRAME_EX) {
    PEBTEB_STRUCT(TEB_ACTIVE_FRAME) BasicFrame;
    PEBTEB_POINTER(PVOID) ExtensionIdentifier; // use address of your DLL Main or something unique to
    // your mapping in the address space
} PEBTEB_STRUCT(TEB_ACTIVE_FRAME_EX),
    *PEBTEB_STRUCT(PTEB_ACTIVE_FRAME_EX);

typedef const PEBTEB_STRUCT(TEB_ACTIVE_FRAME_EX) *PEBTEB_STRUCT(PCTEB_ACTIVE_FRAME_EX);


/* for searching
typedef struct _TEB
typedef struct _TEB32
typedef struct _TEB64
*/
typedef struct PEBTEB_STRUCT(_TEB) {
    PEBTEB_STRUCT(NT_TIB) NtTib;
    PEBTEB_POINTER(PVOID) EnvironmentPointer;
    PEBTEB_STRUCT(CLIENT_ID) ClientId;
    PEBTEB_POINTER(PVOID) ActiveRpcHandle;
    PEBTEB_POINTER(PVOID) ThreadLocalStoragePointer;
    PEBTEB_POINTER(PPEB) ProcessEnvironmentBlock;
    ULONG LastErrorValue;
    ULONG CountOfOwnedCriticalSections;
    PEBTEB_POINTER(PVOID) CsrClientThread;
    PEBTEB_POINTER(PVOID) Win32ThreadInfo;  // PtiCurrent
    ULONG User32Reserved[26];              // user32.dll items
    ULONG UserReserved[5];                 // Winsrv SwitchStack
    PEBTEB_POINTER(PVOID) WOW32Reserved;    // used by WOW
    LCID CurrentLocale;
    ULONG FpSoftwareStatusRegister;        // offset known by outsiders!
    PVOID ReservedForDebuggerInstrumentation[16];
#if defined(_M_AMD64) || defined(__x86_64__)
    PEBTEB_POINTER(PVOID) SystemReserved1[30];
#else
    PEBTEB_POINTER( PVOID ) SystemReserved1[26];
#endif

    CHAR PlaceholderCompatibilityMode;
    CHAR PlaceholderReserved[11];
    ULONG ProxiedProcessId;
    PEBTEB_STRUCT(ACTIVATION_CONTEXT_STACK) ActivationStack;

    UINT8 WorkingOnBehalfTicket[8];
    NTSTATUS ExceptionCode;     // for RaiseUserException

    PEBTEB_POINTER(PEBTEB_STRUCT(PACTIVATION_CONTEXT_STACK)) ActivationContextStackPointer; // Fusion activation stack
    PEBTEB_POINTER(ULONG_PTR) InstrumentationCallbackSp;
    PEBTEB_POINTER(ULONG_PTR) InstrumentationCallbackPreviousPc;
    PEBTEB_POINTER(ULONG_PTR) InstrumentationCallbackPreviousSp;
#if defined(_M_AMD64) || defined(__x86_64__)
    ULONG TxFsContext;
#endif

    BOOLEAN InstrumentationCallbackDisabled;
#if !(defined(_M_AMD64) || defined(__x86_64__))
    UCHAR SpareBytes[23];
    ULONG TxFsContext;
#endif

    PEBTEB_STRUCT(GDI_TEB_BATCH) GdiTebBatch;      // Gdi batching
    PEBTEB_STRUCT(CLIENT_ID) RealClientId;
    PEBTEB_POINTER(HANDLE) GdiCachedProcessHandle;
    ULONG GdiClientPID;
    ULONG GdiClientTID;
    PEBTEB_POINTER(PVOID) GdiThreadLocalInfo;
    PEBTEB_POINTER(ULONG_PTR) Win32ClientInfo[62];
    PEBTEB_POINTER(PVOID) glDispatchTable[233]; // OpenGL
    PEBTEB_POINTER(ULONG_PTR) glReserved1[29];      // OpenGL
    PEBTEB_POINTER(PVOID) glReserved2;          // OpenGL
    PEBTEB_POINTER(PVOID) glSectionInfo;        // OpenGL
    PEBTEB_POINTER(PVOID) glSection;            // OpenGL
    PEBTEB_POINTER(PVOID) glTable;              // OpenGL
    PEBTEB_POINTER(PVOID) glCurrentRC;          // OpenGL
    PEBTEB_POINTER(PVOID) glContext;            // OpenGL
    NTSTATUS LastStatusValue;
    PEBTEB_STRUCT(UNICODE_STRING) StaticUnicodeString;
    WCHAR StaticUnicodeBuffer[STATIC_UNICODE_BUFFER_LENGTH];
    PEBTEB_POINTER(PVOID) DeallocationStack;
    PEBTEB_POINTER(PVOID) TlsSlots[TLS_MINIMUM_AVAILABLE];
    PEBTEB_STRUCT(LIST_ENTRY) TlsLinks;
    PEBTEB_POINTER(PVOID) Vdm;
    PEBTEB_POINTER(PVOID) ReservedForNtRpc;
    PEBTEB_POINTER(PVOID) DbgSsReserved[2];
    ULONG HardErrorMode;
#if defined(_M_AMD64) || defined(__x86_64__)
    PEBTEB_POINTER(PVOID) Instrumentation[11];
#else
    PEBTEB_POINTER( PVOID ) Instrumentation[9];
#endif
    GUID ActivityId;
    PEBTEB_POINTER(PVOID) SubProcessTag;
    PEBTEB_POINTER(PVOID) PerflibData;
    PEBTEB_POINTER(PVOID) EtwTraceData;
    PEBTEB_POINTER(PVOID) WinSockData;          // WinSock
    ULONG GdiBatchCount;
    union {
        PROCESSOR_NUMBER CurrentIdealProcessor;
        ULONG IdealProcessorValue;
        struct {
            UINT8 ReservedPad0;
            UINT8 ReservedPad1;
            UINT8 ReservedPad2;
            UINT8 IdealProcessor;
        };
    };
    ULONG GuaranteedStackBytes;
    PEBTEB_POINTER(PVOID) ReservedForPerf;
    PEBTEB_POINTER(PVOID) ReservedForOle;
    ULONG WaitingOnLoaderLock;
    PEBTEB_POINTER(PVOID) SavedPriorityState;
    PEBTEB_POINTER(ULONG_PTR) ReservedForCodeCoverage;
    PEBTEB_POINTER(PVOID) ThreadPoolData;
    PEBTEB_POINTER(PPVOID) TlsExpansionSlots;
#if ((defined(_M_AMD64) || defined(__x86_64__)) && !defined(PEBTEB_BITS))  \
 || (((defined(_M_AMD64) || defined(__x86_64__)) || (defined(_M_IX86) || defined(__i386__))) \
 && defined(PEBTEB_BITS) && PEBTEB_BITS == 64)
    //
    // These are in native Win64 TEB, Win64 TEB64, and x86 TEB64.
    //
    PEBTEB_POINTER(PVOID) DeallocationBStore;
    PEBTEB_POINTER(PVOID) BStoreLimit;
#endif
    ULONG MuiGeneration;
    ULONG IsImpersonating;         // Thread impersonation status
    PEBTEB_POINTER(PVOID) NlsCache;     // NLS thread cache
    PEBTEB_POINTER(PVOID) pShimData;    // Per thread data used in the shim
    USHORT HeapVirtualAffinity;
    USHORT LowFragHeapDataSlot;
    PEBTEB_POINTER(HANDLE) CurrentTransactionHandle;// reserved for TxF transaction context
    PEBTEB_POINTER(PTEB_ACTIVE_FRAME) ActiveFrame;
    PEBTEB_POINTER(PVOID) FlsData;
    PEBTEB_POINTER(PVOID) PreferredLanguages;
    PEBTEB_POINTER(PVOID) UserPrefLanguages;
    PEBTEB_POINTER(PVOID) MergedPrefLanguages;
    ULONG MuiImpersonation; // mui impersonation status
    union {
        USHORT CrossTebFlags;
        USHORT SpareCrossTebBits : 16;
    };
    union {
        USHORT SameTebFlags;
        struct {
            USHORT SafeThunkCall : 1;
            USHORT InDebugPrint : 1;
            USHORT HasFiberData : 1;
            USHORT SkipThreadAttach : 1;
            USHORT WerInShipAssertCode : 1;
            USHORT RanProcessInit : 1;
            USHORT ClonedThread : 1;
            USHORT SuppressDebugMsg : 1;
            USHORT DisableUserStackWalk : 1;
            USHORT RtlExceptionAttached : 1;
            USHORT InitialThread : 1;
            USHORT SessionAware : 1;
            USHORT LoadOwner : 1;
            USHORT LoaderWorker : 1;
            USHORT SkipLoaderInit : 1;
            USHORT SpareSameTebBits : 1;
        };
    };
    PEBTEB_POINTER(PVOID) TxnScopeEnterCallback;
    PEBTEB_POINTER(PVOID) TxnScopeExitCallback;
    PEBTEB_POINTER(PVOID) TxnScopeContext;
    ULONG LockCount;
    INT32 WowTebOffset;
    PEBTEB_POINTER(PVOID) ResourceRetValue;
    PEBTEB_POINTER(PVOID) ReservedForWdf;
    ULONG64 ReservedForCrt;
    GUID EffectiveContainerId;
} PEBTEB_STRUCT(TEB), *PEBTEB_STRUCT(PTEB);

#undef PEBTEB_POINTER
#undef PEBTEB_STRUCT
#undef PEBTEB_PRIVATE_PASTE
#undef PEBTEB_PASTE
