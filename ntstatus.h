#ifndef _NTSTATUS_
#define _NTSTATUS_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef WIN32_NO_STATUS // winnt
 // begin_ntsecapi

 /*lint -save -e767 */  // Don't complain about different definitions // winnt

#if !defined(NTSTATUS_DEFINED)
#define NTSTATUS_DEFINED
typedef _Return_type_success_(return >= 0) long NTSTATUS;
/*lint -save -e624 */  // Don't complain about different typedefs.
typedef NTSTATUS* PNTSTATUS;

#if _WIN32_WINNT >= 0x0600
typedef CONST NTSTATUS* PCNTSTATUS;
#endif // _WIN32_WINNT >= 0x0600
#endif


//
//  Status values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-------------------------+-------------------------------+
//  |Sev|C|       Facility          |               Code            |
//  +---+-+-------------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//

//
// Generic test for success on any status value (non-negative numbers
// indicate success).
//
#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif //!NT_SUCCESS

//
// Generic test for information on any status value.
//

#ifndef NT_INFORMATION
#ifdef _PREFAST_
#define NT_INFORMATION(Status) (((NTSTATUS)(Status)) >= (long)0x40000000)
#else
#define NT_INFORMATION(Status) ((((ULONG)(Status)) >> 30) == 1)
#endif
#endif //!NT_INFORMATION

//
// Generic test for warning on any status value.
//

#ifndef NT_WARNING
#ifdef _PREFAST_
#define NT_WARNING(Status) (((NTSTATUS)(Status) < (long)0xc0000000))
#else
#define NT_WARNING(Status) ((((ULONG)(Status)) >> 30) == 2)
#endif
#endif //!NT_WARNING

//
// Generic test for error on any status value.
//

#ifndef NT_ERROR
#ifdef _PREFAST_
#define NT_ERROR(Status) (((NTSTATUS)(Status)) >= (unsigned long)0xc0000000)
#else
#define NT_ERROR(Status) ((((ULONG)(Status)) >> 30) == 3)
#endif
#endif //!NT_ERROR


/////////////////////////////////////////////////////////////////////////
//
// Please update FACILITY_MAXIMUM_VALUE when adding new facility values.
//     (This value should be greater than the highest value above)
//
// Facility 0x17 is reserved and used in isolation lib as
//             PIE=0x17:FACILITY_MANIFEST_ERROR_CODE
//
//
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
//
// Standard Success values
//
//
/////////////////////////////////////////////////////////////////////////


//
// The success status codes 0 - 63 are reserved for wait completion status.
// FacilityCodes 0x5 - 0xF have been allocated by various drivers.
//
#ifndef STATUS_WAIT_0
#define STATUS_WAIT_0                           ((NTSTATUS)0x00000000L) // winnt
#endif//STATUS_WAIT_0

//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_DEBUGGER                0x1
#define FACILITY_RPC_RUNTIME             0x2
#define FACILITY_RPC_STUBS               0x3
#define FACILITY_IO_ERROR_CODE           0x4
#define FACILITY_CODCLASS_ERROR_CODE     0x6
#define FACILITY_NTWIN32                 0x7
#define FACILITY_NTCERT                  0x8
#define FACILITY_NTSSPI                  0x9
#define FACILITY_TERMINAL_SERVER         0xA
#define FACILTIY_MUI_ERROR_CODE          0xB
#define FACILITY_USB_ERROR_CODE          0x10
#define FACILITY_HID_ERROR_CODE          0x11
#define FACILITY_FIREWIRE_ERROR_CODE     0x12
#define FACILITY_CLUSTER_ERROR_CODE      0x13
#define FACILITY_ACPI_ERROR_CODE         0x14
#define FACILITY_SXS_ERROR_CODE          0x15
#define FACILITY_TRANSACTION             0x19
#define FACILITY_COMMONLOG               0x1A
#define FACILITY_VIDEO                   0x1B
#define FACILITY_FILTER_MANAGER          0x1C
#define FACILITY_MONITOR                 0x1D
#define FACILITY_GRAPHICS_KERNEL         0x1E
#define FACILITY_DRIVER_FRAMEWORK        0x20
#define FACILITY_FVE_ERROR_CODE          0x21
#define FACILITY_FWP_ERROR_CODE          0x22
#define FACILITY_NDIS_ERROR_CODE         0x23
#define FACILITY_TPM                     0x29
#define FACILITY_RTPM                    0x2A
#define FACILITY_HYPERVISOR              0x35
#define FACILITY_IPSEC                   0x36
#define FACILITY_VIRTUALIZATION          0x37
#define FACILITY_VOLMGR                  0x38
#define FACILITY_BCD_ERROR_CODE          0x39
#define FACILITY_WIN32K_NTUSER           0x3E
#define FACILITY_WIN32K_NTGDI            0x3F
#define FACILITY_RESUME_KEY_FILTER       0x40
#define FACILITY_RDBSS                   0x41
#define FACILITY_BTH_ATT                 0x42
#define FACILITY_SECUREBOOT              0x43
#define FACILITY_AUDIO_KERNEL            0x44
#define FACILITY_VSM                     0x45
#define FACILITY_VOLSNAP                 0x50
#define FACILITY_SDBUS                   0x51
#define FACILITY_SHARED_VHDX             0x5C
#define FACILITY_SMB                     0x5D
#define FACILITY_INTERIX                 0x99
#define FACILITY_SPACES                  0xE7
#define FACILITY_SECURITY_CORE           0xE8
#define FACILITY_SYSTEM_INTEGRITY        0xE9
#define FACILITY_LICENSING               0xEA
#define FACILITY_PLATFORM_MANIFEST       0xEB
#define FACILITY_APP_EXEC                0xEC
#define FACILITY_MAXIMUM_VALUE           0xED


//
// Define the severity codes
//
#ifndef STATUS_SEVERITY_SUCCESS
#define STATUS_SEVERITY_SUCCESS          0x0
#endif//STATUS_SEVERITY_SUCCESS
#ifndef STATUS_SEVERITY_INFORMATIONAL
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#endif//STATUS_SEVERITY_INFORMATIONAL
#ifndef STATUS_SEVERITY_WARNING
#define STATUS_SEVERITY_WARNING          0x2
#endif//STATUS_SEVERITY_WARNING
#ifndef STATUS_SEVERITY_ERROR
#define STATUS_SEVERITY_ERROR            0x3
#endif//STATUS_SEVERITY_ERROR


//
// MessageId: STATUS_SUCCESS
//
// MessageText:
//
//  STATUS_SUCCESS
//
#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS                   ((NTSTATUS)0x00000000L)    // ntsubauth
#endif//STATUS_SUCCESS

//
// MessageId: STATUS_WAIT_1
//
// MessageText:
//
//  STATUS_WAIT_1
//
#ifndef STATUS_WAIT_1
#define STATUS_WAIT_1                    ((NTSTATUS)0x00000001L)
#endif//STATUS_WAIT_1

//
// MessageId: STATUS_WAIT_2
//
// MessageText:
//
//  STATUS_WAIT_2
//
#ifndef STATUS_WAIT_2
#define STATUS_WAIT_2                    ((NTSTATUS)0x00000002L)
#endif//STATUS_WAIT_2

//
// MessageId: STATUS_WAIT_3
//
// MessageText:
//
//  STATUS_WAIT_3
//
#ifndef STATUS_WAIT_3
#define STATUS_WAIT_3                    ((NTSTATUS)0x00000003L)
#endif//STATUS_WAIT_3

//
// MessageId: STATUS_WAIT_63
//
// MessageText:
//
//  STATUS_WAIT_63
//
#ifndef STATUS_WAIT_63
#define STATUS_WAIT_63                   ((NTSTATUS)0x0000003FL)
#endif//STATUS_WAIT_63


//
// The success status codes 128 - 191 are reserved for wait completion
// status with an abandoned mutant object.
//
#ifndef STATUS_ABANDONED
#define STATUS_ABANDONED                        ((NTSTATUS)0x00000080L)
#endif//STATUS_ABANDONED

//
// MessageId: STATUS_ABANDONED_WAIT_0
//
// MessageText:
//
//  STATUS_ABANDONED_WAIT_0
//
#ifndef STATUS_ABANDONED_WAIT_0
#define STATUS_ABANDONED_WAIT_0          ((NTSTATUS)0x00000080L)    // winnt
#endif//STATUS_ABANDONED_WAIT_0

//
// MessageId: STATUS_ABANDONED_WAIT_63
//
// MessageText:
//
//  STATUS_ABANDONED_WAIT_63
//
#ifndef STATUS_ABANDONED_WAIT_63
#define STATUS_ABANDONED_WAIT_63         ((NTSTATUS)0x000000BFL)
#endif//STATUS_ABANDONED_WAIT_63


//
// The success status codes 256, 257, 258, and 258 are reserved for
// User APC, Kernel APC, Alerted, and Timeout.
//
//
// MessageId: STATUS_USER_APC
//
// MessageText:
//
//  STATUS_USER_APC
//
#ifndef STATUS_USER_APC
#define STATUS_USER_APC                  ((NTSTATUS)0x000000C0L)    // winnt
#endif//STATUS_USER_APC

//
// MessageId: STATUS_ALREADY_COMPLETE
//
// MessageText:
//
// The requested action was completed by an earlier operation.
//
#ifndef STATUS_ALREADY_COMPLETE
#define STATUS_ALREADY_COMPLETE          ((NTSTATUS)0x000000FFL)
#endif//STATUS_ALREADY_COMPLETE

//
// MessageId: STATUS_KERNEL_APC
//
// MessageText:
//
//  STATUS_KERNEL_APC
//
#ifndef STATUS_KERNEL_APC
#define STATUS_KERNEL_APC                ((NTSTATUS)0x00000100L)
#endif//STATUS_KERNEL_APC

//
// MessageId: STATUS_ALERTED
//
// MessageText:
//
//  STATUS_ALERTED
//
#ifndef STATUS_ALERTED
#define STATUS_ALERTED                   ((NTSTATUS)0x00000101L)
#endif//STATUS_ALERTED

//
// MessageId: STATUS_TIMEOUT
//
// MessageText:
//
//  STATUS_TIMEOUT
//
#ifndef STATUS_TIMEOUT
#define STATUS_TIMEOUT                   ((NTSTATUS)0x00000102L)    // winnt
#endif//STATUS_TIMEOUT

//
// MessageId: STATUS_PENDING
//
// MessageText:
//
// The operation that was requested is pending completion.
//
#ifndef STATUS_PENDING
#define STATUS_PENDING                   ((NTSTATUS)0x00000103L)    // winnt
#endif//STATUS_PENDING

//
// MessageId: STATUS_REPARSE
//
// MessageText:
//
// A reparse should be performed by the Object Manager since the name of the file resulted in a symbolic link.
//
#ifndef STATUS_REPARSE
#define STATUS_REPARSE                   ((NTSTATUS)0x00000104L)
#endif//STATUS_REPARSE

//
// MessageId: STATUS_MORE_ENTRIES
//
// MessageText:
//
// Returned by enumeration APIs to indicate more information is available to successive calls.
//
#ifndef STATUS_MORE_ENTRIES
#define STATUS_MORE_ENTRIES              ((NTSTATUS)0x00000105L)
#endif//STATUS_MORE_ENTRIES

//
// MessageId: STATUS_NOT_ALL_ASSIGNED
//
// MessageText:
//
// Indicates not all privileges or groups referenced are assigned to the caller.
// This allows, for example, all privileges to be disabled without having to know exactly which privileges are assigned.
//
#ifndef STATUS_NOT_ALL_ASSIGNED
#define STATUS_NOT_ALL_ASSIGNED          ((NTSTATUS)0x00000106L)
#endif//STATUS_NOT_ALL_ASSIGNED

//
// MessageId: STATUS_SOME_NOT_MAPPED
//
// MessageText:
//
// Some of the information to be translated has not been translated.
//
#ifndef STATUS_SOME_NOT_MAPPED
#define STATUS_SOME_NOT_MAPPED           ((NTSTATUS)0x00000107L)
#endif//STATUS_SOME_NOT_MAPPED

//
// MessageId: STATUS_OPLOCK_BREAK_IN_PROGRESS
//
// MessageText:
//
// An open/create operation completed while an oplock break is underway.
//
#ifndef STATUS_OPLOCK_BREAK_IN_PROGRESS
#define STATUS_OPLOCK_BREAK_IN_PROGRESS  ((NTSTATUS)0x00000108L)
#endif//STATUS_OPLOCK_BREAK_IN_PROGRESS

//
// MessageId: STATUS_VOLUME_MOUNTED
//
// MessageText:
//
// A new volume has been mounted by a file system.
//
#ifndef STATUS_VOLUME_MOUNTED
#define STATUS_VOLUME_MOUNTED            ((NTSTATUS)0x00000109L)
#endif//STATUS_VOLUME_MOUNTED

//
// MessageId: STATUS_RXACT_COMMITTED
//
// MessageText:
//
// This success level status indicates that the transaction state already exists for the registry sub-tree, but that a transaction commit was previously aborted. The commit has now been completed.
//
#ifndef STATUS_RXACT_COMMITTED
#define STATUS_RXACT_COMMITTED           ((NTSTATUS)0x0000010AL)
#endif//STATUS_RXACT_COMMITTED

//
// MessageId: STATUS_NOTIFY_CLEANUP
//
// MessageText:
//
// This indicates that a notify change request has been completed due to closing the handle which made the notify change request.
//
#ifndef STATUS_NOTIFY_CLEANUP
#define STATUS_NOTIFY_CLEANUP            ((NTSTATUS)0x0000010BL)
#endif//STATUS_NOTIFY_CLEANUP

//
// MessageId: STATUS_NOTIFY_ENUM_DIR
//
// MessageText:
//
// This indicates that a notify change request is being completed and that the information is not being returned in the caller's buffer.
// The caller now needs to enumerate the files to find the changes.
//
#ifndef STATUS_NOTIFY_ENUM_DIR
#define STATUS_NOTIFY_ENUM_DIR           ((NTSTATUS)0x0000010CL)
#endif//STATUS_NOTIFY_ENUM_DIR

//
// MessageId: STATUS_NO_QUOTAS_FOR_ACCOUNT
//
// MessageText:
//
// {No Quotas}
// No system quota limits are specifically set for this account.
//
#ifndef STATUS_NO_QUOTAS_FOR_ACCOUNT
#define STATUS_NO_QUOTAS_FOR_ACCOUNT     ((NTSTATUS)0x0000010DL)
#endif//STATUS_NO_QUOTAS_FOR_ACCOUNT

//
// MessageId: STATUS_PRIMARY_TRANSPORT_CONNECT_FAILED
//
// MessageText:
//
// {Connect Failure on Primary Transport}
// An attempt was made to connect to the remote server %hs on the primary transport, but the connection failed.
// The computer WAS able to connect on a secondary transport.
//
#ifndef STATUS_PRIMARY_TRANSPORT_CONNECT_FAILED
#define STATUS_PRIMARY_TRANSPORT_CONNECT_FAILED ((NTSTATUS)0x0000010EL)
#endif//STATUS_PRIMARY_TRANSPORT_CONNECT_FAILED

//
// MessageId: STATUS_PAGE_FAULT_TRANSITION
//
// MessageText:
//
// Page fault was a transition fault.
//
#ifndef STATUS_PAGE_FAULT_TRANSITION
#define STATUS_PAGE_FAULT_TRANSITION     ((NTSTATUS)0x00000110L)
#endif//STATUS_PAGE_FAULT_TRANSITION

//
// MessageId: STATUS_PAGE_FAULT_DEMAND_ZERO
//
// MessageText:
//
// Page fault was a demand zero fault.
//
#ifndef STATUS_PAGE_FAULT_DEMAND_ZERO
#define STATUS_PAGE_FAULT_DEMAND_ZERO    ((NTSTATUS)0x00000111L)
#endif//STATUS_PAGE_FAULT_DEMAND_ZERO

//
// MessageId: STATUS_PAGE_FAULT_COPY_ON_WRITE
//
// MessageText:
//
// Page fault was a demand zero fault.
//
#ifndef STATUS_PAGE_FAULT_COPY_ON_WRITE
#define STATUS_PAGE_FAULT_COPY_ON_WRITE  ((NTSTATUS)0x00000112L)
#endif//STATUS_PAGE_FAULT_COPY_ON_WRITE

//
// MessageId: STATUS_PAGE_FAULT_GUARD_PAGE
//
// MessageText:
//
// Page fault was a demand zero fault.
//
#ifndef STATUS_PAGE_FAULT_GUARD_PAGE
#define STATUS_PAGE_FAULT_GUARD_PAGE     ((NTSTATUS)0x00000113L)
#endif//STATUS_PAGE_FAULT_GUARD_PAGE

//
// MessageId: STATUS_PAGE_FAULT_PAGING_FILE
//
// MessageText:
//
// Page fault was satisfied by reading from a secondary storage device.
//
#ifndef STATUS_PAGE_FAULT_PAGING_FILE
#define STATUS_PAGE_FAULT_PAGING_FILE    ((NTSTATUS)0x00000114L)
#endif//STATUS_PAGE_FAULT_PAGING_FILE

//
// MessageId: STATUS_CACHE_PAGE_LOCKED
//
// MessageText:
//
// Cached page was locked during operation.
//
#ifndef STATUS_CACHE_PAGE_LOCKED
#define STATUS_CACHE_PAGE_LOCKED         ((NTSTATUS)0x00000115L)
#endif//STATUS_CACHE_PAGE_LOCKED

//
// MessageId: STATUS_CRASH_DUMP
//
// MessageText:
//
// Crash dump exists in paging file.
//
#ifndef STATUS_CRASH_DUMP
#define STATUS_CRASH_DUMP                ((NTSTATUS)0x00000116L)
#endif//STATUS_CRASH_DUMP

//
// MessageId: STATUS_BUFFER_ALL_ZEROS
//
// MessageText:
//
// Specified buffer contains all zeros.
//
#ifndef STATUS_BUFFER_ALL_ZEROS
#define STATUS_BUFFER_ALL_ZEROS          ((NTSTATUS)0x00000117L)
#endif//STATUS_BUFFER_ALL_ZEROS

//
// MessageId: STATUS_REPARSE_OBJECT
//
// MessageText:
//
// A reparse should be performed by the Object Manager since the name of the file resulted in a symbolic link.
//
#ifndef STATUS_REPARSE_OBJECT
#define STATUS_REPARSE_OBJECT            ((NTSTATUS)0x00000118L)
#endif//STATUS_REPARSE_OBJECT

//
// MessageId: STATUS_RESOURCE_REQUIREMENTS_CHANGED
//
// MessageText:
//
// The device has succeeded a query-stop and its resource requirements have changed.
//
#ifndef STATUS_RESOURCE_REQUIREMENTS_CHANGED
#define STATUS_RESOURCE_REQUIREMENTS_CHANGED ((NTSTATUS)0x00000119L)
#endif//STATUS_RESOURCE_REQUIREMENTS_CHANGED

//
// MessageId: STATUS_TRANSLATION_COMPLETE
//
// MessageText:
//
// The translator has translated these resources into the global space and no further translations should be performed.
//
#ifndef STATUS_TRANSLATION_COMPLETE
#define STATUS_TRANSLATION_COMPLETE      ((NTSTATUS)0x00000120L)
#endif//STATUS_TRANSLATION_COMPLETE

//
// MessageId: STATUS_DS_MEMBERSHIP_EVALUATED_LOCALLY
//
// MessageText:
//
// The directory service evaluated group memberships locally, as it was unable to contact a global catalog server.
//
#ifndef STATUS_DS_MEMBERSHIP_EVALUATED_LOCALLY
#define STATUS_DS_MEMBERSHIP_EVALUATED_LOCALLY ((NTSTATUS)0x00000121L)
#endif//STATUS_DS_MEMBERSHIP_EVALUATED_LOCALLY

//
// MessageId: STATUS_NOTHING_TO_TERMINATE
//
// MessageText:
//
// A process being terminated has no threads to terminate.
//
#ifndef STATUS_NOTHING_TO_TERMINATE
#define STATUS_NOTHING_TO_TERMINATE      ((NTSTATUS)0x00000122L)
#endif//STATUS_NOTHING_TO_TERMINATE

//
// MessageId: STATUS_PROCESS_NOT_IN_JOB
//
// MessageText:
//
// The specified process is not part of a job.
//
#ifndef STATUS_PROCESS_NOT_IN_JOB
#define STATUS_PROCESS_NOT_IN_JOB        ((NTSTATUS)0x00000123L)
#endif//STATUS_PROCESS_NOT_IN_JOB

//
// MessageId: STATUS_PROCESS_IN_JOB
//
// MessageText:
//
// The specified process is part of a job.
//
#ifndef STATUS_PROCESS_IN_JOB
#define STATUS_PROCESS_IN_JOB            ((NTSTATUS)0x00000124L)
#endif//STATUS_PROCESS_IN_JOB

//
// MessageId: STATUS_VOLSNAP_HIBERNATE_READY
//
// MessageText:
//
// {Volume Shadow Copy Service}
// The system is now ready for hibernation.
//
#ifndef STATUS_VOLSNAP_HIBERNATE_READY
#define STATUS_VOLSNAP_HIBERNATE_READY   ((NTSTATUS)0x00000125L)
#endif//STATUS_VOLSNAP_HIBERNATE_READY

//
// MessageId: STATUS_FSFILTER_OP_COMPLETED_SUCCESSFULLY
//
// MessageText:
//
// A file system or file system filter driver has successfully completed an FsFilter operation.
//
#ifndef STATUS_FSFILTER_OP_COMPLETED_SUCCESSFULLY
#define STATUS_FSFILTER_OP_COMPLETED_SUCCESSFULLY ((NTSTATUS)0x00000126L)
#endif//STATUS_FSFILTER_OP_COMPLETED_SUCCESSFULLY

//
// MessageId: STATUS_INTERRUPT_VECTOR_ALREADY_CONNECTED
//
// MessageText:
//
// The specified interrupt vector was already connected.
//
#ifndef STATUS_INTERRUPT_VECTOR_ALREADY_CONNECTED
#define STATUS_INTERRUPT_VECTOR_ALREADY_CONNECTED ((NTSTATUS)0x00000127L)
#endif//STATUS_INTERRUPT_VECTOR_ALREADY_CONNECTED

//
// MessageId: STATUS_INTERRUPT_STILL_CONNECTED
//
// MessageText:
//
// The specified interrupt vector is still connected.
//
#ifndef STATUS_INTERRUPT_STILL_CONNECTED
#define STATUS_INTERRUPT_STILL_CONNECTED ((NTSTATUS)0x00000128L)
#endif//STATUS_INTERRUPT_STILL_CONNECTED

//
// MessageId: STATUS_PROCESS_CLONED
//
// MessageText:
//
// The current process is a cloned process.
//
#ifndef STATUS_PROCESS_CLONED
#define STATUS_PROCESS_CLONED            ((NTSTATUS)0x00000129L)
#endif//STATUS_PROCESS_CLONED

//
// MessageId: STATUS_FILE_LOCKED_WITH_ONLY_READERS
//
// MessageText:
//
// The file was locked and all users of the file can only read.
//
#ifndef STATUS_FILE_LOCKED_WITH_ONLY_READERS
#define STATUS_FILE_LOCKED_WITH_ONLY_READERS ((NTSTATUS)0x0000012AL)
#endif//STATUS_FILE_LOCKED_WITH_ONLY_READERS

//
// MessageId: STATUS_FILE_LOCKED_WITH_WRITERS
//
// MessageText:
//
// The file was locked and at least one user of the file can write.
//
#ifndef STATUS_FILE_LOCKED_WITH_WRITERS
#define STATUS_FILE_LOCKED_WITH_WRITERS  ((NTSTATUS)0x0000012BL)
#endif//STATUS_FILE_LOCKED_WITH_WRITERS

//
// MessageId: STATUS_VALID_IMAGE_HASH
//
// MessageText:
//
// The file image hash is valid.
//
#ifndef STATUS_VALID_IMAGE_HASH
#define STATUS_VALID_IMAGE_HASH          ((NTSTATUS)0x0000012CL)
#endif//STATUS_VALID_IMAGE_HASH

//
// MessageId: STATUS_VALID_CATALOG_HASH
//
// MessageText:
//
// The file catalog hash is valid.
//
#ifndef STATUS_VALID_CATALOG_HASH
#define STATUS_VALID_CATALOG_HASH        ((NTSTATUS)0x0000012DL)
#endif//STATUS_VALID_CATALOG_HASH

//
// MessageId: STATUS_VALID_STRONG_CODE_HASH
//
// MessageText:
//
// The file hash is valid and uses strong code integrity.
//
#ifndef STATUS_VALID_STRONG_CODE_HASH
#define STATUS_VALID_STRONG_CODE_HASH    ((NTSTATUS)0x0000012EL)
#endif//STATUS_VALID_STRONG_CODE_HASH

//
// MessageId: STATUS_GHOSTED
//
// MessageText:
//
// At least a portion of IO range intersects with a ghosted file range.
//
#ifndef STATUS_GHOSTED
#define STATUS_GHOSTED                   ((NTSTATUS)0x0000012FL)
#endif//STATUS_GHOSTED

//
// MessageId: STATUS_DATA_OVERWRITTEN
//
// MessageText:
//
// A completed operation may have overwritten previous data.
//
#ifndef STATUS_DATA_OVERWRITTEN
#define STATUS_DATA_OVERWRITTEN          ((NTSTATUS)0x00000130L)
#endif//STATUS_DATA_OVERWRITTEN

//
// MessageId: STATUS_RESOURCEMANAGER_READ_ONLY
//
// MessageText:
//
// The specified ResourceManager made no changes or updates to the resource under this transaction.
//
#ifndef STATUS_RESOURCEMANAGER_READ_ONLY
#define STATUS_RESOURCEMANAGER_READ_ONLY ((NTSTATUS)0x00000202L)
#endif//STATUS_RESOURCEMANAGER_READ_ONLY

//
// MessageId: STATUS_RING_PREVIOUSLY_EMPTY
//
// MessageText:
//
// The specified ring buffer was empty before the packet was successfully inserted.
//
#ifndef STATUS_RING_PREVIOUSLY_EMPTY
#define STATUS_RING_PREVIOUSLY_EMPTY     ((NTSTATUS)0x00000210L)
#endif//STATUS_RING_PREVIOUSLY_EMPTY

//
// MessageId: STATUS_RING_PREVIOUSLY_FULL
//
// MessageText:
//
// The specified ring buffer was full before the packet was successfully removed.
//
#ifndef STATUS_RING_PREVIOUSLY_FULL
#define STATUS_RING_PREVIOUSLY_FULL      ((NTSTATUS)0x00000211L)
#endif//STATUS_RING_PREVIOUSLY_FULL

//
// MessageId: STATUS_RING_PREVIOUSLY_ABOVE_QUOTA
//
// MessageText:
//
// The specified ring buffer has dropped below its quota of outstanding transactions.
//
#ifndef STATUS_RING_PREVIOUSLY_ABOVE_QUOTA
#define STATUS_RING_PREVIOUSLY_ABOVE_QUOTA ((NTSTATUS)0x00000212L)
#endif//STATUS_RING_PREVIOUSLY_ABOVE_QUOTA

//
// MessageId: STATUS_RING_NEWLY_EMPTY
//
// MessageText:
//
// The specified ring buffer has, with the removal of the current packet, now become empty.
//
#ifndef STATUS_RING_NEWLY_EMPTY
#define STATUS_RING_NEWLY_EMPTY          ((NTSTATUS)0x00000213L)
#endif//STATUS_RING_NEWLY_EMPTY

//
// MessageId: STATUS_RING_SIGNAL_OPPOSITE_ENDPOINT
//
// MessageText:
//
// The specified ring buffer was either previously empty or previously full which implies that the caller should signal the opposite endpoint.
//
#ifndef STATUS_RING_SIGNAL_OPPOSITE_ENDPOINT
#define STATUS_RING_SIGNAL_OPPOSITE_ENDPOINT ((NTSTATUS)0x00000214L)
#endif//STATUS_RING_SIGNAL_OPPOSITE_ENDPOINT

//
// MessageId: STATUS_OPLOCK_SWITCHED_TO_NEW_HANDLE
//
// MessageText:
//
// The oplock that was associated with this handle is now associated with a different handle.
//
#ifndef STATUS_OPLOCK_SWITCHED_TO_NEW_HANDLE
#define STATUS_OPLOCK_SWITCHED_TO_NEW_HANDLE ((NTSTATUS)0x00000215L)
#endif//STATUS_OPLOCK_SWITCHED_TO_NEW_HANDLE

//
// MessageId: STATUS_OPLOCK_HANDLE_CLOSED
//
// MessageText:
//
// The handle with which this oplock was associated has been closed.  The oplock is now broken.
//
#ifndef STATUS_OPLOCK_HANDLE_CLOSED
#define STATUS_OPLOCK_HANDLE_CLOSED      ((NTSTATUS)0x00000216L)
#endif//STATUS_OPLOCK_HANDLE_CLOSED

//
// MessageId: STATUS_WAIT_FOR_OPLOCK
//
// MessageText:
//
// An operation is blocked waiting for an oplock.
//
#ifndef STATUS_WAIT_FOR_OPLOCK
#define STATUS_WAIT_FOR_OPLOCK           ((NTSTATUS)0x00000367L)
#endif//STATUS_WAIT_FOR_OPLOCK

//
// MessageId: STATUS_REPARSE_GLOBAL
//
// MessageText:
//
// A reparse should be performed by the Object Manager from the global root to escape the container name space.
//
#ifndef STATUS_REPARSE_GLOBAL
#define STATUS_REPARSE_GLOBAL            ((NTSTATUS)0x00000368L)
#endif//STATUS_REPARSE_GLOBAL

//
// MessageId: DBG_EXCEPTION_HANDLED
//
// MessageText:
//
// Debugger handled exception
//
#ifndef DBG_EXCEPTION_HANDLED
#define DBG_EXCEPTION_HANDLED            ((NTSTATUS)0x00010001L)    // winnt
#endif//DBG_EXCEPTION_HANDLED

//
// MessageId: DBG_CONTINUE
//
// MessageText:
//
// Debugger continued
//
#ifndef DBG_CONTINUE
#define DBG_CONTINUE                     ((NTSTATUS)0x00010002L)    // winnt
#endif//DBG_CONTINUE

//
// MessageId: STATUS_FLT_IO_COMPLETE
//
// MessageText:
//
// The IO was completed by a filter.
//
#ifndef STATUS_FLT_IO_COMPLETE
#define STATUS_FLT_IO_COMPLETE           ((NTSTATUS)0x001C0001L)
#endif//STATUS_FLT_IO_COMPLETE

/////////////////////////////////////////////////////////////////////////
//
// Standard Information values
//
/////////////////////////////////////////////////////////////////////////

//
// MessageId: STATUS_OBJECT_NAME_EXISTS
//
// MessageText:
//
// {Object Exists}
// An attempt was made to create an object and the object name already existed.
//
#ifndef STATUS_OBJECT_NAME_EXISTS
#define STATUS_OBJECT_NAME_EXISTS        ((NTSTATUS)0x40000000L)
#endif//STATUS_OBJECT_NAME_EXISTS

//
// MessageId: STATUS_THREAD_WAS_SUSPENDED
//
// MessageText:
//
// {Thread Suspended}
// A thread termination occurred while the thread was suspended. The thread was resumed, and termination proceeded.
//
#ifndef STATUS_THREAD_WAS_SUSPENDED
#define STATUS_THREAD_WAS_SUSPENDED      ((NTSTATUS)0x40000001L)
#endif//STATUS_THREAD_WAS_SUSPENDED

//
// MessageId: STATUS_WORKING_SET_LIMIT_RANGE
//
// MessageText:
//
// {Working Set Range Error}
// An attempt was made to set the working set minimum or maximum to values which are outside of the allowable range.
//
#ifndef STATUS_WORKING_SET_LIMIT_RANGE
#define STATUS_WORKING_SET_LIMIT_RANGE   ((NTSTATUS)0x40000002L)
#endif//STATUS_WORKING_SET_LIMIT_RANGE

//
// MessageId: STATUS_IMAGE_NOT_AT_BASE
//
// MessageText:
//
// {Image Relocated}
// An image file could not be mapped at the address specified in the image file. Local fixups must be performed on this image.
//
#ifndef STATUS_IMAGE_NOT_AT_BASE
#define STATUS_IMAGE_NOT_AT_BASE         ((NTSTATUS)0x40000003L)
#endif//STATUS_IMAGE_NOT_AT_BASE

//
// MessageId: STATUS_RXACT_STATE_CREATED
//
// MessageText:
//
// This informational level status indicates that a specified registry sub-tree transaction state did not yet exist and had to be created.
//
#ifndef STATUS_RXACT_STATE_CREATED
#define STATUS_RXACT_STATE_CREATED       ((NTSTATUS)0x40000004L)
#endif//STATUS_RXACT_STATE_CREATED

//
// MessageId: STATUS_SEGMENT_NOTIFICATION
//
// MessageText:
//
// {Segment Load}
// A virtual DOS machine (VDM) is loading, unloading, or moving an MS-DOS or Win16 program segment image.
// An exception is raised so a debugger can load, unload or track symbols and breakpoints within these 16-bit segments.
//
#ifndef STATUS_SEGMENT_NOTIFICATION
#define STATUS_SEGMENT_NOTIFICATION      ((NTSTATUS)0x40000005L)    // winnt
#endif//STATUS_SEGMENT_NOTIFICATION

//
// MessageId: STATUS_LOCAL_USER_SESSION_KEY
//
// MessageText:
//
// {Local Session Key}
// A user session key was requested for a local RPC connection. The session key returned is a constant value and not unique to this connection.
//
#ifndef STATUS_LOCAL_USER_SESSION_KEY
#define STATUS_LOCAL_USER_SESSION_KEY    ((NTSTATUS)0x40000006L)
#endif//STATUS_LOCAL_USER_SESSION_KEY

//
// MessageId: STATUS_BAD_CURRENT_DIRECTORY
//
// MessageText:
//
// {Invalid Current Directory}
// The process cannot switch to the startup current directory %hs.
// Select OK to set current directory to %hs, or select CANCEL to exit.
//
#ifndef STATUS_BAD_CURRENT_DIRECTORY
#define STATUS_BAD_CURRENT_DIRECTORY     ((NTSTATUS)0x40000007L)
#endif//STATUS_BAD_CURRENT_DIRECTORY

//
// MessageId: STATUS_SERIAL_MORE_WRITES
//
// MessageText:
//
// {Serial IOCTL Complete}
// A serial I/O operation was completed by another write to a serial port.
// (The IOCTL_SERIAL_XOFF_COUNTER reached zero.)
//
#ifndef STATUS_SERIAL_MORE_WRITES
#define STATUS_SERIAL_MORE_WRITES        ((NTSTATUS)0x40000008L)
#endif//STATUS_SERIAL_MORE_WRITES

//
// MessageId: STATUS_REGISTRY_RECOVERED
//
// MessageText:
//
// {Registry Recovery}
// One of the files containing the system's Registry data had to be recovered by use of a log or alternate copy. The recovery was successful.
//
#ifndef STATUS_REGISTRY_RECOVERED
#define STATUS_REGISTRY_RECOVERED        ((NTSTATUS)0x40000009L)
#endif//STATUS_REGISTRY_RECOVERED

//
// MessageId: STATUS_FT_READ_RECOVERY_FROM_BACKUP
//
// MessageText:
//
// {Redundant Read}
// To satisfy a read request, the NT fault-tolerant file system successfully read the requested data from a redundant copy.
// This was done because the file system encountered a failure on a member of the fault-tolerant volume, but was unable to reassign the failing area of the device.
//
#ifndef STATUS_FT_READ_RECOVERY_FROM_BACKUP
#define STATUS_FT_READ_RECOVERY_FROM_BACKUP ((NTSTATUS)0x4000000AL)
#endif//STATUS_FT_READ_RECOVERY_FROM_BACKUP

//
// MessageId: STATUS_FT_WRITE_RECOVERY
//
// MessageText:
//
// {Redundant Write}
// To satisfy a write request, the NT fault-tolerant file system successfully wrote a redundant copy of the information.
// This was done because the file system encountered a failure on a member of the fault-tolerant volume, but was not able to reassign the failing area of the device.
//
#ifndef STATUS_FT_WRITE_RECOVERY
#define STATUS_FT_WRITE_RECOVERY         ((NTSTATUS)0x4000000BL)
#endif//STATUS_FT_WRITE_RECOVERY

//
// MessageId: STATUS_SERIAL_COUNTER_TIMEOUT
//
// MessageText:
//
// {Serial IOCTL Timeout}
// A serial I/O operation completed because the time-out period expired. (The IOCTL_SERIAL_XOFF_COUNTER had not reached zero.)
//
#ifndef STATUS_SERIAL_COUNTER_TIMEOUT
#define STATUS_SERIAL_COUNTER_TIMEOUT    ((NTSTATUS)0x4000000CL)
#endif//STATUS_SERIAL_COUNTER_TIMEOUT

//
// MessageId: STATUS_NULL_LM_PASSWORD
//
// MessageText:
//
// {Password Too Complex}
// The Windows password is too complex to be converted to a LAN Manager password. The LAN Manager password returned is a NULL string.
//
#ifndef STATUS_NULL_LM_PASSWORD
#define STATUS_NULL_LM_PASSWORD          ((NTSTATUS)0x4000000DL)
#endif//STATUS_NULL_LM_PASSWORD

//
// MessageId: STATUS_IMAGE_MACHINE_TYPE_MISMATCH
//
// MessageText:
//
// {Machine Type Mismatch}
// The image file %hs is valid, but is for a machine type other than the current machine. Select OK to continue, or CANCEL to fail the DLL load.
//
#ifndef STATUS_IMAGE_MACHINE_TYPE_MISMATCH
#define STATUS_IMAGE_MACHINE_TYPE_MISMATCH ((NTSTATUS)0x4000000EL)
#endif//STATUS_IMAGE_MACHINE_TYPE_MISMATCH

//
// MessageId: STATUS_RECEIVE_PARTIAL
//
// MessageText:
//
// {Partial Data Received}
// The network transport returned partial data to its client. The remaining data will be sent later.
//
#ifndef STATUS_RECEIVE_PARTIAL
#define STATUS_RECEIVE_PARTIAL           ((NTSTATUS)0x4000000FL)
#endif//STATUS_RECEIVE_PARTIAL

//
// MessageId: STATUS_RECEIVE_EXPEDITED
//
// MessageText:
//
// {Expedited Data Received}
// The network transport returned data to its client that was marked as expedited by the remote system.
//
#ifndef STATUS_RECEIVE_EXPEDITED
#define STATUS_RECEIVE_EXPEDITED         ((NTSTATUS)0x40000010L)
#endif//STATUS_RECEIVE_EXPEDITED

//
// MessageId: STATUS_RECEIVE_PARTIAL_EXPEDITED
//
// MessageText:
//
// {Partial Expedited Data Received}
// The network transport returned partial data to its client and this data was marked as expedited by the remote system. The remaining data will be sent later.
//
#ifndef STATUS_RECEIVE_PARTIAL_EXPEDITED
#define STATUS_RECEIVE_PARTIAL_EXPEDITED ((NTSTATUS)0x40000011L)
#endif//STATUS_RECEIVE_PARTIAL_EXPEDITED

//
// MessageId: STATUS_EVENT_DONE
//
// MessageText:
//
// {TDI Event Done}
// The TDI indication has completed successfully.
//
#ifndef STATUS_EVENT_DONE
#define STATUS_EVENT_DONE                ((NTSTATUS)0x40000012L)
#endif//STATUS_EVENT_DONE

//
// MessageId: STATUS_EVENT_PENDING
//
// MessageText:
//
// {TDI Event Pending}
// The TDI indication has entered the pending state.
//
#ifndef STATUS_EVENT_PENDING
#define STATUS_EVENT_PENDING             ((NTSTATUS)0x40000013L)
#endif//STATUS_EVENT_PENDING

//
// MessageId: STATUS_CHECKING_FILE_SYSTEM
//
// MessageText:
//
// Checking file system on %wZ
//
#ifndef STATUS_CHECKING_FILE_SYSTEM
#define STATUS_CHECKING_FILE_SYSTEM      ((NTSTATUS)0x40000014L)
#endif//STATUS_CHECKING_FILE_SYSTEM

//
// MessageId: STATUS_FATAL_APP_EXIT
//
// MessageText:
//
// {Fatal Application Exit}
// %hs
//
#ifndef STATUS_FATAL_APP_EXIT
#define STATUS_FATAL_APP_EXIT            ((NTSTATUS)0x40000015L)    // winnt
#endif//STATUS_FATAL_APP_EXIT

//
// MessageId: STATUS_PREDEFINED_HANDLE
//
// MessageText:
//
// The specified registry key is referenced by a predefined handle.
//
#ifndef STATUS_PREDEFINED_HANDLE
#define STATUS_PREDEFINED_HANDLE         ((NTSTATUS)0x40000016L)
#endif//STATUS_PREDEFINED_HANDLE

//
// MessageId: STATUS_WAS_UNLOCKED
//
// MessageText:
//
// {Page Unlocked}
// The page protection of a locked page was changed to 'No Access' and the page was unlocked from memory and from the process.
//
#ifndef STATUS_WAS_UNLOCKED
#define STATUS_WAS_UNLOCKED              ((NTSTATUS)0x40000017L)
#endif//STATUS_WAS_UNLOCKED

//
// MessageId: STATUS_SERVICE_NOTIFICATION
//
// MessageText:
//
// %hs
//
#ifndef STATUS_SERVICE_NOTIFICATION
#define STATUS_SERVICE_NOTIFICATION      ((NTSTATUS)0x40000018L)
#endif//STATUS_SERVICE_NOTIFICATION

//
// MessageId: STATUS_WAS_LOCKED
//
// MessageText:
//
// {Page Locked}
// One of the pages to lock was already locked.
//
#ifndef STATUS_WAS_LOCKED
#define STATUS_WAS_LOCKED                ((NTSTATUS)0x40000019L)
#endif//STATUS_WAS_LOCKED

//
// MessageId: STATUS_LOG_HARD_ERROR
//
// MessageText:
//
// Application popup: %1 : %2
//
#ifndef STATUS_LOG_HARD_ERROR
#define STATUS_LOG_HARD_ERROR            ((NTSTATUS)0x4000001AL)
#endif//STATUS_LOG_HARD_ERROR

//
// MessageId: STATUS_ALREADY_WIN32
//
// MessageText:
//
//  STATUS_ALREADY_WIN32
//
#ifndef STATUS_ALREADY_WIN32
#define STATUS_ALREADY_WIN32             ((NTSTATUS)0x4000001BL)
#endif//STATUS_ALREADY_WIN32

//
// MessageId: STATUS_WX86_UNSIMULATE
//
// MessageText:
//
// Exception status code used by Win32 x86 emulation subsystem.
//
#ifndef STATUS_WX86_UNSIMULATE
#define STATUS_WX86_UNSIMULATE           ((NTSTATUS)0x4000001CL)
#endif//STATUS_WX86_UNSIMULATE

//
// MessageId: STATUS_WX86_CONTINUE
//
// MessageText:
//
// Exception status code used by Win32 x86 emulation subsystem.
//
#ifndef STATUS_WX86_CONTINUE
#define STATUS_WX86_CONTINUE             ((NTSTATUS)0x4000001DL)
#endif//STATUS_WX86_CONTINUE

//
// MessageId: STATUS_WX86_SINGLE_STEP
//
// MessageText:
//
// Exception status code used by Win32 x86 emulation subsystem.
//
#ifndef STATUS_WX86_SINGLE_STEP
#define STATUS_WX86_SINGLE_STEP          ((NTSTATUS)0x4000001EL)
#endif//STATUS_WX86_SINGLE_STEP

//
// MessageId: STATUS_WX86_BREAKPOINT
//
// MessageText:
//
// Exception status code used by Win32 x86 emulation subsystem.
//
#ifndef STATUS_WX86_BREAKPOINT
#define STATUS_WX86_BREAKPOINT           ((NTSTATUS)0x4000001FL)
#endif//STATUS_WX86_BREAKPOINT

//
// MessageId: STATUS_WX86_EXCEPTION_CONTINUE
//
// MessageText:
//
// Exception status code used by Win32 x86 emulation subsystem.
//
#ifndef STATUS_WX86_EXCEPTION_CONTINUE
#define STATUS_WX86_EXCEPTION_CONTINUE   ((NTSTATUS)0x40000020L)
#endif//STATUS_WX86_EXCEPTION_CONTINUE

//
// MessageId: STATUS_WX86_EXCEPTION_LASTCHANCE
//
// MessageText:
//
// Exception status code used by Win32 x86 emulation subsystem.
//
#ifndef STATUS_WX86_EXCEPTION_LASTCHANCE
#define STATUS_WX86_EXCEPTION_LASTCHANCE ((NTSTATUS)0x40000021L)
#endif//STATUS_WX86_EXCEPTION_LASTCHANCE

//
// MessageId: STATUS_WX86_EXCEPTION_CHAIN
//
// MessageText:
//
// Exception status code used by Win32 x86 emulation subsystem.
//
#ifndef STATUS_WX86_EXCEPTION_CHAIN
#define STATUS_WX86_EXCEPTION_CHAIN      ((NTSTATUS)0x40000022L)
#endif//STATUS_WX86_EXCEPTION_CHAIN

//
// MessageId: STATUS_IMAGE_MACHINE_TYPE_MISMATCH_EXE
//
// MessageText:
//
// {Machine Type Mismatch}
// The image file %hs is valid, but is for a machine type other than the current machine.
//
#ifndef STATUS_IMAGE_MACHINE_TYPE_MISMATCH_EXE
#define STATUS_IMAGE_MACHINE_TYPE_MISMATCH_EXE ((NTSTATUS)0x40000023L)
#endif//STATUS_IMAGE_MACHINE_TYPE_MISMATCH_EXE

//
// MessageId: STATUS_NO_YIELD_PERFORMED
//
// MessageText:
//
// A yield execution was performed and no thread was available to run.
//
#ifndef STATUS_NO_YIELD_PERFORMED
#define STATUS_NO_YIELD_PERFORMED        ((NTSTATUS)0x40000024L)
#endif//STATUS_NO_YIELD_PERFORMED

//
// MessageId: STATUS_TIMER_RESUME_IGNORED
//
// MessageText:
//
// The resumable flag to a timer API was ignored.
//
#ifndef STATUS_TIMER_RESUME_IGNORED
#define STATUS_TIMER_RESUME_IGNORED      ((NTSTATUS)0x40000025L)
#endif//STATUS_TIMER_RESUME_IGNORED

//
// MessageId: STATUS_ARBITRATION_UNHANDLED
//
// MessageText:
//
// The arbiter has deferred arbitration of these resources to its parent
//
#ifndef STATUS_ARBITRATION_UNHANDLED
#define STATUS_ARBITRATION_UNHANDLED     ((NTSTATUS)0x40000026L)
#endif//STATUS_ARBITRATION_UNHANDLED

//
// MessageId: STATUS_CARDBUS_NOT_SUPPORTED
//
// MessageText:
//
// The device "%hs" has detected a CardBus card in its slot, but the firmware on this system is not configured to allow the CardBus controller to be run in CardBus mode.
// The operating system will currently accept only 16-bit (R2) pc-cards on this controller.
//
#ifndef STATUS_CARDBUS_NOT_SUPPORTED
#define STATUS_CARDBUS_NOT_SUPPORTED     ((NTSTATUS)0x40000027L)
#endif//STATUS_CARDBUS_NOT_SUPPORTED

//
// MessageId: STATUS_WX86_CREATEWX86TIB
//
// MessageText:
//
// Exception status code used by Win32 x86 emulation subsystem.
//
#ifndef STATUS_WX86_CREATEWX86TIB
#define STATUS_WX86_CREATEWX86TIB        ((NTSTATUS)0x40000028L)
#endif//STATUS_WX86_CREATEWX86TIB

//
// MessageId: STATUS_MP_PROCESSOR_MISMATCH
//
// MessageText:
//
// The CPUs in this multiprocessor system are not all the same revision level. To use all processors the operating system restricts itself to the features of the least capable processor in the system. Should problems occur with this system, contact the CPU manufacturer to see if this mix of processors is supported.
//
#ifndef STATUS_MP_PROCESSOR_MISMATCH
#define STATUS_MP_PROCESSOR_MISMATCH     ((NTSTATUS)0x40000029L)
#endif//STATUS_MP_PROCESSOR_MISMATCH

//
// MessageId: STATUS_HIBERNATED
//
// MessageText:
//
// The system was put into hibernation.
//
#ifndef STATUS_HIBERNATED
#define STATUS_HIBERNATED                ((NTSTATUS)0x4000002AL)
#endif//STATUS_HIBERNATED

//
// MessageId: STATUS_RESUME_HIBERNATION
//
// MessageText:
//
// The system was resumed from hibernation.
//
#ifndef STATUS_RESUME_HIBERNATION
#define STATUS_RESUME_HIBERNATION        ((NTSTATUS)0x4000002BL)
#endif//STATUS_RESUME_HIBERNATION

//
// MessageId: STATUS_FIRMWARE_UPDATED
//
// MessageText:
//
// Windows has detected that the system firmware (BIOS) was updated [previous firmware date = %2, current firmware date %3].
//
#ifndef STATUS_FIRMWARE_UPDATED
#define STATUS_FIRMWARE_UPDATED          ((NTSTATUS)0x4000002CL)
#endif//STATUS_FIRMWARE_UPDATED

//
// MessageId: STATUS_DRIVERS_LEAKING_LOCKED_PAGES
//
// MessageText:
//
// A device driver is leaking locked I/O pages causing system degradation. The system has automatically enabled tracking code in order to try and catch the culprit.
//
#ifndef STATUS_DRIVERS_LEAKING_LOCKED_PAGES
#define STATUS_DRIVERS_LEAKING_LOCKED_PAGES ((NTSTATUS)0x4000002DL)
#endif//STATUS_DRIVERS_LEAKING_LOCKED_PAGES

//
// MessageId: STATUS_MESSAGE_RETRIEVED
//
// MessageText:
//
// The ALPC message being canceled has already been retrieved from the queue on the other side.
//
#ifndef STATUS_MESSAGE_RETRIEVED
#define STATUS_MESSAGE_RETRIEVED         ((NTSTATUS)0x4000002EL)
#endif//STATUS_MESSAGE_RETRIEVED

//
// MessageId: STATUS_SYSTEM_POWERSTATE_TRANSITION
//
// MessageText:
//
// The system power state is transitioning from %2 to %3.
//
#ifndef STATUS_SYSTEM_POWERSTATE_TRANSITION
#define STATUS_SYSTEM_POWERSTATE_TRANSITION ((NTSTATUS)0x4000002FL)
#endif//STATUS_SYSTEM_POWERSTATE_TRANSITION

//
// MessageId: STATUS_ALPC_CHECK_COMPLETION_LIST
//
// MessageText:
//
// The receive operation was successful. Check the ALPC completion list for the received message.
//
#ifndef STATUS_ALPC_CHECK_COMPLETION_LIST
#define STATUS_ALPC_CHECK_COMPLETION_LIST ((NTSTATUS)0x40000030L)
#endif//STATUS_ALPC_CHECK_COMPLETION_LIST

//
// MessageId: STATUS_SYSTEM_POWERSTATE_COMPLEX_TRANSITION
//
// MessageText:
//
// The system power state is transitioning from %2 to %3 but could enter %4.
//
#ifndef STATUS_SYSTEM_POWERSTATE_COMPLEX_TRANSITION
#define STATUS_SYSTEM_POWERSTATE_COMPLEX_TRANSITION ((NTSTATUS)0x40000031L)
#endif//STATUS_SYSTEM_POWERSTATE_COMPLEX_TRANSITION

//
// MessageId: STATUS_ACCESS_AUDIT_BY_POLICY
//
// MessageText:
//
// Access to %1 is monitored by policy rule %2.
//
#ifndef STATUS_ACCESS_AUDIT_BY_POLICY
#define STATUS_ACCESS_AUDIT_BY_POLICY    ((NTSTATUS)0x40000032L)
#endif//STATUS_ACCESS_AUDIT_BY_POLICY

//
// MessageId: STATUS_ABANDON_HIBERFILE
//
// MessageText:
//
// A valid hibernation file has been invalidated and should be abandoned.
//
#ifndef STATUS_ABANDON_HIBERFILE
#define STATUS_ABANDON_HIBERFILE         ((NTSTATUS)0x40000033L)
#endif//STATUS_ABANDON_HIBERFILE

//
// MessageId: STATUS_BIZRULES_NOT_ENABLED
//
// MessageText:
//
// Business rule scripts are disabled for the calling application.
//
#ifndef STATUS_BIZRULES_NOT_ENABLED
#define STATUS_BIZRULES_NOT_ENABLED      ((NTSTATUS)0x40000034L)
#endif//STATUS_BIZRULES_NOT_ENABLED

//
// MessageId: STATUS_FT_READ_FROM_COPY
//
// MessageText:
//
// The specified copy of the requested data was successfully read.
//
#ifndef STATUS_FT_READ_FROM_COPY
#define STATUS_FT_READ_FROM_COPY         ((NTSTATUS)0x40000035L)
#endif//STATUS_FT_READ_FROM_COPY

//
// MessageId: STATUS_IMAGE_AT_DIFFERENT_BASE
//
// MessageText:
//
// {Image Relocated}
// An image file was mapped at a different address from the one specified in the image file but fixups will still be automatically performed on the image.
//
#ifndef STATUS_IMAGE_AT_DIFFERENT_BASE
#define STATUS_IMAGE_AT_DIFFERENT_BASE   ((NTSTATUS)0x40000036L)
#endif//STATUS_IMAGE_AT_DIFFERENT_BASE

//
// MessageId: DBG_REPLY_LATER
//
// MessageText:
//
// Debugger will reply later.
//
#ifndef DBG_REPLY_LATER
#define DBG_REPLY_LATER                  ((NTSTATUS)0x40010001L)    // winnt
#endif//DBG_REPLY_LATER

//
// MessageId: DBG_UNABLE_TO_PROVIDE_HANDLE
//
// MessageText:
//
// Debugger cannot provide handle.
//
#ifndef DBG_UNABLE_TO_PROVIDE_HANDLE
#define DBG_UNABLE_TO_PROVIDE_HANDLE     ((NTSTATUS)0x40010002L)
#endif//DBG_UNABLE_TO_PROVIDE_HANDLE

//
// MessageId: DBG_TERMINATE_THREAD
//
// MessageText:
//
// Debugger terminated thread.
//
#ifndef DBG_TERMINATE_THREAD
#define DBG_TERMINATE_THREAD             ((NTSTATUS)0x40010003L)    // winnt
#endif//DBG_TERMINATE_THREAD

//
// MessageId: DBG_TERMINATE_PROCESS
//
// MessageText:
//
// Debugger terminated process.
//
#ifndef DBG_TERMINATE_PROCESS
#define DBG_TERMINATE_PROCESS            ((NTSTATUS)0x40010004L)    // winnt
#endif//DBG_TERMINATE_PROCESS

//
// MessageId: DBG_CONTROL_C
//
// MessageText:
//
// Debugger got control C.
//
#ifndef DBG_CONTROL_C
#define DBG_CONTROL_C                    ((NTSTATUS)0x40010005L)    // winnt
#endif//DBG_CONTROL_C

//
// MessageId: DBG_PRINTEXCEPTION_C
//
// MessageText:
//
// Debugger printed exception on control C.
//
#ifndef DBG_PRINTEXCEPTION_C
#define DBG_PRINTEXCEPTION_C             ((NTSTATUS)0x40010006L)    // winnt
#endif//DBG_PRINTEXCEPTION_C

//
// MessageId: DBG_RIPEXCEPTION
//
// MessageText:
//
// Debugger received RIP exception.
//
#ifndef DBG_RIPEXCEPTION
#define DBG_RIPEXCEPTION                 ((NTSTATUS)0x40010007L)    // winnt
#endif//DBG_RIPEXCEPTION

//
// MessageId: DBG_CONTROL_BREAK
//
// MessageText:
//
// Debugger received control break.
//
#ifndef DBG_CONTROL_BREAK
#define DBG_CONTROL_BREAK                ((NTSTATUS)0x40010008L)    // winnt
#endif//DBG_CONTROL_BREAK

//
// MessageId: DBG_COMMAND_EXCEPTION
//
// MessageText:
//
// Debugger command communication exception.
//
#ifndef DBG_COMMAND_EXCEPTION
#define DBG_COMMAND_EXCEPTION            ((NTSTATUS)0x40010009L)    // winnt
#endif//DBG_COMMAND_EXCEPTION

//
// MessageId: DBG_PRINTEXCEPTION_WIDE_C
//
// MessageText:
//
// Debugger printed exception on control C.
//
#ifndef DBG_PRINTEXCEPTION_WIDE_C
#define DBG_PRINTEXCEPTION_WIDE_C        ((NTSTATUS)0x4001000AL)    // winnt
#endif//DBG_PRINTEXCEPTION_WIDE_C

//
// MessageId: STATUS_HEURISTIC_DAMAGE_POSSIBLE
//
// MessageText:
//
// The attempt to commit the Transaction completed, but it is possible that some portion of the transaction tree did not commit successfully due to heuristics.  Therefore it is possible that some data modified in the transaction may not have committed, resulting in transactional inconsistency.  If possible, check the consistency of the associated data.
//
#ifndef STATUS_HEURISTIC_DAMAGE_POSSIBLE
#define STATUS_HEURISTIC_DAMAGE_POSSIBLE ((NTSTATUS)0x40190001L)
#endif//STATUS_HEURISTIC_DAMAGE_POSSIBLE



/////////////////////////////////////////////////////////////////////////
//
// Standard Warning values
//
//
// Note:  Do NOT use the value 0x80000000L, as this is a non-portable value
//        for the NT_SUCCESS macro. Warning values start with a code of 1.
//
/////////////////////////////////////////////////////////////////////////

//
// MessageId: STATUS_GUARD_PAGE_VIOLATION
//
// MessageText:
//
// {EXCEPTION}
// Guard Page Exception
// A page of memory that marks the end of a data structure, such as a stack or an array, has been accessed.
//
#ifndef STATUS_GUARD_PAGE_VIOLATION
#define STATUS_GUARD_PAGE_VIOLATION      ((NTSTATUS)0x80000001L)    // winnt
#endif//STATUS_GUARD_PAGE_VIOLATION

//
// MessageId: STATUS_DATATYPE_MISALIGNMENT
//
// MessageText:
//
// {EXCEPTION}
// Alignment Fault
// A datatype misalignment was detected in a load or store instruction.
//
#ifndef STATUS_DATATYPE_MISALIGNMENT
#define STATUS_DATATYPE_MISALIGNMENT     ((NTSTATUS)0x80000002L)    // winnt
#endif//STATUS_DATATYPE_MISALIGNMENT

//
// MessageId: STATUS_BREAKPOINT
//
// MessageText:
//
// {EXCEPTION}
// Breakpoint
// A breakpoint has been reached.
//
#ifndef STATUS_BREAKPOINT
#define STATUS_BREAKPOINT                ((NTSTATUS)0x80000003L)    // winnt
#endif//STATUS_BREAKPOINT

//
// MessageId: STATUS_SINGLE_STEP
//
// MessageText:
//
// {EXCEPTION}
// Single Step
// A single step or trace operation has just been completed.
//
#ifndef STATUS_SINGLE_STEP
#define STATUS_SINGLE_STEP               ((NTSTATUS)0x80000004L)    // winnt
#endif//STATUS_SINGLE_STEP

//
// MessageId: STATUS_BUFFER_OVERFLOW
//
// MessageText:
//
// {Buffer Overflow}
// The data was too large to fit into the specified buffer.
//
#ifndef STATUS_BUFFER_OVERFLOW
#define STATUS_BUFFER_OVERFLOW           ((NTSTATUS)0x80000005L)
#endif//STATUS_BUFFER_OVERFLOW

//
// MessageId: STATUS_NO_MORE_FILES
//
// MessageText:
//
// {No More Files}
// No more files were found which match the file specification.
//
#ifndef STATUS_NO_MORE_FILES
#define STATUS_NO_MORE_FILES             ((NTSTATUS)0x80000006L)
#endif//STATUS_NO_MORE_FILES

//
// MessageId: STATUS_WAKE_SYSTEM_DEBUGGER
//
// MessageText:
//
// {Kernel Debugger Awakened}
// the system debugger was awakened by an interrupt.
//
#ifndef STATUS_WAKE_SYSTEM_DEBUGGER
#define STATUS_WAKE_SYSTEM_DEBUGGER      ((NTSTATUS)0x80000007L)
#endif//STATUS_WAKE_SYSTEM_DEBUGGER

//
// MessageId: STATUS_HANDLES_CLOSED
//
// MessageText:
//
// {Handles Closed}
// Handles to objects have been automatically closed as a result of the requested operation.
//
#ifndef STATUS_HANDLES_CLOSED
#define STATUS_HANDLES_CLOSED            ((NTSTATUS)0x8000000AL)
#endif//STATUS_HANDLES_CLOSED

//
// MessageId: STATUS_NO_INHERITANCE
//
// MessageText:
//
// {Non-Inheritable ACL}
// An access control list (ACL) contains no components that can be inherited.
//
#ifndef STATUS_NO_INHERITANCE
#define STATUS_NO_INHERITANCE            ((NTSTATUS)0x8000000BL)
#endif//STATUS_NO_INHERITANCE

//
// MessageId: STATUS_GUID_SUBSTITUTION_MADE
//
// MessageText:
//
// {GUID Substitution}
// During the translation of a global identifier (GUID) to a Windows security ID (SID), no administratively-defined GUID prefix was found. A substitute prefix was used, which will not compromise system security. However, this may provide a more restrictive access than intended.
//
#ifndef STATUS_GUID_SUBSTITUTION_MADE
#define STATUS_GUID_SUBSTITUTION_MADE    ((NTSTATUS)0x8000000CL)
#endif//STATUS_GUID_SUBSTITUTION_MADE

//
// MessageId: STATUS_PARTIAL_COPY
//
// MessageText:
//
// {Partial Copy}
// Due to protection conflicts not all the requested bytes could be copied.
//
#ifndef STATUS_PARTIAL_COPY
#define STATUS_PARTIAL_COPY              ((NTSTATUS)0x8000000DL)
#endif//STATUS_PARTIAL_COPY

//
// MessageId: STATUS_DEVICE_PAPER_EMPTY
//
// MessageText:
//
// {Out of Paper}
// The printer is out of paper.
//
#ifndef STATUS_DEVICE_PAPER_EMPTY
#define STATUS_DEVICE_PAPER_EMPTY        ((NTSTATUS)0x8000000EL)
#endif//STATUS_DEVICE_PAPER_EMPTY

//
// MessageId: STATUS_DEVICE_POWERED_OFF
//
// MessageText:
//
// {Device Power Is Off}
// The printer power has been turned off.
//
#ifndef STATUS_DEVICE_POWERED_OFF
#define STATUS_DEVICE_POWERED_OFF        ((NTSTATUS)0x8000000FL)
#endif//STATUS_DEVICE_POWERED_OFF

//
// MessageId: STATUS_DEVICE_OFF_LINE
//
// MessageText:
//
// {Device Offline}
// The printer has been taken offline.
//
#ifndef STATUS_DEVICE_OFF_LINE
#define STATUS_DEVICE_OFF_LINE           ((NTSTATUS)0x80000010L)
#endif//STATUS_DEVICE_OFF_LINE

//
// MessageId: STATUS_DEVICE_BUSY
//
// MessageText:
//
// {Device Busy}
// The device is currently busy.
//
#ifndef STATUS_DEVICE_BUSY
#define STATUS_DEVICE_BUSY               ((NTSTATUS)0x80000011L)
#endif//STATUS_DEVICE_BUSY

//
// MessageId: STATUS_NO_MORE_EAS
//
// MessageText:
//
// {No More EAs}
// No more extended attributes (EAs) were found for the file.
//
#ifndef STATUS_NO_MORE_EAS
#define STATUS_NO_MORE_EAS               ((NTSTATUS)0x80000012L)
#endif//STATUS_NO_MORE_EAS

//
// MessageId: STATUS_INVALID_EA_NAME
//
// MessageText:
//
// {Illegal EA}
// The specified extended attribute (EA) name contains at least one illegal character.
//
#ifndef STATUS_INVALID_EA_NAME
#define STATUS_INVALID_EA_NAME           ((NTSTATUS)0x80000013L)
#endif//STATUS_INVALID_EA_NAME

//
// MessageId: STATUS_EA_LIST_INCONSISTENT
//
// MessageText:
//
// {Inconsistent EA List}
// The extended attribute (EA) list is inconsistent.
//
#ifndef STATUS_EA_LIST_INCONSISTENT
#define STATUS_EA_LIST_INCONSISTENT      ((NTSTATUS)0x80000014L)
#endif//STATUS_EA_LIST_INCONSISTENT

//
// MessageId: STATUS_INVALID_EA_FLAG
//
// MessageText:
//
// {Invalid EA Flag}
// An invalid extended attribute (EA) flag was set.
//
#ifndef STATUS_INVALID_EA_FLAG
#define STATUS_INVALID_EA_FLAG           ((NTSTATUS)0x80000015L)
#endif//STATUS_INVALID_EA_FLAG

//
// MessageId: STATUS_VERIFY_REQUIRED
//
// MessageText:
//
// {Verifying Disk}
// The media has changed and a verify operation is in progress so no reads or writes may be performed to the device, except those used in the verify operation.
//
#ifndef STATUS_VERIFY_REQUIRED
#define STATUS_VERIFY_REQUIRED           ((NTSTATUS)0x80000016L)
#endif//STATUS_VERIFY_REQUIRED

//
// MessageId: STATUS_EXTRANEOUS_INFORMATION
//
// MessageText:
//
// {Too Much Information}
// The specified access control list (ACL) contained more information than was expected.
//
#ifndef STATUS_EXTRANEOUS_INFORMATION
#define STATUS_EXTRANEOUS_INFORMATION    ((NTSTATUS)0x80000017L)
#endif//STATUS_EXTRANEOUS_INFORMATION

//
// MessageId: STATUS_RXACT_COMMIT_NECESSARY
//
// MessageText:
//
// This warning level status indicates that the transaction state already exists for the registry sub-tree, but that a transaction commit was previously aborted.
// The commit has NOT been completed, but has not been rolled back either (so it may still be committed if desired).
//
#ifndef STATUS_RXACT_COMMIT_NECESSARY
#define STATUS_RXACT_COMMIT_NECESSARY    ((NTSTATUS)0x80000018L)
#endif//STATUS_RXACT_COMMIT_NECESSARY

//
// MessageId: STATUS_NO_MORE_ENTRIES
//
// MessageText:
//
// {No More Entries}
// No more entries are available from an enumeration operation.
//
#ifndef STATUS_NO_MORE_ENTRIES
#define STATUS_NO_MORE_ENTRIES           ((NTSTATUS)0x8000001AL)
#endif//STATUS_NO_MORE_ENTRIES

//
// MessageId: STATUS_FILEMARK_DETECTED
//
// MessageText:
//
// {Filemark Found}
// A filemark was detected.
//
#ifndef STATUS_FILEMARK_DETECTED
#define STATUS_FILEMARK_DETECTED         ((NTSTATUS)0x8000001BL)
#endif//STATUS_FILEMARK_DETECTED

//
// MessageId: STATUS_MEDIA_CHANGED
//
// MessageText:
//
// {Media Changed}
// The media may have changed.
//
#ifndef STATUS_MEDIA_CHANGED
#define STATUS_MEDIA_CHANGED             ((NTSTATUS)0x8000001CL)
#endif//STATUS_MEDIA_CHANGED

//
// MessageId: STATUS_BUS_RESET
//
// MessageText:
//
// {I/O Bus Reset}
// An I/O bus reset was detected.
//
#ifndef STATUS_BUS_RESET
#define STATUS_BUS_RESET                 ((NTSTATUS)0x8000001DL)
#endif//STATUS_BUS_RESET

//
// MessageId: STATUS_END_OF_MEDIA
//
// MessageText:
//
// {End of Media}
// The end of the media was encountered.
//
#ifndef STATUS_END_OF_MEDIA
#define STATUS_END_OF_MEDIA              ((NTSTATUS)0x8000001EL)
#endif//STATUS_END_OF_MEDIA

//
// MessageId: STATUS_BEGINNING_OF_MEDIA
//
// MessageText:
//
// Beginning of tape or partition has been detected.
//
#ifndef STATUS_BEGINNING_OF_MEDIA
#define STATUS_BEGINNING_OF_MEDIA        ((NTSTATUS)0x8000001FL)
#endif//STATUS_BEGINNING_OF_MEDIA

//
// MessageId: STATUS_MEDIA_CHECK
//
// MessageText:
//
// {Media Changed}
// The media may have changed.
//
#ifndef STATUS_MEDIA_CHECK
#define STATUS_MEDIA_CHECK               ((NTSTATUS)0x80000020L)
#endif//STATUS_MEDIA_CHECK

//
// MessageId: STATUS_SETMARK_DETECTED
//
// MessageText:
//
// A tape access reached a setmark.
//
#ifndef STATUS_SETMARK_DETECTED
#define STATUS_SETMARK_DETECTED          ((NTSTATUS)0x80000021L)
#endif//STATUS_SETMARK_DETECTED

//
// MessageId: STATUS_NO_DATA_DETECTED
//
// MessageText:
//
// During a tape access, the end of the data written is reached.
//
#ifndef STATUS_NO_DATA_DETECTED
#define STATUS_NO_DATA_DETECTED          ((NTSTATUS)0x80000022L)
#endif//STATUS_NO_DATA_DETECTED

//
// MessageId: STATUS_REDIRECTOR_HAS_OPEN_HANDLES
//
// MessageText:
//
// The redirector is in use and cannot be unloaded.
//
#ifndef STATUS_REDIRECTOR_HAS_OPEN_HANDLES
#define STATUS_REDIRECTOR_HAS_OPEN_HANDLES ((NTSTATUS)0x80000023L)
#endif//STATUS_REDIRECTOR_HAS_OPEN_HANDLES

//
// MessageId: STATUS_SERVER_HAS_OPEN_HANDLES
//
// MessageText:
//
// The server is in use and cannot be unloaded.
//
#ifndef STATUS_SERVER_HAS_OPEN_HANDLES
#define STATUS_SERVER_HAS_OPEN_HANDLES   ((NTSTATUS)0x80000024L)
#endif//STATUS_SERVER_HAS_OPEN_HANDLES

//
// MessageId: STATUS_ALREADY_DISCONNECTED
//
// MessageText:
//
// The specified connection has already been disconnected.
//
#ifndef STATUS_ALREADY_DISCONNECTED
#define STATUS_ALREADY_DISCONNECTED      ((NTSTATUS)0x80000025L)
#endif//STATUS_ALREADY_DISCONNECTED

//
// MessageId: STATUS_LONGJUMP
//
// MessageText:
//
// A long jump has been executed.
//
#ifndef STATUS_LONGJUMP
#define STATUS_LONGJUMP                  ((NTSTATUS)0x80000026L)    // winnt
#endif//STATUS_LONGJUMP

//
// MessageId: STATUS_CLEANER_CARTRIDGE_INSTALLED
//
// MessageText:
//
// A cleaner cartridge is present in the tape library.
//
#ifndef STATUS_CLEANER_CARTRIDGE_INSTALLED
#define STATUS_CLEANER_CARTRIDGE_INSTALLED ((NTSTATUS)0x80000027L)
#endif//STATUS_CLEANER_CARTRIDGE_INSTALLED

//
// MessageId: STATUS_PLUGPLAY_QUERY_VETOED
//
// MessageText:
//
// The Plug and Play query operation was not successful.
//
#ifndef STATUS_PLUGPLAY_QUERY_VETOED
#define STATUS_PLUGPLAY_QUERY_VETOED     ((NTSTATUS)0x80000028L)
#endif//STATUS_PLUGPLAY_QUERY_VETOED

//
// MessageId: STATUS_UNWIND_CONSOLIDATE
//
// MessageText:
//
// A frame consolidation has been executed.
//
#ifndef STATUS_UNWIND_CONSOLIDATE
#define STATUS_UNWIND_CONSOLIDATE        ((NTSTATUS)0x80000029L)    // winnt
#endif//STATUS_UNWIND_CONSOLIDATE

//
// MessageId: STATUS_REGISTRY_HIVE_RECOVERED
//
// MessageText:
//
// {Registry Hive Recovered}
// Registry hive (file):
// %hs
// was corrupted and it has been recovered. Some data might have been lost.
//
#ifndef STATUS_REGISTRY_HIVE_RECOVERED
#define STATUS_REGISTRY_HIVE_RECOVERED   ((NTSTATUS)0x8000002AL)
#endif//STATUS_REGISTRY_HIVE_RECOVERED

//
// MessageId: STATUS_DLL_MIGHT_BE_INSECURE
//
// MessageText:
//
// The application is attempting to run executable code from the module %hs. This may be insecure. An alternative, %hs, is available. Should the application use the secure module %hs?
//
#ifndef STATUS_DLL_MIGHT_BE_INSECURE
#define STATUS_DLL_MIGHT_BE_INSECURE     ((NTSTATUS)0x8000002BL)
#endif//STATUS_DLL_MIGHT_BE_INSECURE

//
// MessageId: STATUS_DLL_MIGHT_BE_INCOMPATIBLE
//
// MessageText:
//
// The application is loading executable code from the module %hs. This is secure, but may be incompatible with previous releases of the operating system. An alternative, %hs, is available. Should the application use the secure module %hs?
//
#ifndef STATUS_DLL_MIGHT_BE_INCOMPATIBLE
#define STATUS_DLL_MIGHT_BE_INCOMPATIBLE ((NTSTATUS)0x8000002CL)
#endif//STATUS_DLL_MIGHT_BE_INCOMPATIBLE

//
// MessageId: STATUS_STOPPED_ON_SYMLINK
//
// MessageText:
//
// The create operation stopped after reaching a symbolic link.
//
#ifndef STATUS_STOPPED_ON_SYMLINK
#define STATUS_STOPPED_ON_SYMLINK        ((NTSTATUS)0x8000002DL)
#endif//STATUS_STOPPED_ON_SYMLINK

//
// MessageId: STATUS_CANNOT_GRANT_REQUESTED_OPLOCK
//
// MessageText:
//
// An oplock of the requested level cannot be granted.  An oplock of a lower level may be available.
//
#ifndef STATUS_CANNOT_GRANT_REQUESTED_OPLOCK
#define STATUS_CANNOT_GRANT_REQUESTED_OPLOCK ((NTSTATUS)0x8000002EL)
#endif//STATUS_CANNOT_GRANT_REQUESTED_OPLOCK

//
// MessageId: STATUS_NO_ACE_CONDITION
//
// MessageText:
//
// {No ACE Condition}
// The specified access control entry (ACE) does not contain a condition.
//
#ifndef STATUS_NO_ACE_CONDITION
#define STATUS_NO_ACE_CONDITION          ((NTSTATUS)0x8000002FL)
#endif//STATUS_NO_ACE_CONDITION

//
// MessageId: STATUS_DEVICE_SUPPORT_IN_PROGRESS
//
// MessageText:
//
// {Support Being Determined}
// Device's command support detection is in progress.
//
#ifndef STATUS_DEVICE_SUPPORT_IN_PROGRESS
#define STATUS_DEVICE_SUPPORT_IN_PROGRESS ((NTSTATUS)0x80000030L)
#endif//STATUS_DEVICE_SUPPORT_IN_PROGRESS

//
// MessageId: STATUS_DEVICE_POWER_CYCLE_REQUIRED
//
// MessageText:
//
// The device needs to be power cycled.
//
#ifndef STATUS_DEVICE_POWER_CYCLE_REQUIRED
#define STATUS_DEVICE_POWER_CYCLE_REQUIRED ((NTSTATUS)0x80000031L)
#endif//STATUS_DEVICE_POWER_CYCLE_REQUIRED

//
// MessageId: STATUS_NO_WORK_DONE
//
// MessageText:
//
// The action requested resulted in no work being done. Error-style clean-up has been performed.
//
#ifndef STATUS_NO_WORK_DONE
#define STATUS_NO_WORK_DONE              ((NTSTATUS)0x80000032L)
#endif//STATUS_NO_WORK_DONE

//
// MessageId: DBG_EXCEPTION_NOT_HANDLED
//
// MessageText:
//
// Debugger did not handle the exception.
//
#ifndef DBG_EXCEPTION_NOT_HANDLED
#define DBG_EXCEPTION_NOT_HANDLED        ((NTSTATUS)0x80010001L)    // winnt
#endif//DBG_EXCEPTION_NOT_HANDLED

//
// MessageId: STATUS_CLUSTER_NODE_ALREADY_UP
//
// MessageText:
//
// The cluster node is already up.
//
#ifndef STATUS_CLUSTER_NODE_ALREADY_UP
#define STATUS_CLUSTER_NODE_ALREADY_UP   ((NTSTATUS)0x80130001L)
#endif//STATUS_CLUSTER_NODE_ALREADY_UP

//
// MessageId: STATUS_CLUSTER_NODE_ALREADY_DOWN
//
// MessageText:
//
// The cluster node is already down.
//
#ifndef STATUS_CLUSTER_NODE_ALREADY_DOWN
#define STATUS_CLUSTER_NODE_ALREADY_DOWN ((NTSTATUS)0x80130002L)
#endif//STATUS_CLUSTER_NODE_ALREADY_DOWN

//
// MessageId: STATUS_CLUSTER_NETWORK_ALREADY_ONLINE
//
// MessageText:
//
// The cluster network is already online.
//
#ifndef STATUS_CLUSTER_NETWORK_ALREADY_ONLINE
#define STATUS_CLUSTER_NETWORK_ALREADY_ONLINE ((NTSTATUS)0x80130003L)
#endif//STATUS_CLUSTER_NETWORK_ALREADY_ONLINE

//
// MessageId: STATUS_CLUSTER_NETWORK_ALREADY_OFFLINE
//
// MessageText:
//
// The cluster network is already offline.
//
#ifndef STATUS_CLUSTER_NETWORK_ALREADY_OFFLINE
#define STATUS_CLUSTER_NETWORK_ALREADY_OFFLINE ((NTSTATUS)0x80130004L)
#endif//STATUS_CLUSTER_NETWORK_ALREADY_OFFLINE

//
// MessageId: STATUS_CLUSTER_NODE_ALREADY_MEMBER
//
// MessageText:
//
// The cluster node is already a member of the cluster.
//
#ifndef STATUS_CLUSTER_NODE_ALREADY_MEMBER
#define STATUS_CLUSTER_NODE_ALREADY_MEMBER ((NTSTATUS)0x80130005L)
#endif//STATUS_CLUSTER_NODE_ALREADY_MEMBER

//
// MessageId: STATUS_FLT_BUFFER_TOO_SMALL
//
// MessageText:
//
// {Buffer too small}
// The buffer is too small to contain the entry. No information has been written to the buffer.
//
#ifndef STATUS_FLT_BUFFER_TOO_SMALL
#define STATUS_FLT_BUFFER_TOO_SMALL      ((NTSTATUS)0x801C0001L)
#endif//STATUS_FLT_BUFFER_TOO_SMALL

//
// MessageId: STATUS_FVE_PARTIAL_METADATA
//
// MessageText:
//
// Volume Metadata read or write is incomplete.
//
#ifndef STATUS_FVE_PARTIAL_METADATA
#define STATUS_FVE_PARTIAL_METADATA      ((NTSTATUS)0x80210001L)
#endif//STATUS_FVE_PARTIAL_METADATA

//
// MessageId: STATUS_FVE_TRANSIENT_STATE
//
// MessageText:
//
// BitLocker encryption keys were ignored because the volume was in a transient state.
//
#ifndef STATUS_FVE_TRANSIENT_STATE
#define STATUS_FVE_TRANSIENT_STATE       ((NTSTATUS)0x80210002L)
#endif//STATUS_FVE_TRANSIENT_STATE

/*++

 MessageId's 0xcf00 - 0xcfff (inclusive) are for Cloud Files specific warning messages.

--*/
//
// MessageId: STATUS_CLOUD_FILE_PROPERTY_BLOB_CHECKSUM_MISMATCH
//
// MessageText:
//
// The cloud file property is possibly corrupt. The on-disk checksum does not match the computed checksum.
//
#ifndef STATUS_CLOUD_FILE_PROPERTY_BLOB_CHECKSUM_MISMATCH
#define STATUS_CLOUD_FILE_PROPERTY_BLOB_CHECKSUM_MISMATCH ((NTSTATUS)0x8000CF00L)
#endif//STATUS_CLOUD_FILE_PROPERTY_BLOB_CHECKSUM_MISMATCH

/*++

 End of Cloud Files specific warning messages.

--*/
/////////////////////////////////////////////////////////////////////////
//
//  Standard Error values
//
/////////////////////////////////////////////////////////////////////////

//
// MessageId: STATUS_UNSUCCESSFUL
//
// MessageText:
//
// {Operation Failed}
// The requested operation was unsuccessful.
//
#ifndef STATUS_UNSUCCESSFUL
#define STATUS_UNSUCCESSFUL              ((NTSTATUS)0xC0000001L)
#endif//STATUS_UNSUCCESSFUL

//
// MessageId: STATUS_NOT_IMPLEMENTED
//
// MessageText:
//
// {Not Implemented}
// The requested operation is not implemented.
//
#ifndef STATUS_NOT_IMPLEMENTED
#define STATUS_NOT_IMPLEMENTED           ((NTSTATUS)0xC0000002L)
#endif//STATUS_NOT_IMPLEMENTED

//
// MessageId: STATUS_INVALID_INFO_CLASS
//
// MessageText:
//
// {Invalid Parameter}
// The specified information class is not a valid information class for the specified object.
//
#ifndef STATUS_INVALID_INFO_CLASS
#define STATUS_INVALID_INFO_CLASS        ((NTSTATUS)0xC0000003L)    // ntsubauth
#endif//STATUS_INVALID_INFO_CLASS

//
// MessageId: STATUS_INFO_LENGTH_MISMATCH
//
// MessageText:
//
// The specified information record length does not match the length required for the specified information class.
//
#ifndef STATUS_INFO_LENGTH_MISMATCH
#define STATUS_INFO_LENGTH_MISMATCH      ((NTSTATUS)0xC0000004L)
#endif//STATUS_INFO_LENGTH_MISMATCH

//
// MessageId: STATUS_ACCESS_VIOLATION
//
// MessageText:
//
// The instruction at 0x%p referenced memory at 0x%p. The memory could not be %s.
//
#ifndef STATUS_ACCESS_VIOLATION
#define STATUS_ACCESS_VIOLATION          ((NTSTATUS)0xC0000005L)    // winnt
#endif//STATUS_ACCESS_VIOLATION

//
// MessageId: STATUS_IN_PAGE_ERROR
//
// MessageText:
//
// The instruction at 0x%p referenced memory at 0x%p. The required data was not placed into memory because of an I/O error status of 0x%x.
//
#ifndef STATUS_IN_PAGE_ERROR
#define STATUS_IN_PAGE_ERROR             ((NTSTATUS)0xC0000006L)    // winnt
#endif//STATUS_IN_PAGE_ERROR

//
// MessageId: STATUS_PAGEFILE_QUOTA
//
// MessageText:
//
// The pagefile quota for the process has been exhausted.
//
#ifndef STATUS_PAGEFILE_QUOTA
#define STATUS_PAGEFILE_QUOTA            ((NTSTATUS)0xC0000007L)
#endif//STATUS_PAGEFILE_QUOTA

//
// MessageId: STATUS_INVALID_HANDLE
//
// MessageText:
//
// An invalid HANDLE was specified.
//
#ifndef STATUS_INVALID_HANDLE
#define STATUS_INVALID_HANDLE            ((NTSTATUS)0xC0000008L)    // winnt
#endif//STATUS_INVALID_HANDLE

//
// MessageId: STATUS_BAD_INITIAL_STACK
//
// MessageText:
//
// An invalid initial stack was specified in a call to NtCreateThread.
//
#ifndef STATUS_BAD_INITIAL_STACK
#define STATUS_BAD_INITIAL_STACK         ((NTSTATUS)0xC0000009L)
#endif//STATUS_BAD_INITIAL_STACK

//
// MessageId: STATUS_BAD_INITIAL_PC
//
// MessageText:
//
// An invalid initial start address was specified in a call to NtCreateThread.
//
#ifndef STATUS_BAD_INITIAL_PC
#define STATUS_BAD_INITIAL_PC            ((NTSTATUS)0xC000000AL)
#endif//STATUS_BAD_INITIAL_PC

//
// MessageId: STATUS_INVALID_CID
//
// MessageText:
//
// An invalid Client ID was specified.
//
#ifndef STATUS_INVALID_CID
#define STATUS_INVALID_CID               ((NTSTATUS)0xC000000BL)
#endif//STATUS_INVALID_CID

//
// MessageId: STATUS_TIMER_NOT_CANCELED
//
// MessageText:
//
// An attempt was made to cancel or set a timer that has an associated APC and the subject thread is not the thread that originally set the timer with an associated APC routine.
//
#ifndef STATUS_TIMER_NOT_CANCELED
#define STATUS_TIMER_NOT_CANCELED        ((NTSTATUS)0xC000000CL)
#endif//STATUS_TIMER_NOT_CANCELED

//
// MessageId: STATUS_INVALID_PARAMETER
//
// MessageText:
//
// An invalid parameter was passed to a service or function.
//
#ifndef STATUS_INVALID_PARAMETER
#define STATUS_INVALID_PARAMETER         ((NTSTATUS)0xC000000DL)    // winnt
#endif//STATUS_INVALID_PARAMETER

//
// MessageId: STATUS_NO_SUCH_DEVICE
//
// MessageText:
//
// A device which does not exist was specified.
//
#ifndef STATUS_NO_SUCH_DEVICE
#define STATUS_NO_SUCH_DEVICE            ((NTSTATUS)0xC000000EL)
#endif//STATUS_NO_SUCH_DEVICE

//
// MessageId: STATUS_NO_SUCH_FILE
//
// MessageText:
//
// {File Not Found}
// The file %hs does not exist.
//
#ifndef STATUS_NO_SUCH_FILE
#define STATUS_NO_SUCH_FILE              ((NTSTATUS)0xC000000FL)
#endif//STATUS_NO_SUCH_FILE

//
// MessageId: STATUS_INVALID_DEVICE_REQUEST
//
// MessageText:
//
// The specified request is not a valid operation for the target device.
//
#ifndef STATUS_INVALID_DEVICE_REQUEST
#define STATUS_INVALID_DEVICE_REQUEST    ((NTSTATUS)0xC0000010L)
#endif//STATUS_INVALID_DEVICE_REQUEST

//
// MessageId: STATUS_END_OF_FILE
//
// MessageText:
//
// The end-of-file marker has been reached. There is no valid data in the file beyond this marker.
//
#ifndef STATUS_END_OF_FILE
#define STATUS_END_OF_FILE               ((NTSTATUS)0xC0000011L)
#endif//STATUS_END_OF_FILE

//
// MessageId: STATUS_WRONG_VOLUME
//
// MessageText:
//
// {Wrong Volume}
// The wrong volume is in the drive.
// Please insert volume %hs into drive %hs.
//
#ifndef STATUS_WRONG_VOLUME
#define STATUS_WRONG_VOLUME              ((NTSTATUS)0xC0000012L)
#endif//STATUS_WRONG_VOLUME

//
// MessageId: STATUS_NO_MEDIA_IN_DEVICE
//
// MessageText:
//
// {No Disk}
// There is no disk in the drive.
// Please insert a disk into drive %hs.
//
#ifndef STATUS_NO_MEDIA_IN_DEVICE
#define STATUS_NO_MEDIA_IN_DEVICE        ((NTSTATUS)0xC0000013L)
#endif//STATUS_NO_MEDIA_IN_DEVICE

//
// MessageId: STATUS_UNRECOGNIZED_MEDIA
//
// MessageText:
//
// {Unknown Disk Format}
// The disk in drive %hs is not formatted properly.
// Please check the disk, and reformat if necessary.
//
#ifndef STATUS_UNRECOGNIZED_MEDIA
#define STATUS_UNRECOGNIZED_MEDIA        ((NTSTATUS)0xC0000014L)
#endif//STATUS_UNRECOGNIZED_MEDIA

//
// MessageId: STATUS_NONEXISTENT_SECTOR
//
// MessageText:
//
// {Sector Not Found}
// The specified sector does not exist.
//
#ifndef STATUS_NONEXISTENT_SECTOR
#define STATUS_NONEXISTENT_SECTOR        ((NTSTATUS)0xC0000015L)
#endif//STATUS_NONEXISTENT_SECTOR

//
// MessageId: STATUS_MORE_PROCESSING_REQUIRED
//
// MessageText:
//
// {Still Busy}
// The specified I/O request packet (IRP) cannot be disposed of because the I/O operation is not complete.
//
#ifndef STATUS_MORE_PROCESSING_REQUIRED
#define STATUS_MORE_PROCESSING_REQUIRED  ((NTSTATUS)0xC0000016L)
#endif//STATUS_MORE_PROCESSING_REQUIRED

//
// MessageId: STATUS_NO_MEMORY
//
// MessageText:
//
// {Not Enough Quota}
// Not enough virtual memory or paging file quota is available to complete the specified operation.
//
#ifndef STATUS_NO_MEMORY
#define STATUS_NO_MEMORY                 ((NTSTATUS)0xC0000017L)    // winnt
#endif//STATUS_NO_MEMORY

//
// MessageId: STATUS_CONFLICTING_ADDRESSES
//
// MessageText:
//
// {Conflicting Address Range}
// The specified address range conflicts with the address space.
//
#ifndef STATUS_CONFLICTING_ADDRESSES
#define STATUS_CONFLICTING_ADDRESSES     ((NTSTATUS)0xC0000018L)
#endif//STATUS_CONFLICTING_ADDRESSES

//
// MessageId: STATUS_NOT_MAPPED_VIEW
//
// MessageText:
//
// Address range to unmap is not a mapped view.
//
#ifndef STATUS_NOT_MAPPED_VIEW
#define STATUS_NOT_MAPPED_VIEW           ((NTSTATUS)0xC0000019L)
#endif//STATUS_NOT_MAPPED_VIEW

//
// MessageId: STATUS_UNABLE_TO_FREE_VM
//
// MessageText:
//
// Virtual memory cannot be freed.
//
#ifndef STATUS_UNABLE_TO_FREE_VM
#define STATUS_UNABLE_TO_FREE_VM         ((NTSTATUS)0xC000001AL)
#endif//STATUS_UNABLE_TO_FREE_VM

//
// MessageId: STATUS_UNABLE_TO_DELETE_SECTION
//
// MessageText:
//
// Specified section cannot be deleted.
//
#ifndef STATUS_UNABLE_TO_DELETE_SECTION
#define STATUS_UNABLE_TO_DELETE_SECTION  ((NTSTATUS)0xC000001BL)
#endif//STATUS_UNABLE_TO_DELETE_SECTION

//
// MessageId: STATUS_INVALID_SYSTEM_SERVICE
//
// MessageText:
//
// An invalid system service was specified in a system service call.
//
#ifndef STATUS_INVALID_SYSTEM_SERVICE
#define STATUS_INVALID_SYSTEM_SERVICE    ((NTSTATUS)0xC000001CL)
#endif//STATUS_INVALID_SYSTEM_SERVICE

//
// MessageId: STATUS_ILLEGAL_INSTRUCTION
//
// MessageText:
//
// {EXCEPTION}
// Illegal Instruction
// An attempt was made to execute an illegal instruction.
//
#ifndef STATUS_ILLEGAL_INSTRUCTION
#define STATUS_ILLEGAL_INSTRUCTION       ((NTSTATUS)0xC000001DL)    // winnt
#endif//STATUS_ILLEGAL_INSTRUCTION

//
// MessageId: STATUS_INVALID_LOCK_SEQUENCE
//
// MessageText:
//
// {Invalid Lock Sequence}
// An attempt was made to execute an invalid lock sequence.
//
#ifndef STATUS_INVALID_LOCK_SEQUENCE
#define STATUS_INVALID_LOCK_SEQUENCE     ((NTSTATUS)0xC000001EL)
#endif//STATUS_INVALID_LOCK_SEQUENCE

//
// MessageId: STATUS_INVALID_VIEW_SIZE
//
// MessageText:
//
// {Invalid Mapping}
// An attempt was made to create a view for a section which is bigger than the section.
//
#ifndef STATUS_INVALID_VIEW_SIZE
#define STATUS_INVALID_VIEW_SIZE         ((NTSTATUS)0xC000001FL)
#endif//STATUS_INVALID_VIEW_SIZE

//
// MessageId: STATUS_INVALID_FILE_FOR_SECTION
//
// MessageText:
//
// {Bad File}
// The attributes of the specified mapping file for a section of memory cannot be read.
//
#ifndef STATUS_INVALID_FILE_FOR_SECTION
#define STATUS_INVALID_FILE_FOR_SECTION  ((NTSTATUS)0xC0000020L)
#endif//STATUS_INVALID_FILE_FOR_SECTION

//
// MessageId: STATUS_ALREADY_COMMITTED
//
// MessageText:
//
// {Already Committed}
// The specified address range is already committed.
//
#ifndef STATUS_ALREADY_COMMITTED
#define STATUS_ALREADY_COMMITTED         ((NTSTATUS)0xC0000021L)
#endif//STATUS_ALREADY_COMMITTED

//
// MessageId: STATUS_ACCESS_DENIED
//
// MessageText:
//
// {Access Denied}
// A process has requested access to an object, but has not been granted those access rights.
//
#ifndef STATUS_ACCESS_DENIED
#define STATUS_ACCESS_DENIED             ((NTSTATUS)0xC0000022L)
#endif//STATUS_ACCESS_DENIED

//
// MessageId: STATUS_BUFFER_TOO_SMALL
//
// MessageText:
//
// {Buffer Too Small}
// The buffer is too small to contain the entry. No information has been written to the buffer.
//
#ifndef STATUS_BUFFER_TOO_SMALL
#define STATUS_BUFFER_TOO_SMALL          ((NTSTATUS)0xC0000023L)
#endif//STATUS_BUFFER_TOO_SMALL

//
// MessageId: STATUS_OBJECT_TYPE_MISMATCH
//
// MessageText:
//
// {Wrong Type}
// There is a mismatch between the type of object required by the requested operation and the type of object that is specified in the request.
//
#ifndef STATUS_OBJECT_TYPE_MISMATCH
#define STATUS_OBJECT_TYPE_MISMATCH      ((NTSTATUS)0xC0000024L)
#endif//STATUS_OBJECT_TYPE_MISMATCH

//
// MessageId: STATUS_NONCONTINUABLE_EXCEPTION
//
// MessageText:
//
// {EXCEPTION}
// Cannot Continue
// Windows cannot continue from this exception.
//
#ifndef STATUS_NONCONTINUABLE_EXCEPTION
#define STATUS_NONCONTINUABLE_EXCEPTION  ((NTSTATUS)0xC0000025L)    // winnt
#endif//STATUS_NONCONTINUABLE_EXCEPTION

//
// MessageId: STATUS_INVALID_DISPOSITION
//
// MessageText:
//
// An invalid exception disposition was returned by an exception handler.
//
#ifndef STATUS_INVALID_DISPOSITION
#define STATUS_INVALID_DISPOSITION       ((NTSTATUS)0xC0000026L)    // winnt
#endif//STATUS_INVALID_DISPOSITION

//
// MessageId: STATUS_UNWIND
//
// MessageText:
//
// Unwind exception code.
//
#ifndef STATUS_UNWIND
#define STATUS_UNWIND                    ((NTSTATUS)0xC0000027L)
#endif//STATUS_UNWIND

//
// MessageId: STATUS_BAD_STACK
//
// MessageText:
//
// An invalid or unaligned stack was encountered during an unwind operation.
//
#ifndef STATUS_BAD_STACK
#define STATUS_BAD_STACK                 ((NTSTATUS)0xC0000028L)
#endif//STATUS_BAD_STACK

//
// MessageId: STATUS_INVALID_UNWIND_TARGET
//
// MessageText:
//
// An invalid unwind target was encountered during an unwind operation.
//
#ifndef STATUS_INVALID_UNWIND_TARGET
#define STATUS_INVALID_UNWIND_TARGET     ((NTSTATUS)0xC0000029L)
#endif//STATUS_INVALID_UNWIND_TARGET

//
// MessageId: STATUS_NOT_LOCKED
//
// MessageText:
//
// An attempt was made to unlock a page of memory which was not locked.
//
#ifndef STATUS_NOT_LOCKED
#define STATUS_NOT_LOCKED                ((NTSTATUS)0xC000002AL)
#endif//STATUS_NOT_LOCKED

//
// MessageId: STATUS_PARITY_ERROR
//
// MessageText:
//
// Device parity error on I/O operation.
//
#ifndef STATUS_PARITY_ERROR
#define STATUS_PARITY_ERROR              ((NTSTATUS)0xC000002BL)
#endif//STATUS_PARITY_ERROR

//
// MessageId: STATUS_UNABLE_TO_DECOMMIT_VM
//
// MessageText:
//
// An attempt was made to decommit uncommitted virtual memory.
//
#ifndef STATUS_UNABLE_TO_DECOMMIT_VM
#define STATUS_UNABLE_TO_DECOMMIT_VM     ((NTSTATUS)0xC000002CL)
#endif//STATUS_UNABLE_TO_DECOMMIT_VM

//
// MessageId: STATUS_NOT_COMMITTED
//
// MessageText:
//
// An attempt was made to change the attributes on memory that has not been committed.
//
#ifndef STATUS_NOT_COMMITTED
#define STATUS_NOT_COMMITTED             ((NTSTATUS)0xC000002DL)
#endif//STATUS_NOT_COMMITTED

//
// MessageId: STATUS_INVALID_PORT_ATTRIBUTES
//
// MessageText:
//
// Invalid Object Attributes specified to NtCreatePort or invalid Port Attributes specified to NtConnectPort
//
#ifndef STATUS_INVALID_PORT_ATTRIBUTES
#define STATUS_INVALID_PORT_ATTRIBUTES   ((NTSTATUS)0xC000002EL)
#endif//STATUS_INVALID_PORT_ATTRIBUTES

//
// MessageId: STATUS_PORT_MESSAGE_TOO_LONG
//
// MessageText:
//
// Length of message passed to NtRequestPort or NtRequestWaitReplyPort was longer than the maximum message allowed by the port.
//
#ifndef STATUS_PORT_MESSAGE_TOO_LONG
#define STATUS_PORT_MESSAGE_TOO_LONG     ((NTSTATUS)0xC000002FL)
#endif//STATUS_PORT_MESSAGE_TOO_LONG

//
// MessageId: STATUS_INVALID_PARAMETER_MIX
//
// MessageText:
//
// An invalid combination of parameters was specified.
//
#ifndef STATUS_INVALID_PARAMETER_MIX
#define STATUS_INVALID_PARAMETER_MIX     ((NTSTATUS)0xC0000030L)
#endif//STATUS_INVALID_PARAMETER_MIX

//
// MessageId: STATUS_INVALID_QUOTA_LOWER
//
// MessageText:
//
// An attempt was made to lower a quota limit below the current usage.
//
#ifndef STATUS_INVALID_QUOTA_LOWER
#define STATUS_INVALID_QUOTA_LOWER       ((NTSTATUS)0xC0000031L)
#endif//STATUS_INVALID_QUOTA_LOWER

//
// MessageId: STATUS_DISK_CORRUPT_ERROR
//
// MessageText:
//
// {Corrupt Disk}
// The file system structure on the disk is corrupt and unusable.
// Please run the Chkdsk utility on the volume %hs.
//
#ifndef STATUS_DISK_CORRUPT_ERROR
#define STATUS_DISK_CORRUPT_ERROR        ((NTSTATUS)0xC0000032L)
#endif//STATUS_DISK_CORRUPT_ERROR

//
// MessageId: STATUS_OBJECT_NAME_INVALID
//
// MessageText:
//
// Object Name invalid.
//
#ifndef STATUS_OBJECT_NAME_INVALID
#define STATUS_OBJECT_NAME_INVALID       ((NTSTATUS)0xC0000033L)
#endif//STATUS_OBJECT_NAME_INVALID

//
// MessageId: STATUS_OBJECT_NAME_NOT_FOUND
//
// MessageText:
//
// Object Name not found.
//
#ifndef STATUS_OBJECT_NAME_NOT_FOUND
#define STATUS_OBJECT_NAME_NOT_FOUND     ((NTSTATUS)0xC0000034L)
#endif//STATUS_OBJECT_NAME_NOT_FOUND

//
// MessageId: STATUS_OBJECT_NAME_COLLISION
//
// MessageText:
//
// Object Name already exists.
//
#ifndef STATUS_OBJECT_NAME_COLLISION
#define STATUS_OBJECT_NAME_COLLISION     ((NTSTATUS)0xC0000035L)
#endif//STATUS_OBJECT_NAME_COLLISION

//
// MessageId: STATUS_PORT_DO_NOT_DISTURB
//
// MessageText:
//
// A port with the 'do not disturb' flag set attempted to send a message to a port in a suspended process.
// The process was not woken, and the message was not delivered.
//
#ifndef STATUS_PORT_DO_NOT_DISTURB
#define STATUS_PORT_DO_NOT_DISTURB       ((NTSTATUS)0xC0000036L)
#endif//STATUS_PORT_DO_NOT_DISTURB

//
// MessageId: STATUS_PORT_DISCONNECTED
//
// MessageText:
//
// Attempt to send a message to a disconnected communication port.
//
#ifndef STATUS_PORT_DISCONNECTED
#define STATUS_PORT_DISCONNECTED         ((NTSTATUS)0xC0000037L)
#endif//STATUS_PORT_DISCONNECTED

//
// MessageId: STATUS_DEVICE_ALREADY_ATTACHED
//
// MessageText:
//
// An attempt was made to attach to a device that was already attached to another device.
//
#ifndef STATUS_DEVICE_ALREADY_ATTACHED
#define STATUS_DEVICE_ALREADY_ATTACHED   ((NTSTATUS)0xC0000038L)
#endif//STATUS_DEVICE_ALREADY_ATTACHED

//
// MessageId: STATUS_OBJECT_PATH_INVALID
//
// MessageText:
//
// Object Path Component was not a directory object.
//
#ifndef STATUS_OBJECT_PATH_INVALID
#define STATUS_OBJECT_PATH_INVALID       ((NTSTATUS)0xC0000039L)
#endif//STATUS_OBJECT_PATH_INVALID

//
// MessageId: STATUS_OBJECT_PATH_NOT_FOUND
//
// MessageText:
//
// {Path Not Found}
// The path %hs does not exist.
//
#ifndef STATUS_OBJECT_PATH_NOT_FOUND
#define STATUS_OBJECT_PATH_NOT_FOUND     ((NTSTATUS)0xC000003AL)
#endif//STATUS_OBJECT_PATH_NOT_FOUND

//
// MessageId: STATUS_OBJECT_PATH_SYNTAX_BAD
//
// MessageText:
//
// Object Path Component was not a directory object.
//
#ifndef STATUS_OBJECT_PATH_SYNTAX_BAD
#define STATUS_OBJECT_PATH_SYNTAX_BAD    ((NTSTATUS)0xC000003BL)
#endif//STATUS_OBJECT_PATH_SYNTAX_BAD

//
// MessageId: STATUS_DATA_OVERRUN
//
// MessageText:
//
// {Data Overrun}
// A data overrun error occurred.
//
#ifndef STATUS_DATA_OVERRUN
#define STATUS_DATA_OVERRUN              ((NTSTATUS)0xC000003CL)
#endif//STATUS_DATA_OVERRUN

//
// MessageId: STATUS_DATA_LATE_ERROR
//
// MessageText:
//
// {Data Late}
// A data late error occurred.
//
#ifndef STATUS_DATA_LATE_ERROR
#define STATUS_DATA_LATE_ERROR           ((NTSTATUS)0xC000003DL)
#endif//STATUS_DATA_LATE_ERROR

//
// MessageId: STATUS_DATA_ERROR
//
// MessageText:
//
// {Data Error}
// An error in reading or writing data occurred.
//
#ifndef STATUS_DATA_ERROR
#define STATUS_DATA_ERROR                ((NTSTATUS)0xC000003EL)
#endif//STATUS_DATA_ERROR

//
// MessageId: STATUS_CRC_ERROR
//
// MessageText:
//
// {Bad CRC}
// A cyclic redundancy check (CRC) checksum error occurred.
//
#ifndef STATUS_CRC_ERROR
#define STATUS_CRC_ERROR                 ((NTSTATUS)0xC000003FL)
#endif//STATUS_CRC_ERROR

//
// MessageId: STATUS_SECTION_TOO_BIG
//
// MessageText:
//
// {Section Too Large}
// The specified section is too big to map the file.
//
#ifndef STATUS_SECTION_TOO_BIG
#define STATUS_SECTION_TOO_BIG           ((NTSTATUS)0xC0000040L)
#endif//STATUS_SECTION_TOO_BIG

//
// MessageId: STATUS_PORT_CONNECTION_REFUSED
//
// MessageText:
//
// The NtConnectPort request is refused.
//
#ifndef STATUS_PORT_CONNECTION_REFUSED
#define STATUS_PORT_CONNECTION_REFUSED   ((NTSTATUS)0xC0000041L)
#endif//STATUS_PORT_CONNECTION_REFUSED

//
// MessageId: STATUS_INVALID_PORT_HANDLE
//
// MessageText:
//
// The type of port handle is invalid for the operation requested.
//
#ifndef STATUS_INVALID_PORT_HANDLE
#define STATUS_INVALID_PORT_HANDLE       ((NTSTATUS)0xC0000042L)
#endif//STATUS_INVALID_PORT_HANDLE

//
// MessageId: STATUS_SHARING_VIOLATION
//
// MessageText:
//
// A file cannot be opened because the share access flags are incompatible.
//
#ifndef STATUS_SHARING_VIOLATION
#define STATUS_SHARING_VIOLATION         ((NTSTATUS)0xC0000043L)
#endif//STATUS_SHARING_VIOLATION

//
// MessageId: STATUS_QUOTA_EXCEEDED
//
// MessageText:
//
// Insufficient quota exists to complete the operation
//
#ifndef STATUS_QUOTA_EXCEEDED
#define STATUS_QUOTA_EXCEEDED            ((NTSTATUS)0xC0000044L)
#endif//STATUS_QUOTA_EXCEEDED

//
// MessageId: STATUS_INVALID_PAGE_PROTECTION
//
// MessageText:
//
// The specified page protection was not valid.
//
#ifndef STATUS_INVALID_PAGE_PROTECTION
#define STATUS_INVALID_PAGE_PROTECTION   ((NTSTATUS)0xC0000045L)
#endif//STATUS_INVALID_PAGE_PROTECTION

//
// MessageId: STATUS_MUTANT_NOT_OWNED
//
// MessageText:
//
// An attempt to release a mutant object was made by a thread that was not the owner of the mutant object.
//
#ifndef STATUS_MUTANT_NOT_OWNED
#define STATUS_MUTANT_NOT_OWNED          ((NTSTATUS)0xC0000046L)
#endif//STATUS_MUTANT_NOT_OWNED

//
// MessageId: STATUS_SEMAPHORE_LIMIT_EXCEEDED
//
// MessageText:
//
// An attempt was made to release a semaphore such that its maximum count would have been exceeded.
//
#ifndef STATUS_SEMAPHORE_LIMIT_EXCEEDED
#define STATUS_SEMAPHORE_LIMIT_EXCEEDED  ((NTSTATUS)0xC0000047L)
#endif//STATUS_SEMAPHORE_LIMIT_EXCEEDED

//
// MessageId: STATUS_PORT_ALREADY_SET
//
// MessageText:
//
// An attempt to set a process's DebugPort or ExceptionPort was made, but a port already exists in the process or an attempt to set a file's CompletionPort made, but a port was already set in the file or an attempt to set an ALPC port's associated completion port was made, but it is already set.
//
#ifndef STATUS_PORT_ALREADY_SET
#define STATUS_PORT_ALREADY_SET          ((NTSTATUS)0xC0000048L)
#endif//STATUS_PORT_ALREADY_SET

//
// MessageId: STATUS_SECTION_NOT_IMAGE
//
// MessageText:
//
// An attempt was made to query image information on a section which does not map an image.
//
#ifndef STATUS_SECTION_NOT_IMAGE
#define STATUS_SECTION_NOT_IMAGE         ((NTSTATUS)0xC0000049L)
#endif//STATUS_SECTION_NOT_IMAGE

//
// MessageId: STATUS_SUSPEND_COUNT_EXCEEDED
//
// MessageText:
//
// An attempt was made to suspend a thread whose suspend count was at its maximum.
//
#ifndef STATUS_SUSPEND_COUNT_EXCEEDED
#define STATUS_SUSPEND_COUNT_EXCEEDED    ((NTSTATUS)0xC000004AL)
#endif//STATUS_SUSPEND_COUNT_EXCEEDED

//
// MessageId: STATUS_THREAD_IS_TERMINATING
//
// MessageText:
//
// An attempt was made to access a thread that has begun termination.
//
#ifndef STATUS_THREAD_IS_TERMINATING
#define STATUS_THREAD_IS_TERMINATING     ((NTSTATUS)0xC000004BL)
#endif//STATUS_THREAD_IS_TERMINATING

//
// MessageId: STATUS_BAD_WORKING_SET_LIMIT
//
// MessageText:
//
// An attempt was made to set the working set limit to an invalid value (minimum greater than maximum, etc).
//
#ifndef STATUS_BAD_WORKING_SET_LIMIT
#define STATUS_BAD_WORKING_SET_LIMIT     ((NTSTATUS)0xC000004CL)
#endif//STATUS_BAD_WORKING_SET_LIMIT

//
// MessageId: STATUS_INCOMPATIBLE_FILE_MAP
//
// MessageText:
//
// A section was created to map a file which is not compatible to an already existing section which maps the same file.
//
#ifndef STATUS_INCOMPATIBLE_FILE_MAP
#define STATUS_INCOMPATIBLE_FILE_MAP     ((NTSTATUS)0xC000004DL)
#endif//STATUS_INCOMPATIBLE_FILE_MAP

//
// MessageId: STATUS_SECTION_PROTECTION
//
// MessageText:
//
// A view to a section specifies a protection which is incompatible with the initial view's protection.
//
#ifndef STATUS_SECTION_PROTECTION
#define STATUS_SECTION_PROTECTION        ((NTSTATUS)0xC000004EL)
#endif//STATUS_SECTION_PROTECTION

//
// MessageId: STATUS_EAS_NOT_SUPPORTED
//
// MessageText:
//
// An operation involving EAs failed because the file system does not support EAs.
//
#ifndef STATUS_EAS_NOT_SUPPORTED
#define STATUS_EAS_NOT_SUPPORTED         ((NTSTATUS)0xC000004FL)
#endif//STATUS_EAS_NOT_SUPPORTED

//
// MessageId: STATUS_EA_TOO_LARGE
//
// MessageText:
//
// An EA operation failed because EA set is too large.
//
#ifndef STATUS_EA_TOO_LARGE
#define STATUS_EA_TOO_LARGE              ((NTSTATUS)0xC0000050L)
#endif//STATUS_EA_TOO_LARGE

//
// MessageId: STATUS_NONEXISTENT_EA_ENTRY
//
// MessageText:
//
// An EA operation failed because the name or EA index is invalid.
//
#ifndef STATUS_NONEXISTENT_EA_ENTRY
#define STATUS_NONEXISTENT_EA_ENTRY      ((NTSTATUS)0xC0000051L)
#endif//STATUS_NONEXISTENT_EA_ENTRY

//
// MessageId: STATUS_NO_EAS_ON_FILE
//
// MessageText:
//
// The file for which EAs were requested has no EAs.
//
#ifndef STATUS_NO_EAS_ON_FILE
#define STATUS_NO_EAS_ON_FILE            ((NTSTATUS)0xC0000052L)
#endif//STATUS_NO_EAS_ON_FILE

//
// MessageId: STATUS_EA_CORRUPT_ERROR
//
// MessageText:
//
// The EA is corrupt and non-readable.
//
#ifndef STATUS_EA_CORRUPT_ERROR
#define STATUS_EA_CORRUPT_ERROR          ((NTSTATUS)0xC0000053L)
#endif//STATUS_EA_CORRUPT_ERROR

//
// MessageId: STATUS_FILE_LOCK_CONFLICT
//
// MessageText:
//
// A requested read/write cannot be granted due to a conflicting file lock.
//
#ifndef STATUS_FILE_LOCK_CONFLICT
#define STATUS_FILE_LOCK_CONFLICT        ((NTSTATUS)0xC0000054L)
#endif//STATUS_FILE_LOCK_CONFLICT

//
// MessageId: STATUS_LOCK_NOT_GRANTED
//
// MessageText:
//
// A requested file lock cannot be granted due to other existing locks.
//
#ifndef STATUS_LOCK_NOT_GRANTED
#define STATUS_LOCK_NOT_GRANTED          ((NTSTATUS)0xC0000055L)
#endif//STATUS_LOCK_NOT_GRANTED

//
// MessageId: STATUS_DELETE_PENDING
//
// MessageText:
//
// A non close operation has been requested of a file object with a delete pending.
//
#ifndef STATUS_DELETE_PENDING
#define STATUS_DELETE_PENDING            ((NTSTATUS)0xC0000056L)
#endif//STATUS_DELETE_PENDING

//
// MessageId: STATUS_CTL_FILE_NOT_SUPPORTED
//
// MessageText:
//
// An attempt was made to set the control attribute on a file. This attribute is not supported in the target file system.
//
#ifndef STATUS_CTL_FILE_NOT_SUPPORTED
#define STATUS_CTL_FILE_NOT_SUPPORTED    ((NTSTATUS)0xC0000057L)
#endif//STATUS_CTL_FILE_NOT_SUPPORTED

//
// MessageId: STATUS_UNKNOWN_REVISION
//
// MessageText:
//
// Indicates a revision number encountered or specified is not one known by the service. It may be a more recent revision than the service is aware of.
//
#ifndef STATUS_UNKNOWN_REVISION
#define STATUS_UNKNOWN_REVISION          ((NTSTATUS)0xC0000058L)
#endif//STATUS_UNKNOWN_REVISION

//
// MessageId: STATUS_REVISION_MISMATCH
//
// MessageText:
//
// Indicates two revision levels are incompatible.
//
#ifndef STATUS_REVISION_MISMATCH
#define STATUS_REVISION_MISMATCH         ((NTSTATUS)0xC0000059L)
#endif//STATUS_REVISION_MISMATCH

//
// MessageId: STATUS_INVALID_OWNER
//
// MessageText:
//
// Indicates a particular Security ID may not be assigned as the owner of an object.
//
#ifndef STATUS_INVALID_OWNER
#define STATUS_INVALID_OWNER             ((NTSTATUS)0xC000005AL)
#endif//STATUS_INVALID_OWNER

//
// MessageId: STATUS_INVALID_PRIMARY_GROUP
//
// MessageText:
//
// Indicates a particular Security ID may not be assigned as the primary group of an object.
//
#ifndef STATUS_INVALID_PRIMARY_GROUP
#define STATUS_INVALID_PRIMARY_GROUP     ((NTSTATUS)0xC000005BL)
#endif//STATUS_INVALID_PRIMARY_GROUP

//
// MessageId: STATUS_NO_IMPERSONATION_TOKEN
//
// MessageText:
//
// An attempt has been made to operate on an impersonation token by a thread that is not currently impersonating a client.
//
#ifndef STATUS_NO_IMPERSONATION_TOKEN
#define STATUS_NO_IMPERSONATION_TOKEN    ((NTSTATUS)0xC000005CL)
#endif//STATUS_NO_IMPERSONATION_TOKEN

//
// MessageId: STATUS_CANT_DISABLE_MANDATORY
//
// MessageText:
//
// A mandatory group may not be disabled.
//
#ifndef STATUS_CANT_DISABLE_MANDATORY
#define STATUS_CANT_DISABLE_MANDATORY    ((NTSTATUS)0xC000005DL)
#endif//STATUS_CANT_DISABLE_MANDATORY

//
// MessageId: STATUS_NO_LOGON_SERVERS
//
// MessageText:
//
// We can't sign you in with this credential because your domain isn't available. Make sure your device is connected to your organization's network and try again. If you previously signed in on this device with another credential, you can sign in with that credential.
//
#ifndef STATUS_NO_LOGON_SERVERS
#define STATUS_NO_LOGON_SERVERS          ((NTSTATUS)0xC000005EL)
#endif//STATUS_NO_LOGON_SERVERS

//
// MessageId: STATUS_NO_SUCH_LOGON_SESSION
//
// MessageText:
//
// A specified logon session does not exist. It may already have been terminated.
//
#ifndef STATUS_NO_SUCH_LOGON_SESSION
#define STATUS_NO_SUCH_LOGON_SESSION     ((NTSTATUS)0xC000005FL)
#endif//STATUS_NO_SUCH_LOGON_SESSION

//
// MessageId: STATUS_NO_SUCH_PRIVILEGE
//
// MessageText:
//
// A specified privilege does not exist.
//
#ifndef STATUS_NO_SUCH_PRIVILEGE
#define STATUS_NO_SUCH_PRIVILEGE         ((NTSTATUS)0xC0000060L)
#endif//STATUS_NO_SUCH_PRIVILEGE

//
// MessageId: STATUS_PRIVILEGE_NOT_HELD
//
// MessageText:
//
// A required privilege is not held by the client.
//
#ifndef STATUS_PRIVILEGE_NOT_HELD
#define STATUS_PRIVILEGE_NOT_HELD        ((NTSTATUS)0xC0000061L)
#endif//STATUS_PRIVILEGE_NOT_HELD

//
// MessageId: STATUS_INVALID_ACCOUNT_NAME
//
// MessageText:
//
// The name provided is not a properly formed account name.
//
#ifndef STATUS_INVALID_ACCOUNT_NAME
#define STATUS_INVALID_ACCOUNT_NAME      ((NTSTATUS)0xC0000062L)
#endif//STATUS_INVALID_ACCOUNT_NAME

//
// MessageId: STATUS_USER_EXISTS
//
// MessageText:
//
// The specified account already exists.
//
#ifndef STATUS_USER_EXISTS
#define STATUS_USER_EXISTS               ((NTSTATUS)0xC0000063L)
#endif//STATUS_USER_EXISTS

//
// MessageId: STATUS_NO_SUCH_USER
//
// MessageText:
//
// The specified account does not exist.
//
#ifndef STATUS_NO_SUCH_USER
#define STATUS_NO_SUCH_USER              ((NTSTATUS)0xC0000064L)     // ntsubauth
#endif//STATUS_NO_SUCH_USER

//
// MessageId: STATUS_GROUP_EXISTS
//
// MessageText:
//
// The specified group already exists.
//
#ifndef STATUS_GROUP_EXISTS
#define STATUS_GROUP_EXISTS              ((NTSTATUS)0xC0000065L)
#endif//STATUS_GROUP_EXISTS

//
// MessageId: STATUS_NO_SUCH_GROUP
//
// MessageText:
//
// The specified group does not exist.
//
#ifndef STATUS_NO_SUCH_GROUP
#define STATUS_NO_SUCH_GROUP             ((NTSTATUS)0xC0000066L)
#endif//STATUS_NO_SUCH_GROUP

//
// MessageId: STATUS_MEMBER_IN_GROUP
//
// MessageText:
//
// The specified user account is already in the specified group account. Also used to indicate a group cannot be deleted because it contains a member.
//
#ifndef STATUS_MEMBER_IN_GROUP
#define STATUS_MEMBER_IN_GROUP           ((NTSTATUS)0xC0000067L)
#endif//STATUS_MEMBER_IN_GROUP

//
// MessageId: STATUS_MEMBER_NOT_IN_GROUP
//
// MessageText:
//
// The specified user account is not a member of the specified group account.
//
#ifndef STATUS_MEMBER_NOT_IN_GROUP
#define STATUS_MEMBER_NOT_IN_GROUP       ((NTSTATUS)0xC0000068L)
#endif//STATUS_MEMBER_NOT_IN_GROUP

//
// MessageId: STATUS_LAST_ADMIN
//
// MessageText:
//
// Indicates the requested operation would disable, delete or could prevent logon for an administration account.
// This is not allowed to prevent creating a situation in which the system cannot be administrated.
//
#ifndef STATUS_LAST_ADMIN
#define STATUS_LAST_ADMIN                ((NTSTATUS)0xC0000069L)
#endif//STATUS_LAST_ADMIN

//
// MessageId: STATUS_WRONG_PASSWORD
//
// MessageText:
//
// When trying to update a password, this return status indicates that the value provided as the current password is not correct.
//
#ifndef STATUS_WRONG_PASSWORD
#define STATUS_WRONG_PASSWORD            ((NTSTATUS)0xC000006AL)     // ntsubauth
#endif//STATUS_WRONG_PASSWORD

//
// MessageId: STATUS_ILL_FORMED_PASSWORD
//
// MessageText:
//
// When trying to update a password, this return status indicates that the value provided for the new password contains values that are not allowed in passwords.
//
#ifndef STATUS_ILL_FORMED_PASSWORD
#define STATUS_ILL_FORMED_PASSWORD       ((NTSTATUS)0xC000006BL)
#endif//STATUS_ILL_FORMED_PASSWORD

//
// MessageId: STATUS_PASSWORD_RESTRICTION
//
// MessageText:
//
// When trying to update a password, this status indicates that some password update rule has been violated. For example, the password may not meet length criteria.
//
#ifndef STATUS_PASSWORD_RESTRICTION
#define STATUS_PASSWORD_RESTRICTION      ((NTSTATUS)0xC000006CL)     // ntsubauth
#endif//STATUS_PASSWORD_RESTRICTION

//
// MessageId: STATUS_LOGON_FAILURE
//
// MessageText:
//
// The attempted logon is invalid. This is either due to a bad username or authentication information.
//
#ifndef STATUS_LOGON_FAILURE
#define STATUS_LOGON_FAILURE             ((NTSTATUS)0xC000006DL)     // ntsubauth
#endif//STATUS_LOGON_FAILURE

//
// MessageId: STATUS_ACCOUNT_RESTRICTION
//
// MessageText:
//
// Indicates a referenced user name and authentication information are valid, but some user account restriction has prevented successful authentication (such as time-of-day restrictions).
//
#ifndef STATUS_ACCOUNT_RESTRICTION
#define STATUS_ACCOUNT_RESTRICTION       ((NTSTATUS)0xC000006EL)     // ntsubauth
#endif//STATUS_ACCOUNT_RESTRICTION

//
// MessageId: STATUS_INVALID_LOGON_HOURS
//
// MessageText:
//
// The user account has time restrictions and may not be logged onto at this time.
//
#ifndef STATUS_INVALID_LOGON_HOURS
#define STATUS_INVALID_LOGON_HOURS       ((NTSTATUS)0xC000006FL)     // ntsubauth
#endif//STATUS_INVALID_LOGON_HOURS

//
// MessageId: STATUS_INVALID_WORKSTATION
//
// MessageText:
//
// The user account is restricted such that it may not be used to log on from the source workstation.
//
#ifndef STATUS_INVALID_WORKSTATION
#define STATUS_INVALID_WORKSTATION       ((NTSTATUS)0xC0000070L)     // ntsubauth
#endif//STATUS_INVALID_WORKSTATION

//
// MessageId: STATUS_PASSWORD_EXPIRED
//
// MessageText:
//
// The user account's password has expired.
//
#ifndef STATUS_PASSWORD_EXPIRED
#define STATUS_PASSWORD_EXPIRED          ((NTSTATUS)0xC0000071L)     // ntsubauth
#endif//STATUS_PASSWORD_EXPIRED

//
// MessageId: STATUS_ACCOUNT_DISABLED
//
// MessageText:
//
// The referenced account is currently disabled and may not be logged on to.
//
#ifndef STATUS_ACCOUNT_DISABLED
#define STATUS_ACCOUNT_DISABLED          ((NTSTATUS)0xC0000072L)     // ntsubauth
#endif//STATUS_ACCOUNT_DISABLED

//
// MessageId: STATUS_NONE_MAPPED
//
// MessageText:
//
// None of the information to be translated has been translated.
//
#ifndef STATUS_NONE_MAPPED
#define STATUS_NONE_MAPPED               ((NTSTATUS)0xC0000073L)
#endif//STATUS_NONE_MAPPED

//
// MessageId: STATUS_TOO_MANY_LUIDS_REQUESTED
//
// MessageText:
//
// The number of LUIDs requested may not be allocated with a single allocation.
//
#ifndef STATUS_TOO_MANY_LUIDS_REQUESTED
#define STATUS_TOO_MANY_LUIDS_REQUESTED  ((NTSTATUS)0xC0000074L)
#endif//STATUS_TOO_MANY_LUIDS_REQUESTED

//
// MessageId: STATUS_LUIDS_EXHAUSTED
//
// MessageText:
//
// Indicates there are no more LUIDs to allocate.
//
#ifndef STATUS_LUIDS_EXHAUSTED
#define STATUS_LUIDS_EXHAUSTED           ((NTSTATUS)0xC0000075L)
#endif//STATUS_LUIDS_EXHAUSTED

//
// MessageId: STATUS_INVALID_SUB_AUTHORITY
//
// MessageText:
//
// Indicates the sub-authority value is invalid for the particular use.
//
#ifndef STATUS_INVALID_SUB_AUTHORITY
#define STATUS_INVALID_SUB_AUTHORITY     ((NTSTATUS)0xC0000076L)
#endif//STATUS_INVALID_SUB_AUTHORITY

//
// MessageId: STATUS_INVALID_ACL
//
// MessageText:
//
// Indicates the ACL structure is not valid.
//
#ifndef STATUS_INVALID_ACL
#define STATUS_INVALID_ACL               ((NTSTATUS)0xC0000077L)
#endif//STATUS_INVALID_ACL

//
// MessageId: STATUS_INVALID_SID
//
// MessageText:
//
// Indicates the SID structure is not valid.
//
#ifndef STATUS_INVALID_SID
#define STATUS_INVALID_SID               ((NTSTATUS)0xC0000078L)
#endif//STATUS_INVALID_SID

//
// MessageId: STATUS_INVALID_SECURITY_DESCR
//
// MessageText:
//
// Indicates the SECURITY_DESCRIPTOR structure is not valid.
//
#ifndef STATUS_INVALID_SECURITY_DESCR
#define STATUS_INVALID_SECURITY_DESCR    ((NTSTATUS)0xC0000079L)
#endif//STATUS_INVALID_SECURITY_DESCR

//
// MessageId: STATUS_PROCEDURE_NOT_FOUND
//
// MessageText:
//
// Indicates the specified procedure address cannot be found in the DLL.
//
#ifndef STATUS_PROCEDURE_NOT_FOUND
#define STATUS_PROCEDURE_NOT_FOUND       ((NTSTATUS)0xC000007AL)
#endif//STATUS_PROCEDURE_NOT_FOUND

//
// MessageId: STATUS_INVALID_IMAGE_FORMAT
//
// MessageText:
//
// {Bad Image}
// %hs is either not designed to run on Windows or it contains an error. Try installing the program again using the original installation media or contact your system administrator or the software vendor for support. Error status 0x%08lx.
//
#ifndef STATUS_INVALID_IMAGE_FORMAT
#define STATUS_INVALID_IMAGE_FORMAT      ((NTSTATUS)0xC000007BL)
#endif//STATUS_INVALID_IMAGE_FORMAT

//
// MessageId: STATUS_NO_TOKEN
//
// MessageText:
//
// An attempt was made to reference a token that doesn't exist.
// This is typically done by referencing the token associated with a thread when the thread is not impersonating a client.
//
#ifndef STATUS_NO_TOKEN
#define STATUS_NO_TOKEN                  ((NTSTATUS)0xC000007CL)
#endif//STATUS_NO_TOKEN

//
// MessageId: STATUS_BAD_INHERITANCE_ACL
//
// MessageText:
//
// Indicates that an attempt to build either an inherited ACL or ACE was not successful.
// This can be caused by a number of things. One of the more probable causes is the replacement of a CreatorId with an SID that didn't fit into the ACE or ACL.
//
#ifndef STATUS_BAD_INHERITANCE_ACL
#define STATUS_BAD_INHERITANCE_ACL       ((NTSTATUS)0xC000007DL)
#endif//STATUS_BAD_INHERITANCE_ACL

//
// MessageId: STATUS_RANGE_NOT_LOCKED
//
// MessageText:
//
// The range specified in NtUnlockFile was not locked.
//
#ifndef STATUS_RANGE_NOT_LOCKED
#define STATUS_RANGE_NOT_LOCKED          ((NTSTATUS)0xC000007EL)
#endif//STATUS_RANGE_NOT_LOCKED

//
// MessageId: STATUS_DISK_FULL
//
// MessageText:
//
// An operation failed because the disk was full.
// If this is a thinly provisioned volume the physical storage backing this volume has been exhausted.
//
#ifndef STATUS_DISK_FULL
#define STATUS_DISK_FULL                 ((NTSTATUS)0xC000007FL)
#endif//STATUS_DISK_FULL

//
// MessageId: STATUS_SERVER_DISABLED
//
// MessageText:
//
// The GUID allocation server is [already] disabled at the moment.
//
#ifndef STATUS_SERVER_DISABLED
#define STATUS_SERVER_DISABLED           ((NTSTATUS)0xC0000080L)
#endif//STATUS_SERVER_DISABLED

//
// MessageId: STATUS_SERVER_NOT_DISABLED
//
// MessageText:
//
// The GUID allocation server is [already] enabled at the moment.
//
#ifndef STATUS_SERVER_NOT_DISABLED
#define STATUS_SERVER_NOT_DISABLED       ((NTSTATUS)0xC0000081L)
#endif//STATUS_SERVER_NOT_DISABLED

//
// MessageId: STATUS_TOO_MANY_GUIDS_REQUESTED
//
// MessageText:
//
// Too many GUIDs were requested from the allocation server at once.
//
#ifndef STATUS_TOO_MANY_GUIDS_REQUESTED
#define STATUS_TOO_MANY_GUIDS_REQUESTED  ((NTSTATUS)0xC0000082L)
#endif//STATUS_TOO_MANY_GUIDS_REQUESTED

//
// MessageId: STATUS_GUIDS_EXHAUSTED
//
// MessageText:
//
// The GUIDs could not be allocated because the Authority Agent was exhausted.
//
#ifndef STATUS_GUIDS_EXHAUSTED
#define STATUS_GUIDS_EXHAUSTED           ((NTSTATUS)0xC0000083L)
#endif//STATUS_GUIDS_EXHAUSTED

//
// MessageId: STATUS_INVALID_ID_AUTHORITY
//
// MessageText:
//
// The value provided was an invalid value for an identifier authority.
//
#ifndef STATUS_INVALID_ID_AUTHORITY
#define STATUS_INVALID_ID_AUTHORITY      ((NTSTATUS)0xC0000084L)
#endif//STATUS_INVALID_ID_AUTHORITY

//
// MessageId: STATUS_AGENTS_EXHAUSTED
//
// MessageText:
//
// There are no more authority agent values available for the given identifier authority value.
//
#ifndef STATUS_AGENTS_EXHAUSTED
#define STATUS_AGENTS_EXHAUSTED          ((NTSTATUS)0xC0000085L)
#endif//STATUS_AGENTS_EXHAUSTED

//
// MessageId: STATUS_INVALID_VOLUME_LABEL
//
// MessageText:
//
// An invalid volume label has been specified.
//
#ifndef STATUS_INVALID_VOLUME_LABEL
#define STATUS_INVALID_VOLUME_LABEL      ((NTSTATUS)0xC0000086L)
#endif//STATUS_INVALID_VOLUME_LABEL

//
// MessageId: STATUS_SECTION_NOT_EXTENDED
//
// MessageText:
//
// A mapped section could not be extended.
//
#ifndef STATUS_SECTION_NOT_EXTENDED
#define STATUS_SECTION_NOT_EXTENDED      ((NTSTATUS)0xC0000087L)
#endif//STATUS_SECTION_NOT_EXTENDED

//
// MessageId: STATUS_NOT_MAPPED_DATA
//
// MessageText:
//
// Specified section to flush does not map a data file.
//
#ifndef STATUS_NOT_MAPPED_DATA
#define STATUS_NOT_MAPPED_DATA           ((NTSTATUS)0xC0000088L)
#endif//STATUS_NOT_MAPPED_DATA

//
// MessageId: STATUS_RESOURCE_DATA_NOT_FOUND
//
// MessageText:
//
// Indicates the specified image file did not contain a resource section.
//
#ifndef STATUS_RESOURCE_DATA_NOT_FOUND
#define STATUS_RESOURCE_DATA_NOT_FOUND   ((NTSTATUS)0xC0000089L)
#endif//STATUS_RESOURCE_DATA_NOT_FOUND

//
// MessageId: STATUS_RESOURCE_TYPE_NOT_FOUND
//
// MessageText:
//
// Indicates the specified resource type cannot be found in the image file.
//
#ifndef STATUS_RESOURCE_TYPE_NOT_FOUND
#define STATUS_RESOURCE_TYPE_NOT_FOUND   ((NTSTATUS)0xC000008AL)
#endif//STATUS_RESOURCE_TYPE_NOT_FOUND

//
// MessageId: STATUS_RESOURCE_NAME_NOT_FOUND
//
// MessageText:
//
// Indicates the specified resource name cannot be found in the image file.
//
#ifndef STATUS_RESOURCE_NAME_NOT_FOUND
#define STATUS_RESOURCE_NAME_NOT_FOUND   ((NTSTATUS)0xC000008BL)
#endif//STATUS_RESOURCE_NAME_NOT_FOUND

//
// MessageId: STATUS_ARRAY_BOUNDS_EXCEEDED
//
// MessageText:
//
// {EXCEPTION}
// Array bounds exceeded.
//
#ifndef STATUS_ARRAY_BOUNDS_EXCEEDED
#define STATUS_ARRAY_BOUNDS_EXCEEDED     ((NTSTATUS)0xC000008CL)    // winnt
#endif//STATUS_ARRAY_BOUNDS_EXCEEDED

//
// MessageId: STATUS_FLOAT_DENORMAL_OPERAND
//
// MessageText:
//
// {EXCEPTION}
// Floating-point denormal operand.
//
#ifndef STATUS_FLOAT_DENORMAL_OPERAND
#define STATUS_FLOAT_DENORMAL_OPERAND    ((NTSTATUS)0xC000008DL)    // winnt
#endif//STATUS_FLOAT_DENORMAL_OPERAND

//
// MessageId: STATUS_FLOAT_DIVIDE_BY_ZERO
//
// MessageText:
//
// {EXCEPTION}
// Floating-point division by zero.
//
#ifndef STATUS_FLOAT_DIVIDE_BY_ZERO
#define STATUS_FLOAT_DIVIDE_BY_ZERO      ((NTSTATUS)0xC000008EL)    // winnt
#endif//STATUS_FLOAT_DIVIDE_BY_ZERO

//
// MessageId: STATUS_FLOAT_INEXACT_RESULT
//
// MessageText:
//
// {EXCEPTION}
// Floating-point inexact result.
//
#ifndef STATUS_FLOAT_INEXACT_RESULT
#define STATUS_FLOAT_INEXACT_RESULT      ((NTSTATUS)0xC000008FL)    // winnt
#endif//STATUS_FLOAT_INEXACT_RESULT

//
// MessageId: STATUS_FLOAT_INVALID_OPERATION
//
// MessageText:
//
// {EXCEPTION}
// Floating-point invalid operation.
//
#ifndef STATUS_FLOAT_INVALID_OPERATION
#define STATUS_FLOAT_INVALID_OPERATION   ((NTSTATUS)0xC0000090L)    // winnt
#endif//STATUS_FLOAT_INVALID_OPERATION

//
// MessageId: STATUS_FLOAT_OVERFLOW
//
// MessageText:
//
// {EXCEPTION}
// Floating-point overflow.
//
#ifndef STATUS_FLOAT_OVERFLOW
#define STATUS_FLOAT_OVERFLOW            ((NTSTATUS)0xC0000091L)    // winnt
#endif//STATUS_FLOAT_OVERFLOW

//
// MessageId: STATUS_FLOAT_STACK_CHECK
//
// MessageText:
//
// {EXCEPTION}
// Floating-point stack check.
//
#ifndef STATUS_FLOAT_STACK_CHECK
#define STATUS_FLOAT_STACK_CHECK         ((NTSTATUS)0xC0000092L)    // winnt
#endif//STATUS_FLOAT_STACK_CHECK

//
// MessageId: STATUS_FLOAT_UNDERFLOW
//
// MessageText:
//
// {EXCEPTION}
// Floating-point underflow.
//
#ifndef STATUS_FLOAT_UNDERFLOW
#define STATUS_FLOAT_UNDERFLOW           ((NTSTATUS)0xC0000093L)    // winnt
#endif//STATUS_FLOAT_UNDERFLOW

//
// MessageId: STATUS_INTEGER_DIVIDE_BY_ZERO
//
// MessageText:
//
// {EXCEPTION}
// Integer division by zero.
//
#ifndef STATUS_INTEGER_DIVIDE_BY_ZERO
#define STATUS_INTEGER_DIVIDE_BY_ZERO    ((NTSTATUS)0xC0000094L)    // winnt
#endif//STATUS_INTEGER_DIVIDE_BY_ZERO

//
// MessageId: STATUS_INTEGER_OVERFLOW
//
// MessageText:
//
// {EXCEPTION}
// Integer overflow.
//
#ifndef STATUS_INTEGER_OVERFLOW
#define STATUS_INTEGER_OVERFLOW          ((NTSTATUS)0xC0000095L)    // winnt
#endif//STATUS_INTEGER_OVERFLOW

//
// MessageId: STATUS_PRIVILEGED_INSTRUCTION
//
// MessageText:
//
// {EXCEPTION}
// Privileged instruction.
//
#ifndef STATUS_PRIVILEGED_INSTRUCTION
#define STATUS_PRIVILEGED_INSTRUCTION    ((NTSTATUS)0xC0000096L)    // winnt
#endif//STATUS_PRIVILEGED_INSTRUCTION

//
// MessageId: STATUS_TOO_MANY_PAGING_FILES
//
// MessageText:
//
// An attempt was made to install more paging files than the system supports.
//
#ifndef STATUS_TOO_MANY_PAGING_FILES
#define STATUS_TOO_MANY_PAGING_FILES     ((NTSTATUS)0xC0000097L)
#endif//STATUS_TOO_MANY_PAGING_FILES

//
// MessageId: STATUS_FILE_INVALID
//
// MessageText:
//
// The volume for a file has been externally altered such that the opened file is no longer valid.
//
#ifndef STATUS_FILE_INVALID
#define STATUS_FILE_INVALID              ((NTSTATUS)0xC0000098L)
#endif//STATUS_FILE_INVALID

//
// MessageId: STATUS_ALLOTTED_SPACE_EXCEEDED
//
// MessageText:
//
// When a block of memory is allotted for future updates, such as the memory allocated to hold discretionary access control and primary group information, successive updates may exceed the amount of memory originally allotted.
// Since quota may already have been charged to several processes which have handles to the object, it is not reasonable to alter the size of the allocated memory.
// Instead, a request that requires more memory than has been allotted must fail and the STATUS_ALLOTED_SPACE_EXCEEDED error returned.
//
#ifndef STATUS_ALLOTTED_SPACE_EXCEEDED
#define STATUS_ALLOTTED_SPACE_EXCEEDED   ((NTSTATUS)0xC0000099L)
#endif//STATUS_ALLOTTED_SPACE_EXCEEDED

//
// MessageId: STATUS_INSUFFICIENT_RESOURCES
//
// MessageText:
//
// Insufficient system resources exist to complete the API.
//
#ifndef STATUS_INSUFFICIENT_RESOURCES
#define STATUS_INSUFFICIENT_RESOURCES    ((NTSTATUS)0xC000009AL)     // ntsubauth
#endif//STATUS_INSUFFICIENT_RESOURCES

//
// MessageId: STATUS_DFS_EXIT_PATH_FOUND
//
// MessageText:
//
// An attempt has been made to open a DFS exit path control file.
//
#ifndef STATUS_DFS_EXIT_PATH_FOUND
#define STATUS_DFS_EXIT_PATH_FOUND       ((NTSTATUS)0xC000009BL)
#endif//STATUS_DFS_EXIT_PATH_FOUND

//
// MessageId: STATUS_DEVICE_DATA_ERROR
//
// MessageText:
//
//  STATUS_DEVICE_DATA_ERROR
//
#ifndef STATUS_DEVICE_DATA_ERROR
#define STATUS_DEVICE_DATA_ERROR         ((NTSTATUS)0xC000009CL)
#endif//STATUS_DEVICE_DATA_ERROR

//
// MessageId: STATUS_DEVICE_NOT_CONNECTED
//
// MessageText:
//
//  STATUS_DEVICE_NOT_CONNECTED
//
#ifndef STATUS_DEVICE_NOT_CONNECTED
#define STATUS_DEVICE_NOT_CONNECTED      ((NTSTATUS)0xC000009DL)
#endif//STATUS_DEVICE_NOT_CONNECTED

//
// MessageId: STATUS_DEVICE_POWER_FAILURE
//
// MessageText:
//
//  STATUS_DEVICE_POWER_FAILURE
//
#ifndef STATUS_DEVICE_POWER_FAILURE
#define STATUS_DEVICE_POWER_FAILURE      ((NTSTATUS)0xC000009EL)
#endif//STATUS_DEVICE_POWER_FAILURE

//
// MessageId: STATUS_FREE_VM_NOT_AT_BASE
//
// MessageText:
//
// Virtual memory cannot be freed as base address is not the base of the region and a region size of zero was specified.
//
#ifndef STATUS_FREE_VM_NOT_AT_BASE
#define STATUS_FREE_VM_NOT_AT_BASE       ((NTSTATUS)0xC000009FL)
#endif//STATUS_FREE_VM_NOT_AT_BASE

//
// MessageId: STATUS_MEMORY_NOT_ALLOCATED
//
// MessageText:
//
// An attempt was made to free virtual memory which is not allocated.
//
#ifndef STATUS_MEMORY_NOT_ALLOCATED
#define STATUS_MEMORY_NOT_ALLOCATED      ((NTSTATUS)0xC00000A0L)
#endif//STATUS_MEMORY_NOT_ALLOCATED

//
// MessageId: STATUS_WORKING_SET_QUOTA
//
// MessageText:
//
// The working set is not big enough to allow the requested pages to be locked.
//
#ifndef STATUS_WORKING_SET_QUOTA
#define STATUS_WORKING_SET_QUOTA         ((NTSTATUS)0xC00000A1L)
#endif//STATUS_WORKING_SET_QUOTA

//
// MessageId: STATUS_MEDIA_WRITE_PROTECTED
//
// MessageText:
//
// {Write Protect Error}
// The disk cannot be written to because it is write protected. Please remove the write protection from the volume %hs in drive %hs.
//
#ifndef STATUS_MEDIA_WRITE_PROTECTED
#define STATUS_MEDIA_WRITE_PROTECTED     ((NTSTATUS)0xC00000A2L)
#endif//STATUS_MEDIA_WRITE_PROTECTED

//
// MessageId: STATUS_DEVICE_NOT_READY
//
// MessageText:
//
// {Drive Not Ready}
// The drive is not ready for use; its door may be open. Please check drive %hs and make sure that a disk is inserted and that the drive door is closed.
//
#ifndef STATUS_DEVICE_NOT_READY
#define STATUS_DEVICE_NOT_READY          ((NTSTATUS)0xC00000A3L)
#endif//STATUS_DEVICE_NOT_READY

//
// MessageId: STATUS_INVALID_GROUP_ATTRIBUTES
//
// MessageText:
//
// The specified attributes are invalid, or incompatible with the attributes for the group as a whole.
//
#ifndef STATUS_INVALID_GROUP_ATTRIBUTES
#define STATUS_INVALID_GROUP_ATTRIBUTES  ((NTSTATUS)0xC00000A4L)
#endif//STATUS_INVALID_GROUP_ATTRIBUTES

//
// MessageId: STATUS_BAD_IMPERSONATION_LEVEL
//
// MessageText:
//
// A specified impersonation level is invalid.
// Also used to indicate a required impersonation level was not provided.
//
#ifndef STATUS_BAD_IMPERSONATION_LEVEL
#define STATUS_BAD_IMPERSONATION_LEVEL   ((NTSTATUS)0xC00000A5L)
#endif//STATUS_BAD_IMPERSONATION_LEVEL

//
// MessageId: STATUS_CANT_OPEN_ANONYMOUS
//
// MessageText:
//
// An attempt was made to open an Anonymous level token.
// Anonymous tokens may not be opened.
//
#ifndef STATUS_CANT_OPEN_ANONYMOUS
#define STATUS_CANT_OPEN_ANONYMOUS       ((NTSTATUS)0xC00000A6L)
#endif//STATUS_CANT_OPEN_ANONYMOUS

//
// MessageId: STATUS_BAD_VALIDATION_CLASS
//
// MessageText:
//
// The validation information class requested was invalid.
//
#ifndef STATUS_BAD_VALIDATION_CLASS
#define STATUS_BAD_VALIDATION_CLASS      ((NTSTATUS)0xC00000A7L)
#endif//STATUS_BAD_VALIDATION_CLASS

//
// MessageId: STATUS_BAD_TOKEN_TYPE
//
// MessageText:
//
// The type of a token object is inappropriate for its attempted use.
//
#ifndef STATUS_BAD_TOKEN_TYPE
#define STATUS_BAD_TOKEN_TYPE            ((NTSTATUS)0xC00000A8L)
#endif//STATUS_BAD_TOKEN_TYPE

//
// MessageId: STATUS_BAD_MASTER_BOOT_RECORD
//
// MessageText:
//
// The type of a token object is inappropriate for its attempted use.
//
#ifndef STATUS_BAD_MASTER_BOOT_RECORD
#define STATUS_BAD_MASTER_BOOT_RECORD    ((NTSTATUS)0xC00000A9L)
#endif//STATUS_BAD_MASTER_BOOT_RECORD

//
// MessageId: STATUS_INSTRUCTION_MISALIGNMENT
//
// MessageText:
//
// An attempt was made to execute an instruction at an unaligned address and the host system does not support unaligned instruction references.
//
#ifndef STATUS_INSTRUCTION_MISALIGNMENT
#define STATUS_INSTRUCTION_MISALIGNMENT  ((NTSTATUS)0xC00000AAL)
#endif//STATUS_INSTRUCTION_MISALIGNMENT

//
// MessageId: STATUS_INSTANCE_NOT_AVAILABLE
//
// MessageText:
//
// The maximum named pipe instance count has been reached.
//
#ifndef STATUS_INSTANCE_NOT_AVAILABLE
#define STATUS_INSTANCE_NOT_AVAILABLE    ((NTSTATUS)0xC00000ABL)
#endif//STATUS_INSTANCE_NOT_AVAILABLE

//
// MessageId: STATUS_PIPE_NOT_AVAILABLE
//
// MessageText:
//
// An instance of a named pipe cannot be found in the listening state.
//
#ifndef STATUS_PIPE_NOT_AVAILABLE
#define STATUS_PIPE_NOT_AVAILABLE        ((NTSTATUS)0xC00000ACL)
#endif//STATUS_PIPE_NOT_AVAILABLE

//
// MessageId: STATUS_INVALID_PIPE_STATE
//
// MessageText:
//
// The named pipe is not in the connected or closing state.
//
#ifndef STATUS_INVALID_PIPE_STATE
#define STATUS_INVALID_PIPE_STATE        ((NTSTATUS)0xC00000ADL)
#endif//STATUS_INVALID_PIPE_STATE

//
// MessageId: STATUS_PIPE_BUSY
//
// MessageText:
//
// The specified pipe is set to complete operations and there are current I/O operations queued so it cannot be changed to queue operations.
//
#ifndef STATUS_PIPE_BUSY
#define STATUS_PIPE_BUSY                 ((NTSTATUS)0xC00000AEL)
#endif//STATUS_PIPE_BUSY

//
// MessageId: STATUS_ILLEGAL_FUNCTION
//
// MessageText:
//
// The specified handle is not open to the server end of the named pipe.
//
#ifndef STATUS_ILLEGAL_FUNCTION
#define STATUS_ILLEGAL_FUNCTION          ((NTSTATUS)0xC00000AFL)
#endif//STATUS_ILLEGAL_FUNCTION

//
// MessageId: STATUS_PIPE_DISCONNECTED
//
// MessageText:
//
// The specified named pipe is in the disconnected state.
//
#ifndef STATUS_PIPE_DISCONNECTED
#define STATUS_PIPE_DISCONNECTED         ((NTSTATUS)0xC00000B0L)
#endif//STATUS_PIPE_DISCONNECTED

//
// MessageId: STATUS_PIPE_CLOSING
//
// MessageText:
//
// The specified named pipe is in the closing state.
//
#ifndef STATUS_PIPE_CLOSING
#define STATUS_PIPE_CLOSING              ((NTSTATUS)0xC00000B1L)
#endif//STATUS_PIPE_CLOSING

//
// MessageId: STATUS_PIPE_CONNECTED
//
// MessageText:
//
// The specified named pipe is in the connected state.
//
#ifndef STATUS_PIPE_CONNECTED
#define STATUS_PIPE_CONNECTED            ((NTSTATUS)0xC00000B2L)
#endif//STATUS_PIPE_CONNECTED

//
// MessageId: STATUS_PIPE_LISTENING
//
// MessageText:
//
// The specified named pipe is in the listening state.
//
#ifndef STATUS_PIPE_LISTENING
#define STATUS_PIPE_LISTENING            ((NTSTATUS)0xC00000B3L)
#endif//STATUS_PIPE_LISTENING

//
// MessageId: STATUS_INVALID_READ_MODE
//
// MessageText:
//
// The specified named pipe is not in message mode.
//
#ifndef STATUS_INVALID_READ_MODE
#define STATUS_INVALID_READ_MODE         ((NTSTATUS)0xC00000B4L)
#endif//STATUS_INVALID_READ_MODE

//
// MessageId: STATUS_IO_TIMEOUT
//
// MessageText:
//
// {Device Timeout}
// The specified I/O operation on %hs was not completed before the time-out period expired.
//
#ifndef STATUS_IO_TIMEOUT
#define STATUS_IO_TIMEOUT                ((NTSTATUS)0xC00000B5L)
#endif//STATUS_IO_TIMEOUT

//
// MessageId: STATUS_FILE_FORCED_CLOSED
//
// MessageText:
//
// The specified file has been closed by another process.
//
#ifndef STATUS_FILE_FORCED_CLOSED
#define STATUS_FILE_FORCED_CLOSED        ((NTSTATUS)0xC00000B6L)
#endif//STATUS_FILE_FORCED_CLOSED

//
// MessageId: STATUS_PROFILING_NOT_STARTED
//
// MessageText:
//
// Profiling not started.
//
#ifndef STATUS_PROFILING_NOT_STARTED
#define STATUS_PROFILING_NOT_STARTED     ((NTSTATUS)0xC00000B7L)
#endif//STATUS_PROFILING_NOT_STARTED

//
// MessageId: STATUS_PROFILING_NOT_STOPPED
//
// MessageText:
//
// Profiling not stopped.
//
#ifndef STATUS_PROFILING_NOT_STOPPED
#define STATUS_PROFILING_NOT_STOPPED     ((NTSTATUS)0xC00000B8L)
#endif//STATUS_PROFILING_NOT_STOPPED

//
// MessageId: STATUS_COULD_NOT_INTERPRET
//
// MessageText:
//
// The passed ACL did not contain the minimum required information.
//
#ifndef STATUS_COULD_NOT_INTERPRET
#define STATUS_COULD_NOT_INTERPRET       ((NTSTATUS)0xC00000B9L)
#endif//STATUS_COULD_NOT_INTERPRET

//
// MessageId: STATUS_FILE_IS_A_DIRECTORY
//
// MessageText:
//
// The file that was specified as a target is a directory and the caller specified that it could be anything but a directory.
//
#ifndef STATUS_FILE_IS_A_DIRECTORY
#define STATUS_FILE_IS_A_DIRECTORY       ((NTSTATUS)0xC00000BAL)
#endif//STATUS_FILE_IS_A_DIRECTORY

//
// Network specific errors.
//
//
//
// MessageId: STATUS_NOT_SUPPORTED
//
// MessageText:
//
// The request is not supported.
//
#ifndef STATUS_NOT_SUPPORTED
#define STATUS_NOT_SUPPORTED             ((NTSTATUS)0xC00000BBL)
#endif//STATUS_NOT_SUPPORTED

//
// MessageId: STATUS_REMOTE_NOT_LISTENING
//
// MessageText:
//
// This remote computer is not listening.
//
#ifndef STATUS_REMOTE_NOT_LISTENING
#define STATUS_REMOTE_NOT_LISTENING      ((NTSTATUS)0xC00000BCL)
#endif//STATUS_REMOTE_NOT_LISTENING

//
// MessageId: STATUS_DUPLICATE_NAME
//
// MessageText:
//
// A duplicate name exists on the network.
//
#ifndef STATUS_DUPLICATE_NAME
#define STATUS_DUPLICATE_NAME            ((NTSTATUS)0xC00000BDL)
#endif//STATUS_DUPLICATE_NAME

//
// MessageId: STATUS_BAD_NETWORK_PATH
//
// MessageText:
//
// The network path cannot be located.
//
#ifndef STATUS_BAD_NETWORK_PATH
#define STATUS_BAD_NETWORK_PATH          ((NTSTATUS)0xC00000BEL)
#endif//STATUS_BAD_NETWORK_PATH

//
// MessageId: STATUS_NETWORK_BUSY
//
// MessageText:
//
// The network is busy.
//
#ifndef STATUS_NETWORK_BUSY
#define STATUS_NETWORK_BUSY              ((NTSTATUS)0xC00000BFL)
#endif//STATUS_NETWORK_BUSY

//
// MessageId: STATUS_DEVICE_DOES_NOT_EXIST
//
// MessageText:
//
// This device does not exist.
//
#ifndef STATUS_DEVICE_DOES_NOT_EXIST
#define STATUS_DEVICE_DOES_NOT_EXIST     ((NTSTATUS)0xC00000C0L)
#endif//STATUS_DEVICE_DOES_NOT_EXIST

//
// MessageId: STATUS_TOO_MANY_COMMANDS
//
// MessageText:
//
// The network BIOS command limit has been reached.
//
#ifndef STATUS_TOO_MANY_COMMANDS
#define STATUS_TOO_MANY_COMMANDS         ((NTSTATUS)0xC00000C1L)
#endif//STATUS_TOO_MANY_COMMANDS

//
// MessageId: STATUS_ADAPTER_HARDWARE_ERROR
//
// MessageText:
//
// An I/O adapter hardware error has occurred.
//
#ifndef STATUS_ADAPTER_HARDWARE_ERROR
#define STATUS_ADAPTER_HARDWARE_ERROR    ((NTSTATUS)0xC00000C2L)
#endif//STATUS_ADAPTER_HARDWARE_ERROR

//
// MessageId: STATUS_INVALID_NETWORK_RESPONSE
//
// MessageText:
//
// The network responded incorrectly.
//
#ifndef STATUS_INVALID_NETWORK_RESPONSE
#define STATUS_INVALID_NETWORK_RESPONSE  ((NTSTATUS)0xC00000C3L)
#endif//STATUS_INVALID_NETWORK_RESPONSE

//
// MessageId: STATUS_UNEXPECTED_NETWORK_ERROR
//
// MessageText:
//
// An unexpected network error occurred.
//
#ifndef STATUS_UNEXPECTED_NETWORK_ERROR
#define STATUS_UNEXPECTED_NETWORK_ERROR  ((NTSTATUS)0xC00000C4L)
#endif//STATUS_UNEXPECTED_NETWORK_ERROR

//
// MessageId: STATUS_BAD_REMOTE_ADAPTER
//
// MessageText:
//
// The remote adapter is not compatible.
//
#ifndef STATUS_BAD_REMOTE_ADAPTER
#define STATUS_BAD_REMOTE_ADAPTER        ((NTSTATUS)0xC00000C5L)
#endif//STATUS_BAD_REMOTE_ADAPTER

//
// MessageId: STATUS_PRINT_QUEUE_FULL
//
// MessageText:
//
// The printer queue is full.
//
#ifndef STATUS_PRINT_QUEUE_FULL
#define STATUS_PRINT_QUEUE_FULL          ((NTSTATUS)0xC00000C6L)
#endif//STATUS_PRINT_QUEUE_FULL

//
// MessageId: STATUS_NO_SPOOL_SPACE
//
// MessageText:
//
// Space to store the file waiting to be printed is not available on the server.
//
#ifndef STATUS_NO_SPOOL_SPACE
#define STATUS_NO_SPOOL_SPACE            ((NTSTATUS)0xC00000C7L)
#endif//STATUS_NO_SPOOL_SPACE

//
// MessageId: STATUS_PRINT_CANCELLED
//
// MessageText:
//
// The requested print file has been canceled.
//
#ifndef STATUS_PRINT_CANCELLED
#define STATUS_PRINT_CANCELLED           ((NTSTATUS)0xC00000C8L)
#endif//STATUS_PRINT_CANCELLED

//
// MessageId: STATUS_NETWORK_NAME_DELETED
//
// MessageText:
//
// The network name was deleted.
//
#ifndef STATUS_NETWORK_NAME_DELETED
#define STATUS_NETWORK_NAME_DELETED      ((NTSTATUS)0xC00000C9L)
#endif//STATUS_NETWORK_NAME_DELETED

//
// MessageId: STATUS_NETWORK_ACCESS_DENIED
//
// MessageText:
//
// Network access is denied.
//
#ifndef STATUS_NETWORK_ACCESS_DENIED
#define STATUS_NETWORK_ACCESS_DENIED     ((NTSTATUS)0xC00000CAL)
#endif//STATUS_NETWORK_ACCESS_DENIED

//
// MessageId: STATUS_BAD_DEVICE_TYPE
//
// MessageText:
//
// {Incorrect Network Resource Type}
// The specified device type (LPT, for example) conflicts with the actual device type on the remote resource.
//
#ifndef STATUS_BAD_DEVICE_TYPE
#define STATUS_BAD_DEVICE_TYPE           ((NTSTATUS)0xC00000CBL)
#endif//STATUS_BAD_DEVICE_TYPE

//
// MessageId: STATUS_BAD_NETWORK_NAME
//
// MessageText:
//
// {Network Name Not Found}
// The specified share name cannot be found on the remote server.
//
#ifndef STATUS_BAD_NETWORK_NAME
#define STATUS_BAD_NETWORK_NAME          ((NTSTATUS)0xC00000CCL)
#endif//STATUS_BAD_NETWORK_NAME

//
// MessageId: STATUS_TOO_MANY_NAMES
//
// MessageText:
//
// The name limit for the local computer network adapter card was exceeded.
//
#ifndef STATUS_TOO_MANY_NAMES
#define STATUS_TOO_MANY_NAMES            ((NTSTATUS)0xC00000CDL)
#endif//STATUS_TOO_MANY_NAMES

//
// MessageId: STATUS_TOO_MANY_SESSIONS
//
// MessageText:
//
// The network BIOS session limit was exceeded.
//
#ifndef STATUS_TOO_MANY_SESSIONS
#define STATUS_TOO_MANY_SESSIONS         ((NTSTATUS)0xC00000CEL)
#endif//STATUS_TOO_MANY_SESSIONS

//
// MessageId: STATUS_SHARING_PAUSED
//
// MessageText:
//
// File sharing has been temporarily paused.
//
#ifndef STATUS_SHARING_PAUSED
#define STATUS_SHARING_PAUSED            ((NTSTATUS)0xC00000CFL)
#endif//STATUS_SHARING_PAUSED

//
// MessageId: STATUS_REQUEST_NOT_ACCEPTED
//
// MessageText:
//
// No more connections can be made to this remote computer at this time because there are already as many connections as the computer can accept.
//
#ifndef STATUS_REQUEST_NOT_ACCEPTED
#define STATUS_REQUEST_NOT_ACCEPTED      ((NTSTATUS)0xC00000D0L)
#endif//STATUS_REQUEST_NOT_ACCEPTED

//
// MessageId: STATUS_REDIRECTOR_PAUSED
//
// MessageText:
//
// Print or disk redirection is temporarily paused.
//
#ifndef STATUS_REDIRECTOR_PAUSED
#define STATUS_REDIRECTOR_PAUSED         ((NTSTATUS)0xC00000D1L)
#endif//STATUS_REDIRECTOR_PAUSED

//
// MessageId: STATUS_NET_WRITE_FAULT
//
// MessageText:
//
// A network data fault occurred.
//
#ifndef STATUS_NET_WRITE_FAULT
#define STATUS_NET_WRITE_FAULT           ((NTSTATUS)0xC00000D2L)
#endif//STATUS_NET_WRITE_FAULT

//
// MessageId: STATUS_PROFILING_AT_LIMIT
//
// MessageText:
//
// The number of active profiling objects is at the maximum and no more may be started.
//
#ifndef STATUS_PROFILING_AT_LIMIT
#define STATUS_PROFILING_AT_LIMIT        ((NTSTATUS)0xC00000D3L)
#endif//STATUS_PROFILING_AT_LIMIT

//
// MessageId: STATUS_NOT_SAME_DEVICE
//
// MessageText:
//
// {Incorrect Volume}
// The target file of a rename request is located on a different device than the source of the rename request.
//
#ifndef STATUS_NOT_SAME_DEVICE
#define STATUS_NOT_SAME_DEVICE           ((NTSTATUS)0xC00000D4L)
#endif//STATUS_NOT_SAME_DEVICE

//
// MessageId: STATUS_FILE_RENAMED
//
// MessageText:
//
// The file specified has been renamed and thus cannot be modified.
//
#ifndef STATUS_FILE_RENAMED
#define STATUS_FILE_RENAMED              ((NTSTATUS)0xC00000D5L)
#endif//STATUS_FILE_RENAMED

//
// MessageId: STATUS_VIRTUAL_CIRCUIT_CLOSED
//
// MessageText:
//
// {Network Request Timeout}
// The session with a remote server has been disconnected because the time-out interval for a request has expired.
//
#ifndef STATUS_VIRTUAL_CIRCUIT_CLOSED
#define STATUS_VIRTUAL_CIRCUIT_CLOSED    ((NTSTATUS)0xC00000D6L)
#endif//STATUS_VIRTUAL_CIRCUIT_CLOSED

//
// MessageId: STATUS_NO_SECURITY_ON_OBJECT
//
// MessageText:
//
// Indicates an attempt was made to operate on the security of an object that does not have security associated with it.
//
#ifndef STATUS_NO_SECURITY_ON_OBJECT
#define STATUS_NO_SECURITY_ON_OBJECT     ((NTSTATUS)0xC00000D7L)
#endif//STATUS_NO_SECURITY_ON_OBJECT

//
// MessageId: STATUS_CANT_WAIT
//
// MessageText:
//
// Used to indicate that an operation cannot continue without blocking for I/O.
//
#ifndef STATUS_CANT_WAIT
#define STATUS_CANT_WAIT                 ((NTSTATUS)0xC00000D8L)
#endif//STATUS_CANT_WAIT

//
// MessageId: STATUS_PIPE_EMPTY
//
// MessageText:
//
// Used to indicate that a read operation was done on an empty pipe.
//
#ifndef STATUS_PIPE_EMPTY
#define STATUS_PIPE_EMPTY                ((NTSTATUS)0xC00000D9L)
#endif//STATUS_PIPE_EMPTY

//
// MessageId: STATUS_CANT_ACCESS_DOMAIN_INFO
//
// MessageText:
//
// Configuration information could not be read from the domain controller, either because the machine is unavailable, or access has been denied.
//
#ifndef STATUS_CANT_ACCESS_DOMAIN_INFO
#define STATUS_CANT_ACCESS_DOMAIN_INFO   ((NTSTATUS)0xC00000DAL)
#endif//STATUS_CANT_ACCESS_DOMAIN_INFO

//
// MessageId: STATUS_CANT_TERMINATE_SELF
//
// MessageText:
//
// Indicates that a thread attempted to terminate itself by default (called NtTerminateThread with NULL) and it was the last thread in the current process.
//
#ifndef STATUS_CANT_TERMINATE_SELF
#define STATUS_CANT_TERMINATE_SELF       ((NTSTATUS)0xC00000DBL)
#endif//STATUS_CANT_TERMINATE_SELF

//
// MessageId: STATUS_INVALID_SERVER_STATE
//
// MessageText:
//
// Indicates the Sam Server was in the wrong state to perform the desired operation.
//
#ifndef STATUS_INVALID_SERVER_STATE
#define STATUS_INVALID_SERVER_STATE      ((NTSTATUS)0xC00000DCL)
#endif//STATUS_INVALID_SERVER_STATE

//
// MessageId: STATUS_INVALID_DOMAIN_STATE
//
// MessageText:
//
// Indicates the Domain was in the wrong state to perform the desired operation.
//
#ifndef STATUS_INVALID_DOMAIN_STATE
#define STATUS_INVALID_DOMAIN_STATE      ((NTSTATUS)0xC00000DDL)
#endif//STATUS_INVALID_DOMAIN_STATE

//
// MessageId: STATUS_INVALID_DOMAIN_ROLE
//
// MessageText:
//
// This operation is only allowed for the Primary Domain Controller of the domain.
//
#ifndef STATUS_INVALID_DOMAIN_ROLE
#define STATUS_INVALID_DOMAIN_ROLE       ((NTSTATUS)0xC00000DEL)
#endif//STATUS_INVALID_DOMAIN_ROLE

//
// MessageId: STATUS_NO_SUCH_DOMAIN
//
// MessageText:
//
// The specified Domain did not exist.
//
#ifndef STATUS_NO_SUCH_DOMAIN
#define STATUS_NO_SUCH_DOMAIN            ((NTSTATUS)0xC00000DFL)
#endif//STATUS_NO_SUCH_DOMAIN

//
// MessageId: STATUS_DOMAIN_EXISTS
//
// MessageText:
//
// The specified Domain already exists.
//
#ifndef STATUS_DOMAIN_EXISTS
#define STATUS_DOMAIN_EXISTS             ((NTSTATUS)0xC00000E0L)
#endif//STATUS_DOMAIN_EXISTS

//
// MessageId: STATUS_DOMAIN_LIMIT_EXCEEDED
//
// MessageText:
//
// An attempt was made to exceed the limit on the number of domains per server for this release.
//
#ifndef STATUS_DOMAIN_LIMIT_EXCEEDED
#define STATUS_DOMAIN_LIMIT_EXCEEDED     ((NTSTATUS)0xC00000E1L)
#endif//STATUS_DOMAIN_LIMIT_EXCEEDED

//
// MessageId: STATUS_OPLOCK_NOT_GRANTED
//
// MessageText:
//
// Error status returned when oplock request is denied.
//
#ifndef STATUS_OPLOCK_NOT_GRANTED
#define STATUS_OPLOCK_NOT_GRANTED        ((NTSTATUS)0xC00000E2L)
#endif//STATUS_OPLOCK_NOT_GRANTED

//
// MessageId: STATUS_INVALID_OPLOCK_PROTOCOL
//
// MessageText:
//
// Error status returned when an invalid oplock acknowledgment is received by a file system.
//
#ifndef STATUS_INVALID_OPLOCK_PROTOCOL
#define STATUS_INVALID_OPLOCK_PROTOCOL   ((NTSTATUS)0xC00000E3L)
#endif//STATUS_INVALID_OPLOCK_PROTOCOL

//
// MessageId: STATUS_INTERNAL_DB_CORRUPTION
//
// MessageText:
//
// This error indicates that the requested operation cannot be completed due to a catastrophic media failure or on-disk data structure corruption.
//
#ifndef STATUS_INTERNAL_DB_CORRUPTION
#define STATUS_INTERNAL_DB_CORRUPTION    ((NTSTATUS)0xC00000E4L)
#endif//STATUS_INTERNAL_DB_CORRUPTION

//
// MessageId: STATUS_INTERNAL_ERROR
//
// MessageText:
//
// An internal error occurred.
//
#ifndef STATUS_INTERNAL_ERROR
#define STATUS_INTERNAL_ERROR            ((NTSTATUS)0xC00000E5L)
#endif//STATUS_INTERNAL_ERROR

//
// MessageId: STATUS_GENERIC_NOT_MAPPED
//
// MessageText:
//
// Indicates generic access types were contained in an access mask which should already be mapped to non-generic access types.
//
#ifndef STATUS_GENERIC_NOT_MAPPED
#define STATUS_GENERIC_NOT_MAPPED        ((NTSTATUS)0xC00000E6L)
#endif//STATUS_GENERIC_NOT_MAPPED

//
// MessageId: STATUS_BAD_DESCRIPTOR_FORMAT
//
// MessageText:
//
// Indicates a security descriptor is not in the necessary format (absolute or self-relative).
//
#ifndef STATUS_BAD_DESCRIPTOR_FORMAT
#define STATUS_BAD_DESCRIPTOR_FORMAT     ((NTSTATUS)0xC00000E7L)
#endif//STATUS_BAD_DESCRIPTOR_FORMAT

//
// Status codes raised by the Cache Manager which must be considered as
// "expected" by its callers.
//
//
// MessageId: STATUS_INVALID_USER_BUFFER
//
// MessageText:
//
// An access to a user buffer failed at an "expected" point in time. This code is defined since the caller does not want to accept STATUS_ACCESS_VIOLATION in its filter.
//
#ifndef STATUS_INVALID_USER_BUFFER
#define STATUS_INVALID_USER_BUFFER       ((NTSTATUS)0xC00000E8L)
#endif//STATUS_INVALID_USER_BUFFER

//
// MessageId: STATUS_UNEXPECTED_IO_ERROR
//
// MessageText:
//
// If an I/O error is returned which is not defined in the standard FsRtl filter, it is converted to the following error which is guaranteed to be in the filter. In this case information is lost, however, the filter correctly handles the exception.
//
#ifndef STATUS_UNEXPECTED_IO_ERROR
#define STATUS_UNEXPECTED_IO_ERROR       ((NTSTATUS)0xC00000E9L)
#endif//STATUS_UNEXPECTED_IO_ERROR

//
// MessageId: STATUS_UNEXPECTED_MM_CREATE_ERR
//
// MessageText:
//
// If an MM error is returned which is not defined in the standard FsRtl filter, it is converted to one of the following errors which is guaranteed to be in the filter. In this case information is lost, however, the filter correctly handles the exception.
//
#ifndef STATUS_UNEXPECTED_MM_CREATE_ERR
#define STATUS_UNEXPECTED_MM_CREATE_ERR  ((NTSTATUS)0xC00000EAL)
#endif//STATUS_UNEXPECTED_MM_CREATE_ERR

//
// MessageId: STATUS_UNEXPECTED_MM_MAP_ERROR
//
// MessageText:
//
// If an MM error is returned which is not defined in the standard FsRtl filter, it is converted to one of the following errors which is guaranteed to be in the filter. In this case information is lost, however, the filter correctly handles the exception.
//
#ifndef STATUS_UNEXPECTED_MM_MAP_ERROR
#define STATUS_UNEXPECTED_MM_MAP_ERROR   ((NTSTATUS)0xC00000EBL)
#endif//STATUS_UNEXPECTED_MM_MAP_ERROR

//
// MessageId: STATUS_UNEXPECTED_MM_EXTEND_ERR
//
// MessageText:
//
// If an MM error is returned which is not defined in the standard FsRtl filter, it is converted to one of the following errors which is guaranteed to be in the filter. In this case information is lost, however, the filter correctly handles the exception.
//
#ifndef STATUS_UNEXPECTED_MM_EXTEND_ERR
#define STATUS_UNEXPECTED_MM_EXTEND_ERR  ((NTSTATUS)0xC00000ECL)
#endif//STATUS_UNEXPECTED_MM_EXTEND_ERR

//
// MessageId: STATUS_NOT_LOGON_PROCESS
//
// MessageText:
//
// The requested action is restricted for use by logon processes only. The calling process has not registered as a logon process.
//
#ifndef STATUS_NOT_LOGON_PROCESS
#define STATUS_NOT_LOGON_PROCESS         ((NTSTATUS)0xC00000EDL)
#endif//STATUS_NOT_LOGON_PROCESS

//
// MessageId: STATUS_LOGON_SESSION_EXISTS
//
// MessageText:
//
// An attempt has been made to start a new session manager or LSA logon session with an ID that is already in use.
//
#ifndef STATUS_LOGON_SESSION_EXISTS
#define STATUS_LOGON_SESSION_EXISTS      ((NTSTATUS)0xC00000EEL)
#endif//STATUS_LOGON_SESSION_EXISTS

//
// MessageId: STATUS_INVALID_PARAMETER_1
//
// MessageText:
//
// An invalid parameter was passed to a service or function as the first argument.
//
#ifndef STATUS_INVALID_PARAMETER_1
#define STATUS_INVALID_PARAMETER_1       ((NTSTATUS)0xC00000EFL)
#endif//STATUS_INVALID_PARAMETER_1

//
// MessageId: STATUS_INVALID_PARAMETER_2
//
// MessageText:
//
// An invalid parameter was passed to a service or function as the second argument.
//
#ifndef STATUS_INVALID_PARAMETER_2
#define STATUS_INVALID_PARAMETER_2       ((NTSTATUS)0xC00000F0L)
#endif//STATUS_INVALID_PARAMETER_2

//
// MessageId: STATUS_INVALID_PARAMETER_3
//
// MessageText:
//
// An invalid parameter was passed to a service or function as the third argument.
//
#ifndef STATUS_INVALID_PARAMETER_3
#define STATUS_INVALID_PARAMETER_3       ((NTSTATUS)0xC00000F1L)
#endif//STATUS_INVALID_PARAMETER_3

//
// MessageId: STATUS_INVALID_PARAMETER_4
//
// MessageText:
//
// An invalid parameter was passed to a service or function as the fourth argument.
//
#ifndef STATUS_INVALID_PARAMETER_4
#define STATUS_INVALID_PARAMETER_4       ((NTSTATUS)0xC00000F2L)
#endif//STATUS_INVALID_PARAMETER_4

//
// MessageId: STATUS_INVALID_PARAMETER_5
//
// MessageText:
//
// An invalid parameter was passed to a service or function as the fifth argument.
//
#ifndef STATUS_INVALID_PARAMETER_5
#define STATUS_INVALID_PARAMETER_5       ((NTSTATUS)0xC00000F3L)
#endif//STATUS_INVALID_PARAMETER_5

//
// MessageId: STATUS_INVALID_PARAMETER_6
//
// MessageText:
//
// An invalid parameter was passed to a service or function as the sixth argument.
//
#ifndef STATUS_INVALID_PARAMETER_6
#define STATUS_INVALID_PARAMETER_6       ((NTSTATUS)0xC00000F4L)
#endif//STATUS_INVALID_PARAMETER_6

//
// MessageId: STATUS_INVALID_PARAMETER_7
//
// MessageText:
//
// An invalid parameter was passed to a service or function as the seventh argument.
//
#ifndef STATUS_INVALID_PARAMETER_7
#define STATUS_INVALID_PARAMETER_7       ((NTSTATUS)0xC00000F5L)
#endif//STATUS_INVALID_PARAMETER_7

//
// MessageId: STATUS_INVALID_PARAMETER_8
//
// MessageText:
//
// An invalid parameter was passed to a service or function as the eighth argument.
//
#ifndef STATUS_INVALID_PARAMETER_8
#define STATUS_INVALID_PARAMETER_8       ((NTSTATUS)0xC00000F6L)
#endif//STATUS_INVALID_PARAMETER_8

//
// MessageId: STATUS_INVALID_PARAMETER_9
//
// MessageText:
//
// An invalid parameter was passed to a service or function as the ninth argument.
//
#ifndef STATUS_INVALID_PARAMETER_9
#define STATUS_INVALID_PARAMETER_9       ((NTSTATUS)0xC00000F7L)
#endif//STATUS_INVALID_PARAMETER_9

//
// MessageId: STATUS_INVALID_PARAMETER_10
//
// MessageText:
//
// An invalid parameter was passed to a service or function as the tenth argument.
//
#ifndef STATUS_INVALID_PARAMETER_10
#define STATUS_INVALID_PARAMETER_10      ((NTSTATUS)0xC00000F8L)
#endif//STATUS_INVALID_PARAMETER_10

//
// MessageId: STATUS_INVALID_PARAMETER_11
//
// MessageText:
//
// An invalid parameter was passed to a service or function as the eleventh argument.
//
#ifndef STATUS_INVALID_PARAMETER_11
#define STATUS_INVALID_PARAMETER_11      ((NTSTATUS)0xC00000F9L)
#endif//STATUS_INVALID_PARAMETER_11

//
// MessageId: STATUS_INVALID_PARAMETER_12
//
// MessageText:
//
// An invalid parameter was passed to a service or function as the twelfth argument.
//
#ifndef STATUS_INVALID_PARAMETER_12
#define STATUS_INVALID_PARAMETER_12      ((NTSTATUS)0xC00000FAL)
#endif//STATUS_INVALID_PARAMETER_12

//
// MessageId: STATUS_REDIRECTOR_NOT_STARTED
//
// MessageText:
//
// An attempt was made to access a network file, but the network software was not yet started.
//
#ifndef STATUS_REDIRECTOR_NOT_STARTED
#define STATUS_REDIRECTOR_NOT_STARTED    ((NTSTATUS)0xC00000FBL)
#endif//STATUS_REDIRECTOR_NOT_STARTED

//
// MessageId: STATUS_REDIRECTOR_STARTED
//
// MessageText:
//
// An attempt was made to start the redirector, but the redirector has already been started.
//
#ifndef STATUS_REDIRECTOR_STARTED
#define STATUS_REDIRECTOR_STARTED        ((NTSTATUS)0xC00000FCL)
#endif//STATUS_REDIRECTOR_STARTED

//
// MessageId: STATUS_STACK_OVERFLOW
//
// MessageText:
//
// A new guard page for the stack cannot be created.
//
#ifndef STATUS_STACK_OVERFLOW
#define STATUS_STACK_OVERFLOW            ((NTSTATUS)0xC00000FDL)    // winnt
#endif//STATUS_STACK_OVERFLOW

//
// MessageId: STATUS_NO_SUCH_PACKAGE
//
// MessageText:
//
// A specified authentication package is unknown.
//
#ifndef STATUS_NO_SUCH_PACKAGE
#define STATUS_NO_SUCH_PACKAGE           ((NTSTATUS)0xC00000FEL)
#endif//STATUS_NO_SUCH_PACKAGE

//
// MessageId: STATUS_BAD_FUNCTION_TABLE
//
// MessageText:
//
// A malformed function table was encountered during an unwind operation.
//
#ifndef STATUS_BAD_FUNCTION_TABLE
#define STATUS_BAD_FUNCTION_TABLE        ((NTSTATUS)0xC00000FFL)
#endif//STATUS_BAD_FUNCTION_TABLE

//
// MessageId: STATUS_VARIABLE_NOT_FOUND
//
// MessageText:
//
// Indicates the specified environment variable name was not found in the specified environment block.
//
#ifndef STATUS_VARIABLE_NOT_FOUND
#define STATUS_VARIABLE_NOT_FOUND        ((NTSTATUS)0xC0000100L)
#endif//STATUS_VARIABLE_NOT_FOUND

//
// MessageId: STATUS_DIRECTORY_NOT_EMPTY
//
// MessageText:
//
// Indicates that the directory trying to be deleted is not empty.
//
#ifndef STATUS_DIRECTORY_NOT_EMPTY
#define STATUS_DIRECTORY_NOT_EMPTY       ((NTSTATUS)0xC0000101L)
#endif//STATUS_DIRECTORY_NOT_EMPTY

//
// MessageId: STATUS_FILE_CORRUPT_ERROR
//
// MessageText:
//
// {Corrupt File}
// The file or directory %hs is corrupt and unreadable.
// Please run the Chkdsk utility.
//
#ifndef STATUS_FILE_CORRUPT_ERROR
#define STATUS_FILE_CORRUPT_ERROR        ((NTSTATUS)0xC0000102L)
#endif//STATUS_FILE_CORRUPT_ERROR

//
// MessageId: STATUS_NOT_A_DIRECTORY
//
// MessageText:
//
// A requested opened file is not a directory.
//
#ifndef STATUS_NOT_A_DIRECTORY
#define STATUS_NOT_A_DIRECTORY           ((NTSTATUS)0xC0000103L)
#endif//STATUS_NOT_A_DIRECTORY

//
// MessageId: STATUS_BAD_LOGON_SESSION_STATE
//
// MessageText:
//
// The logon session is not in a state that is consistent with the requested operation.
//
#ifndef STATUS_BAD_LOGON_SESSION_STATE
#define STATUS_BAD_LOGON_SESSION_STATE   ((NTSTATUS)0xC0000104L)
#endif//STATUS_BAD_LOGON_SESSION_STATE

//
// MessageId: STATUS_LOGON_SESSION_COLLISION
//
// MessageText:
//
// An internal LSA error has occurred. An authentication package has requested the creation of a Logon Session but the ID of an already existing Logon Session has been specified.
//
#ifndef STATUS_LOGON_SESSION_COLLISION
#define STATUS_LOGON_SESSION_COLLISION   ((NTSTATUS)0xC0000105L)
#endif//STATUS_LOGON_SESSION_COLLISION

//
// MessageId: STATUS_NAME_TOO_LONG
//
// MessageText:
//
// A specified name string is too long for its intended use.
//
#ifndef STATUS_NAME_TOO_LONG
#define STATUS_NAME_TOO_LONG             ((NTSTATUS)0xC0000106L)
#endif//STATUS_NAME_TOO_LONG

//
// MessageId: STATUS_FILES_OPEN
//
// MessageText:
//
// The user attempted to force close the files on a redirected drive, but there were opened files on the drive, and the user did not specify a sufficient level of force.
//
#ifndef STATUS_FILES_OPEN
#define STATUS_FILES_OPEN                ((NTSTATUS)0xC0000107L)
#endif//STATUS_FILES_OPEN

//
// MessageId: STATUS_CONNECTION_IN_USE
//
// MessageText:
//
// The user attempted to force close the files on a redirected drive, but there were opened directories on the drive, and the user did not specify a sufficient level of force.
//
#ifndef STATUS_CONNECTION_IN_USE
#define STATUS_CONNECTION_IN_USE         ((NTSTATUS)0xC0000108L)
#endif//STATUS_CONNECTION_IN_USE

//
// MessageId: STATUS_MESSAGE_NOT_FOUND
//
// MessageText:
//
// RtlFindMessage could not locate the requested message ID in the message table resource.
//
#ifndef STATUS_MESSAGE_NOT_FOUND
#define STATUS_MESSAGE_NOT_FOUND         ((NTSTATUS)0xC0000109L)
#endif//STATUS_MESSAGE_NOT_FOUND

//
// MessageId: STATUS_PROCESS_IS_TERMINATING
//
// MessageText:
//
// An attempt was made to access an exiting process.
//
#ifndef STATUS_PROCESS_IS_TERMINATING
#define STATUS_PROCESS_IS_TERMINATING    ((NTSTATUS)0xC000010AL)
#endif//STATUS_PROCESS_IS_TERMINATING

//
// MessageId: STATUS_INVALID_LOGON_TYPE
//
// MessageText:
//
// Indicates an invalid value has been provided for the LogonType requested.
//
#ifndef STATUS_INVALID_LOGON_TYPE
#define STATUS_INVALID_LOGON_TYPE        ((NTSTATUS)0xC000010BL)
#endif//STATUS_INVALID_LOGON_TYPE

//
// MessageId: STATUS_NO_GUID_TRANSLATION
//
// MessageText:
//
// Indicates that an attempt was made to assign protection to a file system file or directory and one of the SIDs in the security descriptor could not be translated into a GUID that could be stored by the file system.
// This causes the protection attempt to fail, which may cause a file creation attempt to fail.
//
#ifndef STATUS_NO_GUID_TRANSLATION
#define STATUS_NO_GUID_TRANSLATION       ((NTSTATUS)0xC000010CL)
#endif//STATUS_NO_GUID_TRANSLATION

//
// MessageId: STATUS_CANNOT_IMPERSONATE
//
// MessageText:
//
// Indicates that an attempt has been made to impersonate via a named pipe that has not yet been read from.
//
#ifndef STATUS_CANNOT_IMPERSONATE
#define STATUS_CANNOT_IMPERSONATE        ((NTSTATUS)0xC000010DL)
#endif//STATUS_CANNOT_IMPERSONATE

//
// MessageId: STATUS_IMAGE_ALREADY_LOADED
//
// MessageText:
//
// Indicates that the specified image is already loaded.
//
#ifndef STATUS_IMAGE_ALREADY_LOADED
#define STATUS_IMAGE_ALREADY_LOADED      ((NTSTATUS)0xC000010EL)
#endif//STATUS_IMAGE_ALREADY_LOADED


//
// ============================================================
// NOTE: The following ABIOS error code should be reserved on
//       non ABIOS kernel. Eventually, I will remove the ifdef
//       ABIOS.
// ============================================================
//
//
// MessageId: STATUS_ABIOS_NOT_PRESENT
//
// MessageText:
//
//  STATUS_ABIOS_NOT_PRESENT
//
#ifndef STATUS_ABIOS_NOT_PRESENT
#define STATUS_ABIOS_NOT_PRESENT         ((NTSTATUS)0xC000010FL)
#endif//STATUS_ABIOS_NOT_PRESENT

//
// MessageId: STATUS_ABIOS_LID_NOT_EXIST
//
// MessageText:
//
//  STATUS_ABIOS_LID_NOT_EXIST
//
#ifndef STATUS_ABIOS_LID_NOT_EXIST
#define STATUS_ABIOS_LID_NOT_EXIST       ((NTSTATUS)0xC0000110L)
#endif//STATUS_ABIOS_LID_NOT_EXIST

//
// MessageId: STATUS_ABIOS_LID_ALREADY_OWNED
//
// MessageText:
//
//  STATUS_ABIOS_LID_ALREADY_OWNED
//
#ifndef STATUS_ABIOS_LID_ALREADY_OWNED
#define STATUS_ABIOS_LID_ALREADY_OWNED   ((NTSTATUS)0xC0000111L)
#endif//STATUS_ABIOS_LID_ALREADY_OWNED

//
// MessageId: STATUS_ABIOS_NOT_LID_OWNER
//
// MessageText:
//
//  STATUS_ABIOS_NOT_LID_OWNER
//
#ifndef STATUS_ABIOS_NOT_LID_OWNER
#define STATUS_ABIOS_NOT_LID_OWNER       ((NTSTATUS)0xC0000112L)
#endif//STATUS_ABIOS_NOT_LID_OWNER

//
// MessageId: STATUS_ABIOS_INVALID_COMMAND
//
// MessageText:
//
//  STATUS_ABIOS_INVALID_COMMAND
//
#ifndef STATUS_ABIOS_INVALID_COMMAND
#define STATUS_ABIOS_INVALID_COMMAND     ((NTSTATUS)0xC0000113L)
#endif//STATUS_ABIOS_INVALID_COMMAND

//
// MessageId: STATUS_ABIOS_INVALID_LID
//
// MessageText:
//
//  STATUS_ABIOS_INVALID_LID
//
#ifndef STATUS_ABIOS_INVALID_LID
#define STATUS_ABIOS_INVALID_LID         ((NTSTATUS)0xC0000114L)
#endif//STATUS_ABIOS_INVALID_LID

//
// MessageId: STATUS_ABIOS_SELECTOR_NOT_AVAILABLE
//
// MessageText:
//
//  STATUS_ABIOS_SELECTOR_NOT_AVAILABLE
//
#ifndef STATUS_ABIOS_SELECTOR_NOT_AVAILABLE
#define STATUS_ABIOS_SELECTOR_NOT_AVAILABLE ((NTSTATUS)0xC0000115L)
#endif//STATUS_ABIOS_SELECTOR_NOT_AVAILABLE

//
// MessageId: STATUS_ABIOS_INVALID_SELECTOR
//
// MessageText:
//
//  STATUS_ABIOS_INVALID_SELECTOR
//
#ifndef STATUS_ABIOS_INVALID_SELECTOR
#define STATUS_ABIOS_INVALID_SELECTOR    ((NTSTATUS)0xC0000116L)
#endif//STATUS_ABIOS_INVALID_SELECTOR

//
// MessageId: STATUS_NO_LDT
//
// MessageText:
//
// Indicates that an attempt was made to change the size of the LDT for a process that has no LDT.
//
#ifndef STATUS_NO_LDT
#define STATUS_NO_LDT                    ((NTSTATUS)0xC0000117L)
#endif//STATUS_NO_LDT

//
// MessageId: STATUS_INVALID_LDT_SIZE
//
// MessageText:
//
// Indicates that an attempt was made to grow an LDT by setting its size, or that the size was not an even number of selectors.
//
#ifndef STATUS_INVALID_LDT_SIZE
#define STATUS_INVALID_LDT_SIZE          ((NTSTATUS)0xC0000118L)
#endif//STATUS_INVALID_LDT_SIZE

//
// MessageId: STATUS_INVALID_LDT_OFFSET
//
// MessageText:
//
// Indicates that the starting value for the LDT information was not an integral multiple of the selector size.
//
#ifndef STATUS_INVALID_LDT_OFFSET
#define STATUS_INVALID_LDT_OFFSET        ((NTSTATUS)0xC0000119L)
#endif//STATUS_INVALID_LDT_OFFSET

//
// MessageId: STATUS_INVALID_LDT_DESCRIPTOR
//
// MessageText:
//
// Indicates that the user supplied an invalid descriptor when trying to set up Ldt descriptors.
//
#ifndef STATUS_INVALID_LDT_DESCRIPTOR
#define STATUS_INVALID_LDT_DESCRIPTOR    ((NTSTATUS)0xC000011AL)
#endif//STATUS_INVALID_LDT_DESCRIPTOR

//
// MessageId: STATUS_INVALID_IMAGE_NE_FORMAT
//
// MessageText:
//
// The specified image file did not have the correct format. It appears to be NE format.
//
#ifndef STATUS_INVALID_IMAGE_NE_FORMAT
#define STATUS_INVALID_IMAGE_NE_FORMAT   ((NTSTATUS)0xC000011BL)
#endif//STATUS_INVALID_IMAGE_NE_FORMAT

//
// MessageId: STATUS_RXACT_INVALID_STATE
//
// MessageText:
//
// Indicates that the transaction state of a registry sub-tree is incompatible with the requested operation. For example, a request has been made to start a new transaction with one already in progress, or a request has been made to apply a transaction when one is not currently in progress.
//
#ifndef STATUS_RXACT_INVALID_STATE
#define STATUS_RXACT_INVALID_STATE       ((NTSTATUS)0xC000011CL)
#endif//STATUS_RXACT_INVALID_STATE

//
// MessageId: STATUS_RXACT_COMMIT_FAILURE
//
// MessageText:
//
// Indicates an error has occurred during a registry transaction commit. The database has been left in an unknown, but probably inconsistent, state. The state of the registry transaction is left as COMMITTING.
//
#ifndef STATUS_RXACT_COMMIT_FAILURE
#define STATUS_RXACT_COMMIT_FAILURE      ((NTSTATUS)0xC000011DL)
#endif//STATUS_RXACT_COMMIT_FAILURE

//
// MessageId: STATUS_MAPPED_FILE_SIZE_ZERO
//
// MessageText:
//
// An attempt was made to map a file of size zero with the maximum size specified as zero.
//
#ifndef STATUS_MAPPED_FILE_SIZE_ZERO
#define STATUS_MAPPED_FILE_SIZE_ZERO     ((NTSTATUS)0xC000011EL)
#endif//STATUS_MAPPED_FILE_SIZE_ZERO

//
// MessageId: STATUS_TOO_MANY_OPENED_FILES
//
// MessageText:
//
// Too many files are opened on a remote server.
// This error should only be returned by the Windows redirector on a remote drive.
//
#ifndef STATUS_TOO_MANY_OPENED_FILES
#define STATUS_TOO_MANY_OPENED_FILES     ((NTSTATUS)0xC000011FL)
#endif//STATUS_TOO_MANY_OPENED_FILES

//
// MessageId: STATUS_CANCELLED
//
// MessageText:
//
// The I/O request was canceled.
//
#ifndef STATUS_CANCELLED
#define STATUS_CANCELLED                 ((NTSTATUS)0xC0000120L)
#endif//STATUS_CANCELLED

//
// MessageId: STATUS_CANNOT_DELETE
//
// MessageText:
//
// An attempt has been made to remove a file or directory that cannot be deleted.
//
#ifndef STATUS_CANNOT_DELETE
#define STATUS_CANNOT_DELETE             ((NTSTATUS)0xC0000121L)
#endif//STATUS_CANNOT_DELETE

//
// MessageId: STATUS_INVALID_COMPUTER_NAME
//
// MessageText:
//
// Indicates a name specified as a remote computer name is syntactically invalid.
//
#ifndef STATUS_INVALID_COMPUTER_NAME
#define STATUS_INVALID_COMPUTER_NAME     ((NTSTATUS)0xC0000122L)
#endif//STATUS_INVALID_COMPUTER_NAME

//
// MessageId: STATUS_FILE_DELETED
//
// MessageText:
//
// An I/O request other than close was performed on a file after it has been deleted, which can only happen to a request which did not complete before the last handle was closed via NtClose.
//
#ifndef STATUS_FILE_DELETED
#define STATUS_FILE_DELETED              ((NTSTATUS)0xC0000123L)
#endif//STATUS_FILE_DELETED

//
// MessageId: STATUS_SPECIAL_ACCOUNT
//
// MessageText:
//
// Indicates an operation has been attempted on a built-in (special) SAM account which is incompatible with built-in accounts. For example, built-in accounts cannot be deleted.
//
#ifndef STATUS_SPECIAL_ACCOUNT
#define STATUS_SPECIAL_ACCOUNT           ((NTSTATUS)0xC0000124L)
#endif//STATUS_SPECIAL_ACCOUNT

//
// MessageId: STATUS_SPECIAL_GROUP
//
// MessageText:
//
// The operation requested may not be performed on the specified group because it is a built-in special group.
//
#ifndef STATUS_SPECIAL_GROUP
#define STATUS_SPECIAL_GROUP             ((NTSTATUS)0xC0000125L)
#endif//STATUS_SPECIAL_GROUP

//
// MessageId: STATUS_SPECIAL_USER
//
// MessageText:
//
// The operation requested may not be performed on the specified user because it is a built-in special user.
//
#ifndef STATUS_SPECIAL_USER
#define STATUS_SPECIAL_USER              ((NTSTATUS)0xC0000126L)
#endif//STATUS_SPECIAL_USER

//
// MessageId: STATUS_MEMBERS_PRIMARY_GROUP
//
// MessageText:
//
// Indicates a member cannot be removed from a group because the group is currently the member's primary group.
//
#ifndef STATUS_MEMBERS_PRIMARY_GROUP
#define STATUS_MEMBERS_PRIMARY_GROUP     ((NTSTATUS)0xC0000127L)
#endif//STATUS_MEMBERS_PRIMARY_GROUP

//
// MessageId: STATUS_FILE_CLOSED
//
// MessageText:
//
// An I/O request other than close and several other special case operations was attempted using a file object that had already been closed.
//
#ifndef STATUS_FILE_CLOSED
#define STATUS_FILE_CLOSED               ((NTSTATUS)0xC0000128L)
#endif//STATUS_FILE_CLOSED

//
// MessageId: STATUS_TOO_MANY_THREADS
//
// MessageText:
//
// Indicates a process has too many threads to perform the requested action. For example, assignment of a primary token may only be performed when a process has zero or one threads.
//
#ifndef STATUS_TOO_MANY_THREADS
#define STATUS_TOO_MANY_THREADS          ((NTSTATUS)0xC0000129L)
#endif//STATUS_TOO_MANY_THREADS

//
// MessageId: STATUS_THREAD_NOT_IN_PROCESS
//
// MessageText:
//
// An attempt was made to operate on a thread within a specific process, but the thread specified is not in the process specified.
//
#ifndef STATUS_THREAD_NOT_IN_PROCESS
#define STATUS_THREAD_NOT_IN_PROCESS     ((NTSTATUS)0xC000012AL)
#endif//STATUS_THREAD_NOT_IN_PROCESS

//
// MessageId: STATUS_TOKEN_ALREADY_IN_USE
//
// MessageText:
//
// An attempt was made to establish a token for use as a primary token but the token is already in use. A token can only be the primary token of one process at a time.
//
#ifndef STATUS_TOKEN_ALREADY_IN_USE
#define STATUS_TOKEN_ALREADY_IN_USE      ((NTSTATUS)0xC000012BL)
#endif//STATUS_TOKEN_ALREADY_IN_USE

//
// MessageId: STATUS_PAGEFILE_QUOTA_EXCEEDED
//
// MessageText:
//
// Page file quota was exceeded.
//
#ifndef STATUS_PAGEFILE_QUOTA_EXCEEDED
#define STATUS_PAGEFILE_QUOTA_EXCEEDED   ((NTSTATUS)0xC000012CL)
#endif//STATUS_PAGEFILE_QUOTA_EXCEEDED

//
// MessageId: STATUS_COMMITMENT_LIMIT
//
// MessageText:
//
// {Out of Virtual Memory}
// Your system is low on virtual memory. To ensure that Windows runs properly, increase the size of your virtual memory paging file. For more information, see Help.
//
#ifndef STATUS_COMMITMENT_LIMIT
#define STATUS_COMMITMENT_LIMIT          ((NTSTATUS)0xC000012DL)
#endif//STATUS_COMMITMENT_LIMIT

//
// MessageId: STATUS_INVALID_IMAGE_LE_FORMAT
//
// MessageText:
//
// The specified image file did not have the correct format, it appears to be LE format.
//
#ifndef STATUS_INVALID_IMAGE_LE_FORMAT
#define STATUS_INVALID_IMAGE_LE_FORMAT   ((NTSTATUS)0xC000012EL)
#endif//STATUS_INVALID_IMAGE_LE_FORMAT

//
// MessageId: STATUS_INVALID_IMAGE_NOT_MZ
//
// MessageText:
//
// The specified image file did not have the correct format, it did not have an initial MZ.
//
#ifndef STATUS_INVALID_IMAGE_NOT_MZ
#define STATUS_INVALID_IMAGE_NOT_MZ      ((NTSTATUS)0xC000012FL)
#endif//STATUS_INVALID_IMAGE_NOT_MZ

//
// MessageId: STATUS_INVALID_IMAGE_PROTECT
//
// MessageText:
//
// The specified image file did not have the correct format, it did not have a proper e_lfarlc in the MZ header.
//
#ifndef STATUS_INVALID_IMAGE_PROTECT
#define STATUS_INVALID_IMAGE_PROTECT     ((NTSTATUS)0xC0000130L)
#endif//STATUS_INVALID_IMAGE_PROTECT

//
// MessageId: STATUS_INVALID_IMAGE_WIN_16
//
// MessageText:
//
// The specified image file did not have the correct format, it appears to be a 16-bit Windows image.
//
#ifndef STATUS_INVALID_IMAGE_WIN_16
#define STATUS_INVALID_IMAGE_WIN_16      ((NTSTATUS)0xC0000131L)
#endif//STATUS_INVALID_IMAGE_WIN_16

//
// MessageId: STATUS_LOGON_SERVER_CONFLICT
//
// MessageText:
//
// The Netlogon service cannot start because another Netlogon service running in the domain conflicts with the specified role.
//
#ifndef STATUS_LOGON_SERVER_CONFLICT
#define STATUS_LOGON_SERVER_CONFLICT     ((NTSTATUS)0xC0000132L)
#endif//STATUS_LOGON_SERVER_CONFLICT

//
// MessageId: STATUS_TIME_DIFFERENCE_AT_DC
//
// MessageText:
//
// The time at the Primary Domain Controller is different than the time at the Backup Domain Controller or member server by too large an amount.
//
#ifndef STATUS_TIME_DIFFERENCE_AT_DC
#define STATUS_TIME_DIFFERENCE_AT_DC     ((NTSTATUS)0xC0000133L)
#endif//STATUS_TIME_DIFFERENCE_AT_DC

//
// MessageId: STATUS_SYNCHRONIZATION_REQUIRED
//
// MessageText:
//
// The SAM database on a Windows Server is significantly out of synchronization with the copy on the Domain Controller. A complete synchronization is required.
//
#ifndef STATUS_SYNCHRONIZATION_REQUIRED
#define STATUS_SYNCHRONIZATION_REQUIRED  ((NTSTATUS)0xC0000134L)
#endif//STATUS_SYNCHRONIZATION_REQUIRED

//
// MessageId: STATUS_DLL_NOT_FOUND
//
// MessageText:
//
// The code execution cannot proceed because %hs was not found. Reinstalling the program may fix this problem.
//
#ifndef STATUS_DLL_NOT_FOUND
#define STATUS_DLL_NOT_FOUND             ((NTSTATUS)0xC0000135L)    // winnt
#endif//STATUS_DLL_NOT_FOUND

//
// MessageId: STATUS_OPEN_FAILED
//
// MessageText:
//
// The NtCreateFile API failed. This error should never be returned to an application, it is a place holder for the Windows Lan Manager Redirector to use in its internal error mapping routines.
//
#ifndef STATUS_OPEN_FAILED
#define STATUS_OPEN_FAILED               ((NTSTATUS)0xC0000136L)
#endif//STATUS_OPEN_FAILED

//
// MessageId: STATUS_IO_PRIVILEGE_FAILED
//
// MessageText:
//
// {Privilege Failed}
// The I/O permissions for the process could not be changed.
//
#ifndef STATUS_IO_PRIVILEGE_FAILED
#define STATUS_IO_PRIVILEGE_FAILED       ((NTSTATUS)0xC0000137L)
#endif//STATUS_IO_PRIVILEGE_FAILED

//
// MessageId: STATUS_ORDINAL_NOT_FOUND
//
// MessageText:
//
// {Ordinal Not Found}
// The ordinal %ld could not be located in the dynamic link library %hs.
//
#ifndef STATUS_ORDINAL_NOT_FOUND
#define STATUS_ORDINAL_NOT_FOUND         ((NTSTATUS)0xC0000138L)    // winnt
#endif//STATUS_ORDINAL_NOT_FOUND

//
// MessageId: STATUS_ENTRYPOINT_NOT_FOUND
//
// MessageText:
//
// {Entry Point Not Found}
// The procedure entry point %hs could not be located in the dynamic link library %hs.
//
#ifndef STATUS_ENTRYPOINT_NOT_FOUND
#define STATUS_ENTRYPOINT_NOT_FOUND      ((NTSTATUS)0xC0000139L)    // winnt
#endif//STATUS_ENTRYPOINT_NOT_FOUND

//
// MessageId: STATUS_CONTROL_C_EXIT
//
// MessageText:
//
// {Application Exit by CTRL+C}
// The application terminated as a result of a CTRL+C.
//
#ifndef STATUS_CONTROL_C_EXIT
#define STATUS_CONTROL_C_EXIT            ((NTSTATUS)0xC000013AL)    // winnt
#endif//STATUS_CONTROL_C_EXIT

//
// MessageId: STATUS_LOCAL_DISCONNECT
//
// MessageText:
//
// {Virtual Circuit Closed}
// The network transport on your computer has closed a network connection. There may or may not be I/O requests outstanding.
//
#ifndef STATUS_LOCAL_DISCONNECT
#define STATUS_LOCAL_DISCONNECT          ((NTSTATUS)0xC000013BL)
#endif//STATUS_LOCAL_DISCONNECT

//
// MessageId: STATUS_REMOTE_DISCONNECT
//
// MessageText:
//
// {Virtual Circuit Closed}
// The network transport on a remote computer has closed a network connection. There may or may not be I/O requests outstanding.
//
#ifndef STATUS_REMOTE_DISCONNECT
#define STATUS_REMOTE_DISCONNECT         ((NTSTATUS)0xC000013CL)
#endif//STATUS_REMOTE_DISCONNECT

//
// MessageId: STATUS_REMOTE_RESOURCES
//
// MessageText:
//
// {Insufficient Resources on Remote Computer}
// The remote computer has insufficient resources to complete the network request. For instance, there may not be enough memory available on the remote computer to carry out the request at this time.
//
#ifndef STATUS_REMOTE_RESOURCES
#define STATUS_REMOTE_RESOURCES          ((NTSTATUS)0xC000013DL)
#endif//STATUS_REMOTE_RESOURCES

//
// MessageId: STATUS_LINK_FAILED
//
// MessageText:
//
// {Virtual Circuit Closed}
// An existing connection (virtual circuit) has been broken at the remote computer. There is probably something wrong with the network software protocol or the network hardware on the remote computer.
//
#ifndef STATUS_LINK_FAILED
#define STATUS_LINK_FAILED               ((NTSTATUS)0xC000013EL)
#endif//STATUS_LINK_FAILED

//
// MessageId: STATUS_LINK_TIMEOUT
//
// MessageText:
//
// {Virtual Circuit Closed}
// The network transport on your computer has closed a network connection because it had to wait too long for a response from the remote computer.
//
#ifndef STATUS_LINK_TIMEOUT
#define STATUS_LINK_TIMEOUT              ((NTSTATUS)0xC000013FL)
#endif//STATUS_LINK_TIMEOUT

//
// MessageId: STATUS_INVALID_CONNECTION
//
// MessageText:
//
// The connection handle given to the transport was invalid.
//
#ifndef STATUS_INVALID_CONNECTION
#define STATUS_INVALID_CONNECTION        ((NTSTATUS)0xC0000140L)
#endif//STATUS_INVALID_CONNECTION

//
// MessageId: STATUS_INVALID_ADDRESS
//
// MessageText:
//
// The address handle given to the transport was invalid.
//
#ifndef STATUS_INVALID_ADDRESS
#define STATUS_INVALID_ADDRESS           ((NTSTATUS)0xC0000141L)
#endif//STATUS_INVALID_ADDRESS

//
// MessageId: STATUS_DLL_INIT_FAILED
//
// MessageText:
//
// {DLL Initialization Failed}
// Initialization of the dynamic link library %hs failed. The process is terminating abnormally.
//
#ifndef STATUS_DLL_INIT_FAILED
#define STATUS_DLL_INIT_FAILED           ((NTSTATUS)0xC0000142L)    // winnt
#endif//STATUS_DLL_INIT_FAILED

//
// MessageId: STATUS_MISSING_SYSTEMFILE
//
// MessageText:
//
// {Missing System File}
// The required system file %hs is bad or missing.
//
#ifndef STATUS_MISSING_SYSTEMFILE
#define STATUS_MISSING_SYSTEMFILE        ((NTSTATUS)0xC0000143L)
#endif//STATUS_MISSING_SYSTEMFILE

//
// MessageId: STATUS_UNHANDLED_EXCEPTION
//
// MessageText:
//
// {Application Error}
// The exception %s (0x%08lx) occurred in the application at location 0x%p.
//
#ifndef STATUS_UNHANDLED_EXCEPTION
#define STATUS_UNHANDLED_EXCEPTION       ((NTSTATUS)0xC0000144L)
#endif//STATUS_UNHANDLED_EXCEPTION

//
// MessageId: STATUS_APP_INIT_FAILURE
//
// MessageText:
//
// {Application Error}
// The application was unable to start correctly (0x%lx). Click OK to close the application.
//
#ifndef STATUS_APP_INIT_FAILURE
#define STATUS_APP_INIT_FAILURE          ((NTSTATUS)0xC0000145L)
#endif//STATUS_APP_INIT_FAILURE

//
// MessageId: STATUS_PAGEFILE_CREATE_FAILED
//
// MessageText:
//
// {Unable to Create Paging File}
// The creation of the paging file %hs failed (%lx). The requested size was %ld.
//
#ifndef STATUS_PAGEFILE_CREATE_FAILED
#define STATUS_PAGEFILE_CREATE_FAILED    ((NTSTATUS)0xC0000146L)
#endif//STATUS_PAGEFILE_CREATE_FAILED

//
// MessageId: STATUS_NO_PAGEFILE
//
// MessageText:
//
// {No Paging File Specified}
// No paging file was specified in the system configuration.
//
#ifndef STATUS_NO_PAGEFILE
#define STATUS_NO_PAGEFILE               ((NTSTATUS)0xC0000147L)
#endif//STATUS_NO_PAGEFILE

//
// MessageId: STATUS_INVALID_LEVEL
//
// MessageText:
//
// {Incorrect System Call Level}
// An invalid level was passed into the specified system call.
//
#ifndef STATUS_INVALID_LEVEL
#define STATUS_INVALID_LEVEL             ((NTSTATUS)0xC0000148L)
#endif//STATUS_INVALID_LEVEL

//
// MessageId: STATUS_WRONG_PASSWORD_CORE
//
// MessageText:
//
// {Incorrect Password to LAN Manager Server}
// You specified an incorrect password to a LAN Manager 2.x or MS-NET server.
//
#ifndef STATUS_WRONG_PASSWORD_CORE
#define STATUS_WRONG_PASSWORD_CORE       ((NTSTATUS)0xC0000149L)
#endif//STATUS_WRONG_PASSWORD_CORE

//
// MessageId: STATUS_ILLEGAL_FLOAT_CONTEXT
//
// MessageText:
//
// {EXCEPTION}
// A real-mode application issued a floating-point instruction and floating-point hardware is not present.
//
#ifndef STATUS_ILLEGAL_FLOAT_CONTEXT
#define STATUS_ILLEGAL_FLOAT_CONTEXT     ((NTSTATUS)0xC000014AL)
#endif//STATUS_ILLEGAL_FLOAT_CONTEXT

//
// MessageId: STATUS_PIPE_BROKEN
//
// MessageText:
//
// The pipe operation has failed because the other end of the pipe has been closed.
//
#ifndef STATUS_PIPE_BROKEN
#define STATUS_PIPE_BROKEN               ((NTSTATUS)0xC000014BL)
#endif//STATUS_PIPE_BROKEN

//
// MessageId: STATUS_REGISTRY_CORRUPT
//
// MessageText:
//
// {The Registry Is Corrupt}
// The structure of one of the files that contains Registry data is corrupt, or the image of the file in memory is corrupt, or the file could not be recovered because the alternate copy or log was absent or corrupt.
//
#ifndef STATUS_REGISTRY_CORRUPT
#define STATUS_REGISTRY_CORRUPT          ((NTSTATUS)0xC000014CL)
#endif//STATUS_REGISTRY_CORRUPT

//
// MessageId: STATUS_REGISTRY_IO_FAILED
//
// MessageText:
//
// An I/O operation initiated by the Registry failed unrecoverably. The Registry could not read in, or write out, or flush, one of the files that contain the system's image of the Registry.
//
#ifndef STATUS_REGISTRY_IO_FAILED
#define STATUS_REGISTRY_IO_FAILED        ((NTSTATUS)0xC000014DL)
#endif//STATUS_REGISTRY_IO_FAILED

//
// MessageId: STATUS_NO_EVENT_PAIR
//
// MessageText:
//
// An event pair synchronization operation was performed using the thread specific client/server event pair object, but no event pair object was associated with the thread.
//
#ifndef STATUS_NO_EVENT_PAIR
#define STATUS_NO_EVENT_PAIR             ((NTSTATUS)0xC000014EL)
#endif//STATUS_NO_EVENT_PAIR

//
// MessageId: STATUS_UNRECOGNIZED_VOLUME
//
// MessageText:
//
// The volume does not contain a recognized file system. Please make sure that all required file system drivers are loaded and that the volume is not corrupt.
//
#ifndef STATUS_UNRECOGNIZED_VOLUME
#define STATUS_UNRECOGNIZED_VOLUME       ((NTSTATUS)0xC000014FL)
#endif//STATUS_UNRECOGNIZED_VOLUME

//
// MessageId: STATUS_SERIAL_NO_DEVICE_INITED
//
// MessageText:
//
// No serial device was successfully initialized. The serial driver will unload.
//
#ifndef STATUS_SERIAL_NO_DEVICE_INITED
#define STATUS_SERIAL_NO_DEVICE_INITED   ((NTSTATUS)0xC0000150L)
#endif//STATUS_SERIAL_NO_DEVICE_INITED

//
// MessageId: STATUS_NO_SUCH_ALIAS
//
// MessageText:
//
// The specified local group does not exist.
//
#ifndef STATUS_NO_SUCH_ALIAS
#define STATUS_NO_SUCH_ALIAS             ((NTSTATUS)0xC0000151L)
#endif//STATUS_NO_SUCH_ALIAS

//
// MessageId: STATUS_MEMBER_NOT_IN_ALIAS
//
// MessageText:
//
// The specified account name is not a member of the group.
//
#ifndef STATUS_MEMBER_NOT_IN_ALIAS
#define STATUS_MEMBER_NOT_IN_ALIAS       ((NTSTATUS)0xC0000152L)
#endif//STATUS_MEMBER_NOT_IN_ALIAS

//
// MessageId: STATUS_MEMBER_IN_ALIAS
//
// MessageText:
//
// The specified account name is already a member of the group.
//
#ifndef STATUS_MEMBER_IN_ALIAS
#define STATUS_MEMBER_IN_ALIAS           ((NTSTATUS)0xC0000153L)
#endif//STATUS_MEMBER_IN_ALIAS

//
// MessageId: STATUS_ALIAS_EXISTS
//
// MessageText:
//
// The specified local group already exists.
//
#ifndef STATUS_ALIAS_EXISTS
#define STATUS_ALIAS_EXISTS              ((NTSTATUS)0xC0000154L)
#endif//STATUS_ALIAS_EXISTS

//
// MessageId: STATUS_LOGON_NOT_GRANTED
//
// MessageText:
//
// A requested type of logon (e.g., Interactive, Network, Service) is not granted by the target system's local security policy.
// Please ask the system administrator to grant the necessary form of logon.
//
#ifndef STATUS_LOGON_NOT_GRANTED
#define STATUS_LOGON_NOT_GRANTED         ((NTSTATUS)0xC0000155L)
#endif//STATUS_LOGON_NOT_GRANTED

//
// MessageId: STATUS_TOO_MANY_SECRETS
//
// MessageText:
//
// The maximum number of secrets that may be stored in a single system has been exceeded. The length and number of secrets is limited to satisfy United States State Department export restrictions.
//
#ifndef STATUS_TOO_MANY_SECRETS
#define STATUS_TOO_MANY_SECRETS          ((NTSTATUS)0xC0000156L)
#endif//STATUS_TOO_MANY_SECRETS

//
// MessageId: STATUS_SECRET_TOO_LONG
//
// MessageText:
//
// The length of a secret exceeds the maximum length allowed. The length and number of secrets is limited to satisfy United States State Department export restrictions.
//
#ifndef STATUS_SECRET_TOO_LONG
#define STATUS_SECRET_TOO_LONG           ((NTSTATUS)0xC0000157L)
#endif//STATUS_SECRET_TOO_LONG

//
// MessageId: STATUS_INTERNAL_DB_ERROR
//
// MessageText:
//
// The Local Security Authority (LSA) database contains an internal inconsistency.
//
#ifndef STATUS_INTERNAL_DB_ERROR
#define STATUS_INTERNAL_DB_ERROR         ((NTSTATUS)0xC0000158L)
#endif//STATUS_INTERNAL_DB_ERROR

//
// MessageId: STATUS_FULLSCREEN_MODE
//
// MessageText:
//
// The requested operation cannot be performed in fullscreen mode.
//
#ifndef STATUS_FULLSCREEN_MODE
#define STATUS_FULLSCREEN_MODE           ((NTSTATUS)0xC0000159L)
#endif//STATUS_FULLSCREEN_MODE

//
// MessageId: STATUS_TOO_MANY_CONTEXT_IDS
//
// MessageText:
//
// During a logon attempt, the user's security context accumulated too many security IDs. This is a very unusual situation. Remove the user from some global or local groups to reduce the number of security ids to incorporate into the security context.
//
#ifndef STATUS_TOO_MANY_CONTEXT_IDS
#define STATUS_TOO_MANY_CONTEXT_IDS      ((NTSTATUS)0xC000015AL)
#endif//STATUS_TOO_MANY_CONTEXT_IDS

//
// MessageId: STATUS_LOGON_TYPE_NOT_GRANTED
//
// MessageText:
//
// A user has requested a type of logon (e.g., interactive or network) that has not been granted. An administrator has control over who may logon interactively and through the network.
//
#ifndef STATUS_LOGON_TYPE_NOT_GRANTED
#define STATUS_LOGON_TYPE_NOT_GRANTED    ((NTSTATUS)0xC000015BL)
#endif//STATUS_LOGON_TYPE_NOT_GRANTED

//
// MessageId: STATUS_NOT_REGISTRY_FILE
//
// MessageText:
//
// The system has attempted to load or restore a file into the registry, and the specified file is not in the format of a registry file.
//
#ifndef STATUS_NOT_REGISTRY_FILE
#define STATUS_NOT_REGISTRY_FILE         ((NTSTATUS)0xC000015CL)
#endif//STATUS_NOT_REGISTRY_FILE

//
// MessageId: STATUS_NT_CROSS_ENCRYPTION_REQUIRED
//
// MessageText:
//
// An attempt was made to change a user password in the security account manager without providing the necessary Windows cross-encrypted password.
//
#ifndef STATUS_NT_CROSS_ENCRYPTION_REQUIRED
#define STATUS_NT_CROSS_ENCRYPTION_REQUIRED ((NTSTATUS)0xC000015DL)
#endif//STATUS_NT_CROSS_ENCRYPTION_REQUIRED

//
// MessageId: STATUS_DOMAIN_CTRLR_CONFIG_ERROR
//
// MessageText:
//
// A Windows Server has an incorrect configuration.
//
#ifndef STATUS_DOMAIN_CTRLR_CONFIG_ERROR
#define STATUS_DOMAIN_CTRLR_CONFIG_ERROR ((NTSTATUS)0xC000015EL)
#endif//STATUS_DOMAIN_CTRLR_CONFIG_ERROR

//
// MessageId: STATUS_FT_MISSING_MEMBER
//
// MessageText:
//
// An attempt was made to explicitly access the secondary copy of information via a device control to the Fault Tolerance driver and the secondary copy is not present in the system.
//
#ifndef STATUS_FT_MISSING_MEMBER
#define STATUS_FT_MISSING_MEMBER         ((NTSTATUS)0xC000015FL)
#endif//STATUS_FT_MISSING_MEMBER

//
// MessageId: STATUS_ILL_FORMED_SERVICE_ENTRY
//
// MessageText:
//
// A configuration registry node representing a driver service entry was ill-formed and did not contain required value entries.
//
#ifndef STATUS_ILL_FORMED_SERVICE_ENTRY
#define STATUS_ILL_FORMED_SERVICE_ENTRY  ((NTSTATUS)0xC0000160L)
#endif//STATUS_ILL_FORMED_SERVICE_ENTRY

//
// MessageId: STATUS_ILLEGAL_CHARACTER
//
// MessageText:
//
// An illegal character was encountered. For a multi-byte character set this includes a lead byte without a succeeding trail byte. For the Unicode character set this includes the characters 0xFFFF and 0xFFFE.
//
#ifndef STATUS_ILLEGAL_CHARACTER
#define STATUS_ILLEGAL_CHARACTER         ((NTSTATUS)0xC0000161L)
#endif//STATUS_ILLEGAL_CHARACTER

//
// MessageId: STATUS_UNMAPPABLE_CHARACTER
//
// MessageText:
//
// No mapping for the Unicode character exists in the target multi-byte code page.
//
#ifndef STATUS_UNMAPPABLE_CHARACTER
#define STATUS_UNMAPPABLE_CHARACTER      ((NTSTATUS)0xC0000162L)
#endif//STATUS_UNMAPPABLE_CHARACTER

//
// MessageId: STATUS_UNDEFINED_CHARACTER
//
// MessageText:
//
// The Unicode character is not defined in the Unicode character set installed on the system.
//
#ifndef STATUS_UNDEFINED_CHARACTER
#define STATUS_UNDEFINED_CHARACTER       ((NTSTATUS)0xC0000163L)
#endif//STATUS_UNDEFINED_CHARACTER

//
// MessageId: STATUS_FLOPPY_VOLUME
//
// MessageText:
//
// The paging file cannot be created on a floppy diskette.
//
#ifndef STATUS_FLOPPY_VOLUME
#define STATUS_FLOPPY_VOLUME             ((NTSTATUS)0xC0000164L)
#endif//STATUS_FLOPPY_VOLUME

//
// MessageId: STATUS_FLOPPY_ID_MARK_NOT_FOUND
//
// MessageText:
//
// {Floppy Disk Error}
// While accessing a floppy disk, an ID address mark was not found.
//
#ifndef STATUS_FLOPPY_ID_MARK_NOT_FOUND
#define STATUS_FLOPPY_ID_MARK_NOT_FOUND  ((NTSTATUS)0xC0000165L)
#endif//STATUS_FLOPPY_ID_MARK_NOT_FOUND

//
// MessageId: STATUS_FLOPPY_WRONG_CYLINDER
//
// MessageText:
//
// {Floppy Disk Error}
// While accessing a floppy disk, the track address from the sector ID field was found to be different than the track address maintained by the controller.
//
#ifndef STATUS_FLOPPY_WRONG_CYLINDER
#define STATUS_FLOPPY_WRONG_CYLINDER     ((NTSTATUS)0xC0000166L)
#endif//STATUS_FLOPPY_WRONG_CYLINDER

//
// MessageId: STATUS_FLOPPY_UNKNOWN_ERROR
//
// MessageText:
//
// {Floppy Disk Error}
// The floppy disk controller reported an error that is not recognized by the floppy disk driver.
//
#ifndef STATUS_FLOPPY_UNKNOWN_ERROR
#define STATUS_FLOPPY_UNKNOWN_ERROR      ((NTSTATUS)0xC0000167L)
#endif//STATUS_FLOPPY_UNKNOWN_ERROR

//
// MessageId: STATUS_FLOPPY_BAD_REGISTERS
//
// MessageText:
//
// {Floppy Disk Error}
// While accessing a floppy-disk, the controller returned inconsistent results via its registers.
//
#ifndef STATUS_FLOPPY_BAD_REGISTERS
#define STATUS_FLOPPY_BAD_REGISTERS      ((NTSTATUS)0xC0000168L)
#endif//STATUS_FLOPPY_BAD_REGISTERS

//
// MessageId: STATUS_DISK_RECALIBRATE_FAILED
//
// MessageText:
//
// {Hard Disk Error}
// While accessing the hard disk, a recalibrate operation failed, even after retries.
//
#ifndef STATUS_DISK_RECALIBRATE_FAILED
#define STATUS_DISK_RECALIBRATE_FAILED   ((NTSTATUS)0xC0000169L)
#endif//STATUS_DISK_RECALIBRATE_FAILED

//
// MessageId: STATUS_DISK_OPERATION_FAILED
//
// MessageText:
//
// {Hard Disk Error}
// While accessing the hard disk, a disk operation failed even after retries.
//
#ifndef STATUS_DISK_OPERATION_FAILED
#define STATUS_DISK_OPERATION_FAILED     ((NTSTATUS)0xC000016AL)
#endif//STATUS_DISK_OPERATION_FAILED

//
// MessageId: STATUS_DISK_RESET_FAILED
//
// MessageText:
//
// {Hard Disk Error}
// While accessing the hard disk, a disk controller reset was needed, but even that failed.
//
#ifndef STATUS_DISK_RESET_FAILED
#define STATUS_DISK_RESET_FAILED         ((NTSTATUS)0xC000016BL)
#endif//STATUS_DISK_RESET_FAILED

//
// MessageId: STATUS_SHARED_IRQ_BUSY
//
// MessageText:
//
// An attempt was made to open a device that was sharing an IRQ with other devices.
// At least one other device that uses that IRQ was already opened.
// Two concurrent opens of devices that share an IRQ and only work via interrupts is not supported for the particular bus type that the devices use.
//
#ifndef STATUS_SHARED_IRQ_BUSY
#define STATUS_SHARED_IRQ_BUSY           ((NTSTATUS)0xC000016CL)
#endif//STATUS_SHARED_IRQ_BUSY

//
// MessageId: STATUS_FT_ORPHANING
//
// MessageText:
//
// {FT Orphaning}
// A disk that is part of a fault-tolerant volume can no longer be accessed.
//
#ifndef STATUS_FT_ORPHANING
#define STATUS_FT_ORPHANING              ((NTSTATUS)0xC000016DL)
#endif//STATUS_FT_ORPHANING

//
// MessageId: STATUS_BIOS_FAILED_TO_CONNECT_INTERRUPT
//
// MessageText:
//
// The system bios failed to connect a system interrupt to the device or bus for which the device is connected.
//
#ifndef STATUS_BIOS_FAILED_TO_CONNECT_INTERRUPT
#define STATUS_BIOS_FAILED_TO_CONNECT_INTERRUPT ((NTSTATUS)0xC000016EL)
#endif//STATUS_BIOS_FAILED_TO_CONNECT_INTERRUPT

//
// MessageId: STATUS_PARTITION_FAILURE
//
// MessageText:
//
// Tape could not be partitioned.
//
#ifndef STATUS_PARTITION_FAILURE
#define STATUS_PARTITION_FAILURE         ((NTSTATUS)0xC0000172L)
#endif//STATUS_PARTITION_FAILURE

//
// MessageId: STATUS_INVALID_BLOCK_LENGTH
//
// MessageText:
//
// When accessing a new tape of a multivolume partition, the current blocksize is incorrect.
//
#ifndef STATUS_INVALID_BLOCK_LENGTH
#define STATUS_INVALID_BLOCK_LENGTH      ((NTSTATUS)0xC0000173L)
#endif//STATUS_INVALID_BLOCK_LENGTH

//
// MessageId: STATUS_DEVICE_NOT_PARTITIONED
//
// MessageText:
//
// Tape partition information could not be found when loading a tape.
//
#ifndef STATUS_DEVICE_NOT_PARTITIONED
#define STATUS_DEVICE_NOT_PARTITIONED    ((NTSTATUS)0xC0000174L)
#endif//STATUS_DEVICE_NOT_PARTITIONED

//
// MessageId: STATUS_UNABLE_TO_LOCK_MEDIA
//
// MessageText:
//
// Attempt to lock the eject media mechanism fails.
//
#ifndef STATUS_UNABLE_TO_LOCK_MEDIA
#define STATUS_UNABLE_TO_LOCK_MEDIA      ((NTSTATUS)0xC0000175L)
#endif//STATUS_UNABLE_TO_LOCK_MEDIA

//
// MessageId: STATUS_UNABLE_TO_UNLOAD_MEDIA
//
// MessageText:
//
// Unload media fails.
//
#ifndef STATUS_UNABLE_TO_UNLOAD_MEDIA
#define STATUS_UNABLE_TO_UNLOAD_MEDIA    ((NTSTATUS)0xC0000176L)
#endif//STATUS_UNABLE_TO_UNLOAD_MEDIA

//
// MessageId: STATUS_EOM_OVERFLOW
//
// MessageText:
//
// Physical end of tape was detected.
//
#ifndef STATUS_EOM_OVERFLOW
#define STATUS_EOM_OVERFLOW              ((NTSTATUS)0xC0000177L)
#endif//STATUS_EOM_OVERFLOW

//
// MessageId: STATUS_NO_MEDIA
//
// MessageText:
//
// {No Media}
// There is no media in the drive. Please insert media into drive %hs.
//
#ifndef STATUS_NO_MEDIA
#define STATUS_NO_MEDIA                  ((NTSTATUS)0xC0000178L)
#endif//STATUS_NO_MEDIA

//
// MessageId: STATUS_NO_SUCH_MEMBER
//
// MessageText:
//
// A member could not be added to or removed from the local group because the member does not exist.
//
#ifndef STATUS_NO_SUCH_MEMBER
#define STATUS_NO_SUCH_MEMBER            ((NTSTATUS)0xC000017AL)
#endif//STATUS_NO_SUCH_MEMBER

//
// MessageId: STATUS_INVALID_MEMBER
//
// MessageText:
//
// A new member could not be added to a local group because the member has the wrong account type.
//
#ifndef STATUS_INVALID_MEMBER
#define STATUS_INVALID_MEMBER            ((NTSTATUS)0xC000017BL)
#endif//STATUS_INVALID_MEMBER

//
// MessageId: STATUS_KEY_DELETED
//
// MessageText:
//
// Illegal operation attempted on a registry key which has been marked for deletion.
//
#ifndef STATUS_KEY_DELETED
#define STATUS_KEY_DELETED               ((NTSTATUS)0xC000017CL)
#endif//STATUS_KEY_DELETED

//
// MessageId: STATUS_NO_LOG_SPACE
//
// MessageText:
//
// System could not allocate required space in a registry log.
//
#ifndef STATUS_NO_LOG_SPACE
#define STATUS_NO_LOG_SPACE              ((NTSTATUS)0xC000017DL)
#endif//STATUS_NO_LOG_SPACE

//
// MessageId: STATUS_TOO_MANY_SIDS
//
// MessageText:
//
// Too many Sids have been specified.
//
#ifndef STATUS_TOO_MANY_SIDS
#define STATUS_TOO_MANY_SIDS             ((NTSTATUS)0xC000017EL)
#endif//STATUS_TOO_MANY_SIDS

//
// MessageId: STATUS_LM_CROSS_ENCRYPTION_REQUIRED
//
// MessageText:
//
// An attempt was made to change a user password in the security account manager without providing the necessary LM cross-encrypted password.
//
#ifndef STATUS_LM_CROSS_ENCRYPTION_REQUIRED
#define STATUS_LM_CROSS_ENCRYPTION_REQUIRED ((NTSTATUS)0xC000017FL)
#endif//STATUS_LM_CROSS_ENCRYPTION_REQUIRED

//
// MessageId: STATUS_KEY_HAS_CHILDREN
//
// MessageText:
//
// An attempt was made to create a symbolic link in a registry key that already has subkeys or values.
//
#ifndef STATUS_KEY_HAS_CHILDREN
#define STATUS_KEY_HAS_CHILDREN          ((NTSTATUS)0xC0000180L)
#endif//STATUS_KEY_HAS_CHILDREN

//
// MessageId: STATUS_CHILD_MUST_BE_VOLATILE
//
// MessageText:
//
// An attempt was made to create a Stable subkey under a Volatile parent key.
//
#ifndef STATUS_CHILD_MUST_BE_VOLATILE
#define STATUS_CHILD_MUST_BE_VOLATILE    ((NTSTATUS)0xC0000181L)
#endif//STATUS_CHILD_MUST_BE_VOLATILE

//
// MessageId: STATUS_DEVICE_CONFIGURATION_ERROR
//
// MessageText:
//
// The I/O device is configured incorrectly or the configuration parameters to the driver are incorrect.
//
#ifndef STATUS_DEVICE_CONFIGURATION_ERROR
#define STATUS_DEVICE_CONFIGURATION_ERROR ((NTSTATUS)0xC0000182L)
#endif//STATUS_DEVICE_CONFIGURATION_ERROR

//
// MessageId: STATUS_DRIVER_INTERNAL_ERROR
//
// MessageText:
//
// An error was detected between two drivers or within an I/O driver.
//
#ifndef STATUS_DRIVER_INTERNAL_ERROR
#define STATUS_DRIVER_INTERNAL_ERROR     ((NTSTATUS)0xC0000183L)
#endif//STATUS_DRIVER_INTERNAL_ERROR

//
// MessageId: STATUS_INVALID_DEVICE_STATE
//
// MessageText:
//
// The device is not in a valid state to perform this request.
//
#ifndef STATUS_INVALID_DEVICE_STATE
#define STATUS_INVALID_DEVICE_STATE      ((NTSTATUS)0xC0000184L)
#endif//STATUS_INVALID_DEVICE_STATE

//
// MessageId: STATUS_IO_DEVICE_ERROR
//
// MessageText:
//
// The I/O device reported an I/O error.
//
#ifndef STATUS_IO_DEVICE_ERROR
#define STATUS_IO_DEVICE_ERROR           ((NTSTATUS)0xC0000185L)
#endif//STATUS_IO_DEVICE_ERROR

//
// MessageId: STATUS_DEVICE_PROTOCOL_ERROR
//
// MessageText:
//
// A protocol error was detected between the driver and the device.
//
#ifndef STATUS_DEVICE_PROTOCOL_ERROR
#define STATUS_DEVICE_PROTOCOL_ERROR     ((NTSTATUS)0xC0000186L)
#endif//STATUS_DEVICE_PROTOCOL_ERROR

//
// MessageId: STATUS_BACKUP_CONTROLLER
//
// MessageText:
//
// This operation is only allowed for the Primary Domain Controller of the domain.
//
#ifndef STATUS_BACKUP_CONTROLLER
#define STATUS_BACKUP_CONTROLLER         ((NTSTATUS)0xC0000187L)
#endif//STATUS_BACKUP_CONTROLLER

//
// MessageId: STATUS_LOG_FILE_FULL
//
// MessageText:
//
// Log file space is insufficient to support this operation.
//
#ifndef STATUS_LOG_FILE_FULL
#define STATUS_LOG_FILE_FULL             ((NTSTATUS)0xC0000188L)
#endif//STATUS_LOG_FILE_FULL

//
// MessageId: STATUS_TOO_LATE
//
// MessageText:
//
// A write operation was attempted to a volume after it was dismounted.
//
#ifndef STATUS_TOO_LATE
#define STATUS_TOO_LATE                  ((NTSTATUS)0xC0000189L)
#endif//STATUS_TOO_LATE

//
// MessageId: STATUS_NO_TRUST_LSA_SECRET
//
// MessageText:
//
// The workstation does not have a trust secret for the primary domain in the local LSA database.
//
#ifndef STATUS_NO_TRUST_LSA_SECRET
#define STATUS_NO_TRUST_LSA_SECRET       ((NTSTATUS)0xC000018AL)
#endif//STATUS_NO_TRUST_LSA_SECRET

//
// MessageId: STATUS_NO_TRUST_SAM_ACCOUNT
//
// MessageText:
//
// The SAM database on the Windows Server does not have a computer account for this workstation trust relationship.
//
#ifndef STATUS_NO_TRUST_SAM_ACCOUNT
#define STATUS_NO_TRUST_SAM_ACCOUNT      ((NTSTATUS)0xC000018BL)
#endif//STATUS_NO_TRUST_SAM_ACCOUNT

//
// MessageId: STATUS_TRUSTED_DOMAIN_FAILURE
//
// MessageText:
//
// The logon request failed because the trust relationship between the primary domain and the trusted domain failed.
//
#ifndef STATUS_TRUSTED_DOMAIN_FAILURE
#define STATUS_TRUSTED_DOMAIN_FAILURE    ((NTSTATUS)0xC000018CL)
#endif//STATUS_TRUSTED_DOMAIN_FAILURE

//
// MessageId: STATUS_TRUSTED_RELATIONSHIP_FAILURE
//
// MessageText:
//
// The logon request failed because the trust relationship between this workstation and the primary domain failed.
//
#ifndef STATUS_TRUSTED_RELATIONSHIP_FAILURE
#define STATUS_TRUSTED_RELATIONSHIP_FAILURE ((NTSTATUS)0xC000018DL)
#endif//STATUS_TRUSTED_RELATIONSHIP_FAILURE

//
// MessageId: STATUS_EVENTLOG_FILE_CORRUPT
//
// MessageText:
//
// The Eventlog log file is corrupt.
//
#ifndef STATUS_EVENTLOG_FILE_CORRUPT
#define STATUS_EVENTLOG_FILE_CORRUPT     ((NTSTATUS)0xC000018EL)
#endif//STATUS_EVENTLOG_FILE_CORRUPT

//
// MessageId: STATUS_EVENTLOG_CANT_START
//
// MessageText:
//
// No Eventlog log file could be opened. The Eventlog service did not start.
//
#ifndef STATUS_EVENTLOG_CANT_START
#define STATUS_EVENTLOG_CANT_START       ((NTSTATUS)0xC000018FL)
#endif//STATUS_EVENTLOG_CANT_START

//
// MessageId: STATUS_TRUST_FAILURE
//
// MessageText:
//
// The network logon failed. This may be because the validation authority can't be reached.
//
#ifndef STATUS_TRUST_FAILURE
#define STATUS_TRUST_FAILURE             ((NTSTATUS)0xC0000190L)
#endif//STATUS_TRUST_FAILURE

//
// MessageId: STATUS_MUTANT_LIMIT_EXCEEDED
//
// MessageText:
//
// An attempt was made to acquire a mutant such that its maximum count would have been exceeded.
//
#ifndef STATUS_MUTANT_LIMIT_EXCEEDED
#define STATUS_MUTANT_LIMIT_EXCEEDED     ((NTSTATUS)0xC0000191L)
#endif//STATUS_MUTANT_LIMIT_EXCEEDED

//
// MessageId: STATUS_NETLOGON_NOT_STARTED
//
// MessageText:
//
// An attempt was made to logon, but the netlogon service was not started.
//
#ifndef STATUS_NETLOGON_NOT_STARTED
#define STATUS_NETLOGON_NOT_STARTED      ((NTSTATUS)0xC0000192L)
#endif//STATUS_NETLOGON_NOT_STARTED

//
// MessageId: STATUS_ACCOUNT_EXPIRED
//
// MessageText:
//
// The user's account has expired.
//
#ifndef STATUS_ACCOUNT_EXPIRED
#define STATUS_ACCOUNT_EXPIRED           ((NTSTATUS)0xC0000193L)    // ntsubauth
#endif//STATUS_ACCOUNT_EXPIRED

//
// MessageId: STATUS_POSSIBLE_DEADLOCK
//
// MessageText:
//
// {EXCEPTION}
// Possible deadlock condition.
//
#ifndef STATUS_POSSIBLE_DEADLOCK
#define STATUS_POSSIBLE_DEADLOCK         ((NTSTATUS)0xC0000194L)
#endif//STATUS_POSSIBLE_DEADLOCK

//
// MessageId: STATUS_NETWORK_CREDENTIAL_CONFLICT
//
// MessageText:
//
// Multiple connections to a server or shared resource by the same user, using more than one user name, are not allowed. Disconnect all previous connections to the server or shared resource and try again.
//
#ifndef STATUS_NETWORK_CREDENTIAL_CONFLICT
#define STATUS_NETWORK_CREDENTIAL_CONFLICT ((NTSTATUS)0xC0000195L)
#endif//STATUS_NETWORK_CREDENTIAL_CONFLICT

//
// MessageId: STATUS_REMOTE_SESSION_LIMIT
//
// MessageText:
//
// An attempt was made to establish a session to a network server, but there are already too many sessions established to that server.
//
#ifndef STATUS_REMOTE_SESSION_LIMIT
#define STATUS_REMOTE_SESSION_LIMIT      ((NTSTATUS)0xC0000196L)
#endif//STATUS_REMOTE_SESSION_LIMIT

//
// MessageId: STATUS_EVENTLOG_FILE_CHANGED
//
// MessageText:
//
// The log file has changed between reads.
//
#ifndef STATUS_EVENTLOG_FILE_CHANGED
#define STATUS_EVENTLOG_FILE_CHANGED     ((NTSTATUS)0xC0000197L)
#endif//STATUS_EVENTLOG_FILE_CHANGED

//
// MessageId: STATUS_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT
//
// MessageText:
//
// The account used is an Interdomain Trust account. Use your global user account or local user account to access this server.
//
#ifndef STATUS_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT
#define STATUS_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT ((NTSTATUS)0xC0000198L)
#endif//STATUS_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT

//
// MessageId: STATUS_NOLOGON_WORKSTATION_TRUST_ACCOUNT
//
// MessageText:
//
// The account used is a Computer Account. Use your global user account or local user account to access this server.
//
#ifndef STATUS_NOLOGON_WORKSTATION_TRUST_ACCOUNT
#define STATUS_NOLOGON_WORKSTATION_TRUST_ACCOUNT ((NTSTATUS)0xC0000199L)
#endif//STATUS_NOLOGON_WORKSTATION_TRUST_ACCOUNT

//
// MessageId: STATUS_NOLOGON_SERVER_TRUST_ACCOUNT
//
// MessageText:
//
// The account used is an Server Trust account. Use your global user account or local user account to access this server.
//
#ifndef STATUS_NOLOGON_SERVER_TRUST_ACCOUNT
#define STATUS_NOLOGON_SERVER_TRUST_ACCOUNT ((NTSTATUS)0xC000019AL)
#endif//STATUS_NOLOGON_SERVER_TRUST_ACCOUNT

//
// MessageId: STATUS_DOMAIN_TRUST_INCONSISTENT
//
// MessageText:
//
// The name or SID of the domain specified is inconsistent with the trust information for that domain.
//
#ifndef STATUS_DOMAIN_TRUST_INCONSISTENT
#define STATUS_DOMAIN_TRUST_INCONSISTENT ((NTSTATUS)0xC000019BL)
#endif//STATUS_DOMAIN_TRUST_INCONSISTENT

//
// MessageId: STATUS_FS_DRIVER_REQUIRED
//
// MessageText:
//
// A volume has been accessed for which a file system driver is required that has not yet been loaded.
//
#ifndef STATUS_FS_DRIVER_REQUIRED
#define STATUS_FS_DRIVER_REQUIRED        ((NTSTATUS)0xC000019CL)
#endif//STATUS_FS_DRIVER_REQUIRED

//
// MessageId: STATUS_IMAGE_ALREADY_LOADED_AS_DLL
//
// MessageText:
//
// Indicates that the specified image is already loaded as a DLL.
//
#ifndef STATUS_IMAGE_ALREADY_LOADED_AS_DLL
#define STATUS_IMAGE_ALREADY_LOADED_AS_DLL ((NTSTATUS)0xC000019DL)
#endif//STATUS_IMAGE_ALREADY_LOADED_AS_DLL

//
// MessageId: STATUS_INCOMPATIBLE_WITH_GLOBAL_SHORT_NAME_REGISTRY_SETTING
//
// MessageText:
//
// Short name settings may not be changed on this volume due to the global registry setting.
//
#ifndef STATUS_INCOMPATIBLE_WITH_GLOBAL_SHORT_NAME_REGISTRY_SETTING
#define STATUS_INCOMPATIBLE_WITH_GLOBAL_SHORT_NAME_REGISTRY_SETTING ((NTSTATUS)0xC000019EL)
#endif//STATUS_INCOMPATIBLE_WITH_GLOBAL_SHORT_NAME_REGISTRY_SETTING

//
// MessageId: STATUS_SHORT_NAMES_NOT_ENABLED_ON_VOLUME
//
// MessageText:
//
// Short names are not enabled on this volume.
//
#ifndef STATUS_SHORT_NAMES_NOT_ENABLED_ON_VOLUME
#define STATUS_SHORT_NAMES_NOT_ENABLED_ON_VOLUME ((NTSTATUS)0xC000019FL)
#endif//STATUS_SHORT_NAMES_NOT_ENABLED_ON_VOLUME

//
// MessageId: STATUS_SECURITY_STREAM_IS_INCONSISTENT
//
// MessageText:
//
// The security stream for the given volume is in an inconsistent state.
// Please run CHKDSK on the volume.
//
#ifndef STATUS_SECURITY_STREAM_IS_INCONSISTENT
#define STATUS_SECURITY_STREAM_IS_INCONSISTENT ((NTSTATUS)0xC00001A0L)
#endif//STATUS_SECURITY_STREAM_IS_INCONSISTENT

//
// MessageId: STATUS_INVALID_LOCK_RANGE
//
// MessageText:
//
// A requested file lock operation cannot be processed due to an invalid byte range.
//
#ifndef STATUS_INVALID_LOCK_RANGE
#define STATUS_INVALID_LOCK_RANGE        ((NTSTATUS)0xC00001A1L)
#endif//STATUS_INVALID_LOCK_RANGE

//
// MessageId: STATUS_INVALID_ACE_CONDITION
//
// MessageText:
//
// {Invalid ACE Condition}
// The specified access control entry (ACE) contains an invalid condition.
//
#ifndef STATUS_INVALID_ACE_CONDITION
#define STATUS_INVALID_ACE_CONDITION     ((NTSTATUS)0xC00001A2L)
#endif//STATUS_INVALID_ACE_CONDITION

//
// MessageId: STATUS_IMAGE_SUBSYSTEM_NOT_PRESENT
//
// MessageText:
//
// The subsystem needed to support the image type is not present.
//
#ifndef STATUS_IMAGE_SUBSYSTEM_NOT_PRESENT
#define STATUS_IMAGE_SUBSYSTEM_NOT_PRESENT ((NTSTATUS)0xC00001A3L)
#endif//STATUS_IMAGE_SUBSYSTEM_NOT_PRESENT

//
// MessageId: STATUS_NOTIFICATION_GUID_ALREADY_DEFINED
//
// MessageText:
//
// {Invalid ACE Condition}
// The specified file already has a notification GUID associated with it.
//
#ifndef STATUS_NOTIFICATION_GUID_ALREADY_DEFINED
#define STATUS_NOTIFICATION_GUID_ALREADY_DEFINED ((NTSTATUS)0xC00001A4L)
#endif//STATUS_NOTIFICATION_GUID_ALREADY_DEFINED

//
// MessageId: STATUS_INVALID_EXCEPTION_HANDLER
//
// MessageText:
//
// An invalid exception handler routine has been detected.
//
#ifndef STATUS_INVALID_EXCEPTION_HANDLER
#define STATUS_INVALID_EXCEPTION_HANDLER ((NTSTATUS)0xC00001A5L)
#endif//STATUS_INVALID_EXCEPTION_HANDLER

//
// MessageId: STATUS_DUPLICATE_PRIVILEGES
//
// MessageText:
//
// Duplicate privileges were specified for the token.
//
#ifndef STATUS_DUPLICATE_PRIVILEGES
#define STATUS_DUPLICATE_PRIVILEGES      ((NTSTATUS)0xC00001A6L)
#endif//STATUS_DUPLICATE_PRIVILEGES

//
// MessageId: STATUS_NOT_ALLOWED_ON_SYSTEM_FILE
//
// MessageText:
//
// Requested action not allowed on a file system internal file.
//
#ifndef STATUS_NOT_ALLOWED_ON_SYSTEM_FILE
#define STATUS_NOT_ALLOWED_ON_SYSTEM_FILE ((NTSTATUS)0xC00001A7L)
#endif//STATUS_NOT_ALLOWED_ON_SYSTEM_FILE

//
// MessageId: STATUS_REPAIR_NEEDED
//
// MessageText:
//
// A portion of the file system requires repair.
//
#ifndef STATUS_REPAIR_NEEDED
#define STATUS_REPAIR_NEEDED             ((NTSTATUS)0xC00001A8L)
#endif//STATUS_REPAIR_NEEDED

//
// MessageId: STATUS_QUOTA_NOT_ENABLED
//
// MessageText:
//
// Quota support is not enabled on the system.
//
#ifndef STATUS_QUOTA_NOT_ENABLED
#define STATUS_QUOTA_NOT_ENABLED         ((NTSTATUS)0xC00001A9L)
#endif//STATUS_QUOTA_NOT_ENABLED

//
// MessageId: STATUS_NO_APPLICATION_PACKAGE
//
// MessageText:
//
// The operation failed because the application is not part of an application package.
//
#ifndef STATUS_NO_APPLICATION_PACKAGE
#define STATUS_NO_APPLICATION_PACKAGE    ((NTSTATUS)0xC00001AAL)
#endif//STATUS_NO_APPLICATION_PACKAGE

//
// MessageId: STATUS_FILE_METADATA_OPTIMIZATION_IN_PROGRESS
//
// MessageText:
//
// File metadata optimization is already in progress.
//
#ifndef STATUS_FILE_METADATA_OPTIMIZATION_IN_PROGRESS
#define STATUS_FILE_METADATA_OPTIMIZATION_IN_PROGRESS ((NTSTATUS)0xC00001ABL)
#endif//STATUS_FILE_METADATA_OPTIMIZATION_IN_PROGRESS

//
// MessageId: STATUS_NOT_SAME_OBJECT
//
// MessageText:
//
// The objects are not identical.
//
#ifndef STATUS_NOT_SAME_OBJECT
#define STATUS_NOT_SAME_OBJECT           ((NTSTATUS)0xC00001ACL)
#endif//STATUS_NOT_SAME_OBJECT

//
// MessageId: STATUS_FATAL_MEMORY_EXHAUSTION
//
// MessageText:
//
// The process has terminated because it could not allocate additional memory.
//
#ifndef STATUS_FATAL_MEMORY_EXHAUSTION
#define STATUS_FATAL_MEMORY_EXHAUSTION   ((NTSTATUS)0xC00001ADL)
#endif//STATUS_FATAL_MEMORY_EXHAUSTION

//
// MessageId: STATUS_ERROR_PROCESS_NOT_IN_JOB
//
// MessageText:
//
// The process is not part of a job.
//
#ifndef STATUS_ERROR_PROCESS_NOT_IN_JOB
#define STATUS_ERROR_PROCESS_NOT_IN_JOB  ((NTSTATUS)0xC00001AEL)
#endif//STATUS_ERROR_PROCESS_NOT_IN_JOB

//
// MessageId: STATUS_CPU_SET_INVALID
//
// MessageText:
//
// The specified CPU Set IDs are invalid.
//
#ifndef STATUS_CPU_SET_INVALID
#define STATUS_CPU_SET_INVALID           ((NTSTATUS)0xC00001AFL)
#endif//STATUS_CPU_SET_INVALID

//
//  Available range of NTSTATUS codes
//
//
// MessageId: STATUS_NETWORK_OPEN_RESTRICTION
//
// MessageText:
//
// A remote open failed because the network open restrictions were not satisfied.
//
#ifndef STATUS_NETWORK_OPEN_RESTRICTION
#define STATUS_NETWORK_OPEN_RESTRICTION  ((NTSTATUS)0xC0000201L)
#endif//STATUS_NETWORK_OPEN_RESTRICTION

//
// MessageId: STATUS_NO_USER_SESSION_KEY
//
// MessageText:
//
// There is no user session key for the specified logon session.
//
#ifndef STATUS_NO_USER_SESSION_KEY
#define STATUS_NO_USER_SESSION_KEY       ((NTSTATUS)0xC0000202L)
#endif//STATUS_NO_USER_SESSION_KEY

//
// MessageId: STATUS_USER_SESSION_DELETED
//
// MessageText:
//
// The remote user session has been deleted.
//
#ifndef STATUS_USER_SESSION_DELETED
#define STATUS_USER_SESSION_DELETED      ((NTSTATUS)0xC0000203L)
#endif//STATUS_USER_SESSION_DELETED

//
// MessageId: STATUS_RESOURCE_LANG_NOT_FOUND
//
// MessageText:
//
// Indicates the specified resource language ID cannot be found in the
// image file.
//
#ifndef STATUS_RESOURCE_LANG_NOT_FOUND
#define STATUS_RESOURCE_LANG_NOT_FOUND   ((NTSTATUS)0xC0000204L)
#endif//STATUS_RESOURCE_LANG_NOT_FOUND

//
// MessageId: STATUS_INSUFF_SERVER_RESOURCES
//
// MessageText:
//
// Insufficient server resources exist to complete the request.
//
#ifndef STATUS_INSUFF_SERVER_RESOURCES
#define STATUS_INSUFF_SERVER_RESOURCES   ((NTSTATUS)0xC0000205L)
#endif//STATUS_INSUFF_SERVER_RESOURCES

//
// MessageId: STATUS_INVALID_BUFFER_SIZE
//
// MessageText:
//
// The size of the buffer is invalid for the specified operation.
//
#ifndef STATUS_INVALID_BUFFER_SIZE
#define STATUS_INVALID_BUFFER_SIZE       ((NTSTATUS)0xC0000206L)
#endif//STATUS_INVALID_BUFFER_SIZE

//
// MessageId: STATUS_INVALID_ADDRESS_COMPONENT
//
// MessageText:
//
// The transport rejected the network address specified as invalid.
//
#ifndef STATUS_INVALID_ADDRESS_COMPONENT
#define STATUS_INVALID_ADDRESS_COMPONENT ((NTSTATUS)0xC0000207L)
#endif//STATUS_INVALID_ADDRESS_COMPONENT

//
// MessageId: STATUS_INVALID_ADDRESS_WILDCARD
//
// MessageText:
//
// The transport rejected the network address specified due to an invalid use of a wildcard.
//
#ifndef STATUS_INVALID_ADDRESS_WILDCARD
#define STATUS_INVALID_ADDRESS_WILDCARD  ((NTSTATUS)0xC0000208L)
#endif//STATUS_INVALID_ADDRESS_WILDCARD

//
// MessageId: STATUS_TOO_MANY_ADDRESSES
//
// MessageText:
//
// The transport address could not be opened because all the available addresses are in use.
//
#ifndef STATUS_TOO_MANY_ADDRESSES
#define STATUS_TOO_MANY_ADDRESSES        ((NTSTATUS)0xC0000209L)
#endif//STATUS_TOO_MANY_ADDRESSES

//
// MessageId: STATUS_ADDRESS_ALREADY_EXISTS
//
// MessageText:
//
// The transport address could not be opened because it already exists.
//
#ifndef STATUS_ADDRESS_ALREADY_EXISTS
#define STATUS_ADDRESS_ALREADY_EXISTS    ((NTSTATUS)0xC000020AL)
#endif//STATUS_ADDRESS_ALREADY_EXISTS

//
// MessageId: STATUS_ADDRESS_CLOSED
//
// MessageText:
//
// The transport address is now closed.
//
#ifndef STATUS_ADDRESS_CLOSED
#define STATUS_ADDRESS_CLOSED            ((NTSTATUS)0xC000020BL)
#endif//STATUS_ADDRESS_CLOSED

//
// MessageId: STATUS_CONNECTION_DISCONNECTED
//
// MessageText:
//
// The transport connection is now disconnected.
//
#ifndef STATUS_CONNECTION_DISCONNECTED
#define STATUS_CONNECTION_DISCONNECTED   ((NTSTATUS)0xC000020CL)
#endif//STATUS_CONNECTION_DISCONNECTED

//
// MessageId: STATUS_CONNECTION_RESET
//
// MessageText:
//
// The transport connection has been reset.
//
#ifndef STATUS_CONNECTION_RESET
#define STATUS_CONNECTION_RESET          ((NTSTATUS)0xC000020DL)
#endif//STATUS_CONNECTION_RESET

//
// MessageId: STATUS_TOO_MANY_NODES
//
// MessageText:
//
// The transport cannot dynamically acquire any more nodes.
//
#ifndef STATUS_TOO_MANY_NODES
#define STATUS_TOO_MANY_NODES            ((NTSTATUS)0xC000020EL)
#endif//STATUS_TOO_MANY_NODES

//
// MessageId: STATUS_TRANSACTION_ABORTED
//
// MessageText:
//
// The transport aborted a pending transaction.
//
#ifndef STATUS_TRANSACTION_ABORTED
#define STATUS_TRANSACTION_ABORTED       ((NTSTATUS)0xC000020FL)
#endif//STATUS_TRANSACTION_ABORTED

//
// MessageId: STATUS_TRANSACTION_TIMED_OUT
//
// MessageText:
//
// The transport timed out a request waiting for a response.
//
#ifndef STATUS_TRANSACTION_TIMED_OUT
#define STATUS_TRANSACTION_TIMED_OUT     ((NTSTATUS)0xC0000210L)
#endif//STATUS_TRANSACTION_TIMED_OUT

//
// MessageId: STATUS_TRANSACTION_NO_RELEASE
//
// MessageText:
//
// The transport did not receive a release for a pending response.
//
#ifndef STATUS_TRANSACTION_NO_RELEASE
#define STATUS_TRANSACTION_NO_RELEASE    ((NTSTATUS)0xC0000211L)
#endif//STATUS_TRANSACTION_NO_RELEASE

//
// MessageId: STATUS_TRANSACTION_NO_MATCH
//
// MessageText:
//
// The transport did not find a transaction matching the specific token.
//
#ifndef STATUS_TRANSACTION_NO_MATCH
#define STATUS_TRANSACTION_NO_MATCH      ((NTSTATUS)0xC0000212L)
#endif//STATUS_TRANSACTION_NO_MATCH

//
// MessageId: STATUS_TRANSACTION_RESPONDED
//
// MessageText:
//
// The transport had previously responded to a transaction request.
//
#ifndef STATUS_TRANSACTION_RESPONDED
#define STATUS_TRANSACTION_RESPONDED     ((NTSTATUS)0xC0000213L)
#endif//STATUS_TRANSACTION_RESPONDED

//
// MessageId: STATUS_TRANSACTION_INVALID_ID
//
// MessageText:
//
// The transport does not recognized the transaction request identifier specified.
//
#ifndef STATUS_TRANSACTION_INVALID_ID
#define STATUS_TRANSACTION_INVALID_ID    ((NTSTATUS)0xC0000214L)
#endif//STATUS_TRANSACTION_INVALID_ID

//
// MessageId: STATUS_TRANSACTION_INVALID_TYPE
//
// MessageText:
//
// The transport does not recognize the transaction request type specified.
//
#ifndef STATUS_TRANSACTION_INVALID_TYPE
#define STATUS_TRANSACTION_INVALID_TYPE  ((NTSTATUS)0xC0000215L)
#endif//STATUS_TRANSACTION_INVALID_TYPE

//
// MessageId: STATUS_NOT_SERVER_SESSION
//
// MessageText:
//
// The transport can only process the specified request on the server side of a session.
//
#ifndef STATUS_NOT_SERVER_SESSION
#define STATUS_NOT_SERVER_SESSION        ((NTSTATUS)0xC0000216L)
#endif//STATUS_NOT_SERVER_SESSION

//
// MessageId: STATUS_NOT_CLIENT_SESSION
//
// MessageText:
//
// The transport can only process the specified request on the client side of a session.
//
#ifndef STATUS_NOT_CLIENT_SESSION
#define STATUS_NOT_CLIENT_SESSION        ((NTSTATUS)0xC0000217L)
#endif//STATUS_NOT_CLIENT_SESSION

//
// MessageId: STATUS_CANNOT_LOAD_REGISTRY_FILE
//
// MessageText:
//
// {Registry File Failure}
// The registry cannot load the hive (file):
// %hs
// or its log or alternate.
// It is corrupt, absent, or not writable.
//
#ifndef STATUS_CANNOT_LOAD_REGISTRY_FILE
#define STATUS_CANNOT_LOAD_REGISTRY_FILE ((NTSTATUS)0xC0000218L)
#endif//STATUS_CANNOT_LOAD_REGISTRY_FILE

//
// MessageId: STATUS_DEBUG_ATTACH_FAILED
//
// MessageText:
//
// {Unexpected Failure in DebugActiveProcess}
// An unexpected failure occurred while processing a DebugActiveProcess API request. You may choose OK to terminate the process, or Cancel to ignore the error.
//
#ifndef STATUS_DEBUG_ATTACH_FAILED
#define STATUS_DEBUG_ATTACH_FAILED       ((NTSTATUS)0xC0000219L)
#endif//STATUS_DEBUG_ATTACH_FAILED

//
// MessageId: STATUS_SYSTEM_PROCESS_TERMINATED
//
// MessageText:
//
// {Fatal System Error}
// The %hs system process terminated unexpectedly with a status of 0x%08x (0x%08x 0x%08x).
// The system has been shut down.
//
#ifndef STATUS_SYSTEM_PROCESS_TERMINATED
#define STATUS_SYSTEM_PROCESS_TERMINATED ((NTSTATUS)0xC000021AL)
#endif//STATUS_SYSTEM_PROCESS_TERMINATED

//
// MessageId: STATUS_DATA_NOT_ACCEPTED
//
// MessageText:
//
// {Data Not Accepted}
// The TDI client could not handle the data received during an indication.
//
#ifndef STATUS_DATA_NOT_ACCEPTED
#define STATUS_DATA_NOT_ACCEPTED         ((NTSTATUS)0xC000021BL)
#endif//STATUS_DATA_NOT_ACCEPTED

//
// MessageId: STATUS_NO_BROWSER_SERVERS_FOUND
//
// MessageText:
//
// {Unable to Retrieve Browser Server List}
// The list of servers for this workgroup is not currently available.
//
#ifndef STATUS_NO_BROWSER_SERVERS_FOUND
#define STATUS_NO_BROWSER_SERVERS_FOUND  ((NTSTATUS)0xC000021CL)
#endif//STATUS_NO_BROWSER_SERVERS_FOUND

//
// MessageId: STATUS_VDM_HARD_ERROR
//
// MessageText:
//
// NTVDM encountered a hard error.
//
#ifndef STATUS_VDM_HARD_ERROR
#define STATUS_VDM_HARD_ERROR            ((NTSTATUS)0xC000021DL)
#endif//STATUS_VDM_HARD_ERROR

//
// MessageId: STATUS_DRIVER_CANCEL_TIMEOUT
//
// MessageText:
//
// {Cancel Timeout}
// The driver %hs failed to complete a cancelled I/O request in the allotted time.
//
#ifndef STATUS_DRIVER_CANCEL_TIMEOUT
#define STATUS_DRIVER_CANCEL_TIMEOUT     ((NTSTATUS)0xC000021EL)
#endif//STATUS_DRIVER_CANCEL_TIMEOUT

//
// MessageId: STATUS_REPLY_MESSAGE_MISMATCH
//
// MessageText:
//
// {Reply Message Mismatch}
// An attempt was made to reply to an LPC message, but the thread specified by the client ID in the message was not waiting on that message.
//
#ifndef STATUS_REPLY_MESSAGE_MISMATCH
#define STATUS_REPLY_MESSAGE_MISMATCH    ((NTSTATUS)0xC000021FL)
#endif//STATUS_REPLY_MESSAGE_MISMATCH

//
// MessageId: STATUS_MAPPED_ALIGNMENT
//
// MessageText:
//
// {Mapped View Alignment Incorrect}
// An attempt was made to map a view of a file, but either the specified base address or the offset into the file were not aligned on the proper allocation granularity.
//
#ifndef STATUS_MAPPED_ALIGNMENT
#define STATUS_MAPPED_ALIGNMENT          ((NTSTATUS)0xC0000220L)
#endif//STATUS_MAPPED_ALIGNMENT

//
// MessageId: STATUS_IMAGE_CHECKSUM_MISMATCH
//
// MessageText:
//
// {Bad Image Checksum}
// The image %hs is possibly corrupt. The header checksum does not match the computed checksum.
//
#ifndef STATUS_IMAGE_CHECKSUM_MISMATCH
#define STATUS_IMAGE_CHECKSUM_MISMATCH   ((NTSTATUS)0xC0000221L)
#endif//STATUS_IMAGE_CHECKSUM_MISMATCH

//
// MessageId: STATUS_LOST_WRITEBEHIND_DATA
//
// MessageText:
//
// {Delayed Write Failed}
// Windows was unable to save all the data for the file %hs. The data has been lost. This error may be caused by a failure of your computer hardware or network connection. Please try to save this file elsewhere.
//
#ifndef STATUS_LOST_WRITEBEHIND_DATA
#define STATUS_LOST_WRITEBEHIND_DATA     ((NTSTATUS)0xC0000222L)
#endif//STATUS_LOST_WRITEBEHIND_DATA

//
// MessageId: STATUS_CLIENT_SERVER_PARAMETERS_INVALID
//
// MessageText:
//
// The parameter(s) passed to the server in the client/server shared memory window were invalid. Too much data may have been put in the shared memory window.
//
#ifndef STATUS_CLIENT_SERVER_PARAMETERS_INVALID
#define STATUS_CLIENT_SERVER_PARAMETERS_INVALID ((NTSTATUS)0xC0000223L)
#endif//STATUS_CLIENT_SERVER_PARAMETERS_INVALID

//
// MessageId: STATUS_PASSWORD_MUST_CHANGE
//
// MessageText:
//
// The user's password must be changed before signing in.
//
#ifndef STATUS_PASSWORD_MUST_CHANGE
#define STATUS_PASSWORD_MUST_CHANGE      ((NTSTATUS)0xC0000224L)    // ntsubauth
#endif//STATUS_PASSWORD_MUST_CHANGE

//
// MessageId: STATUS_NOT_FOUND
//
// MessageText:
//
// The object was not found.
//
#ifndef STATUS_NOT_FOUND
#define STATUS_NOT_FOUND                 ((NTSTATUS)0xC0000225L)
#endif//STATUS_NOT_FOUND

//
// MessageId: STATUS_NOT_TINY_STREAM
//
// MessageText:
//
// The stream is not a tiny stream.
//
#ifndef STATUS_NOT_TINY_STREAM
#define STATUS_NOT_TINY_STREAM           ((NTSTATUS)0xC0000226L)
#endif//STATUS_NOT_TINY_STREAM

//
// MessageId: STATUS_RECOVERY_FAILURE
//
// MessageText:
//
// A transaction recover failed.
//
#ifndef STATUS_RECOVERY_FAILURE
#define STATUS_RECOVERY_FAILURE          ((NTSTATUS)0xC0000227L)
#endif//STATUS_RECOVERY_FAILURE

//
// MessageId: STATUS_STACK_OVERFLOW_READ
//
// MessageText:
//
// The request must be handled by the stack overflow code.
//
#ifndef STATUS_STACK_OVERFLOW_READ
#define STATUS_STACK_OVERFLOW_READ       ((NTSTATUS)0xC0000228L)
#endif//STATUS_STACK_OVERFLOW_READ

//
// MessageId: STATUS_FAIL_CHECK
//
// MessageText:
//
// A consistency check failed.
//
#ifndef STATUS_FAIL_CHECK
#define STATUS_FAIL_CHECK                ((NTSTATUS)0xC0000229L)
#endif//STATUS_FAIL_CHECK

//
// MessageId: STATUS_DUPLICATE_OBJECTID
//
// MessageText:
//
// The attempt to insert the ID in the index failed because the ID is already in the index.
//
#ifndef STATUS_DUPLICATE_OBJECTID
#define STATUS_DUPLICATE_OBJECTID        ((NTSTATUS)0xC000022AL)
#endif//STATUS_DUPLICATE_OBJECTID

//
// MessageId: STATUS_OBJECTID_EXISTS
//
// MessageText:
//
// The attempt to set the object's ID failed because the object already has an ID.
//
#ifndef STATUS_OBJECTID_EXISTS
#define STATUS_OBJECTID_EXISTS           ((NTSTATUS)0xC000022BL)
#endif//STATUS_OBJECTID_EXISTS

//
// MessageId: STATUS_CONVERT_TO_LARGE
//
// MessageText:
//
// Internal OFS status codes indicating how an allocation operation is handled. Either it is retried after the containing onode is moved or the extent stream is converted to a large stream.
//
#ifndef STATUS_CONVERT_TO_LARGE
#define STATUS_CONVERT_TO_LARGE          ((NTSTATUS)0xC000022CL)
#endif//STATUS_CONVERT_TO_LARGE

//
// MessageId: STATUS_RETRY
//
// MessageText:
//
// The request needs to be retried.
//
#ifndef STATUS_RETRY
#define STATUS_RETRY                     ((NTSTATUS)0xC000022DL)
#endif//STATUS_RETRY

//
// MessageId: STATUS_FOUND_OUT_OF_SCOPE
//
// MessageText:
//
// The attempt to find the object found an object matching by ID on the volume but it is out of the scope of the handle used for the operation.
//
#ifndef STATUS_FOUND_OUT_OF_SCOPE
#define STATUS_FOUND_OUT_OF_SCOPE        ((NTSTATUS)0xC000022EL)
#endif//STATUS_FOUND_OUT_OF_SCOPE

//
// MessageId: STATUS_ALLOCATE_BUCKET
//
// MessageText:
//
// The bucket array must be grown. Retry transaction after doing so.
//
#ifndef STATUS_ALLOCATE_BUCKET
#define STATUS_ALLOCATE_BUCKET           ((NTSTATUS)0xC000022FL)
#endif//STATUS_ALLOCATE_BUCKET

//
// MessageId: STATUS_PROPSET_NOT_FOUND
//
// MessageText:
//
// The property set specified does not exist on the object.
//
#ifndef STATUS_PROPSET_NOT_FOUND
#define STATUS_PROPSET_NOT_FOUND         ((NTSTATUS)0xC0000230L)
#endif//STATUS_PROPSET_NOT_FOUND

//
// MessageId: STATUS_MARSHALL_OVERFLOW
//
// MessageText:
//
// The user/kernel marshalling buffer has overflowed.
//
#ifndef STATUS_MARSHALL_OVERFLOW
#define STATUS_MARSHALL_OVERFLOW         ((NTSTATUS)0xC0000231L)
#endif//STATUS_MARSHALL_OVERFLOW

//
// MessageId: STATUS_INVALID_VARIANT
//
// MessageText:
//
// The supplied variant structure contains invalid data.
//
#ifndef STATUS_INVALID_VARIANT
#define STATUS_INVALID_VARIANT           ((NTSTATUS)0xC0000232L)
#endif//STATUS_INVALID_VARIANT

//
// MessageId: STATUS_DOMAIN_CONTROLLER_NOT_FOUND
//
// MessageText:
//
// Could not find a domain controller for this domain.
//
#ifndef STATUS_DOMAIN_CONTROLLER_NOT_FOUND
#define STATUS_DOMAIN_CONTROLLER_NOT_FOUND ((NTSTATUS)0xC0000233L)
#endif//STATUS_DOMAIN_CONTROLLER_NOT_FOUND

//
// MessageId: STATUS_ACCOUNT_LOCKED_OUT
//
// MessageText:
//
// The user account has been automatically locked because too many invalid logon attempts or password change attempts have been requested.
//
#ifndef STATUS_ACCOUNT_LOCKED_OUT
#define STATUS_ACCOUNT_LOCKED_OUT        ((NTSTATUS)0xC0000234L)    // ntsubauth
#endif//STATUS_ACCOUNT_LOCKED_OUT

//
// MessageId: STATUS_HANDLE_NOT_CLOSABLE
//
// MessageText:
//
// NtClose was called on a handle that was protected from close via NtSetInformationObject.
//
#ifndef STATUS_HANDLE_NOT_CLOSABLE
#define STATUS_HANDLE_NOT_CLOSABLE       ((NTSTATUS)0xC0000235L)
#endif//STATUS_HANDLE_NOT_CLOSABLE

//
// MessageId: STATUS_CONNECTION_REFUSED
//
// MessageText:
//
// The transport connection attempt was refused by the remote system.
//
#ifndef STATUS_CONNECTION_REFUSED
#define STATUS_CONNECTION_REFUSED        ((NTSTATUS)0xC0000236L)
#endif//STATUS_CONNECTION_REFUSED

//
// MessageId: STATUS_GRACEFUL_DISCONNECT
//
// MessageText:
//
// The transport connection was gracefully closed.
//
#ifndef STATUS_GRACEFUL_DISCONNECT
#define STATUS_GRACEFUL_DISCONNECT       ((NTSTATUS)0xC0000237L)
#endif//STATUS_GRACEFUL_DISCONNECT

//
// MessageId: STATUS_ADDRESS_ALREADY_ASSOCIATED
//
// MessageText:
//
// The transport endpoint already has an address associated with it.
//
#ifndef STATUS_ADDRESS_ALREADY_ASSOCIATED
#define STATUS_ADDRESS_ALREADY_ASSOCIATED ((NTSTATUS)0xC0000238L)
#endif//STATUS_ADDRESS_ALREADY_ASSOCIATED

//
// MessageId: STATUS_ADDRESS_NOT_ASSOCIATED
//
// MessageText:
//
// An address has not yet been associated with the transport endpoint.
//
#ifndef STATUS_ADDRESS_NOT_ASSOCIATED
#define STATUS_ADDRESS_NOT_ASSOCIATED    ((NTSTATUS)0xC0000239L)
#endif//STATUS_ADDRESS_NOT_ASSOCIATED

//
// MessageId: STATUS_CONNECTION_INVALID
//
// MessageText:
//
// An operation was attempted on a nonexistent transport connection.
//
#ifndef STATUS_CONNECTION_INVALID
#define STATUS_CONNECTION_INVALID        ((NTSTATUS)0xC000023AL)
#endif//STATUS_CONNECTION_INVALID

//
// MessageId: STATUS_CONNECTION_ACTIVE
//
// MessageText:
//
// An invalid operation was attempted on an active transport connection.
//
#ifndef STATUS_CONNECTION_ACTIVE
#define STATUS_CONNECTION_ACTIVE         ((NTSTATUS)0xC000023BL)
#endif//STATUS_CONNECTION_ACTIVE

//
// MessageId: STATUS_NETWORK_UNREACHABLE
//
// MessageText:
//
// The remote network is not reachable by the transport.
//
#ifndef STATUS_NETWORK_UNREACHABLE
#define STATUS_NETWORK_UNREACHABLE       ((NTSTATUS)0xC000023CL)
#endif//STATUS_NETWORK_UNREACHABLE

//
// MessageId: STATUS_HOST_UNREACHABLE
//
// MessageText:
//
// The remote system is not reachable by the transport.
//
#ifndef STATUS_HOST_UNREACHABLE
#define STATUS_HOST_UNREACHABLE          ((NTSTATUS)0xC000023DL)
#endif//STATUS_HOST_UNREACHABLE

//
// MessageId: STATUS_PROTOCOL_UNREACHABLE
//
// MessageText:
//
// The remote system does not support the transport protocol.
//
#ifndef STATUS_PROTOCOL_UNREACHABLE
#define STATUS_PROTOCOL_UNREACHABLE      ((NTSTATUS)0xC000023EL)
#endif//STATUS_PROTOCOL_UNREACHABLE

//
// MessageId: STATUS_PORT_UNREACHABLE
//
// MessageText:
//
// No service is operating at the destination port of the transport on the remote system.
//
#ifndef STATUS_PORT_UNREACHABLE
#define STATUS_PORT_UNREACHABLE          ((NTSTATUS)0xC000023FL)
#endif//STATUS_PORT_UNREACHABLE

//
// MessageId: STATUS_REQUEST_ABORTED
//
// MessageText:
//
// The request was aborted.
//
#ifndef STATUS_REQUEST_ABORTED
#define STATUS_REQUEST_ABORTED           ((NTSTATUS)0xC0000240L)
#endif//STATUS_REQUEST_ABORTED

//
// MessageId: STATUS_CONNECTION_ABORTED
//
// MessageText:
//
// The transport connection was aborted by the local system.
//
#ifndef STATUS_CONNECTION_ABORTED
#define STATUS_CONNECTION_ABORTED        ((NTSTATUS)0xC0000241L)
#endif//STATUS_CONNECTION_ABORTED

//
// MessageId: STATUS_BAD_COMPRESSION_BUFFER
//
// MessageText:
//
// The specified buffer contains ill-formed data.
//
#ifndef STATUS_BAD_COMPRESSION_BUFFER
#define STATUS_BAD_COMPRESSION_BUFFER    ((NTSTATUS)0xC0000242L)
#endif//STATUS_BAD_COMPRESSION_BUFFER

//
// MessageId: STATUS_USER_MAPPED_FILE
//
// MessageText:
//
// The requested operation cannot be performed on a file with a user mapped section open.
//
#ifndef STATUS_USER_MAPPED_FILE
#define STATUS_USER_MAPPED_FILE          ((NTSTATUS)0xC0000243L)
#endif//STATUS_USER_MAPPED_FILE

//
// MessageId: STATUS_AUDIT_FAILED
//
// MessageText:
//
// {Audit Failed}
// An attempt to generate a security audit failed.
//
#ifndef STATUS_AUDIT_FAILED
#define STATUS_AUDIT_FAILED              ((NTSTATUS)0xC0000244L)
#endif//STATUS_AUDIT_FAILED

//
// MessageId: STATUS_TIMER_RESOLUTION_NOT_SET
//
// MessageText:
//
// The timer resolution was not previously set by the current process.
//
#ifndef STATUS_TIMER_RESOLUTION_NOT_SET
#define STATUS_TIMER_RESOLUTION_NOT_SET  ((NTSTATUS)0xC0000245L)
#endif//STATUS_TIMER_RESOLUTION_NOT_SET

//
// MessageId: STATUS_CONNECTION_COUNT_LIMIT
//
// MessageText:
//
// A connection to the server could not be made because the limit on the number of concurrent connections for this account has been reached.
//
#ifndef STATUS_CONNECTION_COUNT_LIMIT
#define STATUS_CONNECTION_COUNT_LIMIT    ((NTSTATUS)0xC0000246L)
#endif//STATUS_CONNECTION_COUNT_LIMIT

//
// MessageId: STATUS_LOGIN_TIME_RESTRICTION
//
// MessageText:
//
// Attempting to login during an unauthorized time of day for this account.
//
#ifndef STATUS_LOGIN_TIME_RESTRICTION
#define STATUS_LOGIN_TIME_RESTRICTION    ((NTSTATUS)0xC0000247L)
#endif//STATUS_LOGIN_TIME_RESTRICTION

//
// MessageId: STATUS_LOGIN_WKSTA_RESTRICTION
//
// MessageText:
//
// The account is not authorized to login from this station.
//
#ifndef STATUS_LOGIN_WKSTA_RESTRICTION
#define STATUS_LOGIN_WKSTA_RESTRICTION   ((NTSTATUS)0xC0000248L)
#endif//STATUS_LOGIN_WKSTA_RESTRICTION

//
// MessageId: STATUS_IMAGE_MP_UP_MISMATCH
//
// MessageText:
//
// {UP/MP Image Mismatch}
// The image %hs has been modified for use on a uniprocessor system, but you are running it on a multiprocessor machine.
// Please reinstall the image file.
//
#ifndef STATUS_IMAGE_MP_UP_MISMATCH
#define STATUS_IMAGE_MP_UP_MISMATCH      ((NTSTATUS)0xC0000249L)
#endif//STATUS_IMAGE_MP_UP_MISMATCH

//
// MessageId: STATUS_INSUFFICIENT_LOGON_INFO
//
// MessageText:
//
// There is insufficient account information to log you on.
//
#ifndef STATUS_INSUFFICIENT_LOGON_INFO
#define STATUS_INSUFFICIENT_LOGON_INFO   ((NTSTATUS)0xC0000250L)
#endif//STATUS_INSUFFICIENT_LOGON_INFO

//
// MessageId: STATUS_BAD_DLL_ENTRYPOINT
//
// MessageText:
//
// {Invalid DLL Entrypoint}
// The dynamic link library %hs is not written correctly. The stack pointer has been left in an inconsistent state. The entrypoint should be declared as WINAPI or STDCALL. Select YES to fail the DLL load. Select NO to continue execution. Selecting NO may cause the application to operate incorrectly.
//
#ifndef STATUS_BAD_DLL_ENTRYPOINT
#define STATUS_BAD_DLL_ENTRYPOINT        ((NTSTATUS)0xC0000251L)
#endif//STATUS_BAD_DLL_ENTRYPOINT

//
// MessageId: STATUS_BAD_SERVICE_ENTRYPOINT
//
// MessageText:
//
// {Invalid Service Callback Entrypoint}
// The %hs service is not written correctly. The stack pointer has been left in an inconsistent state. The callback entrypoint should be declared as WINAPI or STDCALL. Selecting OK will cause the service to continue operation. However, the service process may operate incorrectly.
//
#ifndef STATUS_BAD_SERVICE_ENTRYPOINT
#define STATUS_BAD_SERVICE_ENTRYPOINT    ((NTSTATUS)0xC0000252L)
#endif//STATUS_BAD_SERVICE_ENTRYPOINT

//
// MessageId: STATUS_LPC_REPLY_LOST
//
// MessageText:
//
// The server received the messages but did not send a reply.
//
#ifndef STATUS_LPC_REPLY_LOST
#define STATUS_LPC_REPLY_LOST            ((NTSTATUS)0xC0000253L)
#endif//STATUS_LPC_REPLY_LOST

//
// MessageId: STATUS_IP_ADDRESS_CONFLICT1
//
// MessageText:
//
// There is an IP address conflict with another system on the network
//
#ifndef STATUS_IP_ADDRESS_CONFLICT1
#define STATUS_IP_ADDRESS_CONFLICT1      ((NTSTATUS)0xC0000254L)
#endif//STATUS_IP_ADDRESS_CONFLICT1

//
// MessageId: STATUS_IP_ADDRESS_CONFLICT2
//
// MessageText:
//
// There is an IP address conflict with another system on the network
//
#ifndef STATUS_IP_ADDRESS_CONFLICT2
#define STATUS_IP_ADDRESS_CONFLICT2      ((NTSTATUS)0xC0000255L)
#endif//STATUS_IP_ADDRESS_CONFLICT2

//
// MessageId: STATUS_REGISTRY_QUOTA_LIMIT
//
// MessageText:
//
// {Low On Registry Space}
// The system has reached the maximum size allowed for the system part of the registry. Additional storage requests will be ignored.
//
#ifndef STATUS_REGISTRY_QUOTA_LIMIT
#define STATUS_REGISTRY_QUOTA_LIMIT      ((NTSTATUS)0xC0000256L)
#endif//STATUS_REGISTRY_QUOTA_LIMIT

//
// MessageId: STATUS_PATH_NOT_COVERED
//
// MessageText:
//
// The contacted server does not support the indicated part of the DFS namespace.
//
#ifndef STATUS_PATH_NOT_COVERED
#define STATUS_PATH_NOT_COVERED          ((NTSTATUS)0xC0000257L)
#endif//STATUS_PATH_NOT_COVERED

//
// MessageId: STATUS_NO_CALLBACK_ACTIVE
//
// MessageText:
//
// A callback return system service cannot be executed when no callback is active.
//
#ifndef STATUS_NO_CALLBACK_ACTIVE
#define STATUS_NO_CALLBACK_ACTIVE        ((NTSTATUS)0xC0000258L)
#endif//STATUS_NO_CALLBACK_ACTIVE

//
// MessageId: STATUS_LICENSE_QUOTA_EXCEEDED
//
// MessageText:
//
// The service being accessed is licensed for a particular number of connections. No more connections can be made to the service at this time because there are already as many connections as the service can accept.
//
#ifndef STATUS_LICENSE_QUOTA_EXCEEDED
#define STATUS_LICENSE_QUOTA_EXCEEDED    ((NTSTATUS)0xC0000259L)
#endif//STATUS_LICENSE_QUOTA_EXCEEDED

//
// MessageId: STATUS_PWD_TOO_SHORT
//
// MessageText:
//
// The password provided is too short to meet the policy of your user account. Please choose a longer password.
//
#ifndef STATUS_PWD_TOO_SHORT
#define STATUS_PWD_TOO_SHORT             ((NTSTATUS)0xC000025AL)
#endif//STATUS_PWD_TOO_SHORT

//
// MessageId: STATUS_PWD_TOO_RECENT
//
// MessageText:
//
// The policy of your user account does not allow you to change passwords too frequently. This is done to prevent users from changing back to a familiar, but potentially discovered, password. If you feel your password has been compromised then please contact your administrator immediately to have a new one assigned.
//
#ifndef STATUS_PWD_TOO_RECENT
#define STATUS_PWD_TOO_RECENT            ((NTSTATUS)0xC000025BL)
#endif//STATUS_PWD_TOO_RECENT

//
// MessageId: STATUS_PWD_HISTORY_CONFLICT
//
// MessageText:
//
// You have attempted to change your password to one that you have used in the past. The policy of your user account does not allow this. Please select a password that you have not previously used.
//
#ifndef STATUS_PWD_HISTORY_CONFLICT
#define STATUS_PWD_HISTORY_CONFLICT      ((NTSTATUS)0xC000025CL)
#endif//STATUS_PWD_HISTORY_CONFLICT

//
// MessageId: STATUS_PLUGPLAY_NO_DEVICE
//
// MessageText:
//
// You have attempted to load a legacy device driver while its device instance had been disabled.
//
#ifndef STATUS_PLUGPLAY_NO_DEVICE
#define STATUS_PLUGPLAY_NO_DEVICE        ((NTSTATUS)0xC000025EL)
#endif//STATUS_PLUGPLAY_NO_DEVICE

//
// MessageId: STATUS_UNSUPPORTED_COMPRESSION
//
// MessageText:
//
// The specified compression format is unsupported.
//
#ifndef STATUS_UNSUPPORTED_COMPRESSION
#define STATUS_UNSUPPORTED_COMPRESSION   ((NTSTATUS)0xC000025FL)
#endif//STATUS_UNSUPPORTED_COMPRESSION

//
// MessageId: STATUS_INVALID_HW_PROFILE
//
// MessageText:
//
// The specified hardware profile configuration is invalid.
//
#ifndef STATUS_INVALID_HW_PROFILE
#define STATUS_INVALID_HW_PROFILE        ((NTSTATUS)0xC0000260L)
#endif//STATUS_INVALID_HW_PROFILE

//
// MessageId: STATUS_INVALID_PLUGPLAY_DEVICE_PATH
//
// MessageText:
//
// The specified Plug and Play registry device path is invalid.
//
#ifndef STATUS_INVALID_PLUGPLAY_DEVICE_PATH
#define STATUS_INVALID_PLUGPLAY_DEVICE_PATH ((NTSTATUS)0xC0000261L)
#endif//STATUS_INVALID_PLUGPLAY_DEVICE_PATH

//
// MessageId: STATUS_DRIVER_ORDINAL_NOT_FOUND
//
// MessageText:
//
// {Driver Entry Point Not Found}
// The %hs device driver could not locate the ordinal %ld in driver %hs.
//
#ifndef STATUS_DRIVER_ORDINAL_NOT_FOUND
#define STATUS_DRIVER_ORDINAL_NOT_FOUND  ((NTSTATUS)0xC0000262L)
#endif//STATUS_DRIVER_ORDINAL_NOT_FOUND

//
// MessageId: STATUS_DRIVER_ENTRYPOINT_NOT_FOUND
//
// MessageText:
//
// {Driver Entry Point Not Found}
// The %hs device driver could not locate the entry point %hs in driver %hs.
//
#ifndef STATUS_DRIVER_ENTRYPOINT_NOT_FOUND
#define STATUS_DRIVER_ENTRYPOINT_NOT_FOUND ((NTSTATUS)0xC0000263L)
#endif//STATUS_DRIVER_ENTRYPOINT_NOT_FOUND

//
// MessageId: STATUS_RESOURCE_NOT_OWNED
//
// MessageText:
//
// {Application Error}
// The application attempted to release a resource it did not own. Click OK to terminate the application.
//
#ifndef STATUS_RESOURCE_NOT_OWNED
#define STATUS_RESOURCE_NOT_OWNED        ((NTSTATUS)0xC0000264L)
#endif//STATUS_RESOURCE_NOT_OWNED

//
// MessageId: STATUS_TOO_MANY_LINKS
//
// MessageText:
//
// An attempt was made to create more links on a file than the file system supports.
//
#ifndef STATUS_TOO_MANY_LINKS
#define STATUS_TOO_MANY_LINKS            ((NTSTATUS)0xC0000265L)
#endif//STATUS_TOO_MANY_LINKS

//
// MessageId: STATUS_QUOTA_LIST_INCONSISTENT
//
// MessageText:
//
// The specified quota list is internally inconsistent with its descriptor.
//
#ifndef STATUS_QUOTA_LIST_INCONSISTENT
#define STATUS_QUOTA_LIST_INCONSISTENT   ((NTSTATUS)0xC0000266L)
#endif//STATUS_QUOTA_LIST_INCONSISTENT

//
// MessageId: STATUS_FILE_IS_OFFLINE
//
// MessageText:
//
// The specified file has been relocated to offline storage.
//
#ifndef STATUS_FILE_IS_OFFLINE
#define STATUS_FILE_IS_OFFLINE           ((NTSTATUS)0xC0000267L)
#endif//STATUS_FILE_IS_OFFLINE

//
// MessageId: STATUS_EVALUATION_EXPIRATION
//
// MessageText:
//
// {Windows Evaluation Notification}
// The evaluation period for this installation of Windows has expired. This system will shutdown in 1 hour. To restore access to this installation of Windows, please upgrade this installation using a licensed distribution of this product.
//
#ifndef STATUS_EVALUATION_EXPIRATION
#define STATUS_EVALUATION_EXPIRATION     ((NTSTATUS)0xC0000268L)
#endif//STATUS_EVALUATION_EXPIRATION

//
// MessageId: STATUS_ILLEGAL_DLL_RELOCATION
//
// MessageText:
//
// {Illegal System DLL Relocation}
// The system DLL %hs was relocated in memory. The application will not run properly. The relocation occurred because the DLL %hs occupied an address range reserved for Windows system DLLs. The vendor supplying the DLL should be contacted for a new DLL.
//
#ifndef STATUS_ILLEGAL_DLL_RELOCATION
#define STATUS_ILLEGAL_DLL_RELOCATION    ((NTSTATUS)0xC0000269L)
#endif//STATUS_ILLEGAL_DLL_RELOCATION

//
// MessageId: STATUS_LICENSE_VIOLATION
//
// MessageText:
//
// {License Violation}
// The system has detected tampering with your registered product type. This is a violation of your software license. Tampering with product type is not permitted.
//
#ifndef STATUS_LICENSE_VIOLATION
#define STATUS_LICENSE_VIOLATION         ((NTSTATUS)0xC000026AL)
#endif//STATUS_LICENSE_VIOLATION

//
// MessageId: STATUS_DLL_INIT_FAILED_LOGOFF
//
// MessageText:
//
// {DLL Initialization Failed}
// The application failed to initialize because the window station is shutting down.
//
#ifndef STATUS_DLL_INIT_FAILED_LOGOFF
#define STATUS_DLL_INIT_FAILED_LOGOFF    ((NTSTATUS)0xC000026BL)
#endif//STATUS_DLL_INIT_FAILED_LOGOFF

//
// MessageId: STATUS_DRIVER_UNABLE_TO_LOAD
//
// MessageText:
//
// {Unable to Load Device Driver}
// %hs device driver could not be loaded.
// Error Status was 0x%x
//
#ifndef STATUS_DRIVER_UNABLE_TO_LOAD
#define STATUS_DRIVER_UNABLE_TO_LOAD     ((NTSTATUS)0xC000026CL)
#endif//STATUS_DRIVER_UNABLE_TO_LOAD

//
// MessageId: STATUS_DFS_UNAVAILABLE
//
// MessageText:
//
// DFS is unavailable on the contacted server.
//
#ifndef STATUS_DFS_UNAVAILABLE
#define STATUS_DFS_UNAVAILABLE           ((NTSTATUS)0xC000026DL)
#endif//STATUS_DFS_UNAVAILABLE

//
// MessageId: STATUS_VOLUME_DISMOUNTED
//
// MessageText:
//
// An operation was attempted to a volume after it was dismounted.
//
#ifndef STATUS_VOLUME_DISMOUNTED
#define STATUS_VOLUME_DISMOUNTED         ((NTSTATUS)0xC000026EL)
#endif//STATUS_VOLUME_DISMOUNTED

//
// MessageId: STATUS_WX86_INTERNAL_ERROR
//
// MessageText:
//
// An internal error occurred in the Win32 x86 emulation subsystem.
//
#ifndef STATUS_WX86_INTERNAL_ERROR
#define STATUS_WX86_INTERNAL_ERROR       ((NTSTATUS)0xC000026FL)
#endif//STATUS_WX86_INTERNAL_ERROR

//
// MessageId: STATUS_WX86_FLOAT_STACK_CHECK
//
// MessageText:
//
// Win32 x86 emulation subsystem Floating-point stack check.
//
#ifndef STATUS_WX86_FLOAT_STACK_CHECK
#define STATUS_WX86_FLOAT_STACK_CHECK    ((NTSTATUS)0xC0000270L)
#endif//STATUS_WX86_FLOAT_STACK_CHECK

//
// MessageId: STATUS_VALIDATE_CONTINUE
//
// MessageText:
//
// The validation process needs to continue on to the next step.
//
#ifndef STATUS_VALIDATE_CONTINUE
#define STATUS_VALIDATE_CONTINUE         ((NTSTATUS)0xC0000271L)
#endif//STATUS_VALIDATE_CONTINUE

//
// MessageId: STATUS_NO_MATCH
//
// MessageText:
//
// There was no match for the specified key in the index.
//
#ifndef STATUS_NO_MATCH
#define STATUS_NO_MATCH                  ((NTSTATUS)0xC0000272L)
#endif//STATUS_NO_MATCH

//
// MessageId: STATUS_NO_MORE_MATCHES
//
// MessageText:
//
// There are no more matches for the current index enumeration.
//
#ifndef STATUS_NO_MORE_MATCHES
#define STATUS_NO_MORE_MATCHES           ((NTSTATUS)0xC0000273L)
#endif//STATUS_NO_MORE_MATCHES

//
// MessageId: STATUS_NOT_A_REPARSE_POINT
//
// MessageText:
//
// The file or directory is not a reparse point.
//
#ifndef STATUS_NOT_A_REPARSE_POINT
#define STATUS_NOT_A_REPARSE_POINT       ((NTSTATUS)0xC0000275L)
#endif//STATUS_NOT_A_REPARSE_POINT

//
// MessageId: STATUS_IO_REPARSE_TAG_INVALID
//
// MessageText:
//
// The Windows I/O reparse tag passed for the reparse point is invalid.
//
#ifndef STATUS_IO_REPARSE_TAG_INVALID
#define STATUS_IO_REPARSE_TAG_INVALID    ((NTSTATUS)0xC0000276L)
#endif//STATUS_IO_REPARSE_TAG_INVALID

//
// MessageId: STATUS_IO_REPARSE_TAG_MISMATCH
//
// MessageText:
//
// The Windows I/O reparse tag does not match the one present in the reparse point.
//
#ifndef STATUS_IO_REPARSE_TAG_MISMATCH
#define STATUS_IO_REPARSE_TAG_MISMATCH   ((NTSTATUS)0xC0000277L)
#endif//STATUS_IO_REPARSE_TAG_MISMATCH

//
// MessageId: STATUS_IO_REPARSE_DATA_INVALID
//
// MessageText:
//
// The user data passed for the reparse point is invalid.
//
#ifndef STATUS_IO_REPARSE_DATA_INVALID
#define STATUS_IO_REPARSE_DATA_INVALID   ((NTSTATUS)0xC0000278L)
#endif//STATUS_IO_REPARSE_DATA_INVALID

//
// MessageId: STATUS_IO_REPARSE_TAG_NOT_HANDLED
//
// MessageText:
//
// The layered file system driver for this IO tag did not handle it when needed.
//
#ifndef STATUS_IO_REPARSE_TAG_NOT_HANDLED
#define STATUS_IO_REPARSE_TAG_NOT_HANDLED ((NTSTATUS)0xC0000279L)
#endif//STATUS_IO_REPARSE_TAG_NOT_HANDLED

//
// MessageId: STATUS_PWD_TOO_LONG
//
// MessageText:
//
// The password provided is too long to meet the policy of your user account. Please choose a shorter password.
//
#ifndef STATUS_PWD_TOO_LONG
#define STATUS_PWD_TOO_LONG              ((NTSTATUS)0xC000027AL)
#endif//STATUS_PWD_TOO_LONG

//
// MessageId: STATUS_STOWED_EXCEPTION
//
// MessageText:
//
// An application-internal exception has occurred.
//
#ifndef STATUS_STOWED_EXCEPTION
#define STATUS_STOWED_EXCEPTION          ((NTSTATUS)0xC000027BL)
#endif//STATUS_STOWED_EXCEPTION

//
// MessageId: STATUS_CONTEXT_STOWED_EXCEPTION
//
// MessageText:
//
// An application-internal exception has occurred.
//
#ifndef STATUS_CONTEXT_STOWED_EXCEPTION
#define STATUS_CONTEXT_STOWED_EXCEPTION  ((NTSTATUS)0xC000027CL)
#endif//STATUS_CONTEXT_STOWED_EXCEPTION

//
// MessageId: STATUS_REPARSE_POINT_NOT_RESOLVED
//
// MessageText:
//
// The symbolic link could not be resolved even though the initial file name is valid.
//
#ifndef STATUS_REPARSE_POINT_NOT_RESOLVED
#define STATUS_REPARSE_POINT_NOT_RESOLVED ((NTSTATUS)0xC0000280L)
#endif//STATUS_REPARSE_POINT_NOT_RESOLVED

//
// MessageId: STATUS_DIRECTORY_IS_A_REPARSE_POINT
//
// MessageText:
//
// The directory is a reparse point.
//
#ifndef STATUS_DIRECTORY_IS_A_REPARSE_POINT
#define STATUS_DIRECTORY_IS_A_REPARSE_POINT ((NTSTATUS)0xC0000281L)
#endif//STATUS_DIRECTORY_IS_A_REPARSE_POINT

//
// MessageId: STATUS_RANGE_LIST_CONFLICT
//
// MessageText:
//
// The range could not be added to the range list because of a conflict.
//
#ifndef STATUS_RANGE_LIST_CONFLICT
#define STATUS_RANGE_LIST_CONFLICT       ((NTSTATUS)0xC0000282L)
#endif//STATUS_RANGE_LIST_CONFLICT

//
// MessageId: STATUS_SOURCE_ELEMENT_EMPTY
//
// MessageText:
//
// The specified medium changer source element contains no media.
//
#ifndef STATUS_SOURCE_ELEMENT_EMPTY
#define STATUS_SOURCE_ELEMENT_EMPTY      ((NTSTATUS)0xC0000283L)
#endif//STATUS_SOURCE_ELEMENT_EMPTY

//
// MessageId: STATUS_DESTINATION_ELEMENT_FULL
//
// MessageText:
//
// The specified medium changer destination element already contains media.
//
#ifndef STATUS_DESTINATION_ELEMENT_FULL
#define STATUS_DESTINATION_ELEMENT_FULL  ((NTSTATUS)0xC0000284L)
#endif//STATUS_DESTINATION_ELEMENT_FULL

//
// MessageId: STATUS_ILLEGAL_ELEMENT_ADDRESS
//
// MessageText:
//
// The specified medium changer element does not exist.
//
#ifndef STATUS_ILLEGAL_ELEMENT_ADDRESS
#define STATUS_ILLEGAL_ELEMENT_ADDRESS   ((NTSTATUS)0xC0000285L)
#endif//STATUS_ILLEGAL_ELEMENT_ADDRESS

//
// MessageId: STATUS_MAGAZINE_NOT_PRESENT
//
// MessageText:
//
// The specified element is contained within a magazine that is no longer present.
//
#ifndef STATUS_MAGAZINE_NOT_PRESENT
#define STATUS_MAGAZINE_NOT_PRESENT      ((NTSTATUS)0xC0000286L)
#endif//STATUS_MAGAZINE_NOT_PRESENT

//
// MessageId: STATUS_REINITIALIZATION_NEEDED
//
// MessageText:
//
// The device requires reinitialization due to hardware errors.
//
#ifndef STATUS_REINITIALIZATION_NEEDED
#define STATUS_REINITIALIZATION_NEEDED   ((NTSTATUS)0xC0000287L)
#endif//STATUS_REINITIALIZATION_NEEDED

//
// MessageId: STATUS_DEVICE_REQUIRES_CLEANING
//
// MessageText:
//
// The device has indicated that cleaning is necessary.
//
#ifndef STATUS_DEVICE_REQUIRES_CLEANING
#define STATUS_DEVICE_REQUIRES_CLEANING  ((NTSTATUS)0x80000288L)
#endif//STATUS_DEVICE_REQUIRES_CLEANING

//
// MessageId: STATUS_DEVICE_DOOR_OPEN
//
// MessageText:
//
// The device has indicated that its door is open. Further operations require it closed and secured.
//
#ifndef STATUS_DEVICE_DOOR_OPEN
#define STATUS_DEVICE_DOOR_OPEN          ((NTSTATUS)0x80000289L)
#endif//STATUS_DEVICE_DOOR_OPEN

//
// MessageId: STATUS_ENCRYPTION_FAILED
//
// MessageText:
//
// The file encryption attempt failed.
//
#ifndef STATUS_ENCRYPTION_FAILED
#define STATUS_ENCRYPTION_FAILED         ((NTSTATUS)0xC000028AL)
#endif//STATUS_ENCRYPTION_FAILED

//
// MessageId: STATUS_DECRYPTION_FAILED
//
// MessageText:
//
// The file decryption attempt failed.
//
#ifndef STATUS_DECRYPTION_FAILED
#define STATUS_DECRYPTION_FAILED         ((NTSTATUS)0xC000028BL)
#endif//STATUS_DECRYPTION_FAILED

//
// MessageId: STATUS_RANGE_NOT_FOUND
//
// MessageText:
//
// The specified range could not be found in the range list.
//
#ifndef STATUS_RANGE_NOT_FOUND
#define STATUS_RANGE_NOT_FOUND           ((NTSTATUS)0xC000028CL)
#endif//STATUS_RANGE_NOT_FOUND

//
// MessageId: STATUS_NO_RECOVERY_POLICY
//
// MessageText:
//
// There is no encryption recovery policy configured for this system.
//
#ifndef STATUS_NO_RECOVERY_POLICY
#define STATUS_NO_RECOVERY_POLICY        ((NTSTATUS)0xC000028DL)
#endif//STATUS_NO_RECOVERY_POLICY

//
// MessageId: STATUS_NO_EFS
//
// MessageText:
//
// The required encryption driver is not loaded for this system.
//
#ifndef STATUS_NO_EFS
#define STATUS_NO_EFS                    ((NTSTATUS)0xC000028EL)
#endif//STATUS_NO_EFS

//
// MessageId: STATUS_WRONG_EFS
//
// MessageText:
//
// The file was encrypted with a different encryption driver than is currently loaded.
//
#ifndef STATUS_WRONG_EFS
#define STATUS_WRONG_EFS                 ((NTSTATUS)0xC000028FL)
#endif//STATUS_WRONG_EFS

//
// MessageId: STATUS_NO_USER_KEYS
//
// MessageText:
//
// There are no EFS keys defined for the user.
//
#ifndef STATUS_NO_USER_KEYS
#define STATUS_NO_USER_KEYS              ((NTSTATUS)0xC0000290L)
#endif//STATUS_NO_USER_KEYS

//
// MessageId: STATUS_FILE_NOT_ENCRYPTED
//
// MessageText:
//
// The specified file is not encrypted.
//
#ifndef STATUS_FILE_NOT_ENCRYPTED
#define STATUS_FILE_NOT_ENCRYPTED        ((NTSTATUS)0xC0000291L)
#endif//STATUS_FILE_NOT_ENCRYPTED

//
// MessageId: STATUS_NOT_EXPORT_FORMAT
//
// MessageText:
//
// The specified file is not in the defined EFS export format.
//
#ifndef STATUS_NOT_EXPORT_FORMAT
#define STATUS_NOT_EXPORT_FORMAT         ((NTSTATUS)0xC0000292L)
#endif//STATUS_NOT_EXPORT_FORMAT

//
// MessageId: STATUS_FILE_ENCRYPTED
//
// MessageText:
//
// The specified file is encrypted and the user does not have the ability to decrypt it.
//
#ifndef STATUS_FILE_ENCRYPTED
#define STATUS_FILE_ENCRYPTED            ((NTSTATUS)0xC0000293L)
#endif//STATUS_FILE_ENCRYPTED

//
// MessageId: STATUS_WAKE_SYSTEM
//
// MessageText:
//
// The system has awoken
//
#ifndef STATUS_WAKE_SYSTEM
#define STATUS_WAKE_SYSTEM               ((NTSTATUS)0x40000294L)
#endif//STATUS_WAKE_SYSTEM

//
// MessageId: STATUS_WMI_GUID_NOT_FOUND
//
// MessageText:
//
// The guid passed was not recognized as valid by a WMI data provider.
//
#ifndef STATUS_WMI_GUID_NOT_FOUND
#define STATUS_WMI_GUID_NOT_FOUND        ((NTSTATUS)0xC0000295L)
#endif//STATUS_WMI_GUID_NOT_FOUND

//
// MessageId: STATUS_WMI_INSTANCE_NOT_FOUND
//
// MessageText:
//
// The instance name passed was not recognized as valid by a WMI data provider.
//
#ifndef STATUS_WMI_INSTANCE_NOT_FOUND
#define STATUS_WMI_INSTANCE_NOT_FOUND    ((NTSTATUS)0xC0000296L)
#endif//STATUS_WMI_INSTANCE_NOT_FOUND

//
// MessageId: STATUS_WMI_ITEMID_NOT_FOUND
//
// MessageText:
//
// The data item id passed was not recognized as valid by a WMI data provider.
//
#ifndef STATUS_WMI_ITEMID_NOT_FOUND
#define STATUS_WMI_ITEMID_NOT_FOUND      ((NTSTATUS)0xC0000297L)
#endif//STATUS_WMI_ITEMID_NOT_FOUND

//
// MessageId: STATUS_WMI_TRY_AGAIN
//
// MessageText:
//
// The WMI request could not be completed and should be retried.
//
#ifndef STATUS_WMI_TRY_AGAIN
#define STATUS_WMI_TRY_AGAIN             ((NTSTATUS)0xC0000298L)
#endif//STATUS_WMI_TRY_AGAIN

//
// MessageId: STATUS_SHARED_POLICY
//
// MessageText:
//
// The policy object is shared and can only be modified at the root
//
#ifndef STATUS_SHARED_POLICY
#define STATUS_SHARED_POLICY             ((NTSTATUS)0xC0000299L)
#endif//STATUS_SHARED_POLICY

//
// MessageId: STATUS_POLICY_OBJECT_NOT_FOUND
//
// MessageText:
//
// The policy object does not exist when it should
//
#ifndef STATUS_POLICY_OBJECT_NOT_FOUND
#define STATUS_POLICY_OBJECT_NOT_FOUND   ((NTSTATUS)0xC000029AL)
#endif//STATUS_POLICY_OBJECT_NOT_FOUND

//
// MessageId: STATUS_POLICY_ONLY_IN_DS
//
// MessageText:
//
// The requested policy information only lives in the Ds
//
#ifndef STATUS_POLICY_ONLY_IN_DS
#define STATUS_POLICY_ONLY_IN_DS         ((NTSTATUS)0xC000029BL)
#endif//STATUS_POLICY_ONLY_IN_DS

//
// MessageId: STATUS_VOLUME_NOT_UPGRADED
//
// MessageText:
//
// The volume must be upgraded to enable this feature
//
#ifndef STATUS_VOLUME_NOT_UPGRADED
#define STATUS_VOLUME_NOT_UPGRADED       ((NTSTATUS)0xC000029CL)
#endif//STATUS_VOLUME_NOT_UPGRADED

//
// MessageId: STATUS_REMOTE_STORAGE_NOT_ACTIVE
//
// MessageText:
//
// The remote storage service is not operational at this time.
//
#ifndef STATUS_REMOTE_STORAGE_NOT_ACTIVE
#define STATUS_REMOTE_STORAGE_NOT_ACTIVE ((NTSTATUS)0xC000029DL)
#endif//STATUS_REMOTE_STORAGE_NOT_ACTIVE

//
// MessageId: STATUS_REMOTE_STORAGE_MEDIA_ERROR
//
// MessageText:
//
// The remote storage service encountered a media error.
//
#ifndef STATUS_REMOTE_STORAGE_MEDIA_ERROR
#define STATUS_REMOTE_STORAGE_MEDIA_ERROR ((NTSTATUS)0xC000029EL)
#endif//STATUS_REMOTE_STORAGE_MEDIA_ERROR

//
// MessageId: STATUS_NO_TRACKING_SERVICE
//
// MessageText:
//
// The tracking (workstation) service is not running.
//
#ifndef STATUS_NO_TRACKING_SERVICE
#define STATUS_NO_TRACKING_SERVICE       ((NTSTATUS)0xC000029FL)
#endif//STATUS_NO_TRACKING_SERVICE

//
// MessageId: STATUS_SERVER_SID_MISMATCH
//
// MessageText:
//
// The server process is running under a SID different than that required by client.
//
#ifndef STATUS_SERVER_SID_MISMATCH
#define STATUS_SERVER_SID_MISMATCH       ((NTSTATUS)0xC00002A0L)
#endif//STATUS_SERVER_SID_MISMATCH

//
// Directory Service specific Errors
//
//
// MessageId: STATUS_DS_NO_ATTRIBUTE_OR_VALUE
//
// MessageText:
//
// The specified directory service attribute or value does not exist.
//
#ifndef STATUS_DS_NO_ATTRIBUTE_OR_VALUE
#define STATUS_DS_NO_ATTRIBUTE_OR_VALUE  ((NTSTATUS)0xC00002A1L)
#endif//STATUS_DS_NO_ATTRIBUTE_OR_VALUE

//
// MessageId: STATUS_DS_INVALID_ATTRIBUTE_SYNTAX
//
// MessageText:
//
// The attribute syntax specified to the directory service is invalid.
//
#ifndef STATUS_DS_INVALID_ATTRIBUTE_SYNTAX
#define STATUS_DS_INVALID_ATTRIBUTE_SYNTAX ((NTSTATUS)0xC00002A2L)
#endif//STATUS_DS_INVALID_ATTRIBUTE_SYNTAX

//
// MessageId: STATUS_DS_ATTRIBUTE_TYPE_UNDEFINED
//
// MessageText:
//
// The attribute type specified to the directory service is not defined.
//
#ifndef STATUS_DS_ATTRIBUTE_TYPE_UNDEFINED
#define STATUS_DS_ATTRIBUTE_TYPE_UNDEFINED ((NTSTATUS)0xC00002A3L)
#endif//STATUS_DS_ATTRIBUTE_TYPE_UNDEFINED

//
// MessageId: STATUS_DS_ATTRIBUTE_OR_VALUE_EXISTS
//
// MessageText:
//
// The specified directory service attribute or value already exists.
//
#ifndef STATUS_DS_ATTRIBUTE_OR_VALUE_EXISTS
#define STATUS_DS_ATTRIBUTE_OR_VALUE_EXISTS ((NTSTATUS)0xC00002A4L)
#endif//STATUS_DS_ATTRIBUTE_OR_VALUE_EXISTS

//
// MessageId: STATUS_DS_BUSY
//
// MessageText:
//
// The directory service is busy.
//
#ifndef STATUS_DS_BUSY
#define STATUS_DS_BUSY                   ((NTSTATUS)0xC00002A5L)
#endif//STATUS_DS_BUSY

//
// MessageId: STATUS_DS_UNAVAILABLE
//
// MessageText:
//
// The directory service is not available.
//
#ifndef STATUS_DS_UNAVAILABLE
#define STATUS_DS_UNAVAILABLE            ((NTSTATUS)0xC00002A6L)
#endif//STATUS_DS_UNAVAILABLE

//
// MessageId: STATUS_DS_NO_RIDS_ALLOCATED
//
// MessageText:
//
// The directory service was unable to allocate a relative identifier.
//
#ifndef STATUS_DS_NO_RIDS_ALLOCATED
#define STATUS_DS_NO_RIDS_ALLOCATED      ((NTSTATUS)0xC00002A7L)
#endif//STATUS_DS_NO_RIDS_ALLOCATED

//
// MessageId: STATUS_DS_NO_MORE_RIDS
//
// MessageText:
//
// The directory service has exhausted the pool of relative identifiers.
//
#ifndef STATUS_DS_NO_MORE_RIDS
#define STATUS_DS_NO_MORE_RIDS           ((NTSTATUS)0xC00002A8L)
#endif//STATUS_DS_NO_MORE_RIDS

//
// MessageId: STATUS_DS_INCORRECT_ROLE_OWNER
//
// MessageText:
//
// The requested operation could not be performed because the directory service is not the master for that type of operation.
//
#ifndef STATUS_DS_INCORRECT_ROLE_OWNER
#define STATUS_DS_INCORRECT_ROLE_OWNER   ((NTSTATUS)0xC00002A9L)
#endif//STATUS_DS_INCORRECT_ROLE_OWNER

//
// MessageId: STATUS_DS_RIDMGR_INIT_ERROR
//
// MessageText:
//
// The directory service was unable to initialize the subsystem that allocates relative identifiers.
//
#ifndef STATUS_DS_RIDMGR_INIT_ERROR
#define STATUS_DS_RIDMGR_INIT_ERROR      ((NTSTATUS)0xC00002AAL)
#endif//STATUS_DS_RIDMGR_INIT_ERROR

//
// MessageId: STATUS_DS_OBJ_CLASS_VIOLATION
//
// MessageText:
//
// The requested operation did not satisfy one or more constraints associated with the class of the object.
//
#ifndef STATUS_DS_OBJ_CLASS_VIOLATION
#define STATUS_DS_OBJ_CLASS_VIOLATION    ((NTSTATUS)0xC00002ABL)
#endif//STATUS_DS_OBJ_CLASS_VIOLATION

//
// MessageId: STATUS_DS_CANT_ON_NON_LEAF
//
// MessageText:
//
// The directory service can perform the requested operation only on a leaf object.
//
#ifndef STATUS_DS_CANT_ON_NON_LEAF
#define STATUS_DS_CANT_ON_NON_LEAF       ((NTSTATUS)0xC00002ACL)
#endif//STATUS_DS_CANT_ON_NON_LEAF

//
// MessageId: STATUS_DS_CANT_ON_RDN
//
// MessageText:
//
// The directory service cannot perform the requested operation on the Relatively Defined Name (RDN) attribute of an object.
//
#ifndef STATUS_DS_CANT_ON_RDN
#define STATUS_DS_CANT_ON_RDN            ((NTSTATUS)0xC00002ADL)
#endif//STATUS_DS_CANT_ON_RDN

//
// MessageId: STATUS_DS_CANT_MOD_OBJ_CLASS
//
// MessageText:
//
// The directory service detected an attempt to modify the object class of an object.
//
#ifndef STATUS_DS_CANT_MOD_OBJ_CLASS
#define STATUS_DS_CANT_MOD_OBJ_CLASS     ((NTSTATUS)0xC00002AEL)
#endif//STATUS_DS_CANT_MOD_OBJ_CLASS

//
// MessageId: STATUS_DS_CROSS_DOM_MOVE_FAILED
//
// MessageText:
//
// An error occurred while performing a cross domain move operation.
//
#ifndef STATUS_DS_CROSS_DOM_MOVE_FAILED
#define STATUS_DS_CROSS_DOM_MOVE_FAILED  ((NTSTATUS)0xC00002AFL)
#endif//STATUS_DS_CROSS_DOM_MOVE_FAILED

//
// MessageId: STATUS_DS_GC_NOT_AVAILABLE
//
// MessageText:
//
// Unable to Contact the Global Catalog Server.
//
#ifndef STATUS_DS_GC_NOT_AVAILABLE
#define STATUS_DS_GC_NOT_AVAILABLE       ((NTSTATUS)0xC00002B0L)
#endif//STATUS_DS_GC_NOT_AVAILABLE

//
// MessageId: STATUS_DIRECTORY_SERVICE_REQUIRED
//
// MessageText:
//
// The requested operation requires a directory service, and none was available.
//
#ifndef STATUS_DIRECTORY_SERVICE_REQUIRED
#define STATUS_DIRECTORY_SERVICE_REQUIRED ((NTSTATUS)0xC00002B1L)
#endif//STATUS_DIRECTORY_SERVICE_REQUIRED

//
// MessageId: STATUS_REPARSE_ATTRIBUTE_CONFLICT
//
// MessageText:
//
// The reparse attribute cannot be set as it is incompatible with an existing attribute.
//
#ifndef STATUS_REPARSE_ATTRIBUTE_CONFLICT
#define STATUS_REPARSE_ATTRIBUTE_CONFLICT ((NTSTATUS)0xC00002B2L)
#endif//STATUS_REPARSE_ATTRIBUTE_CONFLICT

//
// MessageId: STATUS_CANT_ENABLE_DENY_ONLY
//
// MessageText:
//
// A group marked use for deny only cannot be enabled.
//
#ifndef STATUS_CANT_ENABLE_DENY_ONLY
#define STATUS_CANT_ENABLE_DENY_ONLY     ((NTSTATUS)0xC00002B3L)
#endif//STATUS_CANT_ENABLE_DENY_ONLY

//
// MessageId: STATUS_FLOAT_MULTIPLE_FAULTS
//
// MessageText:
//
// {EXCEPTION}
// Multiple floating point faults.
//
#ifndef STATUS_FLOAT_MULTIPLE_FAULTS
#define STATUS_FLOAT_MULTIPLE_FAULTS     ((NTSTATUS)0xC00002B4L)    // winnt
#endif//STATUS_FLOAT_MULTIPLE_FAULTS

//
// MessageId: STATUS_FLOAT_MULTIPLE_TRAPS
//
// MessageText:
//
// {EXCEPTION}
// Multiple floating point traps.
//
#ifndef STATUS_FLOAT_MULTIPLE_TRAPS
#define STATUS_FLOAT_MULTIPLE_TRAPS      ((NTSTATUS)0xC00002B5L)    // winnt
#endif//STATUS_FLOAT_MULTIPLE_TRAPS

//
// MessageId: STATUS_DEVICE_REMOVED
//
// MessageText:
//
// The device has been removed.
//
#ifndef STATUS_DEVICE_REMOVED
#define STATUS_DEVICE_REMOVED            ((NTSTATUS)0xC00002B6L)
#endif//STATUS_DEVICE_REMOVED

//
// MessageId: STATUS_JOURNAL_DELETE_IN_PROGRESS
//
// MessageText:
//
// The volume change journal is being deleted.
//
#ifndef STATUS_JOURNAL_DELETE_IN_PROGRESS
#define STATUS_JOURNAL_DELETE_IN_PROGRESS ((NTSTATUS)0xC00002B7L)
#endif//STATUS_JOURNAL_DELETE_IN_PROGRESS

//
// MessageId: STATUS_JOURNAL_NOT_ACTIVE
//
// MessageText:
//
// The volume change journal is not active.
//
#ifndef STATUS_JOURNAL_NOT_ACTIVE
#define STATUS_JOURNAL_NOT_ACTIVE        ((NTSTATUS)0xC00002B8L)
#endif//STATUS_JOURNAL_NOT_ACTIVE

//
// MessageId: STATUS_NOINTERFACE
//
// MessageText:
//
// The requested interface is not supported.
//
#ifndef STATUS_NOINTERFACE
#define STATUS_NOINTERFACE               ((NTSTATUS)0xC00002B9L)
#endif//STATUS_NOINTERFACE

//
// MessageId: STATUS_DS_RIDMGR_DISABLED
//
// MessageText:
//
// The directory service detected the subsystem that allocates relative identifiers is disabled. This can occur as a protective mechanism when the system determines a significant portion of relative identifiers (RIDs) have been exhausted. Please see http://go.microsoft.com/fwlink/?LinkId=228610 for recommended diagnostic steps and the procedure to re-enable account creation.
//
#ifndef STATUS_DS_RIDMGR_DISABLED
#define STATUS_DS_RIDMGR_DISABLED        ((NTSTATUS)0xC00002BAL)
#endif//STATUS_DS_RIDMGR_DISABLED

//
// MessageId: STATUS_DS_ADMIN_LIMIT_EXCEEDED
//
// MessageText:
//
// A directory service resource limit has been exceeded.
//
#ifndef STATUS_DS_ADMIN_LIMIT_EXCEEDED
#define STATUS_DS_ADMIN_LIMIT_EXCEEDED   ((NTSTATUS)0xC00002C1L)
#endif//STATUS_DS_ADMIN_LIMIT_EXCEEDED

//
// MessageId: STATUS_DRIVER_FAILED_SLEEP
//
// MessageText:
//
// {System Standby Failed}
// The driver %hs does not support standby mode. Updating this driver may allow the system to go to standby mode.
//
#ifndef STATUS_DRIVER_FAILED_SLEEP
#define STATUS_DRIVER_FAILED_SLEEP       ((NTSTATUS)0xC00002C2L)
#endif//STATUS_DRIVER_FAILED_SLEEP

//
// MessageId: STATUS_MUTUAL_AUTHENTICATION_FAILED
//
// MessageText:
//
// Mutual Authentication failed. The server's password is out of date at the domain controller.
//
#ifndef STATUS_MUTUAL_AUTHENTICATION_FAILED
#define STATUS_MUTUAL_AUTHENTICATION_FAILED ((NTSTATUS)0xC00002C3L)
#endif//STATUS_MUTUAL_AUTHENTICATION_FAILED

//
// MessageId: STATUS_CORRUPT_SYSTEM_FILE
//
// MessageText:
//
// The system file %1 has become corrupt and has been replaced.
//
#ifndef STATUS_CORRUPT_SYSTEM_FILE
#define STATUS_CORRUPT_SYSTEM_FILE       ((NTSTATUS)0xC00002C4L)
#endif//STATUS_CORRUPT_SYSTEM_FILE

//
// MessageId: STATUS_DATATYPE_MISALIGNMENT_ERROR
//
// MessageText:
//
// {EXCEPTION}
// Alignment Error
// A datatype misalignment error was detected in a load or store instruction.
//
#ifndef STATUS_DATATYPE_MISALIGNMENT_ERROR
#define STATUS_DATATYPE_MISALIGNMENT_ERROR ((NTSTATUS)0xC00002C5L)
#endif//STATUS_DATATYPE_MISALIGNMENT_ERROR

//
// MessageId: STATUS_WMI_READ_ONLY
//
// MessageText:
//
// The WMI data item or data block is read only.
//
#ifndef STATUS_WMI_READ_ONLY
#define STATUS_WMI_READ_ONLY             ((NTSTATUS)0xC00002C6L)
#endif//STATUS_WMI_READ_ONLY

//
// MessageId: STATUS_WMI_SET_FAILURE
//
// MessageText:
//
// The WMI data item or data block could not be changed.
//
#ifndef STATUS_WMI_SET_FAILURE
#define STATUS_WMI_SET_FAILURE           ((NTSTATUS)0xC00002C7L)
#endif//STATUS_WMI_SET_FAILURE

//
// MessageId: STATUS_COMMITMENT_MINIMUM
//
// MessageText:
//
// {Virtual Memory Minimum Too Low}
// Your system is low on virtual memory. Windows is increasing the size of your virtual memory paging file. During this process, memory requests for some applications may be denied. For more information, see Help.
//
#ifndef STATUS_COMMITMENT_MINIMUM
#define STATUS_COMMITMENT_MINIMUM        ((NTSTATUS)0xC00002C8L)
#endif//STATUS_COMMITMENT_MINIMUM

//
// MessageId: STATUS_REG_NAT_CONSUMPTION
//
// MessageText:
//
// {EXCEPTION}
// Register NaT consumption faults.
// A NaT value is consumed on a non speculative instruction.
//
#ifndef STATUS_REG_NAT_CONSUMPTION
#define STATUS_REG_NAT_CONSUMPTION       ((NTSTATUS)0xC00002C9L)    // winnt
#endif//STATUS_REG_NAT_CONSUMPTION

//
// MessageId: STATUS_TRANSPORT_FULL
//
// MessageText:
//
// The medium changer's transport element contains media, which is causing the operation to fail.
//
#ifndef STATUS_TRANSPORT_FULL
#define STATUS_TRANSPORT_FULL            ((NTSTATUS)0xC00002CAL)
#endif//STATUS_TRANSPORT_FULL

//
// MessageId: STATUS_DS_SAM_INIT_FAILURE
//
// MessageText:
//
// Security Accounts Manager initialization failed because of the following error:
// %hs
// Error Status: 0x%x.
// Please shutdown this system and reboot into Directory Services Restore Mode, check the event log for more detailed information.
//
#ifndef STATUS_DS_SAM_INIT_FAILURE
#define STATUS_DS_SAM_INIT_FAILURE       ((NTSTATUS)0xC00002CBL)
#endif//STATUS_DS_SAM_INIT_FAILURE

//
// MessageId: STATUS_ONLY_IF_CONNECTED
//
// MessageText:
//
// This operation is supported only when you are connected to the server.
//
#ifndef STATUS_ONLY_IF_CONNECTED
#define STATUS_ONLY_IF_CONNECTED         ((NTSTATUS)0xC00002CCL)
#endif//STATUS_ONLY_IF_CONNECTED

//
// MessageId: STATUS_DS_SENSITIVE_GROUP_VIOLATION
//
// MessageText:
//
// Only an administrator can modify the membership list of an administrative group.
//
#ifndef STATUS_DS_SENSITIVE_GROUP_VIOLATION
#define STATUS_DS_SENSITIVE_GROUP_VIOLATION ((NTSTATUS)0xC00002CDL)
#endif//STATUS_DS_SENSITIVE_GROUP_VIOLATION

//
// MessageId: STATUS_PNP_RESTART_ENUMERATION
//
// MessageText:
//
// A device was removed so enumeration must be restarted.
//
#ifndef STATUS_PNP_RESTART_ENUMERATION
#define STATUS_PNP_RESTART_ENUMERATION   ((NTSTATUS)0xC00002CEL)
#endif//STATUS_PNP_RESTART_ENUMERATION

//
// MessageId: STATUS_JOURNAL_ENTRY_DELETED
//
// MessageText:
//
// The journal entry has been deleted from the journal.
//
#ifndef STATUS_JOURNAL_ENTRY_DELETED
#define STATUS_JOURNAL_ENTRY_DELETED     ((NTSTATUS)0xC00002CFL)
#endif//STATUS_JOURNAL_ENTRY_DELETED

//
// MessageId: STATUS_DS_CANT_MOD_PRIMARYGROUPID
//
// MessageText:
//
// Cannot change the primary group ID of a domain controller account.
//
#ifndef STATUS_DS_CANT_MOD_PRIMARYGROUPID
#define STATUS_DS_CANT_MOD_PRIMARYGROUPID ((NTSTATUS)0xC00002D0L)
#endif//STATUS_DS_CANT_MOD_PRIMARYGROUPID

//
// MessageId: STATUS_SYSTEM_IMAGE_BAD_SIGNATURE
//
// MessageText:
//
// {Fatal System Error}
// The system image %s is not properly signed. The file has been replaced with the signed file. The system has been shut down.
//
#ifndef STATUS_SYSTEM_IMAGE_BAD_SIGNATURE
#define STATUS_SYSTEM_IMAGE_BAD_SIGNATURE ((NTSTATUS)0xC00002D1L)
#endif//STATUS_SYSTEM_IMAGE_BAD_SIGNATURE

//
// MessageId: STATUS_PNP_REBOOT_REQUIRED
//
// MessageText:
//
// Device will not start without a reboot.
//
#ifndef STATUS_PNP_REBOOT_REQUIRED
#define STATUS_PNP_REBOOT_REQUIRED       ((NTSTATUS)0xC00002D2L)
#endif//STATUS_PNP_REBOOT_REQUIRED

//
// MessageId: STATUS_POWER_STATE_INVALID
//
// MessageText:
//
// Current device power state cannot support this request.
//
#ifndef STATUS_POWER_STATE_INVALID
#define STATUS_POWER_STATE_INVALID       ((NTSTATUS)0xC00002D3L)
#endif//STATUS_POWER_STATE_INVALID

//
// MessageId: STATUS_DS_INVALID_GROUP_TYPE
//
// MessageText:
//
// The specified group type is invalid.
//
#ifndef STATUS_DS_INVALID_GROUP_TYPE
#define STATUS_DS_INVALID_GROUP_TYPE     ((NTSTATUS)0xC00002D4L)
#endif//STATUS_DS_INVALID_GROUP_TYPE

//
// MessageId: STATUS_DS_NO_NEST_GLOBALGROUP_IN_MIXEDDOMAIN
//
// MessageText:
//
// In mixed domain no nesting of global group if group is security enabled.
//
#ifndef STATUS_DS_NO_NEST_GLOBALGROUP_IN_MIXEDDOMAIN
#define STATUS_DS_NO_NEST_GLOBALGROUP_IN_MIXEDDOMAIN ((NTSTATUS)0xC00002D5L)
#endif//STATUS_DS_NO_NEST_GLOBALGROUP_IN_MIXEDDOMAIN

//
// MessageId: STATUS_DS_NO_NEST_LOCALGROUP_IN_MIXEDDOMAIN
//
// MessageText:
//
// In mixed domain, cannot nest local groups with other local groups, if the group is security enabled.
//
#ifndef STATUS_DS_NO_NEST_LOCALGROUP_IN_MIXEDDOMAIN
#define STATUS_DS_NO_NEST_LOCALGROUP_IN_MIXEDDOMAIN ((NTSTATUS)0xC00002D6L)
#endif//STATUS_DS_NO_NEST_LOCALGROUP_IN_MIXEDDOMAIN

//
// MessageId: STATUS_DS_GLOBAL_CANT_HAVE_LOCAL_MEMBER
//
// MessageText:
//
// A global group cannot have a local group as a member.
//
#ifndef STATUS_DS_GLOBAL_CANT_HAVE_LOCAL_MEMBER
#define STATUS_DS_GLOBAL_CANT_HAVE_LOCAL_MEMBER ((NTSTATUS)0xC00002D7L)
#endif//STATUS_DS_GLOBAL_CANT_HAVE_LOCAL_MEMBER

//
// MessageId: STATUS_DS_GLOBAL_CANT_HAVE_UNIVERSAL_MEMBER
//
// MessageText:
//
// A global group cannot have a universal group as a member.
//
#ifndef STATUS_DS_GLOBAL_CANT_HAVE_UNIVERSAL_MEMBER
#define STATUS_DS_GLOBAL_CANT_HAVE_UNIVERSAL_MEMBER ((NTSTATUS)0xC00002D8L)
#endif//STATUS_DS_GLOBAL_CANT_HAVE_UNIVERSAL_MEMBER

//
// MessageId: STATUS_DS_UNIVERSAL_CANT_HAVE_LOCAL_MEMBER
//
// MessageText:
//
// A universal group cannot have a local group as a member.
//
#ifndef STATUS_DS_UNIVERSAL_CANT_HAVE_LOCAL_MEMBER
#define STATUS_DS_UNIVERSAL_CANT_HAVE_LOCAL_MEMBER ((NTSTATUS)0xC00002D9L)
#endif//STATUS_DS_UNIVERSAL_CANT_HAVE_LOCAL_MEMBER

//
// MessageId: STATUS_DS_GLOBAL_CANT_HAVE_CROSSDOMAIN_MEMBER
//
// MessageText:
//
// A global group cannot have a cross domain member.
//
#ifndef STATUS_DS_GLOBAL_CANT_HAVE_CROSSDOMAIN_MEMBER
#define STATUS_DS_GLOBAL_CANT_HAVE_CROSSDOMAIN_MEMBER ((NTSTATUS)0xC00002DAL)
#endif//STATUS_DS_GLOBAL_CANT_HAVE_CROSSDOMAIN_MEMBER

//
// MessageId: STATUS_DS_LOCAL_CANT_HAVE_CROSSDOMAIN_LOCAL_MEMBER
//
// MessageText:
//
// A local group cannot have another cross domain local group as a member.
//
#ifndef STATUS_DS_LOCAL_CANT_HAVE_CROSSDOMAIN_LOCAL_MEMBER
#define STATUS_DS_LOCAL_CANT_HAVE_CROSSDOMAIN_LOCAL_MEMBER ((NTSTATUS)0xC00002DBL)
#endif//STATUS_DS_LOCAL_CANT_HAVE_CROSSDOMAIN_LOCAL_MEMBER

//
// MessageId: STATUS_DS_HAVE_PRIMARY_MEMBERS
//
// MessageText:
//
// Cannot change to security disabled group because of having primary members in this group.
//
#ifndef STATUS_DS_HAVE_PRIMARY_MEMBERS
#define STATUS_DS_HAVE_PRIMARY_MEMBERS   ((NTSTATUS)0xC00002DCL)
#endif//STATUS_DS_HAVE_PRIMARY_MEMBERS

//
// MessageId: STATUS_WMI_NOT_SUPPORTED
//
// MessageText:
//
// The WMI operation is not supported by the data block or method.
//
#ifndef STATUS_WMI_NOT_SUPPORTED
#define STATUS_WMI_NOT_SUPPORTED         ((NTSTATUS)0xC00002DDL)
#endif//STATUS_WMI_NOT_SUPPORTED

//
// MessageId: STATUS_INSUFFICIENT_POWER
//
// MessageText:
//
// There is not enough power to complete the requested operation.
//
#ifndef STATUS_INSUFFICIENT_POWER
#define STATUS_INSUFFICIENT_POWER        ((NTSTATUS)0xC00002DEL)
#endif//STATUS_INSUFFICIENT_POWER

//
// MessageId: STATUS_SAM_NEED_BOOTKEY_PASSWORD
//
// MessageText:
//
// Security Account Manager needs to get the boot password.
//
#ifndef STATUS_SAM_NEED_BOOTKEY_PASSWORD
#define STATUS_SAM_NEED_BOOTKEY_PASSWORD ((NTSTATUS)0xC00002DFL)
#endif//STATUS_SAM_NEED_BOOTKEY_PASSWORD

//
// MessageId: STATUS_SAM_NEED_BOOTKEY_FLOPPY
//
// MessageText:
//
// Security Account Manager needs to get the boot key from floppy disk.
//
#ifndef STATUS_SAM_NEED_BOOTKEY_FLOPPY
#define STATUS_SAM_NEED_BOOTKEY_FLOPPY   ((NTSTATUS)0xC00002E0L)
#endif//STATUS_SAM_NEED_BOOTKEY_FLOPPY

//
// MessageId: STATUS_DS_CANT_START
//
// MessageText:
//
// Directory Service cannot start.
//
#ifndef STATUS_DS_CANT_START
#define STATUS_DS_CANT_START             ((NTSTATUS)0xC00002E1L)
#endif//STATUS_DS_CANT_START

//
// MessageId: STATUS_DS_INIT_FAILURE
//
// MessageText:
//
// Directory Services could not start because of the following error:
// %hs
// Error Status: 0x%x.
// Please shutdown this system and reboot into Directory Services Restore Mode, check the event log for more detailed information.
//
#ifndef STATUS_DS_INIT_FAILURE
#define STATUS_DS_INIT_FAILURE           ((NTSTATUS)0xC00002E2L)
#endif//STATUS_DS_INIT_FAILURE

//
// MessageId: STATUS_SAM_INIT_FAILURE
//
// MessageText:
//
// Security Accounts Manager initialization failed because of the following error:
// %hs
// Error Status: 0x%x.
// Please click OK to shutdown this system and reboot into Safe Mode, check the event log for more detailed information.
//
#ifndef STATUS_SAM_INIT_FAILURE
#define STATUS_SAM_INIT_FAILURE          ((NTSTATUS)0xC00002E3L)
#endif//STATUS_SAM_INIT_FAILURE

//
// MessageId: STATUS_DS_GC_REQUIRED
//
// MessageText:
//
// The requested operation can be performed only on a global catalog server.
//
#ifndef STATUS_DS_GC_REQUIRED
#define STATUS_DS_GC_REQUIRED            ((NTSTATUS)0xC00002E4L)
#endif//STATUS_DS_GC_REQUIRED

//
// MessageId: STATUS_DS_LOCAL_MEMBER_OF_LOCAL_ONLY
//
// MessageText:
//
// A local group can only be a member of other local groups in the same domain.
//
#ifndef STATUS_DS_LOCAL_MEMBER_OF_LOCAL_ONLY
#define STATUS_DS_LOCAL_MEMBER_OF_LOCAL_ONLY ((NTSTATUS)0xC00002E5L)
#endif//STATUS_DS_LOCAL_MEMBER_OF_LOCAL_ONLY

//
// MessageId: STATUS_DS_NO_FPO_IN_UNIVERSAL_GROUPS
//
// MessageText:
//
// Foreign security principals cannot be members of universal groups.
//
#ifndef STATUS_DS_NO_FPO_IN_UNIVERSAL_GROUPS
#define STATUS_DS_NO_FPO_IN_UNIVERSAL_GROUPS ((NTSTATUS)0xC00002E6L)
#endif//STATUS_DS_NO_FPO_IN_UNIVERSAL_GROUPS

//
// MessageId: STATUS_DS_MACHINE_ACCOUNT_QUOTA_EXCEEDED
//
// MessageText:
//
// Your computer could not be joined to the domain. You have exceeded the maximum number of computer accounts you are allowed to create in this domain. Contact your system administrator to have this limit reset or increased.
//
#ifndef STATUS_DS_MACHINE_ACCOUNT_QUOTA_EXCEEDED
#define STATUS_DS_MACHINE_ACCOUNT_QUOTA_EXCEEDED ((NTSTATUS)0xC00002E7L)
#endif//STATUS_DS_MACHINE_ACCOUNT_QUOTA_EXCEEDED

//
// MessageId: STATUS_MULTIPLE_FAULT_VIOLATION
//
// MessageText:
//
//  STATUS_MULTIPLE_FAULT_VIOLATION
//
#ifndef STATUS_MULTIPLE_FAULT_VIOLATION
#define STATUS_MULTIPLE_FAULT_VIOLATION  ((NTSTATUS)0xC00002E8L)
#endif//STATUS_MULTIPLE_FAULT_VIOLATION

//
// MessageId: STATUS_CURRENT_DOMAIN_NOT_ALLOWED
//
// MessageText:
//
// This operation cannot be performed on the current domain.
//
#ifndef STATUS_CURRENT_DOMAIN_NOT_ALLOWED
#define STATUS_CURRENT_DOMAIN_NOT_ALLOWED ((NTSTATUS)0xC00002E9L)
#endif//STATUS_CURRENT_DOMAIN_NOT_ALLOWED

//
// MessageId: STATUS_CANNOT_MAKE
//
// MessageText:
//
// The directory or file cannot be created.
//
#ifndef STATUS_CANNOT_MAKE
#define STATUS_CANNOT_MAKE               ((NTSTATUS)0xC00002EAL)
#endif//STATUS_CANNOT_MAKE

//
// MessageId: STATUS_SYSTEM_SHUTDOWN
//
// MessageText:
//
// The system is in the process of shutting down.
//
#ifndef STATUS_SYSTEM_SHUTDOWN
#define STATUS_SYSTEM_SHUTDOWN           ((NTSTATUS)0xC00002EBL)
#endif//STATUS_SYSTEM_SHUTDOWN

//
// MessageId: STATUS_DS_INIT_FAILURE_CONSOLE
//
// MessageText:
//
// Directory Services could not start because of the following error:
// %hs
// Error Status: 0x%x.
// Please click OK to shutdown the system. You can use the recovery console to diagnose the system further.
//
#ifndef STATUS_DS_INIT_FAILURE_CONSOLE
#define STATUS_DS_INIT_FAILURE_CONSOLE   ((NTSTATUS)0xC00002ECL)
#endif//STATUS_DS_INIT_FAILURE_CONSOLE

//
// MessageId: STATUS_DS_SAM_INIT_FAILURE_CONSOLE
//
// MessageText:
//
// Security Accounts Manager initialization failed because of the following error:
// %hs
// Error Status: 0x%x.
// Please click OK to shutdown the system. You can use the recovery console to diagnose the system further.
//
#ifndef STATUS_DS_SAM_INIT_FAILURE_CONSOLE
#define STATUS_DS_SAM_INIT_FAILURE_CONSOLE ((NTSTATUS)0xC00002EDL)
#endif//STATUS_DS_SAM_INIT_FAILURE_CONSOLE

//
// MessageId: STATUS_UNFINISHED_CONTEXT_DELETED
//
// MessageText:
//
// A security context was deleted before the context was completed. This is considered a logon failure.
//
#ifndef STATUS_UNFINISHED_CONTEXT_DELETED
#define STATUS_UNFINISHED_CONTEXT_DELETED ((NTSTATUS)0xC00002EEL)
#endif//STATUS_UNFINISHED_CONTEXT_DELETED

//
// MessageId: STATUS_NO_TGT_REPLY
//
// MessageText:
//
// The client is trying to negotiate a context and the server requires user-to-user but didn't send a TGT reply.
//
#ifndef STATUS_NO_TGT_REPLY
#define STATUS_NO_TGT_REPLY              ((NTSTATUS)0xC00002EFL)
#endif//STATUS_NO_TGT_REPLY

//
// MessageId: STATUS_OBJECTID_NOT_FOUND
//
// MessageText:
//
// An object ID was not found in the file.
//
#ifndef STATUS_OBJECTID_NOT_FOUND
#define STATUS_OBJECTID_NOT_FOUND        ((NTSTATUS)0xC00002F0L)
#endif//STATUS_OBJECTID_NOT_FOUND

//
// MessageId: STATUS_NO_IP_ADDRESSES
//
// MessageText:
//
// Unable to accomplish the requested task because the local machine does not have any IP addresses.
//
#ifndef STATUS_NO_IP_ADDRESSES
#define STATUS_NO_IP_ADDRESSES           ((NTSTATUS)0xC00002F1L)
#endif//STATUS_NO_IP_ADDRESSES

//
// MessageId: STATUS_WRONG_CREDENTIAL_HANDLE
//
// MessageText:
//
// The supplied credential handle does not match the credential associated with the security context.
//
#ifndef STATUS_WRONG_CREDENTIAL_HANDLE
#define STATUS_WRONG_CREDENTIAL_HANDLE   ((NTSTATUS)0xC00002F2L)
#endif//STATUS_WRONG_CREDENTIAL_HANDLE

//
// MessageId: STATUS_CRYPTO_SYSTEM_INVALID
//
// MessageText:
//
// The crypto system or checksum function is invalid because a required function is unavailable.
//
#ifndef STATUS_CRYPTO_SYSTEM_INVALID
#define STATUS_CRYPTO_SYSTEM_INVALID     ((NTSTATUS)0xC00002F3L)
#endif//STATUS_CRYPTO_SYSTEM_INVALID

//
// MessageId: STATUS_MAX_REFERRALS_EXCEEDED
//
// MessageText:
//
// The number of maximum ticket referrals has been exceeded.
//
#ifndef STATUS_MAX_REFERRALS_EXCEEDED
#define STATUS_MAX_REFERRALS_EXCEEDED    ((NTSTATUS)0xC00002F4L)
#endif//STATUS_MAX_REFERRALS_EXCEEDED

//
// MessageId: STATUS_MUST_BE_KDC
//
// MessageText:
//
// The local machine must be a Kerberos KDC (domain controller) and it is not.
//
#ifndef STATUS_MUST_BE_KDC
#define STATUS_MUST_BE_KDC               ((NTSTATUS)0xC00002F5L)
#endif//STATUS_MUST_BE_KDC

//
// MessageId: STATUS_STRONG_CRYPTO_NOT_SUPPORTED
//
// MessageText:
//
// The other end of the security negotiation is requires strong crypto but it is not supported on the local machine.
//
#ifndef STATUS_STRONG_CRYPTO_NOT_SUPPORTED
#define STATUS_STRONG_CRYPTO_NOT_SUPPORTED ((NTSTATUS)0xC00002F6L)
#endif//STATUS_STRONG_CRYPTO_NOT_SUPPORTED

//
// MessageId: STATUS_TOO_MANY_PRINCIPALS
//
// MessageText:
//
// The KDC reply contained more than one principal name.
//
#ifndef STATUS_TOO_MANY_PRINCIPALS
#define STATUS_TOO_MANY_PRINCIPALS       ((NTSTATUS)0xC00002F7L)
#endif//STATUS_TOO_MANY_PRINCIPALS

//
// MessageId: STATUS_NO_PA_DATA
//
// MessageText:
//
// Expected to find PA data for a hint of what etype to use, but it was not found.
//
#ifndef STATUS_NO_PA_DATA
#define STATUS_NO_PA_DATA                ((NTSTATUS)0xC00002F8L)
#endif//STATUS_NO_PA_DATA

//
// MessageId: STATUS_PKINIT_NAME_MISMATCH
//
// MessageText:
//
// The client certificate does not contain a valid UPN, or does not match the client name in the logon request. Please contact your administrator.
//
#ifndef STATUS_PKINIT_NAME_MISMATCH
#define STATUS_PKINIT_NAME_MISMATCH      ((NTSTATUS)0xC00002F9L)
#endif//STATUS_PKINIT_NAME_MISMATCH

//
// MessageId: STATUS_SMARTCARD_LOGON_REQUIRED
//
// MessageText:
//
// Smartcard logon is required and was not used.
//
#ifndef STATUS_SMARTCARD_LOGON_REQUIRED
#define STATUS_SMARTCARD_LOGON_REQUIRED  ((NTSTATUS)0xC00002FAL)
#endif//STATUS_SMARTCARD_LOGON_REQUIRED

//
// MessageId: STATUS_KDC_INVALID_REQUEST
//
// MessageText:
//
// An invalid request was sent to the KDC.
//
#ifndef STATUS_KDC_INVALID_REQUEST
#define STATUS_KDC_INVALID_REQUEST       ((NTSTATUS)0xC00002FBL)
#endif//STATUS_KDC_INVALID_REQUEST

//
// MessageId: STATUS_KDC_UNABLE_TO_REFER
//
// MessageText:
//
// The KDC was unable to generate a referral for the service requested.
//
#ifndef STATUS_KDC_UNABLE_TO_REFER
#define STATUS_KDC_UNABLE_TO_REFER       ((NTSTATUS)0xC00002FCL)
#endif//STATUS_KDC_UNABLE_TO_REFER

//
// MessageId: STATUS_KDC_UNKNOWN_ETYPE
//
// MessageText:
//
// The encryption type requested is not supported by the KDC.
//
#ifndef STATUS_KDC_UNKNOWN_ETYPE
#define STATUS_KDC_UNKNOWN_ETYPE         ((NTSTATUS)0xC00002FDL)
#endif//STATUS_KDC_UNKNOWN_ETYPE

//
// MessageId: STATUS_SHUTDOWN_IN_PROGRESS
//
// MessageText:
//
// A system shutdown is in progress.
//
#ifndef STATUS_SHUTDOWN_IN_PROGRESS
#define STATUS_SHUTDOWN_IN_PROGRESS      ((NTSTATUS)0xC00002FEL)
#endif//STATUS_SHUTDOWN_IN_PROGRESS

//
// MessageId: STATUS_SERVER_SHUTDOWN_IN_PROGRESS
//
// MessageText:
//
// The server machine is shutting down.
//
#ifndef STATUS_SERVER_SHUTDOWN_IN_PROGRESS
#define STATUS_SERVER_SHUTDOWN_IN_PROGRESS ((NTSTATUS)0xC00002FFL)
#endif//STATUS_SERVER_SHUTDOWN_IN_PROGRESS

//
// MessageId: STATUS_NOT_SUPPORTED_ON_SBS
//
// MessageText:
//
// This operation is not supported on a computer running Windows Server 2003 for Small Business Server
//
#ifndef STATUS_NOT_SUPPORTED_ON_SBS
#define STATUS_NOT_SUPPORTED_ON_SBS      ((NTSTATUS)0xC0000300L)
#endif//STATUS_NOT_SUPPORTED_ON_SBS

//
// MessageId: STATUS_WMI_GUID_DISCONNECTED
//
// MessageText:
//
// The WMI GUID is no longer available
//
#ifndef STATUS_WMI_GUID_DISCONNECTED
#define STATUS_WMI_GUID_DISCONNECTED     ((NTSTATUS)0xC0000301L)
#endif//STATUS_WMI_GUID_DISCONNECTED

//
// MessageId: STATUS_WMI_ALREADY_DISABLED
//
// MessageText:
//
// Collection or events for the WMI GUID is already disabled.
//
#ifndef STATUS_WMI_ALREADY_DISABLED
#define STATUS_WMI_ALREADY_DISABLED      ((NTSTATUS)0xC0000302L)
#endif//STATUS_WMI_ALREADY_DISABLED

//
// MessageId: STATUS_WMI_ALREADY_ENABLED
//
// MessageText:
//
// Collection or events for the WMI GUID is already enabled.
//
#ifndef STATUS_WMI_ALREADY_ENABLED
#define STATUS_WMI_ALREADY_ENABLED       ((NTSTATUS)0xC0000303L)
#endif//STATUS_WMI_ALREADY_ENABLED

//
// MessageId: STATUS_MFT_TOO_FRAGMENTED
//
// MessageText:
//
// The Master File Table on the volume is too fragmented to complete this operation.
//
#ifndef STATUS_MFT_TOO_FRAGMENTED
#define STATUS_MFT_TOO_FRAGMENTED        ((NTSTATUS)0xC0000304L)
#endif//STATUS_MFT_TOO_FRAGMENTED

//
// MessageId: STATUS_COPY_PROTECTION_FAILURE
//
// MessageText:
//
// Copy protection failure.
//
#ifndef STATUS_COPY_PROTECTION_FAILURE
#define STATUS_COPY_PROTECTION_FAILURE   ((NTSTATUS)0xC0000305L)
#endif//STATUS_COPY_PROTECTION_FAILURE

//
// MessageId: STATUS_CSS_AUTHENTICATION_FAILURE
//
// MessageText:
//
// Copy protection error - DVD CSS Authentication failed.
//
#ifndef STATUS_CSS_AUTHENTICATION_FAILURE
#define STATUS_CSS_AUTHENTICATION_FAILURE ((NTSTATUS)0xC0000306L)
#endif//STATUS_CSS_AUTHENTICATION_FAILURE

//
// MessageId: STATUS_CSS_KEY_NOT_PRESENT
//
// MessageText:
//
// Copy protection error - The given sector does not contain a valid key.
//
#ifndef STATUS_CSS_KEY_NOT_PRESENT
#define STATUS_CSS_KEY_NOT_PRESENT       ((NTSTATUS)0xC0000307L)
#endif//STATUS_CSS_KEY_NOT_PRESENT

//
// MessageId: STATUS_CSS_KEY_NOT_ESTABLISHED
//
// MessageText:
//
// Copy protection error - DVD session key not established.
//
#ifndef STATUS_CSS_KEY_NOT_ESTABLISHED
#define STATUS_CSS_KEY_NOT_ESTABLISHED   ((NTSTATUS)0xC0000308L)
#endif//STATUS_CSS_KEY_NOT_ESTABLISHED

//
// MessageId: STATUS_CSS_SCRAMBLED_SECTOR
//
// MessageText:
//
// Copy protection error - The read failed because the sector is encrypted.
//
#ifndef STATUS_CSS_SCRAMBLED_SECTOR
#define STATUS_CSS_SCRAMBLED_SECTOR      ((NTSTATUS)0xC0000309L)
#endif//STATUS_CSS_SCRAMBLED_SECTOR

//
// MessageId: STATUS_CSS_REGION_MISMATCH
//
// MessageText:
//
// Copy protection error - The given DVD's region does not correspond to the
// region setting of the drive.
//
#ifndef STATUS_CSS_REGION_MISMATCH
#define STATUS_CSS_REGION_MISMATCH       ((NTSTATUS)0xC000030AL)
#endif//STATUS_CSS_REGION_MISMATCH

//
// MessageId: STATUS_CSS_RESETS_EXHAUSTED
//
// MessageText:
//
// Copy protection error - The drive's region setting may be permanent.
//
#ifndef STATUS_CSS_RESETS_EXHAUSTED
#define STATUS_CSS_RESETS_EXHAUSTED      ((NTSTATUS)0xC000030BL)
#endif//STATUS_CSS_RESETS_EXHAUSTED

//
// MessageId: STATUS_PASSWORD_CHANGE_REQUIRED
//
// MessageText:
//
// EAS policy requires that the user change their password before this operation can be performed.
//
#ifndef STATUS_PASSWORD_CHANGE_REQUIRED
#define STATUS_PASSWORD_CHANGE_REQUIRED  ((NTSTATUS)0xC000030CL)
#endif//STATUS_PASSWORD_CHANGE_REQUIRED

//
// MessageId: STATUS_LOST_MODE_LOGON_RESTRICTION
//
// MessageText:
//
// An administrator has restricted sign in. To sign in, make sure your device is connected to the Internet, and have your administrator sign in first.
//
#ifndef STATUS_LOST_MODE_LOGON_RESTRICTION
#define STATUS_LOST_MODE_LOGON_RESTRICTION ((NTSTATUS)0xC000030DL)
#endif//STATUS_LOST_MODE_LOGON_RESTRICTION

/*++

 MessageId's 0x030e - 0x031f (inclusive) are reserved for future **STORAGE**
 copy protection errors.

--*/
//
// MessageId: STATUS_PKINIT_FAILURE
//
// MessageText:
//
// The Kerberos protocol encountered an error while validating the KDC certificate during logon. There is more information in the system event log.
//
#ifndef STATUS_PKINIT_FAILURE
#define STATUS_PKINIT_FAILURE            ((NTSTATUS)0xC0000320L)
#endif//STATUS_PKINIT_FAILURE

//
// MessageId: STATUS_SMARTCARD_SUBSYSTEM_FAILURE
//
// MessageText:
//
// The Kerberos protocol encountered an error while attempting to utilize the smartcard subsystem.
//
#ifndef STATUS_SMARTCARD_SUBSYSTEM_FAILURE
#define STATUS_SMARTCARD_SUBSYSTEM_FAILURE ((NTSTATUS)0xC0000321L)
#endif//STATUS_SMARTCARD_SUBSYSTEM_FAILURE

//
// MessageId: STATUS_NO_KERB_KEY
//
// MessageText:
//
// The target server does not have acceptable Kerberos credentials.
//
#ifndef STATUS_NO_KERB_KEY
#define STATUS_NO_KERB_KEY               ((NTSTATUS)0xC0000322L)
#endif//STATUS_NO_KERB_KEY

/*++

 MessageId's 0x0323 - 0x034f (inclusive) are reserved for other future copy
 protection errors.

--*/
//
// MessageId: STATUS_HOST_DOWN
//
// MessageText:
//
// The transport determined that the remote system is down.
//
#ifndef STATUS_HOST_DOWN
#define STATUS_HOST_DOWN                 ((NTSTATUS)0xC0000350L)
#endif//STATUS_HOST_DOWN

//
// MessageId: STATUS_UNSUPPORTED_PREAUTH
//
// MessageText:
//
// An unsupported preauthentication mechanism was presented to the Kerberos package.
//
#ifndef STATUS_UNSUPPORTED_PREAUTH
#define STATUS_UNSUPPORTED_PREAUTH       ((NTSTATUS)0xC0000351L)
#endif//STATUS_UNSUPPORTED_PREAUTH

//
// MessageId: STATUS_EFS_ALG_BLOB_TOO_BIG
//
// MessageText:
//
// The encryption algorithm used on the source file needs a bigger key buffer than the one used on the destination file.
//
#ifndef STATUS_EFS_ALG_BLOB_TOO_BIG
#define STATUS_EFS_ALG_BLOB_TOO_BIG      ((NTSTATUS)0xC0000352L)
#endif//STATUS_EFS_ALG_BLOB_TOO_BIG

//
// MessageId: STATUS_PORT_NOT_SET
//
// MessageText:
//
// An attempt to remove a process's DebugPort was made, but a port was not already associated with the process.
//
#ifndef STATUS_PORT_NOT_SET
#define STATUS_PORT_NOT_SET              ((NTSTATUS)0xC0000353L)
#endif//STATUS_PORT_NOT_SET

//
// MessageId: STATUS_DEBUGGER_INACTIVE
//
// MessageText:
//
// Debugger Inactive: Windows may have been started without kernel debugging enabled.
//
#ifndef STATUS_DEBUGGER_INACTIVE
#define STATUS_DEBUGGER_INACTIVE         ((NTSTATUS)0xC0000354L)
#endif//STATUS_DEBUGGER_INACTIVE

//
// MessageId: STATUS_DS_VERSION_CHECK_FAILURE
//
// MessageText:
//
// This version of Windows is not compatible with the behavior version of directory forest, domain or domain controller.
//
#ifndef STATUS_DS_VERSION_CHECK_FAILURE
#define STATUS_DS_VERSION_CHECK_FAILURE  ((NTSTATUS)0xC0000355L)
#endif//STATUS_DS_VERSION_CHECK_FAILURE

//
// MessageId: STATUS_AUDITING_DISABLED
//
// MessageText:
//
// The specified event is currently not being audited.
//
#ifndef STATUS_AUDITING_DISABLED
#define STATUS_AUDITING_DISABLED         ((NTSTATUS)0xC0000356L)
#endif//STATUS_AUDITING_DISABLED

//
// MessageId: STATUS_PRENT4_MACHINE_ACCOUNT
//
// MessageText:
//
// The machine account was created pre-NT4. The account needs to be recreated.
//
#ifndef STATUS_PRENT4_MACHINE_ACCOUNT
#define STATUS_PRENT4_MACHINE_ACCOUNT    ((NTSTATUS)0xC0000357L)
#endif//STATUS_PRENT4_MACHINE_ACCOUNT

//
// MessageId: STATUS_DS_AG_CANT_HAVE_UNIVERSAL_MEMBER
//
// MessageText:
//
// A account group cannot have a universal group as a member.
//
#ifndef STATUS_DS_AG_CANT_HAVE_UNIVERSAL_MEMBER
#define STATUS_DS_AG_CANT_HAVE_UNIVERSAL_MEMBER ((NTSTATUS)0xC0000358L)
#endif//STATUS_DS_AG_CANT_HAVE_UNIVERSAL_MEMBER

//
// MessageId: STATUS_INVALID_IMAGE_WIN_32
//
// MessageText:
//
// The specified image file did not have the correct format, it appears to be a 32-bit Windows image.
//
#ifndef STATUS_INVALID_IMAGE_WIN_32
#define STATUS_INVALID_IMAGE_WIN_32      ((NTSTATUS)0xC0000359L)
#endif//STATUS_INVALID_IMAGE_WIN_32

//
// MessageId: STATUS_INVALID_IMAGE_WIN_64
//
// MessageText:
//
// The specified image file did not have the correct format, it appears to be a 64-bit Windows image.
//
#ifndef STATUS_INVALID_IMAGE_WIN_64
#define STATUS_INVALID_IMAGE_WIN_64      ((NTSTATUS)0xC000035AL)
#endif//STATUS_INVALID_IMAGE_WIN_64

//
// MessageId: STATUS_BAD_BINDINGS
//
// MessageText:
//
// Client's supplied SSPI channel bindings were incorrect.
//
#ifndef STATUS_BAD_BINDINGS
#define STATUS_BAD_BINDINGS              ((NTSTATUS)0xC000035BL)
#endif//STATUS_BAD_BINDINGS

//
// MessageId: STATUS_NETWORK_SESSION_EXPIRED
//
// MessageText:
//
// The client's session has expired, so the client must reauthenticate to continue accessing the remote resources.
//
#ifndef STATUS_NETWORK_SESSION_EXPIRED
#define STATUS_NETWORK_SESSION_EXPIRED   ((NTSTATUS)0xC000035CL)
#endif//STATUS_NETWORK_SESSION_EXPIRED

//
// MessageId: STATUS_APPHELP_BLOCK
//
// MessageText:
//
// AppHelp dialog canceled thus preventing the application from starting.
//
#ifndef STATUS_APPHELP_BLOCK
#define STATUS_APPHELP_BLOCK             ((NTSTATUS)0xC000035DL)
#endif//STATUS_APPHELP_BLOCK

//
// MessageId: STATUS_ALL_SIDS_FILTERED
//
// MessageText:
//
// The SID filtering operation removed all SIDs.
//
#ifndef STATUS_ALL_SIDS_FILTERED
#define STATUS_ALL_SIDS_FILTERED         ((NTSTATUS)0xC000035EL)
#endif//STATUS_ALL_SIDS_FILTERED

//
// MessageId: STATUS_NOT_SAFE_MODE_DRIVER
//
// MessageText:
//
// The driver was not loaded because the system is booting into safe mode.
//
#ifndef STATUS_NOT_SAFE_MODE_DRIVER
#define STATUS_NOT_SAFE_MODE_DRIVER      ((NTSTATUS)0xC000035FL)
#endif//STATUS_NOT_SAFE_MODE_DRIVER

//
// MessageId: STATUS_ACCESS_DISABLED_BY_POLICY_DEFAULT
//
// MessageText:
//
// Access to %1 has been restricted by your Administrator by the default software restriction policy level.
//
#ifndef STATUS_ACCESS_DISABLED_BY_POLICY_DEFAULT
#define STATUS_ACCESS_DISABLED_BY_POLICY_DEFAULT ((NTSTATUS)0xC0000361L)
#endif//STATUS_ACCESS_DISABLED_BY_POLICY_DEFAULT

//
// MessageId: STATUS_ACCESS_DISABLED_BY_POLICY_PATH
//
// MessageText:
//
// Access to %1 has been restricted by your Administrator by location with policy rule %2 placed on path %3
//
#ifndef STATUS_ACCESS_DISABLED_BY_POLICY_PATH
#define STATUS_ACCESS_DISABLED_BY_POLICY_PATH ((NTSTATUS)0xC0000362L)
#endif//STATUS_ACCESS_DISABLED_BY_POLICY_PATH

//
// MessageId: STATUS_ACCESS_DISABLED_BY_POLICY_PUBLISHER
//
// MessageText:
//
// Access to %1 has been restricted by your Administrator by software publisher policy.
//
#ifndef STATUS_ACCESS_DISABLED_BY_POLICY_PUBLISHER
#define STATUS_ACCESS_DISABLED_BY_POLICY_PUBLISHER ((NTSTATUS)0xC0000363L)
#endif//STATUS_ACCESS_DISABLED_BY_POLICY_PUBLISHER

//
// MessageId: STATUS_ACCESS_DISABLED_BY_POLICY_OTHER
//
// MessageText:
//
// Access to %1 has been restricted by your Administrator by policy rule %2.
//
#ifndef STATUS_ACCESS_DISABLED_BY_POLICY_OTHER
#define STATUS_ACCESS_DISABLED_BY_POLICY_OTHER ((NTSTATUS)0xC0000364L)
#endif//STATUS_ACCESS_DISABLED_BY_POLICY_OTHER

//
// MessageId: STATUS_FAILED_DRIVER_ENTRY
//
// MessageText:
//
// The driver was not loaded because it failed its initialization call.
//
#ifndef STATUS_FAILED_DRIVER_ENTRY
#define STATUS_FAILED_DRIVER_ENTRY       ((NTSTATUS)0xC0000365L)
#endif//STATUS_FAILED_DRIVER_ENTRY

//
// MessageId: STATUS_DEVICE_ENUMERATION_ERROR
//
// MessageText:
//
// The "%hs" encountered an error while applying power or reading the device configuration. This may be caused by a failure of your hardware or by a poor connection.
//
#ifndef STATUS_DEVICE_ENUMERATION_ERROR
#define STATUS_DEVICE_ENUMERATION_ERROR  ((NTSTATUS)0xC0000366L)
#endif//STATUS_DEVICE_ENUMERATION_ERROR

//
// MessageId: STATUS_MOUNT_POINT_NOT_RESOLVED
//
// MessageText:
//
// The create operation failed because the name contained at least one mount point which resolves to a volume to which the specified device object is not attached.
//
#ifndef STATUS_MOUNT_POINT_NOT_RESOLVED
#define STATUS_MOUNT_POINT_NOT_RESOLVED  ((NTSTATUS)0xC0000368L)
#endif//STATUS_MOUNT_POINT_NOT_RESOLVED

//
// MessageId: STATUS_INVALID_DEVICE_OBJECT_PARAMETER
//
// MessageText:
//
// The device object parameter is either not a valid device object or is not attached to the volume specified by the file name.
//
#ifndef STATUS_INVALID_DEVICE_OBJECT_PARAMETER
#define STATUS_INVALID_DEVICE_OBJECT_PARAMETER ((NTSTATUS)0xC0000369L)
#endif//STATUS_INVALID_DEVICE_OBJECT_PARAMETER

//
// MessageId: STATUS_MCA_OCCURED
//
// MessageText:
//
// A Machine Check Error has occurred. Please check the system eventlog for additional information.
//
#ifndef STATUS_MCA_OCCURED
#define STATUS_MCA_OCCURED               ((NTSTATUS)0xC000036AL)
#endif//STATUS_MCA_OCCURED

//
// MessageId: STATUS_DRIVER_BLOCKED_CRITICAL
//
// MessageText:
//
// Driver %2 has been blocked from loading.
//
#ifndef STATUS_DRIVER_BLOCKED_CRITICAL
#define STATUS_DRIVER_BLOCKED_CRITICAL   ((NTSTATUS)0xC000036BL)
#endif//STATUS_DRIVER_BLOCKED_CRITICAL

//
// MessageId: STATUS_DRIVER_BLOCKED
//
// MessageText:
//
// Driver %2 has been blocked from loading.
//
#ifndef STATUS_DRIVER_BLOCKED
#define STATUS_DRIVER_BLOCKED            ((NTSTATUS)0xC000036CL)
#endif//STATUS_DRIVER_BLOCKED

//
// MessageId: STATUS_DRIVER_DATABASE_ERROR
//
// MessageText:
//
// There was error [%2] processing the driver database.
//
#ifndef STATUS_DRIVER_DATABASE_ERROR
#define STATUS_DRIVER_DATABASE_ERROR     ((NTSTATUS)0xC000036DL)
#endif//STATUS_DRIVER_DATABASE_ERROR

//
// MessageId: STATUS_SYSTEM_HIVE_TOO_LARGE
//
// MessageText:
//
// System hive size has exceeded its limit.
//
#ifndef STATUS_SYSTEM_HIVE_TOO_LARGE
#define STATUS_SYSTEM_HIVE_TOO_LARGE     ((NTSTATUS)0xC000036EL)
#endif//STATUS_SYSTEM_HIVE_TOO_LARGE

//
// MessageId: STATUS_INVALID_IMPORT_OF_NON_DLL
//
// MessageText:
//
// A dynamic link library (DLL) referenced a module that was neither a DLL nor the process's executable image.
//
#ifndef STATUS_INVALID_IMPORT_OF_NON_DLL
#define STATUS_INVALID_IMPORT_OF_NON_DLL ((NTSTATUS)0xC000036FL)
#endif//STATUS_INVALID_IMPORT_OF_NON_DLL

//
// MessageId: STATUS_DS_SHUTTING_DOWN
//
// MessageText:
//
// The Directory Service is shutting down.
//
#ifndef STATUS_DS_SHUTTING_DOWN
#define STATUS_DS_SHUTTING_DOWN          ((NTSTATUS)0x40000370L)
#endif//STATUS_DS_SHUTTING_DOWN

//
// MessageId: STATUS_NO_SECRETS
//
// MessageText:
//
// The local account store does not contain secret material for the specified account.
//
#ifndef STATUS_NO_SECRETS
#define STATUS_NO_SECRETS                ((NTSTATUS)0xC0000371L)
#endif//STATUS_NO_SECRETS

//
// MessageId: STATUS_ACCESS_DISABLED_NO_SAFER_UI_BY_POLICY
//
// MessageText:
//
// Access to %1 has been restricted by your Administrator by policy rule %2.
//
#ifndef STATUS_ACCESS_DISABLED_NO_SAFER_UI_BY_POLICY
#define STATUS_ACCESS_DISABLED_NO_SAFER_UI_BY_POLICY ((NTSTATUS)0xC0000372L)
#endif//STATUS_ACCESS_DISABLED_NO_SAFER_UI_BY_POLICY

//
// MessageId: STATUS_FAILED_STACK_SWITCH
//
// MessageText:
//
// The system was not able to allocate enough memory to perform a stack switch.
//
#ifndef STATUS_FAILED_STACK_SWITCH
#define STATUS_FAILED_STACK_SWITCH       ((NTSTATUS)0xC0000373L)
#endif//STATUS_FAILED_STACK_SWITCH

//
// MessageId: STATUS_HEAP_CORRUPTION
//
// MessageText:
//
// A heap has been corrupted.
//
#ifndef STATUS_HEAP_CORRUPTION
#define STATUS_HEAP_CORRUPTION           ((NTSTATUS)0xC0000374L)    // winnt
#endif//STATUS_HEAP_CORRUPTION

//
// MessageId: STATUS_SMARTCARD_WRONG_PIN
//
// MessageText:
//
// An incorrect PIN was presented to the smart card
//
#ifndef STATUS_SMARTCARD_WRONG_PIN
#define STATUS_SMARTCARD_WRONG_PIN       ((NTSTATUS)0xC0000380L)
#endif//STATUS_SMARTCARD_WRONG_PIN

//
// MessageId: STATUS_SMARTCARD_CARD_BLOCKED
//
// MessageText:
//
// The smart card is blocked
//
#ifndef STATUS_SMARTCARD_CARD_BLOCKED
#define STATUS_SMARTCARD_CARD_BLOCKED    ((NTSTATUS)0xC0000381L)
#endif//STATUS_SMARTCARD_CARD_BLOCKED

//
// MessageId: STATUS_SMARTCARD_CARD_NOT_AUTHENTICATED
//
// MessageText:
//
// No PIN was presented to the smart card
//
#ifndef STATUS_SMARTCARD_CARD_NOT_AUTHENTICATED
#define STATUS_SMARTCARD_CARD_NOT_AUTHENTICATED ((NTSTATUS)0xC0000382L)
#endif//STATUS_SMARTCARD_CARD_NOT_AUTHENTICATED

//
// MessageId: STATUS_SMARTCARD_NO_CARD
//
// MessageText:
//
// No smart card available
//
#ifndef STATUS_SMARTCARD_NO_CARD
#define STATUS_SMARTCARD_NO_CARD         ((NTSTATUS)0xC0000383L)
#endif//STATUS_SMARTCARD_NO_CARD

//
// MessageId: STATUS_SMARTCARD_NO_KEY_CONTAINER
//
// MessageText:
//
// The requested key container does not exist on the smart card
//
#ifndef STATUS_SMARTCARD_NO_KEY_CONTAINER
#define STATUS_SMARTCARD_NO_KEY_CONTAINER ((NTSTATUS)0xC0000384L)
#endif//STATUS_SMARTCARD_NO_KEY_CONTAINER

//
// MessageId: STATUS_SMARTCARD_NO_CERTIFICATE
//
// MessageText:
//
// The requested certificate does not exist on the smart card
//
#ifndef STATUS_SMARTCARD_NO_CERTIFICATE
#define STATUS_SMARTCARD_NO_CERTIFICATE  ((NTSTATUS)0xC0000385L)
#endif//STATUS_SMARTCARD_NO_CERTIFICATE

//
// MessageId: STATUS_SMARTCARD_NO_KEYSET
//
// MessageText:
//
// The requested keyset does not exist
//
#ifndef STATUS_SMARTCARD_NO_KEYSET
#define STATUS_SMARTCARD_NO_KEYSET       ((NTSTATUS)0xC0000386L)
#endif//STATUS_SMARTCARD_NO_KEYSET

//
// MessageId: STATUS_SMARTCARD_IO_ERROR
//
// MessageText:
//
// A communication error with the smart card has been detected.
//
#ifndef STATUS_SMARTCARD_IO_ERROR
#define STATUS_SMARTCARD_IO_ERROR        ((NTSTATUS)0xC0000387L)
#endif//STATUS_SMARTCARD_IO_ERROR

//
// MessageId: STATUS_DOWNGRADE_DETECTED
//
// MessageText:
//
// The system cannot contact a domain controller to service the authentication request. Please try again later.
//
#ifndef STATUS_DOWNGRADE_DETECTED
#define STATUS_DOWNGRADE_DETECTED        ((NTSTATUS)0xC0000388L)
#endif//STATUS_DOWNGRADE_DETECTED

//
// MessageId: STATUS_SMARTCARD_CERT_REVOKED
//
// MessageText:
//
// The smartcard certificate used for authentication has been revoked. Please contact your system administrator. There may be additional information in the event log.
//
#ifndef STATUS_SMARTCARD_CERT_REVOKED
#define STATUS_SMARTCARD_CERT_REVOKED    ((NTSTATUS)0xC0000389L)
#endif//STATUS_SMARTCARD_CERT_REVOKED

//
// MessageId: STATUS_ISSUING_CA_UNTRUSTED
//
// MessageText:
//
// An untrusted certificate authority was detected while processing the certificate used for authentication.
//
#ifndef STATUS_ISSUING_CA_UNTRUSTED
#define STATUS_ISSUING_CA_UNTRUSTED      ((NTSTATUS)0xC000038AL)
#endif//STATUS_ISSUING_CA_UNTRUSTED

//
// MessageId: STATUS_REVOCATION_OFFLINE_C
//
// MessageText:
//
// The revocation status of the certificate used for authentication could not be determined.
//
#ifndef STATUS_REVOCATION_OFFLINE_C
#define STATUS_REVOCATION_OFFLINE_C      ((NTSTATUS)0xC000038BL)
#endif//STATUS_REVOCATION_OFFLINE_C

//
// MessageId: STATUS_PKINIT_CLIENT_FAILURE
//
// MessageText:
//
// The client certificate used for authentication was not trusted.
//
#ifndef STATUS_PKINIT_CLIENT_FAILURE
#define STATUS_PKINIT_CLIENT_FAILURE     ((NTSTATUS)0xC000038CL)
#endif//STATUS_PKINIT_CLIENT_FAILURE

//
// MessageId: STATUS_SMARTCARD_CERT_EXPIRED
//
// MessageText:
//
// The smartcard certificate used for authentication has expired. Please
// contact your system administrator.
//
#ifndef STATUS_SMARTCARD_CERT_EXPIRED
#define STATUS_SMARTCARD_CERT_EXPIRED    ((NTSTATUS)0xC000038DL)
#endif//STATUS_SMARTCARD_CERT_EXPIRED

//
// MessageId: STATUS_DRIVER_FAILED_PRIOR_UNLOAD
//
// MessageText:
//
// The driver could not be loaded because a previous version of the driver is still in memory.
//
#ifndef STATUS_DRIVER_FAILED_PRIOR_UNLOAD
#define STATUS_DRIVER_FAILED_PRIOR_UNLOAD ((NTSTATUS)0xC000038EL)
#endif//STATUS_DRIVER_FAILED_PRIOR_UNLOAD

//
// MessageId: STATUS_SMARTCARD_SILENT_CONTEXT
//
// MessageText:
//
// The smartcard provider could not perform the action since the context was acquired as silent.
//
#ifndef STATUS_SMARTCARD_SILENT_CONTEXT
#define STATUS_SMARTCARD_SILENT_CONTEXT  ((NTSTATUS)0xC000038FL)
#endif//STATUS_SMARTCARD_SILENT_CONTEXT

 /* MessageId up to 0x400 is reserved for smart cards */
//
// MessageId: STATUS_PER_USER_TRUST_QUOTA_EXCEEDED
//
// MessageText:
//
// The current user's delegated trust creation quota has been exceeded.
//
#ifndef STATUS_PER_USER_TRUST_QUOTA_EXCEEDED
#define STATUS_PER_USER_TRUST_QUOTA_EXCEEDED ((NTSTATUS)0xC0000401L)
#endif//STATUS_PER_USER_TRUST_QUOTA_EXCEEDED

//
// MessageId: STATUS_ALL_USER_TRUST_QUOTA_EXCEEDED
//
// MessageText:
//
// The total delegated trust creation quota has been exceeded.
//
#ifndef STATUS_ALL_USER_TRUST_QUOTA_EXCEEDED
#define STATUS_ALL_USER_TRUST_QUOTA_EXCEEDED ((NTSTATUS)0xC0000402L)
#endif//STATUS_ALL_USER_TRUST_QUOTA_EXCEEDED

//
// MessageId: STATUS_USER_DELETE_TRUST_QUOTA_EXCEEDED
//
// MessageText:
//
// The current user's delegated trust deletion quota has been exceeded.
//
#ifndef STATUS_USER_DELETE_TRUST_QUOTA_EXCEEDED
#define STATUS_USER_DELETE_TRUST_QUOTA_EXCEEDED ((NTSTATUS)0xC0000403L)
#endif//STATUS_USER_DELETE_TRUST_QUOTA_EXCEEDED

//
// MessageId: STATUS_DS_NAME_NOT_UNIQUE
//
// MessageText:
//
// The requested name already exists as a unique identifier.
//
#ifndef STATUS_DS_NAME_NOT_UNIQUE
#define STATUS_DS_NAME_NOT_UNIQUE        ((NTSTATUS)0xC0000404L)
#endif//STATUS_DS_NAME_NOT_UNIQUE

//
// MessageId: STATUS_DS_DUPLICATE_ID_FOUND
//
// MessageText:
//
// The requested object has a non-unique identifier and cannot be retrieved.
//
#ifndef STATUS_DS_DUPLICATE_ID_FOUND
#define STATUS_DS_DUPLICATE_ID_FOUND     ((NTSTATUS)0xC0000405L)
#endif//STATUS_DS_DUPLICATE_ID_FOUND

//
// MessageId: STATUS_DS_GROUP_CONVERSION_ERROR
//
// MessageText:
//
// The group cannot be converted due to attribute restrictions on the requested group type.
//
#ifndef STATUS_DS_GROUP_CONVERSION_ERROR
#define STATUS_DS_GROUP_CONVERSION_ERROR ((NTSTATUS)0xC0000406L)
#endif//STATUS_DS_GROUP_CONVERSION_ERROR

//
// MessageId: STATUS_VOLSNAP_PREPARE_HIBERNATE
//
// MessageText:
//
// {Volume Shadow Copy Service}
// Please wait while the Volume Shadow Copy Service prepares volume %hs for hibernation.
//
#ifndef STATUS_VOLSNAP_PREPARE_HIBERNATE
#define STATUS_VOLSNAP_PREPARE_HIBERNATE ((NTSTATUS)0xC0000407L)
#endif//STATUS_VOLSNAP_PREPARE_HIBERNATE

//
// MessageId: STATUS_USER2USER_REQUIRED
//
// MessageText:
//
// Kerberos sub-protocol User2User is required.
//
#ifndef STATUS_USER2USER_REQUIRED
#define STATUS_USER2USER_REQUIRED        ((NTSTATUS)0xC0000408L)
#endif//STATUS_USER2USER_REQUIRED

//
// MessageId: STATUS_STACK_BUFFER_OVERRUN
//
// MessageText:
//
// The system detected an overrun of a stack-based buffer in this application. This overrun could potentially allow a malicious user to gain control of this application.
//
#ifndef STATUS_STACK_BUFFER_OVERRUN
#define STATUS_STACK_BUFFER_OVERRUN      ((NTSTATUS)0xC0000409L)    // winnt
#endif//STATUS_STACK_BUFFER_OVERRUN

//
// MessageId: STATUS_NO_S4U_PROT_SUPPORT
//
// MessageText:
//
// The Kerberos subsystem encountered an error. A service for user protocol request was made against a domain controller which does not support service for user.
//
#ifndef STATUS_NO_S4U_PROT_SUPPORT
#define STATUS_NO_S4U_PROT_SUPPORT       ((NTSTATUS)0xC000040AL)
#endif//STATUS_NO_S4U_PROT_SUPPORT

//
// MessageId: STATUS_CROSSREALM_DELEGATION_FAILURE
//
// MessageText:
//
// An attempt was made by this server to make a Kerberos constrained delegation request for a target outside of the server's realm. This is not supported, and indicates a misconfiguration on this server's allowed to delegate to list. Please contact your administrator.
//
#ifndef STATUS_CROSSREALM_DELEGATION_FAILURE
#define STATUS_CROSSREALM_DELEGATION_FAILURE ((NTSTATUS)0xC000040BL)
#endif//STATUS_CROSSREALM_DELEGATION_FAILURE

//
// MessageId: STATUS_REVOCATION_OFFLINE_KDC
//
// MessageText:
//
// The revocation status of the domain controller certificate used for authentication could not be determined. There is additional information in the system event log.
//
#ifndef STATUS_REVOCATION_OFFLINE_KDC
#define STATUS_REVOCATION_OFFLINE_KDC    ((NTSTATUS)0xC000040CL)
#endif//STATUS_REVOCATION_OFFLINE_KDC

//
// MessageId: STATUS_ISSUING_CA_UNTRUSTED_KDC
//
// MessageText:
//
// An untrusted certificate authority was detected while processing the domain controller certificate used for authentication. There is additional information in the system event log. Please contact your system administrator.
//
#ifndef STATUS_ISSUING_CA_UNTRUSTED_KDC
#define STATUS_ISSUING_CA_UNTRUSTED_KDC  ((NTSTATUS)0xC000040DL)
#endif//STATUS_ISSUING_CA_UNTRUSTED_KDC

//
// MessageId: STATUS_KDC_CERT_EXPIRED
//
// MessageText:
//
// The domain controller certificate used for logon has expired. There is additional information in the system event log.
//
#ifndef STATUS_KDC_CERT_EXPIRED
#define STATUS_KDC_CERT_EXPIRED          ((NTSTATUS)0xC000040EL)
#endif//STATUS_KDC_CERT_EXPIRED

//
// MessageId: STATUS_KDC_CERT_REVOKED
//
// MessageText:
//
// The domain controller certificate used for logon has been revoked. There is additional information in the system event log.
//
#ifndef STATUS_KDC_CERT_REVOKED
#define STATUS_KDC_CERT_REVOKED          ((NTSTATUS)0xC000040FL)
#endif//STATUS_KDC_CERT_REVOKED

//
// MessageId: STATUS_PARAMETER_QUOTA_EXCEEDED
//
// MessageText:
//
// Data present in one of the parameters is more than the function can operate on.
//
#ifndef STATUS_PARAMETER_QUOTA_EXCEEDED
#define STATUS_PARAMETER_QUOTA_EXCEEDED  ((NTSTATUS)0xC0000410L)
#endif//STATUS_PARAMETER_QUOTA_EXCEEDED

//
// MessageId: STATUS_HIBERNATION_FAILURE
//
// MessageText:
//
// The system has failed to hibernate (The error code is %hs). Hibernation will be disabled until the system is restarted.
//
#ifndef STATUS_HIBERNATION_FAILURE
#define STATUS_HIBERNATION_FAILURE       ((NTSTATUS)0xC0000411L)
#endif//STATUS_HIBERNATION_FAILURE

//
// MessageId: STATUS_DELAY_LOAD_FAILED
//
// MessageText:
//
// An attempt to delay-load a .dll or get a function address in a delay-loaded .dll failed.
//
#ifndef STATUS_DELAY_LOAD_FAILED
#define STATUS_DELAY_LOAD_FAILED         ((NTSTATUS)0xC0000412L)
#endif//STATUS_DELAY_LOAD_FAILED

//
// MessageId: STATUS_AUTHENTICATION_FIREWALL_FAILED
//
// MessageText:
//
// Logon Failure: The machine you are logging onto is protected by an authentication firewall. The specified account is not allowed to authenticate to the machine.
//
#ifndef STATUS_AUTHENTICATION_FIREWALL_FAILED
#define STATUS_AUTHENTICATION_FIREWALL_FAILED ((NTSTATUS)0xC0000413L)
#endif//STATUS_AUTHENTICATION_FIREWALL_FAILED

//
// MessageId: STATUS_VDM_DISALLOWED
//
// MessageText:
//
// %hs is a 16-bit application. You do not have permissions to execute 16-bit applications. Check your permissions with your system administrator.
//
#ifndef STATUS_VDM_DISALLOWED
#define STATUS_VDM_DISALLOWED            ((NTSTATUS)0xC0000414L)
#endif//STATUS_VDM_DISALLOWED

//
// MessageId: STATUS_HUNG_DISPLAY_DRIVER_THREAD
//
// MessageText:
//
// {Display Driver Stopped Responding}
// The %hs display driver has stopped working normally. Save your work and reboot the system to restore full display functionality. The next time you reboot the machine a dialog will be displayed giving you a chance to report this failure to Microsoft.
//
#ifndef STATUS_HUNG_DISPLAY_DRIVER_THREAD
#define STATUS_HUNG_DISPLAY_DRIVER_THREAD ((NTSTATUS)0xC0000415L)
#endif//STATUS_HUNG_DISPLAY_DRIVER_THREAD

//
// MessageId: STATUS_INSUFFICIENT_RESOURCE_FOR_SPECIFIED_SHARED_SECTION_SIZE
//
// MessageText:
//
// The Desktop heap encountered an error while allocating session memory. There is more information in the system event log.
//
#ifndef STATUS_INSUFFICIENT_RESOURCE_FOR_SPECIFIED_SHARED_SECTION_SIZE
#define STATUS_INSUFFICIENT_RESOURCE_FOR_SPECIFIED_SHARED_SECTION_SIZE ((NTSTATUS)0xC0000416L)
#endif//STATUS_INSUFFICIENT_RESOURCE_FOR_SPECIFIED_SHARED_SECTION_SIZE

//
// MessageId: STATUS_INVALID_CRUNTIME_PARAMETER
//
// MessageText:
//
// An invalid parameter was passed to a C runtime function.
//
#ifndef STATUS_INVALID_CRUNTIME_PARAMETER
#define STATUS_INVALID_CRUNTIME_PARAMETER ((NTSTATUS)0xC0000417L)    // winnt
#endif//STATUS_INVALID_CRUNTIME_PARAMETER

//
// MessageId: STATUS_NTLM_BLOCKED
//
// MessageText:
//
// The authentication failed since NTLM was blocked.
//
#ifndef STATUS_NTLM_BLOCKED
#define STATUS_NTLM_BLOCKED              ((NTSTATUS)0xC0000418L)
#endif//STATUS_NTLM_BLOCKED

//
// MessageId: STATUS_DS_SRC_SID_EXISTS_IN_FOREST
//
// MessageText:
//
// The source object's SID already exists in destination forest.
//
#ifndef STATUS_DS_SRC_SID_EXISTS_IN_FOREST
#define STATUS_DS_SRC_SID_EXISTS_IN_FOREST ((NTSTATUS)0xC0000419L)
#endif//STATUS_DS_SRC_SID_EXISTS_IN_FOREST

//
// MessageId: STATUS_DS_DOMAIN_NAME_EXISTS_IN_FOREST
//
// MessageText:
//
// The domain name of the trusted domain already exists in the forest.
//
#ifndef STATUS_DS_DOMAIN_NAME_EXISTS_IN_FOREST
#define STATUS_DS_DOMAIN_NAME_EXISTS_IN_FOREST ((NTSTATUS)0xC000041AL)
#endif//STATUS_DS_DOMAIN_NAME_EXISTS_IN_FOREST

//
// MessageId: STATUS_DS_FLAT_NAME_EXISTS_IN_FOREST
//
// MessageText:
//
// The flat name of the trusted domain already exists in the forest.
//
#ifndef STATUS_DS_FLAT_NAME_EXISTS_IN_FOREST
#define STATUS_DS_FLAT_NAME_EXISTS_IN_FOREST ((NTSTATUS)0xC000041BL)
#endif//STATUS_DS_FLAT_NAME_EXISTS_IN_FOREST

//
// MessageId: STATUS_INVALID_USER_PRINCIPAL_NAME
//
// MessageText:
//
// The User Principal Name (UPN) is invalid.
//
#ifndef STATUS_INVALID_USER_PRINCIPAL_NAME
#define STATUS_INVALID_USER_PRINCIPAL_NAME ((NTSTATUS)0xC000041CL)
#endif//STATUS_INVALID_USER_PRINCIPAL_NAME

//
// MessageId: STATUS_FATAL_USER_CALLBACK_EXCEPTION
//
// MessageText:
//
// An unhandled exception was encountered during a user callback.
//
#ifndef STATUS_FATAL_USER_CALLBACK_EXCEPTION
#define STATUS_FATAL_USER_CALLBACK_EXCEPTION ((NTSTATUS)0xC000041DL)
#endif//STATUS_FATAL_USER_CALLBACK_EXCEPTION

//
// MessageId: STATUS_ASSERTION_FAILURE
//
// MessageText:
//
// An assertion failure has occurred.
//
#ifndef STATUS_ASSERTION_FAILURE
#define STATUS_ASSERTION_FAILURE         ((NTSTATUS)0xC0000420L)    // winnt
#endif//STATUS_ASSERTION_FAILURE

//
// MessageId: STATUS_VERIFIER_STOP
//
// MessageText:
//
// Application verifier has found an error in the current process.
//
#ifndef STATUS_VERIFIER_STOP
#define STATUS_VERIFIER_STOP             ((NTSTATUS)0xC0000421L)
#endif//STATUS_VERIFIER_STOP

//
// MessageId: STATUS_CALLBACK_POP_STACK
//
// MessageText:
//
// An exception has occurred in a user mode callback and the kernel callback frame should be removed.
//
#ifndef STATUS_CALLBACK_POP_STACK
#define STATUS_CALLBACK_POP_STACK        ((NTSTATUS)0xC0000423L)
#endif//STATUS_CALLBACK_POP_STACK

//
// MessageId: STATUS_INCOMPATIBLE_DRIVER_BLOCKED
//
// MessageText:
//
// %2 has been blocked from loading due to incompatibility with this system. Please contact your software vendor for a compatible version of the driver.
//
#ifndef STATUS_INCOMPATIBLE_DRIVER_BLOCKED
#define STATUS_INCOMPATIBLE_DRIVER_BLOCKED ((NTSTATUS)0xC0000424L)
#endif//STATUS_INCOMPATIBLE_DRIVER_BLOCKED

//
// MessageId: STATUS_HIVE_UNLOADED
//
// MessageText:
//
// Illegal operation attempted on a registry key which has already been unloaded.
//
#ifndef STATUS_HIVE_UNLOADED
#define STATUS_HIVE_UNLOADED             ((NTSTATUS)0xC0000425L)
#endif//STATUS_HIVE_UNLOADED

//
// MessageId: STATUS_COMPRESSION_DISABLED
//
// MessageText:
//
// Compression is disabled for this volume.
//
#ifndef STATUS_COMPRESSION_DISABLED
#define STATUS_COMPRESSION_DISABLED      ((NTSTATUS)0xC0000426L)
#endif//STATUS_COMPRESSION_DISABLED

//
// MessageId: STATUS_FILE_SYSTEM_LIMITATION
//
// MessageText:
//
// The requested operation could not be completed due to a file system limitation
//
#ifndef STATUS_FILE_SYSTEM_LIMITATION
#define STATUS_FILE_SYSTEM_LIMITATION    ((NTSTATUS)0xC0000427L)
#endif//STATUS_FILE_SYSTEM_LIMITATION

//
// MessageId: STATUS_INVALID_IMAGE_HASH
//
// MessageText:
//
// Windows cannot verify the digital signature for this file. A recent hardware or software change might have installed a file that is signed incorrectly or damaged, or that might be malicious software from an unknown source.
//
#ifndef STATUS_INVALID_IMAGE_HASH
#define STATUS_INVALID_IMAGE_HASH        ((NTSTATUS)0xC0000428L)
#endif//STATUS_INVALID_IMAGE_HASH

//
// MessageId: STATUS_NOT_CAPABLE
//
// MessageText:
//
// The implementation is not capable of performing the request.
//
#ifndef STATUS_NOT_CAPABLE
#define STATUS_NOT_CAPABLE               ((NTSTATUS)0xC0000429L)
#endif//STATUS_NOT_CAPABLE

//
// MessageId: STATUS_REQUEST_OUT_OF_SEQUENCE
//
// MessageText:
//
// The requested operation is out of order with respect to other operations.
//
#ifndef STATUS_REQUEST_OUT_OF_SEQUENCE
#define STATUS_REQUEST_OUT_OF_SEQUENCE   ((NTSTATUS)0xC000042AL)
#endif//STATUS_REQUEST_OUT_OF_SEQUENCE

//
// MessageId: STATUS_IMPLEMENTATION_LIMIT
//
// MessageText:
//
// An operation attempted to exceed an implementation-defined limit.
//
#ifndef STATUS_IMPLEMENTATION_LIMIT
#define STATUS_IMPLEMENTATION_LIMIT      ((NTSTATUS)0xC000042BL)
#endif//STATUS_IMPLEMENTATION_LIMIT

//
// MessageId: STATUS_ELEVATION_REQUIRED
//
// MessageText:
//
// The requested operation requires elevation.
//
#ifndef STATUS_ELEVATION_REQUIRED
#define STATUS_ELEVATION_REQUIRED        ((NTSTATUS)0xC000042CL)
#endif//STATUS_ELEVATION_REQUIRED

//
// MessageId: STATUS_NO_SECURITY_CONTEXT
//
// MessageText:
//
// The required security context does not exist.
//
#ifndef STATUS_NO_SECURITY_CONTEXT
#define STATUS_NO_SECURITY_CONTEXT       ((NTSTATUS)0xC000042DL)
#endif//STATUS_NO_SECURITY_CONTEXT

//
// MessageId 0x042E is reserved and used in isolation lib as
//
// MessageId=0x042E Facility=System Severity=ERROR SymbolicName=STATUS_VERSION_PARSE_ERROR
// Language=English
// A version number could not be parsed.
// .
//
// MessageId: STATUS_PKU2U_CERT_FAILURE
//
// MessageText:
//
// The PKU2U protocol encountered an error while attempting to utilize the associated certificates.
//
#ifndef STATUS_PKU2U_CERT_FAILURE
#define STATUS_PKU2U_CERT_FAILURE        ((NTSTATUS)0xC000042FL)
#endif//STATUS_PKU2U_CERT_FAILURE

//
// MessageId: STATUS_BEYOND_VDL
//
// MessageText:
//
// The operation was attempted beyond the valid data length of the file.
//
#ifndef STATUS_BEYOND_VDL
#define STATUS_BEYOND_VDL                ((NTSTATUS)0xC0000432L)
#endif//STATUS_BEYOND_VDL

//
// MessageId: STATUS_ENCOUNTERED_WRITE_IN_PROGRESS
//
// MessageText:
//
// The attempted write operation encountered a write already in progress for some portion of the range.
//
#ifndef STATUS_ENCOUNTERED_WRITE_IN_PROGRESS
#define STATUS_ENCOUNTERED_WRITE_IN_PROGRESS ((NTSTATUS)0xC0000433L)
#endif//STATUS_ENCOUNTERED_WRITE_IN_PROGRESS

//
// MessageId: STATUS_PTE_CHANGED
//
// MessageText:
//
// The page fault mappings changed in the middle of processing a fault so the operation must be retried.
//
#ifndef STATUS_PTE_CHANGED
#define STATUS_PTE_CHANGED               ((NTSTATUS)0xC0000434L)
#endif//STATUS_PTE_CHANGED

//
// MessageId: STATUS_PURGE_FAILED
//
// MessageText:
//
// The attempt to purge this file from memory failed to purge some or all the data from memory.
//
#ifndef STATUS_PURGE_FAILED
#define STATUS_PURGE_FAILED              ((NTSTATUS)0xC0000435L)
#endif//STATUS_PURGE_FAILED

//
// MessageId: STATUS_CRED_REQUIRES_CONFIRMATION
//
// MessageText:
//
// The requested credential requires confirmation.
//
#ifndef STATUS_CRED_REQUIRES_CONFIRMATION
#define STATUS_CRED_REQUIRES_CONFIRMATION ((NTSTATUS)0xC0000440L)
#endif//STATUS_CRED_REQUIRES_CONFIRMATION

//
// MessageId: STATUS_CS_ENCRYPTION_INVALID_SERVER_RESPONSE
//
// MessageText:
//
// The remote server sent an invalid response for a file being opened with Client Side Encryption.
//
#ifndef STATUS_CS_ENCRYPTION_INVALID_SERVER_RESPONSE
#define STATUS_CS_ENCRYPTION_INVALID_SERVER_RESPONSE ((NTSTATUS)0xC0000441L)
#endif//STATUS_CS_ENCRYPTION_INVALID_SERVER_RESPONSE

//
// MessageId: STATUS_CS_ENCRYPTION_UNSUPPORTED_SERVER
//
// MessageText:
//
// Client Side Encryption is not supported by the remote server even though it claims to support it.
//
#ifndef STATUS_CS_ENCRYPTION_UNSUPPORTED_SERVER
#define STATUS_CS_ENCRYPTION_UNSUPPORTED_SERVER ((NTSTATUS)0xC0000442L)
#endif//STATUS_CS_ENCRYPTION_UNSUPPORTED_SERVER

//
// MessageId: STATUS_CS_ENCRYPTION_EXISTING_ENCRYPTED_FILE
//
// MessageText:
//
// File is encrypted and should be opened in Client Side Encryption mode.
//
#ifndef STATUS_CS_ENCRYPTION_EXISTING_ENCRYPTED_FILE
#define STATUS_CS_ENCRYPTION_EXISTING_ENCRYPTED_FILE ((NTSTATUS)0xC0000443L)
#endif//STATUS_CS_ENCRYPTION_EXISTING_ENCRYPTED_FILE

//
// MessageId: STATUS_CS_ENCRYPTION_NEW_ENCRYPTED_FILE
//
// MessageText:
//
// A new encrypted file is being created and a $EFS needs to be provided.
//
#ifndef STATUS_CS_ENCRYPTION_NEW_ENCRYPTED_FILE
#define STATUS_CS_ENCRYPTION_NEW_ENCRYPTED_FILE ((NTSTATUS)0xC0000444L)
#endif//STATUS_CS_ENCRYPTION_NEW_ENCRYPTED_FILE

//
// MessageId: STATUS_CS_ENCRYPTION_FILE_NOT_CSE
//
// MessageText:
//
// The SMB client requested a CSE FSCTL on a non-CSE file.
//
#ifndef STATUS_CS_ENCRYPTION_FILE_NOT_CSE
#define STATUS_CS_ENCRYPTION_FILE_NOT_CSE ((NTSTATUS)0xC0000445L)
#endif//STATUS_CS_ENCRYPTION_FILE_NOT_CSE

//
// MessageId: STATUS_INVALID_LABEL
//
// MessageText:
//
// Indicates a particular Security ID may not be assigned as the label of an object.
//
#ifndef STATUS_INVALID_LABEL
#define STATUS_INVALID_LABEL             ((NTSTATUS)0xC0000446L)
#endif//STATUS_INVALID_LABEL

//
// MessageId: STATUS_DRIVER_PROCESS_TERMINATED
//
// MessageText:
//
// The process hosting the driver for this device has terminated.
//
#ifndef STATUS_DRIVER_PROCESS_TERMINATED
#define STATUS_DRIVER_PROCESS_TERMINATED ((NTSTATUS)0xC0000450L)
#endif//STATUS_DRIVER_PROCESS_TERMINATED

//
// MessageId: STATUS_AMBIGUOUS_SYSTEM_DEVICE
//
// MessageText:
//
// The requested system device cannot be identified due to multiple indistinguishable devices potentially matching the identification criteria.
//
#ifndef STATUS_AMBIGUOUS_SYSTEM_DEVICE
#define STATUS_AMBIGUOUS_SYSTEM_DEVICE   ((NTSTATUS)0xC0000451L)
#endif//STATUS_AMBIGUOUS_SYSTEM_DEVICE

//
// MessageId: STATUS_SYSTEM_DEVICE_NOT_FOUND
//
// MessageText:
//
// The requested system device cannot be found.
//
#ifndef STATUS_SYSTEM_DEVICE_NOT_FOUND
#define STATUS_SYSTEM_DEVICE_NOT_FOUND   ((NTSTATUS)0xC0000452L)
#endif//STATUS_SYSTEM_DEVICE_NOT_FOUND

//
// MessageId: STATUS_RESTART_BOOT_APPLICATION
//
// MessageText:
//
// This boot application must be restarted.
//
#ifndef STATUS_RESTART_BOOT_APPLICATION
#define STATUS_RESTART_BOOT_APPLICATION  ((NTSTATUS)0xC0000453L)
#endif//STATUS_RESTART_BOOT_APPLICATION

//
// MessageId: STATUS_INSUFFICIENT_NVRAM_RESOURCES
//
// MessageText:
//
// Insufficient NVRAM resources exist to complete the API.  A reboot might be required.
//
#ifndef STATUS_INSUFFICIENT_NVRAM_RESOURCES
#define STATUS_INSUFFICIENT_NVRAM_RESOURCES ((NTSTATUS)0xC0000454L)
#endif//STATUS_INSUFFICIENT_NVRAM_RESOURCES

//
// MessageId: STATUS_INVALID_SESSION
//
// MessageText:
//
// The specified session is invalid.
//
#ifndef STATUS_INVALID_SESSION
#define STATUS_INVALID_SESSION           ((NTSTATUS)0xC0000455L)
#endif//STATUS_INVALID_SESSION

//
// MessageId: STATUS_THREAD_ALREADY_IN_SESSION
//
// MessageText:
//
// The specified thread is already in a session.
//
#ifndef STATUS_THREAD_ALREADY_IN_SESSION
#define STATUS_THREAD_ALREADY_IN_SESSION ((NTSTATUS)0xC0000456L)
#endif//STATUS_THREAD_ALREADY_IN_SESSION

//
// MessageId: STATUS_THREAD_NOT_IN_SESSION
//
// MessageText:
//
// The specified thread is not in a session.
//
#ifndef STATUS_THREAD_NOT_IN_SESSION
#define STATUS_THREAD_NOT_IN_SESSION     ((NTSTATUS)0xC0000457L)
#endif//STATUS_THREAD_NOT_IN_SESSION

//
// MessageId: STATUS_INVALID_WEIGHT
//
// MessageText:
//
// The specified weight is invalid.
//
#ifndef STATUS_INVALID_WEIGHT
#define STATUS_INVALID_WEIGHT            ((NTSTATUS)0xC0000458L)
#endif//STATUS_INVALID_WEIGHT

//
// MessageId: STATUS_REQUEST_PAUSED
//
// MessageText:
//
// The operation was paused.
//
#ifndef STATUS_REQUEST_PAUSED
#define STATUS_REQUEST_PAUSED            ((NTSTATUS)0xC0000459L)
#endif//STATUS_REQUEST_PAUSED

//
// MessageId: STATUS_NO_RANGES_PROCESSED
//
// MessageText:
//
// No ranges for the specified operation were able to be processed.
//
#ifndef STATUS_NO_RANGES_PROCESSED
#define STATUS_NO_RANGES_PROCESSED       ((NTSTATUS)0xC0000460L)
#endif//STATUS_NO_RANGES_PROCESSED

//
// MessageId: STATUS_DISK_RESOURCES_EXHAUSTED
//
// MessageText:
//
// The physical resources of this disk have been exhausted.
//
#ifndef STATUS_DISK_RESOURCES_EXHAUSTED
#define STATUS_DISK_RESOURCES_EXHAUSTED  ((NTSTATUS)0xC0000461L)
#endif//STATUS_DISK_RESOURCES_EXHAUSTED

//
// MessageId: STATUS_NEEDS_REMEDIATION
//
// MessageText:
//
// The application cannot be started. Try reinstalling the application to fix the problem.
//
#ifndef STATUS_NEEDS_REMEDIATION
#define STATUS_NEEDS_REMEDIATION         ((NTSTATUS)0xC0000462L)
#endif//STATUS_NEEDS_REMEDIATION

//
// MessageId: STATUS_DEVICE_FEATURE_NOT_SUPPORTED
//
// MessageText:
//
// {Device Feature Not Supported}
// The device does not support the command feature.
//
#ifndef STATUS_DEVICE_FEATURE_NOT_SUPPORTED
#define STATUS_DEVICE_FEATURE_NOT_SUPPORTED ((NTSTATUS)0xC0000463L)
#endif//STATUS_DEVICE_FEATURE_NOT_SUPPORTED

//
// MessageId: STATUS_DEVICE_UNREACHABLE
//
// MessageText:
//
// {Source/Destination device unreachable}
// The device is unreachable.
//
#ifndef STATUS_DEVICE_UNREACHABLE
#define STATUS_DEVICE_UNREACHABLE        ((NTSTATUS)0xC0000464L)
#endif//STATUS_DEVICE_UNREACHABLE

//
// MessageId: STATUS_INVALID_TOKEN
//
// MessageText:
//
// {Invalid Proxy Data Token}
// The token representing the data is invalid.
//
#ifndef STATUS_INVALID_TOKEN
#define STATUS_INVALID_TOKEN             ((NTSTATUS)0xC0000465L)
#endif//STATUS_INVALID_TOKEN

//
// MessageId: STATUS_SERVER_UNAVAILABLE
//
// MessageText:
//
// The file server is temporarily unavailable.
//
#ifndef STATUS_SERVER_UNAVAILABLE
#define STATUS_SERVER_UNAVAILABLE        ((NTSTATUS)0xC0000466L)
#endif//STATUS_SERVER_UNAVAILABLE

//
// MessageId: STATUS_FILE_NOT_AVAILABLE
//
// MessageText:
//
// The file is temporarily unavailable.
//
#ifndef STATUS_FILE_NOT_AVAILABLE
#define STATUS_FILE_NOT_AVAILABLE        ((NTSTATUS)0xC0000467L)
#endif//STATUS_FILE_NOT_AVAILABLE

//
// MessageId: STATUS_DEVICE_INSUFFICIENT_RESOURCES
//
// MessageText:
//
// {Device Insufficient Resources}
// The target device has insufficient resources to complete the operation.
//
#ifndef STATUS_DEVICE_INSUFFICIENT_RESOURCES
#define STATUS_DEVICE_INSUFFICIENT_RESOURCES ((NTSTATUS)0xC0000468L)
#endif//STATUS_DEVICE_INSUFFICIENT_RESOURCES

//
// MessageId: STATUS_PACKAGE_UPDATING
//
// MessageText:
//
// The application cannot be started because it is currently updating.
//
#ifndef STATUS_PACKAGE_UPDATING
#define STATUS_PACKAGE_UPDATING          ((NTSTATUS)0xC0000469L)
#endif//STATUS_PACKAGE_UPDATING

//
// MessageId: STATUS_NOT_READ_FROM_COPY
//
// MessageText:
//
// The specified copy of the requested data could not be read.
//
#ifndef STATUS_NOT_READ_FROM_COPY
#define STATUS_NOT_READ_FROM_COPY        ((NTSTATUS)0xC000046AL)
#endif//STATUS_NOT_READ_FROM_COPY

//
// MessageId: STATUS_FT_WRITE_FAILURE
//
// MessageText:
//
// The specified data could not be written to any of the copies.
//
#ifndef STATUS_FT_WRITE_FAILURE
#define STATUS_FT_WRITE_FAILURE          ((NTSTATUS)0xC000046BL)
#endif//STATUS_FT_WRITE_FAILURE

//
// MessageId: STATUS_FT_DI_SCAN_REQUIRED
//
// MessageText:
//
// One or more copies of data on this device may be out of sync. No writes may be performed until a data integrity scan is completed.
//
#ifndef STATUS_FT_DI_SCAN_REQUIRED
#define STATUS_FT_DI_SCAN_REQUIRED       ((NTSTATUS)0xC000046CL)
#endif//STATUS_FT_DI_SCAN_REQUIRED

//
// MessageId: STATUS_OBJECT_NOT_EXTERNALLY_BACKED
//
// MessageText:
//
// This object is not externally backed by any provider.
//
#ifndef STATUS_OBJECT_NOT_EXTERNALLY_BACKED
#define STATUS_OBJECT_NOT_EXTERNALLY_BACKED ((NTSTATUS)0xC000046DL)
#endif//STATUS_OBJECT_NOT_EXTERNALLY_BACKED

//
// MessageId: STATUS_EXTERNAL_BACKING_PROVIDER_UNKNOWN
//
// MessageText:
//
// The external backing provider is not recognized.
//
#ifndef STATUS_EXTERNAL_BACKING_PROVIDER_UNKNOWN
#define STATUS_EXTERNAL_BACKING_PROVIDER_UNKNOWN ((NTSTATUS)0xC000046EL)
#endif//STATUS_EXTERNAL_BACKING_PROVIDER_UNKNOWN

//
// MessageId: STATUS_COMPRESSION_NOT_BENEFICIAL
//
// MessageText:
//
// Compressing this object would not save space.
//
#ifndef STATUS_COMPRESSION_NOT_BENEFICIAL
#define STATUS_COMPRESSION_NOT_BENEFICIAL ((NTSTATUS)0xC000046FL)
#endif//STATUS_COMPRESSION_NOT_BENEFICIAL

//
// MessageId: STATUS_DATA_CHECKSUM_ERROR
//
// MessageText:
//
// A data integrity checksum error occurred. Data in the file stream is corrupt.
//
#ifndef STATUS_DATA_CHECKSUM_ERROR
#define STATUS_DATA_CHECKSUM_ERROR       ((NTSTATUS)0xC0000470L)
#endif//STATUS_DATA_CHECKSUM_ERROR

//
// MessageId: STATUS_INTERMIXED_KERNEL_EA_OPERATION
//
// MessageText:
//
// An attempt was made to modify both a KERNEL and normal Extended Attribute (EA) in the same operation.
//
#ifndef STATUS_INTERMIXED_KERNEL_EA_OPERATION
#define STATUS_INTERMIXED_KERNEL_EA_OPERATION ((NTSTATUS)0xC0000471L)
#endif//STATUS_INTERMIXED_KERNEL_EA_OPERATION

//
// MessageId: STATUS_TRIM_READ_ZERO_NOT_SUPPORTED
//
// MessageText:
//
// {LogicalBlockProvisioningReadZero Not Supported}
// The target device does not support read returning zeros from trimmed/unmapped blocks.
//
#ifndef STATUS_TRIM_READ_ZERO_NOT_SUPPORTED
#define STATUS_TRIM_READ_ZERO_NOT_SUPPORTED ((NTSTATUS)0xC0000472L)
#endif//STATUS_TRIM_READ_ZERO_NOT_SUPPORTED

//
// MessageId: STATUS_TOO_MANY_SEGMENT_DESCRIPTORS
//
// MessageText:
//
// {Maximum Segment Descriptors Exceeded}
// The command specified a number of descriptors that exceeded the maximum supported by the device.
//
#ifndef STATUS_TOO_MANY_SEGMENT_DESCRIPTORS
#define STATUS_TOO_MANY_SEGMENT_DESCRIPTORS ((NTSTATUS)0xC0000473L)
#endif//STATUS_TOO_MANY_SEGMENT_DESCRIPTORS

//
// MessageId: STATUS_INVALID_OFFSET_ALIGNMENT
//
// MessageText:
//
// {Alignment Violation}
// The command specified a data offset that does not align to the device's granularity/alignment.
//
#ifndef STATUS_INVALID_OFFSET_ALIGNMENT
#define STATUS_INVALID_OFFSET_ALIGNMENT  ((NTSTATUS)0xC0000474L)
#endif//STATUS_INVALID_OFFSET_ALIGNMENT

//
// MessageId: STATUS_INVALID_FIELD_IN_PARAMETER_LIST
//
// MessageText:
//
// {Invalid Field In Parameter List}
// The command specified an invalid field in its parameter list.
//
#ifndef STATUS_INVALID_FIELD_IN_PARAMETER_LIST
#define STATUS_INVALID_FIELD_IN_PARAMETER_LIST ((NTSTATUS)0xC0000475L)
#endif//STATUS_INVALID_FIELD_IN_PARAMETER_LIST

//
// MessageId: STATUS_OPERATION_IN_PROGRESS
//
// MessageText:
//
// {Operation In Progress}
// An operation is currently in progress with the device.
//
#ifndef STATUS_OPERATION_IN_PROGRESS
#define STATUS_OPERATION_IN_PROGRESS     ((NTSTATUS)0xC0000476L)
#endif//STATUS_OPERATION_IN_PROGRESS

//
// MessageId: STATUS_INVALID_INITIATOR_TARGET_PATH
//
// MessageText:
//
// {Invalid I_T Nexus}
// An attempt was made to send down the command via an invalid path to the target device.
//
#ifndef STATUS_INVALID_INITIATOR_TARGET_PATH
#define STATUS_INVALID_INITIATOR_TARGET_PATH ((NTSTATUS)0xC0000477L)
#endif//STATUS_INVALID_INITIATOR_TARGET_PATH

//
// MessageId: STATUS_SCRUB_DATA_DISABLED
//
// MessageText:
//
// Scrub is disabled on the specified file.
//
#ifndef STATUS_SCRUB_DATA_DISABLED
#define STATUS_SCRUB_DATA_DISABLED       ((NTSTATUS)0xC0000478L)
#endif//STATUS_SCRUB_DATA_DISABLED

//
// MessageId: STATUS_NOT_REDUNDANT_STORAGE
//
// MessageText:
//
// The storage device does not provide redundancy.
//
#ifndef STATUS_NOT_REDUNDANT_STORAGE
#define STATUS_NOT_REDUNDANT_STORAGE     ((NTSTATUS)0xC0000479L)
#endif//STATUS_NOT_REDUNDANT_STORAGE

//
// MessageId: STATUS_RESIDENT_FILE_NOT_SUPPORTED
//
// MessageText:
//
// An operation is not supported on a resident file.
//
#ifndef STATUS_RESIDENT_FILE_NOT_SUPPORTED
#define STATUS_RESIDENT_FILE_NOT_SUPPORTED ((NTSTATUS)0xC000047AL)
#endif//STATUS_RESIDENT_FILE_NOT_SUPPORTED

//
// MessageId: STATUS_COMPRESSED_FILE_NOT_SUPPORTED
//
// MessageText:
//
// An operation is not supported on a compressed file.
//
#ifndef STATUS_COMPRESSED_FILE_NOT_SUPPORTED
#define STATUS_COMPRESSED_FILE_NOT_SUPPORTED ((NTSTATUS)0xC000047BL)
#endif//STATUS_COMPRESSED_FILE_NOT_SUPPORTED

//
// MessageId: STATUS_DIRECTORY_NOT_SUPPORTED
//
// MessageText:
//
// An operation is not supported on a directory.
//
#ifndef STATUS_DIRECTORY_NOT_SUPPORTED
#define STATUS_DIRECTORY_NOT_SUPPORTED   ((NTSTATUS)0xC000047CL)
#endif//STATUS_DIRECTORY_NOT_SUPPORTED

//
// MessageId: STATUS_IO_OPERATION_TIMEOUT
//
// MessageText:
//
// {IO Operation Timeout}
// The specified I/O operation failed to complete within the expected time period.
//
#ifndef STATUS_IO_OPERATION_TIMEOUT
#define STATUS_IO_OPERATION_TIMEOUT      ((NTSTATUS)0xC000047DL)
#endif//STATUS_IO_OPERATION_TIMEOUT

//
// MessageId: STATUS_SYSTEM_NEEDS_REMEDIATION
//
// MessageText:
//
// An error in a system binary was detected. Try refreshing the PC to fix the problem.
//
#ifndef STATUS_SYSTEM_NEEDS_REMEDIATION
#define STATUS_SYSTEM_NEEDS_REMEDIATION  ((NTSTATUS)0xC000047EL)
#endif//STATUS_SYSTEM_NEEDS_REMEDIATION

//
// MessageId: STATUS_APPX_INTEGRITY_FAILURE_CLR_NGEN
//
// MessageText:
//
// A corrupted CLR NGEN binary was detected on the system.
//
#ifndef STATUS_APPX_INTEGRITY_FAILURE_CLR_NGEN
#define STATUS_APPX_INTEGRITY_FAILURE_CLR_NGEN ((NTSTATUS)0xC000047FL)
#endif//STATUS_APPX_INTEGRITY_FAILURE_CLR_NGEN

//
// MessageId: STATUS_SHARE_UNAVAILABLE
//
// MessageText:
//
// The share is temporarily unavailable.
//
#ifndef STATUS_SHARE_UNAVAILABLE
#define STATUS_SHARE_UNAVAILABLE         ((NTSTATUS)0xC0000480L)
#endif//STATUS_SHARE_UNAVAILABLE

//
// MessageId: STATUS_APISET_NOT_HOSTED
//
// MessageText:
//
// The target dll was not found because the apiset %hs is not hosted.
//
#ifndef STATUS_APISET_NOT_HOSTED
#define STATUS_APISET_NOT_HOSTED         ((NTSTATUS)0xC0000481L)
#endif//STATUS_APISET_NOT_HOSTED

//
// MessageId: STATUS_APISET_NOT_PRESENT
//
// MessageText:
//
// The API set extension contains a host for a non-existent API set.
//
#ifndef STATUS_APISET_NOT_PRESENT
#define STATUS_APISET_NOT_PRESENT        ((NTSTATUS)0xC0000482L)
#endif//STATUS_APISET_NOT_PRESENT

//
// MessageId: STATUS_DEVICE_HARDWARE_ERROR
//
// MessageText:
//
// The request failed due to a fatal device hardware error.
//
#ifndef STATUS_DEVICE_HARDWARE_ERROR
#define STATUS_DEVICE_HARDWARE_ERROR     ((NTSTATUS)0xC0000483L)
#endif//STATUS_DEVICE_HARDWARE_ERROR

//
// MessageId: STATUS_FIRMWARE_SLOT_INVALID
//
// MessageText:
//
// The specified firmware slot is invalid.
//
#ifndef STATUS_FIRMWARE_SLOT_INVALID
#define STATUS_FIRMWARE_SLOT_INVALID     ((NTSTATUS)0xC0000484L)
#endif//STATUS_FIRMWARE_SLOT_INVALID

//
// MessageId: STATUS_FIRMWARE_IMAGE_INVALID
//
// MessageText:
//
// The specified firmware image is invalid.
//
#ifndef STATUS_FIRMWARE_IMAGE_INVALID
#define STATUS_FIRMWARE_IMAGE_INVALID    ((NTSTATUS)0xC0000485L)
#endif//STATUS_FIRMWARE_IMAGE_INVALID

//
// MessageId: STATUS_STORAGE_TOPOLOGY_ID_MISMATCH
//
// MessageText:
//
// The request failed due to a storage topology ID mismatch.
//
#ifndef STATUS_STORAGE_TOPOLOGY_ID_MISMATCH
#define STATUS_STORAGE_TOPOLOGY_ID_MISMATCH ((NTSTATUS)0xC0000486L)
#endif//STATUS_STORAGE_TOPOLOGY_ID_MISMATCH

//
// MessageId: STATUS_WIM_NOT_BOOTABLE
//
// MessageText:
//
// The specified Windows Image (WIM) is not marked as bootable.
//
#ifndef STATUS_WIM_NOT_BOOTABLE
#define STATUS_WIM_NOT_BOOTABLE          ((NTSTATUS)0xC0000487L)
#endif//STATUS_WIM_NOT_BOOTABLE

//
// MessageId: STATUS_BLOCKED_BY_PARENTAL_CONTROLS
//
// MessageText:
//
// The operation was blocked by parental controls.
//
#ifndef STATUS_BLOCKED_BY_PARENTAL_CONTROLS
#define STATUS_BLOCKED_BY_PARENTAL_CONTROLS ((NTSTATUS)0xC0000488L)
#endif//STATUS_BLOCKED_BY_PARENTAL_CONTROLS

//
// MessageId: STATUS_NEEDS_REGISTRATION
//
// MessageText:
//
// The deployment operation failed because the specified application needs to be registered first.
//
#ifndef STATUS_NEEDS_REGISTRATION
#define STATUS_NEEDS_REGISTRATION        ((NTSTATUS)0xC0000489L)
#endif//STATUS_NEEDS_REGISTRATION

//
// MessageId: STATUS_QUOTA_ACTIVITY
//
// MessageText:
//
// The requested operation failed due to quota operation is still in progress.
//
#ifndef STATUS_QUOTA_ACTIVITY
#define STATUS_QUOTA_ACTIVITY            ((NTSTATUS)0xC000048AL)
#endif//STATUS_QUOTA_ACTIVITY

//
// MessageId: STATUS_CALLBACK_INVOKE_INLINE
//
// MessageText:
//
// The callback function must be invoked inline.
//
#ifndef STATUS_CALLBACK_INVOKE_INLINE
#define STATUS_CALLBACK_INVOKE_INLINE    ((NTSTATUS)0xC000048BL)
#endif//STATUS_CALLBACK_INVOKE_INLINE

//
// MessageId: STATUS_BLOCK_TOO_MANY_REFERENCES
//
// MessageText:
//
// A file system block being referenced has already reached the maximum reference count and can't be referenced any further.
//
#ifndef STATUS_BLOCK_TOO_MANY_REFERENCES
#define STATUS_BLOCK_TOO_MANY_REFERENCES ((NTSTATUS)0xC000048CL)
#endif//STATUS_BLOCK_TOO_MANY_REFERENCES

//
// MessageId: STATUS_MARKED_TO_DISALLOW_WRITES
//
// MessageText:
//
// The requested operation failed because the file stream is marked to disallow writes.
//
#ifndef STATUS_MARKED_TO_DISALLOW_WRITES
#define STATUS_MARKED_TO_DISALLOW_WRITES ((NTSTATUS)0xC000048DL)
#endif//STATUS_MARKED_TO_DISALLOW_WRITES

//
// MessageId: STATUS_NETWORK_ACCESS_DENIED_EDP
//
// MessageText:
//
// Windows Information Protection policy does not allow access to this network resource.
//
#ifndef STATUS_NETWORK_ACCESS_DENIED_EDP
#define STATUS_NETWORK_ACCESS_DENIED_EDP ((NTSTATUS)0xC000048EL)
#endif//STATUS_NETWORK_ACCESS_DENIED_EDP

//
// MessageId: STATUS_ENCLAVE_FAILURE
//
// MessageText:
//
// The requested operation failed with an architecture-specific failure code.
//
#ifndef STATUS_ENCLAVE_FAILURE
#define STATUS_ENCLAVE_FAILURE           ((NTSTATUS)0xC000048FL)
#endif//STATUS_ENCLAVE_FAILURE

//
// MessageId: STATUS_PNP_NO_COMPAT_DRIVERS
//
// MessageText:
//
// There are no compatible drivers available for this device.
//
#ifndef STATUS_PNP_NO_COMPAT_DRIVERS
#define STATUS_PNP_NO_COMPAT_DRIVERS     ((NTSTATUS)0xC0000490L)
#endif//STATUS_PNP_NO_COMPAT_DRIVERS

//
// MessageId: STATUS_PNP_DRIVER_PACKAGE_NOT_FOUND
//
// MessageText:
//
// The specified driver package cannot be found on the system.
//
#ifndef STATUS_PNP_DRIVER_PACKAGE_NOT_FOUND
#define STATUS_PNP_DRIVER_PACKAGE_NOT_FOUND ((NTSTATUS)0xC0000491L)
#endif//STATUS_PNP_DRIVER_PACKAGE_NOT_FOUND

//
// MessageId: STATUS_PNP_DRIVER_CONFIGURATION_NOT_FOUND
//
// MessageText:
//
// The driver package cannot find a required driver configuration.
//
#ifndef STATUS_PNP_DRIVER_CONFIGURATION_NOT_FOUND
#define STATUS_PNP_DRIVER_CONFIGURATION_NOT_FOUND ((NTSTATUS)0xC0000492L)
#endif//STATUS_PNP_DRIVER_CONFIGURATION_NOT_FOUND

//
// MessageId: STATUS_PNP_DRIVER_CONFIGURATION_INCOMPLETE
//
// MessageText:
//
// The driver configuration is incomplete for use with this device.
//
#ifndef STATUS_PNP_DRIVER_CONFIGURATION_INCOMPLETE
#define STATUS_PNP_DRIVER_CONFIGURATION_INCOMPLETE ((NTSTATUS)0xC0000493L)
#endif//STATUS_PNP_DRIVER_CONFIGURATION_INCOMPLETE

//
// MessageId: STATUS_PNP_FUNCTION_DRIVER_REQUIRED
//
// MessageText:
//
// The device requires a driver configuration with a function driver.
//
#ifndef STATUS_PNP_FUNCTION_DRIVER_REQUIRED
#define STATUS_PNP_FUNCTION_DRIVER_REQUIRED ((NTSTATUS)0xC0000494L)
#endif//STATUS_PNP_FUNCTION_DRIVER_REQUIRED

//
// MessageId: STATUS_PNP_DEVICE_CONFIGURATION_PENDING
//
// MessageText:
//
// The device is pending further configuration.
//
#ifndef STATUS_PNP_DEVICE_CONFIGURATION_PENDING
#define STATUS_PNP_DEVICE_CONFIGURATION_PENDING ((NTSTATUS)0xC0000495L)
#endif//STATUS_PNP_DEVICE_CONFIGURATION_PENDING

//
// MessageId: STATUS_DEVICE_HINT_NAME_BUFFER_TOO_SMALL
//
// MessageText:
//
// The device hint name buffer is too small to receive the remaining name.
//
#ifndef STATUS_DEVICE_HINT_NAME_BUFFER_TOO_SMALL
#define STATUS_DEVICE_HINT_NAME_BUFFER_TOO_SMALL ((NTSTATUS)0xC0000496L)
#endif//STATUS_DEVICE_HINT_NAME_BUFFER_TOO_SMALL

//
// MessageId: STATUS_PACKAGE_NOT_AVAILABLE
//
// MessageText:
//
// The package is currently not available.
//
#ifndef STATUS_PACKAGE_NOT_AVAILABLE
#define STATUS_PACKAGE_NOT_AVAILABLE     ((NTSTATUS)0xC0000497L)
#endif//STATUS_PACKAGE_NOT_AVAILABLE

//
// MessageId: STATUS_DEVICE_IN_MAINTENANCE
//
// MessageText:
//
// The device is in maintenance mode.
//
#ifndef STATUS_DEVICE_IN_MAINTENANCE
#define STATUS_DEVICE_IN_MAINTENANCE     ((NTSTATUS)0xC0000499L)
#endif//STATUS_DEVICE_IN_MAINTENANCE

//
// MessageId: STATUS_NOT_SUPPORTED_ON_DAX
//
// MessageText:
//
// This operation is not supported on a DAX volume.
//
#ifndef STATUS_NOT_SUPPORTED_ON_DAX
#define STATUS_NOT_SUPPORTED_ON_DAX      ((NTSTATUS)0xC000049AL)
#endif//STATUS_NOT_SUPPORTED_ON_DAX

//
// MessageId: STATUS_FREE_SPACE_TOO_FRAGMENTED
//
// MessageText:
//
// The free space on the volume is too fragmented to complete this operation.
//
#ifndef STATUS_FREE_SPACE_TOO_FRAGMENTED
#define STATUS_FREE_SPACE_TOO_FRAGMENTED ((NTSTATUS)0xC000049BL)
#endif//STATUS_FREE_SPACE_TOO_FRAGMENTED

//
// MessageId: STATUS_DAX_MAPPING_EXISTS
//
// MessageText:
//
// The volume has active DAX mappings.
//
#ifndef STATUS_DAX_MAPPING_EXISTS
#define STATUS_DAX_MAPPING_EXISTS        ((NTSTATUS)0xC000049CL)
#endif//STATUS_DAX_MAPPING_EXISTS

//
// MessageId: STATUS_CHILD_PROCESS_BLOCKED
//
// MessageText:
//
// The process creation has been blocked.
//
#ifndef STATUS_CHILD_PROCESS_BLOCKED
#define STATUS_CHILD_PROCESS_BLOCKED     ((NTSTATUS)0xC000049DL)
#endif//STATUS_CHILD_PROCESS_BLOCKED

//
// MessageId: STATUS_STORAGE_LOST_DATA_PERSISTENCE
//
// MessageText:
//
// The storage device has lost data or persistence.
//
#ifndef STATUS_STORAGE_LOST_DATA_PERSISTENCE
#define STATUS_STORAGE_LOST_DATA_PERSISTENCE ((NTSTATUS)0xC000049EL)
#endif//STATUS_STORAGE_LOST_DATA_PERSISTENCE

//
// MessageId: STATUS_VRF_CFG_ENABLED
//
// MessageText:
//
// Driver Verifier Volatile settings cannot be set when CFG is enabled.
//
#ifndef STATUS_VRF_CFG_ENABLED
#define STATUS_VRF_CFG_ENABLED           ((NTSTATUS)0xC000049FL)
#endif//STATUS_VRF_CFG_ENABLED

//
// MessageId: STATUS_PARTITION_TERMINATING
//
// MessageText:
//
// An attempt was made to access a partition that has begun termination.
//
#ifndef STATUS_PARTITION_TERMINATING
#define STATUS_PARTITION_TERMINATING     ((NTSTATUS)0xC00004A0L)
#endif//STATUS_PARTITION_TERMINATING

//
// MessageId: STATUS_EXTERNAL_SYSKEY_NOT_SUPPORTED
//
// MessageText:
//
// An externally encrypted syskey has been configured, but the system no longer supports this feature.  Please see https://go.microsoft.com/fwlink/?linkid=851152 for more information.
//
#ifndef STATUS_EXTERNAL_SYSKEY_NOT_SUPPORTED
#define STATUS_EXTERNAL_SYSKEY_NOT_SUPPORTED ((NTSTATUS)0xC00004A1L)
#endif//STATUS_EXTERNAL_SYSKEY_NOT_SUPPORTED

//
// MessageId: STATUS_ENCLAVE_VIOLATION
//
// MessageText:
//
// An attempt was made to access protected memory in violation of its secure access policy.
//
#ifndef STATUS_ENCLAVE_VIOLATION
#define STATUS_ENCLAVE_VIOLATION         ((NTSTATUS)0xC00004A2L)    // winnt
#endif//STATUS_ENCLAVE_VIOLATION

//
// MessageId: STATUS_FILE_PROTECTED_UNDER_DPL
//
// MessageText:
//
// File is not accessible because it's currently protected under DPL.
//
#ifndef STATUS_FILE_PROTECTED_UNDER_DPL
#define STATUS_FILE_PROTECTED_UNDER_DPL  ((NTSTATUS)0xC00004A3L)
#endif//STATUS_FILE_PROTECTED_UNDER_DPL

//
// MessageId: STATUS_VOLUME_NOT_CLUSTER_ALIGNED
//
// MessageText:
//
// The volume is not cluster aligned on the disk.
//
#ifndef STATUS_VOLUME_NOT_CLUSTER_ALIGNED
#define STATUS_VOLUME_NOT_CLUSTER_ALIGNED ((NTSTATUS)0xC00004A4L)
#endif//STATUS_VOLUME_NOT_CLUSTER_ALIGNED

//
// MessageId: STATUS_NO_PHYSICALLY_ALIGNED_FREE_SPACE_FOUND
//
// MessageText:
//
// No physically aligned free space was found on the volume.
//
#ifndef STATUS_NO_PHYSICALLY_ALIGNED_FREE_SPACE_FOUND
#define STATUS_NO_PHYSICALLY_ALIGNED_FREE_SPACE_FOUND ((NTSTATUS)0xC00004A5L)
#endif//STATUS_NO_PHYSICALLY_ALIGNED_FREE_SPACE_FOUND

//
// MessageId: STATUS_APPX_FILE_NOT_ENCRYPTED
//
// MessageText:
//
// The APPX file can not be accessed because it is not encrypted as expected.
//
#ifndef STATUS_APPX_FILE_NOT_ENCRYPTED
#define STATUS_APPX_FILE_NOT_ENCRYPTED   ((NTSTATUS)0xC00004A6L)
#endif//STATUS_APPX_FILE_NOT_ENCRYPTED

//
// MessageId: STATUS_RWRAW_ENCRYPTED_FILE_NOT_ENCRYPTED
//
// MessageText:
//
// A read or write of raw encrypted data cannot be performed because the file is not encrypted.
//
#ifndef STATUS_RWRAW_ENCRYPTED_FILE_NOT_ENCRYPTED
#define STATUS_RWRAW_ENCRYPTED_FILE_NOT_ENCRYPTED ((NTSTATUS)0xC00004A7L)
#endif//STATUS_RWRAW_ENCRYPTED_FILE_NOT_ENCRYPTED

//
// MessageId: STATUS_RWRAW_ENCRYPTED_INVALID_EDATAINFO_FILEOFFSET
//
// MessageText:
//
// An invalid file offset in the encrypted data info block was passed for read or write operation of file's raw encrypted data.
//
#ifndef STATUS_RWRAW_ENCRYPTED_INVALID_EDATAINFO_FILEOFFSET
#define STATUS_RWRAW_ENCRYPTED_INVALID_EDATAINFO_FILEOFFSET ((NTSTATUS)0xC00004A8L)
#endif//STATUS_RWRAW_ENCRYPTED_INVALID_EDATAINFO_FILEOFFSET

//
// MessageId: STATUS_RWRAW_ENCRYPTED_INVALID_EDATAINFO_FILERANGE
//
// MessageText:
//
// An invalid offset and length combination in the encrypted data info was passed for read or write operation of file's raw encrypted data.
//
#ifndef STATUS_RWRAW_ENCRYPTED_INVALID_EDATAINFO_FILERANGE
#define STATUS_RWRAW_ENCRYPTED_INVALID_EDATAINFO_FILERANGE ((NTSTATUS)0xC00004A9L)
#endif//STATUS_RWRAW_ENCRYPTED_INVALID_EDATAINFO_FILERANGE

//
// MessageId: STATUS_RWRAW_ENCRYPTED_INVALID_EDATAINFO_PARAMETER
//
// MessageText:
//
// An invalid parameter in the encrypted data info was passed for read or write operation of file's raw encrypted data.
//
#ifndef STATUS_RWRAW_ENCRYPTED_INVALID_EDATAINFO_PARAMETER
#define STATUS_RWRAW_ENCRYPTED_INVALID_EDATAINFO_PARAMETER ((NTSTATUS)0xC00004AAL)
#endif//STATUS_RWRAW_ENCRYPTED_INVALID_EDATAINFO_PARAMETER


//     **** New SYSTEM error codes can be inserted here ****

//
// MessageId: STATUS_INVALID_TASK_NAME
//
// MessageText:
//
// The specified task name is invalid.
//
#ifndef STATUS_INVALID_TASK_NAME
#define STATUS_INVALID_TASK_NAME         ((NTSTATUS)0xC0000500L)
#endif//STATUS_INVALID_TASK_NAME

//
// MessageId: STATUS_INVALID_TASK_INDEX
//
// MessageText:
//
// The specified task index is invalid.
//
#ifndef STATUS_INVALID_TASK_INDEX
#define STATUS_INVALID_TASK_INDEX        ((NTSTATUS)0xC0000501L)
#endif//STATUS_INVALID_TASK_INDEX

//
// MessageId: STATUS_THREAD_ALREADY_IN_TASK
//
// MessageText:
//
// The specified thread is already joining a task.
//
#ifndef STATUS_THREAD_ALREADY_IN_TASK
#define STATUS_THREAD_ALREADY_IN_TASK    ((NTSTATUS)0xC0000502L)
#endif//STATUS_THREAD_ALREADY_IN_TASK

//
// MessageId: STATUS_CALLBACK_BYPASS
//
// MessageText:
//
// A callback has requested to bypass native code.
//
#ifndef STATUS_CALLBACK_BYPASS
#define STATUS_CALLBACK_BYPASS           ((NTSTATUS)0xC0000503L)
#endif//STATUS_CALLBACK_BYPASS

//
// MessageId: STATUS_UNDEFINED_SCOPE
//
// MessageText:
//
// The Central Access Policy specified is not defined on the target machine.
//
#ifndef STATUS_UNDEFINED_SCOPE
#define STATUS_UNDEFINED_SCOPE           ((NTSTATUS)0xC0000504L)
#endif//STATUS_UNDEFINED_SCOPE

//
// MessageId: STATUS_INVALID_CAP
//
// MessageText:
//
// The Central Access Policy obtained from Active Directory is invalid.
//
#ifndef STATUS_INVALID_CAP
#define STATUS_INVALID_CAP               ((NTSTATUS)0xC0000505L)
#endif//STATUS_INVALID_CAP

//
// MessageId: STATUS_NOT_GUI_PROCESS
//
// MessageText:
//
// Unable to finish the requested operation because the specified process is not a GUI process.
//
#ifndef STATUS_NOT_GUI_PROCESS
#define STATUS_NOT_GUI_PROCESS           ((NTSTATUS)0xC0000506L)
#endif//STATUS_NOT_GUI_PROCESS

//
// MessageId: STATUS_DEVICE_HUNG
//
// MessageText:
//
// The device is not responding and cannot be safely removed.
//
#ifndef STATUS_DEVICE_HUNG
#define STATUS_DEVICE_HUNG               ((NTSTATUS)0xC0000507L)
#endif//STATUS_DEVICE_HUNG

//
// MessageId: STATUS_CONTAINER_ASSIGNED
//
// MessageText:
//
// The specified Job already has a container assigned to it.
//
#ifndef STATUS_CONTAINER_ASSIGNED
#define STATUS_CONTAINER_ASSIGNED        ((NTSTATUS)0xC0000508L)
#endif//STATUS_CONTAINER_ASSIGNED

//
// MessageId: STATUS_JOB_NO_CONTAINER
//
// MessageText:
//
// The specified Job does not have a container assigned to it.
//
#ifndef STATUS_JOB_NO_CONTAINER
#define STATUS_JOB_NO_CONTAINER          ((NTSTATUS)0xC0000509L)
#endif//STATUS_JOB_NO_CONTAINER

//
// MessageId: STATUS_DEVICE_UNRESPONSIVE
//
// MessageText:
//
// The device is unresponsive.
//
#ifndef STATUS_DEVICE_UNRESPONSIVE
#define STATUS_DEVICE_UNRESPONSIVE       ((NTSTATUS)0xC000050AL)
#endif//STATUS_DEVICE_UNRESPONSIVE

//
// MessageId: STATUS_REPARSE_POINT_ENCOUNTERED
//
// MessageText:
//
// The object manager encountered a reparse point while retrieving an object.
//
#ifndef STATUS_REPARSE_POINT_ENCOUNTERED
#define STATUS_REPARSE_POINT_ENCOUNTERED ((NTSTATUS)0xC000050BL)
#endif//STATUS_REPARSE_POINT_ENCOUNTERED

//
// MessageId: STATUS_ATTRIBUTE_NOT_PRESENT
//
// MessageText:
//
// The requested attribute is not present on the specified file or directory.
//
#ifndef STATUS_ATTRIBUTE_NOT_PRESENT
#define STATUS_ATTRIBUTE_NOT_PRESENT     ((NTSTATUS)0xC000050CL)
#endif//STATUS_ATTRIBUTE_NOT_PRESENT

//
// MessageId: STATUS_NOT_A_TIERED_VOLUME
//
// MessageText:
//
// This volume is not a tiered volume.
//
#ifndef STATUS_NOT_A_TIERED_VOLUME
#define STATUS_NOT_A_TIERED_VOLUME       ((NTSTATUS)0xC000050DL)
#endif//STATUS_NOT_A_TIERED_VOLUME

//
// MessageId: STATUS_ALREADY_HAS_STREAM_ID
//
// MessageText:
//
// This file is currently associated with a different stream id.
//
#ifndef STATUS_ALREADY_HAS_STREAM_ID
#define STATUS_ALREADY_HAS_STREAM_ID     ((NTSTATUS)0xC000050EL)
#endif//STATUS_ALREADY_HAS_STREAM_ID

//
// MessageId: STATUS_JOB_NOT_EMPTY
//
// MessageText:
//
// The requested operation could not be completed because the specified job has children.
//
#ifndef STATUS_JOB_NOT_EMPTY
#define STATUS_JOB_NOT_EMPTY             ((NTSTATUS)0xC000050FL)
#endif//STATUS_JOB_NOT_EMPTY

//
// MessageId: STATUS_ALREADY_INITIALIZED
//
// MessageText:
//
// The specified object has already been initialized.
//
#ifndef STATUS_ALREADY_INITIALIZED
#define STATUS_ALREADY_INITIALIZED       ((NTSTATUS)0xC0000510L)
#endif//STATUS_ALREADY_INITIALIZED

//
// MessageId: STATUS_ENCLAVE_NOT_TERMINATED
//
// MessageText:
//
// The specified enclave has not yet been terminated.
//
#ifndef STATUS_ENCLAVE_NOT_TERMINATED
#define STATUS_ENCLAVE_NOT_TERMINATED    ((NTSTATUS)0xC0000511L)
#endif//STATUS_ENCLAVE_NOT_TERMINATED

//
// MessageId: STATUS_ENCLAVE_IS_TERMINATING
//
// MessageText:
//
// An attempt was made to access an enclave that has begun termination.
//
#ifndef STATUS_ENCLAVE_IS_TERMINATING
#define STATUS_ENCLAVE_IS_TERMINATING    ((NTSTATUS)0xC0000512L)
#endif//STATUS_ENCLAVE_IS_TERMINATING

//
// MessageId: STATUS_SMB1_NOT_AVAILABLE
//
// MessageText:
//
// You can't connect to the file share because it's not secure. This share requires the obsolete SMB1 protocol, which is unsafe and could expose your system to attack.
// Your system requires SMB2 or higher. For more info on resolving this issue, see: https://go.microsoft.com/fwlink/?linkid=852747
//
#ifndef STATUS_SMB1_NOT_AVAILABLE
#define STATUS_SMB1_NOT_AVAILABLE        ((NTSTATUS)0xC0000513L)
#endif//STATUS_SMB1_NOT_AVAILABLE

//
// MessageId: STATUS_SMR_GARBAGE_COLLECTION_REQUIRED
//
// MessageText:
//
// The volume must undergo garbage collection.
//
#ifndef STATUS_SMR_GARBAGE_COLLECTION_REQUIRED
#define STATUS_SMR_GARBAGE_COLLECTION_REQUIRED ((NTSTATUS)0xC0000514L)
#endif//STATUS_SMR_GARBAGE_COLLECTION_REQUIRED


//     **** New SYSTEM error codes can be inserted here ****

//
// MessageId: STATUS_FAIL_FAST_EXCEPTION
//
// MessageText:
//
// {Fail Fast Exception}
// A fail fast exception occurred. Exception handlers will not be invoked and the process will be terminated immediately.
//
#ifndef STATUS_FAIL_FAST_EXCEPTION
#define STATUS_FAIL_FAST_EXCEPTION       ((NTSTATUS)0xC0000602L)
#endif//STATUS_FAIL_FAST_EXCEPTION

//
// MessageId: STATUS_IMAGE_CERT_REVOKED
//
// MessageText:
//
// Windows cannot verify the digital signature for this file. The signing certificate for this file has been revoked.
//
#ifndef STATUS_IMAGE_CERT_REVOKED
#define STATUS_IMAGE_CERT_REVOKED        ((NTSTATUS)0xC0000603L)
#endif//STATUS_IMAGE_CERT_REVOKED

//
// MessageId: STATUS_DYNAMIC_CODE_BLOCKED
//
// MessageText:
//
// The operation was blocked as the process prohibits dynamic code generation.
//
#ifndef STATUS_DYNAMIC_CODE_BLOCKED
#define STATUS_DYNAMIC_CODE_BLOCKED      ((NTSTATUS)0xC0000604L)
#endif//STATUS_DYNAMIC_CODE_BLOCKED

//
// MessageId: STATUS_IMAGE_CERT_EXPIRED
//
// MessageText:
//
// Windows cannot verify the digital signature for this file. The signing certificate for this file has expired.
//
#ifndef STATUS_IMAGE_CERT_EXPIRED
#define STATUS_IMAGE_CERT_EXPIRED        ((NTSTATUS)0xC0000605L)
#endif//STATUS_IMAGE_CERT_EXPIRED

//
// MessageId: STATUS_STRICT_CFG_VIOLATION
//
// MessageText:
//
// The specified image file was blocked from loading because it does not enable a feature required by the process: Control Flow Guard.
//
#ifndef STATUS_STRICT_CFG_VIOLATION
#define STATUS_STRICT_CFG_VIOLATION      ((NTSTATUS)0xC0000606L)
#endif//STATUS_STRICT_CFG_VIOLATION

//
// MessageId: STATUS_SET_CONTEXT_DENIED
//
// MessageText:
//
// The thread context could not be updated because this has been restricted for the process.
//
#ifndef STATUS_SET_CONTEXT_DENIED
#define STATUS_SET_CONTEXT_DENIED        ((NTSTATUS)0xC000060AL)
#endif//STATUS_SET_CONTEXT_DENIED

//
// MessageId: STATUS_CROSS_PARTITION_VIOLATION
//
// MessageText:
//
// An attempt to access another partition's private file/section was rejected.
//
#ifndef STATUS_CROSS_PARTITION_VIOLATION
#define STATUS_CROSS_PARTITION_VIOLATION ((NTSTATUS)0xC000060BL)
#endif//STATUS_CROSS_PARTITION_VIOLATION

//
// MessageId: STATUS_PORT_CLOSED
//
// MessageText:
//
// The ALPC port is closed.
//
#ifndef STATUS_PORT_CLOSED
#define STATUS_PORT_CLOSED               ((NTSTATUS)0xC0000700L)
#endif//STATUS_PORT_CLOSED

//
// MessageId: STATUS_MESSAGE_LOST
//
// MessageText:
//
// The ALPC message requested is no longer available.
//
#ifndef STATUS_MESSAGE_LOST
#define STATUS_MESSAGE_LOST              ((NTSTATUS)0xC0000701L)
#endif//STATUS_MESSAGE_LOST

//
// MessageId: STATUS_INVALID_MESSAGE
//
// MessageText:
//
// The ALPC message supplied is invalid.
//
#ifndef STATUS_INVALID_MESSAGE
#define STATUS_INVALID_MESSAGE           ((NTSTATUS)0xC0000702L)
#endif//STATUS_INVALID_MESSAGE

//
// MessageId: STATUS_REQUEST_CANCELED
//
// MessageText:
//
// The ALPC message has been canceled.
//
#ifndef STATUS_REQUEST_CANCELED
#define STATUS_REQUEST_CANCELED          ((NTSTATUS)0xC0000703L)
#endif//STATUS_REQUEST_CANCELED

//
// MessageId: STATUS_RECURSIVE_DISPATCH
//
// MessageText:
//
// Invalid recursive dispatch attempt.
//
#ifndef STATUS_RECURSIVE_DISPATCH
#define STATUS_RECURSIVE_DISPATCH        ((NTSTATUS)0xC0000704L)
#endif//STATUS_RECURSIVE_DISPATCH

//
// MessageId: STATUS_LPC_RECEIVE_BUFFER_EXPECTED
//
// MessageText:
//
// No receive buffer has been supplied in a synchrounus request.
//
#ifndef STATUS_LPC_RECEIVE_BUFFER_EXPECTED
#define STATUS_LPC_RECEIVE_BUFFER_EXPECTED ((NTSTATUS)0xC0000705L)
#endif//STATUS_LPC_RECEIVE_BUFFER_EXPECTED

//
// MessageId: STATUS_LPC_INVALID_CONNECTION_USAGE
//
// MessageText:
//
// The connection port is used in an invalid context.
//
#ifndef STATUS_LPC_INVALID_CONNECTION_USAGE
#define STATUS_LPC_INVALID_CONNECTION_USAGE ((NTSTATUS)0xC0000706L)
#endif//STATUS_LPC_INVALID_CONNECTION_USAGE

//
// MessageId: STATUS_LPC_REQUESTS_NOT_ALLOWED
//
// MessageText:
//
// The ALPC port does not accept new request messages.
//
#ifndef STATUS_LPC_REQUESTS_NOT_ALLOWED
#define STATUS_LPC_REQUESTS_NOT_ALLOWED  ((NTSTATUS)0xC0000707L)
#endif//STATUS_LPC_REQUESTS_NOT_ALLOWED

//
// MessageId: STATUS_RESOURCE_IN_USE
//
// MessageText:
//
// The resource requested is already in use.
//
#ifndef STATUS_RESOURCE_IN_USE
#define STATUS_RESOURCE_IN_USE           ((NTSTATUS)0xC0000708L)
#endif//STATUS_RESOURCE_IN_USE

//
// MessageId: STATUS_HARDWARE_MEMORY_ERROR
//
// MessageText:
//
// The hardware has reported an uncorrectable memory error.
//
#ifndef STATUS_HARDWARE_MEMORY_ERROR
#define STATUS_HARDWARE_MEMORY_ERROR     ((NTSTATUS)0xC0000709L)
#endif//STATUS_HARDWARE_MEMORY_ERROR

//
// MessageId: STATUS_THREADPOOL_HANDLE_EXCEPTION
//
// MessageText:
//
// Status 0x%08x was returned, waiting on handle 0x%x for wait 0x%p, in waiter 0x%p.
//
#ifndef STATUS_THREADPOOL_HANDLE_EXCEPTION
#define STATUS_THREADPOOL_HANDLE_EXCEPTION ((NTSTATUS)0xC000070AL)
#endif//STATUS_THREADPOOL_HANDLE_EXCEPTION

//
// MessageId: STATUS_THREADPOOL_SET_EVENT_ON_COMPLETION_FAILED
//
// MessageText:
//
// After a callback to 0x%p(0x%p), a completion call to SetEvent(0x%p) failed with status 0x%08x.
//
#ifndef STATUS_THREADPOOL_SET_EVENT_ON_COMPLETION_FAILED
#define STATUS_THREADPOOL_SET_EVENT_ON_COMPLETION_FAILED ((NTSTATUS)0xC000070BL)
#endif//STATUS_THREADPOOL_SET_EVENT_ON_COMPLETION_FAILED

//
// MessageId: STATUS_THREADPOOL_RELEASE_SEMAPHORE_ON_COMPLETION_FAILED
//
// MessageText:
//
// After a callback to 0x%p(0x%p), a completion call to ReleaseSemaphore(0x%p, %d) failed with status 0x%08x.
//
#ifndef STATUS_THREADPOOL_RELEASE_SEMAPHORE_ON_COMPLETION_FAILED
#define STATUS_THREADPOOL_RELEASE_SEMAPHORE_ON_COMPLETION_FAILED ((NTSTATUS)0xC000070CL)
#endif//STATUS_THREADPOOL_RELEASE_SEMAPHORE_ON_COMPLETION_FAILED

//
// MessageId: STATUS_THREADPOOL_RELEASE_MUTEX_ON_COMPLETION_FAILED
//
// MessageText:
//
// After a callback to 0x%p(0x%p), a completion call to ReleaseMutex(%p) failed with status 0x%08x.
//
#ifndef STATUS_THREADPOOL_RELEASE_MUTEX_ON_COMPLETION_FAILED
#define STATUS_THREADPOOL_RELEASE_MUTEX_ON_COMPLETION_FAILED ((NTSTATUS)0xC000070DL)
#endif//STATUS_THREADPOOL_RELEASE_MUTEX_ON_COMPLETION_FAILED

//
// MessageId: STATUS_THREADPOOL_FREE_LIBRARY_ON_COMPLETION_FAILED
//
// MessageText:
//
// After a callback to 0x%p(0x%p), an completion call to FreeLibrary(%p) failed with status 0x%08x.
//
#ifndef STATUS_THREADPOOL_FREE_LIBRARY_ON_COMPLETION_FAILED
#define STATUS_THREADPOOL_FREE_LIBRARY_ON_COMPLETION_FAILED ((NTSTATUS)0xC000070EL)
#endif//STATUS_THREADPOOL_FREE_LIBRARY_ON_COMPLETION_FAILED

//
// MessageId: STATUS_THREADPOOL_RELEASED_DURING_OPERATION
//
// MessageText:
//
// The threadpool 0x%p was released while a thread was posting a callback to 0x%p(0x%p) to it.
//
#ifndef STATUS_THREADPOOL_RELEASED_DURING_OPERATION
#define STATUS_THREADPOOL_RELEASED_DURING_OPERATION ((NTSTATUS)0xC000070FL)
#endif//STATUS_THREADPOOL_RELEASED_DURING_OPERATION

//
// MessageId: STATUS_CALLBACK_RETURNED_WHILE_IMPERSONATING
//
// MessageText:
//
// A threadpool worker thread is impersonating a client, after a callback to 0x%p(0x%p).
// This is unexpected, indicating that the callback is missing a call to revert the impersonation.
//
#ifndef STATUS_CALLBACK_RETURNED_WHILE_IMPERSONATING
#define STATUS_CALLBACK_RETURNED_WHILE_IMPERSONATING ((NTSTATUS)0xC0000710L)
#endif//STATUS_CALLBACK_RETURNED_WHILE_IMPERSONATING

//
// MessageId: STATUS_APC_RETURNED_WHILE_IMPERSONATING
//
// MessageText:
//
// A threadpool worker thread is impersonating a client, after executing an APC.
// This is unexpected, indicating that the APC is missing a call to revert the impersonation.
//
#ifndef STATUS_APC_RETURNED_WHILE_IMPERSONATING
#define STATUS_APC_RETURNED_WHILE_IMPERSONATING ((NTSTATUS)0xC0000711L)
#endif//STATUS_APC_RETURNED_WHILE_IMPERSONATING

//
// MessageId: STATUS_PROCESS_IS_PROTECTED
//
// MessageText:
//
// Either the target process, or the target thread's containing process, is a protected process.
//
#ifndef STATUS_PROCESS_IS_PROTECTED
#define STATUS_PROCESS_IS_PROTECTED      ((NTSTATUS)0xC0000712L)
#endif//STATUS_PROCESS_IS_PROTECTED

//
// MessageId: STATUS_MCA_EXCEPTION
//
// MessageText:
//
// A Thread is getting dispatched with MCA EXCEPTION because of MCA.
//
#ifndef STATUS_MCA_EXCEPTION
#define STATUS_MCA_EXCEPTION             ((NTSTATUS)0xC0000713L)
#endif//STATUS_MCA_EXCEPTION

//
// MessageId: STATUS_CERTIFICATE_MAPPING_NOT_UNIQUE
//
// MessageText:
//
// The client certificate account mapping is not unique.
//
#ifndef STATUS_CERTIFICATE_MAPPING_NOT_UNIQUE
#define STATUS_CERTIFICATE_MAPPING_NOT_UNIQUE ((NTSTATUS)0xC0000714L)
#endif//STATUS_CERTIFICATE_MAPPING_NOT_UNIQUE

//
// MessageId: STATUS_SYMLINK_CLASS_DISABLED
//
// MessageText:
//
// The symbolic link cannot be followed because its type is disabled.
//
#ifndef STATUS_SYMLINK_CLASS_DISABLED
#define STATUS_SYMLINK_CLASS_DISABLED    ((NTSTATUS)0xC0000715L)
#endif//STATUS_SYMLINK_CLASS_DISABLED

//
// MessageId: STATUS_INVALID_IDN_NORMALIZATION
//
// MessageText:
//
// Indicates that the specified string is not valid for IDN normalization.
//
#ifndef STATUS_INVALID_IDN_NORMALIZATION
#define STATUS_INVALID_IDN_NORMALIZATION ((NTSTATUS)0xC0000716L)
#endif//STATUS_INVALID_IDN_NORMALIZATION

//
// MessageId: STATUS_NO_UNICODE_TRANSLATION
//
// MessageText:
//
// No mapping for the Unicode character exists in the target multi-byte code page.
//
#ifndef STATUS_NO_UNICODE_TRANSLATION
#define STATUS_NO_UNICODE_TRANSLATION    ((NTSTATUS)0xC0000717L)
#endif//STATUS_NO_UNICODE_TRANSLATION

//
// MessageId: STATUS_ALREADY_REGISTERED
//
// MessageText:
//
// The provided callback is already registered.
//
#ifndef STATUS_ALREADY_REGISTERED
#define STATUS_ALREADY_REGISTERED        ((NTSTATUS)0xC0000718L)
#endif//STATUS_ALREADY_REGISTERED

//
// MessageId: STATUS_CONTEXT_MISMATCH
//
// MessageText:
//
// The provided context did not match the target.
//
#ifndef STATUS_CONTEXT_MISMATCH
#define STATUS_CONTEXT_MISMATCH          ((NTSTATUS)0xC0000719L)
#endif//STATUS_CONTEXT_MISMATCH

//
// MessageId: STATUS_PORT_ALREADY_HAS_COMPLETION_LIST
//
// MessageText:
//
// The specified port already has a completion list.
//
#ifndef STATUS_PORT_ALREADY_HAS_COMPLETION_LIST
#define STATUS_PORT_ALREADY_HAS_COMPLETION_LIST ((NTSTATUS)0xC000071AL)
#endif//STATUS_PORT_ALREADY_HAS_COMPLETION_LIST

//
// MessageId: STATUS_CALLBACK_RETURNED_THREAD_PRIORITY
//
// MessageText:
//
// A threadpool worker thread enter a callback at thread base priority 0x%x and exited at priority 0x%x.
// This is unexpected, indicating that the callback missed restoring the priority.
//
#ifndef STATUS_CALLBACK_RETURNED_THREAD_PRIORITY
#define STATUS_CALLBACK_RETURNED_THREAD_PRIORITY ((NTSTATUS)0xC000071BL)
#endif//STATUS_CALLBACK_RETURNED_THREAD_PRIORITY

//
// MessageId: STATUS_INVALID_THREAD
//
// MessageText:
//
// An invalid thread, handle %p, is specified for this operation. Possibly, a threadpool worker thread was specified.
//
#ifndef STATUS_INVALID_THREAD
#define STATUS_INVALID_THREAD            ((NTSTATUS)0xC000071CL)
#endif//STATUS_INVALID_THREAD

//
// MessageId: STATUS_CALLBACK_RETURNED_TRANSACTION
//
// MessageText:
//
// A threadpool worker thread enter a callback, which left transaction state.
// This is unexpected, indicating that the callback missed clearing the transaction.
//
#ifndef STATUS_CALLBACK_RETURNED_TRANSACTION
#define STATUS_CALLBACK_RETURNED_TRANSACTION ((NTSTATUS)0xC000071DL)
#endif//STATUS_CALLBACK_RETURNED_TRANSACTION

//
// MessageId: STATUS_CALLBACK_RETURNED_LDR_LOCK
//
// MessageText:
//
// A threadpool worker thread enter a callback, which left the loader lock held.
// This is unexpected, indicating that the callback missed releasing the lock.
//
#ifndef STATUS_CALLBACK_RETURNED_LDR_LOCK
#define STATUS_CALLBACK_RETURNED_LDR_LOCK ((NTSTATUS)0xC000071EL)
#endif//STATUS_CALLBACK_RETURNED_LDR_LOCK

//
// MessageId: STATUS_CALLBACK_RETURNED_LANG
//
// MessageText:
//
// A threadpool worker thread enter a callback, which left with preferred languages set.
// This is unexpected, indicating that the callback missed clearing them.
//
#ifndef STATUS_CALLBACK_RETURNED_LANG
#define STATUS_CALLBACK_RETURNED_LANG    ((NTSTATUS)0xC000071FL)
#endif//STATUS_CALLBACK_RETURNED_LANG

//
// MessageId: STATUS_CALLBACK_RETURNED_PRI_BACK
//
// MessageText:
//
// A threadpool worker thread enter a callback, which left with background priorities set.
// This is unexpected, indicating that the callback missed restoring the original priorities.
//
#ifndef STATUS_CALLBACK_RETURNED_PRI_BACK
#define STATUS_CALLBACK_RETURNED_PRI_BACK ((NTSTATUS)0xC0000720L)
#endif//STATUS_CALLBACK_RETURNED_PRI_BACK

//
// MessageId: STATUS_CALLBACK_RETURNED_THREAD_AFFINITY
//
// MessageText:
//
// A threadpool worker thread enter a callback at thread affinity %p and exited at affinity %p.
// This is unexpected, indicating that the callback missed restoring the priority.
//
#ifndef STATUS_CALLBACK_RETURNED_THREAD_AFFINITY
#define STATUS_CALLBACK_RETURNED_THREAD_AFFINITY ((NTSTATUS)0xC0000721L)
#endif//STATUS_CALLBACK_RETURNED_THREAD_AFFINITY

//
// MessageId: STATUS_LPC_HANDLE_COUNT_EXCEEDED
//
// MessageText:
//
// The caller has exceeded the maximum number of handles that may be transmitted in
// a single local procedure call.
//
#ifndef STATUS_LPC_HANDLE_COUNT_EXCEEDED
#define STATUS_LPC_HANDLE_COUNT_EXCEEDED ((NTSTATUS)0xC0000722L)
#endif//STATUS_LPC_HANDLE_COUNT_EXCEEDED

//
// MessageId: STATUS_EXECUTABLE_MEMORY_WRITE
//
// MessageText:
//
// A write to executable memory occurred for a process that is managing such operations.
//
#ifndef STATUS_EXECUTABLE_MEMORY_WRITE
#define STATUS_EXECUTABLE_MEMORY_WRITE   ((NTSTATUS)0xC0000723L)
#endif//STATUS_EXECUTABLE_MEMORY_WRITE

//
// MessageId: STATUS_KERNEL_EXECUTABLE_MEMORY_WRITE
//
// MessageText:
//
// A write to executable memory occurred from kernel mode for a process that is managing such operations.
//
#ifndef STATUS_KERNEL_EXECUTABLE_MEMORY_WRITE
#define STATUS_KERNEL_EXECUTABLE_MEMORY_WRITE ((NTSTATUS)0xC0000724L)
#endif//STATUS_KERNEL_EXECUTABLE_MEMORY_WRITE

//
// MessageId: STATUS_ATTACHED_EXECUTABLE_MEMORY_WRITE
//
// MessageText:
//
// A write to executable memory occurred from kernel mode while attached to a process that is managing such operations.
//
#ifndef STATUS_ATTACHED_EXECUTABLE_MEMORY_WRITE
#define STATUS_ATTACHED_EXECUTABLE_MEMORY_WRITE ((NTSTATUS)0xC0000725L)
#endif//STATUS_ATTACHED_EXECUTABLE_MEMORY_WRITE

//
// MessageId: STATUS_TRIGGERED_EXECUTABLE_MEMORY_WRITE
//
// MessageText:
//
// A write to executable memory was triggered cross-process to a process that is managing such operations.
//
#ifndef STATUS_TRIGGERED_EXECUTABLE_MEMORY_WRITE
#define STATUS_TRIGGERED_EXECUTABLE_MEMORY_WRITE ((NTSTATUS)0xC0000726L)
#endif//STATUS_TRIGGERED_EXECUTABLE_MEMORY_WRITE

//
// MessageId: STATUS_DISK_REPAIR_DISABLED
//
// MessageText:
//
// The attempted operation required self healing to be enabled.
//
#ifndef STATUS_DISK_REPAIR_DISABLED
#define STATUS_DISK_REPAIR_DISABLED      ((NTSTATUS)0xC0000800L)
#endif//STATUS_DISK_REPAIR_DISABLED

//
// MessageId: STATUS_DS_DOMAIN_RENAME_IN_PROGRESS
//
// MessageText:
//
// The Directory Service cannot perform the requested operation because a domain rename operation is in progress.
//
#ifndef STATUS_DS_DOMAIN_RENAME_IN_PROGRESS
#define STATUS_DS_DOMAIN_RENAME_IN_PROGRESS ((NTSTATUS)0xC0000801L)
#endif//STATUS_DS_DOMAIN_RENAME_IN_PROGRESS

//
// MessageId: STATUS_DISK_QUOTA_EXCEEDED
//
// MessageText:
//
// The requested file operation failed because the storage quota was exceeded.
// To free up disk space, move files to a different location or delete unnecessary files. For more information, contact your system administrator.
//
#ifndef STATUS_DISK_QUOTA_EXCEEDED
#define STATUS_DISK_QUOTA_EXCEEDED       ((NTSTATUS)0xC0000802L)
#endif//STATUS_DISK_QUOTA_EXCEEDED

//
// MessageId: STATUS_DATA_LOST_REPAIR
//
// MessageText:
//
// Windows discovered a corruption in the file "%hs".
// This file has now been repaired.
// Please check if any data in the file was lost because of the corruption.
//
#ifndef STATUS_DATA_LOST_REPAIR
#define STATUS_DATA_LOST_REPAIR          ((NTSTATUS)0x80000803L)
#endif//STATUS_DATA_LOST_REPAIR

//
// MessageId: STATUS_CONTENT_BLOCKED
//
// MessageText:
//
// The requested file operation failed because the storage policy blocks that type of file. For more information, contact your system administrator.
//
#ifndef STATUS_CONTENT_BLOCKED
#define STATUS_CONTENT_BLOCKED           ((NTSTATUS)0xC0000804L)
#endif//STATUS_CONTENT_BLOCKED

//
// MessageId: STATUS_BAD_CLUSTERS
//
// MessageText:
//
// The operation could not be completed due to bad clusters on disk.
//
#ifndef STATUS_BAD_CLUSTERS
#define STATUS_BAD_CLUSTERS              ((NTSTATUS)0xC0000805L)
#endif//STATUS_BAD_CLUSTERS

//
// MessageId: STATUS_VOLUME_DIRTY
//
// MessageText:
//
// The operation could not be completed because the volume is dirty. Please run chkdsk and try again.
//
#ifndef STATUS_VOLUME_DIRTY
#define STATUS_VOLUME_DIRTY              ((NTSTATUS)0xC0000806L)
#endif//STATUS_VOLUME_DIRTY

//
// MessageId: STATUS_DISK_REPAIR_REDIRECTED
//
// MessageText:
//
// The volume repair could not be performed while it is online.
// Please schedule to take the volume offline so that it can be repaired.
//
#ifndef STATUS_DISK_REPAIR_REDIRECTED
#define STATUS_DISK_REPAIR_REDIRECTED    ((NTSTATUS)0x40000807L)
#endif//STATUS_DISK_REPAIR_REDIRECTED

//
// MessageId: STATUS_DISK_REPAIR_UNSUCCESSFUL
//
// MessageText:
//
// The volume repair was not successful.
//
#ifndef STATUS_DISK_REPAIR_UNSUCCESSFUL
#define STATUS_DISK_REPAIR_UNSUCCESSFUL  ((NTSTATUS)0xC0000808L)
#endif//STATUS_DISK_REPAIR_UNSUCCESSFUL

//
// MessageId: STATUS_CORRUPT_LOG_OVERFULL
//
// MessageText:
//
// One of the volume corruption logs is full. Further corruptions that may be detected won't be logged.
//
#ifndef STATUS_CORRUPT_LOG_OVERFULL
#define STATUS_CORRUPT_LOG_OVERFULL      ((NTSTATUS)0xC0000809L)
#endif//STATUS_CORRUPT_LOG_OVERFULL

//
// MessageId: STATUS_CORRUPT_LOG_CORRUPTED
//
// MessageText:
//
// One of the volume corruption logs is internally corrupted and needs to be recreated. The volume may contain undetected corruptions and must be scanned.
//
#ifndef STATUS_CORRUPT_LOG_CORRUPTED
#define STATUS_CORRUPT_LOG_CORRUPTED     ((NTSTATUS)0xC000080AL)
#endif//STATUS_CORRUPT_LOG_CORRUPTED

//
// MessageId: STATUS_CORRUPT_LOG_UNAVAILABLE
//
// MessageText:
//
// One of the volume corruption logs is unavailable for being operated on.
//
#ifndef STATUS_CORRUPT_LOG_UNAVAILABLE
#define STATUS_CORRUPT_LOG_UNAVAILABLE   ((NTSTATUS)0xC000080BL)
#endif//STATUS_CORRUPT_LOG_UNAVAILABLE

//
// MessageId: STATUS_CORRUPT_LOG_DELETED_FULL
//
// MessageText:
//
// One of the volume corruption logs was deleted while still having corruption records in them. The volume contains detected corruptions and must be scanned.
//
#ifndef STATUS_CORRUPT_LOG_DELETED_FULL
#define STATUS_CORRUPT_LOG_DELETED_FULL  ((NTSTATUS)0xC000080CL)
#endif//STATUS_CORRUPT_LOG_DELETED_FULL

//
// MessageId: STATUS_CORRUPT_LOG_CLEARED
//
// MessageText:
//
// One of the volume corruption logs was cleared by chkdsk and no longer contains real corruptions.
//
#ifndef STATUS_CORRUPT_LOG_CLEARED
#define STATUS_CORRUPT_LOG_CLEARED       ((NTSTATUS)0xC000080DL)
#endif//STATUS_CORRUPT_LOG_CLEARED

//
// MessageId: STATUS_ORPHAN_NAME_EXHAUSTED
//
// MessageText:
//
// Orphaned files exist on the volume but could not be recovered because no more new names could be created in the recovery directory. Files must be moved from the recovery directory.
//
#ifndef STATUS_ORPHAN_NAME_EXHAUSTED
#define STATUS_ORPHAN_NAME_EXHAUSTED     ((NTSTATUS)0xC000080EL)
#endif//STATUS_ORPHAN_NAME_EXHAUSTED

//
// MessageId: STATUS_PROACTIVE_SCAN_IN_PROGRESS
//
// MessageText:
//
// The operation could not be completed because an instance of Proactive Scanner is currently running.
//
#ifndef STATUS_PROACTIVE_SCAN_IN_PROGRESS
#define STATUS_PROACTIVE_SCAN_IN_PROGRESS ((NTSTATUS)0xC000080FL)
#endif//STATUS_PROACTIVE_SCAN_IN_PROGRESS

//
// MessageId: STATUS_ENCRYPTED_IO_NOT_POSSIBLE
//
// MessageText:
//
// The read or write operation to an encrypted file could not be completed because the file has not been opened for data access.
//
#ifndef STATUS_ENCRYPTED_IO_NOT_POSSIBLE
#define STATUS_ENCRYPTED_IO_NOT_POSSIBLE ((NTSTATUS)0xC0000810L)
#endif//STATUS_ENCRYPTED_IO_NOT_POSSIBLE

//
// MessageId: STATUS_CORRUPT_LOG_UPLEVEL_RECORDS
//
// MessageText:
//
// One of the volume corruption logs comes from a newer version of Windows and contains corruption records. The log will be emptied and reset to the current version, and the volume health state will be updated accordingly.
//
#ifndef STATUS_CORRUPT_LOG_UPLEVEL_RECORDS
#define STATUS_CORRUPT_LOG_UPLEVEL_RECORDS ((NTSTATUS)0xC0000811L)
#endif//STATUS_CORRUPT_LOG_UPLEVEL_RECORDS

//
// MessageId: STATUS_FILE_CHECKED_OUT
//
// MessageText:
//
// This file is checked out or locked for editing by another user.
//
#ifndef STATUS_FILE_CHECKED_OUT
#define STATUS_FILE_CHECKED_OUT          ((NTSTATUS)0xC0000901L)
#endif//STATUS_FILE_CHECKED_OUT

//
// MessageId: STATUS_CHECKOUT_REQUIRED
//
// MessageText:
//
// The file must be checked out before saving changes.
//
#ifndef STATUS_CHECKOUT_REQUIRED
#define STATUS_CHECKOUT_REQUIRED         ((NTSTATUS)0xC0000902L)
#endif//STATUS_CHECKOUT_REQUIRED

//
// MessageId: STATUS_BAD_FILE_TYPE
//
// MessageText:
//
// The file type being saved or retrieved has been blocked.
//
#ifndef STATUS_BAD_FILE_TYPE
#define STATUS_BAD_FILE_TYPE             ((NTSTATUS)0xC0000903L)
#endif//STATUS_BAD_FILE_TYPE

//
// MessageId: STATUS_FILE_TOO_LARGE
//
// MessageText:
//
// The file size exceeds the limit allowed and cannot be saved.
//
#ifndef STATUS_FILE_TOO_LARGE
#define STATUS_FILE_TOO_LARGE            ((NTSTATUS)0xC0000904L)
#endif//STATUS_FILE_TOO_LARGE

//
// MessageId: STATUS_FORMS_AUTH_REQUIRED
//
// MessageText:
//
// Access Denied. Before opening files in this location, you must first browse to the web site and select the option to login automatically.
//
#ifndef STATUS_FORMS_AUTH_REQUIRED
#define STATUS_FORMS_AUTH_REQUIRED       ((NTSTATUS)0xC0000905L)
#endif//STATUS_FORMS_AUTH_REQUIRED

//
// MessageId: STATUS_VIRUS_INFECTED
//
// MessageText:
//
// Operation did not complete successfully because the file contains a virus or potentially unwanted software.
//
#ifndef STATUS_VIRUS_INFECTED
#define STATUS_VIRUS_INFECTED            ((NTSTATUS)0xC0000906L)
#endif//STATUS_VIRUS_INFECTED

//
// MessageId: STATUS_VIRUS_DELETED
//
// MessageText:
//
// This file contains a virus or potentially unwanted software and cannot be opened. Due to the nature of this virus or potentially unwanted software, the file has been removed from this location.
//
#ifndef STATUS_VIRUS_DELETED
#define STATUS_VIRUS_DELETED             ((NTSTATUS)0xC0000907L)
#endif//STATUS_VIRUS_DELETED

//
// MessageId: STATUS_BAD_MCFG_TABLE
//
// MessageText:
//
// The resources required for this device conflict with the MCFG table.
//
#ifndef STATUS_BAD_MCFG_TABLE
#define STATUS_BAD_MCFG_TABLE            ((NTSTATUS)0xC0000908L)
#endif//STATUS_BAD_MCFG_TABLE

//
// MessageId: STATUS_CANNOT_BREAK_OPLOCK
//
// MessageText:
//
// The operation did not complete successfully because it would cause an oplock to be broken. The caller has requested that existing oplocks not be broken.
//
#ifndef STATUS_CANNOT_BREAK_OPLOCK
#define STATUS_CANNOT_BREAK_OPLOCK       ((NTSTATUS)0xC0000909L)
#endif//STATUS_CANNOT_BREAK_OPLOCK

//
// MessageId: STATUS_BAD_KEY
//
// MessageText:
//
// Bad key.
//
#ifndef STATUS_BAD_KEY
#define STATUS_BAD_KEY                   ((NTSTATUS)0xC000090AL)
#endif//STATUS_BAD_KEY

//
// MessageId: STATUS_BAD_DATA
//
// MessageText:
//
// Bad data.
//
#ifndef STATUS_BAD_DATA
#define STATUS_BAD_DATA                  ((NTSTATUS)0xC000090BL)
#endif//STATUS_BAD_DATA

//
// MessageId: STATUS_NO_KEY
//
// MessageText:
//
// Key does not exist.
//
#ifndef STATUS_NO_KEY
#define STATUS_NO_KEY                    ((NTSTATUS)0xC000090CL)
#endif//STATUS_NO_KEY

//
// MessageId: STATUS_FILE_HANDLE_REVOKED
//
// MessageText:
//
// Access to the specified file handle has been revoked.
//
#ifndef STATUS_FILE_HANDLE_REVOKED
#define STATUS_FILE_HANDLE_REVOKED       ((NTSTATUS)0xC0000910L)
#endif//STATUS_FILE_HANDLE_REVOKED

//
// MessageId: STATUS_WOW_ASSERTION
//
// MessageText:
//
// WOW Assertion Error.
//
#ifndef STATUS_WOW_ASSERTION
#define STATUS_WOW_ASSERTION             ((NTSTATUS)0xC0009898L)
#endif//STATUS_WOW_ASSERTION

//
// MessageId: STATUS_INVALID_SIGNATURE
//
// MessageText:
//
// The cryptographic signature is invalid.
//
#ifndef STATUS_INVALID_SIGNATURE
#define STATUS_INVALID_SIGNATURE         ((NTSTATUS)0xC000A000L)
#endif//STATUS_INVALID_SIGNATURE

//
// MessageId: STATUS_HMAC_NOT_SUPPORTED
//
// MessageText:
//
// The cryptographic provider does not support HMAC.
//
#ifndef STATUS_HMAC_NOT_SUPPORTED
#define STATUS_HMAC_NOT_SUPPORTED        ((NTSTATUS)0xC000A001L)
#endif//STATUS_HMAC_NOT_SUPPORTED

//
// MessageId: STATUS_AUTH_TAG_MISMATCH
//
// MessageText:
//
// The computed authentication tag did not match the input authentication tag.
//
#ifndef STATUS_AUTH_TAG_MISMATCH
#define STATUS_AUTH_TAG_MISMATCH         ((NTSTATUS)0xC000A002L)
#endif//STATUS_AUTH_TAG_MISMATCH

//
// MessageId: STATUS_INVALID_STATE_TRANSITION
//
// MessageText:
//
// The requested state transition is invalid and cannot be performed.
//
#ifndef STATUS_INVALID_STATE_TRANSITION
#define STATUS_INVALID_STATE_TRANSITION  ((NTSTATUS)0xC000A003L)
#endif//STATUS_INVALID_STATE_TRANSITION

//
// MessageId: STATUS_INVALID_KERNEL_INFO_VERSION
//
// MessageText:
//
// The supplied kernel information version is invalid.
//
#ifndef STATUS_INVALID_KERNEL_INFO_VERSION
#define STATUS_INVALID_KERNEL_INFO_VERSION ((NTSTATUS)0xC000A004L)
#endif//STATUS_INVALID_KERNEL_INFO_VERSION

//
// MessageId: STATUS_INVALID_PEP_INFO_VERSION
//
// MessageText:
//
// The supplied PEP information version is invalid.
//
#ifndef STATUS_INVALID_PEP_INFO_VERSION
#define STATUS_INVALID_PEP_INFO_VERSION  ((NTSTATUS)0xC000A005L)
#endif//STATUS_INVALID_PEP_INFO_VERSION

//
// MessageId: STATUS_HANDLE_REVOKED
//
// MessageText:
//
// Access to the specified handle has been revoked.
//
#ifndef STATUS_HANDLE_REVOKED
#define STATUS_HANDLE_REVOKED            ((NTSTATUS)0xC000A006L)
#endif//STATUS_HANDLE_REVOKED

//
// MessageId: STATUS_EOF_ON_GHOSTED_RANGE
//
// MessageText:
//
// The file operation will result in the end of file being on a ghosted range.
//
#ifndef STATUS_EOF_ON_GHOSTED_RANGE
#define STATUS_EOF_ON_GHOSTED_RANGE      ((NTSTATUS)0xC000A007L)
#endif//STATUS_EOF_ON_GHOSTED_RANGE

/*++

 MessageId's 0xa010 - 0xa07f (inclusive) are reserved for TCPIP errors.

--*/
//
// MessageId: STATUS_IPSEC_QUEUE_OVERFLOW
//
// MessageText:
//
// The IPSEC queue overflowed.
//
#ifndef STATUS_IPSEC_QUEUE_OVERFLOW
#define STATUS_IPSEC_QUEUE_OVERFLOW      ((NTSTATUS)0xC000A010L)
#endif//STATUS_IPSEC_QUEUE_OVERFLOW

//
// MessageId: STATUS_ND_QUEUE_OVERFLOW
//
// MessageText:
//
// The neighbor discovery queue overflowed.
//
#ifndef STATUS_ND_QUEUE_OVERFLOW
#define STATUS_ND_QUEUE_OVERFLOW         ((NTSTATUS)0xC000A011L)
#endif//STATUS_ND_QUEUE_OVERFLOW

//
// MessageId: STATUS_HOPLIMIT_EXCEEDED
//
// MessageText:
//
// An ICMP hop limit exceeded error was received.
//
#ifndef STATUS_HOPLIMIT_EXCEEDED
#define STATUS_HOPLIMIT_EXCEEDED         ((NTSTATUS)0xC000A012L)
#endif//STATUS_HOPLIMIT_EXCEEDED

//
// MessageId: STATUS_PROTOCOL_NOT_SUPPORTED
//
// MessageText:
//
// The protocol is not installed on the local machine.
//
#ifndef STATUS_PROTOCOL_NOT_SUPPORTED
#define STATUS_PROTOCOL_NOT_SUPPORTED    ((NTSTATUS)0xC000A013L)
#endif//STATUS_PROTOCOL_NOT_SUPPORTED

//
// MessageId: STATUS_FASTPATH_REJECTED
//
// MessageText:
//
// An operation or data has been rejected while on the network fast path.
//
#ifndef STATUS_FASTPATH_REJECTED
#define STATUS_FASTPATH_REJECTED         ((NTSTATUS)0xC000A014L)
#endif//STATUS_FASTPATH_REJECTED

/*++

 MessageId's 0xa014 - 0xa07f (inclusive) are reserved for TCPIP errors.

--*/
//
// MessageId: STATUS_LOST_WRITEBEHIND_DATA_NETWORK_DISCONNECTED
//
// MessageText:
//
// {Delayed Write Failed}
// Windows was unable to save all the data for the file %hs; the data has been lost.
// This error may be caused by network connectivity issues. Please try to save this file elsewhere.
//
#ifndef STATUS_LOST_WRITEBEHIND_DATA_NETWORK_DISCONNECTED
#define STATUS_LOST_WRITEBEHIND_DATA_NETWORK_DISCONNECTED ((NTSTATUS)0xC000A080L)
#endif//STATUS_LOST_WRITEBEHIND_DATA_NETWORK_DISCONNECTED

//
// MessageId: STATUS_LOST_WRITEBEHIND_DATA_NETWORK_SERVER_ERROR
//
// MessageText:
//
// {Delayed Write Failed}
// Windows was unable to save all the data for the file %hs; the data has been lost.
// This error was returned by the server on which the file exists. Please try to save this file elsewhere.
//
#ifndef STATUS_LOST_WRITEBEHIND_DATA_NETWORK_SERVER_ERROR
#define STATUS_LOST_WRITEBEHIND_DATA_NETWORK_SERVER_ERROR ((NTSTATUS)0xC000A081L)
#endif//STATUS_LOST_WRITEBEHIND_DATA_NETWORK_SERVER_ERROR

//
// MessageId: STATUS_LOST_WRITEBEHIND_DATA_LOCAL_DISK_ERROR
//
// MessageText:
//
// {Delayed Write Failed}
// Windows was unable to save all the data for the file %hs; the data has been lost.
// This error may be caused if the device has been removed or the media is write-protected.
//
#ifndef STATUS_LOST_WRITEBEHIND_DATA_LOCAL_DISK_ERROR
#define STATUS_LOST_WRITEBEHIND_DATA_LOCAL_DISK_ERROR ((NTSTATUS)0xC000A082L)
#endif//STATUS_LOST_WRITEBEHIND_DATA_LOCAL_DISK_ERROR

//
// MessageId: STATUS_XML_PARSE_ERROR
//
// MessageText:
//
// Windows was unable to parse the requested XML data.
//
#ifndef STATUS_XML_PARSE_ERROR
#define STATUS_XML_PARSE_ERROR           ((NTSTATUS)0xC000A083L)
#endif//STATUS_XML_PARSE_ERROR

//
// MessageId: STATUS_XMLDSIG_ERROR
//
// MessageText:
//
// An error was encountered while processing an XML digital signature.
//
#ifndef STATUS_XMLDSIG_ERROR
#define STATUS_XMLDSIG_ERROR             ((NTSTATUS)0xC000A084L)
#endif//STATUS_XMLDSIG_ERROR

//
// MessageId: STATUS_WRONG_COMPARTMENT
//
// MessageText:
//
// Indicates that the caller made the connection request in the wrong routing compartment.
//
#ifndef STATUS_WRONG_COMPARTMENT
#define STATUS_WRONG_COMPARTMENT         ((NTSTATUS)0xC000A085L)
#endif//STATUS_WRONG_COMPARTMENT

//
// MessageId: STATUS_AUTHIP_FAILURE
//
// MessageText:
//
// Indicates that there was an AuthIP failure when attempting to connect to the remote host.
//
#ifndef STATUS_AUTHIP_FAILURE
#define STATUS_AUTHIP_FAILURE            ((NTSTATUS)0xC000A086L)
#endif//STATUS_AUTHIP_FAILURE

//
// MessageId: STATUS_DS_OID_MAPPED_GROUP_CANT_HAVE_MEMBERS
//
// MessageText:
//
// OID mapped groups cannot have members.
//
#ifndef STATUS_DS_OID_MAPPED_GROUP_CANT_HAVE_MEMBERS
#define STATUS_DS_OID_MAPPED_GROUP_CANT_HAVE_MEMBERS ((NTSTATUS)0xC000A087L)
#endif//STATUS_DS_OID_MAPPED_GROUP_CANT_HAVE_MEMBERS

//
// MessageId: STATUS_DS_OID_NOT_FOUND
//
// MessageText:
//
// The specified OID cannot be found.
//
#ifndef STATUS_DS_OID_NOT_FOUND
#define STATUS_DS_OID_NOT_FOUND          ((NTSTATUS)0xC000A088L)
#endif//STATUS_DS_OID_NOT_FOUND

//
// MessageId: STATUS_INCORRECT_ACCOUNT_TYPE
//
// MessageText:
//
// The system is not authoritative for the specified account and therefore cannot complete the operation. Please retry the operation using the provider associated with this account. If this is an online provider please use the provider's online site.
//
#ifndef STATUS_INCORRECT_ACCOUNT_TYPE
#define STATUS_INCORRECT_ACCOUNT_TYPE    ((NTSTATUS)0xC000A089L)
#endif//STATUS_INCORRECT_ACCOUNT_TYPE

/*++

 MessageId's 0xa100 - 0xa120 (inclusive) are for the SMB Hash Generation Service.

--*/
//
// MessageId: STATUS_HASH_NOT_SUPPORTED
//
// MessageText:
//
// Hash generation for the specified version and hash type is not enabled on server.
//
#ifndef STATUS_HASH_NOT_SUPPORTED
#define STATUS_HASH_NOT_SUPPORTED        ((NTSTATUS)0xC000A100L)
#endif//STATUS_HASH_NOT_SUPPORTED

//
// MessageId: STATUS_HASH_NOT_PRESENT
//
// MessageText:
//
// The hash requests is not present or not up to date with the current file contents.
//
#ifndef STATUS_HASH_NOT_PRESENT
#define STATUS_HASH_NOT_PRESENT          ((NTSTATUS)0xC000A101L)
#endif//STATUS_HASH_NOT_PRESENT

/*++

 MessageId's 0xa121 - 0xa140 (inclusive) are for GPIO (General Purpose I/O) controller related errors.

--*/
//
// MessageId: STATUS_SECONDARY_IC_PROVIDER_NOT_REGISTERED
//
// MessageText:
//
// The secondary interrupt controller instance that manages the specified interrupt is not registered.
//
#ifndef STATUS_SECONDARY_IC_PROVIDER_NOT_REGISTERED
#define STATUS_SECONDARY_IC_PROVIDER_NOT_REGISTERED ((NTSTATUS)0xC000A121L)
#endif//STATUS_SECONDARY_IC_PROVIDER_NOT_REGISTERED

//
// MessageId: STATUS_GPIO_CLIENT_INFORMATION_INVALID
//
// MessageText:
//
// The information supplied by the GPIO client driver is invalid.
//
#ifndef STATUS_GPIO_CLIENT_INFORMATION_INVALID
#define STATUS_GPIO_CLIENT_INFORMATION_INVALID ((NTSTATUS)0xC000A122L)
#endif//STATUS_GPIO_CLIENT_INFORMATION_INVALID

//
// MessageId: STATUS_GPIO_VERSION_NOT_SUPPORTED
//
// MessageText:
//
// The version specified by the GPIO client driver is not supported.
//
#ifndef STATUS_GPIO_VERSION_NOT_SUPPORTED
#define STATUS_GPIO_VERSION_NOT_SUPPORTED ((NTSTATUS)0xC000A123L)
#endif//STATUS_GPIO_VERSION_NOT_SUPPORTED

//
// MessageId: STATUS_GPIO_INVALID_REGISTRATION_PACKET
//
// MessageText:
//
// The registration packet supplied by the GPIO client driver is not valid.
//
#ifndef STATUS_GPIO_INVALID_REGISTRATION_PACKET
#define STATUS_GPIO_INVALID_REGISTRATION_PACKET ((NTSTATUS)0xC000A124L)
#endif//STATUS_GPIO_INVALID_REGISTRATION_PACKET

//
// MessageId: STATUS_GPIO_OPERATION_DENIED
//
// MessageText:
//
// The requested operation is not suppported for the specified handle.
//
#ifndef STATUS_GPIO_OPERATION_DENIED
#define STATUS_GPIO_OPERATION_DENIED     ((NTSTATUS)0xC000A125L)
#endif//STATUS_GPIO_OPERATION_DENIED

//
// MessageId: STATUS_GPIO_INCOMPATIBLE_CONNECT_MODE
//
// MessageText:
//
// The requested connect mode conflicts with an existing mode on one or more of the specified pins.
//
#ifndef STATUS_GPIO_INCOMPATIBLE_CONNECT_MODE
#define STATUS_GPIO_INCOMPATIBLE_CONNECT_MODE ((NTSTATUS)0xC000A126L)
#endif//STATUS_GPIO_INCOMPATIBLE_CONNECT_MODE

//
// MessageId: STATUS_GPIO_INTERRUPT_ALREADY_UNMASKED
//
// MessageText:
//
// The interrupt requested to be unmasked is not masked.
//
#ifndef STATUS_GPIO_INTERRUPT_ALREADY_UNMASKED
#define STATUS_GPIO_INTERRUPT_ALREADY_UNMASKED ((NTSTATUS)0x8000A127L)
#endif//STATUS_GPIO_INTERRUPT_ALREADY_UNMASKED

/*++

 MessageId's 0xa141 - 0xa160 (inclusive) are for run levels support.

--*/
//
// MessageId: STATUS_CANNOT_SWITCH_RUNLEVEL
//
// MessageText:
//
// The requested run level switch cannot be completed successfully since
// one or more services refused to stop or restart.
//
#ifndef STATUS_CANNOT_SWITCH_RUNLEVEL
#define STATUS_CANNOT_SWITCH_RUNLEVEL    ((NTSTATUS)0xC000A141L)
#endif//STATUS_CANNOT_SWITCH_RUNLEVEL

//
// MessageId: STATUS_INVALID_RUNLEVEL_SETTING
//
// MessageText:
//
// The service has an invalid run level setting. The run level for a service
// must not be higher than the run level of its dependent services.
//
#ifndef STATUS_INVALID_RUNLEVEL_SETTING
#define STATUS_INVALID_RUNLEVEL_SETTING  ((NTSTATUS)0xC000A142L)
#endif//STATUS_INVALID_RUNLEVEL_SETTING

//
// MessageId: STATUS_RUNLEVEL_SWITCH_TIMEOUT
//
// MessageText:
//
// The requested run level switch cannot be completed successfully since
// one or more services will not stop or restart within the specified timeout.
//
#ifndef STATUS_RUNLEVEL_SWITCH_TIMEOUT
#define STATUS_RUNLEVEL_SWITCH_TIMEOUT   ((NTSTATUS)0xC000A143L)
#endif//STATUS_RUNLEVEL_SWITCH_TIMEOUT

//
// MessageId: STATUS_SERVICES_FAILED_AUTOSTART
//
// MessageText:
//
// One or more services failed to start during the service startup phase of a run level switch.
//
#ifndef STATUS_SERVICES_FAILED_AUTOSTART
#define STATUS_SERVICES_FAILED_AUTOSTART ((NTSTATUS)0x4000A144L)
#endif//STATUS_SERVICES_FAILED_AUTOSTART

//
// MessageId: STATUS_RUNLEVEL_SWITCH_AGENT_TIMEOUT
//
// MessageText:
//
// A run level switch agent did not respond within the specified timeout.
//
#ifndef STATUS_RUNLEVEL_SWITCH_AGENT_TIMEOUT
#define STATUS_RUNLEVEL_SWITCH_AGENT_TIMEOUT ((NTSTATUS)0xC000A145L)
#endif//STATUS_RUNLEVEL_SWITCH_AGENT_TIMEOUT

//
// MessageId: STATUS_RUNLEVEL_SWITCH_IN_PROGRESS
//
// MessageText:
//
// A run level switch is currently in progress.
//
#ifndef STATUS_RUNLEVEL_SWITCH_IN_PROGRESS
#define STATUS_RUNLEVEL_SWITCH_IN_PROGRESS ((NTSTATUS)0xC000A146L)
#endif//STATUS_RUNLEVEL_SWITCH_IN_PROGRESS

/*++

 MessageId's 0xa200 - 0xa280 (inclusive) are reserved for app container specific messages.

--*/
//
// MessageId: STATUS_NOT_APPCONTAINER
//
// MessageText:
//
// This operation is only valid in the context of an app container.
//
#ifndef STATUS_NOT_APPCONTAINER
#define STATUS_NOT_APPCONTAINER          ((NTSTATUS)0xC000A200L)
#endif//STATUS_NOT_APPCONTAINER

//
// MessageId: STATUS_NOT_SUPPORTED_IN_APPCONTAINER
//
// MessageText:
//
// This functionality is not supported in the context of an app container.
//
#ifndef STATUS_NOT_SUPPORTED_IN_APPCONTAINER
#define STATUS_NOT_SUPPORTED_IN_APPCONTAINER ((NTSTATUS)0xC000A201L)
#endif//STATUS_NOT_SUPPORTED_IN_APPCONTAINER

//
// MessageId: STATUS_INVALID_PACKAGE_SID_LENGTH
//
// MessageText:
//
// The length of the SID supplied is not a valid length for app container SIDs.
//
#ifndef STATUS_INVALID_PACKAGE_SID_LENGTH
#define STATUS_INVALID_PACKAGE_SID_LENGTH ((NTSTATUS)0xC000A202L)
#endif//STATUS_INVALID_PACKAGE_SID_LENGTH

//
// MessageId: STATUS_LPAC_ACCESS_DENIED
//
// MessageText:
//
// Access to the specified resource has been denied for a less privileged app container.
//
#ifndef STATUS_LPAC_ACCESS_DENIED
#define STATUS_LPAC_ACCESS_DENIED        ((NTSTATUS)0xC000A203L)
#endif//STATUS_LPAC_ACCESS_DENIED

//
// MessageId: STATUS_ADMINLESS_ACCESS_DENIED
//
// MessageText:
//
// Access to the specified resource has been denied for an adminless system.
//
#ifndef STATUS_ADMINLESS_ACCESS_DENIED
#define STATUS_ADMINLESS_ACCESS_DENIED   ((NTSTATUS)0xC000A204L)
#endif//STATUS_ADMINLESS_ACCESS_DENIED

/*++

 MessageId's 0xa281 - 0xa2a0 (inclusive) are reserved for Fast Cache specific messages.

--*/
//
// MessageId: STATUS_APP_DATA_NOT_FOUND
//
// MessageText:
//
// Fast Cache data not found.
//
#ifndef STATUS_APP_DATA_NOT_FOUND
#define STATUS_APP_DATA_NOT_FOUND        ((NTSTATUS)0xC000A281L)
#endif//STATUS_APP_DATA_NOT_FOUND

//
// MessageId: STATUS_APP_DATA_EXPIRED
//
// MessageText:
//
// Fast Cache data expired.
//
#ifndef STATUS_APP_DATA_EXPIRED
#define STATUS_APP_DATA_EXPIRED          ((NTSTATUS)0xC000A282L)
#endif//STATUS_APP_DATA_EXPIRED

//
// MessageId: STATUS_APP_DATA_CORRUPT
//
// MessageText:
//
// Fast Cache data corrupt.
//
#ifndef STATUS_APP_DATA_CORRUPT
#define STATUS_APP_DATA_CORRUPT          ((NTSTATUS)0xC000A283L)
#endif//STATUS_APP_DATA_CORRUPT

//
// MessageId: STATUS_APP_DATA_LIMIT_EXCEEDED
//
// MessageText:
//
// Fast Cache data has exceeded its max size and cannot be updated.
//
#ifndef STATUS_APP_DATA_LIMIT_EXCEEDED
#define STATUS_APP_DATA_LIMIT_EXCEEDED   ((NTSTATUS)0xC000A284L)
#endif//STATUS_APP_DATA_LIMIT_EXCEEDED

//
// MessageId: STATUS_APP_DATA_REBOOT_REQUIRED
//
// MessageText:
//
// Fast Cache has been ReArmed and requires a reboot until it can be updated.
//
#ifndef STATUS_APP_DATA_REBOOT_REQUIRED
#define STATUS_APP_DATA_REBOOT_REQUIRED  ((NTSTATUS)0xC000A285L)
#endif//STATUS_APP_DATA_REBOOT_REQUIRED

/*++

 MessageId's 0xa2a1 - 0xa300 (inclusive) are for File System specific messages.

--*/
//
// MessageId: STATUS_OFFLOAD_READ_FLT_NOT_SUPPORTED
//
// MessageText:
//
// The copy offload read operation is not supported by a filter.
//
#ifndef STATUS_OFFLOAD_READ_FLT_NOT_SUPPORTED
#define STATUS_OFFLOAD_READ_FLT_NOT_SUPPORTED ((NTSTATUS)0xC000A2A1L)
#endif//STATUS_OFFLOAD_READ_FLT_NOT_SUPPORTED

//
// MessageId: STATUS_OFFLOAD_WRITE_FLT_NOT_SUPPORTED
//
// MessageText:
//
// The copy offload write operation is not supported by a filter.
//
#ifndef STATUS_OFFLOAD_WRITE_FLT_NOT_SUPPORTED
#define STATUS_OFFLOAD_WRITE_FLT_NOT_SUPPORTED ((NTSTATUS)0xC000A2A2L)
#endif//STATUS_OFFLOAD_WRITE_FLT_NOT_SUPPORTED

//
// MessageId: STATUS_OFFLOAD_READ_FILE_NOT_SUPPORTED
//
// MessageText:
//
// The copy offload read operation is not supported for the file.
//
#ifndef STATUS_OFFLOAD_READ_FILE_NOT_SUPPORTED
#define STATUS_OFFLOAD_READ_FILE_NOT_SUPPORTED ((NTSTATUS)0xC000A2A3L)
#endif//STATUS_OFFLOAD_READ_FILE_NOT_SUPPORTED

//
// MessageId: STATUS_OFFLOAD_WRITE_FILE_NOT_SUPPORTED
//
// MessageText:
//
// The copy offload write operation is not supported for the file.
//
#ifndef STATUS_OFFLOAD_WRITE_FILE_NOT_SUPPORTED
#define STATUS_OFFLOAD_WRITE_FILE_NOT_SUPPORTED ((NTSTATUS)0xC000A2A4L)
#endif//STATUS_OFFLOAD_WRITE_FILE_NOT_SUPPORTED

//
// MessageId: STATUS_WOF_WIM_HEADER_CORRUPT
//
// MessageText:
//
// The WOF driver encountered a corruption in WIM image's Header.
//
#ifndef STATUS_WOF_WIM_HEADER_CORRUPT
#define STATUS_WOF_WIM_HEADER_CORRUPT    ((NTSTATUS)0xC000A2A5L)
#endif//STATUS_WOF_WIM_HEADER_CORRUPT

//
// MessageId: STATUS_WOF_WIM_RESOURCE_TABLE_CORRUPT
//
// MessageText:
//
// The WOF driver encountered a corruption in WIM image's Resource Table.
//
#ifndef STATUS_WOF_WIM_RESOURCE_TABLE_CORRUPT
#define STATUS_WOF_WIM_RESOURCE_TABLE_CORRUPT ((NTSTATUS)0xC000A2A6L)
#endif//STATUS_WOF_WIM_RESOURCE_TABLE_CORRUPT

//
// MessageId: STATUS_WOF_FILE_RESOURCE_TABLE_CORRUPT
//
// MessageText:
//
// The WOF driver encountered a corruption in the compressed file's Resource Table.
//
#ifndef STATUS_WOF_FILE_RESOURCE_TABLE_CORRUPT
#define STATUS_WOF_FILE_RESOURCE_TABLE_CORRUPT ((NTSTATUS)0xC000A2A7L)
#endif//STATUS_WOF_FILE_RESOURCE_TABLE_CORRUPT

/*++

 MessageId's 0xce00 - 0xceff (inclusive) are for File System virtualization specific messages.

--*/
//
// MessageId: STATUS_FILE_SYSTEM_VIRTUALIZATION_UNAVAILABLE
//
// MessageText:
//
// The provider that supports file system virtualization is temporarily unavailable.
//
#ifndef STATUS_FILE_SYSTEM_VIRTUALIZATION_UNAVAILABLE
#define STATUS_FILE_SYSTEM_VIRTUALIZATION_UNAVAILABLE ((NTSTATUS)0xC000CE01L)
#endif//STATUS_FILE_SYSTEM_VIRTUALIZATION_UNAVAILABLE

//
// MessageId: STATUS_FILE_SYSTEM_VIRTUALIZATION_METADATA_CORRUPT
//
// MessageText:
//
// The metadata for file system virtualization is corrupt and unreadable.
//
#ifndef STATUS_FILE_SYSTEM_VIRTUALIZATION_METADATA_CORRUPT
#define STATUS_FILE_SYSTEM_VIRTUALIZATION_METADATA_CORRUPT ((NTSTATUS)0xC000CE02L)
#endif//STATUS_FILE_SYSTEM_VIRTUALIZATION_METADATA_CORRUPT

//
// MessageId: STATUS_FILE_SYSTEM_VIRTUALIZATION_BUSY
//
// MessageText:
//
// The provider that supports file system virtualization is too busy to complete this operation.
//
#ifndef STATUS_FILE_SYSTEM_VIRTUALIZATION_BUSY
#define STATUS_FILE_SYSTEM_VIRTUALIZATION_BUSY ((NTSTATUS)0xC000CE03L)
#endif//STATUS_FILE_SYSTEM_VIRTUALIZATION_BUSY

//
// MessageId: STATUS_FILE_SYSTEM_VIRTUALIZATION_PROVIDER_UNKNOWN
//
// MessageText:
//
// The provider that supports file system virtualization is unknown.
//
#ifndef STATUS_FILE_SYSTEM_VIRTUALIZATION_PROVIDER_UNKNOWN
#define STATUS_FILE_SYSTEM_VIRTUALIZATION_PROVIDER_UNKNOWN ((NTSTATUS)0xC000CE04L)
#endif//STATUS_FILE_SYSTEM_VIRTUALIZATION_PROVIDER_UNKNOWN

//
// MessageId: STATUS_FILE_SYSTEM_VIRTUALIZATION_INVALID_OPERATION
//
// MessageText:
//
// The virtualization operation is not allowed on the file in its current state.
//
#ifndef STATUS_FILE_SYSTEM_VIRTUALIZATION_INVALID_OPERATION
#define STATUS_FILE_SYSTEM_VIRTUALIZATION_INVALID_OPERATION ((NTSTATUS)0xC000CE05L)
#endif//STATUS_FILE_SYSTEM_VIRTUALIZATION_INVALID_OPERATION

/*++

 MessageId's 0xcf00 - 0xcfff (inclusive) are for Cloud Files specific messages.

--*/
//
// MessageId: STATUS_CLOUD_FILE_SYNC_ROOT_METADATA_CORRUPT
//
// MessageText:
//
// The cloud sync root metadata is corrupted.
//
#ifndef STATUS_CLOUD_FILE_SYNC_ROOT_METADATA_CORRUPT
#define STATUS_CLOUD_FILE_SYNC_ROOT_METADATA_CORRUPT ((NTSTATUS)0xC000CF00L)
#endif//STATUS_CLOUD_FILE_SYNC_ROOT_METADATA_CORRUPT

//
// MessageId: STATUS_CLOUD_FILE_PROVIDER_NOT_RUNNING
//
// MessageText:
//
// The cloud file provider is not running.
//
#ifndef STATUS_CLOUD_FILE_PROVIDER_NOT_RUNNING
#define STATUS_CLOUD_FILE_PROVIDER_NOT_RUNNING ((NTSTATUS)0xC000CF01L)
#endif//STATUS_CLOUD_FILE_PROVIDER_NOT_RUNNING

//
// MessageId: STATUS_CLOUD_FILE_METADATA_CORRUPT
//
// MessageText:
//
// The cloud file metadata is corrupt and unreadable.
//
#ifndef STATUS_CLOUD_FILE_METADATA_CORRUPT
#define STATUS_CLOUD_FILE_METADATA_CORRUPT ((NTSTATUS)0xC000CF02L)
#endif//STATUS_CLOUD_FILE_METADATA_CORRUPT

//
// MessageId: STATUS_CLOUD_FILE_METADATA_TOO_LARGE
//
// MessageText:
//
// The cloud file metadata is too large.
//
#ifndef STATUS_CLOUD_FILE_METADATA_TOO_LARGE
#define STATUS_CLOUD_FILE_METADATA_TOO_LARGE ((NTSTATUS)0xC000CF03L)
#endif//STATUS_CLOUD_FILE_METADATA_TOO_LARGE

//
// MessageId: STATUS_CLOUD_FILE_PROPERTY_BLOB_TOO_LARGE
//
// MessageText:
//
// The cloud file property is too large.
//
#ifndef STATUS_CLOUD_FILE_PROPERTY_BLOB_TOO_LARGE
#define STATUS_CLOUD_FILE_PROPERTY_BLOB_TOO_LARGE ((NTSTATUS)0x8000CF04L)
#endif//STATUS_CLOUD_FILE_PROPERTY_BLOB_TOO_LARGE

//
// MessageId: STATUS_CLOUD_FILE_TOO_MANY_PROPERTY_BLOBS
//
// MessageText:
//
// The maximum number of cloud file properties has been reached.
//
#ifndef STATUS_CLOUD_FILE_TOO_MANY_PROPERTY_BLOBS
#define STATUS_CLOUD_FILE_TOO_MANY_PROPERTY_BLOBS ((NTSTATUS)0x8000CF05L)
#endif//STATUS_CLOUD_FILE_TOO_MANY_PROPERTY_BLOBS

//
// MessageId: STATUS_CLOUD_FILE_PROPERTY_VERSION_NOT_SUPPORTED
//
// MessageText:
//
// The version of the cloud file property store is not supported.
//
#ifndef STATUS_CLOUD_FILE_PROPERTY_VERSION_NOT_SUPPORTED
#define STATUS_CLOUD_FILE_PROPERTY_VERSION_NOT_SUPPORTED ((NTSTATUS)0xC000CF06L)
#endif//STATUS_CLOUD_FILE_PROPERTY_VERSION_NOT_SUPPORTED

//
// MessageId: STATUS_NOT_A_CLOUD_FILE
//
// MessageText:
//
// The file is not a cloud file.
//
#ifndef STATUS_NOT_A_CLOUD_FILE
#define STATUS_NOT_A_CLOUD_FILE          ((NTSTATUS)0xC000CF07L)
#endif//STATUS_NOT_A_CLOUD_FILE

//
// MessageId: STATUS_CLOUD_FILE_NOT_IN_SYNC
//
// MessageText:
//
// The file is not in sync with the cloud.
//
#ifndef STATUS_CLOUD_FILE_NOT_IN_SYNC
#define STATUS_CLOUD_FILE_NOT_IN_SYNC    ((NTSTATUS)0xC000CF08L)
#endif//STATUS_CLOUD_FILE_NOT_IN_SYNC

//
// MessageId: STATUS_CLOUD_FILE_ALREADY_CONNECTED
//
// MessageText:
//
// The cloud sync root is already connected with another cloud sync provider.
//
#ifndef STATUS_CLOUD_FILE_ALREADY_CONNECTED
#define STATUS_CLOUD_FILE_ALREADY_CONNECTED ((NTSTATUS)0xC000CF09L)
#endif//STATUS_CLOUD_FILE_ALREADY_CONNECTED

//
// MessageId: STATUS_CLOUD_FILE_NOT_SUPPORTED
//
// MessageText:
//
// The operation is not supported by the cloud sync provider.
//
#ifndef STATUS_CLOUD_FILE_NOT_SUPPORTED
#define STATUS_CLOUD_FILE_NOT_SUPPORTED  ((NTSTATUS)0xC000CF0AL)
#endif//STATUS_CLOUD_FILE_NOT_SUPPORTED

//
// MessageId: STATUS_CLOUD_FILE_INVALID_REQUEST
//
// MessageText:
//
// The cloud operation is invalid.
//
#ifndef STATUS_CLOUD_FILE_INVALID_REQUEST
#define STATUS_CLOUD_FILE_INVALID_REQUEST ((NTSTATUS)0xC000CF0BL)
#endif//STATUS_CLOUD_FILE_INVALID_REQUEST

//
// MessageId: STATUS_CLOUD_FILE_READ_ONLY_VOLUME
//
// MessageText:
//
// The cloud operation is not supported on a read-only volume.
//
#ifndef STATUS_CLOUD_FILE_READ_ONLY_VOLUME
#define STATUS_CLOUD_FILE_READ_ONLY_VOLUME ((NTSTATUS)0xC000CF0CL)
#endif//STATUS_CLOUD_FILE_READ_ONLY_VOLUME

//
// MessageId: STATUS_CLOUD_FILE_CONNECTED_PROVIDER_ONLY
//
// MessageText:
//
// The operation is reserved for a connected cloud sync provider.
//
#ifndef STATUS_CLOUD_FILE_CONNECTED_PROVIDER_ONLY
#define STATUS_CLOUD_FILE_CONNECTED_PROVIDER_ONLY ((NTSTATUS)0xC000CF0DL)
#endif//STATUS_CLOUD_FILE_CONNECTED_PROVIDER_ONLY

//
// MessageId: STATUS_CLOUD_FILE_VALIDATION_FAILED
//
// MessageText:
//
// The cloud sync provider failed to validate the downloaded data.
//
#ifndef STATUS_CLOUD_FILE_VALIDATION_FAILED
#define STATUS_CLOUD_FILE_VALIDATION_FAILED ((NTSTATUS)0xC000CF0EL)
#endif//STATUS_CLOUD_FILE_VALIDATION_FAILED

//
// MessageId: STATUS_CLOUD_FILE_AUTHENTICATION_FAILED
//
// MessageText:
//
// The cloud sync provider failed user authentication.
//
#ifndef STATUS_CLOUD_FILE_AUTHENTICATION_FAILED
#define STATUS_CLOUD_FILE_AUTHENTICATION_FAILED ((NTSTATUS)0xC000CF0FL)
#endif//STATUS_CLOUD_FILE_AUTHENTICATION_FAILED

//
// MessageId: STATUS_CLOUD_FILE_INSUFFICIENT_RESOURCES
//
// MessageText:
//
// The cloud sync provider failed to perform the operation due to low system resources.
//
#ifndef STATUS_CLOUD_FILE_INSUFFICIENT_RESOURCES
#define STATUS_CLOUD_FILE_INSUFFICIENT_RESOURCES ((NTSTATUS)0xC000CF10L)
#endif//STATUS_CLOUD_FILE_INSUFFICIENT_RESOURCES

//
// MessageId: STATUS_CLOUD_FILE_NETWORK_UNAVAILABLE
//
// MessageText:
//
// The cloud sync provider failed to perform the operation due to network being unavailable.
//
#ifndef STATUS_CLOUD_FILE_NETWORK_UNAVAILABLE
#define STATUS_CLOUD_FILE_NETWORK_UNAVAILABLE ((NTSTATUS)0xC000CF11L)
#endif//STATUS_CLOUD_FILE_NETWORK_UNAVAILABLE

//
// MessageId: STATUS_CLOUD_FILE_UNSUCCESSFUL
//
// MessageText:
//
// The cloud operation was unsuccessful.
//
#ifndef STATUS_CLOUD_FILE_UNSUCCESSFUL
#define STATUS_CLOUD_FILE_UNSUCCESSFUL   ((NTSTATUS)0xC000CF12L)
#endif//STATUS_CLOUD_FILE_UNSUCCESSFUL

//
// MessageId: STATUS_CLOUD_FILE_NOT_UNDER_SYNC_ROOT
//
// MessageText:
//
// The operation is only supported on files under a cloud sync root.
//
#ifndef STATUS_CLOUD_FILE_NOT_UNDER_SYNC_ROOT
#define STATUS_CLOUD_FILE_NOT_UNDER_SYNC_ROOT ((NTSTATUS)0xC000CF13L)
#endif//STATUS_CLOUD_FILE_NOT_UNDER_SYNC_ROOT

//
// MessageId: STATUS_CLOUD_FILE_IN_USE
//
// MessageText:
//
// The operation cannot be performed on cloud files in use.
//
#ifndef STATUS_CLOUD_FILE_IN_USE
#define STATUS_CLOUD_FILE_IN_USE         ((NTSTATUS)0xC000CF14L)
#endif//STATUS_CLOUD_FILE_IN_USE

//
// MessageId: STATUS_CLOUD_FILE_PINNED
//
// MessageText:
//
// The operation cannot be performed on pinned cloud files.
//
#ifndef STATUS_CLOUD_FILE_PINNED
#define STATUS_CLOUD_FILE_PINNED         ((NTSTATUS)0xC000CF15L)
#endif//STATUS_CLOUD_FILE_PINNED

//
// MessageId: STATUS_CLOUD_FILE_REQUEST_ABORTED
//
// MessageText:
//
// The cloud operation was aborted.
//
#ifndef STATUS_CLOUD_FILE_REQUEST_ABORTED
#define STATUS_CLOUD_FILE_REQUEST_ABORTED ((NTSTATUS)0xC000CF16L)
#endif//STATUS_CLOUD_FILE_REQUEST_ABORTED

//
// MessageId: STATUS_CLOUD_FILE_PROPERTY_CORRUPT
//
// MessageText:
//
// The cloud file's property store is corrupt.
//
#ifndef STATUS_CLOUD_FILE_PROPERTY_CORRUPT
#define STATUS_CLOUD_FILE_PROPERTY_CORRUPT ((NTSTATUS)0xC000CF17L)
#endif//STATUS_CLOUD_FILE_PROPERTY_CORRUPT

//
// MessageId: STATUS_CLOUD_FILE_ACCESS_DENIED
//
// MessageText:
//
// Access to the cloud file is denied.
//
#ifndef STATUS_CLOUD_FILE_ACCESS_DENIED
#define STATUS_CLOUD_FILE_ACCESS_DENIED  ((NTSTATUS)0xC000CF18L)
#endif//STATUS_CLOUD_FILE_ACCESS_DENIED

//
// MessageId: STATUS_CLOUD_FILE_INCOMPATIBLE_HARDLINKS
//
// MessageText:
//
// The cloud operation cannot be performed on a file with incompatible hardlinks.
//
#ifndef STATUS_CLOUD_FILE_INCOMPATIBLE_HARDLINKS
#define STATUS_CLOUD_FILE_INCOMPATIBLE_HARDLINKS ((NTSTATUS)0xC000CF19L)
#endif//STATUS_CLOUD_FILE_INCOMPATIBLE_HARDLINKS

//
// MessageId: STATUS_CLOUD_FILE_PROPERTY_LOCK_CONFLICT
//
// MessageText:
//
// The operation failed due to a conflicting cloud file property lock.
//
#ifndef STATUS_CLOUD_FILE_PROPERTY_LOCK_CONFLICT
#define STATUS_CLOUD_FILE_PROPERTY_LOCK_CONFLICT ((NTSTATUS)0xC000CF1AL)
#endif//STATUS_CLOUD_FILE_PROPERTY_LOCK_CONFLICT

//
// MessageId: STATUS_CLOUD_FILE_REQUEST_CANCELED
//
// MessageText:
//
// The cloud operation was canceled by user.
//
#ifndef STATUS_CLOUD_FILE_REQUEST_CANCELED
#define STATUS_CLOUD_FILE_REQUEST_CANCELED ((NTSTATUS)0xC000CF1BL)
#endif//STATUS_CLOUD_FILE_REQUEST_CANCELED

//
// MessageId: STATUS_CLOUD_FILE_PROVIDER_TERMINATED
//
// MessageText:
//
// The cloud file provider exited unexpectedly.
//
#ifndef STATUS_CLOUD_FILE_PROVIDER_TERMINATED
#define STATUS_CLOUD_FILE_PROVIDER_TERMINATED ((NTSTATUS)0xC000CF1DL)
#endif//STATUS_CLOUD_FILE_PROVIDER_TERMINATED

//
// MessageId: STATUS_NOT_A_CLOUD_SYNC_ROOT
//
// MessageText:
//
// The file is not a cloud sync root.
//
#ifndef STATUS_NOT_A_CLOUD_SYNC_ROOT
#define STATUS_NOT_A_CLOUD_SYNC_ROOT     ((NTSTATUS)0xC000CF1EL)
#endif//STATUS_NOT_A_CLOUD_SYNC_ROOT

/*++

 End of Cloud Files specific messages.

--*/

//     **** New SYSTEM error codes can be inserted here ****


//
//  Debugger error values
//

//
// MessageId: DBG_NO_STATE_CHANGE
//
// MessageText:
//
// Debugger did not perform a state change.
//
#ifndef DBG_NO_STATE_CHANGE
#define DBG_NO_STATE_CHANGE              ((NTSTATUS)0xC0010001L)
#endif//DBG_NO_STATE_CHANGE

//
// MessageId: DBG_APP_NOT_IDLE
//
// MessageText:
//
// Debugger has found the application is not idle.
//
#ifndef DBG_APP_NOT_IDLE
#define DBG_APP_NOT_IDLE                 ((NTSTATUS)0xC0010002L)
#endif//DBG_APP_NOT_IDLE


//
//  RPC error values
//

//
// MessageId: RPC_NT_INVALID_STRING_BINDING
//
// MessageText:
//
// The string binding is invalid.
//
#ifndef RPC_NT_INVALID_STRING_BINDING
#define RPC_NT_INVALID_STRING_BINDING    ((NTSTATUS)0xC0020001L)
#endif//RPC_NT_INVALID_STRING_BINDING

//
// MessageId: RPC_NT_WRONG_KIND_OF_BINDING
//
// MessageText:
//
// The binding handle is not the correct type.
//
#ifndef RPC_NT_WRONG_KIND_OF_BINDING
#define RPC_NT_WRONG_KIND_OF_BINDING     ((NTSTATUS)0xC0020002L)
#endif//RPC_NT_WRONG_KIND_OF_BINDING

//
// MessageId: RPC_NT_INVALID_BINDING
//
// MessageText:
//
// The binding handle is invalid.
//
#ifndef RPC_NT_INVALID_BINDING
#define RPC_NT_INVALID_BINDING           ((NTSTATUS)0xC0020003L)
#endif//RPC_NT_INVALID_BINDING

//
// MessageId: RPC_NT_PROTSEQ_NOT_SUPPORTED
//
// MessageText:
//
// The RPC protocol sequence is not supported.
//
#ifndef RPC_NT_PROTSEQ_NOT_SUPPORTED
#define RPC_NT_PROTSEQ_NOT_SUPPORTED     ((NTSTATUS)0xC0020004L)
#endif//RPC_NT_PROTSEQ_NOT_SUPPORTED

//
// MessageId: RPC_NT_INVALID_RPC_PROTSEQ
//
// MessageText:
//
// The RPC protocol sequence is invalid.
//
#ifndef RPC_NT_INVALID_RPC_PROTSEQ
#define RPC_NT_INVALID_RPC_PROTSEQ       ((NTSTATUS)0xC0020005L)
#endif//RPC_NT_INVALID_RPC_PROTSEQ

//
// MessageId: RPC_NT_INVALID_STRING_UUID
//
// MessageText:
//
// The string UUID is invalid.
//
#ifndef RPC_NT_INVALID_STRING_UUID
#define RPC_NT_INVALID_STRING_UUID       ((NTSTATUS)0xC0020006L)
#endif//RPC_NT_INVALID_STRING_UUID

//
// MessageId: RPC_NT_INVALID_ENDPOINT_FORMAT
//
// MessageText:
//
// The endpoint format is invalid.
//
#ifndef RPC_NT_INVALID_ENDPOINT_FORMAT
#define RPC_NT_INVALID_ENDPOINT_FORMAT   ((NTSTATUS)0xC0020007L)
#endif//RPC_NT_INVALID_ENDPOINT_FORMAT

//
// MessageId: RPC_NT_INVALID_NET_ADDR
//
// MessageText:
//
// The network address is invalid.
//
#ifndef RPC_NT_INVALID_NET_ADDR
#define RPC_NT_INVALID_NET_ADDR          ((NTSTATUS)0xC0020008L)
#endif//RPC_NT_INVALID_NET_ADDR

//
// MessageId: RPC_NT_NO_ENDPOINT_FOUND
//
// MessageText:
//
// No endpoint was found.
//
#ifndef RPC_NT_NO_ENDPOINT_FOUND
#define RPC_NT_NO_ENDPOINT_FOUND         ((NTSTATUS)0xC0020009L)
#endif//RPC_NT_NO_ENDPOINT_FOUND

//
// MessageId: RPC_NT_INVALID_TIMEOUT
//
// MessageText:
//
// The timeout value is invalid.
//
#ifndef RPC_NT_INVALID_TIMEOUT
#define RPC_NT_INVALID_TIMEOUT           ((NTSTATUS)0xC002000AL)
#endif//RPC_NT_INVALID_TIMEOUT

//
// MessageId: RPC_NT_OBJECT_NOT_FOUND
//
// MessageText:
//
// The object UUID was not found.
//
#ifndef RPC_NT_OBJECT_NOT_FOUND
#define RPC_NT_OBJECT_NOT_FOUND          ((NTSTATUS)0xC002000BL)
#endif//RPC_NT_OBJECT_NOT_FOUND

//
// MessageId: RPC_NT_ALREADY_REGISTERED
//
// MessageText:
//
// The object UUID has already been registered.
//
#ifndef RPC_NT_ALREADY_REGISTERED
#define RPC_NT_ALREADY_REGISTERED        ((NTSTATUS)0xC002000CL)
#endif//RPC_NT_ALREADY_REGISTERED

//
// MessageId: RPC_NT_TYPE_ALREADY_REGISTERED
//
// MessageText:
//
// The type UUID has already been registered.
//
#ifndef RPC_NT_TYPE_ALREADY_REGISTERED
#define RPC_NT_TYPE_ALREADY_REGISTERED   ((NTSTATUS)0xC002000DL)
#endif//RPC_NT_TYPE_ALREADY_REGISTERED

//
// MessageId: RPC_NT_ALREADY_LISTENING
//
// MessageText:
//
// The RPC server is already listening.
//
#ifndef RPC_NT_ALREADY_LISTENING
#define RPC_NT_ALREADY_LISTENING         ((NTSTATUS)0xC002000EL)
#endif//RPC_NT_ALREADY_LISTENING

//
// MessageId: RPC_NT_NO_PROTSEQS_REGISTERED
//
// MessageText:
//
// No protocol sequences have been registered.
//
#ifndef RPC_NT_NO_PROTSEQS_REGISTERED
#define RPC_NT_NO_PROTSEQS_REGISTERED    ((NTSTATUS)0xC002000FL)
#endif//RPC_NT_NO_PROTSEQS_REGISTERED

//
// MessageId: RPC_NT_NOT_LISTENING
//
// MessageText:
//
// The RPC server is not listening.
//
#ifndef RPC_NT_NOT_LISTENING
#define RPC_NT_NOT_LISTENING             ((NTSTATUS)0xC0020010L)
#endif//RPC_NT_NOT_LISTENING

//
// MessageId: RPC_NT_UNKNOWN_MGR_TYPE
//
// MessageText:
//
// The manager type is unknown.
//
#ifndef RPC_NT_UNKNOWN_MGR_TYPE
#define RPC_NT_UNKNOWN_MGR_TYPE          ((NTSTATUS)0xC0020011L)
#endif//RPC_NT_UNKNOWN_MGR_TYPE

//
// MessageId: RPC_NT_UNKNOWN_IF
//
// MessageText:
//
// The interface is unknown.
//
#ifndef RPC_NT_UNKNOWN_IF
#define RPC_NT_UNKNOWN_IF                ((NTSTATUS)0xC0020012L)
#endif//RPC_NT_UNKNOWN_IF

//
// MessageId: RPC_NT_NO_BINDINGS
//
// MessageText:
//
// There are no bindings.
//
#ifndef RPC_NT_NO_BINDINGS
#define RPC_NT_NO_BINDINGS               ((NTSTATUS)0xC0020013L)
#endif//RPC_NT_NO_BINDINGS

//
// MessageId: RPC_NT_NO_PROTSEQS
//
// MessageText:
//
// There are no protocol sequences.
//
#ifndef RPC_NT_NO_PROTSEQS
#define RPC_NT_NO_PROTSEQS               ((NTSTATUS)0xC0020014L)
#endif//RPC_NT_NO_PROTSEQS

//
// MessageId: RPC_NT_CANT_CREATE_ENDPOINT
//
// MessageText:
//
// The endpoint cannot be created.
//
#ifndef RPC_NT_CANT_CREATE_ENDPOINT
#define RPC_NT_CANT_CREATE_ENDPOINT      ((NTSTATUS)0xC0020015L)
#endif//RPC_NT_CANT_CREATE_ENDPOINT

//
// MessageId: RPC_NT_OUT_OF_RESOURCES
//
// MessageText:
//
// Not enough resources are available to complete this operation.
//
#ifndef RPC_NT_OUT_OF_RESOURCES
#define RPC_NT_OUT_OF_RESOURCES          ((NTSTATUS)0xC0020016L)
#endif//RPC_NT_OUT_OF_RESOURCES

//
// MessageId: RPC_NT_SERVER_UNAVAILABLE
//
// MessageText:
//
// The RPC server is unavailable.
//
#ifndef RPC_NT_SERVER_UNAVAILABLE
#define RPC_NT_SERVER_UNAVAILABLE        ((NTSTATUS)0xC0020017L)
#endif//RPC_NT_SERVER_UNAVAILABLE

//
// MessageId: RPC_NT_SERVER_TOO_BUSY
//
// MessageText:
//
// The RPC server is too busy to complete this operation.
//
#ifndef RPC_NT_SERVER_TOO_BUSY
#define RPC_NT_SERVER_TOO_BUSY           ((NTSTATUS)0xC0020018L)
#endif//RPC_NT_SERVER_TOO_BUSY

//
// MessageId: RPC_NT_INVALID_NETWORK_OPTIONS
//
// MessageText:
//
// The network options are invalid.
//
#ifndef RPC_NT_INVALID_NETWORK_OPTIONS
#define RPC_NT_INVALID_NETWORK_OPTIONS   ((NTSTATUS)0xC0020019L)
#endif//RPC_NT_INVALID_NETWORK_OPTIONS

//
// MessageId: RPC_NT_NO_CALL_ACTIVE
//
// MessageText:
//
// There are no remote procedure calls active on this thread.
//
#ifndef RPC_NT_NO_CALL_ACTIVE
#define RPC_NT_NO_CALL_ACTIVE            ((NTSTATUS)0xC002001AL)
#endif//RPC_NT_NO_CALL_ACTIVE

//
// MessageId: RPC_NT_CALL_FAILED
//
// MessageText:
//
// The remote procedure call failed.
//
#ifndef RPC_NT_CALL_FAILED
#define RPC_NT_CALL_FAILED               ((NTSTATUS)0xC002001BL)
#endif//RPC_NT_CALL_FAILED

//
// MessageId: RPC_NT_CALL_FAILED_DNE
//
// MessageText:
//
// The remote procedure call failed and did not execute.
//
#ifndef RPC_NT_CALL_FAILED_DNE
#define RPC_NT_CALL_FAILED_DNE           ((NTSTATUS)0xC002001CL)
#endif//RPC_NT_CALL_FAILED_DNE

//
// MessageId: RPC_NT_PROTOCOL_ERROR
//
// MessageText:
//
// An RPC protocol error occurred.
//
#ifndef RPC_NT_PROTOCOL_ERROR
#define RPC_NT_PROTOCOL_ERROR            ((NTSTATUS)0xC002001DL)
#endif//RPC_NT_PROTOCOL_ERROR

//
// MessageId: RPC_NT_UNSUPPORTED_TRANS_SYN
//
// MessageText:
//
// The transfer syntax is not supported by the RPC server.
//
#ifndef RPC_NT_UNSUPPORTED_TRANS_SYN
#define RPC_NT_UNSUPPORTED_TRANS_SYN     ((NTSTATUS)0xC002001FL)
#endif//RPC_NT_UNSUPPORTED_TRANS_SYN

//
// MessageId: RPC_NT_UNSUPPORTED_TYPE
//
// MessageText:
//
// The type UUID is not supported.
//
#ifndef RPC_NT_UNSUPPORTED_TYPE
#define RPC_NT_UNSUPPORTED_TYPE          ((NTSTATUS)0xC0020021L)
#endif//RPC_NT_UNSUPPORTED_TYPE

//
// MessageId: RPC_NT_INVALID_TAG
//
// MessageText:
//
// The tag is invalid.
//
#ifndef RPC_NT_INVALID_TAG
#define RPC_NT_INVALID_TAG               ((NTSTATUS)0xC0020022L)
#endif//RPC_NT_INVALID_TAG

//
// MessageId: RPC_NT_INVALID_BOUND
//
// MessageText:
//
// The array bounds are invalid.
//
#ifndef RPC_NT_INVALID_BOUND
#define RPC_NT_INVALID_BOUND             ((NTSTATUS)0xC0020023L)
#endif//RPC_NT_INVALID_BOUND

//
// MessageId: RPC_NT_NO_ENTRY_NAME
//
// MessageText:
//
// The binding does not contain an entry name.
//
#ifndef RPC_NT_NO_ENTRY_NAME
#define RPC_NT_NO_ENTRY_NAME             ((NTSTATUS)0xC0020024L)
#endif//RPC_NT_NO_ENTRY_NAME

//
// MessageId: RPC_NT_INVALID_NAME_SYNTAX
//
// MessageText:
//
// The name syntax is invalid.
//
#ifndef RPC_NT_INVALID_NAME_SYNTAX
#define RPC_NT_INVALID_NAME_SYNTAX       ((NTSTATUS)0xC0020025L)
#endif//RPC_NT_INVALID_NAME_SYNTAX

//
// MessageId: RPC_NT_UNSUPPORTED_NAME_SYNTAX
//
// MessageText:
//
// The name syntax is not supported.
//
#ifndef RPC_NT_UNSUPPORTED_NAME_SYNTAX
#define RPC_NT_UNSUPPORTED_NAME_SYNTAX   ((NTSTATUS)0xC0020026L)
#endif//RPC_NT_UNSUPPORTED_NAME_SYNTAX

//
// MessageId: RPC_NT_UUID_NO_ADDRESS
//
// MessageText:
//
// No network address is available to use to construct a UUID.
//
#ifndef RPC_NT_UUID_NO_ADDRESS
#define RPC_NT_UUID_NO_ADDRESS           ((NTSTATUS)0xC0020028L)
#endif//RPC_NT_UUID_NO_ADDRESS

//
// MessageId: RPC_NT_DUPLICATE_ENDPOINT
//
// MessageText:
//
// The endpoint is a duplicate.
//
#ifndef RPC_NT_DUPLICATE_ENDPOINT
#define RPC_NT_DUPLICATE_ENDPOINT        ((NTSTATUS)0xC0020029L)
#endif//RPC_NT_DUPLICATE_ENDPOINT

//
// MessageId: RPC_NT_UNKNOWN_AUTHN_TYPE
//
// MessageText:
//
// The authentication type is unknown.
//
#ifndef RPC_NT_UNKNOWN_AUTHN_TYPE
#define RPC_NT_UNKNOWN_AUTHN_TYPE        ((NTSTATUS)0xC002002AL)
#endif//RPC_NT_UNKNOWN_AUTHN_TYPE

//
// MessageId: RPC_NT_MAX_CALLS_TOO_SMALL
//
// MessageText:
//
// The maximum number of calls is too small.
//
#ifndef RPC_NT_MAX_CALLS_TOO_SMALL
#define RPC_NT_MAX_CALLS_TOO_SMALL       ((NTSTATUS)0xC002002BL)
#endif//RPC_NT_MAX_CALLS_TOO_SMALL

//
// MessageId: RPC_NT_STRING_TOO_LONG
//
// MessageText:
//
// The string is too long.
//
#ifndef RPC_NT_STRING_TOO_LONG
#define RPC_NT_STRING_TOO_LONG           ((NTSTATUS)0xC002002CL)
#endif//RPC_NT_STRING_TOO_LONG

//
// MessageId: RPC_NT_PROTSEQ_NOT_FOUND
//
// MessageText:
//
// The RPC protocol sequence was not found.
//
#ifndef RPC_NT_PROTSEQ_NOT_FOUND
#define RPC_NT_PROTSEQ_NOT_FOUND         ((NTSTATUS)0xC002002DL)
#endif//RPC_NT_PROTSEQ_NOT_FOUND

//
// MessageId: RPC_NT_PROCNUM_OUT_OF_RANGE
//
// MessageText:
//
// The procedure number is out of range.
//
#ifndef RPC_NT_PROCNUM_OUT_OF_RANGE
#define RPC_NT_PROCNUM_OUT_OF_RANGE      ((NTSTATUS)0xC002002EL)
#endif//RPC_NT_PROCNUM_OUT_OF_RANGE

//
// MessageId: RPC_NT_BINDING_HAS_NO_AUTH
//
// MessageText:
//
// The binding does not contain any authentication information.
//
#ifndef RPC_NT_BINDING_HAS_NO_AUTH
#define RPC_NT_BINDING_HAS_NO_AUTH       ((NTSTATUS)0xC002002FL)
#endif//RPC_NT_BINDING_HAS_NO_AUTH

//
// MessageId: RPC_NT_UNKNOWN_AUTHN_SERVICE
//
// MessageText:
//
// The authentication service is unknown.
//
#ifndef RPC_NT_UNKNOWN_AUTHN_SERVICE
#define RPC_NT_UNKNOWN_AUTHN_SERVICE     ((NTSTATUS)0xC0020030L)
#endif//RPC_NT_UNKNOWN_AUTHN_SERVICE

//
// MessageId: RPC_NT_UNKNOWN_AUTHN_LEVEL
//
// MessageText:
//
// The authentication level is unknown.
//
#ifndef RPC_NT_UNKNOWN_AUTHN_LEVEL
#define RPC_NT_UNKNOWN_AUTHN_LEVEL       ((NTSTATUS)0xC0020031L)
#endif//RPC_NT_UNKNOWN_AUTHN_LEVEL

//
// MessageId: RPC_NT_INVALID_AUTH_IDENTITY
//
// MessageText:
//
// The security context is invalid.
//
#ifndef RPC_NT_INVALID_AUTH_IDENTITY
#define RPC_NT_INVALID_AUTH_IDENTITY     ((NTSTATUS)0xC0020032L)
#endif//RPC_NT_INVALID_AUTH_IDENTITY

//
// MessageId: RPC_NT_UNKNOWN_AUTHZ_SERVICE
//
// MessageText:
//
// The authorization service is unknown.
//
#ifndef RPC_NT_UNKNOWN_AUTHZ_SERVICE
#define RPC_NT_UNKNOWN_AUTHZ_SERVICE     ((NTSTATUS)0xC0020033L)
#endif//RPC_NT_UNKNOWN_AUTHZ_SERVICE

//
// MessageId: EPT_NT_INVALID_ENTRY
//
// MessageText:
//
// The entry is invalid.
//
#define EPT_NT_INVALID_ENTRY             ((NTSTATUS)0xC0020034L)

//
// MessageId: EPT_NT_CANT_PERFORM_OP
//
// MessageText:
//
// The operation cannot be performed.
//
#define EPT_NT_CANT_PERFORM_OP           ((NTSTATUS)0xC0020035L)

//
// MessageId: EPT_NT_NOT_REGISTERED
//
// MessageText:
//
// There are no more endpoints available from the endpoint mapper.
//
#define EPT_NT_NOT_REGISTERED            ((NTSTATUS)0xC0020036L)

//
// MessageId: RPC_NT_NOTHING_TO_EXPORT
//
// MessageText:
//
// No interfaces have been exported.
//
#ifndef RPC_NT_NOTHING_TO_EXPORT
#define RPC_NT_NOTHING_TO_EXPORT         ((NTSTATUS)0xC0020037L)
#endif//RPC_NT_NOTHING_TO_EXPORT

//
// MessageId: RPC_NT_INCOMPLETE_NAME
//
// MessageText:
//
// The entry name is incomplete.
//
#ifndef RPC_NT_INCOMPLETE_NAME
#define RPC_NT_INCOMPLETE_NAME           ((NTSTATUS)0xC0020038L)
#endif//RPC_NT_INCOMPLETE_NAME

//
// MessageId: RPC_NT_INVALID_VERS_OPTION
//
// MessageText:
//
// The version option is invalid.
//
#ifndef RPC_NT_INVALID_VERS_OPTION
#define RPC_NT_INVALID_VERS_OPTION       ((NTSTATUS)0xC0020039L)
#endif//RPC_NT_INVALID_VERS_OPTION

//
// MessageId: RPC_NT_NO_MORE_MEMBERS
//
// MessageText:
//
// There are no more members.
//
#ifndef RPC_NT_NO_MORE_MEMBERS
#define RPC_NT_NO_MORE_MEMBERS           ((NTSTATUS)0xC002003AL)
#endif//RPC_NT_NO_MORE_MEMBERS

//
// MessageId: RPC_NT_NOT_ALL_OBJS_UNEXPORTED
//
// MessageText:
//
// There is nothing to unexport.
//
#ifndef RPC_NT_NOT_ALL_OBJS_UNEXPORTED
#define RPC_NT_NOT_ALL_OBJS_UNEXPORTED   ((NTSTATUS)0xC002003BL)
#endif//RPC_NT_NOT_ALL_OBJS_UNEXPORTED

//
// MessageId: RPC_NT_INTERFACE_NOT_FOUND
//
// MessageText:
//
// The interface was not found.
//
#ifndef RPC_NT_INTERFACE_NOT_FOUND
#define RPC_NT_INTERFACE_NOT_FOUND       ((NTSTATUS)0xC002003CL)
#endif//RPC_NT_INTERFACE_NOT_FOUND

//
// MessageId: RPC_NT_ENTRY_ALREADY_EXISTS
//
// MessageText:
//
// The entry already exists.
//
#ifndef RPC_NT_ENTRY_ALREADY_EXISTS
#define RPC_NT_ENTRY_ALREADY_EXISTS      ((NTSTATUS)0xC002003DL)
#endif//RPC_NT_ENTRY_ALREADY_EXISTS

//
// MessageId: RPC_NT_ENTRY_NOT_FOUND
//
// MessageText:
//
// The entry is not found.
//
#ifndef RPC_NT_ENTRY_NOT_FOUND
#define RPC_NT_ENTRY_NOT_FOUND           ((NTSTATUS)0xC002003EL)
#endif//RPC_NT_ENTRY_NOT_FOUND

//
// MessageId: RPC_NT_NAME_SERVICE_UNAVAILABLE
//
// MessageText:
//
// The name service is unavailable.
//
#ifndef RPC_NT_NAME_SERVICE_UNAVAILABLE
#define RPC_NT_NAME_SERVICE_UNAVAILABLE  ((NTSTATUS)0xC002003FL)
#endif//RPC_NT_NAME_SERVICE_UNAVAILABLE

//
// MessageId: RPC_NT_INVALID_NAF_ID
//
// MessageText:
//
// The network address family is invalid.
//
#ifndef RPC_NT_INVALID_NAF_ID
#define RPC_NT_INVALID_NAF_ID            ((NTSTATUS)0xC0020040L)
#endif//RPC_NT_INVALID_NAF_ID

//
// MessageId: RPC_NT_CANNOT_SUPPORT
//
// MessageText:
//
// The requested operation is not supported.
//
#ifndef RPC_NT_CANNOT_SUPPORT
#define RPC_NT_CANNOT_SUPPORT            ((NTSTATUS)0xC0020041L)
#endif//RPC_NT_CANNOT_SUPPORT

//
// MessageId: RPC_NT_NO_CONTEXT_AVAILABLE
//
// MessageText:
//
// No security context is available to allow impersonation.
//
#ifndef RPC_NT_NO_CONTEXT_AVAILABLE
#define RPC_NT_NO_CONTEXT_AVAILABLE      ((NTSTATUS)0xC0020042L)
#endif//RPC_NT_NO_CONTEXT_AVAILABLE

//
// MessageId: RPC_NT_INTERNAL_ERROR
//
// MessageText:
//
// An internal error occurred in RPC.
//
#ifndef RPC_NT_INTERNAL_ERROR
#define RPC_NT_INTERNAL_ERROR            ((NTSTATUS)0xC0020043L)
#endif//RPC_NT_INTERNAL_ERROR

//
// MessageId: RPC_NT_ZERO_DIVIDE
//
// MessageText:
//
// The RPC server attempted an integer divide by zero.
//
#ifndef RPC_NT_ZERO_DIVIDE
#define RPC_NT_ZERO_DIVIDE               ((NTSTATUS)0xC0020044L)
#endif//RPC_NT_ZERO_DIVIDE

//
// MessageId: RPC_NT_ADDRESS_ERROR
//
// MessageText:
//
// An addressing error occurred in the RPC server.
//
#ifndef RPC_NT_ADDRESS_ERROR
#define RPC_NT_ADDRESS_ERROR             ((NTSTATUS)0xC0020045L)
#endif//RPC_NT_ADDRESS_ERROR

//
// MessageId: RPC_NT_FP_DIV_ZERO
//
// MessageText:
//
// A floating point operation at the RPC server caused a divide by zero.
//
#ifndef RPC_NT_FP_DIV_ZERO
#define RPC_NT_FP_DIV_ZERO               ((NTSTATUS)0xC0020046L)
#endif//RPC_NT_FP_DIV_ZERO

//
// MessageId: RPC_NT_FP_UNDERFLOW
//
// MessageText:
//
// A floating point underflow occurred at the RPC server.
//
#ifndef RPC_NT_FP_UNDERFLOW
#define RPC_NT_FP_UNDERFLOW              ((NTSTATUS)0xC0020047L)
#endif//RPC_NT_FP_UNDERFLOW

//
// MessageId: RPC_NT_FP_OVERFLOW
//
// MessageText:
//
// A floating point overflow occurred at the RPC server.
//
#ifndef RPC_NT_FP_OVERFLOW
#define RPC_NT_FP_OVERFLOW               ((NTSTATUS)0xC0020048L)
#endif//RPC_NT_FP_OVERFLOW

//
// MessageId: RPC_NT_NO_MORE_ENTRIES
//
// MessageText:
//
// The list of RPC servers available for auto-handle binding has been exhausted.
//
#ifndef RPC_NT_NO_MORE_ENTRIES
#define RPC_NT_NO_MORE_ENTRIES           ((NTSTATUS)0xC0030001L)
#endif//RPC_NT_NO_MORE_ENTRIES

//
// MessageId: RPC_NT_SS_CHAR_TRANS_OPEN_FAIL
//
// MessageText:
//
// The file designated by DCERPCCHARTRANS cannot be opened.
//
#ifndef RPC_NT_SS_CHAR_TRANS_OPEN_FAIL
#define RPC_NT_SS_CHAR_TRANS_OPEN_FAIL   ((NTSTATUS)0xC0030002L)
#endif//RPC_NT_SS_CHAR_TRANS_OPEN_FAIL

//
// MessageId: RPC_NT_SS_CHAR_TRANS_SHORT_FILE
//
// MessageText:
//
// The file containing the character translation table has fewer than 512 bytes.
//
#ifndef RPC_NT_SS_CHAR_TRANS_SHORT_FILE
#define RPC_NT_SS_CHAR_TRANS_SHORT_FILE  ((NTSTATUS)0xC0030003L)
#endif//RPC_NT_SS_CHAR_TRANS_SHORT_FILE

//
// MessageId: RPC_NT_SS_IN_NULL_CONTEXT
//
// MessageText:
//
// A null context handle is passed as an [in] parameter.
//
#ifndef RPC_NT_SS_IN_NULL_CONTEXT
#define RPC_NT_SS_IN_NULL_CONTEXT        ((NTSTATUS)0xC0030004L)
#endif//RPC_NT_SS_IN_NULL_CONTEXT

//
// MessageId: RPC_NT_SS_CONTEXT_MISMATCH
//
// MessageText:
//
// The context handle does not match any known context handles.
//
#ifndef RPC_NT_SS_CONTEXT_MISMATCH
#define RPC_NT_SS_CONTEXT_MISMATCH       ((NTSTATUS)0xC0030005L)
#endif//RPC_NT_SS_CONTEXT_MISMATCH

//
// MessageId: RPC_NT_SS_CONTEXT_DAMAGED
//
// MessageText:
//
// The context handle changed during a call.
//
#ifndef RPC_NT_SS_CONTEXT_DAMAGED
#define RPC_NT_SS_CONTEXT_DAMAGED        ((NTSTATUS)0xC0030006L)
#endif//RPC_NT_SS_CONTEXT_DAMAGED

//
// MessageId: RPC_NT_SS_HANDLES_MISMATCH
//
// MessageText:
//
// The binding handles passed to a remote procedure call do not match.
//
#ifndef RPC_NT_SS_HANDLES_MISMATCH
#define RPC_NT_SS_HANDLES_MISMATCH       ((NTSTATUS)0xC0030007L)
#endif//RPC_NT_SS_HANDLES_MISMATCH

//
// MessageId: RPC_NT_SS_CANNOT_GET_CALL_HANDLE
//
// MessageText:
//
// The stub is unable to get the call handle.
//
#ifndef RPC_NT_SS_CANNOT_GET_CALL_HANDLE
#define RPC_NT_SS_CANNOT_GET_CALL_HANDLE ((NTSTATUS)0xC0030008L)
#endif//RPC_NT_SS_CANNOT_GET_CALL_HANDLE

//
// MessageId: RPC_NT_NULL_REF_POINTER
//
// MessageText:
//
// A null reference pointer was passed to the stub.
//
#ifndef RPC_NT_NULL_REF_POINTER
#define RPC_NT_NULL_REF_POINTER          ((NTSTATUS)0xC0030009L)
#endif//RPC_NT_NULL_REF_POINTER

//
// MessageId: RPC_NT_ENUM_VALUE_OUT_OF_RANGE
//
// MessageText:
//
// The enumeration value is out of range.
//
#ifndef RPC_NT_ENUM_VALUE_OUT_OF_RANGE
#define RPC_NT_ENUM_VALUE_OUT_OF_RANGE   ((NTSTATUS)0xC003000AL)
#endif//RPC_NT_ENUM_VALUE_OUT_OF_RANGE

//
// MessageId: RPC_NT_BYTE_COUNT_TOO_SMALL
//
// MessageText:
//
// The byte count is too small.
//
#ifndef RPC_NT_BYTE_COUNT_TOO_SMALL
#define RPC_NT_BYTE_COUNT_TOO_SMALL      ((NTSTATUS)0xC003000BL)
#endif//RPC_NT_BYTE_COUNT_TOO_SMALL

//
// MessageId: RPC_NT_BAD_STUB_DATA
//
// MessageText:
//
// The stub received bad data.
//
#ifndef RPC_NT_BAD_STUB_DATA
#define RPC_NT_BAD_STUB_DATA             ((NTSTATUS)0xC003000CL)
#endif//RPC_NT_BAD_STUB_DATA

//
// MessageId: RPC_NT_CALL_IN_PROGRESS
//
// MessageText:
//
// A remote procedure call is already in progress for this thread.
//
#ifndef RPC_NT_CALL_IN_PROGRESS
#define RPC_NT_CALL_IN_PROGRESS          ((NTSTATUS)0xC0020049L)
#endif//RPC_NT_CALL_IN_PROGRESS

//
// MessageId: RPC_NT_NO_MORE_BINDINGS
//
// MessageText:
//
// There are no more bindings.
//
#ifndef RPC_NT_NO_MORE_BINDINGS
#define RPC_NT_NO_MORE_BINDINGS          ((NTSTATUS)0xC002004AL)
#endif//RPC_NT_NO_MORE_BINDINGS

//
// MessageId: RPC_NT_GROUP_MEMBER_NOT_FOUND
//
// MessageText:
//
// The group member was not found.
//
#ifndef RPC_NT_GROUP_MEMBER_NOT_FOUND
#define RPC_NT_GROUP_MEMBER_NOT_FOUND    ((NTSTATUS)0xC002004BL)
#endif//RPC_NT_GROUP_MEMBER_NOT_FOUND

//
// MessageId: EPT_NT_CANT_CREATE
//
// MessageText:
//
// The endpoint mapper database entry could not be created.
//
#define EPT_NT_CANT_CREATE               ((NTSTATUS)0xC002004CL)

//
// MessageId: RPC_NT_INVALID_OBJECT
//
// MessageText:
//
// The object UUID is the nil UUID.
//
#ifndef RPC_NT_INVALID_OBJECT
#define RPC_NT_INVALID_OBJECT            ((NTSTATUS)0xC002004DL)
#endif//RPC_NT_INVALID_OBJECT

//
// MessageId: RPC_NT_NO_INTERFACES
//
// MessageText:
//
// No interfaces have been registered.
//
#ifndef RPC_NT_NO_INTERFACES
#define RPC_NT_NO_INTERFACES             ((NTSTATUS)0xC002004FL)
#endif//RPC_NT_NO_INTERFACES

//
// MessageId: RPC_NT_CALL_CANCELLED
//
// MessageText:
//
// The remote procedure call was cancelled.
//
#ifndef RPC_NT_CALL_CANCELLED
#define RPC_NT_CALL_CANCELLED            ((NTSTATUS)0xC0020050L)
#endif//RPC_NT_CALL_CANCELLED

//
// MessageId: RPC_NT_BINDING_INCOMPLETE
//
// MessageText:
//
// The binding handle does not contain all required information.
//
#ifndef RPC_NT_BINDING_INCOMPLETE
#define RPC_NT_BINDING_INCOMPLETE        ((NTSTATUS)0xC0020051L)
#endif//RPC_NT_BINDING_INCOMPLETE

//
// MessageId: RPC_NT_COMM_FAILURE
//
// MessageText:
//
// A communications failure occurred during a remote procedure call.
//
#ifndef RPC_NT_COMM_FAILURE
#define RPC_NT_COMM_FAILURE              ((NTSTATUS)0xC0020052L)
#endif//RPC_NT_COMM_FAILURE

//
// MessageId: RPC_NT_UNSUPPORTED_AUTHN_LEVEL
//
// MessageText:
//
// The requested authentication level is not supported.
//
#ifndef RPC_NT_UNSUPPORTED_AUTHN_LEVEL
#define RPC_NT_UNSUPPORTED_AUTHN_LEVEL   ((NTSTATUS)0xC0020053L)
#endif//RPC_NT_UNSUPPORTED_AUTHN_LEVEL

//
// MessageId: RPC_NT_NO_PRINC_NAME
//
// MessageText:
//
// No principal name registered.
//
#ifndef RPC_NT_NO_PRINC_NAME
#define RPC_NT_NO_PRINC_NAME             ((NTSTATUS)0xC0020054L)
#endif//RPC_NT_NO_PRINC_NAME

//
// MessageId: RPC_NT_NOT_RPC_ERROR
//
// MessageText:
//
// The error specified is not a valid Windows RPC error code.
//
#ifndef RPC_NT_NOT_RPC_ERROR
#define RPC_NT_NOT_RPC_ERROR             ((NTSTATUS)0xC0020055L)
#endif//RPC_NT_NOT_RPC_ERROR

//
// MessageId: RPC_NT_UUID_LOCAL_ONLY
//
// MessageText:
//
// A UUID that is valid only on this computer has been allocated.
//
#ifndef RPC_NT_UUID_LOCAL_ONLY
#define RPC_NT_UUID_LOCAL_ONLY           ((NTSTATUS)0x40020056L)
#endif//RPC_NT_UUID_LOCAL_ONLY

//
// MessageId: RPC_NT_SEC_PKG_ERROR
//
// MessageText:
//
// A security package specific error occurred.
//
#ifndef RPC_NT_SEC_PKG_ERROR
#define RPC_NT_SEC_PKG_ERROR             ((NTSTATUS)0xC0020057L)
#endif//RPC_NT_SEC_PKG_ERROR

//
// MessageId: RPC_NT_NOT_CANCELLED
//
// MessageText:
//
// Thread is not cancelled.
//
#ifndef RPC_NT_NOT_CANCELLED
#define RPC_NT_NOT_CANCELLED             ((NTSTATUS)0xC0020058L)
#endif//RPC_NT_NOT_CANCELLED

//
// MessageId: RPC_NT_INVALID_ES_ACTION
//
// MessageText:
//
// Invalid operation on the encoding/decoding handle.
//
#ifndef RPC_NT_INVALID_ES_ACTION
#define RPC_NT_INVALID_ES_ACTION         ((NTSTATUS)0xC0030059L)
#endif//RPC_NT_INVALID_ES_ACTION

//
// MessageId: RPC_NT_WRONG_ES_VERSION
//
// MessageText:
//
// Incompatible version of the serializing package.
//
#ifndef RPC_NT_WRONG_ES_VERSION
#define RPC_NT_WRONG_ES_VERSION          ((NTSTATUS)0xC003005AL)
#endif//RPC_NT_WRONG_ES_VERSION

//
// MessageId: RPC_NT_WRONG_STUB_VERSION
//
// MessageText:
//
// Incompatible version of the RPC stub.
//
#ifndef RPC_NT_WRONG_STUB_VERSION
#define RPC_NT_WRONG_STUB_VERSION        ((NTSTATUS)0xC003005BL)
#endif//RPC_NT_WRONG_STUB_VERSION

//
// MessageId: RPC_NT_INVALID_PIPE_OBJECT
//
// MessageText:
//
// The RPC pipe object is invalid or corrupted.
//
#ifndef RPC_NT_INVALID_PIPE_OBJECT
#define RPC_NT_INVALID_PIPE_OBJECT       ((NTSTATUS)0xC003005CL)
#endif//RPC_NT_INVALID_PIPE_OBJECT

//
// MessageId: RPC_NT_INVALID_PIPE_OPERATION
//
// MessageText:
//
// An invalid operation was attempted on an RPC pipe object.
//
#ifndef RPC_NT_INVALID_PIPE_OPERATION
#define RPC_NT_INVALID_PIPE_OPERATION    ((NTSTATUS)0xC003005DL)
#endif//RPC_NT_INVALID_PIPE_OPERATION

//
// MessageId: RPC_NT_WRONG_PIPE_VERSION
//
// MessageText:
//
// Unsupported RPC pipe version.
//
#ifndef RPC_NT_WRONG_PIPE_VERSION
#define RPC_NT_WRONG_PIPE_VERSION        ((NTSTATUS)0xC003005EL)
#endif//RPC_NT_WRONG_PIPE_VERSION

//
// MessageId: RPC_NT_PIPE_CLOSED
//
// MessageText:
//
// The RPC pipe object has already been closed.
//
#ifndef RPC_NT_PIPE_CLOSED
#define RPC_NT_PIPE_CLOSED               ((NTSTATUS)0xC003005FL)
#endif//RPC_NT_PIPE_CLOSED

//
// MessageId: RPC_NT_PIPE_DISCIPLINE_ERROR
//
// MessageText:
//
// The RPC call completed before all pipes were processed.
//
#ifndef RPC_NT_PIPE_DISCIPLINE_ERROR
#define RPC_NT_PIPE_DISCIPLINE_ERROR     ((NTSTATUS)0xC0030060L)
#endif//RPC_NT_PIPE_DISCIPLINE_ERROR

//
// MessageId: RPC_NT_PIPE_EMPTY
//
// MessageText:
//
// No more data is available from the RPC pipe.
//
#ifndef RPC_NT_PIPE_EMPTY
#define RPC_NT_PIPE_EMPTY                ((NTSTATUS)0xC0030061L)
#endif//RPC_NT_PIPE_EMPTY

//
// MessageId: RPC_NT_INVALID_ASYNC_HANDLE
//
// MessageText:
//
// Invalid asynchronous remote procedure call handle.
//
#ifndef RPC_NT_INVALID_ASYNC_HANDLE
#define RPC_NT_INVALID_ASYNC_HANDLE      ((NTSTATUS)0xC0020062L)
#endif//RPC_NT_INVALID_ASYNC_HANDLE

//
// MessageId: RPC_NT_INVALID_ASYNC_CALL
//
// MessageText:
//
// Invalid asynchronous RPC call handle for this operation.
//
#ifndef RPC_NT_INVALID_ASYNC_CALL
#define RPC_NT_INVALID_ASYNC_CALL        ((NTSTATUS)0xC0020063L)
#endif//RPC_NT_INVALID_ASYNC_CALL

//
// MessageId: RPC_NT_PROXY_ACCESS_DENIED
//
// MessageText:
//
// Access to the HTTP proxy is denied.
//
#ifndef RPC_NT_PROXY_ACCESS_DENIED
#define RPC_NT_PROXY_ACCESS_DENIED       ((NTSTATUS)0xC0020064L)
#endif//RPC_NT_PROXY_ACCESS_DENIED

//
// MessageId: RPC_NT_COOKIE_AUTH_FAILED
//
// MessageText:
//
// HTTP proxy server rejected the connection because the cookie authentication failed.
//
#ifndef RPC_NT_COOKIE_AUTH_FAILED
#define RPC_NT_COOKIE_AUTH_FAILED        ((NTSTATUS)0xC0020065L)
#endif//RPC_NT_COOKIE_AUTH_FAILED

//
// MessageId: RPC_NT_SEND_INCOMPLETE
//
// MessageText:
//
// Some data remains to be sent in the request buffer.
//
#ifndef RPC_NT_SEND_INCOMPLETE
#define RPC_NT_SEND_INCOMPLETE           ((NTSTATUS)0x400200AFL)
#endif//RPC_NT_SEND_INCOMPLETE


//
//  ACPI error values
//

//
// MessageId: STATUS_ACPI_INVALID_OPCODE
//
// MessageText:
//
// An attempt was made to run an invalid AML opcode
//
#ifndef STATUS_ACPI_INVALID_OPCODE
#define STATUS_ACPI_INVALID_OPCODE       ((NTSTATUS)0xC0140001L)
#endif//STATUS_ACPI_INVALID_OPCODE

//
// MessageId: STATUS_ACPI_STACK_OVERFLOW
//
// MessageText:
//
// The AML Interpreter Stack has overflowed
//
#ifndef STATUS_ACPI_STACK_OVERFLOW
#define STATUS_ACPI_STACK_OVERFLOW       ((NTSTATUS)0xC0140002L)
#endif//STATUS_ACPI_STACK_OVERFLOW

//
// MessageId: STATUS_ACPI_ASSERT_FAILED
//
// MessageText:
//
// An inconsistent state has occurred
//
#ifndef STATUS_ACPI_ASSERT_FAILED
#define STATUS_ACPI_ASSERT_FAILED        ((NTSTATUS)0xC0140003L)
#endif//STATUS_ACPI_ASSERT_FAILED

//
// MessageId: STATUS_ACPI_INVALID_INDEX
//
// MessageText:
//
// An attempt was made to access an array outside of its bounds
//
#ifndef STATUS_ACPI_INVALID_INDEX
#define STATUS_ACPI_INVALID_INDEX        ((NTSTATUS)0xC0140004L)
#endif//STATUS_ACPI_INVALID_INDEX

//
// MessageId: STATUS_ACPI_INVALID_ARGUMENT
//
// MessageText:
//
// A required argument was not specified
//
#ifndef STATUS_ACPI_INVALID_ARGUMENT
#define STATUS_ACPI_INVALID_ARGUMENT     ((NTSTATUS)0xC0140005L)
#endif//STATUS_ACPI_INVALID_ARGUMENT

//
// MessageId: STATUS_ACPI_FATAL
//
// MessageText:
//
// A fatal error has occurred
//
#ifndef STATUS_ACPI_FATAL
#define STATUS_ACPI_FATAL                ((NTSTATUS)0xC0140006L)
#endif//STATUS_ACPI_FATAL

//
// MessageId: STATUS_ACPI_INVALID_SUPERNAME
//
// MessageText:
//
// An invalid SuperName was specified
//
#ifndef STATUS_ACPI_INVALID_SUPERNAME
#define STATUS_ACPI_INVALID_SUPERNAME    ((NTSTATUS)0xC0140007L)
#endif//STATUS_ACPI_INVALID_SUPERNAME

//
// MessageId: STATUS_ACPI_INVALID_ARGTYPE
//
// MessageText:
//
// An argument with an incorrect type was specified
//
#ifndef STATUS_ACPI_INVALID_ARGTYPE
#define STATUS_ACPI_INVALID_ARGTYPE      ((NTSTATUS)0xC0140008L)
#endif//STATUS_ACPI_INVALID_ARGTYPE

//
// MessageId: STATUS_ACPI_INVALID_OBJTYPE
//
// MessageText:
//
// An object with an incorrect type was specified
//
#ifndef STATUS_ACPI_INVALID_OBJTYPE
#define STATUS_ACPI_INVALID_OBJTYPE      ((NTSTATUS)0xC0140009L)
#endif//STATUS_ACPI_INVALID_OBJTYPE

//
// MessageId: STATUS_ACPI_INVALID_TARGETTYPE
//
// MessageText:
//
// A target with an incorrect type was specified
//
#ifndef STATUS_ACPI_INVALID_TARGETTYPE
#define STATUS_ACPI_INVALID_TARGETTYPE   ((NTSTATUS)0xC014000AL)
#endif//STATUS_ACPI_INVALID_TARGETTYPE

//
// MessageId: STATUS_ACPI_INCORRECT_ARGUMENT_COUNT
//
// MessageText:
//
// An incorrect number of arguments were specified
//
#ifndef STATUS_ACPI_INCORRECT_ARGUMENT_COUNT
#define STATUS_ACPI_INCORRECT_ARGUMENT_COUNT ((NTSTATUS)0xC014000BL)
#endif//STATUS_ACPI_INCORRECT_ARGUMENT_COUNT

//
// MessageId: STATUS_ACPI_ADDRESS_NOT_MAPPED
//
// MessageText:
//
// An address failed to translate
//
#ifndef STATUS_ACPI_ADDRESS_NOT_MAPPED
#define STATUS_ACPI_ADDRESS_NOT_MAPPED   ((NTSTATUS)0xC014000CL)
#endif//STATUS_ACPI_ADDRESS_NOT_MAPPED

//
// MessageId: STATUS_ACPI_INVALID_EVENTTYPE
//
// MessageText:
//
// An incorrect event type was specified
//
#ifndef STATUS_ACPI_INVALID_EVENTTYPE
#define STATUS_ACPI_INVALID_EVENTTYPE    ((NTSTATUS)0xC014000DL)
#endif//STATUS_ACPI_INVALID_EVENTTYPE

//
// MessageId: STATUS_ACPI_HANDLER_COLLISION
//
// MessageText:
//
// A handler for the target already exists
//
#ifndef STATUS_ACPI_HANDLER_COLLISION
#define STATUS_ACPI_HANDLER_COLLISION    ((NTSTATUS)0xC014000EL)
#endif//STATUS_ACPI_HANDLER_COLLISION

//
// MessageId: STATUS_ACPI_INVALID_DATA
//
// MessageText:
//
// Invalid data for the target was specified
//
#ifndef STATUS_ACPI_INVALID_DATA
#define STATUS_ACPI_INVALID_DATA         ((NTSTATUS)0xC014000FL)
#endif//STATUS_ACPI_INVALID_DATA

//
// MessageId: STATUS_ACPI_INVALID_REGION
//
// MessageText:
//
// An invalid region for the target was specified
//
#ifndef STATUS_ACPI_INVALID_REGION
#define STATUS_ACPI_INVALID_REGION       ((NTSTATUS)0xC0140010L)
#endif//STATUS_ACPI_INVALID_REGION

//
// MessageId: STATUS_ACPI_INVALID_ACCESS_SIZE
//
// MessageText:
//
// An attempt was made to access a field outside of the defined range
//
#ifndef STATUS_ACPI_INVALID_ACCESS_SIZE
#define STATUS_ACPI_INVALID_ACCESS_SIZE  ((NTSTATUS)0xC0140011L)
#endif//STATUS_ACPI_INVALID_ACCESS_SIZE

//
// MessageId: STATUS_ACPI_ACQUIRE_GLOBAL_LOCK
//
// MessageText:
//
// The Global system lock could not be acquired
//
#ifndef STATUS_ACPI_ACQUIRE_GLOBAL_LOCK
#define STATUS_ACPI_ACQUIRE_GLOBAL_LOCK  ((NTSTATUS)0xC0140012L)
#endif//STATUS_ACPI_ACQUIRE_GLOBAL_LOCK

//
// MessageId: STATUS_ACPI_ALREADY_INITIALIZED
//
// MessageText:
//
// An attempt was made to reinitialize the ACPI subsystem
//
#ifndef STATUS_ACPI_ALREADY_INITIALIZED
#define STATUS_ACPI_ALREADY_INITIALIZED  ((NTSTATUS)0xC0140013L)
#endif//STATUS_ACPI_ALREADY_INITIALIZED

//
// MessageId: STATUS_ACPI_NOT_INITIALIZED
//
// MessageText:
//
// The ACPI subsystem has not been initialized
//
#ifndef STATUS_ACPI_NOT_INITIALIZED
#define STATUS_ACPI_NOT_INITIALIZED      ((NTSTATUS)0xC0140014L)
#endif//STATUS_ACPI_NOT_INITIALIZED

//
// MessageId: STATUS_ACPI_INVALID_MUTEX_LEVEL
//
// MessageText:
//
// An incorrect mutex was specified
//
#ifndef STATUS_ACPI_INVALID_MUTEX_LEVEL
#define STATUS_ACPI_INVALID_MUTEX_LEVEL  ((NTSTATUS)0xC0140015L)
#endif//STATUS_ACPI_INVALID_MUTEX_LEVEL

//
// MessageId: STATUS_ACPI_MUTEX_NOT_OWNED
//
// MessageText:
//
// The mutex is not currently owned
//
#ifndef STATUS_ACPI_MUTEX_NOT_OWNED
#define STATUS_ACPI_MUTEX_NOT_OWNED      ((NTSTATUS)0xC0140016L)
#endif//STATUS_ACPI_MUTEX_NOT_OWNED

//
// MessageId: STATUS_ACPI_MUTEX_NOT_OWNER
//
// MessageText:
//
// An attempt was made to access the mutex by a process that was not the owner
//
#ifndef STATUS_ACPI_MUTEX_NOT_OWNER
#define STATUS_ACPI_MUTEX_NOT_OWNER      ((NTSTATUS)0xC0140017L)
#endif//STATUS_ACPI_MUTEX_NOT_OWNER

//
// MessageId: STATUS_ACPI_RS_ACCESS
//
// MessageText:
//
// An error occurred during an access to Region Space
//
#ifndef STATUS_ACPI_RS_ACCESS
#define STATUS_ACPI_RS_ACCESS            ((NTSTATUS)0xC0140018L)
#endif//STATUS_ACPI_RS_ACCESS

//
// MessageId: STATUS_ACPI_INVALID_TABLE
//
// MessageText:
//
// An attempt was made to use an incorrect table
//
#ifndef STATUS_ACPI_INVALID_TABLE
#define STATUS_ACPI_INVALID_TABLE        ((NTSTATUS)0xC0140019L)
#endif//STATUS_ACPI_INVALID_TABLE

//
// MessageId: STATUS_ACPI_REG_HANDLER_FAILED
//
// MessageText:
//
// The registration of an ACPI event failed
//
#ifndef STATUS_ACPI_REG_HANDLER_FAILED
#define STATUS_ACPI_REG_HANDLER_FAILED   ((NTSTATUS)0xC0140020L)
#endif//STATUS_ACPI_REG_HANDLER_FAILED

//
// MessageId: STATUS_ACPI_POWER_REQUEST_FAILED
//
// MessageText:
//
// An ACPI Power Object failed to transition state
//
#ifndef STATUS_ACPI_POWER_REQUEST_FAILED
#define STATUS_ACPI_POWER_REQUEST_FAILED ((NTSTATUS)0xC0140021L)
#endif//STATUS_ACPI_POWER_REQUEST_FAILED

//
// Terminal Server specific Errors
//
//
// MessageId: STATUS_CTX_WINSTATION_NAME_INVALID
//
// MessageText:
//
// Session name %1 is invalid.
//
#ifndef STATUS_CTX_WINSTATION_NAME_INVALID
#define STATUS_CTX_WINSTATION_NAME_INVALID ((NTSTATUS)0xC00A0001L)
#endif//STATUS_CTX_WINSTATION_NAME_INVALID

//
// MessageId: STATUS_CTX_INVALID_PD
//
// MessageText:
//
// The protocol driver %1 is invalid.
//
#ifndef STATUS_CTX_INVALID_PD
#define STATUS_CTX_INVALID_PD            ((NTSTATUS)0xC00A0002L)
#endif//STATUS_CTX_INVALID_PD

//
// MessageId: STATUS_CTX_PD_NOT_FOUND
//
// MessageText:
//
// The protocol driver %1 was not found in the system path.
//
#ifndef STATUS_CTX_PD_NOT_FOUND
#define STATUS_CTX_PD_NOT_FOUND          ((NTSTATUS)0xC00A0003L)
#endif//STATUS_CTX_PD_NOT_FOUND

//
// MessageId: STATUS_CTX_CDM_CONNECT
//
// MessageText:
//
// The Client Drive Mapping Service Has Connected on Terminal Connection.
//
#ifndef STATUS_CTX_CDM_CONNECT
#define STATUS_CTX_CDM_CONNECT           ((NTSTATUS)0x400A0004L)
#endif//STATUS_CTX_CDM_CONNECT

//
// MessageId: STATUS_CTX_CDM_DISCONNECT
//
// MessageText:
//
// The Client Drive Mapping Service Has Disconnected on Terminal Connection.
//
#ifndef STATUS_CTX_CDM_DISCONNECT
#define STATUS_CTX_CDM_DISCONNECT        ((NTSTATUS)0x400A0005L)
#endif//STATUS_CTX_CDM_DISCONNECT

//
// MessageId: STATUS_CTX_CLOSE_PENDING
//
// MessageText:
//
// A close operation is pending on the Terminal Connection.
//
#ifndef STATUS_CTX_CLOSE_PENDING
#define STATUS_CTX_CLOSE_PENDING         ((NTSTATUS)0xC00A0006L)
#endif//STATUS_CTX_CLOSE_PENDING

//
// MessageId: STATUS_CTX_NO_OUTBUF
//
// MessageText:
//
// There are no free output buffers available.
//
#ifndef STATUS_CTX_NO_OUTBUF
#define STATUS_CTX_NO_OUTBUF             ((NTSTATUS)0xC00A0007L)
#endif//STATUS_CTX_NO_OUTBUF

//
// MessageId: STATUS_CTX_MODEM_INF_NOT_FOUND
//
// MessageText:
//
// The MODEM.INF file was not found.
//
#ifndef STATUS_CTX_MODEM_INF_NOT_FOUND
#define STATUS_CTX_MODEM_INF_NOT_FOUND   ((NTSTATUS)0xC00A0008L)
#endif//STATUS_CTX_MODEM_INF_NOT_FOUND

//
// MessageId: STATUS_CTX_INVALID_MODEMNAME
//
// MessageText:
//
// The modem (%1) was not found in MODEM.INF.
//
#ifndef STATUS_CTX_INVALID_MODEMNAME
#define STATUS_CTX_INVALID_MODEMNAME     ((NTSTATUS)0xC00A0009L)
#endif//STATUS_CTX_INVALID_MODEMNAME

//
// MessageId: STATUS_CTX_RESPONSE_ERROR
//
// MessageText:
//
// The modem did not accept the command sent to it.
// Verify the configured modem name matches the attached modem.
//
#ifndef STATUS_CTX_RESPONSE_ERROR
#define STATUS_CTX_RESPONSE_ERROR        ((NTSTATUS)0xC00A000AL)
#endif//STATUS_CTX_RESPONSE_ERROR

//
// MessageId: STATUS_CTX_MODEM_RESPONSE_TIMEOUT
//
// MessageText:
//
// The modem did not respond to the command sent to it.
// Verify the modem is properly cabled and powered on.
//
#ifndef STATUS_CTX_MODEM_RESPONSE_TIMEOUT
#define STATUS_CTX_MODEM_RESPONSE_TIMEOUT ((NTSTATUS)0xC00A000BL)
#endif//STATUS_CTX_MODEM_RESPONSE_TIMEOUT

//
// MessageId: STATUS_CTX_MODEM_RESPONSE_NO_CARRIER
//
// MessageText:
//
// Carrier detect has failed or carrier has been dropped due to disconnect.
//
#ifndef STATUS_CTX_MODEM_RESPONSE_NO_CARRIER
#define STATUS_CTX_MODEM_RESPONSE_NO_CARRIER ((NTSTATUS)0xC00A000CL)
#endif//STATUS_CTX_MODEM_RESPONSE_NO_CARRIER

//
// MessageId: STATUS_CTX_MODEM_RESPONSE_NO_DIALTONE
//
// MessageText:
//
// Dial tone not detected within required time.
// Verify phone cable is properly attached and functional.
//
#ifndef STATUS_CTX_MODEM_RESPONSE_NO_DIALTONE
#define STATUS_CTX_MODEM_RESPONSE_NO_DIALTONE ((NTSTATUS)0xC00A000DL)
#endif//STATUS_CTX_MODEM_RESPONSE_NO_DIALTONE

//
// MessageId: STATUS_CTX_MODEM_RESPONSE_BUSY
//
// MessageText:
//
// Busy signal detected at remote site on callback.
//
#ifndef STATUS_CTX_MODEM_RESPONSE_BUSY
#define STATUS_CTX_MODEM_RESPONSE_BUSY   ((NTSTATUS)0xC00A000EL)
#endif//STATUS_CTX_MODEM_RESPONSE_BUSY

//
// MessageId: STATUS_CTX_MODEM_RESPONSE_VOICE
//
// MessageText:
//
// Voice detected at remote site on callback.
//
#ifndef STATUS_CTX_MODEM_RESPONSE_VOICE
#define STATUS_CTX_MODEM_RESPONSE_VOICE  ((NTSTATUS)0xC00A000FL)
#endif//STATUS_CTX_MODEM_RESPONSE_VOICE

//
// MessageId: STATUS_CTX_TD_ERROR
//
// MessageText:
//
// Transport driver error
//
#ifndef STATUS_CTX_TD_ERROR
#define STATUS_CTX_TD_ERROR              ((NTSTATUS)0xC00A0010L)
#endif//STATUS_CTX_TD_ERROR

//
// MessageId: STATUS_CTX_LICENSE_CLIENT_INVALID
//
// MessageText:
//
// The client you are using is not licensed to use this system. Your logon request is denied.
//
#ifndef STATUS_CTX_LICENSE_CLIENT_INVALID
#define STATUS_CTX_LICENSE_CLIENT_INVALID ((NTSTATUS)0xC00A0012L)
#endif//STATUS_CTX_LICENSE_CLIENT_INVALID

//
// MessageId: STATUS_CTX_LICENSE_NOT_AVAILABLE
//
// MessageText:
//
// The system has reached its licensed logon limit.
// Please try again later.
//
#ifndef STATUS_CTX_LICENSE_NOT_AVAILABLE
#define STATUS_CTX_LICENSE_NOT_AVAILABLE ((NTSTATUS)0xC00A0013L)
#endif//STATUS_CTX_LICENSE_NOT_AVAILABLE

//
// MessageId: STATUS_CTX_LICENSE_EXPIRED
//
// MessageText:
//
// The system license has expired. Your logon request is denied.
//
#ifndef STATUS_CTX_LICENSE_EXPIRED
#define STATUS_CTX_LICENSE_EXPIRED       ((NTSTATUS)0xC00A0014L)
#endif//STATUS_CTX_LICENSE_EXPIRED

//
// MessageId: STATUS_CTX_WINSTATION_NOT_FOUND
//
// MessageText:
//
// The specified session cannot be found.
//
#ifndef STATUS_CTX_WINSTATION_NOT_FOUND
#define STATUS_CTX_WINSTATION_NOT_FOUND  ((NTSTATUS)0xC00A0015L)
#endif//STATUS_CTX_WINSTATION_NOT_FOUND

//
// MessageId: STATUS_CTX_WINSTATION_NAME_COLLISION
//
// MessageText:
//
// The specified session name is already in use.
//
#ifndef STATUS_CTX_WINSTATION_NAME_COLLISION
#define STATUS_CTX_WINSTATION_NAME_COLLISION ((NTSTATUS)0xC00A0016L)
#endif//STATUS_CTX_WINSTATION_NAME_COLLISION

//
// MessageId: STATUS_CTX_WINSTATION_BUSY
//
// MessageText:
//
// The task you are trying to do can't be completed because Remote Desktop Services is currently busy. Please try again in a few minutes. Other users should still be able to log on.
//
#ifndef STATUS_CTX_WINSTATION_BUSY
#define STATUS_CTX_WINSTATION_BUSY       ((NTSTATUS)0xC00A0017L)
#endif//STATUS_CTX_WINSTATION_BUSY

//
// MessageId: STATUS_CTX_BAD_VIDEO_MODE
//
// MessageText:
//
// An attempt has been made to connect to a session whose video mode is not supported by the current client.
//
#ifndef STATUS_CTX_BAD_VIDEO_MODE
#define STATUS_CTX_BAD_VIDEO_MODE        ((NTSTATUS)0xC00A0018L)
#endif//STATUS_CTX_BAD_VIDEO_MODE

//
// MessageId: STATUS_CTX_GRAPHICS_INVALID
//
// MessageText:
//
// The application attempted to enable DOS graphics mode.
// DOS graphics mode is not supported.
//
#ifndef STATUS_CTX_GRAPHICS_INVALID
#define STATUS_CTX_GRAPHICS_INVALID      ((NTSTATUS)0xC00A0022L)
#endif//STATUS_CTX_GRAPHICS_INVALID

//
// MessageId: STATUS_CTX_NOT_CONSOLE
//
// MessageText:
//
// The requested operation can be performed only on the system console.
// This is most often the result of a driver or system DLL requiring direct console access.
//
#ifndef STATUS_CTX_NOT_CONSOLE
#define STATUS_CTX_NOT_CONSOLE           ((NTSTATUS)0xC00A0024L)
#endif//STATUS_CTX_NOT_CONSOLE

//
// MessageId: STATUS_CTX_CLIENT_QUERY_TIMEOUT
//
// MessageText:
//
// The client failed to respond to the server connect message.
//
#ifndef STATUS_CTX_CLIENT_QUERY_TIMEOUT
#define STATUS_CTX_CLIENT_QUERY_TIMEOUT  ((NTSTATUS)0xC00A0026L)
#endif//STATUS_CTX_CLIENT_QUERY_TIMEOUT

//
// MessageId: STATUS_CTX_CONSOLE_DISCONNECT
//
// MessageText:
//
// Disconnecting the console session is not supported.
//
#ifndef STATUS_CTX_CONSOLE_DISCONNECT
#define STATUS_CTX_CONSOLE_DISCONNECT    ((NTSTATUS)0xC00A0027L)
#endif//STATUS_CTX_CONSOLE_DISCONNECT

//
// MessageId: STATUS_CTX_CONSOLE_CONNECT
//
// MessageText:
//
// Reconnecting a disconnected session to the console is not supported.
//
#ifndef STATUS_CTX_CONSOLE_CONNECT
#define STATUS_CTX_CONSOLE_CONNECT       ((NTSTATUS)0xC00A0028L)
#endif//STATUS_CTX_CONSOLE_CONNECT

//
// MessageId: STATUS_CTX_SHADOW_DENIED
//
// MessageText:
//
// The request to control another session remotely was denied.
//
#ifndef STATUS_CTX_SHADOW_DENIED
#define STATUS_CTX_SHADOW_DENIED         ((NTSTATUS)0xC00A002AL)
#endif//STATUS_CTX_SHADOW_DENIED

//
// MessageId: STATUS_CTX_WINSTATION_ACCESS_DENIED
//
// MessageText:
//
// A process has requested access to a session, but has not been granted those access rights.
//
#ifndef STATUS_CTX_WINSTATION_ACCESS_DENIED
#define STATUS_CTX_WINSTATION_ACCESS_DENIED ((NTSTATUS)0xC00A002BL)
#endif//STATUS_CTX_WINSTATION_ACCESS_DENIED

//
// MessageId: STATUS_CTX_INVALID_WD
//
// MessageText:
//
// The Terminal Connection driver %1 is invalid.
//
#ifndef STATUS_CTX_INVALID_WD
#define STATUS_CTX_INVALID_WD            ((NTSTATUS)0xC00A002EL)
#endif//STATUS_CTX_INVALID_WD

//
// MessageId: STATUS_CTX_WD_NOT_FOUND
//
// MessageText:
//
// The Terminal Connection driver %1 was not found in the system path.
//
#ifndef STATUS_CTX_WD_NOT_FOUND
#define STATUS_CTX_WD_NOT_FOUND          ((NTSTATUS)0xC00A002FL)
#endif//STATUS_CTX_WD_NOT_FOUND

//
// MessageId: STATUS_CTX_SHADOW_INVALID
//
// MessageText:
//
// The requested session cannot be controlled remotely.
// You cannot control your own session, a session that is trying to control your session,
// a session that has no user logged on, nor control other sessions from the console.
//
#ifndef STATUS_CTX_SHADOW_INVALID
#define STATUS_CTX_SHADOW_INVALID        ((NTSTATUS)0xC00A0030L)
#endif//STATUS_CTX_SHADOW_INVALID

//
// MessageId: STATUS_CTX_SHADOW_DISABLED
//
// MessageText:
//
// The requested session is not configured to allow remote control.
//
#ifndef STATUS_CTX_SHADOW_DISABLED
#define STATUS_CTX_SHADOW_DISABLED       ((NTSTATUS)0xC00A0031L)
#endif//STATUS_CTX_SHADOW_DISABLED

//
// MessageId: STATUS_RDP_PROTOCOL_ERROR
//
// MessageText:
//
// The RDP protocol component %2 detected an error in the protocol stream and has disconnected the client.
//
#ifndef STATUS_RDP_PROTOCOL_ERROR
#define STATUS_RDP_PROTOCOL_ERROR        ((NTSTATUS)0xC00A0032L)
#endif//STATUS_RDP_PROTOCOL_ERROR

//
// MessageId: STATUS_CTX_CLIENT_LICENSE_NOT_SET
//
// MessageText:
//
// Your request to connect to this Terminal server has been rejected.
// Your Terminal Server Client license number has not been entered for this copy of the Terminal Client.
// Please call your system administrator for help in entering a valid, unique license number for this Terminal Server Client.
// Click OK to continue.
//
#ifndef STATUS_CTX_CLIENT_LICENSE_NOT_SET
#define STATUS_CTX_CLIENT_LICENSE_NOT_SET ((NTSTATUS)0xC00A0033L)
#endif//STATUS_CTX_CLIENT_LICENSE_NOT_SET

//
// MessageId: STATUS_CTX_CLIENT_LICENSE_IN_USE
//
// MessageText:
//
// Your request to connect to this Terminal server has been rejected.
// Your Terminal Server Client license number is currently being used by another user.
// Please call your system administrator to obtain a new copy of the Terminal Server Client with a valid, unique license number.
// Click OK to continue.
//
#ifndef STATUS_CTX_CLIENT_LICENSE_IN_USE
#define STATUS_CTX_CLIENT_LICENSE_IN_USE ((NTSTATUS)0xC00A0034L)
#endif//STATUS_CTX_CLIENT_LICENSE_IN_USE

//
// MessageId: STATUS_CTX_SHADOW_ENDED_BY_MODE_CHANGE
//
// MessageText:
//
// The remote control of the console was terminated because the display mode was changed. Changing the display mode in a remote control session is not supported.
//
#ifndef STATUS_CTX_SHADOW_ENDED_BY_MODE_CHANGE
#define STATUS_CTX_SHADOW_ENDED_BY_MODE_CHANGE ((NTSTATUS)0xC00A0035L)
#endif//STATUS_CTX_SHADOW_ENDED_BY_MODE_CHANGE

//
// MessageId: STATUS_CTX_SHADOW_NOT_RUNNING
//
// MessageText:
//
// Remote control could not be terminated because the specified session is not currently being remotely controlled.
//
#ifndef STATUS_CTX_SHADOW_NOT_RUNNING
#define STATUS_CTX_SHADOW_NOT_RUNNING    ((NTSTATUS)0xC00A0036L)
#endif//STATUS_CTX_SHADOW_NOT_RUNNING

//
// MessageId: STATUS_CTX_LOGON_DISABLED
//
// MessageText:
//
// Your interactive logon privilege has been disabled.
// Please contact your system administrator.
//
#ifndef STATUS_CTX_LOGON_DISABLED
#define STATUS_CTX_LOGON_DISABLED        ((NTSTATUS)0xC00A0037L)
#endif//STATUS_CTX_LOGON_DISABLED

//
// MessageId: STATUS_CTX_SECURITY_LAYER_ERROR
//
// MessageText:
//
// The Terminal Server security layer detected an error in the protocol stream and has disconnected the client.
// Client IP: %2.
//
#ifndef STATUS_CTX_SECURITY_LAYER_ERROR
#define STATUS_CTX_SECURITY_LAYER_ERROR  ((NTSTATUS)0xC00A0038L)
#endif//STATUS_CTX_SECURITY_LAYER_ERROR

//
// MessageId: STATUS_TS_INCOMPATIBLE_SESSIONS
//
// MessageText:
//
// The target session is incompatible with the current session.
//
#ifndef STATUS_TS_INCOMPATIBLE_SESSIONS
#define STATUS_TS_INCOMPATIBLE_SESSIONS  ((NTSTATUS)0xC00A0039L)
#endif//STATUS_TS_INCOMPATIBLE_SESSIONS

//
// MessageId: STATUS_TS_VIDEO_SUBSYSTEM_ERROR
//
// MessageText:
//
// Windows can't connect to your session because a problem occurred in the Windows video subsystem. Try connecting again later, or contact the server administrator for assistance.
//
#ifndef STATUS_TS_VIDEO_SUBSYSTEM_ERROR
#define STATUS_TS_VIDEO_SUBSYSTEM_ERROR  ((NTSTATUS)0xC00A003AL)
#endif//STATUS_TS_VIDEO_SUBSYSTEM_ERROR


//
//  IO error values
//

//
// MessageId: STATUS_PNP_BAD_MPS_TABLE
//
// MessageText:
//
// A device is missing in the system BIOS MPS table. This device will not be used.
// Please contact your system vendor for system BIOS update.
//
#ifndef STATUS_PNP_BAD_MPS_TABLE
#define STATUS_PNP_BAD_MPS_TABLE         ((NTSTATUS)0xC0040035L)
#endif//STATUS_PNP_BAD_MPS_TABLE

//
// MessageId: STATUS_PNP_TRANSLATION_FAILED
//
// MessageText:
//
// A translator failed to translate resources.
//
#ifndef STATUS_PNP_TRANSLATION_FAILED
#define STATUS_PNP_TRANSLATION_FAILED    ((NTSTATUS)0xC0040036L)
#endif//STATUS_PNP_TRANSLATION_FAILED

//
// MessageId: STATUS_PNP_IRQ_TRANSLATION_FAILED
//
// MessageText:
//
// A IRQ translator failed to translate resources.
//
#ifndef STATUS_PNP_IRQ_TRANSLATION_FAILED
#define STATUS_PNP_IRQ_TRANSLATION_FAILED ((NTSTATUS)0xC0040037L)
#endif//STATUS_PNP_IRQ_TRANSLATION_FAILED

//
// MessageId: STATUS_PNP_INVALID_ID
//
// MessageText:
//
// Driver %2 returned invalid ID for a child device (%3).
//
#ifndef STATUS_PNP_INVALID_ID
#define STATUS_PNP_INVALID_ID            ((NTSTATUS)0xC0040038L)
#endif//STATUS_PNP_INVALID_ID

//
// MessageId: STATUS_IO_REISSUE_AS_CACHED
//
// MessageText:
//
// Reissue the given operation as a cached IO operation
//
#ifndef STATUS_IO_REISSUE_AS_CACHED
#define STATUS_IO_REISSUE_AS_CACHED      ((NTSTATUS)0xC0040039L)
#endif//STATUS_IO_REISSUE_AS_CACHED


//
//  MUI error values
//

//
// MessageId: STATUS_MUI_FILE_NOT_FOUND
//
// MessageText:
//
// The resource loader failed to find MUI file.
//
#ifndef STATUS_MUI_FILE_NOT_FOUND
#define STATUS_MUI_FILE_NOT_FOUND        ((NTSTATUS)0xC00B0001L)
#endif//STATUS_MUI_FILE_NOT_FOUND

//
// MessageId: STATUS_MUI_INVALID_FILE
//
// MessageText:
//
// The resource loader failed to load MUI file because the file fail to pass validation.
//
#ifndef STATUS_MUI_INVALID_FILE
#define STATUS_MUI_INVALID_FILE          ((NTSTATUS)0xC00B0002L)
#endif//STATUS_MUI_INVALID_FILE

//
// MessageId: STATUS_MUI_INVALID_RC_CONFIG
//
// MessageText:
//
// The RC Manifest is corrupted with garbage data or unsupported version or missing required item.
//
#ifndef STATUS_MUI_INVALID_RC_CONFIG
#define STATUS_MUI_INVALID_RC_CONFIG     ((NTSTATUS)0xC00B0003L)
#endif//STATUS_MUI_INVALID_RC_CONFIG

//
// MessageId: STATUS_MUI_INVALID_LOCALE_NAME
//
// MessageText:
//
// The RC Manifest has invalid culture name.
//
#ifndef STATUS_MUI_INVALID_LOCALE_NAME
#define STATUS_MUI_INVALID_LOCALE_NAME   ((NTSTATUS)0xC00B0004L)
#endif//STATUS_MUI_INVALID_LOCALE_NAME

//
// MessageId: STATUS_MUI_INVALID_ULTIMATEFALLBACK_NAME
//
// MessageText:
//
// The RC Manifest has invalid ultimatefallback name.
//
#ifndef STATUS_MUI_INVALID_ULTIMATEFALLBACK_NAME
#define STATUS_MUI_INVALID_ULTIMATEFALLBACK_NAME ((NTSTATUS)0xC00B0005L)
#endif//STATUS_MUI_INVALID_ULTIMATEFALLBACK_NAME

//
// MessageId: STATUS_MUI_FILE_NOT_LOADED
//
// MessageText:
//
// The resource loader cache doesn't have loaded MUI entry.
//
#ifndef STATUS_MUI_FILE_NOT_LOADED
#define STATUS_MUI_FILE_NOT_LOADED       ((NTSTATUS)0xC00B0006L)
#endif//STATUS_MUI_FILE_NOT_LOADED

//
// MessageId: STATUS_RESOURCE_ENUM_USER_STOP
//
// MessageText:
//
// User stopped resource enumeration.
//
#ifndef STATUS_RESOURCE_ENUM_USER_STOP
#define STATUS_RESOURCE_ENUM_USER_STOP   ((NTSTATUS)0xC00B0007L)
#endif//STATUS_RESOURCE_ENUM_USER_STOP


//
//  Filter Manager error values
//

//
//  Translation macro for converting:
//     HRESULT --> NTSTATUS
//

#define FILTER_FLT_NTSTATUS_FROM_HRESULT(x) ((NTSTATUS) (((x) & 0xC0007FFF) | (FACILITY_FILTER_MANAGER << 16) | 0x40000000))

//
// MessageId: STATUS_FLT_NO_HANDLER_DEFINED
//
// MessageText:
//
// A handler was not defined by the filter for this operation.
//
#ifndef STATUS_FLT_NO_HANDLER_DEFINED
#define STATUS_FLT_NO_HANDLER_DEFINED    ((NTSTATUS)0xC01C0001L)
#endif//STATUS_FLT_NO_HANDLER_DEFINED

//
// MessageId: STATUS_FLT_CONTEXT_ALREADY_DEFINED
//
// MessageText:
//
// A context is already defined for this object.
//
#ifndef STATUS_FLT_CONTEXT_ALREADY_DEFINED
#define STATUS_FLT_CONTEXT_ALREADY_DEFINED ((NTSTATUS)0xC01C0002L)
#endif//STATUS_FLT_CONTEXT_ALREADY_DEFINED

//
// MessageId: STATUS_FLT_INVALID_ASYNCHRONOUS_REQUEST
//
// MessageText:
//
// Asynchronous requests are not valid for this operation.
//
#ifndef STATUS_FLT_INVALID_ASYNCHRONOUS_REQUEST
#define STATUS_FLT_INVALID_ASYNCHRONOUS_REQUEST ((NTSTATUS)0xC01C0003L)
#endif//STATUS_FLT_INVALID_ASYNCHRONOUS_REQUEST

//
// MessageId: STATUS_FLT_DISALLOW_FAST_IO
//
// MessageText:
//
// Internal error code used by the filter manager to determine if a fastio operation should be forced down the IRP path. Mini-filters should never return this value.
//
#ifndef STATUS_FLT_DISALLOW_FAST_IO
#define STATUS_FLT_DISALLOW_FAST_IO      ((NTSTATUS)0xC01C0004L)
#endif//STATUS_FLT_DISALLOW_FAST_IO

//
//  The same code used to disallow fast IO is also used to disallow the FS
//  filter QueryOpen callback.
//

#ifndef STATUS_FLT_DISALLOW_FSFILTER_IO
#define STATUS_FLT_DISALLOW_FSFILTER_IO STATUS_FLT_DISALLOW_FAST_IO
#endif//STATUS_FLT_DISALLOW_FSFILTER_IO

//
// MessageId: STATUS_FLT_INVALID_NAME_REQUEST
//
// MessageText:
//
// An invalid name request was made. The name requested cannot be retrieved at this time.
//
#ifndef STATUS_FLT_INVALID_NAME_REQUEST
#define STATUS_FLT_INVALID_NAME_REQUEST  ((NTSTATUS)0xC01C0005L)
#endif//STATUS_FLT_INVALID_NAME_REQUEST

//
// MessageId: STATUS_FLT_NOT_SAFE_TO_POST_OPERATION
//
// MessageText:
//
// Posting this operation to a worker thread for further processing is not safe at this time because it could lead to a system deadlock.
//
#ifndef STATUS_FLT_NOT_SAFE_TO_POST_OPERATION
#define STATUS_FLT_NOT_SAFE_TO_POST_OPERATION ((NTSTATUS)0xC01C0006L)
#endif//STATUS_FLT_NOT_SAFE_TO_POST_OPERATION

//
// MessageId: STATUS_FLT_NOT_INITIALIZED
//
// MessageText:
//
// The Filter Manager was not initialized when a filter tried to register. Make sure that the Filter Manager is getting loaded as a driver.
//
#ifndef STATUS_FLT_NOT_INITIALIZED
#define STATUS_FLT_NOT_INITIALIZED       ((NTSTATUS)0xC01C0007L)
#endif//STATUS_FLT_NOT_INITIALIZED

//
// MessageId: STATUS_FLT_FILTER_NOT_READY
//
// MessageText:
//
// The filter is not ready for attachment to volumes because it has not finished initializing (FltStartFiltering has not been called).
//
#ifndef STATUS_FLT_FILTER_NOT_READY
#define STATUS_FLT_FILTER_NOT_READY      ((NTSTATUS)0xC01C0008L)
#endif//STATUS_FLT_FILTER_NOT_READY

//
// MessageId: STATUS_FLT_POST_OPERATION_CLEANUP
//
// MessageText:
//
// The filter must cleanup any operation specific context at this time because it is being removed from the system before the operation is completed by the lower drivers.
//
#ifndef STATUS_FLT_POST_OPERATION_CLEANUP
#define STATUS_FLT_POST_OPERATION_CLEANUP ((NTSTATUS)0xC01C0009L)
#endif//STATUS_FLT_POST_OPERATION_CLEANUP

//
// MessageId: STATUS_FLT_INTERNAL_ERROR
//
// MessageText:
//
// The Filter Manager had an internal error from which it cannot recover, therefore the operation has been failed. This is usually the result of a filter returning an invalid value from a pre-operation callback.
//
#ifndef STATUS_FLT_INTERNAL_ERROR
#define STATUS_FLT_INTERNAL_ERROR        ((NTSTATUS)0xC01C000AL)
#endif//STATUS_FLT_INTERNAL_ERROR

//
// MessageId: STATUS_FLT_DELETING_OBJECT
//
// MessageText:
//
// The object specified for this action is in the process of being deleted, therefore the action requested cannot be completed at this time.
//
#ifndef STATUS_FLT_DELETING_OBJECT
#define STATUS_FLT_DELETING_OBJECT       ((NTSTATUS)0xC01C000BL)
#endif//STATUS_FLT_DELETING_OBJECT

//
// MessageId: STATUS_FLT_MUST_BE_NONPAGED_POOL
//
// MessageText:
//
// Non-paged pool must be used for this type of context.
//
#ifndef STATUS_FLT_MUST_BE_NONPAGED_POOL
#define STATUS_FLT_MUST_BE_NONPAGED_POOL ((NTSTATUS)0xC01C000CL)
#endif//STATUS_FLT_MUST_BE_NONPAGED_POOL

//
// MessageId: STATUS_FLT_DUPLICATE_ENTRY
//
// MessageText:
//
// A duplicate handler definition has been provided for an operation.
//
#ifndef STATUS_FLT_DUPLICATE_ENTRY
#define STATUS_FLT_DUPLICATE_ENTRY       ((NTSTATUS)0xC01C000DL)
#endif//STATUS_FLT_DUPLICATE_ENTRY

//
// MessageId: STATUS_FLT_CBDQ_DISABLED
//
// MessageText:
//
// The callback data queue has been disabled.
//
#ifndef STATUS_FLT_CBDQ_DISABLED
#define STATUS_FLT_CBDQ_DISABLED         ((NTSTATUS)0xC01C000EL)
#endif//STATUS_FLT_CBDQ_DISABLED

//
// MessageId: STATUS_FLT_DO_NOT_ATTACH
//
// MessageText:
//
// Do not attach the filter to the volume at this time.
//
#ifndef STATUS_FLT_DO_NOT_ATTACH
#define STATUS_FLT_DO_NOT_ATTACH         ((NTSTATUS)0xC01C000FL)
#endif//STATUS_FLT_DO_NOT_ATTACH

//
// MessageId: STATUS_FLT_DO_NOT_DETACH
//
// MessageText:
//
// Do not detach the filter from the volume at this time.
//
#ifndef STATUS_FLT_DO_NOT_DETACH
#define STATUS_FLT_DO_NOT_DETACH         ((NTSTATUS)0xC01C0010L)
#endif//STATUS_FLT_DO_NOT_DETACH

//
// MessageId: STATUS_FLT_INSTANCE_ALTITUDE_COLLISION
//
// MessageText:
//
// An instance already exists at this altitude on the volume specified.
//
#ifndef STATUS_FLT_INSTANCE_ALTITUDE_COLLISION
#define STATUS_FLT_INSTANCE_ALTITUDE_COLLISION ((NTSTATUS)0xC01C0011L)
#endif//STATUS_FLT_INSTANCE_ALTITUDE_COLLISION

//
// MessageId: STATUS_FLT_INSTANCE_NAME_COLLISION
//
// MessageText:
//
// An instance already exists with this name on the volume specified.
//
#ifndef STATUS_FLT_INSTANCE_NAME_COLLISION
#define STATUS_FLT_INSTANCE_NAME_COLLISION ((NTSTATUS)0xC01C0012L)
#endif//STATUS_FLT_INSTANCE_NAME_COLLISION

//
// MessageId: STATUS_FLT_FILTER_NOT_FOUND
//
// MessageText:
//
// The system could not find the filter specified.
//
#ifndef STATUS_FLT_FILTER_NOT_FOUND
#define STATUS_FLT_FILTER_NOT_FOUND      ((NTSTATUS)0xC01C0013L)
#endif//STATUS_FLT_FILTER_NOT_FOUND

//
// MessageId: STATUS_FLT_VOLUME_NOT_FOUND
//
// MessageText:
//
// The system could not find the volume specified.
//
#ifndef STATUS_FLT_VOLUME_NOT_FOUND
#define STATUS_FLT_VOLUME_NOT_FOUND      ((NTSTATUS)0xC01C0014L)
#endif//STATUS_FLT_VOLUME_NOT_FOUND

//
// MessageId: STATUS_FLT_INSTANCE_NOT_FOUND
//
// MessageText:
//
// The system could not find the instance specified.
//
#ifndef STATUS_FLT_INSTANCE_NOT_FOUND
#define STATUS_FLT_INSTANCE_NOT_FOUND    ((NTSTATUS)0xC01C0015L)
#endif//STATUS_FLT_INSTANCE_NOT_FOUND

//
// MessageId: STATUS_FLT_CONTEXT_ALLOCATION_NOT_FOUND
//
// MessageText:
//
// No registered context allocation definition was found for the given request.
//
#ifndef STATUS_FLT_CONTEXT_ALLOCATION_NOT_FOUND
#define STATUS_FLT_CONTEXT_ALLOCATION_NOT_FOUND ((NTSTATUS)0xC01C0016L)
#endif//STATUS_FLT_CONTEXT_ALLOCATION_NOT_FOUND

//
// MessageId: STATUS_FLT_INVALID_CONTEXT_REGISTRATION
//
// MessageText:
//
// An invalid parameter was specified during context registration.
//
#ifndef STATUS_FLT_INVALID_CONTEXT_REGISTRATION
#define STATUS_FLT_INVALID_CONTEXT_REGISTRATION ((NTSTATUS)0xC01C0017L)
#endif//STATUS_FLT_INVALID_CONTEXT_REGISTRATION

//
// MessageId: STATUS_FLT_NAME_CACHE_MISS
//
// MessageText:
//
// The name requested was not found in Filter Manager's name cache and could not be retrieved from the file system.
//
#ifndef STATUS_FLT_NAME_CACHE_MISS
#define STATUS_FLT_NAME_CACHE_MISS       ((NTSTATUS)0xC01C0018L)
#endif//STATUS_FLT_NAME_CACHE_MISS

//
// MessageId: STATUS_FLT_NO_DEVICE_OBJECT
//
// MessageText:
//
// The requested device object does not exist for the given volume.
//
#ifndef STATUS_FLT_NO_DEVICE_OBJECT
#define STATUS_FLT_NO_DEVICE_OBJECT      ((NTSTATUS)0xC01C0019L)
#endif//STATUS_FLT_NO_DEVICE_OBJECT

//
// MessageId: STATUS_FLT_VOLUME_ALREADY_MOUNTED
//
// MessageText:
//
// The specified volume is already mounted.
//
#ifndef STATUS_FLT_VOLUME_ALREADY_MOUNTED
#define STATUS_FLT_VOLUME_ALREADY_MOUNTED ((NTSTATUS)0xC01C001AL)
#endif//STATUS_FLT_VOLUME_ALREADY_MOUNTED

//
// MessageId: STATUS_FLT_ALREADY_ENLISTED
//
// MessageText:
//
// The specified Transaction Context is already enlisted in a transaction
//
#ifndef STATUS_FLT_ALREADY_ENLISTED
#define STATUS_FLT_ALREADY_ENLISTED      ((NTSTATUS)0xC01C001BL)
#endif//STATUS_FLT_ALREADY_ENLISTED

//
// MessageId: STATUS_FLT_CONTEXT_ALREADY_LINKED
//
// MessageText:
//
// The specifiec context is already attached to another object
//
#ifndef STATUS_FLT_CONTEXT_ALREADY_LINKED
#define STATUS_FLT_CONTEXT_ALREADY_LINKED ((NTSTATUS)0xC01C001CL)
#endif//STATUS_FLT_CONTEXT_ALREADY_LINKED

//
// MessageId: STATUS_FLT_NO_WAITER_FOR_REPLY
//
// MessageText:
//
// No waiter is present for the filter's reply to this message.
//
#ifndef STATUS_FLT_NO_WAITER_FOR_REPLY
#define STATUS_FLT_NO_WAITER_FOR_REPLY   ((NTSTATUS)0xC01C0020L)
#endif//STATUS_FLT_NO_WAITER_FOR_REPLY

//
// MessageId: STATUS_FLT_REGISTRATION_BUSY
//
// MessageText:
//
// The filesystem database resource is in use. Registration cannot complete at this time.
//
#ifndef STATUS_FLT_REGISTRATION_BUSY
#define STATUS_FLT_REGISTRATION_BUSY     ((NTSTATUS)0xC01C0023L)
#endif//STATUS_FLT_REGISTRATION_BUSY


//
//  Side-by-side (SXS) error values
//

//
// MessageId: STATUS_SXS_SECTION_NOT_FOUND
//
// MessageText:
//
// The requested section is not present in the activation context.
//
#ifndef STATUS_SXS_SECTION_NOT_FOUND
#define STATUS_SXS_SECTION_NOT_FOUND     ((NTSTATUS)0xC0150001L)
#endif//STATUS_SXS_SECTION_NOT_FOUND

//
// MessageId: STATUS_SXS_CANT_GEN_ACTCTX
//
// MessageText:
//
// Windows was not able to process the application binding information.
// Please refer to your System Event Log for further information.
//
#ifndef STATUS_SXS_CANT_GEN_ACTCTX
#define STATUS_SXS_CANT_GEN_ACTCTX       ((NTSTATUS)0xC0150002L)
#endif//STATUS_SXS_CANT_GEN_ACTCTX

//
// MessageId: STATUS_SXS_INVALID_ACTCTXDATA_FORMAT
//
// MessageText:
//
// The application binding data format is invalid.
//
#ifndef STATUS_SXS_INVALID_ACTCTXDATA_FORMAT
#define STATUS_SXS_INVALID_ACTCTXDATA_FORMAT ((NTSTATUS)0xC0150003L)
#endif//STATUS_SXS_INVALID_ACTCTXDATA_FORMAT

//
// MessageId: STATUS_SXS_ASSEMBLY_NOT_FOUND
//
// MessageText:
//
// The referenced assembly is not installed on your system.
//
#ifndef STATUS_SXS_ASSEMBLY_NOT_FOUND
#define STATUS_SXS_ASSEMBLY_NOT_FOUND    ((NTSTATUS)0xC0150004L)
#endif//STATUS_SXS_ASSEMBLY_NOT_FOUND

//
// MessageId: STATUS_SXS_MANIFEST_FORMAT_ERROR
//
// MessageText:
//
// The manifest file does not begin with the required tag and format information.
//
#ifndef STATUS_SXS_MANIFEST_FORMAT_ERROR
#define STATUS_SXS_MANIFEST_FORMAT_ERROR ((NTSTATUS)0xC0150005L)
#endif//STATUS_SXS_MANIFEST_FORMAT_ERROR

//
// MessageId: STATUS_SXS_MANIFEST_PARSE_ERROR
//
// MessageText:
//
// The manifest file contains one or more syntax errors.
//
#ifndef STATUS_SXS_MANIFEST_PARSE_ERROR
#define STATUS_SXS_MANIFEST_PARSE_ERROR  ((NTSTATUS)0xC0150006L)
#endif//STATUS_SXS_MANIFEST_PARSE_ERROR

//
// MessageId: STATUS_SXS_ACTIVATION_CONTEXT_DISABLED
//
// MessageText:
//
// The application attempted to activate a disabled activation context.
//
#ifndef STATUS_SXS_ACTIVATION_CONTEXT_DISABLED
#define STATUS_SXS_ACTIVATION_CONTEXT_DISABLED ((NTSTATUS)0xC0150007L)
#endif//STATUS_SXS_ACTIVATION_CONTEXT_DISABLED

//
// MessageId: STATUS_SXS_KEY_NOT_FOUND
//
// MessageText:
//
// The requested lookup key was not found in any active activation context.
//
#ifndef STATUS_SXS_KEY_NOT_FOUND
#define STATUS_SXS_KEY_NOT_FOUND         ((NTSTATUS)0xC0150008L)
#endif//STATUS_SXS_KEY_NOT_FOUND

//
// MessageId: STATUS_SXS_VERSION_CONFLICT
//
// MessageText:
//
// A component version required by the application conflicts with another component version already active.
//
#ifndef STATUS_SXS_VERSION_CONFLICT
#define STATUS_SXS_VERSION_CONFLICT      ((NTSTATUS)0xC0150009L)
#endif//STATUS_SXS_VERSION_CONFLICT

//
// MessageId: STATUS_SXS_WRONG_SECTION_TYPE
//
// MessageText:
//
// The type requested activation context section does not match the query API used.
//
#ifndef STATUS_SXS_WRONG_SECTION_TYPE
#define STATUS_SXS_WRONG_SECTION_TYPE    ((NTSTATUS)0xC015000AL)
#endif//STATUS_SXS_WRONG_SECTION_TYPE

//
// MessageId: STATUS_SXS_THREAD_QUERIES_DISABLED
//
// MessageText:
//
// Lack of system resources has required isolated activation to be disabled for the current thread of execution.
//
#ifndef STATUS_SXS_THREAD_QUERIES_DISABLED
#define STATUS_SXS_THREAD_QUERIES_DISABLED ((NTSTATUS)0xC015000BL)
#endif//STATUS_SXS_THREAD_QUERIES_DISABLED

//
// MessageId: STATUS_SXS_ASSEMBLY_MISSING
//
// MessageText:
//
// The referenced assembly could not be found.
//
#ifndef STATUS_SXS_ASSEMBLY_MISSING
#define STATUS_SXS_ASSEMBLY_MISSING      ((NTSTATUS)0xC015000CL)
#endif//STATUS_SXS_ASSEMBLY_MISSING

//
// MessageId: STATUS_SXS_RELEASE_ACTIVATION_CONTEXT
//
// MessageText:
//
// A kernel mode component is releasing a reference on an activation context.
//
#ifndef STATUS_SXS_RELEASE_ACTIVATION_CONTEXT
#define STATUS_SXS_RELEASE_ACTIVATION_CONTEXT ((NTSTATUS)0x4015000DL)
#endif//STATUS_SXS_RELEASE_ACTIVATION_CONTEXT

//
// MessageId: STATUS_SXS_PROCESS_DEFAULT_ALREADY_SET
//
// MessageText:
//
// An attempt to set the process default activation context failed because the process default activation context was already set.
//
#ifndef STATUS_SXS_PROCESS_DEFAULT_ALREADY_SET
#define STATUS_SXS_PROCESS_DEFAULT_ALREADY_SET ((NTSTATUS)0xC015000EL)
#endif//STATUS_SXS_PROCESS_DEFAULT_ALREADY_SET

#if defined(STATUS_SUCCESS) || (_WIN32_WINNT > 0x0500) || (_WIN32_FUSION >= 0x0100) // winnt
//
// MessageId: STATUS_SXS_EARLY_DEACTIVATION
//
// MessageText:
//
// The activation context being deactivated is not the most recently activated one.
//
#ifndef STATUS_SXS_EARLY_DEACTIVATION
#define STATUS_SXS_EARLY_DEACTIVATION    ((NTSTATUS)0xC015000FL)    // winnt
#endif//STATUS_SXS_EARLY_DEACTIVATION

//
// MessageId: STATUS_SXS_INVALID_DEACTIVATION
//
// MessageText:
//
// The activation context being deactivated is not active for the current thread of execution.
//
#ifndef STATUS_SXS_INVALID_DEACTIVATION
#define STATUS_SXS_INVALID_DEACTIVATION  ((NTSTATUS)0xC0150010L)    // winnt
#endif//STATUS_SXS_INVALID_DEACTIVATION

#endif // winnt
//
// MessageId: STATUS_SXS_MULTIPLE_DEACTIVATION
//
// MessageText:
//
// The activation context being deactivated has already been deactivated.
//
#ifndef STATUS_SXS_MULTIPLE_DEACTIVATION
#define STATUS_SXS_MULTIPLE_DEACTIVATION ((NTSTATUS)0xC0150011L)
#endif//STATUS_SXS_MULTIPLE_DEACTIVATION

//
// MessageId: STATUS_SXS_SYSTEM_DEFAULT_ACTIVATION_CONTEXT_EMPTY
//
// MessageText:
//
// The activation context of system default assembly could not be generated.
//
#ifndef STATUS_SXS_SYSTEM_DEFAULT_ACTIVATION_CONTEXT_EMPTY
#define STATUS_SXS_SYSTEM_DEFAULT_ACTIVATION_CONTEXT_EMPTY ((NTSTATUS)0xC0150012L)
#endif//STATUS_SXS_SYSTEM_DEFAULT_ACTIVATION_CONTEXT_EMPTY

//
// MessageId: STATUS_SXS_PROCESS_TERMINATION_REQUESTED
//
// MessageText:
//
// A component used by the isolation facility has requested to terminate the process.
//
#ifndef STATUS_SXS_PROCESS_TERMINATION_REQUESTED
#define STATUS_SXS_PROCESS_TERMINATION_REQUESTED ((NTSTATUS)0xC0150013L)
#endif//STATUS_SXS_PROCESS_TERMINATION_REQUESTED

//
// MessageId: STATUS_SXS_CORRUPT_ACTIVATION_STACK
//
// MessageText:
//
// The activation context activation stack for the running thread of execution is corrupt.
//
#ifndef STATUS_SXS_CORRUPT_ACTIVATION_STACK
#define STATUS_SXS_CORRUPT_ACTIVATION_STACK ((NTSTATUS)0xC0150014L)
#endif//STATUS_SXS_CORRUPT_ACTIVATION_STACK

//
// MessageId: STATUS_SXS_CORRUPTION
//
// MessageText:
//
// The application isolation metadata for this process or thread has become corrupt.
//
#ifndef STATUS_SXS_CORRUPTION
#define STATUS_SXS_CORRUPTION            ((NTSTATUS)0xC0150015L)
#endif//STATUS_SXS_CORRUPTION

//
// MessageId: STATUS_SXS_INVALID_IDENTITY_ATTRIBUTE_VALUE
//
// MessageText:
//
// The value of an attribute in an identity is not within the legal range.
//
#ifndef STATUS_SXS_INVALID_IDENTITY_ATTRIBUTE_VALUE
#define STATUS_SXS_INVALID_IDENTITY_ATTRIBUTE_VALUE ((NTSTATUS)0xC0150016L)
#endif//STATUS_SXS_INVALID_IDENTITY_ATTRIBUTE_VALUE

//
// MessageId: STATUS_SXS_INVALID_IDENTITY_ATTRIBUTE_NAME
//
// MessageText:
//
// The name of an attribute in an identity is not within the legal range.
//
#ifndef STATUS_SXS_INVALID_IDENTITY_ATTRIBUTE_NAME
#define STATUS_SXS_INVALID_IDENTITY_ATTRIBUTE_NAME ((NTSTATUS)0xC0150017L)
#endif//STATUS_SXS_INVALID_IDENTITY_ATTRIBUTE_NAME

//
// MessageId: STATUS_SXS_IDENTITY_DUPLICATE_ATTRIBUTE
//
// MessageText:
//
// An identity contains two definitions for the same attribute.
//
#ifndef STATUS_SXS_IDENTITY_DUPLICATE_ATTRIBUTE
#define STATUS_SXS_IDENTITY_DUPLICATE_ATTRIBUTE ((NTSTATUS)0xC0150018L)
#endif//STATUS_SXS_IDENTITY_DUPLICATE_ATTRIBUTE

//
// MessageId: STATUS_SXS_IDENTITY_PARSE_ERROR
//
// MessageText:
//
// The identity string is malformed. This may be due to a trailing comma, more than two unnamed attributes, missing attribute name or missing attribute value.
//
#ifndef STATUS_SXS_IDENTITY_PARSE_ERROR
#define STATUS_SXS_IDENTITY_PARSE_ERROR  ((NTSTATUS)0xC0150019L)
#endif//STATUS_SXS_IDENTITY_PARSE_ERROR

//
// MessageId: STATUS_SXS_COMPONENT_STORE_CORRUPT
//
// MessageText:
//
// The component store has been corrupted.
//
#ifndef STATUS_SXS_COMPONENT_STORE_CORRUPT
#define STATUS_SXS_COMPONENT_STORE_CORRUPT ((NTSTATUS)0xC015001AL)
#endif//STATUS_SXS_COMPONENT_STORE_CORRUPT

//
// MessageId: STATUS_SXS_FILE_HASH_MISMATCH
//
// MessageText:
//
// A component's file does not match the verification information present in the component manifest.
//
#ifndef STATUS_SXS_FILE_HASH_MISMATCH
#define STATUS_SXS_FILE_HASH_MISMATCH    ((NTSTATUS)0xC015001BL)
#endif//STATUS_SXS_FILE_HASH_MISMATCH

//
// MessageId: STATUS_SXS_MANIFEST_IDENTITY_SAME_BUT_CONTENTS_DIFFERENT
//
// MessageText:
//
// The identities of the manifests are identical but their contents are different.
//
#ifndef STATUS_SXS_MANIFEST_IDENTITY_SAME_BUT_CONTENTS_DIFFERENT
#define STATUS_SXS_MANIFEST_IDENTITY_SAME_BUT_CONTENTS_DIFFERENT ((NTSTATUS)0xC015001CL)
#endif//STATUS_SXS_MANIFEST_IDENTITY_SAME_BUT_CONTENTS_DIFFERENT

//
// MessageId: STATUS_SXS_IDENTITIES_DIFFERENT
//
// MessageText:
//
// The component identities are different.
//
#ifndef STATUS_SXS_IDENTITIES_DIFFERENT
#define STATUS_SXS_IDENTITIES_DIFFERENT  ((NTSTATUS)0xC015001DL)
#endif//STATUS_SXS_IDENTITIES_DIFFERENT

//
// MessageId: STATUS_SXS_ASSEMBLY_IS_NOT_A_DEPLOYMENT
//
// MessageText:
//
// The assembly is not a deployment.
//
#ifndef STATUS_SXS_ASSEMBLY_IS_NOT_A_DEPLOYMENT
#define STATUS_SXS_ASSEMBLY_IS_NOT_A_DEPLOYMENT ((NTSTATUS)0xC015001EL)
#endif//STATUS_SXS_ASSEMBLY_IS_NOT_A_DEPLOYMENT

//
// MessageId: STATUS_SXS_FILE_NOT_PART_OF_ASSEMBLY
//
// MessageText:
//
// The file is not a part of the assembly.
//
#ifndef STATUS_SXS_FILE_NOT_PART_OF_ASSEMBLY
#define STATUS_SXS_FILE_NOT_PART_OF_ASSEMBLY ((NTSTATUS)0xC015001FL)
#endif//STATUS_SXS_FILE_NOT_PART_OF_ASSEMBLY

//
// MessageId: STATUS_ADVANCED_INSTALLER_FAILED
//
// MessageText:
//
// An advanced installer failed during setup or servicing.
//
#ifndef STATUS_ADVANCED_INSTALLER_FAILED
#define STATUS_ADVANCED_INSTALLER_FAILED ((NTSTATUS)0xC0150020L)
#endif//STATUS_ADVANCED_INSTALLER_FAILED

//
// MessageId: STATUS_XML_ENCODING_MISMATCH
//
// MessageText:
//
// The character encoding in the XML declaration did not match the encoding used in the document.
//
#ifndef STATUS_XML_ENCODING_MISMATCH
#define STATUS_XML_ENCODING_MISMATCH     ((NTSTATUS)0xC0150021L)
#endif//STATUS_XML_ENCODING_MISMATCH

//
// MessageId: STATUS_SXS_MANIFEST_TOO_BIG
//
// MessageText:
//
// The size of the manifest exceeds the maximum allowed.
//
#ifndef STATUS_SXS_MANIFEST_TOO_BIG
#define STATUS_SXS_MANIFEST_TOO_BIG      ((NTSTATUS)0xC0150022L)
#endif//STATUS_SXS_MANIFEST_TOO_BIG

//
// MessageId: STATUS_SXS_SETTING_NOT_REGISTERED
//
// MessageText:
//
// The setting is not registered.
//
#ifndef STATUS_SXS_SETTING_NOT_REGISTERED
#define STATUS_SXS_SETTING_NOT_REGISTERED ((NTSTATUS)0xC0150023L)
#endif//STATUS_SXS_SETTING_NOT_REGISTERED

//
// MessageId: STATUS_SXS_TRANSACTION_CLOSURE_INCOMPLETE
//
// MessageText:
//
// One or more required members of the transaction are not present.
//
#ifndef STATUS_SXS_TRANSACTION_CLOSURE_INCOMPLETE
#define STATUS_SXS_TRANSACTION_CLOSURE_INCOMPLETE ((NTSTATUS)0xC0150024L)
#endif//STATUS_SXS_TRANSACTION_CLOSURE_INCOMPLETE

//
// MessageId: STATUS_SMI_PRIMITIVE_INSTALLER_FAILED
//
// MessageText:
//
// The SMI primitive installer failed during setup or servicing.
//
#ifndef STATUS_SMI_PRIMITIVE_INSTALLER_FAILED
#define STATUS_SMI_PRIMITIVE_INSTALLER_FAILED ((NTSTATUS)0xC0150025L)
#endif//STATUS_SMI_PRIMITIVE_INSTALLER_FAILED

//
// MessageId: STATUS_GENERIC_COMMAND_FAILED
//
// MessageText:
//
// A generic command executable returned a result that indicates failure.
//
#ifndef STATUS_GENERIC_COMMAND_FAILED
#define STATUS_GENERIC_COMMAND_FAILED    ((NTSTATUS)0xC0150026L)
#endif//STATUS_GENERIC_COMMAND_FAILED

//
// MessageId: STATUS_SXS_FILE_HASH_MISSING
//
// MessageText:
//
// A component is missing file verification information in its manifest.
//
#ifndef STATUS_SXS_FILE_HASH_MISSING
#define STATUS_SXS_FILE_HASH_MISSING     ((NTSTATUS)0xC0150027L)
#endif//STATUS_SXS_FILE_HASH_MISSING


//
//  Cluster error values
//

//
// MessageId: STATUS_CLUSTER_INVALID_NODE
//
// MessageText:
//
// The cluster node is not valid.
//
#ifndef STATUS_CLUSTER_INVALID_NODE
#define STATUS_CLUSTER_INVALID_NODE      ((NTSTATUS)0xC0130001L)
#endif//STATUS_CLUSTER_INVALID_NODE

//
// MessageId: STATUS_CLUSTER_NODE_EXISTS
//
// MessageText:
//
// The cluster node already exists.
//
#ifndef STATUS_CLUSTER_NODE_EXISTS
#define STATUS_CLUSTER_NODE_EXISTS       ((NTSTATUS)0xC0130002L)
#endif//STATUS_CLUSTER_NODE_EXISTS

//
// MessageId: STATUS_CLUSTER_JOIN_IN_PROGRESS
//
// MessageText:
//
// A node is in the process of joining the cluster.
//
#ifndef STATUS_CLUSTER_JOIN_IN_PROGRESS
#define STATUS_CLUSTER_JOIN_IN_PROGRESS  ((NTSTATUS)0xC0130003L)
#endif//STATUS_CLUSTER_JOIN_IN_PROGRESS

//
// MessageId: STATUS_CLUSTER_NODE_NOT_FOUND
//
// MessageText:
//
// The cluster node was not found.
//
#ifndef STATUS_CLUSTER_NODE_NOT_FOUND
#define STATUS_CLUSTER_NODE_NOT_FOUND    ((NTSTATUS)0xC0130004L)
#endif//STATUS_CLUSTER_NODE_NOT_FOUND

//
// MessageId: STATUS_CLUSTER_LOCAL_NODE_NOT_FOUND
//
// MessageText:
//
// The cluster local node information was not found.
//
#ifndef STATUS_CLUSTER_LOCAL_NODE_NOT_FOUND
#define STATUS_CLUSTER_LOCAL_NODE_NOT_FOUND ((NTSTATUS)0xC0130005L)
#endif//STATUS_CLUSTER_LOCAL_NODE_NOT_FOUND

//
// MessageId: STATUS_CLUSTER_NETWORK_EXISTS
//
// MessageText:
//
// The cluster network already exists.
//
#ifndef STATUS_CLUSTER_NETWORK_EXISTS
#define STATUS_CLUSTER_NETWORK_EXISTS    ((NTSTATUS)0xC0130006L)
#endif//STATUS_CLUSTER_NETWORK_EXISTS

//
// MessageId: STATUS_CLUSTER_NETWORK_NOT_FOUND
//
// MessageText:
//
// The cluster network was not found.
//
#ifndef STATUS_CLUSTER_NETWORK_NOT_FOUND
#define STATUS_CLUSTER_NETWORK_NOT_FOUND ((NTSTATUS)0xC0130007L)
#endif//STATUS_CLUSTER_NETWORK_NOT_FOUND

//
// MessageId: STATUS_CLUSTER_NETINTERFACE_EXISTS
//
// MessageText:
//
// The cluster network interface already exists.
//
#ifndef STATUS_CLUSTER_NETINTERFACE_EXISTS
#define STATUS_CLUSTER_NETINTERFACE_EXISTS ((NTSTATUS)0xC0130008L)
#endif//STATUS_CLUSTER_NETINTERFACE_EXISTS

//
// MessageId: STATUS_CLUSTER_NETINTERFACE_NOT_FOUND
//
// MessageText:
//
// The cluster network interface was not found.
//
#ifndef STATUS_CLUSTER_NETINTERFACE_NOT_FOUND
#define STATUS_CLUSTER_NETINTERFACE_NOT_FOUND ((NTSTATUS)0xC0130009L)
#endif//STATUS_CLUSTER_NETINTERFACE_NOT_FOUND

//
// MessageId: STATUS_CLUSTER_INVALID_REQUEST
//
// MessageText:
//
// The cluster request is not valid for this object.
//
#ifndef STATUS_CLUSTER_INVALID_REQUEST
#define STATUS_CLUSTER_INVALID_REQUEST   ((NTSTATUS)0xC013000AL)
#endif//STATUS_CLUSTER_INVALID_REQUEST

//
// MessageId: STATUS_CLUSTER_INVALID_NETWORK_PROVIDER
//
// MessageText:
//
// The cluster network provider is not valid.
//
#ifndef STATUS_CLUSTER_INVALID_NETWORK_PROVIDER
#define STATUS_CLUSTER_INVALID_NETWORK_PROVIDER ((NTSTATUS)0xC013000BL)
#endif//STATUS_CLUSTER_INVALID_NETWORK_PROVIDER

//
// MessageId: STATUS_CLUSTER_NODE_DOWN
//
// MessageText:
//
// The cluster node is down.
//
#ifndef STATUS_CLUSTER_NODE_DOWN
#define STATUS_CLUSTER_NODE_DOWN         ((NTSTATUS)0xC013000CL)
#endif//STATUS_CLUSTER_NODE_DOWN

//
// MessageId: STATUS_CLUSTER_NODE_UNREACHABLE
//
// MessageText:
//
// The cluster node is not reachable.
//
#ifndef STATUS_CLUSTER_NODE_UNREACHABLE
#define STATUS_CLUSTER_NODE_UNREACHABLE  ((NTSTATUS)0xC013000DL)
#endif//STATUS_CLUSTER_NODE_UNREACHABLE

//
// MessageId: STATUS_CLUSTER_NODE_NOT_MEMBER
//
// MessageText:
//
// The cluster node is not a member of the cluster.
//
#ifndef STATUS_CLUSTER_NODE_NOT_MEMBER
#define STATUS_CLUSTER_NODE_NOT_MEMBER   ((NTSTATUS)0xC013000EL)
#endif//STATUS_CLUSTER_NODE_NOT_MEMBER

//
// MessageId: STATUS_CLUSTER_JOIN_NOT_IN_PROGRESS
//
// MessageText:
//
// A cluster join operation is not in progress.
//
#ifndef STATUS_CLUSTER_JOIN_NOT_IN_PROGRESS
#define STATUS_CLUSTER_JOIN_NOT_IN_PROGRESS ((NTSTATUS)0xC013000FL)
#endif//STATUS_CLUSTER_JOIN_NOT_IN_PROGRESS

//
// MessageId: STATUS_CLUSTER_INVALID_NETWORK
//
// MessageText:
//
// The cluster network is not valid.
//
#ifndef STATUS_CLUSTER_INVALID_NETWORK
#define STATUS_CLUSTER_INVALID_NETWORK   ((NTSTATUS)0xC0130010L)
#endif//STATUS_CLUSTER_INVALID_NETWORK

//
// MessageId: STATUS_CLUSTER_NO_NET_ADAPTERS
//
// MessageText:
//
// No network adapters are available.
//
#ifndef STATUS_CLUSTER_NO_NET_ADAPTERS
#define STATUS_CLUSTER_NO_NET_ADAPTERS   ((NTSTATUS)0xC0130011L)
#endif//STATUS_CLUSTER_NO_NET_ADAPTERS

//
// MessageId: STATUS_CLUSTER_NODE_UP
//
// MessageText:
//
// The cluster node is up.
//
#ifndef STATUS_CLUSTER_NODE_UP
#define STATUS_CLUSTER_NODE_UP           ((NTSTATUS)0xC0130012L)
#endif//STATUS_CLUSTER_NODE_UP

//
// MessageId: STATUS_CLUSTER_NODE_PAUSED
//
// MessageText:
//
// The cluster node is paused.
//
#ifndef STATUS_CLUSTER_NODE_PAUSED
#define STATUS_CLUSTER_NODE_PAUSED       ((NTSTATUS)0xC0130013L)
#endif//STATUS_CLUSTER_NODE_PAUSED

//
// MessageId: STATUS_CLUSTER_NODE_NOT_PAUSED
//
// MessageText:
//
// The cluster node is not paused.
//
#ifndef STATUS_CLUSTER_NODE_NOT_PAUSED
#define STATUS_CLUSTER_NODE_NOT_PAUSED   ((NTSTATUS)0xC0130014L)
#endif//STATUS_CLUSTER_NODE_NOT_PAUSED

//
// MessageId: STATUS_CLUSTER_NO_SECURITY_CONTEXT
//
// MessageText:
//
// No cluster security context is available.
//
#ifndef STATUS_CLUSTER_NO_SECURITY_CONTEXT
#define STATUS_CLUSTER_NO_SECURITY_CONTEXT ((NTSTATUS)0xC0130015L)
#endif//STATUS_CLUSTER_NO_SECURITY_CONTEXT

//
// MessageId: STATUS_CLUSTER_NETWORK_NOT_INTERNAL
//
// MessageText:
//
// The cluster network is not configured for internal cluster communication.
//
#ifndef STATUS_CLUSTER_NETWORK_NOT_INTERNAL
#define STATUS_CLUSTER_NETWORK_NOT_INTERNAL ((NTSTATUS)0xC0130016L)
#endif//STATUS_CLUSTER_NETWORK_NOT_INTERNAL

//
// MessageId: STATUS_CLUSTER_POISONED
//
// MessageText:
//
// The cluster node has been poisoned.
//
#ifndef STATUS_CLUSTER_POISONED
#define STATUS_CLUSTER_POISONED          ((NTSTATUS)0xC0130017L)
#endif//STATUS_CLUSTER_POISONED

//
// MessageId: STATUS_CLUSTER_NON_CSV_PATH
//
// MessageText:
//
// The path does not belong to a cluster shared volume.
//
#ifndef STATUS_CLUSTER_NON_CSV_PATH
#define STATUS_CLUSTER_NON_CSV_PATH      ((NTSTATUS)0xC0130018L)
#endif//STATUS_CLUSTER_NON_CSV_PATH

//
// MessageId: STATUS_CLUSTER_CSV_VOLUME_NOT_LOCAL
//
// MessageText:
//
// The cluster shared volume is not locally mounted.
//
#ifndef STATUS_CLUSTER_CSV_VOLUME_NOT_LOCAL
#define STATUS_CLUSTER_CSV_VOLUME_NOT_LOCAL ((NTSTATUS)0xC0130019L)
#endif//STATUS_CLUSTER_CSV_VOLUME_NOT_LOCAL

//
// MessageId: STATUS_CLUSTER_CSV_READ_OPLOCK_BREAK_IN_PROGRESS
//
// MessageText:
//
// The operation has failed because read oplock break is in progress.
//
#ifndef STATUS_CLUSTER_CSV_READ_OPLOCK_BREAK_IN_PROGRESS
#define STATUS_CLUSTER_CSV_READ_OPLOCK_BREAK_IN_PROGRESS ((NTSTATUS)0xC0130020L)
#endif//STATUS_CLUSTER_CSV_READ_OPLOCK_BREAK_IN_PROGRESS

//
// MessageId: STATUS_CLUSTER_CSV_AUTO_PAUSE_ERROR
//
// MessageText:
//
// The operation has failed. CSVFS has to pause and refresh information.
//
#ifndef STATUS_CLUSTER_CSV_AUTO_PAUSE_ERROR
#define STATUS_CLUSTER_CSV_AUTO_PAUSE_ERROR ((NTSTATUS)0xC0130021L)
#endif//STATUS_CLUSTER_CSV_AUTO_PAUSE_ERROR

//
// MessageId: STATUS_CLUSTER_CSV_REDIRECTED
//
// MessageText:
//
// The operation has failed. CSVFS does not allow block i/o in redirected mode.
//
#ifndef STATUS_CLUSTER_CSV_REDIRECTED
#define STATUS_CLUSTER_CSV_REDIRECTED    ((NTSTATUS)0xC0130022L)
#endif//STATUS_CLUSTER_CSV_REDIRECTED

//
// MessageId: STATUS_CLUSTER_CSV_NOT_REDIRECTED
//
// MessageText:
//
// The operation has failed. CSVFS is not in redirected mode.
//
#ifndef STATUS_CLUSTER_CSV_NOT_REDIRECTED
#define STATUS_CLUSTER_CSV_NOT_REDIRECTED ((NTSTATUS)0xC0130023L)
#endif//STATUS_CLUSTER_CSV_NOT_REDIRECTED

//
// MessageId: STATUS_CLUSTER_CSV_VOLUME_DRAINING
//
// MessageText:
//
// CSVFS is failing operation because it is in draining state.
//
#ifndef STATUS_CLUSTER_CSV_VOLUME_DRAINING
#define STATUS_CLUSTER_CSV_VOLUME_DRAINING ((NTSTATUS)0xC0130024L)
#endif//STATUS_CLUSTER_CSV_VOLUME_DRAINING

//
// MessageId: STATUS_CLUSTER_CSV_SNAPSHOT_CREATION_IN_PROGRESS
//
// MessageText:
//
// The operation has failed because snapshot creation is in progress.
//
#ifndef STATUS_CLUSTER_CSV_SNAPSHOT_CREATION_IN_PROGRESS
#define STATUS_CLUSTER_CSV_SNAPSHOT_CREATION_IN_PROGRESS ((NTSTATUS)0xC0130025L)
#endif//STATUS_CLUSTER_CSV_SNAPSHOT_CREATION_IN_PROGRESS

//
// MessageId: STATUS_CLUSTER_CSV_VOLUME_DRAINING_SUCCEEDED_DOWNLEVEL
//
// MessageText:
//
// The operation has succeeded on the down level file system, but CSV is failing it because it is in draining state.
//
#ifndef STATUS_CLUSTER_CSV_VOLUME_DRAINING_SUCCEEDED_DOWNLEVEL
#define STATUS_CLUSTER_CSV_VOLUME_DRAINING_SUCCEEDED_DOWNLEVEL ((NTSTATUS)0xC0130026L)
#endif//STATUS_CLUSTER_CSV_VOLUME_DRAINING_SUCCEEDED_DOWNLEVEL

//
// MessageId: STATUS_CLUSTER_CSV_NO_SNAPSHOTS
//
// MessageText:
//
// Volsnap on the coordinating node returned an error indicating that there is no snapshots on this volume.
//
#ifndef STATUS_CLUSTER_CSV_NO_SNAPSHOTS
#define STATUS_CLUSTER_CSV_NO_SNAPSHOTS  ((NTSTATUS)0xC0130027L)
#endif//STATUS_CLUSTER_CSV_NO_SNAPSHOTS

//
// MessageId: STATUS_CSV_IO_PAUSE_TIMEOUT
//
// MessageText:
//
// The operation has failed because CSV volume was not able to recover in time specified on this file object.
//
#ifndef STATUS_CSV_IO_PAUSE_TIMEOUT
#define STATUS_CSV_IO_PAUSE_TIMEOUT      ((NTSTATUS)0xC0130028L)
#endif//STATUS_CSV_IO_PAUSE_TIMEOUT

//
// MessageId: STATUS_CLUSTER_CSV_INVALID_HANDLE
//
// MessageText:
//
// The operation has failed because CSV has invalidated this file object.
//
#ifndef STATUS_CLUSTER_CSV_INVALID_HANDLE
#define STATUS_CLUSTER_CSV_INVALID_HANDLE ((NTSTATUS)0xC0130029L)
#endif//STATUS_CLUSTER_CSV_INVALID_HANDLE

//
// MessageId: STATUS_CLUSTER_CSV_SUPPORTED_ONLY_ON_COORDINATOR
//
// MessageText:
//
// This operation is supported only on the CSV coordinator node.
//
#ifndef STATUS_CLUSTER_CSV_SUPPORTED_ONLY_ON_COORDINATOR
#define STATUS_CLUSTER_CSV_SUPPORTED_ONLY_ON_COORDINATOR ((NTSTATUS)0xC0130030L)
#endif//STATUS_CLUSTER_CSV_SUPPORTED_ONLY_ON_COORDINATOR

//
// MessageId: STATUS_CLUSTER_CAM_TICKET_REPLAY_DETECTED
//
// MessageText:
//
// Cluster CAM has detected that somone is trying to reply ticket.
//
#ifndef STATUS_CLUSTER_CAM_TICKET_REPLAY_DETECTED
#define STATUS_CLUSTER_CAM_TICKET_REPLAY_DETECTED ((NTSTATUS)0xC0130031L)
#endif//STATUS_CLUSTER_CAM_TICKET_REPLAY_DETECTED


//
//  Transaction Manager error values
//

//
// MessageId: STATUS_TRANSACTIONAL_CONFLICT
//
// MessageText:
//
// The function attempted to use a name that is reserved for use by another transaction.
//
#ifndef STATUS_TRANSACTIONAL_CONFLICT
#define STATUS_TRANSACTIONAL_CONFLICT    ((NTSTATUS)0xC0190001L)
#endif//STATUS_TRANSACTIONAL_CONFLICT

//
// MessageId: STATUS_INVALID_TRANSACTION
//
// MessageText:
//
// The transaction handle associated with this operation is not valid.
//
#ifndef STATUS_INVALID_TRANSACTION
#define STATUS_INVALID_TRANSACTION       ((NTSTATUS)0xC0190002L)
#endif//STATUS_INVALID_TRANSACTION

//
// MessageId: STATUS_TRANSACTION_NOT_ACTIVE
//
// MessageText:
//
// The requested operation was made in the context of a transaction that is no longer active.
//
#ifndef STATUS_TRANSACTION_NOT_ACTIVE
#define STATUS_TRANSACTION_NOT_ACTIVE    ((NTSTATUS)0xC0190003L)
#endif//STATUS_TRANSACTION_NOT_ACTIVE

//
// MessageId: STATUS_TM_INITIALIZATION_FAILED
//
// MessageText:
//
// The Transaction Manager was unable to be successfully initialized. Transacted operations are not supported.
//
#ifndef STATUS_TM_INITIALIZATION_FAILED
#define STATUS_TM_INITIALIZATION_FAILED  ((NTSTATUS)0xC0190004L)
#endif//STATUS_TM_INITIALIZATION_FAILED

//
// MessageId: STATUS_RM_NOT_ACTIVE
//
// MessageText:
//
// Transaction support within the specified resource manager is not started or was shut down due to an error.
//
#ifndef STATUS_RM_NOT_ACTIVE
#define STATUS_RM_NOT_ACTIVE             ((NTSTATUS)0xC0190005L)
#endif//STATUS_RM_NOT_ACTIVE

//
// MessageId: STATUS_RM_METADATA_CORRUPT
//
// MessageText:
//
// The metadata of the RM has been corrupted. The RM will not function.
//
#ifndef STATUS_RM_METADATA_CORRUPT
#define STATUS_RM_METADATA_CORRUPT       ((NTSTATUS)0xC0190006L)
#endif//STATUS_RM_METADATA_CORRUPT

//
// MessageId: STATUS_TRANSACTION_NOT_JOINED
//
// MessageText:
//
// The resource manager has attempted to prepare a transaction that it has not successfully joined.
//
#ifndef STATUS_TRANSACTION_NOT_JOINED
#define STATUS_TRANSACTION_NOT_JOINED    ((NTSTATUS)0xC0190007L)
#endif//STATUS_TRANSACTION_NOT_JOINED

//
// MessageId: STATUS_DIRECTORY_NOT_RM
//
// MessageText:
//
// The specified directory does not contain a file system resource manager.
//
#ifndef STATUS_DIRECTORY_NOT_RM
#define STATUS_DIRECTORY_NOT_RM          ((NTSTATUS)0xC0190008L)
#endif//STATUS_DIRECTORY_NOT_RM

//
// MessageId: STATUS_COULD_NOT_RESIZE_LOG
//
// MessageText:
//
// The log could not be set to the requested size.
//
#ifndef STATUS_COULD_NOT_RESIZE_LOG
#define STATUS_COULD_NOT_RESIZE_LOG      ((NTSTATUS)0x80190009L)
#endif//STATUS_COULD_NOT_RESIZE_LOG

//
// MessageId: STATUS_TRANSACTIONS_UNSUPPORTED_REMOTE
//
// MessageText:
//
// The remote server or share does not support transacted file operations.
//
#ifndef STATUS_TRANSACTIONS_UNSUPPORTED_REMOTE
#define STATUS_TRANSACTIONS_UNSUPPORTED_REMOTE ((NTSTATUS)0xC019000AL)
#endif//STATUS_TRANSACTIONS_UNSUPPORTED_REMOTE

//
// MessageId: STATUS_LOG_RESIZE_INVALID_SIZE
//
// MessageText:
//
// The requested log size for the file system resource manager is invalid.
//
#ifndef STATUS_LOG_RESIZE_INVALID_SIZE
#define STATUS_LOG_RESIZE_INVALID_SIZE   ((NTSTATUS)0xC019000BL)
#endif//STATUS_LOG_RESIZE_INVALID_SIZE

//
// MessageId: STATUS_REMOTE_FILE_VERSION_MISMATCH
//
// MessageText:
//
// The remote server sent mismatching version number or Fid for a file opened with transactions.
//
#ifndef STATUS_REMOTE_FILE_VERSION_MISMATCH
#define STATUS_REMOTE_FILE_VERSION_MISMATCH ((NTSTATUS)0xC019000CL)
#endif//STATUS_REMOTE_FILE_VERSION_MISMATCH

//
// MessageId: STATUS_CRM_PROTOCOL_ALREADY_EXISTS
//
// MessageText:
//
// The RM tried to register a protocol that already exists.
//
#ifndef STATUS_CRM_PROTOCOL_ALREADY_EXISTS
#define STATUS_CRM_PROTOCOL_ALREADY_EXISTS ((NTSTATUS)0xC019000FL)
#endif//STATUS_CRM_PROTOCOL_ALREADY_EXISTS

//
// MessageId: STATUS_TRANSACTION_PROPAGATION_FAILED
//
// MessageText:
//
// The attempt to propagate the Transaction failed.
//
#ifndef STATUS_TRANSACTION_PROPAGATION_FAILED
#define STATUS_TRANSACTION_PROPAGATION_FAILED ((NTSTATUS)0xC0190010L)
#endif//STATUS_TRANSACTION_PROPAGATION_FAILED

//
// MessageId: STATUS_CRM_PROTOCOL_NOT_FOUND
//
// MessageText:
//
// The requested propagation protocol was not registered as a CRM.
//
#ifndef STATUS_CRM_PROTOCOL_NOT_FOUND
#define STATUS_CRM_PROTOCOL_NOT_FOUND    ((NTSTATUS)0xC0190011L)
#endif//STATUS_CRM_PROTOCOL_NOT_FOUND

//
// MessageId: STATUS_TRANSACTION_SUPERIOR_EXISTS
//
// MessageText:
//
// The Transaction object already has a superior enlistment, and the caller attempted an operation that would have created a new superior. Only a single superior enlistment is allowed.
//
#ifndef STATUS_TRANSACTION_SUPERIOR_EXISTS
#define STATUS_TRANSACTION_SUPERIOR_EXISTS ((NTSTATUS)0xC0190012L)
#endif//STATUS_TRANSACTION_SUPERIOR_EXISTS

//
// MessageId: STATUS_TRANSACTION_REQUEST_NOT_VALID
//
// MessageText:
//
// The requested operation is not valid on the Transaction object in its current state.
//
#ifndef STATUS_TRANSACTION_REQUEST_NOT_VALID
#define STATUS_TRANSACTION_REQUEST_NOT_VALID ((NTSTATUS)0xC0190013L)
#endif//STATUS_TRANSACTION_REQUEST_NOT_VALID

//
// MessageId: STATUS_TRANSACTION_NOT_REQUESTED
//
// MessageText:
//
// The caller has called a response API, but the response is not expected because the TM did not issue the corresponding request to the caller.
//
#ifndef STATUS_TRANSACTION_NOT_REQUESTED
#define STATUS_TRANSACTION_NOT_REQUESTED ((NTSTATUS)0xC0190014L)
#endif//STATUS_TRANSACTION_NOT_REQUESTED

//
// MessageId: STATUS_TRANSACTION_ALREADY_ABORTED
//
// MessageText:
//
// It is too late to perform the requested operation, since the Transaction has already been aborted.
//
#ifndef STATUS_TRANSACTION_ALREADY_ABORTED
#define STATUS_TRANSACTION_ALREADY_ABORTED ((NTSTATUS)0xC0190015L)
#endif//STATUS_TRANSACTION_ALREADY_ABORTED

//
// MessageId: STATUS_TRANSACTION_ALREADY_COMMITTED
//
// MessageText:
//
// It is too late to perform the requested operation, since the Transaction has already been committed.
//
#ifndef STATUS_TRANSACTION_ALREADY_COMMITTED
#define STATUS_TRANSACTION_ALREADY_COMMITTED ((NTSTATUS)0xC0190016L)
#endif//STATUS_TRANSACTION_ALREADY_COMMITTED

//
// MessageId: STATUS_TRANSACTION_INVALID_MARSHALL_BUFFER
//
// MessageText:
//
// The buffer passed in to NtPushTransaction or NtPullTransaction is not in a valid format.
//
#ifndef STATUS_TRANSACTION_INVALID_MARSHALL_BUFFER
#define STATUS_TRANSACTION_INVALID_MARSHALL_BUFFER ((NTSTATUS)0xC0190017L)
#endif//STATUS_TRANSACTION_INVALID_MARSHALL_BUFFER

//
// MessageId: STATUS_CURRENT_TRANSACTION_NOT_VALID
//
// MessageText:
//
// The current transaction context associated with the thread is not a valid handle to a transaction object.
//
#ifndef STATUS_CURRENT_TRANSACTION_NOT_VALID
#define STATUS_CURRENT_TRANSACTION_NOT_VALID ((NTSTATUS)0xC0190018L)
#endif//STATUS_CURRENT_TRANSACTION_NOT_VALID

//
// MessageId: STATUS_LOG_GROWTH_FAILED
//
// MessageText:
//
// An attempt to create space in the transactional resource manager's log failed. The failure status has been recorded in the event log.
//
#ifndef STATUS_LOG_GROWTH_FAILED
#define STATUS_LOG_GROWTH_FAILED         ((NTSTATUS)0xC0190019L)
#endif//STATUS_LOG_GROWTH_FAILED

//
// MessageId: STATUS_OBJECT_NO_LONGER_EXISTS
//
// MessageText:
//
// The object (file, stream, link) corresponding to the handle has been deleted by a transaction savepoint rollback.
//
#ifndef STATUS_OBJECT_NO_LONGER_EXISTS
#define STATUS_OBJECT_NO_LONGER_EXISTS   ((NTSTATUS)0xC0190021L)
#endif//STATUS_OBJECT_NO_LONGER_EXISTS

//
// MessageId: STATUS_STREAM_MINIVERSION_NOT_FOUND
//
// MessageText:
//
// The specified file miniversion was not found for this transacted file open.
//
#ifndef STATUS_STREAM_MINIVERSION_NOT_FOUND
#define STATUS_STREAM_MINIVERSION_NOT_FOUND ((NTSTATUS)0xC0190022L)
#endif//STATUS_STREAM_MINIVERSION_NOT_FOUND

//
// MessageId: STATUS_STREAM_MINIVERSION_NOT_VALID
//
// MessageText:
//
// The specified file miniversion was found but has been invalidated. Most likely cause is a transaction savepoint rollback.
//
#ifndef STATUS_STREAM_MINIVERSION_NOT_VALID
#define STATUS_STREAM_MINIVERSION_NOT_VALID ((NTSTATUS)0xC0190023L)
#endif//STATUS_STREAM_MINIVERSION_NOT_VALID

//
// MessageId: STATUS_MINIVERSION_INACCESSIBLE_FROM_SPECIFIED_TRANSACTION
//
// MessageText:
//
// A miniversion may only be opened in the context of the transaction that created it.
//
#ifndef STATUS_MINIVERSION_INACCESSIBLE_FROM_SPECIFIED_TRANSACTION
#define STATUS_MINIVERSION_INACCESSIBLE_FROM_SPECIFIED_TRANSACTION ((NTSTATUS)0xC0190024L)
#endif//STATUS_MINIVERSION_INACCESSIBLE_FROM_SPECIFIED_TRANSACTION

//
// MessageId: STATUS_CANT_OPEN_MINIVERSION_WITH_MODIFY_INTENT
//
// MessageText:
//
// It is not possible to open a miniversion with modify access.
//
#ifndef STATUS_CANT_OPEN_MINIVERSION_WITH_MODIFY_INTENT
#define STATUS_CANT_OPEN_MINIVERSION_WITH_MODIFY_INTENT ((NTSTATUS)0xC0190025L)
#endif//STATUS_CANT_OPEN_MINIVERSION_WITH_MODIFY_INTENT

//
// MessageId: STATUS_CANT_CREATE_MORE_STREAM_MINIVERSIONS
//
// MessageText:
//
// It is not possible to create any more miniversions for this stream.
//
#ifndef STATUS_CANT_CREATE_MORE_STREAM_MINIVERSIONS
#define STATUS_CANT_CREATE_MORE_STREAM_MINIVERSIONS ((NTSTATUS)0xC0190026L)
#endif//STATUS_CANT_CREATE_MORE_STREAM_MINIVERSIONS

//
// MessageId: STATUS_HANDLE_NO_LONGER_VALID
//
// MessageText:
//
// The handle has been invalidated by a transaction. The most likely cause is the presence of memory mapping on a file or an open handle when the transaction ended or rolled back to savepoint.
//
#ifndef STATUS_HANDLE_NO_LONGER_VALID
#define STATUS_HANDLE_NO_LONGER_VALID    ((NTSTATUS)0xC0190028L)
#endif//STATUS_HANDLE_NO_LONGER_VALID

//
// MessageId: STATUS_NO_TXF_METADATA
//
// MessageText:
//
// There is no transaction metadata on the file.
//
#ifndef STATUS_NO_TXF_METADATA
#define STATUS_NO_TXF_METADATA           ((NTSTATUS)0x80190029L)
#endif//STATUS_NO_TXF_METADATA

//
// MessageId: STATUS_LOG_CORRUPTION_DETECTED
//
// MessageText:
//
// The log data is corrupt.
//
#ifndef STATUS_LOG_CORRUPTION_DETECTED
#define STATUS_LOG_CORRUPTION_DETECTED   ((NTSTATUS)0xC0190030L)
#endif//STATUS_LOG_CORRUPTION_DETECTED

//
// MessageId: STATUS_CANT_RECOVER_WITH_HANDLE_OPEN
//
// MessageText:
//
// The file can't be recovered because there is a handle still open on it.
//
#ifndef STATUS_CANT_RECOVER_WITH_HANDLE_OPEN
#define STATUS_CANT_RECOVER_WITH_HANDLE_OPEN ((NTSTATUS)0x80190031L)
#endif//STATUS_CANT_RECOVER_WITH_HANDLE_OPEN

//
// MessageId: STATUS_RM_DISCONNECTED
//
// MessageText:
//
// The transaction outcome is unavailable because the resource manager responsible for it has disconnected.
//
#ifndef STATUS_RM_DISCONNECTED
#define STATUS_RM_DISCONNECTED           ((NTSTATUS)0xC0190032L)
#endif//STATUS_RM_DISCONNECTED

//
// MessageId: STATUS_ENLISTMENT_NOT_SUPERIOR
//
// MessageText:
//
// The request was rejected because the enlistment in question is not a superior enlistment.
//
#ifndef STATUS_ENLISTMENT_NOT_SUPERIOR
#define STATUS_ENLISTMENT_NOT_SUPERIOR   ((NTSTATUS)0xC0190033L)
#endif//STATUS_ENLISTMENT_NOT_SUPERIOR

//
// MessageId: STATUS_RECOVERY_NOT_NEEDED
//
// MessageText:
//
// The transactional resource manager is already consistent. Recovery is not needed.
//
#ifndef STATUS_RECOVERY_NOT_NEEDED
#define STATUS_RECOVERY_NOT_NEEDED       ((NTSTATUS)0x40190034L)
#endif//STATUS_RECOVERY_NOT_NEEDED

//
// MessageId: STATUS_RM_ALREADY_STARTED
//
// MessageText:
//
// The transactional resource manager has already been started.
//
#ifndef STATUS_RM_ALREADY_STARTED
#define STATUS_RM_ALREADY_STARTED        ((NTSTATUS)0x40190035L)
#endif//STATUS_RM_ALREADY_STARTED

//
// MessageId: STATUS_FILE_IDENTITY_NOT_PERSISTENT
//
// MessageText:
//
// The file cannot be opened transactionally, because its identity depends on the outcome of an unresolved transaction.
//
#ifndef STATUS_FILE_IDENTITY_NOT_PERSISTENT
#define STATUS_FILE_IDENTITY_NOT_PERSISTENT ((NTSTATUS)0xC0190036L)
#endif//STATUS_FILE_IDENTITY_NOT_PERSISTENT

//
// MessageId: STATUS_CANT_BREAK_TRANSACTIONAL_DEPENDENCY
//
// MessageText:
//
// The operation cannot be performed because another transaction is depending on the fact that this property will not change.
//
#ifndef STATUS_CANT_BREAK_TRANSACTIONAL_DEPENDENCY
#define STATUS_CANT_BREAK_TRANSACTIONAL_DEPENDENCY ((NTSTATUS)0xC0190037L)
#endif//STATUS_CANT_BREAK_TRANSACTIONAL_DEPENDENCY

//
// MessageId: STATUS_CANT_CROSS_RM_BOUNDARY
//
// MessageText:
//
// The operation would involve a single file with two transactional resource managers and is therefore not allowed.
//
#ifndef STATUS_CANT_CROSS_RM_BOUNDARY
#define STATUS_CANT_CROSS_RM_BOUNDARY    ((NTSTATUS)0xC0190038L)
#endif//STATUS_CANT_CROSS_RM_BOUNDARY

//
// MessageId: STATUS_TXF_DIR_NOT_EMPTY
//
// MessageText:
//
// The $Txf directory must be empty for this operation to succeed.
//
#ifndef STATUS_TXF_DIR_NOT_EMPTY
#define STATUS_TXF_DIR_NOT_EMPTY         ((NTSTATUS)0xC0190039L)
#endif//STATUS_TXF_DIR_NOT_EMPTY

//
// MessageId: STATUS_INDOUBT_TRANSACTIONS_EXIST
//
// MessageText:
//
// The operation would leave a transactional resource manager in an inconsistent state and is therefore not allowed.
//
#ifndef STATUS_INDOUBT_TRANSACTIONS_EXIST
#define STATUS_INDOUBT_TRANSACTIONS_EXIST ((NTSTATUS)0xC019003AL)
#endif//STATUS_INDOUBT_TRANSACTIONS_EXIST

//
// MessageId: STATUS_TM_VOLATILE
//
// MessageText:
//
// The operation could not be completed because the transaction manager does not have a log.
//
#ifndef STATUS_TM_VOLATILE
#define STATUS_TM_VOLATILE               ((NTSTATUS)0xC019003BL)
#endif//STATUS_TM_VOLATILE

//
// MessageId: STATUS_ROLLBACK_TIMER_EXPIRED
//
// MessageText:
//
// A rollback could not be scheduled because a previously scheduled rollback has already executed or been queued for execution.
//
#ifndef STATUS_ROLLBACK_TIMER_EXPIRED
#define STATUS_ROLLBACK_TIMER_EXPIRED    ((NTSTATUS)0xC019003CL)
#endif//STATUS_ROLLBACK_TIMER_EXPIRED

//
// MessageId: STATUS_TXF_ATTRIBUTE_CORRUPT
//
// MessageText:
//
// The transactional metadata attribute on the file or directory %hs is corrupt and unreadable.
//
#ifndef STATUS_TXF_ATTRIBUTE_CORRUPT
#define STATUS_TXF_ATTRIBUTE_CORRUPT     ((NTSTATUS)0xC019003DL)
#endif//STATUS_TXF_ATTRIBUTE_CORRUPT

//
// MessageId: STATUS_EFS_NOT_ALLOWED_IN_TRANSACTION
//
// MessageText:
//
// The encryption operation could not be completed because a transaction is active.
//
#ifndef STATUS_EFS_NOT_ALLOWED_IN_TRANSACTION
#define STATUS_EFS_NOT_ALLOWED_IN_TRANSACTION ((NTSTATUS)0xC019003EL)
#endif//STATUS_EFS_NOT_ALLOWED_IN_TRANSACTION

//
// MessageId: STATUS_TRANSACTIONAL_OPEN_NOT_ALLOWED
//
// MessageText:
//
// This object is not allowed to be opened in a transaction.
//
#ifndef STATUS_TRANSACTIONAL_OPEN_NOT_ALLOWED
#define STATUS_TRANSACTIONAL_OPEN_NOT_ALLOWED ((NTSTATUS)0xC019003FL)
#endif//STATUS_TRANSACTIONAL_OPEN_NOT_ALLOWED

//
// MessageId: STATUS_TRANSACTED_MAPPING_UNSUPPORTED_REMOTE
//
// MessageText:
//
// Memory mapping (creating a mapped section) a remote file under a transaction is not supported.
//
#ifndef STATUS_TRANSACTED_MAPPING_UNSUPPORTED_REMOTE
#define STATUS_TRANSACTED_MAPPING_UNSUPPORTED_REMOTE ((NTSTATUS)0xC0190040L)
#endif//STATUS_TRANSACTED_MAPPING_UNSUPPORTED_REMOTE

//
// MessageId: STATUS_TXF_METADATA_ALREADY_PRESENT
//
// MessageText:
//
// Transaction metadata is already present on this file and cannot be superseded.
//
#ifndef STATUS_TXF_METADATA_ALREADY_PRESENT
#define STATUS_TXF_METADATA_ALREADY_PRESENT ((NTSTATUS)0x80190041L)
#endif//STATUS_TXF_METADATA_ALREADY_PRESENT

//
// MessageId: STATUS_TRANSACTION_SCOPE_CALLBACKS_NOT_SET
//
// MessageText:
//
// A transaction scope could not be entered because the scope handler has not been initialized.
//
#ifndef STATUS_TRANSACTION_SCOPE_CALLBACKS_NOT_SET
#define STATUS_TRANSACTION_SCOPE_CALLBACKS_NOT_SET ((NTSTATUS)0x80190042L)
#endif//STATUS_TRANSACTION_SCOPE_CALLBACKS_NOT_SET

//
// MessageId: STATUS_TRANSACTION_REQUIRED_PROMOTION
//
// MessageText:
//
// Promotion was required in order to allow the resource manager to enlist, but the transaction was set to disallow it.
//
#ifndef STATUS_TRANSACTION_REQUIRED_PROMOTION
#define STATUS_TRANSACTION_REQUIRED_PROMOTION ((NTSTATUS)0xC0190043L)
#endif//STATUS_TRANSACTION_REQUIRED_PROMOTION

//
// MessageId: STATUS_CANNOT_EXECUTE_FILE_IN_TRANSACTION
//
// MessageText:
//
// This file is open for modification in an unresolved transaction and may be opened for execute only by a transacted reader.
//
#ifndef STATUS_CANNOT_EXECUTE_FILE_IN_TRANSACTION
#define STATUS_CANNOT_EXECUTE_FILE_IN_TRANSACTION ((NTSTATUS)0xC0190044L)
#endif//STATUS_CANNOT_EXECUTE_FILE_IN_TRANSACTION

//
// MessageId: STATUS_TRANSACTIONS_NOT_FROZEN
//
// MessageText:
//
// The request to thaw frozen transactions was ignored because transactions had not previously been frozen.
//
#ifndef STATUS_TRANSACTIONS_NOT_FROZEN
#define STATUS_TRANSACTIONS_NOT_FROZEN   ((NTSTATUS)0xC0190045L)
#endif//STATUS_TRANSACTIONS_NOT_FROZEN

//
// MessageId: STATUS_TRANSACTION_FREEZE_IN_PROGRESS
//
// MessageText:
//
// Transactions cannot be frozen because a freeze is already in progress.
//
#ifndef STATUS_TRANSACTION_FREEZE_IN_PROGRESS
#define STATUS_TRANSACTION_FREEZE_IN_PROGRESS ((NTSTATUS)0xC0190046L)
#endif//STATUS_TRANSACTION_FREEZE_IN_PROGRESS

//
// MessageId: STATUS_NOT_SNAPSHOT_VOLUME
//
// MessageText:
//
// The target volume is not a snapshot volume. This operation is only valid on a volume mounted as a snapshot.
//
#ifndef STATUS_NOT_SNAPSHOT_VOLUME
#define STATUS_NOT_SNAPSHOT_VOLUME       ((NTSTATUS)0xC0190047L)
#endif//STATUS_NOT_SNAPSHOT_VOLUME

//
// MessageId: STATUS_NO_SAVEPOINT_WITH_OPEN_FILES
//
// MessageText:
//
// The savepoint operation failed because files are open on the transaction. This is not permitted.
//
#ifndef STATUS_NO_SAVEPOINT_WITH_OPEN_FILES
#define STATUS_NO_SAVEPOINT_WITH_OPEN_FILES ((NTSTATUS)0xC0190048L)
#endif//STATUS_NO_SAVEPOINT_WITH_OPEN_FILES

//
// MessageId: STATUS_SPARSE_NOT_ALLOWED_IN_TRANSACTION
//
// MessageText:
//
// The sparse operation could not be completed because a transaction is active on the file.
//
#ifndef STATUS_SPARSE_NOT_ALLOWED_IN_TRANSACTION
#define STATUS_SPARSE_NOT_ALLOWED_IN_TRANSACTION ((NTSTATUS)0xC0190049L)
#endif//STATUS_SPARSE_NOT_ALLOWED_IN_TRANSACTION

//
// MessageId: STATUS_TM_IDENTITY_MISMATCH
//
// MessageText:
//
// The call to create a TransactionManager object failed because the Tm Identity stored in the logfile does not match the Tm Identity that was passed in as an argument.
//
#ifndef STATUS_TM_IDENTITY_MISMATCH
#define STATUS_TM_IDENTITY_MISMATCH      ((NTSTATUS)0xC019004AL)
#endif//STATUS_TM_IDENTITY_MISMATCH

//
// MessageId: STATUS_FLOATED_SECTION
//
// MessageText:
//
// I/O was attempted on a section object that has been floated as a result of a transaction ending. There is no valid data.
//
#ifndef STATUS_FLOATED_SECTION
#define STATUS_FLOATED_SECTION           ((NTSTATUS)0xC019004BL)
#endif//STATUS_FLOATED_SECTION

//
// MessageId: STATUS_CANNOT_ACCEPT_TRANSACTED_WORK
//
// MessageText:
//
// The transactional resource manager cannot currently accept transacted work due to a transient condition such as low resources.
//
#ifndef STATUS_CANNOT_ACCEPT_TRANSACTED_WORK
#define STATUS_CANNOT_ACCEPT_TRANSACTED_WORK ((NTSTATUS)0xC019004CL)
#endif//STATUS_CANNOT_ACCEPT_TRANSACTED_WORK

//
// MessageId: STATUS_CANNOT_ABORT_TRANSACTIONS
//
// MessageText:
//
// The transactional resource manager had too many tranactions outstanding that could not be aborted. The transactional resource manger has been shut down.
//
#ifndef STATUS_CANNOT_ABORT_TRANSACTIONS
#define STATUS_CANNOT_ABORT_TRANSACTIONS ((NTSTATUS)0xC019004DL)
#endif//STATUS_CANNOT_ABORT_TRANSACTIONS

//
// MessageId: STATUS_TRANSACTION_NOT_FOUND
//
// MessageText:
//
// The specified Transaction was unable to be opened, because it was not found.
//
#ifndef STATUS_TRANSACTION_NOT_FOUND
#define STATUS_TRANSACTION_NOT_FOUND     ((NTSTATUS)0xC019004EL)
#endif//STATUS_TRANSACTION_NOT_FOUND

//
// MessageId: STATUS_RESOURCEMANAGER_NOT_FOUND
//
// MessageText:
//
// The specified ResourceManager was unable to be opened, because it was not found.
//
#ifndef STATUS_RESOURCEMANAGER_NOT_FOUND
#define STATUS_RESOURCEMANAGER_NOT_FOUND ((NTSTATUS)0xC019004FL)
#endif//STATUS_RESOURCEMANAGER_NOT_FOUND

//
// MessageId: STATUS_ENLISTMENT_NOT_FOUND
//
// MessageText:
//
// The specified Enlistment was unable to be opened, because it was not found.
//
#ifndef STATUS_ENLISTMENT_NOT_FOUND
#define STATUS_ENLISTMENT_NOT_FOUND      ((NTSTATUS)0xC0190050L)
#endif//STATUS_ENLISTMENT_NOT_FOUND

//
// MessageId: STATUS_TRANSACTIONMANAGER_NOT_FOUND
//
// MessageText:
//
// The specified TransactionManager was unable to be opened, because it was not found.
//
#ifndef STATUS_TRANSACTIONMANAGER_NOT_FOUND
#define STATUS_TRANSACTIONMANAGER_NOT_FOUND ((NTSTATUS)0xC0190051L)
#endif//STATUS_TRANSACTIONMANAGER_NOT_FOUND

//
// MessageId: STATUS_TRANSACTIONMANAGER_NOT_ONLINE
//
// MessageText:
//
// The object specified could not be created or opened, because its associated TransactionManager is not online.  The TransactionManager must be brought fully Online by calling RecoverTransactionManager to recover to the end of its LogFile before objects in its Transaction or ResourceManager namespaces can be opened.  In addition, errors in writing records to its LogFile can cause a TransactionManager to go offline.
//
#ifndef STATUS_TRANSACTIONMANAGER_NOT_ONLINE
#define STATUS_TRANSACTIONMANAGER_NOT_ONLINE ((NTSTATUS)0xC0190052L)
#endif//STATUS_TRANSACTIONMANAGER_NOT_ONLINE

//
// MessageId: STATUS_TRANSACTIONMANAGER_RECOVERY_NAME_COLLISION
//
// MessageText:
//
// The specified TransactionManager was unable to create the objects contained in its logfile in the Ob namespace. Therefore, the TransactionManager was unable to recover.
//
#ifndef STATUS_TRANSACTIONMANAGER_RECOVERY_NAME_COLLISION
#define STATUS_TRANSACTIONMANAGER_RECOVERY_NAME_COLLISION ((NTSTATUS)0xC0190053L)
#endif//STATUS_TRANSACTIONMANAGER_RECOVERY_NAME_COLLISION

//
// MessageId: STATUS_TRANSACTION_NOT_ROOT
//
// MessageText:
//
// The call to create a superior Enlistment on this Transaction object could not be completed, because the Transaction object specified for the enlistment is a subordinate branch of the Transaction. Only the root of the Transaction can be enlisted on as a superior.
//
#ifndef STATUS_TRANSACTION_NOT_ROOT
#define STATUS_TRANSACTION_NOT_ROOT      ((NTSTATUS)0xC0190054L)
#endif//STATUS_TRANSACTION_NOT_ROOT

//
// MessageId: STATUS_TRANSACTION_OBJECT_EXPIRED
//
// MessageText:
//
// Because the associated transaction manager or resource manager has been closed, the handle is no longer valid.
//
#ifndef STATUS_TRANSACTION_OBJECT_EXPIRED
#define STATUS_TRANSACTION_OBJECT_EXPIRED ((NTSTATUS)0xC0190055L)
#endif//STATUS_TRANSACTION_OBJECT_EXPIRED

//
// MessageId: STATUS_COMPRESSION_NOT_ALLOWED_IN_TRANSACTION
//
// MessageText:
//
// The compression operation could not be completed because a transaction is active on the file.
//
#ifndef STATUS_COMPRESSION_NOT_ALLOWED_IN_TRANSACTION
#define STATUS_COMPRESSION_NOT_ALLOWED_IN_TRANSACTION ((NTSTATUS)0xC0190056L)
#endif//STATUS_COMPRESSION_NOT_ALLOWED_IN_TRANSACTION

//
// MessageId: STATUS_TRANSACTION_RESPONSE_NOT_ENLISTED
//
// MessageText:
//
// The specified operation could not be performed on this Superior enlistment, because the enlistment was not created with the corresponding completion response in the NotificationMask.
//
#ifndef STATUS_TRANSACTION_RESPONSE_NOT_ENLISTED
#define STATUS_TRANSACTION_RESPONSE_NOT_ENLISTED ((NTSTATUS)0xC0190057L)
#endif//STATUS_TRANSACTION_RESPONSE_NOT_ENLISTED

//
// MessageId: STATUS_TRANSACTION_RECORD_TOO_LONG
//
// MessageText:
//
// The specified operation could not be performed, because the record that would be logged was too long. This can occur because of two conditions:  either there are too many Enlistments on this Transaction, or the combined RecoveryInformation being logged on behalf of those Enlistments is too long.
//
#ifndef STATUS_TRANSACTION_RECORD_TOO_LONG
#define STATUS_TRANSACTION_RECORD_TOO_LONG ((NTSTATUS)0xC0190058L)
#endif//STATUS_TRANSACTION_RECORD_TOO_LONG

//
// MessageId: STATUS_NO_LINK_TRACKING_IN_TRANSACTION
//
// MessageText:
//
// The link tracking operation could not be completed because a transaction is active.
//
#ifndef STATUS_NO_LINK_TRACKING_IN_TRANSACTION
#define STATUS_NO_LINK_TRACKING_IN_TRANSACTION ((NTSTATUS)0xC0190059L)
#endif//STATUS_NO_LINK_TRACKING_IN_TRANSACTION

//
// MessageId: STATUS_OPERATION_NOT_SUPPORTED_IN_TRANSACTION
//
// MessageText:
//
// This operation cannot be performed in a transaction.
//
#ifndef STATUS_OPERATION_NOT_SUPPORTED_IN_TRANSACTION
#define STATUS_OPERATION_NOT_SUPPORTED_IN_TRANSACTION ((NTSTATUS)0xC019005AL)
#endif//STATUS_OPERATION_NOT_SUPPORTED_IN_TRANSACTION

//
// MessageId: STATUS_TRANSACTION_INTEGRITY_VIOLATED
//
// MessageText:
//
// The kernel transaction manager had to abort or forget the transaction because it blocked forward progress.
//
#ifndef STATUS_TRANSACTION_INTEGRITY_VIOLATED
#define STATUS_TRANSACTION_INTEGRITY_VIOLATED ((NTSTATUS)0xC019005BL)
#endif//STATUS_TRANSACTION_INTEGRITY_VIOLATED

//
// MessageId: STATUS_TRANSACTIONMANAGER_IDENTITY_MISMATCH
//
// MessageText:
//
// The TransactionManager identity that was supplied did not match the one recorded in the TransactionManager's log file.
//
#ifndef STATUS_TRANSACTIONMANAGER_IDENTITY_MISMATCH
#define STATUS_TRANSACTIONMANAGER_IDENTITY_MISMATCH ((NTSTATUS)0xC019005CL)
#endif//STATUS_TRANSACTIONMANAGER_IDENTITY_MISMATCH

//
// MessageId: STATUS_RM_CANNOT_BE_FROZEN_FOR_SNAPSHOT
//
// MessageText:
//
// This snapshot operation cannot continue because a transactional resource manager cannot be frozen in its current state.  Please try again.
//
#ifndef STATUS_RM_CANNOT_BE_FROZEN_FOR_SNAPSHOT
#define STATUS_RM_CANNOT_BE_FROZEN_FOR_SNAPSHOT ((NTSTATUS)0xC019005DL)
#endif//STATUS_RM_CANNOT_BE_FROZEN_FOR_SNAPSHOT

//
// MessageId: STATUS_TRANSACTION_MUST_WRITETHROUGH
//
// MessageText:
//
// The transaction cannot be enlisted on with the specified EnlistmentMask, because the transaction has already completed the PrePrepare phase.  In order to ensure correctness, the ResourceManager must switch to a write-through mode and cease caching data within this transaction.  Enlisting for only subsequent transaction phases may still succeed.
//
#ifndef STATUS_TRANSACTION_MUST_WRITETHROUGH
#define STATUS_TRANSACTION_MUST_WRITETHROUGH ((NTSTATUS)0xC019005EL)
#endif//STATUS_TRANSACTION_MUST_WRITETHROUGH

//
// MessageId: STATUS_TRANSACTION_NO_SUPERIOR
//
// MessageText:
//
// The transaction does not have a superior enlistment.
//
#ifndef STATUS_TRANSACTION_NO_SUPERIOR
#define STATUS_TRANSACTION_NO_SUPERIOR   ((NTSTATUS)0xC019005FL)
#endif//STATUS_TRANSACTION_NO_SUPERIOR

//
// MessageId: STATUS_EXPIRED_HANDLE
//
// MessageText:
//
// The handle is no longer properly associated with its transaction.  It may have been opened in a transactional resource manager that was subsequently forced to restart.  Please close the handle and open a new one.
//
#ifndef STATUS_EXPIRED_HANDLE
#define STATUS_EXPIRED_HANDLE            ((NTSTATUS)0xC0190060L)
#endif//STATUS_EXPIRED_HANDLE

//
// MessageId: STATUS_TRANSACTION_NOT_ENLISTED
//
// MessageText:
//
// The specified operation could not be performed because the resource manager is not enlisted in the transaction.
//
#ifndef STATUS_TRANSACTION_NOT_ENLISTED
#define STATUS_TRANSACTION_NOT_ENLISTED  ((NTSTATUS)0xC0190061L)
#endif//STATUS_TRANSACTION_NOT_ENLISTED


//
//  CLFS (common log file system) error values
//

//
// MessageId: STATUS_LOG_SECTOR_INVALID
//
// MessageText:
//
// Log service found an invalid log sector.
//
#ifndef STATUS_LOG_SECTOR_INVALID
#define STATUS_LOG_SECTOR_INVALID        ((NTSTATUS)0xC01A0001L)
#endif//STATUS_LOG_SECTOR_INVALID

//
// MessageId: STATUS_LOG_SECTOR_PARITY_INVALID
//
// MessageText:
//
// Log service encountered a log sector with invalid block parity.
//
#ifndef STATUS_LOG_SECTOR_PARITY_INVALID
#define STATUS_LOG_SECTOR_PARITY_INVALID ((NTSTATUS)0xC01A0002L)
#endif//STATUS_LOG_SECTOR_PARITY_INVALID

//
// MessageId: STATUS_LOG_SECTOR_REMAPPED
//
// MessageText:
//
// Log service encountered a remapped log sector.
//
#ifndef STATUS_LOG_SECTOR_REMAPPED
#define STATUS_LOG_SECTOR_REMAPPED       ((NTSTATUS)0xC01A0003L)
#endif//STATUS_LOG_SECTOR_REMAPPED

//
// MessageId: STATUS_LOG_BLOCK_INCOMPLETE
//
// MessageText:
//
// Log service encountered a partial or incomplete log block.
//
#ifndef STATUS_LOG_BLOCK_INCOMPLETE
#define STATUS_LOG_BLOCK_INCOMPLETE      ((NTSTATUS)0xC01A0004L)
#endif//STATUS_LOG_BLOCK_INCOMPLETE

//
// MessageId: STATUS_LOG_INVALID_RANGE
//
// MessageText:
//
// Log service encountered an attempt access data outside the active log range.
//
#ifndef STATUS_LOG_INVALID_RANGE
#define STATUS_LOG_INVALID_RANGE         ((NTSTATUS)0xC01A0005L)
#endif//STATUS_LOG_INVALID_RANGE

//
// MessageId: STATUS_LOG_BLOCKS_EXHAUSTED
//
// MessageText:
//
// Log service user log marshalling buffers are exhausted.
//
#ifndef STATUS_LOG_BLOCKS_EXHAUSTED
#define STATUS_LOG_BLOCKS_EXHAUSTED      ((NTSTATUS)0xC01A0006L)
#endif//STATUS_LOG_BLOCKS_EXHAUSTED

//
// MessageId: STATUS_LOG_READ_CONTEXT_INVALID
//
// MessageText:
//
// Log service encountered an attempt read from a marshalling area with an invalid read context.
//
#ifndef STATUS_LOG_READ_CONTEXT_INVALID
#define STATUS_LOG_READ_CONTEXT_INVALID  ((NTSTATUS)0xC01A0007L)
#endif//STATUS_LOG_READ_CONTEXT_INVALID

//
// MessageId: STATUS_LOG_RESTART_INVALID
//
// MessageText:
//
// Log service encountered an invalid log restart area.
//
#ifndef STATUS_LOG_RESTART_INVALID
#define STATUS_LOG_RESTART_INVALID       ((NTSTATUS)0xC01A0008L)
#endif//STATUS_LOG_RESTART_INVALID

//
// MessageId: STATUS_LOG_BLOCK_VERSION
//
// MessageText:
//
// Log service encountered an invalid log block version.
//
#ifndef STATUS_LOG_BLOCK_VERSION
#define STATUS_LOG_BLOCK_VERSION         ((NTSTATUS)0xC01A0009L)
#endif//STATUS_LOG_BLOCK_VERSION

//
// MessageId: STATUS_LOG_BLOCK_INVALID
//
// MessageText:
//
// Log service encountered an invalid log block.
//
#ifndef STATUS_LOG_BLOCK_INVALID
#define STATUS_LOG_BLOCK_INVALID         ((NTSTATUS)0xC01A000AL)
#endif//STATUS_LOG_BLOCK_INVALID

//
// MessageId: STATUS_LOG_READ_MODE_INVALID
//
// MessageText:
//
// Log service encountered an attempt to read the log with an invalid read mode.
//
#ifndef STATUS_LOG_READ_MODE_INVALID
#define STATUS_LOG_READ_MODE_INVALID     ((NTSTATUS)0xC01A000BL)
#endif//STATUS_LOG_READ_MODE_INVALID

//
// MessageId: STATUS_LOG_NO_RESTART
//
// MessageText:
//
// Log service encountered a log stream with no restart area.
//
#ifndef STATUS_LOG_NO_RESTART
#define STATUS_LOG_NO_RESTART            ((NTSTATUS)0x401A000CL)
#endif//STATUS_LOG_NO_RESTART

//
// MessageId: STATUS_LOG_METADATA_CORRUPT
//
// MessageText:
//
// Log service encountered a corrupted metadata file.
//
#ifndef STATUS_LOG_METADATA_CORRUPT
#define STATUS_LOG_METADATA_CORRUPT      ((NTSTATUS)0xC01A000DL)
#endif//STATUS_LOG_METADATA_CORRUPT

//
// MessageId: STATUS_LOG_METADATA_INVALID
//
// MessageText:
//
// Log service encountered a metadata file that could not be created by the log file system.
//
#ifndef STATUS_LOG_METADATA_INVALID
#define STATUS_LOG_METADATA_INVALID      ((NTSTATUS)0xC01A000EL)
#endif//STATUS_LOG_METADATA_INVALID

//
// MessageId: STATUS_LOG_METADATA_INCONSISTENT
//
// MessageText:
//
// Log service encountered a metadata file with inconsistent data.
//
#ifndef STATUS_LOG_METADATA_INCONSISTENT
#define STATUS_LOG_METADATA_INCONSISTENT ((NTSTATUS)0xC01A000FL)
#endif//STATUS_LOG_METADATA_INCONSISTENT

//
// MessageId: STATUS_LOG_RESERVATION_INVALID
//
// MessageText:
//
// Log service encountered an attempt to erroneously allocate or dispose reservation space.
//
#ifndef STATUS_LOG_RESERVATION_INVALID
#define STATUS_LOG_RESERVATION_INVALID   ((NTSTATUS)0xC01A0010L)
#endif//STATUS_LOG_RESERVATION_INVALID

//
// MessageId: STATUS_LOG_CANT_DELETE
//
// MessageText:
//
// Log service cannot delete log file or file system container.
//
#ifndef STATUS_LOG_CANT_DELETE
#define STATUS_LOG_CANT_DELETE           ((NTSTATUS)0xC01A0011L)
#endif//STATUS_LOG_CANT_DELETE

//
// MessageId: STATUS_LOG_CONTAINER_LIMIT_EXCEEDED
//
// MessageText:
//
// Log service has reached the maximum allowable containers allocated to a log file.
//
#ifndef STATUS_LOG_CONTAINER_LIMIT_EXCEEDED
#define STATUS_LOG_CONTAINER_LIMIT_EXCEEDED ((NTSTATUS)0xC01A0012L)
#endif//STATUS_LOG_CONTAINER_LIMIT_EXCEEDED

//
// MessageId: STATUS_LOG_START_OF_LOG
//
// MessageText:
//
// Log service has attempted to read or write backwards past the start of the log.
//
#ifndef STATUS_LOG_START_OF_LOG
#define STATUS_LOG_START_OF_LOG          ((NTSTATUS)0xC01A0013L)
#endif//STATUS_LOG_START_OF_LOG

//
// MessageId: STATUS_LOG_POLICY_ALREADY_INSTALLED
//
// MessageText:
//
// Log policy could not be installed because a policy of the same type is already present.
//
#ifndef STATUS_LOG_POLICY_ALREADY_INSTALLED
#define STATUS_LOG_POLICY_ALREADY_INSTALLED ((NTSTATUS)0xC01A0014L)
#endif//STATUS_LOG_POLICY_ALREADY_INSTALLED

//
// MessageId: STATUS_LOG_POLICY_NOT_INSTALLED
//
// MessageText:
//
// Log policy in question was not installed at the time of the request.
//
#ifndef STATUS_LOG_POLICY_NOT_INSTALLED
#define STATUS_LOG_POLICY_NOT_INSTALLED  ((NTSTATUS)0xC01A0015L)
#endif//STATUS_LOG_POLICY_NOT_INSTALLED

//
// MessageId: STATUS_LOG_POLICY_INVALID
//
// MessageText:
//
// The installed set of policies on the log is invalid.
//
#ifndef STATUS_LOG_POLICY_INVALID
#define STATUS_LOG_POLICY_INVALID        ((NTSTATUS)0xC01A0016L)
#endif//STATUS_LOG_POLICY_INVALID

//
// MessageId: STATUS_LOG_POLICY_CONFLICT
//
// MessageText:
//
// A policy on the log in question prevented the operation from completing.
//
#ifndef STATUS_LOG_POLICY_CONFLICT
#define STATUS_LOG_POLICY_CONFLICT       ((NTSTATUS)0xC01A0017L)
#endif//STATUS_LOG_POLICY_CONFLICT

//
// MessageId: STATUS_LOG_PINNED_ARCHIVE_TAIL
//
// MessageText:
//
// Log space cannot be reclaimed because the log is pinned by the archive tail.
//
#ifndef STATUS_LOG_PINNED_ARCHIVE_TAIL
#define STATUS_LOG_PINNED_ARCHIVE_TAIL   ((NTSTATUS)0xC01A0018L)
#endif//STATUS_LOG_PINNED_ARCHIVE_TAIL

//
// MessageId: STATUS_LOG_RECORD_NONEXISTENT
//
// MessageText:
//
// Log record is not a record in the log file.
//
#ifndef STATUS_LOG_RECORD_NONEXISTENT
#define STATUS_LOG_RECORD_NONEXISTENT    ((NTSTATUS)0xC01A0019L)
#endif//STATUS_LOG_RECORD_NONEXISTENT

//
// MessageId: STATUS_LOG_RECORDS_RESERVED_INVALID
//
// MessageText:
//
// Number of reserved log records or the adjustment of the number of reserved log records is invalid.
//
#ifndef STATUS_LOG_RECORDS_RESERVED_INVALID
#define STATUS_LOG_RECORDS_RESERVED_INVALID ((NTSTATUS)0xC01A001AL)
#endif//STATUS_LOG_RECORDS_RESERVED_INVALID

//
// MessageId: STATUS_LOG_SPACE_RESERVED_INVALID
//
// MessageText:
//
// Reserved log space or the adjustment of the log space is invalid.
//
#ifndef STATUS_LOG_SPACE_RESERVED_INVALID
#define STATUS_LOG_SPACE_RESERVED_INVALID ((NTSTATUS)0xC01A001BL)
#endif//STATUS_LOG_SPACE_RESERVED_INVALID

//
// MessageId: STATUS_LOG_TAIL_INVALID
//
// MessageText:
//
// A new or existing archive tail or base of the active log is invalid.
//
#ifndef STATUS_LOG_TAIL_INVALID
#define STATUS_LOG_TAIL_INVALID          ((NTSTATUS)0xC01A001CL)
#endif//STATUS_LOG_TAIL_INVALID

//
// MessageId: STATUS_LOG_FULL
//
// MessageText:
//
// Log space is exhausted.
//
#ifndef STATUS_LOG_FULL
#define STATUS_LOG_FULL                  ((NTSTATUS)0xC01A001DL)
#endif//STATUS_LOG_FULL

//
// MessageId: STATUS_LOG_MULTIPLEXED
//
// MessageText:
//
// Log is multiplexed, no direct writes to the physical log is allowed.
//
#ifndef STATUS_LOG_MULTIPLEXED
#define STATUS_LOG_MULTIPLEXED           ((NTSTATUS)0xC01A001EL)
#endif//STATUS_LOG_MULTIPLEXED

//
// MessageId: STATUS_LOG_DEDICATED
//
// MessageText:
//
// The operation failed because the log is a dedicated log.
//
#ifndef STATUS_LOG_DEDICATED
#define STATUS_LOG_DEDICATED             ((NTSTATUS)0xC01A001FL)
#endif//STATUS_LOG_DEDICATED

//
// MessageId: STATUS_LOG_ARCHIVE_NOT_IN_PROGRESS
//
// MessageText:
//
// The operation requires an archive context.
//
#ifndef STATUS_LOG_ARCHIVE_NOT_IN_PROGRESS
#define STATUS_LOG_ARCHIVE_NOT_IN_PROGRESS ((NTSTATUS)0xC01A0020L)
#endif//STATUS_LOG_ARCHIVE_NOT_IN_PROGRESS

//
// MessageId: STATUS_LOG_ARCHIVE_IN_PROGRESS
//
// MessageText:
//
// Log archival is in progress.
//
#ifndef STATUS_LOG_ARCHIVE_IN_PROGRESS
#define STATUS_LOG_ARCHIVE_IN_PROGRESS   ((NTSTATUS)0xC01A0021L)
#endif//STATUS_LOG_ARCHIVE_IN_PROGRESS

//
// MessageId: STATUS_LOG_EPHEMERAL
//
// MessageText:
//
// The operation requires a non-ephemeral log, but the log is ephemeral.
//
#ifndef STATUS_LOG_EPHEMERAL
#define STATUS_LOG_EPHEMERAL             ((NTSTATUS)0xC01A0022L)
#endif//STATUS_LOG_EPHEMERAL

//
// MessageId: STATUS_LOG_NOT_ENOUGH_CONTAINERS
//
// MessageText:
//
// The log must have at least two containers before it can be read from or written to.
//
#ifndef STATUS_LOG_NOT_ENOUGH_CONTAINERS
#define STATUS_LOG_NOT_ENOUGH_CONTAINERS ((NTSTATUS)0xC01A0023L)
#endif//STATUS_LOG_NOT_ENOUGH_CONTAINERS

//
// MessageId: STATUS_LOG_CLIENT_ALREADY_REGISTERED
//
// MessageText:
//
// A log client has already registered on the stream.
//
#ifndef STATUS_LOG_CLIENT_ALREADY_REGISTERED
#define STATUS_LOG_CLIENT_ALREADY_REGISTERED ((NTSTATUS)0xC01A0024L)
#endif//STATUS_LOG_CLIENT_ALREADY_REGISTERED

//
// MessageId: STATUS_LOG_CLIENT_NOT_REGISTERED
//
// MessageText:
//
// A log client has not been registered on the stream.
//
#ifndef STATUS_LOG_CLIENT_NOT_REGISTERED
#define STATUS_LOG_CLIENT_NOT_REGISTERED ((NTSTATUS)0xC01A0025L)
#endif//STATUS_LOG_CLIENT_NOT_REGISTERED

//
// MessageId: STATUS_LOG_FULL_HANDLER_IN_PROGRESS
//
// MessageText:
//
// A request has already been made to handle the log full condition.
//
#ifndef STATUS_LOG_FULL_HANDLER_IN_PROGRESS
#define STATUS_LOG_FULL_HANDLER_IN_PROGRESS ((NTSTATUS)0xC01A0026L)
#endif//STATUS_LOG_FULL_HANDLER_IN_PROGRESS

//
// MessageId: STATUS_LOG_CONTAINER_READ_FAILED
//
// MessageText:
//
// Log service encountered an error when attempting to read from a log container.
//
#ifndef STATUS_LOG_CONTAINER_READ_FAILED
#define STATUS_LOG_CONTAINER_READ_FAILED ((NTSTATUS)0xC01A0027L)
#endif//STATUS_LOG_CONTAINER_READ_FAILED

//
// MessageId: STATUS_LOG_CONTAINER_WRITE_FAILED
//
// MessageText:
//
// Log service encountered an error when attempting to write to a log container.
//
#ifndef STATUS_LOG_CONTAINER_WRITE_FAILED
#define STATUS_LOG_CONTAINER_WRITE_FAILED ((NTSTATUS)0xC01A0028L)
#endif//STATUS_LOG_CONTAINER_WRITE_FAILED

//
// MessageId: STATUS_LOG_CONTAINER_OPEN_FAILED
//
// MessageText:
//
// Log service encountered an error when attempting open a log container.
//
#ifndef STATUS_LOG_CONTAINER_OPEN_FAILED
#define STATUS_LOG_CONTAINER_OPEN_FAILED ((NTSTATUS)0xC01A0029L)
#endif//STATUS_LOG_CONTAINER_OPEN_FAILED

//
// MessageId: STATUS_LOG_CONTAINER_STATE_INVALID
//
// MessageText:
//
// Log service encountered an invalid container state when attempting a requested action.
//
#ifndef STATUS_LOG_CONTAINER_STATE_INVALID
#define STATUS_LOG_CONTAINER_STATE_INVALID ((NTSTATUS)0xC01A002AL)
#endif//STATUS_LOG_CONTAINER_STATE_INVALID

//
// MessageId: STATUS_LOG_STATE_INVALID
//
// MessageText:
//
// Log service is not in the correct state to perform a requested action.
//
#ifndef STATUS_LOG_STATE_INVALID
#define STATUS_LOG_STATE_INVALID         ((NTSTATUS)0xC01A002BL)
#endif//STATUS_LOG_STATE_INVALID

//
// MessageId: STATUS_LOG_PINNED
//
// MessageText:
//
// Log space cannot be reclaimed because the log is pinned.
//
#ifndef STATUS_LOG_PINNED
#define STATUS_LOG_PINNED                ((NTSTATUS)0xC01A002CL)
#endif//STATUS_LOG_PINNED

//
// MessageId: STATUS_LOG_METADATA_FLUSH_FAILED
//
// MessageText:
//
// Log metadata flush failed.
//
#ifndef STATUS_LOG_METADATA_FLUSH_FAILED
#define STATUS_LOG_METADATA_FLUSH_FAILED ((NTSTATUS)0xC01A002DL)
#endif//STATUS_LOG_METADATA_FLUSH_FAILED

//
// MessageId: STATUS_LOG_INCONSISTENT_SECURITY
//
// MessageText:
//
// Security on the log and its containers is inconsistent.
//
#ifndef STATUS_LOG_INCONSISTENT_SECURITY
#define STATUS_LOG_INCONSISTENT_SECURITY ((NTSTATUS)0xC01A002EL)
#endif//STATUS_LOG_INCONSISTENT_SECURITY

//
// MessageId: STATUS_LOG_APPENDED_FLUSH_FAILED
//
// MessageText:
//
// Records were appended to the log or reservation changes were made, but the log could not be flushed.
//
#ifndef STATUS_LOG_APPENDED_FLUSH_FAILED
#define STATUS_LOG_APPENDED_FLUSH_FAILED ((NTSTATUS)0xC01A002FL)
#endif//STATUS_LOG_APPENDED_FLUSH_FAILED

//
// MessageId: STATUS_LOG_PINNED_RESERVATION
//
// MessageText:
//
// The log is pinned due to reservation consuming most of the log space. Free some reserved records to make space available.
//
#ifndef STATUS_LOG_PINNED_RESERVATION
#define STATUS_LOG_PINNED_RESERVATION    ((NTSTATUS)0xC01A0030L)
#endif//STATUS_LOG_PINNED_RESERVATION


//
// XDDM Video Facility Error codes (videoprt.sys)
//

//
// MessageId: STATUS_VIDEO_HUNG_DISPLAY_DRIVER_THREAD
//
// MessageText:
//
// {Display Driver Stopped Responding}
// The %hs display driver has stopped working normally. Save your work and reboot the system to restore full display functionality. The next time you reboot the machine a dialog will be displayed giving you a chance to upload data about this failure to Microsoft.
//
#ifndef STATUS_VIDEO_HUNG_DISPLAY_DRIVER_THREAD
#define STATUS_VIDEO_HUNG_DISPLAY_DRIVER_THREAD ((NTSTATUS)0xC01B00EAL)
#endif//STATUS_VIDEO_HUNG_DISPLAY_DRIVER_THREAD

//
// MessageId: STATUS_VIDEO_HUNG_DISPLAY_DRIVER_THREAD_RECOVERED
//
// MessageText:
//
// {Display Driver Stopped Responding and recovered}
// The %hs display driver has stopped working normally. The recovery had been performed.
//
#ifndef STATUS_VIDEO_HUNG_DISPLAY_DRIVER_THREAD_RECOVERED
#define STATUS_VIDEO_HUNG_DISPLAY_DRIVER_THREAD_RECOVERED ((NTSTATUS)0x801B00EBL)
#endif//STATUS_VIDEO_HUNG_DISPLAY_DRIVER_THREAD_RECOVERED

//
// MessageId: STATUS_VIDEO_DRIVER_DEBUG_REPORT_REQUEST
//
// MessageText:
//
// {Display Driver Recovered From Failure}
// The %hs display driver has detected and recovered from a failure. Some graphical operations may have failed. The next time you reboot the machine a dialog will be displayed giving you a chance to upload data about this failure to Microsoft.
//
#ifndef STATUS_VIDEO_DRIVER_DEBUG_REPORT_REQUEST
#define STATUS_VIDEO_DRIVER_DEBUG_REPORT_REQUEST ((NTSTATUS)0x401B00ECL)
#endif//STATUS_VIDEO_DRIVER_DEBUG_REPORT_REQUEST


//
// Monitor Facility Error codes (monitor.sys)
//

//
// MessageId: STATUS_MONITOR_NO_DESCRIPTOR
//
// MessageText:
//
// Monitor descriptor could not be obtained.
//
#ifndef STATUS_MONITOR_NO_DESCRIPTOR
#define STATUS_MONITOR_NO_DESCRIPTOR     ((NTSTATUS)0xC01D0001L)
#endif//STATUS_MONITOR_NO_DESCRIPTOR

//
// MessageId: STATUS_MONITOR_UNKNOWN_DESCRIPTOR_FORMAT
//
// MessageText:
//
// Format of the obtained monitor descriptor is not supported by this release.
//
#ifndef STATUS_MONITOR_UNKNOWN_DESCRIPTOR_FORMAT
#define STATUS_MONITOR_UNKNOWN_DESCRIPTOR_FORMAT ((NTSTATUS)0xC01D0002L)
#endif//STATUS_MONITOR_UNKNOWN_DESCRIPTOR_FORMAT

//
// MessageId: STATUS_MONITOR_INVALID_DESCRIPTOR_CHECKSUM
//
// MessageText:
//
// Checksum of the obtained monitor descriptor is invalid.
//
#ifndef STATUS_MONITOR_INVALID_DESCRIPTOR_CHECKSUM
#define STATUS_MONITOR_INVALID_DESCRIPTOR_CHECKSUM ((NTSTATUS)0xC01D0003L)
#endif//STATUS_MONITOR_INVALID_DESCRIPTOR_CHECKSUM

//
// MessageId: STATUS_MONITOR_INVALID_STANDARD_TIMING_BLOCK
//
// MessageText:
//
// Monitor descriptor contains an invalid standard timing block.
//
#ifndef STATUS_MONITOR_INVALID_STANDARD_TIMING_BLOCK
#define STATUS_MONITOR_INVALID_STANDARD_TIMING_BLOCK ((NTSTATUS)0xC01D0004L)
#endif//STATUS_MONITOR_INVALID_STANDARD_TIMING_BLOCK

//
// MessageId: STATUS_MONITOR_WMI_DATABLOCK_REGISTRATION_FAILED
//
// MessageText:
//
// WMI data block registration failed for one of the MSMonitorClass WMI subclasses.
//
#ifndef STATUS_MONITOR_WMI_DATABLOCK_REGISTRATION_FAILED
#define STATUS_MONITOR_WMI_DATABLOCK_REGISTRATION_FAILED ((NTSTATUS)0xC01D0005L)
#endif//STATUS_MONITOR_WMI_DATABLOCK_REGISTRATION_FAILED

//
// MessageId: STATUS_MONITOR_INVALID_SERIAL_NUMBER_MONDSC_BLOCK
//
// MessageText:
//
// Provided monitor descriptor block is either corrupted or does not contain monitor's detailed serial number.
//
#ifndef STATUS_MONITOR_INVALID_SERIAL_NUMBER_MONDSC_BLOCK
#define STATUS_MONITOR_INVALID_SERIAL_NUMBER_MONDSC_BLOCK ((NTSTATUS)0xC01D0006L)
#endif//STATUS_MONITOR_INVALID_SERIAL_NUMBER_MONDSC_BLOCK

//
// MessageId: STATUS_MONITOR_INVALID_USER_FRIENDLY_MONDSC_BLOCK
//
// MessageText:
//
// Provided monitor descriptor block is either corrupted or does not contain monitor's user friendly name.
//
#ifndef STATUS_MONITOR_INVALID_USER_FRIENDLY_MONDSC_BLOCK
#define STATUS_MONITOR_INVALID_USER_FRIENDLY_MONDSC_BLOCK ((NTSTATUS)0xC01D0007L)
#endif//STATUS_MONITOR_INVALID_USER_FRIENDLY_MONDSC_BLOCK

//
// MessageId: STATUS_MONITOR_NO_MORE_DESCRIPTOR_DATA
//
// MessageText:
//
// There is no monitor descriptor data at the specified (offset, size) region.
//
#ifndef STATUS_MONITOR_NO_MORE_DESCRIPTOR_DATA
#define STATUS_MONITOR_NO_MORE_DESCRIPTOR_DATA ((NTSTATUS)0xC01D0008L)
#endif//STATUS_MONITOR_NO_MORE_DESCRIPTOR_DATA

//
// MessageId: STATUS_MONITOR_INVALID_DETAILED_TIMING_BLOCK
//
// MessageText:
//
// Monitor descriptor contains an invalid detailed timing block.
//
#ifndef STATUS_MONITOR_INVALID_DETAILED_TIMING_BLOCK
#define STATUS_MONITOR_INVALID_DETAILED_TIMING_BLOCK ((NTSTATUS)0xC01D0009L)
#endif//STATUS_MONITOR_INVALID_DETAILED_TIMING_BLOCK

//
// MessageId: STATUS_MONITOR_INVALID_MANUFACTURE_DATE
//
// MessageText:
//
// Monitor descriptor contains invalid manufacture date.
//
#ifndef STATUS_MONITOR_INVALID_MANUFACTURE_DATE
#define STATUS_MONITOR_INVALID_MANUFACTURE_DATE ((NTSTATUS)0xC01D000AL)
#endif//STATUS_MONITOR_INVALID_MANUFACTURE_DATE


//
// Graphics Facility Error codes (dxg.sys, dxgkrnl.sys)
//

//
//   Common Windows Graphics Kernel Subsystem status codes {0x0000..0x00ff}
//
//
// MessageId: STATUS_GRAPHICS_NOT_EXCLUSIVE_MODE_OWNER
//
// MessageText:
//
// Exclusive mode ownership is needed to create unmanaged primary allocation.
//
#ifndef STATUS_GRAPHICS_NOT_EXCLUSIVE_MODE_OWNER
#define STATUS_GRAPHICS_NOT_EXCLUSIVE_MODE_OWNER ((NTSTATUS)0xC01E0000L)
#endif//STATUS_GRAPHICS_NOT_EXCLUSIVE_MODE_OWNER

//
// MessageId: STATUS_GRAPHICS_INSUFFICIENT_DMA_BUFFER
//
// MessageText:
//
// The driver needs more DMA buffer space in order to complete the requested operation.
//
#ifndef STATUS_GRAPHICS_INSUFFICIENT_DMA_BUFFER
#define STATUS_GRAPHICS_INSUFFICIENT_DMA_BUFFER ((NTSTATUS)0xC01E0001L)
#endif//STATUS_GRAPHICS_INSUFFICIENT_DMA_BUFFER

//
// MessageId: STATUS_GRAPHICS_INVALID_DISPLAY_ADAPTER
//
// MessageText:
//
// Specified display adapter handle is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_DISPLAY_ADAPTER
#define STATUS_GRAPHICS_INVALID_DISPLAY_ADAPTER ((NTSTATUS)0xC01E0002L)
#endif//STATUS_GRAPHICS_INVALID_DISPLAY_ADAPTER

//
// MessageId: STATUS_GRAPHICS_ADAPTER_WAS_RESET
//
// MessageText:
//
// Specified display adapter and all of its state has been reset.
//
#ifndef STATUS_GRAPHICS_ADAPTER_WAS_RESET
#define STATUS_GRAPHICS_ADAPTER_WAS_RESET ((NTSTATUS)0xC01E0003L)
#endif//STATUS_GRAPHICS_ADAPTER_WAS_RESET

//
// MessageId: STATUS_GRAPHICS_INVALID_DRIVER_MODEL
//
// MessageText:
//
// The driver stack doesn't match the expected driver model.
//
#ifndef STATUS_GRAPHICS_INVALID_DRIVER_MODEL
#define STATUS_GRAPHICS_INVALID_DRIVER_MODEL ((NTSTATUS)0xC01E0004L)
#endif//STATUS_GRAPHICS_INVALID_DRIVER_MODEL

//
// MessageId: STATUS_GRAPHICS_PRESENT_MODE_CHANGED
//
// MessageText:
//
// Present happened but ended up into the changed desktop mode
//
#ifndef STATUS_GRAPHICS_PRESENT_MODE_CHANGED
#define STATUS_GRAPHICS_PRESENT_MODE_CHANGED ((NTSTATUS)0xC01E0005L)
#endif//STATUS_GRAPHICS_PRESENT_MODE_CHANGED

//
// MessageId: STATUS_GRAPHICS_PRESENT_OCCLUDED
//
// MessageText:
//
// Nothing to present due to desktop occlusion
//
#ifndef STATUS_GRAPHICS_PRESENT_OCCLUDED
#define STATUS_GRAPHICS_PRESENT_OCCLUDED ((NTSTATUS)0xC01E0006L)
#endif//STATUS_GRAPHICS_PRESENT_OCCLUDED

//
// MessageId: STATUS_GRAPHICS_PRESENT_DENIED
//
// MessageText:
//
// Not able to present due to denial of desktop access
//
#ifndef STATUS_GRAPHICS_PRESENT_DENIED
#define STATUS_GRAPHICS_PRESENT_DENIED   ((NTSTATUS)0xC01E0007L)
#endif//STATUS_GRAPHICS_PRESENT_DENIED

//
// MessageId: STATUS_GRAPHICS_CANNOTCOLORCONVERT
//
// MessageText:
//
// Not able to present with color convertion
//
#ifndef STATUS_GRAPHICS_CANNOTCOLORCONVERT
#define STATUS_GRAPHICS_CANNOTCOLORCONVERT ((NTSTATUS)0xC01E0008L)
#endif//STATUS_GRAPHICS_CANNOTCOLORCONVERT

//
// MessageId: STATUS_GRAPHICS_DRIVER_MISMATCH
//
// MessageText:
//
// The kernel driver detected a version mismatch between it and the user mode driver.
//
#ifndef STATUS_GRAPHICS_DRIVER_MISMATCH
#define STATUS_GRAPHICS_DRIVER_MISMATCH  ((NTSTATUS)0xC01E0009L)
#endif//STATUS_GRAPHICS_DRIVER_MISMATCH

//
// MessageId: STATUS_GRAPHICS_PARTIAL_DATA_POPULATED
//
// MessageText:
//
// Specified buffer is not big enough to contain entire requested dataset. Partial data populated upto the size of the buffer. Caller needs to provide buffer of size as specified in the partially populated buffer's content (interface specific).
//
#ifndef STATUS_GRAPHICS_PARTIAL_DATA_POPULATED
#define STATUS_GRAPHICS_PARTIAL_DATA_POPULATED ((NTSTATUS)0x401E000AL)
#endif//STATUS_GRAPHICS_PARTIAL_DATA_POPULATED

//
// MessageId: STATUS_GRAPHICS_PRESENT_REDIRECTION_DISABLED
//
// MessageText:
//
// Present redirection is disabled (desktop windowing management subsystem is off).
//
#ifndef STATUS_GRAPHICS_PRESENT_REDIRECTION_DISABLED
#define STATUS_GRAPHICS_PRESENT_REDIRECTION_DISABLED ((NTSTATUS)0xC01E000BL)
#endif//STATUS_GRAPHICS_PRESENT_REDIRECTION_DISABLED

//
// MessageId: STATUS_GRAPHICS_PRESENT_UNOCCLUDED
//
// MessageText:
//
// Previous exclusive VidPn source owner has released its ownership
//
#ifndef STATUS_GRAPHICS_PRESENT_UNOCCLUDED
#define STATUS_GRAPHICS_PRESENT_UNOCCLUDED ((NTSTATUS)0xC01E000CL)
#endif//STATUS_GRAPHICS_PRESENT_UNOCCLUDED

//
// MessageId: STATUS_GRAPHICS_WINDOWDC_NOT_AVAILABLE
//
// MessageText:
//
// Window DC is not available for presentation
//
#ifndef STATUS_GRAPHICS_WINDOWDC_NOT_AVAILABLE
#define STATUS_GRAPHICS_WINDOWDC_NOT_AVAILABLE ((NTSTATUS)0xC01E000DL)
#endif//STATUS_GRAPHICS_WINDOWDC_NOT_AVAILABLE

//
// MessageId: STATUS_GRAPHICS_WINDOWLESS_PRESENT_DISABLED
//
// MessageText:
//
// Windowless present is disabled (desktop windowing management subsystem is off).
//
#ifndef STATUS_GRAPHICS_WINDOWLESS_PRESENT_DISABLED
#define STATUS_GRAPHICS_WINDOWLESS_PRESENT_DISABLED ((NTSTATUS)0xC01E000EL)
#endif//STATUS_GRAPHICS_WINDOWLESS_PRESENT_DISABLED

//
//   Video Memory Manager (VidMM) specific status codes {0x0100..0x01ff}
//
//
// MessageId: STATUS_GRAPHICS_NO_VIDEO_MEMORY
//
// MessageText:
//
// Not enough video memory available to complete the operation.
//
#ifndef STATUS_GRAPHICS_NO_VIDEO_MEMORY
#define STATUS_GRAPHICS_NO_VIDEO_MEMORY  ((NTSTATUS)0xC01E0100L)
#endif//STATUS_GRAPHICS_NO_VIDEO_MEMORY

//
// MessageId: STATUS_GRAPHICS_CANT_LOCK_MEMORY
//
// MessageText:
//
// Couldn't probe and lock the underlying memory of an allocation.
//
#ifndef STATUS_GRAPHICS_CANT_LOCK_MEMORY
#define STATUS_GRAPHICS_CANT_LOCK_MEMORY ((NTSTATUS)0xC01E0101L)
#endif//STATUS_GRAPHICS_CANT_LOCK_MEMORY

//
// MessageId: STATUS_GRAPHICS_ALLOCATION_BUSY
//
// MessageText:
//
// The allocation is currently busy.
//
#ifndef STATUS_GRAPHICS_ALLOCATION_BUSY
#define STATUS_GRAPHICS_ALLOCATION_BUSY  ((NTSTATUS)0xC01E0102L)
#endif//STATUS_GRAPHICS_ALLOCATION_BUSY

//
// MessageId: STATUS_GRAPHICS_TOO_MANY_REFERENCES
//
// MessageText:
//
// An object being referenced has already reached the maximum reference count and can't be referenced any further.
//
#ifndef STATUS_GRAPHICS_TOO_MANY_REFERENCES
#define STATUS_GRAPHICS_TOO_MANY_REFERENCES ((NTSTATUS)0xC01E0103L)
#endif//STATUS_GRAPHICS_TOO_MANY_REFERENCES

//
// MessageId: STATUS_GRAPHICS_TRY_AGAIN_LATER
//
// MessageText:
//
// A problem couldn't be solved due to some currently existing condition. The problem should be tried again later.
//
#ifndef STATUS_GRAPHICS_TRY_AGAIN_LATER
#define STATUS_GRAPHICS_TRY_AGAIN_LATER  ((NTSTATUS)0xC01E0104L)
#endif//STATUS_GRAPHICS_TRY_AGAIN_LATER

//
// MessageId: STATUS_GRAPHICS_TRY_AGAIN_NOW
//
// MessageText:
//
// A problem couldn't be solved due to some currently existing condition. The problem should be tried again immediately.
//
#ifndef STATUS_GRAPHICS_TRY_AGAIN_NOW
#define STATUS_GRAPHICS_TRY_AGAIN_NOW    ((NTSTATUS)0xC01E0105L)
#endif//STATUS_GRAPHICS_TRY_AGAIN_NOW

//
// MessageId: STATUS_GRAPHICS_ALLOCATION_INVALID
//
// MessageText:
//
// The allocation is invalid.
//
#ifndef STATUS_GRAPHICS_ALLOCATION_INVALID
#define STATUS_GRAPHICS_ALLOCATION_INVALID ((NTSTATUS)0xC01E0106L)
#endif//STATUS_GRAPHICS_ALLOCATION_INVALID

//
// MessageId: STATUS_GRAPHICS_UNSWIZZLING_APERTURE_UNAVAILABLE
//
// MessageText:
//
// No more unswizzling aperture are currently available.
//
#ifndef STATUS_GRAPHICS_UNSWIZZLING_APERTURE_UNAVAILABLE
#define STATUS_GRAPHICS_UNSWIZZLING_APERTURE_UNAVAILABLE ((NTSTATUS)0xC01E0107L)
#endif//STATUS_GRAPHICS_UNSWIZZLING_APERTURE_UNAVAILABLE

//
// MessageId: STATUS_GRAPHICS_UNSWIZZLING_APERTURE_UNSUPPORTED
//
// MessageText:
//
// The current allocation can't be unswizzled by an aperture.
//
#ifndef STATUS_GRAPHICS_UNSWIZZLING_APERTURE_UNSUPPORTED
#define STATUS_GRAPHICS_UNSWIZZLING_APERTURE_UNSUPPORTED ((NTSTATUS)0xC01E0108L)
#endif//STATUS_GRAPHICS_UNSWIZZLING_APERTURE_UNSUPPORTED

//
// MessageId: STATUS_GRAPHICS_CANT_EVICT_PINNED_ALLOCATION
//
// MessageText:
//
// The request failed because a pinned allocation can't be evicted.
//
#ifndef STATUS_GRAPHICS_CANT_EVICT_PINNED_ALLOCATION
#define STATUS_GRAPHICS_CANT_EVICT_PINNED_ALLOCATION ((NTSTATUS)0xC01E0109L)
#endif//STATUS_GRAPHICS_CANT_EVICT_PINNED_ALLOCATION

//
// MessageId: STATUS_GRAPHICS_INVALID_ALLOCATION_USAGE
//
// MessageText:
//
// The allocation can't be used from its current segment location for the specified operation.
//
#ifndef STATUS_GRAPHICS_INVALID_ALLOCATION_USAGE
#define STATUS_GRAPHICS_INVALID_ALLOCATION_USAGE ((NTSTATUS)0xC01E0110L)
#endif//STATUS_GRAPHICS_INVALID_ALLOCATION_USAGE

//
// MessageId: STATUS_GRAPHICS_CANT_RENDER_LOCKED_ALLOCATION
//
// MessageText:
//
// A locked allocation can't be used in the current command buffer.
//
#ifndef STATUS_GRAPHICS_CANT_RENDER_LOCKED_ALLOCATION
#define STATUS_GRAPHICS_CANT_RENDER_LOCKED_ALLOCATION ((NTSTATUS)0xC01E0111L)
#endif//STATUS_GRAPHICS_CANT_RENDER_LOCKED_ALLOCATION

//
// MessageId: STATUS_GRAPHICS_ALLOCATION_CLOSED
//
// MessageText:
//
// The allocation being referenced has been closed permanently.
//
#ifndef STATUS_GRAPHICS_ALLOCATION_CLOSED
#define STATUS_GRAPHICS_ALLOCATION_CLOSED ((NTSTATUS)0xC01E0112L)
#endif//STATUS_GRAPHICS_ALLOCATION_CLOSED

//
// MessageId: STATUS_GRAPHICS_INVALID_ALLOCATION_INSTANCE
//
// MessageText:
//
// An invalid allocation instance is being referenced.
//
#ifndef STATUS_GRAPHICS_INVALID_ALLOCATION_INSTANCE
#define STATUS_GRAPHICS_INVALID_ALLOCATION_INSTANCE ((NTSTATUS)0xC01E0113L)
#endif//STATUS_GRAPHICS_INVALID_ALLOCATION_INSTANCE

//
// MessageId: STATUS_GRAPHICS_INVALID_ALLOCATION_HANDLE
//
// MessageText:
//
// An invalid allocation handle is being referenced.
//
#ifndef STATUS_GRAPHICS_INVALID_ALLOCATION_HANDLE
#define STATUS_GRAPHICS_INVALID_ALLOCATION_HANDLE ((NTSTATUS)0xC01E0114L)
#endif//STATUS_GRAPHICS_INVALID_ALLOCATION_HANDLE

//
// MessageId: STATUS_GRAPHICS_WRONG_ALLOCATION_DEVICE
//
// MessageText:
//
// The allocation being referenced doesn't belong to the current device.
//
#ifndef STATUS_GRAPHICS_WRONG_ALLOCATION_DEVICE
#define STATUS_GRAPHICS_WRONG_ALLOCATION_DEVICE ((NTSTATUS)0xC01E0115L)
#endif//STATUS_GRAPHICS_WRONG_ALLOCATION_DEVICE

//
// MessageId: STATUS_GRAPHICS_ALLOCATION_CONTENT_LOST
//
// MessageText:
//
// The specified allocation lost its content.
//
#ifndef STATUS_GRAPHICS_ALLOCATION_CONTENT_LOST
#define STATUS_GRAPHICS_ALLOCATION_CONTENT_LOST ((NTSTATUS)0xC01E0116L)
#endif//STATUS_GRAPHICS_ALLOCATION_CONTENT_LOST

//
//   Video GPU Scheduler (VidSch) specific status codes {0x0200..0x02ff}
//
//
// MessageId: STATUS_GRAPHICS_GPU_EXCEPTION_ON_DEVICE
//
// MessageText:
//
// GPU exception is detected on the given device. The device is not able to be scheduled.
//
#ifndef STATUS_GRAPHICS_GPU_EXCEPTION_ON_DEVICE
#define STATUS_GRAPHICS_GPU_EXCEPTION_ON_DEVICE ((NTSTATUS)0xC01E0200L)
#endif//STATUS_GRAPHICS_GPU_EXCEPTION_ON_DEVICE

//
// MessageId: STATUS_GRAPHICS_SKIP_ALLOCATION_PREPARATION
//
// MessageText:
//
// Skip preparation of allocations referenced by the DMA buffer.
//
#ifndef STATUS_GRAPHICS_SKIP_ALLOCATION_PREPARATION
#define STATUS_GRAPHICS_SKIP_ALLOCATION_PREPARATION ((NTSTATUS)0x401E0201L)
#endif//STATUS_GRAPHICS_SKIP_ALLOCATION_PREPARATION

//
//   Video Present Network Management (VidPNMgr) specific status codes {0x0300..0x03ff}
//
//
// MessageId: STATUS_GRAPHICS_INVALID_VIDPN_TOPOLOGY
//
// MessageText:
//
// Specified VidPN topology is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_VIDPN_TOPOLOGY
#define STATUS_GRAPHICS_INVALID_VIDPN_TOPOLOGY ((NTSTATUS)0xC01E0300L)
#endif//STATUS_GRAPHICS_INVALID_VIDPN_TOPOLOGY

//
// MessageId: STATUS_GRAPHICS_VIDPN_TOPOLOGY_NOT_SUPPORTED
//
// MessageText:
//
// Specified VidPN topology is valid but is not supported by this model of the display adapter.
//
#ifndef STATUS_GRAPHICS_VIDPN_TOPOLOGY_NOT_SUPPORTED
#define STATUS_GRAPHICS_VIDPN_TOPOLOGY_NOT_SUPPORTED ((NTSTATUS)0xC01E0301L)
#endif//STATUS_GRAPHICS_VIDPN_TOPOLOGY_NOT_SUPPORTED

//
// MessageId: STATUS_GRAPHICS_VIDPN_TOPOLOGY_CURRENTLY_NOT_SUPPORTED
//
// MessageText:
//
// Specified VidPN topology is valid but is not supported by the display adapter at this time, due to current allocation of its resources.
//
#ifndef STATUS_GRAPHICS_VIDPN_TOPOLOGY_CURRENTLY_NOT_SUPPORTED
#define STATUS_GRAPHICS_VIDPN_TOPOLOGY_CURRENTLY_NOT_SUPPORTED ((NTSTATUS)0xC01E0302L)
#endif//STATUS_GRAPHICS_VIDPN_TOPOLOGY_CURRENTLY_NOT_SUPPORTED

//
// MessageId: STATUS_GRAPHICS_INVALID_VIDPN
//
// MessageText:
//
// Specified VidPN handle is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_VIDPN
#define STATUS_GRAPHICS_INVALID_VIDPN    ((NTSTATUS)0xC01E0303L)
#endif//STATUS_GRAPHICS_INVALID_VIDPN

//
// MessageId: STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_SOURCE
//
// MessageText:
//
// Specified video present source is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_SOURCE
#define STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_SOURCE ((NTSTATUS)0xC01E0304L)
#endif//STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_SOURCE

//
// MessageId: STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_TARGET
//
// MessageText:
//
// Specified video present target is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_TARGET
#define STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_TARGET ((NTSTATUS)0xC01E0305L)
#endif//STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_TARGET

//
// MessageId: STATUS_GRAPHICS_VIDPN_MODALITY_NOT_SUPPORTED
//
// MessageText:
//
// Specified VidPN modality is not supported (e.g. at least two of the pinned modes are not cofunctional).
//
#ifndef STATUS_GRAPHICS_VIDPN_MODALITY_NOT_SUPPORTED
#define STATUS_GRAPHICS_VIDPN_MODALITY_NOT_SUPPORTED ((NTSTATUS)0xC01E0306L)
#endif//STATUS_GRAPHICS_VIDPN_MODALITY_NOT_SUPPORTED

//
// MessageId: STATUS_GRAPHICS_MODE_NOT_PINNED
//
// MessageText:
//
// No mode is pinned on the specified VidPN source/target.
//
#ifndef STATUS_GRAPHICS_MODE_NOT_PINNED
#define STATUS_GRAPHICS_MODE_NOT_PINNED  ((NTSTATUS)0x401E0307L)
#endif//STATUS_GRAPHICS_MODE_NOT_PINNED

//
// MessageId: STATUS_GRAPHICS_INVALID_VIDPN_SOURCEMODESET
//
// MessageText:
//
// Specified VidPN source mode set is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_VIDPN_SOURCEMODESET
#define STATUS_GRAPHICS_INVALID_VIDPN_SOURCEMODESET ((NTSTATUS)0xC01E0308L)
#endif//STATUS_GRAPHICS_INVALID_VIDPN_SOURCEMODESET

//
// MessageId: STATUS_GRAPHICS_INVALID_VIDPN_TARGETMODESET
//
// MessageText:
//
// Specified VidPN target mode set is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_VIDPN_TARGETMODESET
#define STATUS_GRAPHICS_INVALID_VIDPN_TARGETMODESET ((NTSTATUS)0xC01E0309L)
#endif//STATUS_GRAPHICS_INVALID_VIDPN_TARGETMODESET

//
// MessageId: STATUS_GRAPHICS_INVALID_FREQUENCY
//
// MessageText:
//
// Specified video signal frequency is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_FREQUENCY
#define STATUS_GRAPHICS_INVALID_FREQUENCY ((NTSTATUS)0xC01E030AL)
#endif//STATUS_GRAPHICS_INVALID_FREQUENCY

//
// MessageId: STATUS_GRAPHICS_INVALID_ACTIVE_REGION
//
// MessageText:
//
// Specified video signal active region is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_ACTIVE_REGION
#define STATUS_GRAPHICS_INVALID_ACTIVE_REGION ((NTSTATUS)0xC01E030BL)
#endif//STATUS_GRAPHICS_INVALID_ACTIVE_REGION

//
// MessageId: STATUS_GRAPHICS_INVALID_TOTAL_REGION
//
// MessageText:
//
// Specified video signal total region is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_TOTAL_REGION
#define STATUS_GRAPHICS_INVALID_TOTAL_REGION ((NTSTATUS)0xC01E030CL)
#endif//STATUS_GRAPHICS_INVALID_TOTAL_REGION

//
// MessageId: STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_SOURCE_MODE
//
// MessageText:
//
// Specified video present source mode is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_SOURCE_MODE
#define STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_SOURCE_MODE ((NTSTATUS)0xC01E0310L)
#endif//STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_SOURCE_MODE

//
// MessageId: STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_TARGET_MODE
//
// MessageText:
//
// Specified video present target mode is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_TARGET_MODE
#define STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_TARGET_MODE ((NTSTATUS)0xC01E0311L)
#endif//STATUS_GRAPHICS_INVALID_VIDEO_PRESENT_TARGET_MODE

//
// MessageId: STATUS_GRAPHICS_PINNED_MODE_MUST_REMAIN_IN_SET
//
// MessageText:
//
// Pinned mode must remain in the set on VidPN's cofunctional modality enumeration.
//
#ifndef STATUS_GRAPHICS_PINNED_MODE_MUST_REMAIN_IN_SET
#define STATUS_GRAPHICS_PINNED_MODE_MUST_REMAIN_IN_SET ((NTSTATUS)0xC01E0312L)
#endif//STATUS_GRAPHICS_PINNED_MODE_MUST_REMAIN_IN_SET

//
// MessageId: STATUS_GRAPHICS_PATH_ALREADY_IN_TOPOLOGY
//
// MessageText:
//
// Specified video present path is already in VidPN's topology.
//
#ifndef STATUS_GRAPHICS_PATH_ALREADY_IN_TOPOLOGY
#define STATUS_GRAPHICS_PATH_ALREADY_IN_TOPOLOGY ((NTSTATUS)0xC01E0313L)
#endif//STATUS_GRAPHICS_PATH_ALREADY_IN_TOPOLOGY

//
// MessageId: STATUS_GRAPHICS_MODE_ALREADY_IN_MODESET
//
// MessageText:
//
// Specified mode is already in the mode set.
//
#ifndef STATUS_GRAPHICS_MODE_ALREADY_IN_MODESET
#define STATUS_GRAPHICS_MODE_ALREADY_IN_MODESET ((NTSTATUS)0xC01E0314L)
#endif//STATUS_GRAPHICS_MODE_ALREADY_IN_MODESET

//
// MessageId: STATUS_GRAPHICS_INVALID_VIDEOPRESENTSOURCESET
//
// MessageText:
//
// Specified video present source set is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_VIDEOPRESENTSOURCESET
#define STATUS_GRAPHICS_INVALID_VIDEOPRESENTSOURCESET ((NTSTATUS)0xC01E0315L)
#endif//STATUS_GRAPHICS_INVALID_VIDEOPRESENTSOURCESET

//
// MessageId: STATUS_GRAPHICS_INVALID_VIDEOPRESENTTARGETSET
//
// MessageText:
//
// Specified video present target set is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_VIDEOPRESENTTARGETSET
#define STATUS_GRAPHICS_INVALID_VIDEOPRESENTTARGETSET ((NTSTATUS)0xC01E0316L)
#endif//STATUS_GRAPHICS_INVALID_VIDEOPRESENTTARGETSET

//
// MessageId: STATUS_GRAPHICS_SOURCE_ALREADY_IN_SET
//
// MessageText:
//
// Specified video present source is already in the video present source set.
//
#ifndef STATUS_GRAPHICS_SOURCE_ALREADY_IN_SET
#define STATUS_GRAPHICS_SOURCE_ALREADY_IN_SET ((NTSTATUS)0xC01E0317L)
#endif//STATUS_GRAPHICS_SOURCE_ALREADY_IN_SET

//
// MessageId: STATUS_GRAPHICS_TARGET_ALREADY_IN_SET
//
// MessageText:
//
// Specified video present target is already in the video present target set.
//
#ifndef STATUS_GRAPHICS_TARGET_ALREADY_IN_SET
#define STATUS_GRAPHICS_TARGET_ALREADY_IN_SET ((NTSTATUS)0xC01E0318L)
#endif//STATUS_GRAPHICS_TARGET_ALREADY_IN_SET

//
// MessageId: STATUS_GRAPHICS_INVALID_VIDPN_PRESENT_PATH
//
// MessageText:
//
// Specified VidPN present path is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_VIDPN_PRESENT_PATH
#define STATUS_GRAPHICS_INVALID_VIDPN_PRESENT_PATH ((NTSTATUS)0xC01E0319L)
#endif//STATUS_GRAPHICS_INVALID_VIDPN_PRESENT_PATH

//
// MessageId: STATUS_GRAPHICS_NO_RECOMMENDED_VIDPN_TOPOLOGY
//
// MessageText:
//
// Miniport has no recommendation for augmentation of the specified VidPN's topology.
//
#ifndef STATUS_GRAPHICS_NO_RECOMMENDED_VIDPN_TOPOLOGY
#define STATUS_GRAPHICS_NO_RECOMMENDED_VIDPN_TOPOLOGY ((NTSTATUS)0xC01E031AL)
#endif//STATUS_GRAPHICS_NO_RECOMMENDED_VIDPN_TOPOLOGY

//
// MessageId: STATUS_GRAPHICS_INVALID_MONITOR_FREQUENCYRANGESET
//
// MessageText:
//
// Specified monitor frequency range set is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_MONITOR_FREQUENCYRANGESET
#define STATUS_GRAPHICS_INVALID_MONITOR_FREQUENCYRANGESET ((NTSTATUS)0xC01E031BL)
#endif//STATUS_GRAPHICS_INVALID_MONITOR_FREQUENCYRANGESET

//
// MessageId: STATUS_GRAPHICS_INVALID_MONITOR_FREQUENCYRANGE
//
// MessageText:
//
// Specified monitor frequency range is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_MONITOR_FREQUENCYRANGE
#define STATUS_GRAPHICS_INVALID_MONITOR_FREQUENCYRANGE ((NTSTATUS)0xC01E031CL)
#endif//STATUS_GRAPHICS_INVALID_MONITOR_FREQUENCYRANGE

//
// MessageId: STATUS_GRAPHICS_FREQUENCYRANGE_NOT_IN_SET
//
// MessageText:
//
// Specified frequency range is not in the specified monitor frequency range set.
//
#ifndef STATUS_GRAPHICS_FREQUENCYRANGE_NOT_IN_SET
#define STATUS_GRAPHICS_FREQUENCYRANGE_NOT_IN_SET ((NTSTATUS)0xC01E031DL)
#endif//STATUS_GRAPHICS_FREQUENCYRANGE_NOT_IN_SET

//
// MessageId: STATUS_GRAPHICS_NO_PREFERRED_MODE
//
// MessageText:
//
// Specified mode set does not specify preference for one of its modes.
//
#ifndef STATUS_GRAPHICS_NO_PREFERRED_MODE
#define STATUS_GRAPHICS_NO_PREFERRED_MODE ((NTSTATUS)0x401E031EL)
#endif//STATUS_GRAPHICS_NO_PREFERRED_MODE

//
// MessageId: STATUS_GRAPHICS_FREQUENCYRANGE_ALREADY_IN_SET
//
// MessageText:
//
// Specified frequency range is already in the specified monitor frequency range set.
//
#ifndef STATUS_GRAPHICS_FREQUENCYRANGE_ALREADY_IN_SET
#define STATUS_GRAPHICS_FREQUENCYRANGE_ALREADY_IN_SET ((NTSTATUS)0xC01E031FL)
#endif//STATUS_GRAPHICS_FREQUENCYRANGE_ALREADY_IN_SET

//
// MessageId: STATUS_GRAPHICS_STALE_MODESET
//
// MessageText:
//
// Specified mode set is stale. Please reacquire the new mode set.
//
#ifndef STATUS_GRAPHICS_STALE_MODESET
#define STATUS_GRAPHICS_STALE_MODESET    ((NTSTATUS)0xC01E0320L)
#endif//STATUS_GRAPHICS_STALE_MODESET

//
// MessageId: STATUS_GRAPHICS_INVALID_MONITOR_SOURCEMODESET
//
// MessageText:
//
// Specified monitor source mode set is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_MONITOR_SOURCEMODESET
#define STATUS_GRAPHICS_INVALID_MONITOR_SOURCEMODESET ((NTSTATUS)0xC01E0321L)
#endif//STATUS_GRAPHICS_INVALID_MONITOR_SOURCEMODESET

//
// MessageId: STATUS_GRAPHICS_INVALID_MONITOR_SOURCE_MODE
//
// MessageText:
//
// Specified monitor source mode is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_MONITOR_SOURCE_MODE
#define STATUS_GRAPHICS_INVALID_MONITOR_SOURCE_MODE ((NTSTATUS)0xC01E0322L)
#endif//STATUS_GRAPHICS_INVALID_MONITOR_SOURCE_MODE

//
// MessageId: STATUS_GRAPHICS_NO_RECOMMENDED_FUNCTIONAL_VIDPN
//
// MessageText:
//
// Miniport does not have any recommendation regarding the request to provide a functional VidPN given the current display adapter configuration.
//
#ifndef STATUS_GRAPHICS_NO_RECOMMENDED_FUNCTIONAL_VIDPN
#define STATUS_GRAPHICS_NO_RECOMMENDED_FUNCTIONAL_VIDPN ((NTSTATUS)0xC01E0323L)
#endif//STATUS_GRAPHICS_NO_RECOMMENDED_FUNCTIONAL_VIDPN

//
// MessageId: STATUS_GRAPHICS_MODE_ID_MUST_BE_UNIQUE
//
// MessageText:
//
// ID of the specified mode is already used by another mode in the set.
//
#ifndef STATUS_GRAPHICS_MODE_ID_MUST_BE_UNIQUE
#define STATUS_GRAPHICS_MODE_ID_MUST_BE_UNIQUE ((NTSTATUS)0xC01E0324L)
#endif//STATUS_GRAPHICS_MODE_ID_MUST_BE_UNIQUE

//
// MessageId: STATUS_GRAPHICS_EMPTY_ADAPTER_MONITOR_MODE_SUPPORT_INTERSECTION
//
// MessageText:
//
// System failed to determine a mode that is supported by both the display adapter and the monitor connected to it.
//
#ifndef STATUS_GRAPHICS_EMPTY_ADAPTER_MONITOR_MODE_SUPPORT_INTERSECTION
#define STATUS_GRAPHICS_EMPTY_ADAPTER_MONITOR_MODE_SUPPORT_INTERSECTION ((NTSTATUS)0xC01E0325L)
#endif//STATUS_GRAPHICS_EMPTY_ADAPTER_MONITOR_MODE_SUPPORT_INTERSECTION

//
// MessageId: STATUS_GRAPHICS_VIDEO_PRESENT_TARGETS_LESS_THAN_SOURCES
//
// MessageText:
//
// Number of video present targets must be greater than or equal to the number of video present sources.
//
#ifndef STATUS_GRAPHICS_VIDEO_PRESENT_TARGETS_LESS_THAN_SOURCES
#define STATUS_GRAPHICS_VIDEO_PRESENT_TARGETS_LESS_THAN_SOURCES ((NTSTATUS)0xC01E0326L)
#endif//STATUS_GRAPHICS_VIDEO_PRESENT_TARGETS_LESS_THAN_SOURCES

//
// MessageId: STATUS_GRAPHICS_PATH_NOT_IN_TOPOLOGY
//
// MessageText:
//
// Specified present path is not in VidPN's topology.
//
#ifndef STATUS_GRAPHICS_PATH_NOT_IN_TOPOLOGY
#define STATUS_GRAPHICS_PATH_NOT_IN_TOPOLOGY ((NTSTATUS)0xC01E0327L)
#endif//STATUS_GRAPHICS_PATH_NOT_IN_TOPOLOGY

//
// MessageId: STATUS_GRAPHICS_ADAPTER_MUST_HAVE_AT_LEAST_ONE_SOURCE
//
// MessageText:
//
// Display adapter must have at least one video present source.
//
#ifndef STATUS_GRAPHICS_ADAPTER_MUST_HAVE_AT_LEAST_ONE_SOURCE
#define STATUS_GRAPHICS_ADAPTER_MUST_HAVE_AT_LEAST_ONE_SOURCE ((NTSTATUS)0xC01E0328L)
#endif//STATUS_GRAPHICS_ADAPTER_MUST_HAVE_AT_LEAST_ONE_SOURCE

//
// MessageId: STATUS_GRAPHICS_ADAPTER_MUST_HAVE_AT_LEAST_ONE_TARGET
//
// MessageText:
//
// Display adapter must have at least one video present target.
//
#ifndef STATUS_GRAPHICS_ADAPTER_MUST_HAVE_AT_LEAST_ONE_TARGET
#define STATUS_GRAPHICS_ADAPTER_MUST_HAVE_AT_LEAST_ONE_TARGET ((NTSTATUS)0xC01E0329L)
#endif//STATUS_GRAPHICS_ADAPTER_MUST_HAVE_AT_LEAST_ONE_TARGET

//
// MessageId: STATUS_GRAPHICS_INVALID_MONITORDESCRIPTORSET
//
// MessageText:
//
// Specified monitor descriptor set is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_MONITORDESCRIPTORSET
#define STATUS_GRAPHICS_INVALID_MONITORDESCRIPTORSET ((NTSTATUS)0xC01E032AL)
#endif//STATUS_GRAPHICS_INVALID_MONITORDESCRIPTORSET

//
// MessageId: STATUS_GRAPHICS_INVALID_MONITORDESCRIPTOR
//
// MessageText:
//
// Specified monitor descriptor is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_MONITORDESCRIPTOR
#define STATUS_GRAPHICS_INVALID_MONITORDESCRIPTOR ((NTSTATUS)0xC01E032BL)
#endif//STATUS_GRAPHICS_INVALID_MONITORDESCRIPTOR

//
// MessageId: STATUS_GRAPHICS_MONITORDESCRIPTOR_NOT_IN_SET
//
// MessageText:
//
// Specified descriptor is not in the specified monitor descriptor set.
//
#ifndef STATUS_GRAPHICS_MONITORDESCRIPTOR_NOT_IN_SET
#define STATUS_GRAPHICS_MONITORDESCRIPTOR_NOT_IN_SET ((NTSTATUS)0xC01E032CL)
#endif//STATUS_GRAPHICS_MONITORDESCRIPTOR_NOT_IN_SET

//
// MessageId: STATUS_GRAPHICS_MONITORDESCRIPTOR_ALREADY_IN_SET
//
// MessageText:
//
// Specified descriptor is already in the specified monitor descriptor set.
//
#ifndef STATUS_GRAPHICS_MONITORDESCRIPTOR_ALREADY_IN_SET
#define STATUS_GRAPHICS_MONITORDESCRIPTOR_ALREADY_IN_SET ((NTSTATUS)0xC01E032DL)
#endif//STATUS_GRAPHICS_MONITORDESCRIPTOR_ALREADY_IN_SET

//
// MessageId: STATUS_GRAPHICS_MONITORDESCRIPTOR_ID_MUST_BE_UNIQUE
//
// MessageText:
//
// ID of the specified monitor descriptor is already used by another descriptor in the set.
//
#ifndef STATUS_GRAPHICS_MONITORDESCRIPTOR_ID_MUST_BE_UNIQUE
#define STATUS_GRAPHICS_MONITORDESCRIPTOR_ID_MUST_BE_UNIQUE ((NTSTATUS)0xC01E032EL)
#endif//STATUS_GRAPHICS_MONITORDESCRIPTOR_ID_MUST_BE_UNIQUE

//
// MessageId: STATUS_GRAPHICS_INVALID_VIDPN_TARGET_SUBSET_TYPE
//
// MessageText:
//
// Specified video present target subset type is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_VIDPN_TARGET_SUBSET_TYPE
#define STATUS_GRAPHICS_INVALID_VIDPN_TARGET_SUBSET_TYPE ((NTSTATUS)0xC01E032FL)
#endif//STATUS_GRAPHICS_INVALID_VIDPN_TARGET_SUBSET_TYPE

//
// MessageId: STATUS_GRAPHICS_RESOURCES_NOT_RELATED
//
// MessageText:
//
// Two or more of the specified resources are not related to each other, as defined by the interface semantics.
//
#ifndef STATUS_GRAPHICS_RESOURCES_NOT_RELATED
#define STATUS_GRAPHICS_RESOURCES_NOT_RELATED ((NTSTATUS)0xC01E0330L)
#endif//STATUS_GRAPHICS_RESOURCES_NOT_RELATED

//
// MessageId: STATUS_GRAPHICS_SOURCE_ID_MUST_BE_UNIQUE
//
// MessageText:
//
// ID of the specified video present source is already used by another source in the set.
//
#ifndef STATUS_GRAPHICS_SOURCE_ID_MUST_BE_UNIQUE
#define STATUS_GRAPHICS_SOURCE_ID_MUST_BE_UNIQUE ((NTSTATUS)0xC01E0331L)
#endif//STATUS_GRAPHICS_SOURCE_ID_MUST_BE_UNIQUE

//
// MessageId: STATUS_GRAPHICS_TARGET_ID_MUST_BE_UNIQUE
//
// MessageText:
//
// ID of the specified video present target is already used by another target in the set.
//
#ifndef STATUS_GRAPHICS_TARGET_ID_MUST_BE_UNIQUE
#define STATUS_GRAPHICS_TARGET_ID_MUST_BE_UNIQUE ((NTSTATUS)0xC01E0332L)
#endif//STATUS_GRAPHICS_TARGET_ID_MUST_BE_UNIQUE

//
// MessageId: STATUS_GRAPHICS_NO_AVAILABLE_VIDPN_TARGET
//
// MessageText:
//
// Specified VidPN source cannot be used because there is no available VidPN target to connect it to.
//
#ifndef STATUS_GRAPHICS_NO_AVAILABLE_VIDPN_TARGET
#define STATUS_GRAPHICS_NO_AVAILABLE_VIDPN_TARGET ((NTSTATUS)0xC01E0333L)
#endif//STATUS_GRAPHICS_NO_AVAILABLE_VIDPN_TARGET

//
// MessageId: STATUS_GRAPHICS_MONITOR_COULD_NOT_BE_ASSOCIATED_WITH_ADAPTER
//
// MessageText:
//
// Newly arrived monitor could not be associated with a display adapter.
//
#ifndef STATUS_GRAPHICS_MONITOR_COULD_NOT_BE_ASSOCIATED_WITH_ADAPTER
#define STATUS_GRAPHICS_MONITOR_COULD_NOT_BE_ASSOCIATED_WITH_ADAPTER ((NTSTATUS)0xC01E0334L)
#endif//STATUS_GRAPHICS_MONITOR_COULD_NOT_BE_ASSOCIATED_WITH_ADAPTER

//
// MessageId: STATUS_GRAPHICS_NO_VIDPNMGR
//
// MessageText:
//
// Display adapter in question does not have an associated VidPN manager.
//
#ifndef STATUS_GRAPHICS_NO_VIDPNMGR
#define STATUS_GRAPHICS_NO_VIDPNMGR      ((NTSTATUS)0xC01E0335L)
#endif//STATUS_GRAPHICS_NO_VIDPNMGR

//
// MessageId: STATUS_GRAPHICS_NO_ACTIVE_VIDPN
//
// MessageText:
//
// VidPN manager of the display adapter in question does not have an active VidPN.
//
#ifndef STATUS_GRAPHICS_NO_ACTIVE_VIDPN
#define STATUS_GRAPHICS_NO_ACTIVE_VIDPN  ((NTSTATUS)0xC01E0336L)
#endif//STATUS_GRAPHICS_NO_ACTIVE_VIDPN

//
// MessageId: STATUS_GRAPHICS_STALE_VIDPN_TOPOLOGY
//
// MessageText:
//
// Specified VidPN topology is stale. Please reacquire the new topology.
//
#ifndef STATUS_GRAPHICS_STALE_VIDPN_TOPOLOGY
#define STATUS_GRAPHICS_STALE_VIDPN_TOPOLOGY ((NTSTATUS)0xC01E0337L)
#endif//STATUS_GRAPHICS_STALE_VIDPN_TOPOLOGY

//
// MessageId: STATUS_GRAPHICS_MONITOR_NOT_CONNECTED
//
// MessageText:
//
// There is no monitor connected on the specified video present target.
//
#ifndef STATUS_GRAPHICS_MONITOR_NOT_CONNECTED
#define STATUS_GRAPHICS_MONITOR_NOT_CONNECTED ((NTSTATUS)0xC01E0338L)
#endif//STATUS_GRAPHICS_MONITOR_NOT_CONNECTED

//
// MessageId: STATUS_GRAPHICS_SOURCE_NOT_IN_TOPOLOGY
//
// MessageText:
//
// Specified source is not part of the specified VidPN's topology.
//
#ifndef STATUS_GRAPHICS_SOURCE_NOT_IN_TOPOLOGY
#define STATUS_GRAPHICS_SOURCE_NOT_IN_TOPOLOGY ((NTSTATUS)0xC01E0339L)
#endif//STATUS_GRAPHICS_SOURCE_NOT_IN_TOPOLOGY

//
// MessageId: STATUS_GRAPHICS_INVALID_PRIMARYSURFACE_SIZE
//
// MessageText:
//
// Specified primary surface size is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_PRIMARYSURFACE_SIZE
#define STATUS_GRAPHICS_INVALID_PRIMARYSURFACE_SIZE ((NTSTATUS)0xC01E033AL)
#endif//STATUS_GRAPHICS_INVALID_PRIMARYSURFACE_SIZE

//
// MessageId: STATUS_GRAPHICS_INVALID_VISIBLEREGION_SIZE
//
// MessageText:
//
// Specified visible region size is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_VISIBLEREGION_SIZE
#define STATUS_GRAPHICS_INVALID_VISIBLEREGION_SIZE ((NTSTATUS)0xC01E033BL)
#endif//STATUS_GRAPHICS_INVALID_VISIBLEREGION_SIZE

//
// MessageId: STATUS_GRAPHICS_INVALID_STRIDE
//
// MessageText:
//
// Specified stride is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_STRIDE
#define STATUS_GRAPHICS_INVALID_STRIDE   ((NTSTATUS)0xC01E033CL)
#endif//STATUS_GRAPHICS_INVALID_STRIDE

//
// MessageId: STATUS_GRAPHICS_INVALID_PIXELFORMAT
//
// MessageText:
//
// Specified pixel format is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_PIXELFORMAT
#define STATUS_GRAPHICS_INVALID_PIXELFORMAT ((NTSTATUS)0xC01E033DL)
#endif//STATUS_GRAPHICS_INVALID_PIXELFORMAT

//
// MessageId: STATUS_GRAPHICS_INVALID_COLORBASIS
//
// MessageText:
//
// Specified color basis is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_COLORBASIS
#define STATUS_GRAPHICS_INVALID_COLORBASIS ((NTSTATUS)0xC01E033EL)
#endif//STATUS_GRAPHICS_INVALID_COLORBASIS

//
// MessageId: STATUS_GRAPHICS_INVALID_PIXELVALUEACCESSMODE
//
// MessageText:
//
// Specified pixel value access mode is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_PIXELVALUEACCESSMODE
#define STATUS_GRAPHICS_INVALID_PIXELVALUEACCESSMODE ((NTSTATUS)0xC01E033FL)
#endif//STATUS_GRAPHICS_INVALID_PIXELVALUEACCESSMODE

//
// MessageId: STATUS_GRAPHICS_TARGET_NOT_IN_TOPOLOGY
//
// MessageText:
//
// Specified target is not part of the specified VidPN's topology.
//
#ifndef STATUS_GRAPHICS_TARGET_NOT_IN_TOPOLOGY
#define STATUS_GRAPHICS_TARGET_NOT_IN_TOPOLOGY ((NTSTATUS)0xC01E0340L)
#endif//STATUS_GRAPHICS_TARGET_NOT_IN_TOPOLOGY

//
// MessageId: STATUS_GRAPHICS_NO_DISPLAY_MODE_MANAGEMENT_SUPPORT
//
// MessageText:
//
// Failed to acquire display mode management interface.
//
#ifndef STATUS_GRAPHICS_NO_DISPLAY_MODE_MANAGEMENT_SUPPORT
#define STATUS_GRAPHICS_NO_DISPLAY_MODE_MANAGEMENT_SUPPORT ((NTSTATUS)0xC01E0341L)
#endif//STATUS_GRAPHICS_NO_DISPLAY_MODE_MANAGEMENT_SUPPORT

//
// MessageId: STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE
//
// MessageText:
//
// Specified VidPN source is already owned by a DMM client and cannot be used until that client releases it.
//
#ifndef STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE
#define STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE ((NTSTATUS)0xC01E0342L)
#endif//STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE

//
// MessageId: STATUS_GRAPHICS_CANT_ACCESS_ACTIVE_VIDPN
//
// MessageText:
//
// Specified VidPN is active and cannot be accessed.
//
#ifndef STATUS_GRAPHICS_CANT_ACCESS_ACTIVE_VIDPN
#define STATUS_GRAPHICS_CANT_ACCESS_ACTIVE_VIDPN ((NTSTATUS)0xC01E0343L)
#endif//STATUS_GRAPHICS_CANT_ACCESS_ACTIVE_VIDPN

//
// MessageId: STATUS_GRAPHICS_INVALID_PATH_IMPORTANCE_ORDINAL
//
// MessageText:
//
// Specified VidPN present path importance ordinal is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_PATH_IMPORTANCE_ORDINAL
#define STATUS_GRAPHICS_INVALID_PATH_IMPORTANCE_ORDINAL ((NTSTATUS)0xC01E0344L)
#endif//STATUS_GRAPHICS_INVALID_PATH_IMPORTANCE_ORDINAL

//
// MessageId: STATUS_GRAPHICS_INVALID_PATH_CONTENT_GEOMETRY_TRANSFORMATION
//
// MessageText:
//
// Specified VidPN present path content geometry transformation is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_PATH_CONTENT_GEOMETRY_TRANSFORMATION
#define STATUS_GRAPHICS_INVALID_PATH_CONTENT_GEOMETRY_TRANSFORMATION ((NTSTATUS)0xC01E0345L)
#endif//STATUS_GRAPHICS_INVALID_PATH_CONTENT_GEOMETRY_TRANSFORMATION

//
// MessageId: STATUS_GRAPHICS_PATH_CONTENT_GEOMETRY_TRANSFORMATION_NOT_SUPPORTED
//
// MessageText:
//
// Specified content geometry transformation is not supported on the respective VidPN present path.
//
#ifndef STATUS_GRAPHICS_PATH_CONTENT_GEOMETRY_TRANSFORMATION_NOT_SUPPORTED
#define STATUS_GRAPHICS_PATH_CONTENT_GEOMETRY_TRANSFORMATION_NOT_SUPPORTED ((NTSTATUS)0xC01E0346L)
#endif//STATUS_GRAPHICS_PATH_CONTENT_GEOMETRY_TRANSFORMATION_NOT_SUPPORTED

//
// MessageId: STATUS_GRAPHICS_INVALID_GAMMA_RAMP
//
// MessageText:
//
// Specified gamma ramp is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_GAMMA_RAMP
#define STATUS_GRAPHICS_INVALID_GAMMA_RAMP ((NTSTATUS)0xC01E0347L)
#endif//STATUS_GRAPHICS_INVALID_GAMMA_RAMP

//
// MessageId: STATUS_GRAPHICS_GAMMA_RAMP_NOT_SUPPORTED
//
// MessageText:
//
// Specified gamma ramp is not supported on the respective VidPN present path.
//
#ifndef STATUS_GRAPHICS_GAMMA_RAMP_NOT_SUPPORTED
#define STATUS_GRAPHICS_GAMMA_RAMP_NOT_SUPPORTED ((NTSTATUS)0xC01E0348L)
#endif//STATUS_GRAPHICS_GAMMA_RAMP_NOT_SUPPORTED

//
// MessageId: STATUS_GRAPHICS_MULTISAMPLING_NOT_SUPPORTED
//
// MessageText:
//
// Multi-sampling is not supported on the respective VidPN present path.
//
#ifndef STATUS_GRAPHICS_MULTISAMPLING_NOT_SUPPORTED
#define STATUS_GRAPHICS_MULTISAMPLING_NOT_SUPPORTED ((NTSTATUS)0xC01E0349L)
#endif//STATUS_GRAPHICS_MULTISAMPLING_NOT_SUPPORTED

//
// MessageId: STATUS_GRAPHICS_MODE_NOT_IN_MODESET
//
// MessageText:
//
// Specified mode is not in the specified mode set.
//
#ifndef STATUS_GRAPHICS_MODE_NOT_IN_MODESET
#define STATUS_GRAPHICS_MODE_NOT_IN_MODESET ((NTSTATUS)0xC01E034AL)
#endif//STATUS_GRAPHICS_MODE_NOT_IN_MODESET

//
// MessageId: STATUS_GRAPHICS_DATASET_IS_EMPTY
//
// MessageText:
//
// Specified data set (e.g. mode set, frequency range set, descriptor set, topology, etc.) is empty.
//
#ifndef STATUS_GRAPHICS_DATASET_IS_EMPTY
#define STATUS_GRAPHICS_DATASET_IS_EMPTY ((NTSTATUS)0x401E034BL)
#endif//STATUS_GRAPHICS_DATASET_IS_EMPTY

//
// MessageId: STATUS_GRAPHICS_NO_MORE_ELEMENTS_IN_DATASET
//
// MessageText:
//
// Specified data set (e.g. mode set, frequency range set, descriptor set, topology, etc.) does not contain any more elements.
//
#ifndef STATUS_GRAPHICS_NO_MORE_ELEMENTS_IN_DATASET
#define STATUS_GRAPHICS_NO_MORE_ELEMENTS_IN_DATASET ((NTSTATUS)0x401E034CL)
#endif//STATUS_GRAPHICS_NO_MORE_ELEMENTS_IN_DATASET

//
// MessageId: STATUS_GRAPHICS_INVALID_VIDPN_TOPOLOGY_RECOMMENDATION_REASON
//
// MessageText:
//
// Specified VidPN topology recommendation reason is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_VIDPN_TOPOLOGY_RECOMMENDATION_REASON
#define STATUS_GRAPHICS_INVALID_VIDPN_TOPOLOGY_RECOMMENDATION_REASON ((NTSTATUS)0xC01E034DL)
#endif//STATUS_GRAPHICS_INVALID_VIDPN_TOPOLOGY_RECOMMENDATION_REASON

//
// MessageId: STATUS_GRAPHICS_INVALID_PATH_CONTENT_TYPE
//
// MessageText:
//
// Specified VidPN present path content type is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_PATH_CONTENT_TYPE
#define STATUS_GRAPHICS_INVALID_PATH_CONTENT_TYPE ((NTSTATUS)0xC01E034EL)
#endif//STATUS_GRAPHICS_INVALID_PATH_CONTENT_TYPE

//
// MessageId: STATUS_GRAPHICS_INVALID_COPYPROTECTION_TYPE
//
// MessageText:
//
// Specified VidPN present path copy protection type is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_COPYPROTECTION_TYPE
#define STATUS_GRAPHICS_INVALID_COPYPROTECTION_TYPE ((NTSTATUS)0xC01E034FL)
#endif//STATUS_GRAPHICS_INVALID_COPYPROTECTION_TYPE

//
// MessageId: STATUS_GRAPHICS_UNASSIGNED_MODESET_ALREADY_EXISTS
//
// MessageText:
//
// No more than one unassigned mode set can exist at any given time for a given VidPN source/target.
//
#ifndef STATUS_GRAPHICS_UNASSIGNED_MODESET_ALREADY_EXISTS
#define STATUS_GRAPHICS_UNASSIGNED_MODESET_ALREADY_EXISTS ((NTSTATUS)0xC01E0350L)
#endif//STATUS_GRAPHICS_UNASSIGNED_MODESET_ALREADY_EXISTS

//
// MessageId: STATUS_GRAPHICS_PATH_CONTENT_GEOMETRY_TRANSFORMATION_NOT_PINNED
//
// MessageText:
//
// Specified content transformation is not pinned on the specified VidPN present path.
//
#ifndef STATUS_GRAPHICS_PATH_CONTENT_GEOMETRY_TRANSFORMATION_NOT_PINNED
#define STATUS_GRAPHICS_PATH_CONTENT_GEOMETRY_TRANSFORMATION_NOT_PINNED ((NTSTATUS)0x401E0351L)
#endif//STATUS_GRAPHICS_PATH_CONTENT_GEOMETRY_TRANSFORMATION_NOT_PINNED

//
// MessageId: STATUS_GRAPHICS_INVALID_SCANLINE_ORDERING
//
// MessageText:
//
// Specified scanline ordering type is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_SCANLINE_ORDERING
#define STATUS_GRAPHICS_INVALID_SCANLINE_ORDERING ((NTSTATUS)0xC01E0352L)
#endif//STATUS_GRAPHICS_INVALID_SCANLINE_ORDERING

//
// MessageId: STATUS_GRAPHICS_TOPOLOGY_CHANGES_NOT_ALLOWED
//
// MessageText:
//
// Topology changes are not allowed for the specified VidPN.
//
#ifndef STATUS_GRAPHICS_TOPOLOGY_CHANGES_NOT_ALLOWED
#define STATUS_GRAPHICS_TOPOLOGY_CHANGES_NOT_ALLOWED ((NTSTATUS)0xC01E0353L)
#endif//STATUS_GRAPHICS_TOPOLOGY_CHANGES_NOT_ALLOWED

//
// MessageId: STATUS_GRAPHICS_NO_AVAILABLE_IMPORTANCE_ORDINALS
//
// MessageText:
//
// All available importance ordinals are already used in specified topology.
//
#ifndef STATUS_GRAPHICS_NO_AVAILABLE_IMPORTANCE_ORDINALS
#define STATUS_GRAPHICS_NO_AVAILABLE_IMPORTANCE_ORDINALS ((NTSTATUS)0xC01E0354L)
#endif//STATUS_GRAPHICS_NO_AVAILABLE_IMPORTANCE_ORDINALS

//
// MessageId: STATUS_GRAPHICS_INCOMPATIBLE_PRIVATE_FORMAT
//
// MessageText:
//
// Specified primary surface has a different private format attribute than the current primary surface
//
#ifndef STATUS_GRAPHICS_INCOMPATIBLE_PRIVATE_FORMAT
#define STATUS_GRAPHICS_INCOMPATIBLE_PRIVATE_FORMAT ((NTSTATUS)0xC01E0355L)
#endif//STATUS_GRAPHICS_INCOMPATIBLE_PRIVATE_FORMAT

//
// MessageId: STATUS_GRAPHICS_INVALID_MODE_PRUNING_ALGORITHM
//
// MessageText:
//
// Specified mode pruning algorithm is invalid
//
#ifndef STATUS_GRAPHICS_INVALID_MODE_PRUNING_ALGORITHM
#define STATUS_GRAPHICS_INVALID_MODE_PRUNING_ALGORITHM ((NTSTATUS)0xC01E0356L)
#endif//STATUS_GRAPHICS_INVALID_MODE_PRUNING_ALGORITHM

//
// MessageId: STATUS_GRAPHICS_INVALID_MONITOR_CAPABILITY_ORIGIN
//
// MessageText:
//
// Specified monitor capability origin is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_MONITOR_CAPABILITY_ORIGIN
#define STATUS_GRAPHICS_INVALID_MONITOR_CAPABILITY_ORIGIN ((NTSTATUS)0xC01E0357L)
#endif//STATUS_GRAPHICS_INVALID_MONITOR_CAPABILITY_ORIGIN

//
// MessageId: STATUS_GRAPHICS_INVALID_MONITOR_FREQUENCYRANGE_CONSTRAINT
//
// MessageText:
//
// Specified monitor frequency range constraint is invalid.
//
#ifndef STATUS_GRAPHICS_INVALID_MONITOR_FREQUENCYRANGE_CONSTRAINT
#define STATUS_GRAPHICS_INVALID_MONITOR_FREQUENCYRANGE_CONSTRAINT ((NTSTATUS)0xC01E0358L)
#endif//STATUS_GRAPHICS_INVALID_MONITOR_FREQUENCYRANGE_CONSTRAINT

//
// MessageId: STATUS_GRAPHICS_MAX_NUM_PATHS_REACHED
//
// MessageText:
//
// Maximum supported number of present paths has been reached.
//
#ifndef STATUS_GRAPHICS_MAX_NUM_PATHS_REACHED
#define STATUS_GRAPHICS_MAX_NUM_PATHS_REACHED ((NTSTATUS)0xC01E0359L)
#endif//STATUS_GRAPHICS_MAX_NUM_PATHS_REACHED

//
// MessageId: STATUS_GRAPHICS_CANCEL_VIDPN_TOPOLOGY_AUGMENTATION
//
// MessageText:
//
// Miniport requested that augmentation be cancelled for the specified source of the specified VidPN's topology.
//
#ifndef STATUS_GRAPHICS_CANCEL_VIDPN_TOPOLOGY_AUGMENTATION
#define STATUS_GRAPHICS_CANCEL_VIDPN_TOPOLOGY_AUGMENTATION ((NTSTATUS)0xC01E035AL)
#endif//STATUS_GRAPHICS_CANCEL_VIDPN_TOPOLOGY_AUGMENTATION

//
// MessageId: STATUS_GRAPHICS_INVALID_CLIENT_TYPE
//
// MessageText:
//
// Specified client type was not recognized.
//
#ifndef STATUS_GRAPHICS_INVALID_CLIENT_TYPE
#define STATUS_GRAPHICS_INVALID_CLIENT_TYPE ((NTSTATUS)0xC01E035BL)
#endif//STATUS_GRAPHICS_INVALID_CLIENT_TYPE

//
// MessageId: STATUS_GRAPHICS_CLIENTVIDPN_NOT_SET
//
// MessageText:
//
// Client VidPN is not set on this adapter (e.g. no user mode initiated mode changes took place on this adapter yet).
//
#ifndef STATUS_GRAPHICS_CLIENTVIDPN_NOT_SET
#define STATUS_GRAPHICS_CLIENTVIDPN_NOT_SET ((NTSTATUS)0xC01E035CL)
#endif//STATUS_GRAPHICS_CLIENTVIDPN_NOT_SET

//
//   Port specific status codes {0x0400..0x04ff}
//
//
// MessageId: STATUS_GRAPHICS_SPECIFIED_CHILD_ALREADY_CONNECTED
//
// MessageText:
//
// Specified display adapter child device already has an external device connected to it.
//
#ifndef STATUS_GRAPHICS_SPECIFIED_CHILD_ALREADY_CONNECTED
#define STATUS_GRAPHICS_SPECIFIED_CHILD_ALREADY_CONNECTED ((NTSTATUS)0xC01E0400L)
#endif//STATUS_GRAPHICS_SPECIFIED_CHILD_ALREADY_CONNECTED

//
// MessageId: STATUS_GRAPHICS_CHILD_DESCRIPTOR_NOT_SUPPORTED
//
// MessageText:
//
// Specified display adapter child device does not support descriptor exposure.
//
#ifndef STATUS_GRAPHICS_CHILD_DESCRIPTOR_NOT_SUPPORTED
#define STATUS_GRAPHICS_CHILD_DESCRIPTOR_NOT_SUPPORTED ((NTSTATUS)0xC01E0401L)
#endif//STATUS_GRAPHICS_CHILD_DESCRIPTOR_NOT_SUPPORTED

//
// MessageId: STATUS_GRAPHICS_UNKNOWN_CHILD_STATUS
//
// MessageText:
//
// Child device presence was not reliably detected.
//
#ifndef STATUS_GRAPHICS_UNKNOWN_CHILD_STATUS
#define STATUS_GRAPHICS_UNKNOWN_CHILD_STATUS ((NTSTATUS)0x401E042FL)
#endif//STATUS_GRAPHICS_UNKNOWN_CHILD_STATUS

//
// MessageId: STATUS_GRAPHICS_NOT_A_LINKED_ADAPTER
//
// MessageText:
//
// The display adapter is not linked to any other adapters.
//
#ifndef STATUS_GRAPHICS_NOT_A_LINKED_ADAPTER
#define STATUS_GRAPHICS_NOT_A_LINKED_ADAPTER ((NTSTATUS)0xC01E0430L)
#endif//STATUS_GRAPHICS_NOT_A_LINKED_ADAPTER

//
// MessageId: STATUS_GRAPHICS_LEADLINK_NOT_ENUMERATED
//
// MessageText:
//
// Lead adapter in a linked configuration was not enumerated yet.
//
#ifndef STATUS_GRAPHICS_LEADLINK_NOT_ENUMERATED
#define STATUS_GRAPHICS_LEADLINK_NOT_ENUMERATED ((NTSTATUS)0xC01E0431L)
#endif//STATUS_GRAPHICS_LEADLINK_NOT_ENUMERATED

//
// MessageId: STATUS_GRAPHICS_CHAINLINKS_NOT_ENUMERATED
//
// MessageText:
//
// Some chain adapters in a linked configuration were not enumerated yet.
//
#ifndef STATUS_GRAPHICS_CHAINLINKS_NOT_ENUMERATED
#define STATUS_GRAPHICS_CHAINLINKS_NOT_ENUMERATED ((NTSTATUS)0xC01E0432L)
#endif//STATUS_GRAPHICS_CHAINLINKS_NOT_ENUMERATED

//
// MessageId: STATUS_GRAPHICS_ADAPTER_CHAIN_NOT_READY
//
// MessageText:
//
// The chain of linked adapters is not ready to start because of an unknown failure.
//
#ifndef STATUS_GRAPHICS_ADAPTER_CHAIN_NOT_READY
#define STATUS_GRAPHICS_ADAPTER_CHAIN_NOT_READY ((NTSTATUS)0xC01E0433L)
#endif//STATUS_GRAPHICS_ADAPTER_CHAIN_NOT_READY

//
// MessageId: STATUS_GRAPHICS_CHAINLINKS_NOT_STARTED
//
// MessageText:
//
// An attempt was made to start a lead link display adapter when the chain links were not started yet.
//
#ifndef STATUS_GRAPHICS_CHAINLINKS_NOT_STARTED
#define STATUS_GRAPHICS_CHAINLINKS_NOT_STARTED ((NTSTATUS)0xC01E0434L)
#endif//STATUS_GRAPHICS_CHAINLINKS_NOT_STARTED

//
// MessageId: STATUS_GRAPHICS_CHAINLINKS_NOT_POWERED_ON
//
// MessageText:
//
// An attempt was made to power up a lead link display adapter when the chain links were powered down.
//
#ifndef STATUS_GRAPHICS_CHAINLINKS_NOT_POWERED_ON
#define STATUS_GRAPHICS_CHAINLINKS_NOT_POWERED_ON ((NTSTATUS)0xC01E0435L)
#endif//STATUS_GRAPHICS_CHAINLINKS_NOT_POWERED_ON

//
// MessageId: STATUS_GRAPHICS_INCONSISTENT_DEVICE_LINK_STATE
//
// MessageText:
//
// The adapter link was found to be in an inconsistent state. Not all adapters are in an expected PNP/Power state.
//
#ifndef STATUS_GRAPHICS_INCONSISTENT_DEVICE_LINK_STATE
#define STATUS_GRAPHICS_INCONSISTENT_DEVICE_LINK_STATE ((NTSTATUS)0xC01E0436L)
#endif//STATUS_GRAPHICS_INCONSISTENT_DEVICE_LINK_STATE

//
// MessageId: STATUS_GRAPHICS_LEADLINK_START_DEFERRED
//
// MessageText:
//
// Starting the leadlink adapter has been deferred temporarily.
//
#ifndef STATUS_GRAPHICS_LEADLINK_START_DEFERRED
#define STATUS_GRAPHICS_LEADLINK_START_DEFERRED ((NTSTATUS)0x401E0437L)
#endif//STATUS_GRAPHICS_LEADLINK_START_DEFERRED

//
// MessageId: STATUS_GRAPHICS_NOT_POST_DEVICE_DRIVER
//
// MessageText:
//
// The driver trying to start is not the same as the driver for the POSTed display adapter.
//
#ifndef STATUS_GRAPHICS_NOT_POST_DEVICE_DRIVER
#define STATUS_GRAPHICS_NOT_POST_DEVICE_DRIVER ((NTSTATUS)0xC01E0438L)
#endif//STATUS_GRAPHICS_NOT_POST_DEVICE_DRIVER

//
// MessageId: STATUS_GRAPHICS_POLLING_TOO_FREQUENTLY
//
// MessageText:
//
// The display adapter is being polled for children too frequently at the same polling level.
//
#ifndef STATUS_GRAPHICS_POLLING_TOO_FREQUENTLY
#define STATUS_GRAPHICS_POLLING_TOO_FREQUENTLY ((NTSTATUS)0x401E0439L)
#endif//STATUS_GRAPHICS_POLLING_TOO_FREQUENTLY

//
// MessageId: STATUS_GRAPHICS_START_DEFERRED
//
// MessageText:
//
// Starting the adapter has been deferred temporarily.
//
#ifndef STATUS_GRAPHICS_START_DEFERRED
#define STATUS_GRAPHICS_START_DEFERRED   ((NTSTATUS)0x401E043AL)
#endif//STATUS_GRAPHICS_START_DEFERRED

//
// MessageId: STATUS_GRAPHICS_ADAPTER_ACCESS_NOT_EXCLUDED
//
// MessageText:
//
// An operation is being attempted that requires the display adapter to be in a quiescent state.
//
#ifndef STATUS_GRAPHICS_ADAPTER_ACCESS_NOT_EXCLUDED
#define STATUS_GRAPHICS_ADAPTER_ACCESS_NOT_EXCLUDED ((NTSTATUS)0xC01E043BL)
#endif//STATUS_GRAPHICS_ADAPTER_ACCESS_NOT_EXCLUDED

//
// MessageId: STATUS_GRAPHICS_DEPENDABLE_CHILD_STATUS
//
// MessageText:
//
// We can depend on the child device presence returned by the driver.
//
#ifndef STATUS_GRAPHICS_DEPENDABLE_CHILD_STATUS
#define STATUS_GRAPHICS_DEPENDABLE_CHILD_STATUS ((NTSTATUS)0x401E043CL)
#endif//STATUS_GRAPHICS_DEPENDABLE_CHILD_STATUS

//
//   OPM, PVP and UAB status codes {0x0500..0x057F}
//
//
// MessageId: STATUS_GRAPHICS_OPM_NOT_SUPPORTED
//
// MessageText:
//
// The driver does not support OPM.
//
#ifndef STATUS_GRAPHICS_OPM_NOT_SUPPORTED
#define STATUS_GRAPHICS_OPM_NOT_SUPPORTED ((NTSTATUS)0xC01E0500L)
#endif//STATUS_GRAPHICS_OPM_NOT_SUPPORTED

//
// MessageId: STATUS_GRAPHICS_COPP_NOT_SUPPORTED
//
// MessageText:
//
// The driver does not support COPP.
//
#ifndef STATUS_GRAPHICS_COPP_NOT_SUPPORTED
#define STATUS_GRAPHICS_COPP_NOT_SUPPORTED ((NTSTATUS)0xC01E0501L)
#endif//STATUS_GRAPHICS_COPP_NOT_SUPPORTED

//
// MessageId: STATUS_GRAPHICS_UAB_NOT_SUPPORTED
//
// MessageText:
//
// The driver does not support UAB.
//
#ifndef STATUS_GRAPHICS_UAB_NOT_SUPPORTED
#define STATUS_GRAPHICS_UAB_NOT_SUPPORTED ((NTSTATUS)0xC01E0502L)
#endif//STATUS_GRAPHICS_UAB_NOT_SUPPORTED

//
// MessageId: STATUS_GRAPHICS_OPM_INVALID_ENCRYPTED_PARAMETERS
//
// MessageText:
//
// The specified encrypted parameters are invalid.
//
#ifndef STATUS_GRAPHICS_OPM_INVALID_ENCRYPTED_PARAMETERS
#define STATUS_GRAPHICS_OPM_INVALID_ENCRYPTED_PARAMETERS ((NTSTATUS)0xC01E0503L)
#endif//STATUS_GRAPHICS_OPM_INVALID_ENCRYPTED_PARAMETERS

//
// MessageId: STATUS_GRAPHICS_OPM_NO_PROTECTED_OUTPUTS_EXIST
//
// MessageText:
//
// The GDI display device passed to this function does not have any active protected outputs.
//
#ifndef STATUS_GRAPHICS_OPM_NO_PROTECTED_OUTPUTS_EXIST
#define STATUS_GRAPHICS_OPM_NO_PROTECTED_OUTPUTS_EXIST ((NTSTATUS)0xC01E0505L)
#endif//STATUS_GRAPHICS_OPM_NO_PROTECTED_OUTPUTS_EXIST

//
// MessageId: STATUS_GRAPHICS_OPM_INTERNAL_ERROR
//
// MessageText:
//
// An internal error caused an operation to fail.
//
#ifndef STATUS_GRAPHICS_OPM_INTERNAL_ERROR
#define STATUS_GRAPHICS_OPM_INTERNAL_ERROR ((NTSTATUS)0xC01E050BL)
#endif//STATUS_GRAPHICS_OPM_INTERNAL_ERROR

//
// MessageId: STATUS_GRAPHICS_OPM_INVALID_HANDLE
//
// MessageText:
//
// The function failed because the caller passed in an invalid OPM user mode handle.
//
#ifndef STATUS_GRAPHICS_OPM_INVALID_HANDLE
#define STATUS_GRAPHICS_OPM_INVALID_HANDLE ((NTSTATUS)0xC01E050CL)
#endif//STATUS_GRAPHICS_OPM_INVALID_HANDLE

//
// MessageId: STATUS_GRAPHICS_PVP_INVALID_CERTIFICATE_LENGTH
//
// MessageText:
//
// A certificate could not be returned because the certificate buffer passed to the function was too small.
//
#ifndef STATUS_GRAPHICS_PVP_INVALID_CERTIFICATE_LENGTH
#define STATUS_GRAPHICS_PVP_INVALID_CERTIFICATE_LENGTH ((NTSTATUS)0xC01E050EL)
#endif//STATUS_GRAPHICS_PVP_INVALID_CERTIFICATE_LENGTH

//
// MessageId: STATUS_GRAPHICS_OPM_SPANNING_MODE_ENABLED
//
// MessageText:
//
// The DxgkDdiOpmCreateProtectedOutput function could not create a protected output because the Video Present Target is in spanning mode.
//
#ifndef STATUS_GRAPHICS_OPM_SPANNING_MODE_ENABLED
#define STATUS_GRAPHICS_OPM_SPANNING_MODE_ENABLED ((NTSTATUS)0xC01E050FL)
#endif//STATUS_GRAPHICS_OPM_SPANNING_MODE_ENABLED

//
// MessageId: STATUS_GRAPHICS_OPM_THEATER_MODE_ENABLED
//
// MessageText:
//
// The DxgkDdiOpmCreateProtectedOutput function could not create a protected output because the Video Present Target is in theater mode.
//
#ifndef STATUS_GRAPHICS_OPM_THEATER_MODE_ENABLED
#define STATUS_GRAPHICS_OPM_THEATER_MODE_ENABLED ((NTSTATUS)0xC01E0510L)
#endif//STATUS_GRAPHICS_OPM_THEATER_MODE_ENABLED

//
// MessageId: STATUS_GRAPHICS_PVP_HFS_FAILED
//
// MessageText:
//
// The function failed because the display adapter's Hardware Functionality Scan failed to validate the graphics hardware.
//
#ifndef STATUS_GRAPHICS_PVP_HFS_FAILED
#define STATUS_GRAPHICS_PVP_HFS_FAILED   ((NTSTATUS)0xC01E0511L)
#endif//STATUS_GRAPHICS_PVP_HFS_FAILED

//
// MessageId: STATUS_GRAPHICS_OPM_INVALID_SRM
//
// MessageText:
//
// The HDCP System Renewability Message passed to this function did not comply with section 5 of the HDCP 1.1 specification.
//
#ifndef STATUS_GRAPHICS_OPM_INVALID_SRM
#define STATUS_GRAPHICS_OPM_INVALID_SRM  ((NTSTATUS)0xC01E0512L)
#endif//STATUS_GRAPHICS_OPM_INVALID_SRM

//
// MessageId: STATUS_GRAPHICS_OPM_OUTPUT_DOES_NOT_SUPPORT_HDCP
//
// MessageText:
//
// The protected output cannot enable the High-bandwidth Digital Content Protection (HDCP) System because it does not support HDCP.
//
#ifndef STATUS_GRAPHICS_OPM_OUTPUT_DOES_NOT_SUPPORT_HDCP
#define STATUS_GRAPHICS_OPM_OUTPUT_DOES_NOT_SUPPORT_HDCP ((NTSTATUS)0xC01E0513L)
#endif//STATUS_GRAPHICS_OPM_OUTPUT_DOES_NOT_SUPPORT_HDCP

//
// MessageId: STATUS_GRAPHICS_OPM_OUTPUT_DOES_NOT_SUPPORT_ACP
//
// MessageText:
//
// The protected output cannot enable Analogue Copy Protection (ACP) because it does not support ACP.
//
#ifndef STATUS_GRAPHICS_OPM_OUTPUT_DOES_NOT_SUPPORT_ACP
#define STATUS_GRAPHICS_OPM_OUTPUT_DOES_NOT_SUPPORT_ACP ((NTSTATUS)0xC01E0514L)
#endif//STATUS_GRAPHICS_OPM_OUTPUT_DOES_NOT_SUPPORT_ACP

//
// MessageId: STATUS_GRAPHICS_OPM_OUTPUT_DOES_NOT_SUPPORT_CGMSA
//
// MessageText:
//
// The protected output cannot enable the Content Generation Management System Analogue (CGMS-A) protection technology because it does not support CGMS-A.
//
#ifndef STATUS_GRAPHICS_OPM_OUTPUT_DOES_NOT_SUPPORT_CGMSA
#define STATUS_GRAPHICS_OPM_OUTPUT_DOES_NOT_SUPPORT_CGMSA ((NTSTATUS)0xC01E0515L)
#endif//STATUS_GRAPHICS_OPM_OUTPUT_DOES_NOT_SUPPORT_CGMSA

//
// MessageId: STATUS_GRAPHICS_OPM_HDCP_SRM_NEVER_SET
//
// MessageText:
//
// The DxgkDdiOPMGetInformation function cannot return the version of the SRM being used because the application never successfully passed an SRM to the protected output.
//
#ifndef STATUS_GRAPHICS_OPM_HDCP_SRM_NEVER_SET
#define STATUS_GRAPHICS_OPM_HDCP_SRM_NEVER_SET ((NTSTATUS)0xC01E0516L)
#endif//STATUS_GRAPHICS_OPM_HDCP_SRM_NEVER_SET

//
// MessageId: STATUS_GRAPHICS_OPM_RESOLUTION_TOO_HIGH
//
// MessageText:
//
// The DxgkDdiOPMConfigureProtectedOutput function cannot enable the specified output protection technology because the output's screen resolution is too high.
//
#ifndef STATUS_GRAPHICS_OPM_RESOLUTION_TOO_HIGH
#define STATUS_GRAPHICS_OPM_RESOLUTION_TOO_HIGH ((NTSTATUS)0xC01E0517L)
#endif//STATUS_GRAPHICS_OPM_RESOLUTION_TOO_HIGH

//
// MessageId: STATUS_GRAPHICS_OPM_ALL_HDCP_HARDWARE_ALREADY_IN_USE
//
// MessageText:
//
// The DxgkDdiOPMConfigureProtectedOutput function cannot enable HDCP because the display adapter's HDCP hardware is already being used by other physical outputs.
//
#ifndef STATUS_GRAPHICS_OPM_ALL_HDCP_HARDWARE_ALREADY_IN_USE
#define STATUS_GRAPHICS_OPM_ALL_HDCP_HARDWARE_ALREADY_IN_USE ((NTSTATUS)0xC01E0518L)
#endif//STATUS_GRAPHICS_OPM_ALL_HDCP_HARDWARE_ALREADY_IN_USE

//
// MessageId: STATUS_GRAPHICS_OPM_PROTECTED_OUTPUT_NO_LONGER_EXISTS
//
// MessageText:
//
// The operating system asynchronously destroyed this OPM protected output because the operating system's state changed. This error typically occurs because the monitor PDO associated with this protected output was removed, the monitor PDO associated with this protected output was stopped, or the protected output's session became a non-console session.
//
#ifndef STATUS_GRAPHICS_OPM_PROTECTED_OUTPUT_NO_LONGER_EXISTS
#define STATUS_GRAPHICS_OPM_PROTECTED_OUTPUT_NO_LONGER_EXISTS ((NTSTATUS)0xC01E051AL)
#endif//STATUS_GRAPHICS_OPM_PROTECTED_OUTPUT_NO_LONGER_EXISTS

//
// MessageId: STATUS_GRAPHICS_OPM_PROTECTED_OUTPUT_DOES_NOT_HAVE_COPP_SEMANTICS
//
// MessageText:
//
// Either the DxgkDdiOPMGetCOPPCompatibleInformation, DxgkDdiOPMGetInformation, or DxgkDdiOPMConfigureProtectedOutput function failed. This error is returned when the caller tries to use a COPP specific command while the protected output has OPM semantics only.
//
#ifndef STATUS_GRAPHICS_OPM_PROTECTED_OUTPUT_DOES_NOT_HAVE_COPP_SEMANTICS
#define STATUS_GRAPHICS_OPM_PROTECTED_OUTPUT_DOES_NOT_HAVE_COPP_SEMANTICS ((NTSTATUS)0xC01E051CL)
#endif//STATUS_GRAPHICS_OPM_PROTECTED_OUTPUT_DOES_NOT_HAVE_COPP_SEMANTICS

//
// MessageId: STATUS_GRAPHICS_OPM_INVALID_INFORMATION_REQUEST
//
// MessageText:
//
// The DxgkDdiOPMGetInformation and DxgkDdiOPMGetCOPPCompatibleInformation functions return this error code if the passed in sequence number is not the expected sequence number or the passed in OMAC value is invalid.
//
#ifndef STATUS_GRAPHICS_OPM_INVALID_INFORMATION_REQUEST
#define STATUS_GRAPHICS_OPM_INVALID_INFORMATION_REQUEST ((NTSTATUS)0xC01E051DL)
#endif//STATUS_GRAPHICS_OPM_INVALID_INFORMATION_REQUEST

//
// MessageId: STATUS_GRAPHICS_OPM_DRIVER_INTERNAL_ERROR
//
// MessageText:
//
// The function failed because an unexpected error occurred inside of a display driver.
//
#ifndef STATUS_GRAPHICS_OPM_DRIVER_INTERNAL_ERROR
#define STATUS_GRAPHICS_OPM_DRIVER_INTERNAL_ERROR ((NTSTATUS)0xC01E051EL)
#endif//STATUS_GRAPHICS_OPM_DRIVER_INTERNAL_ERROR

//
// MessageId: STATUS_GRAPHICS_OPM_PROTECTED_OUTPUT_DOES_NOT_HAVE_OPM_SEMANTICS
//
// MessageText:
//
// Either the DxgkDdiOPMGetCOPPCompatibleInformation, DxgkDdiOPMGetInformation, or DxgkDdiOPMConfigureProtectedOutput function failed. This error is returned when the caller tries to use an OPM specific command while the protected output has COPP semantics only.
//
#ifndef STATUS_GRAPHICS_OPM_PROTECTED_OUTPUT_DOES_NOT_HAVE_OPM_SEMANTICS
#define STATUS_GRAPHICS_OPM_PROTECTED_OUTPUT_DOES_NOT_HAVE_OPM_SEMANTICS ((NTSTATUS)0xC01E051FL)
#endif//STATUS_GRAPHICS_OPM_PROTECTED_OUTPUT_DOES_NOT_HAVE_OPM_SEMANTICS

//
// MessageId: STATUS_GRAPHICS_OPM_SIGNALING_NOT_SUPPORTED
//
// MessageText:
//
// The DxgkDdiOPMGetCOPPCompatibleInformation and DxgkDdiOPMConfigureProtectedOutput functions return this error if the display driver does not support the DXGKMDT_OPM_GET_ACP_AND_CGMSA_SIGNALING and DXGKMDT_OPM_SET_ACP_AND_CGMSA_SIGNALING GUIDs.
//
#ifndef STATUS_GRAPHICS_OPM_SIGNALING_NOT_SUPPORTED
#define STATUS_GRAPHICS_OPM_SIGNALING_NOT_SUPPORTED ((NTSTATUS)0xC01E0520L)
#endif//STATUS_GRAPHICS_OPM_SIGNALING_NOT_SUPPORTED

//
// MessageId: STATUS_GRAPHICS_OPM_INVALID_CONFIGURATION_REQUEST
//
// MessageText:
//
// The DxgkDdiOPMConfigureProtectedOutput function returns this error code if the passed in sequence number is not the expected sequence number or the passed in OMAC value is invalid.
//
#ifndef STATUS_GRAPHICS_OPM_INVALID_CONFIGURATION_REQUEST
#define STATUS_GRAPHICS_OPM_INVALID_CONFIGURATION_REQUEST ((NTSTATUS)0xC01E0521L)
#endif//STATUS_GRAPHICS_OPM_INVALID_CONFIGURATION_REQUEST

//
//   Monitor Configuration API status codes {0x0580..0x05DF}
//
//
// MessageId: STATUS_GRAPHICS_I2C_NOT_SUPPORTED
//
// MessageText:
//
// The monitor connected to the specified video output does not have an I2C bus.
//
#ifndef STATUS_GRAPHICS_I2C_NOT_SUPPORTED
#define STATUS_GRAPHICS_I2C_NOT_SUPPORTED ((NTSTATUS)0xC01E0580L)
#endif//STATUS_GRAPHICS_I2C_NOT_SUPPORTED

//
// MessageId: STATUS_GRAPHICS_I2C_DEVICE_DOES_NOT_EXIST
//
// MessageText:
//
// No device on the I2C bus has the specified address.
//
#ifndef STATUS_GRAPHICS_I2C_DEVICE_DOES_NOT_EXIST
#define STATUS_GRAPHICS_I2C_DEVICE_DOES_NOT_EXIST ((NTSTATUS)0xC01E0581L)
#endif//STATUS_GRAPHICS_I2C_DEVICE_DOES_NOT_EXIST

//
// MessageId: STATUS_GRAPHICS_I2C_ERROR_TRANSMITTING_DATA
//
// MessageText:
//
// An error occurred while transmitting data to the device on the I2C bus.
//
#ifndef STATUS_GRAPHICS_I2C_ERROR_TRANSMITTING_DATA
#define STATUS_GRAPHICS_I2C_ERROR_TRANSMITTING_DATA ((NTSTATUS)0xC01E0582L)
#endif//STATUS_GRAPHICS_I2C_ERROR_TRANSMITTING_DATA

//
// MessageId: STATUS_GRAPHICS_I2C_ERROR_RECEIVING_DATA
//
// MessageText:
//
// An error occurred while receiving data from the device on the I2C bus.
//
#ifndef STATUS_GRAPHICS_I2C_ERROR_RECEIVING_DATA
#define STATUS_GRAPHICS_I2C_ERROR_RECEIVING_DATA ((NTSTATUS)0xC01E0583L)
#endif//STATUS_GRAPHICS_I2C_ERROR_RECEIVING_DATA

//
// MessageId: STATUS_GRAPHICS_DDCCI_VCP_NOT_SUPPORTED
//
// MessageText:
//
// The monitor does not support the specified VCP code.
//
#ifndef STATUS_GRAPHICS_DDCCI_VCP_NOT_SUPPORTED
#define STATUS_GRAPHICS_DDCCI_VCP_NOT_SUPPORTED ((NTSTATUS)0xC01E0584L)
#endif//STATUS_GRAPHICS_DDCCI_VCP_NOT_SUPPORTED

//
// MessageId: STATUS_GRAPHICS_DDCCI_INVALID_DATA
//
// MessageText:
//
// The data received from the monitor is invalid.
//
#ifndef STATUS_GRAPHICS_DDCCI_INVALID_DATA
#define STATUS_GRAPHICS_DDCCI_INVALID_DATA ((NTSTATUS)0xC01E0585L)
#endif//STATUS_GRAPHICS_DDCCI_INVALID_DATA

//
// MessageId: STATUS_GRAPHICS_DDCCI_MONITOR_RETURNED_INVALID_TIMING_STATUS_BYTE
//
// MessageText:
//
// The function failed because a monitor returned an invalid Timing Status byte when the operating system used the DDC/CI Get Timing Report & Timing Message command to get a timing report from a monitor.
//
#ifndef STATUS_GRAPHICS_DDCCI_MONITOR_RETURNED_INVALID_TIMING_STATUS_BYTE
#define STATUS_GRAPHICS_DDCCI_MONITOR_RETURNED_INVALID_TIMING_STATUS_BYTE ((NTSTATUS)0xC01E0586L)
#endif//STATUS_GRAPHICS_DDCCI_MONITOR_RETURNED_INVALID_TIMING_STATUS_BYTE

//
// MessageId: STATUS_GRAPHICS_DDCCI_INVALID_CAPABILITIES_STRING
//
// MessageText:
//
// A monitor returned a DDC/CI capabilities string which did not comply with the ACCESS.bus 3.0, DDC/CI 1.1, or MCCS 2 Revision 1 specification.
//
#ifndef STATUS_GRAPHICS_DDCCI_INVALID_CAPABILITIES_STRING
#define STATUS_GRAPHICS_DDCCI_INVALID_CAPABILITIES_STRING ((NTSTATUS)0xC01E0587L)
#endif//STATUS_GRAPHICS_DDCCI_INVALID_CAPABILITIES_STRING

//
// MessageId: STATUS_GRAPHICS_MCA_INTERNAL_ERROR
//
// MessageText:
//
// An internal error caused an operation to fail.
//
#ifndef STATUS_GRAPHICS_MCA_INTERNAL_ERROR
#define STATUS_GRAPHICS_MCA_INTERNAL_ERROR ((NTSTATUS)0xC01E0588L)
#endif//STATUS_GRAPHICS_MCA_INTERNAL_ERROR

//
// MessageId: STATUS_GRAPHICS_DDCCI_INVALID_MESSAGE_COMMAND
//
// MessageText:
//
// An operation failed because a DDC/CI message had an invalid value in its command field.
//
#ifndef STATUS_GRAPHICS_DDCCI_INVALID_MESSAGE_COMMAND
#define STATUS_GRAPHICS_DDCCI_INVALID_MESSAGE_COMMAND ((NTSTATUS)0xC01E0589L)
#endif//STATUS_GRAPHICS_DDCCI_INVALID_MESSAGE_COMMAND

//
// MessageId: STATUS_GRAPHICS_DDCCI_INVALID_MESSAGE_LENGTH
//
// MessageText:
//
// An error occurred because the field length of a DDC/CI message contained an invalid value.
//
#ifndef STATUS_GRAPHICS_DDCCI_INVALID_MESSAGE_LENGTH
#define STATUS_GRAPHICS_DDCCI_INVALID_MESSAGE_LENGTH ((NTSTATUS)0xC01E058AL)
#endif//STATUS_GRAPHICS_DDCCI_INVALID_MESSAGE_LENGTH

//
// MessageId: STATUS_GRAPHICS_DDCCI_INVALID_MESSAGE_CHECKSUM
//
// MessageText:
//
// An error occurred because the checksum field in a DDC/CI message did not match the message's computed checksum value. This error implies that the data was corrupted while it was being transmitted from a monitor to a computer.
//
#ifndef STATUS_GRAPHICS_DDCCI_INVALID_MESSAGE_CHECKSUM
#define STATUS_GRAPHICS_DDCCI_INVALID_MESSAGE_CHECKSUM ((NTSTATUS)0xC01E058BL)
#endif//STATUS_GRAPHICS_DDCCI_INVALID_MESSAGE_CHECKSUM

//
// MessageId: STATUS_GRAPHICS_INVALID_PHYSICAL_MONITOR_HANDLE
//
// MessageText:
//
// This function failed because an invalid monitor handle was passed to it.
//
#ifndef STATUS_GRAPHICS_INVALID_PHYSICAL_MONITOR_HANDLE
#define STATUS_GRAPHICS_INVALID_PHYSICAL_MONITOR_HANDLE ((NTSTATUS)0xC01E058CL)
#endif//STATUS_GRAPHICS_INVALID_PHYSICAL_MONITOR_HANDLE

//
// MessageId: STATUS_GRAPHICS_MONITOR_NO_LONGER_EXISTS
//
// MessageText:
//
// The operating system asynchronously destroyed the monitor which corresponds to this handle because the operating system's state changed. This error typically occurs because the monitor PDO associated with this handle was removed, the monitor PDO associated with this handle was stopped, or a display mode change occurred. A display mode change occurs when windows sends a WM_DISPLAYCHANGE windows message to applications.
//
#ifndef STATUS_GRAPHICS_MONITOR_NO_LONGER_EXISTS
#define STATUS_GRAPHICS_MONITOR_NO_LONGER_EXISTS ((NTSTATUS)0xC01E058DL)
#endif//STATUS_GRAPHICS_MONITOR_NO_LONGER_EXISTS

//
//   OPM, UAB, PVP and DDC/CI shared status codes {0x25E0..0x25FF}
//
//
// MessageId: STATUS_GRAPHICS_ONLY_CONSOLE_SESSION_SUPPORTED
//
// MessageText:
//
// This function can only be used if a program is running in the local console session. It cannot be used if a program is running on a remote desktop session or on a terminal server session.
//
#ifndef STATUS_GRAPHICS_ONLY_CONSOLE_SESSION_SUPPORTED
#define STATUS_GRAPHICS_ONLY_CONSOLE_SESSION_SUPPORTED ((NTSTATUS)0xC01E05E0L)
#endif//STATUS_GRAPHICS_ONLY_CONSOLE_SESSION_SUPPORTED

//
// MessageId: STATUS_GRAPHICS_NO_DISPLAY_DEVICE_CORRESPONDS_TO_NAME
//
// MessageText:
//
// This function cannot find an actual GDI display device which corresponds to the specified GDI display device name.
//
#ifndef STATUS_GRAPHICS_NO_DISPLAY_DEVICE_CORRESPONDS_TO_NAME
#define STATUS_GRAPHICS_NO_DISPLAY_DEVICE_CORRESPONDS_TO_NAME ((NTSTATUS)0xC01E05E1L)
#endif//STATUS_GRAPHICS_NO_DISPLAY_DEVICE_CORRESPONDS_TO_NAME

//
// MessageId: STATUS_GRAPHICS_DISPLAY_DEVICE_NOT_ATTACHED_TO_DESKTOP
//
// MessageText:
//
// The function failed because the specified GDI display device was not attached to the Windows desktop.
//
#ifndef STATUS_GRAPHICS_DISPLAY_DEVICE_NOT_ATTACHED_TO_DESKTOP
#define STATUS_GRAPHICS_DISPLAY_DEVICE_NOT_ATTACHED_TO_DESKTOP ((NTSTATUS)0xC01E05E2L)
#endif//STATUS_GRAPHICS_DISPLAY_DEVICE_NOT_ATTACHED_TO_DESKTOP

//
// MessageId: STATUS_GRAPHICS_MIRRORING_DEVICES_NOT_SUPPORTED
//
// MessageText:
//
// This function does not support GDI mirroring display devices because GDI mirroring display devices do not have any physical monitors associated with them.
//
#ifndef STATUS_GRAPHICS_MIRRORING_DEVICES_NOT_SUPPORTED
#define STATUS_GRAPHICS_MIRRORING_DEVICES_NOT_SUPPORTED ((NTSTATUS)0xC01E05E3L)
#endif//STATUS_GRAPHICS_MIRRORING_DEVICES_NOT_SUPPORTED

//
// MessageId: STATUS_GRAPHICS_INVALID_POINTER
//
// MessageText:
//
// The function failed because an invalid pointer parameter was passed to it. A pointer parameter is invalid if it is NULL, it points to an invalid address, it points to a kernel mode address or it is not correctly aligned.
//
#ifndef STATUS_GRAPHICS_INVALID_POINTER
#define STATUS_GRAPHICS_INVALID_POINTER  ((NTSTATUS)0xC01E05E4L)
#endif//STATUS_GRAPHICS_INVALID_POINTER

//
// MessageId: STATUS_GRAPHICS_NO_MONITORS_CORRESPOND_TO_DISPLAY_DEVICE
//
// MessageText:
//
// This function failed because the GDI device passed to it did not have any monitors associated with it.
//
#ifndef STATUS_GRAPHICS_NO_MONITORS_CORRESPOND_TO_DISPLAY_DEVICE
#define STATUS_GRAPHICS_NO_MONITORS_CORRESPOND_TO_DISPLAY_DEVICE ((NTSTATUS)0xC01E05E5L)
#endif//STATUS_GRAPHICS_NO_MONITORS_CORRESPOND_TO_DISPLAY_DEVICE

//
// MessageId: STATUS_GRAPHICS_PARAMETER_ARRAY_TOO_SMALL
//
// MessageText:
//
// An array passed to the function cannot hold all of the data that the function must copy into the array.
//
#ifndef STATUS_GRAPHICS_PARAMETER_ARRAY_TOO_SMALL
#define STATUS_GRAPHICS_PARAMETER_ARRAY_TOO_SMALL ((NTSTATUS)0xC01E05E6L)
#endif//STATUS_GRAPHICS_PARAMETER_ARRAY_TOO_SMALL

//
// MessageId: STATUS_GRAPHICS_INTERNAL_ERROR
//
// MessageText:
//
// An internal error caused an operation to fail.
//
#ifndef STATUS_GRAPHICS_INTERNAL_ERROR
#define STATUS_GRAPHICS_INTERNAL_ERROR   ((NTSTATUS)0xC01E05E7L)
#endif//STATUS_GRAPHICS_INTERNAL_ERROR

//
// MessageId: STATUS_GRAPHICS_SESSION_TYPE_CHANGE_IN_PROGRESS
//
// MessageText:
//
// The function failed because the current session is changing its type. This function cannot be called when the current session is changing its type. There are currently three types of sessions: console, disconnected and remote.
//
#ifndef STATUS_GRAPHICS_SESSION_TYPE_CHANGE_IN_PROGRESS
#define STATUS_GRAPHICS_SESSION_TYPE_CHANGE_IN_PROGRESS ((NTSTATUS)0xC01E05E8L)
#endif//STATUS_GRAPHICS_SESSION_TYPE_CHANGE_IN_PROGRESS


//
// Full Volume Encryption Error codes (fvevol.sys)
//

//
// MessageId: STATUS_FVE_LOCKED_VOLUME
//
// MessageText:
//
// This volume is locked by BitLocker Drive Encryption.
//
#ifndef STATUS_FVE_LOCKED_VOLUME
#define STATUS_FVE_LOCKED_VOLUME         ((NTSTATUS)0xC0210000L)
#endif//STATUS_FVE_LOCKED_VOLUME

//
// MessageId: STATUS_FVE_NOT_ENCRYPTED
//
// MessageText:
//
// The volume is not encrypted, no key is available.
//
#ifndef STATUS_FVE_NOT_ENCRYPTED
#define STATUS_FVE_NOT_ENCRYPTED         ((NTSTATUS)0xC0210001L)
#endif//STATUS_FVE_NOT_ENCRYPTED

//
// MessageId: STATUS_FVE_BAD_INFORMATION
//
// MessageText:
//
// The control block for the encrypted volume is not valid.
//
#ifndef STATUS_FVE_BAD_INFORMATION
#define STATUS_FVE_BAD_INFORMATION       ((NTSTATUS)0xC0210002L)
#endif//STATUS_FVE_BAD_INFORMATION

//
// MessageId: STATUS_FVE_TOO_SMALL
//
// MessageText:
//
// The volume cannot be encrypted because it does not have enough free space.
//
#ifndef STATUS_FVE_TOO_SMALL
#define STATUS_FVE_TOO_SMALL             ((NTSTATUS)0xC0210003L)
#endif//STATUS_FVE_TOO_SMALL

//
// MessageId: STATUS_FVE_FAILED_WRONG_FS
//
// MessageText:
//
// The volume cannot be encrypted because the file system is not supported.
//
#ifndef STATUS_FVE_FAILED_WRONG_FS
#define STATUS_FVE_FAILED_WRONG_FS       ((NTSTATUS)0xC0210004L)
#endif//STATUS_FVE_FAILED_WRONG_FS

//
// MessageId: STATUS_FVE_BAD_PARTITION_SIZE
//
// MessageText:
//
// The file system size is larger than the partition size in the partition table.
//
#ifndef STATUS_FVE_BAD_PARTITION_SIZE
#define STATUS_FVE_BAD_PARTITION_SIZE    ((NTSTATUS)0xC0210005L)
#endif//STATUS_FVE_BAD_PARTITION_SIZE

//
// MessageId: STATUS_FVE_FS_NOT_EXTENDED
//
// MessageText:
//
// The file system does not extend to the end of the volume.
//
#ifndef STATUS_FVE_FS_NOT_EXTENDED
#define STATUS_FVE_FS_NOT_EXTENDED       ((NTSTATUS)0xC0210006L)
#endif//STATUS_FVE_FS_NOT_EXTENDED

//
// MessageId: STATUS_FVE_FS_MOUNTED
//
// MessageText:
//
// This operation cannot be performed while a file system is mounted on the volume.
//
#ifndef STATUS_FVE_FS_MOUNTED
#define STATUS_FVE_FS_MOUNTED            ((NTSTATUS)0xC0210007L)
#endif//STATUS_FVE_FS_MOUNTED

//
// MessageId: STATUS_FVE_NO_LICENSE
//
// MessageText:
//
// BitLocker Drive Encryption is not included with this version of Windows.
//
#ifndef STATUS_FVE_NO_LICENSE
#define STATUS_FVE_NO_LICENSE            ((NTSTATUS)0xC0210008L)
#endif//STATUS_FVE_NO_LICENSE

//
// MessageId: STATUS_FVE_ACTION_NOT_ALLOWED
//
// MessageText:
//
// Requested action not allowed in the current volume state.
//
#ifndef STATUS_FVE_ACTION_NOT_ALLOWED
#define STATUS_FVE_ACTION_NOT_ALLOWED    ((NTSTATUS)0xC0210009L)
#endif//STATUS_FVE_ACTION_NOT_ALLOWED

//
// MessageId: STATUS_FVE_BAD_DATA
//
// MessageText:
//
// Data supplied is malformed.
//
#ifndef STATUS_FVE_BAD_DATA
#define STATUS_FVE_BAD_DATA              ((NTSTATUS)0xC021000AL)
#endif//STATUS_FVE_BAD_DATA

//
// MessageId: STATUS_FVE_VOLUME_NOT_BOUND
//
// MessageText:
//
// The volume is not bound to the system.
//
#ifndef STATUS_FVE_VOLUME_NOT_BOUND
#define STATUS_FVE_VOLUME_NOT_BOUND      ((NTSTATUS)0xC021000BL)
#endif//STATUS_FVE_VOLUME_NOT_BOUND

//
// MessageId: STATUS_FVE_NOT_DATA_VOLUME
//
// MessageText:
//
// That volume is not a data volume.
//
#ifndef STATUS_FVE_NOT_DATA_VOLUME
#define STATUS_FVE_NOT_DATA_VOLUME       ((NTSTATUS)0xC021000CL)
#endif//STATUS_FVE_NOT_DATA_VOLUME

//
// MessageId: STATUS_FVE_CONV_READ_ERROR
//
// MessageText:
//
// A read operation failed while converting the volume.
//
#ifndef STATUS_FVE_CONV_READ_ERROR
#define STATUS_FVE_CONV_READ_ERROR       ((NTSTATUS)0xC021000DL)
#endif//STATUS_FVE_CONV_READ_ERROR

//
// MessageId: STATUS_FVE_CONV_WRITE_ERROR
//
// MessageText:
//
// A write operation failed while converting the volume.
//
#ifndef STATUS_FVE_CONV_WRITE_ERROR
#define STATUS_FVE_CONV_WRITE_ERROR      ((NTSTATUS)0xC021000EL)
#endif//STATUS_FVE_CONV_WRITE_ERROR

//
// MessageId: STATUS_FVE_OVERLAPPED_UPDATE
//
// MessageText:
//
// The control block for the encrypted volume was updated by another thread. Try again.
//
#ifndef STATUS_FVE_OVERLAPPED_UPDATE
#define STATUS_FVE_OVERLAPPED_UPDATE     ((NTSTATUS)0xC021000FL)
#endif//STATUS_FVE_OVERLAPPED_UPDATE

//
// MessageId: STATUS_FVE_FAILED_SECTOR_SIZE
//
// MessageText:
//
// The encryption algorithm does not support the sector size of that volume.
//
#ifndef STATUS_FVE_FAILED_SECTOR_SIZE
#define STATUS_FVE_FAILED_SECTOR_SIZE    ((NTSTATUS)0xC0210010L)
#endif//STATUS_FVE_FAILED_SECTOR_SIZE

//
// MessageId: STATUS_FVE_FAILED_AUTHENTICATION
//
// MessageText:
//
// BitLocker recovery authentication failed.
//
#ifndef STATUS_FVE_FAILED_AUTHENTICATION
#define STATUS_FVE_FAILED_AUTHENTICATION ((NTSTATUS)0xC0210011L)
#endif//STATUS_FVE_FAILED_AUTHENTICATION

//
// MessageId: STATUS_FVE_NOT_OS_VOLUME
//
// MessageText:
//
// That volume is not the OS volume.
//
#ifndef STATUS_FVE_NOT_OS_VOLUME
#define STATUS_FVE_NOT_OS_VOLUME         ((NTSTATUS)0xC0210012L)
#endif//STATUS_FVE_NOT_OS_VOLUME

//
// MessageId: STATUS_FVE_KEYFILE_NOT_FOUND
//
// MessageText:
//
// The BitLocker startup key or recovery password could not be read from external media.
//
#ifndef STATUS_FVE_KEYFILE_NOT_FOUND
#define STATUS_FVE_KEYFILE_NOT_FOUND     ((NTSTATUS)0xC0210013L)
#endif//STATUS_FVE_KEYFILE_NOT_FOUND

//
// MessageId: STATUS_FVE_KEYFILE_INVALID
//
// MessageText:
//
// The BitLocker startup key or recovery password file is corrupt or invalid.
//
#ifndef STATUS_FVE_KEYFILE_INVALID
#define STATUS_FVE_KEYFILE_INVALID       ((NTSTATUS)0xC0210014L)
#endif//STATUS_FVE_KEYFILE_INVALID

//
// MessageId: STATUS_FVE_KEYFILE_NO_VMK
//
// MessageText:
//
// The BitLocker encryption key could not be obtained from the startup key or recovery password.
//
#ifndef STATUS_FVE_KEYFILE_NO_VMK
#define STATUS_FVE_KEYFILE_NO_VMK        ((NTSTATUS)0xC0210015L)
#endif//STATUS_FVE_KEYFILE_NO_VMK

//
// MessageId: STATUS_FVE_TPM_DISABLED
//
// MessageText:
//
// The Trusted Platform Module (TPM) is disabled.
//
#ifndef STATUS_FVE_TPM_DISABLED
#define STATUS_FVE_TPM_DISABLED          ((NTSTATUS)0xC0210016L)
#endif//STATUS_FVE_TPM_DISABLED

//
// MessageId: STATUS_FVE_TPM_SRK_AUTH_NOT_ZERO
//
// MessageText:
//
// The authorization data for the Storage Root Key (SRK) of the Trusted Platform Module (TPM) is not zero.
//
#ifndef STATUS_FVE_TPM_SRK_AUTH_NOT_ZERO
#define STATUS_FVE_TPM_SRK_AUTH_NOT_ZERO ((NTSTATUS)0xC0210017L)
#endif//STATUS_FVE_TPM_SRK_AUTH_NOT_ZERO

//
// MessageId: STATUS_FVE_TPM_INVALID_PCR
//
// MessageText:
//
// The system boot information changed or the Trusted Platform Module (TPM) locked out access to BitLocker encryption keys until the computer is restarted.
//
#ifndef STATUS_FVE_TPM_INVALID_PCR
#define STATUS_FVE_TPM_INVALID_PCR       ((NTSTATUS)0xC0210018L)
#endif//STATUS_FVE_TPM_INVALID_PCR

//
// MessageId: STATUS_FVE_TPM_NO_VMK
//
// MessageText:
//
// The BitLocker encryption key could not be obtained from the Trusted Platform Module (TPM).
//
#ifndef STATUS_FVE_TPM_NO_VMK
#define STATUS_FVE_TPM_NO_VMK            ((NTSTATUS)0xC0210019L)
#endif//STATUS_FVE_TPM_NO_VMK

//
// MessageId: STATUS_FVE_PIN_INVALID
//
// MessageText:
//
// The BitLocker encryption key could not be obtained from the Trusted Platform Module (TPM) and PIN.
//
#ifndef STATUS_FVE_PIN_INVALID
#define STATUS_FVE_PIN_INVALID           ((NTSTATUS)0xC021001AL)
#endif//STATUS_FVE_PIN_INVALID

//
// MessageId: STATUS_FVE_AUTH_INVALID_APPLICATION
//
// MessageText:
//
// A boot application hash does not match the hash computed when BitLocker was turned on.
//
#ifndef STATUS_FVE_AUTH_INVALID_APPLICATION
#define STATUS_FVE_AUTH_INVALID_APPLICATION ((NTSTATUS)0xC021001BL)
#endif//STATUS_FVE_AUTH_INVALID_APPLICATION

//
// MessageId: STATUS_FVE_AUTH_INVALID_CONFIG
//
// MessageText:
//
// The Boot Configuration Data (BCD) settings are not supported or have changed since BitLocker was enabled.
//
#ifndef STATUS_FVE_AUTH_INVALID_CONFIG
#define STATUS_FVE_AUTH_INVALID_CONFIG   ((NTSTATUS)0xC021001CL)
#endif//STATUS_FVE_AUTH_INVALID_CONFIG

//
// MessageId: STATUS_FVE_DEBUGGER_ENABLED
//
// MessageText:
//
// Boot debugging is enabled. Run bcdedit to turn it off.
//
#ifndef STATUS_FVE_DEBUGGER_ENABLED
#define STATUS_FVE_DEBUGGER_ENABLED      ((NTSTATUS)0xC021001DL)
#endif//STATUS_FVE_DEBUGGER_ENABLED

//
// MessageId: STATUS_FVE_DRY_RUN_FAILED
//
// MessageText:
//
// The BitLocker encryption key could not be obtained.
//
#ifndef STATUS_FVE_DRY_RUN_FAILED
#define STATUS_FVE_DRY_RUN_FAILED        ((NTSTATUS)0xC021001EL)
#endif//STATUS_FVE_DRY_RUN_FAILED

//
// MessageId: STATUS_FVE_BAD_METADATA_POINTER
//
// MessageText:
//
// The metadata disk region pointer is incorrect.
//
#ifndef STATUS_FVE_BAD_METADATA_POINTER
#define STATUS_FVE_BAD_METADATA_POINTER  ((NTSTATUS)0xC021001FL)
#endif//STATUS_FVE_BAD_METADATA_POINTER

//
// MessageId: STATUS_FVE_OLD_METADATA_COPY
//
// MessageText:
//
// The backup copy of the metadata is out of date.
//
#ifndef STATUS_FVE_OLD_METADATA_COPY
#define STATUS_FVE_OLD_METADATA_COPY     ((NTSTATUS)0xC0210020L)
#endif//STATUS_FVE_OLD_METADATA_COPY

//
// MessageId: STATUS_FVE_REBOOT_REQUIRED
//
// MessageText:
//
// No action was taken as a system reboot is required.
//
#ifndef STATUS_FVE_REBOOT_REQUIRED
#define STATUS_FVE_REBOOT_REQUIRED       ((NTSTATUS)0xC0210021L)
#endif//STATUS_FVE_REBOOT_REQUIRED

//
// MessageId: STATUS_FVE_RAW_ACCESS
//
// MessageText:
//
// No action was taken as BitLocker Drive Encryption is in RAW access mode.
//
#ifndef STATUS_FVE_RAW_ACCESS
#define STATUS_FVE_RAW_ACCESS            ((NTSTATUS)0xC0210022L)
#endif//STATUS_FVE_RAW_ACCESS

//
// MessageId: STATUS_FVE_RAW_BLOCKED
//
// MessageText:
//
// BitLocker Drive Encryption cannot enter raw access mode for this volume.
//
#ifndef STATUS_FVE_RAW_BLOCKED
#define STATUS_FVE_RAW_BLOCKED           ((NTSTATUS)0xC0210023L)
#endif//STATUS_FVE_RAW_BLOCKED

//
// MessageId: STATUS_FVE_NO_AUTOUNLOCK_MASTER_KEY
//
// MessageText:
//
// The auto-unlock master key was not available from the operating system volume. Retry the operation using the BitLocker WMI interface.
//
#ifndef STATUS_FVE_NO_AUTOUNLOCK_MASTER_KEY
#define STATUS_FVE_NO_AUTOUNLOCK_MASTER_KEY ((NTSTATUS)0xC0210024L)
#endif//STATUS_FVE_NO_AUTOUNLOCK_MASTER_KEY

//
// MessageId: STATUS_FVE_MOR_FAILED
//
// MessageText:
//
// The system firmware failed to enable clearing of system memory on reboot.
//
#ifndef STATUS_FVE_MOR_FAILED
#define STATUS_FVE_MOR_FAILED            ((NTSTATUS)0xC0210025L)
#endif//STATUS_FVE_MOR_FAILED

//
// MessageId: STATUS_FVE_NO_FEATURE_LICENSE
//
// MessageText:
//
// This feature of BitLocker Drive Encryption is not included with this version of Windows.
//
#ifndef STATUS_FVE_NO_FEATURE_LICENSE
#define STATUS_FVE_NO_FEATURE_LICENSE    ((NTSTATUS)0xC0210026L)
#endif//STATUS_FVE_NO_FEATURE_LICENSE

//
// MessageId: STATUS_FVE_POLICY_USER_DISABLE_RDV_NOT_ALLOWED
//
// MessageText:
//
// Group policy does not permit turning off BitLocker Drive Encryption on roaming data volumes.
//
#ifndef STATUS_FVE_POLICY_USER_DISABLE_RDV_NOT_ALLOWED
#define STATUS_FVE_POLICY_USER_DISABLE_RDV_NOT_ALLOWED ((NTSTATUS)0xC0210027L)
#endif//STATUS_FVE_POLICY_USER_DISABLE_RDV_NOT_ALLOWED

//
// MessageId: STATUS_FVE_CONV_RECOVERY_FAILED
//
// MessageText:
//
// Bitlocker Drive Encryption failed to recover from aborted conversion. This could be due to either all conversion logs being corrupted or the media being write-protected.
//
#ifndef STATUS_FVE_CONV_RECOVERY_FAILED
#define STATUS_FVE_CONV_RECOVERY_FAILED  ((NTSTATUS)0xC0210028L)
#endif//STATUS_FVE_CONV_RECOVERY_FAILED

//
// MessageId: STATUS_FVE_VIRTUALIZED_SPACE_TOO_BIG
//
// MessageText:
//
// The requested virtualization size is too big.
//
#ifndef STATUS_FVE_VIRTUALIZED_SPACE_TOO_BIG
#define STATUS_FVE_VIRTUALIZED_SPACE_TOO_BIG ((NTSTATUS)0xC0210029L)
#endif//STATUS_FVE_VIRTUALIZED_SPACE_TOO_BIG

//
// MessageId: STATUS_FVE_INVALID_DATUM_TYPE
//
// MessageText:
//
// The management information stored on the drive contained an unknown type. If you are using an old version of Windows, try accessing the drive from the latest version.
//
#ifndef STATUS_FVE_INVALID_DATUM_TYPE
#define STATUS_FVE_INVALID_DATUM_TYPE    ((NTSTATUS)0xC021002AL)
#endif//STATUS_FVE_INVALID_DATUM_TYPE

//
// MessageId: STATUS_FVE_VOLUME_TOO_SMALL
//
// MessageText:
//
// The drive is too small to be protected using BitLocker Drive Encryption.
//
#ifndef STATUS_FVE_VOLUME_TOO_SMALL
#define STATUS_FVE_VOLUME_TOO_SMALL      ((NTSTATUS)0xC0210030L)
#endif//STATUS_FVE_VOLUME_TOO_SMALL

//
// MessageId: STATUS_FVE_ENH_PIN_INVALID
//
// MessageText:
//
// The BitLocker encryption key could not be obtained from the Trusted Platform Module (TPM) and enhanced PIN. Try using a PIN containing only numerals.
//
#ifndef STATUS_FVE_ENH_PIN_INVALID
#define STATUS_FVE_ENH_PIN_INVALID       ((NTSTATUS)0xC0210031L)
#endif//STATUS_FVE_ENH_PIN_INVALID

//
// MessageId: STATUS_FVE_FULL_ENCRYPTION_NOT_ALLOWED_ON_TP_STORAGE
//
// MessageText:
//
// BitLocker Drive Encryption only supports Used Space Only encryption on thin provisioned storage.
//
#ifndef STATUS_FVE_FULL_ENCRYPTION_NOT_ALLOWED_ON_TP_STORAGE
#define STATUS_FVE_FULL_ENCRYPTION_NOT_ALLOWED_ON_TP_STORAGE ((NTSTATUS)0xC0210032L)
#endif//STATUS_FVE_FULL_ENCRYPTION_NOT_ALLOWED_ON_TP_STORAGE

//
// MessageId: STATUS_FVE_WIPE_NOT_ALLOWED_ON_TP_STORAGE
//
// MessageText:
//
// BitLocker Drive Encryption does not support wiping free space on thin provisioned storage.
//
#ifndef STATUS_FVE_WIPE_NOT_ALLOWED_ON_TP_STORAGE
#define STATUS_FVE_WIPE_NOT_ALLOWED_ON_TP_STORAGE ((NTSTATUS)0xC0210033L)
#endif//STATUS_FVE_WIPE_NOT_ALLOWED_ON_TP_STORAGE

//
// MessageId: STATUS_FVE_NOT_ALLOWED_ON_CSV_STACK
//
// MessageText:
//
// This command can only be performed from the coordinator node for the specified CSV volume.
//
#ifndef STATUS_FVE_NOT_ALLOWED_ON_CSV_STACK
#define STATUS_FVE_NOT_ALLOWED_ON_CSV_STACK ((NTSTATUS)0xC0210034L)
#endif//STATUS_FVE_NOT_ALLOWED_ON_CSV_STACK

//
// MessageId: STATUS_FVE_NOT_ALLOWED_ON_CLUSTER
//
// MessageText:
//
// This command cannot be performed on a volume when it is part of a cluster.
//
#ifndef STATUS_FVE_NOT_ALLOWED_ON_CLUSTER
#define STATUS_FVE_NOT_ALLOWED_ON_CLUSTER ((NTSTATUS)0xC0210035L)
#endif//STATUS_FVE_NOT_ALLOWED_ON_CLUSTER

//
// MessageId: STATUS_FVE_NOT_ALLOWED_TO_UPGRADE_WHILE_CONVERTING
//
// MessageText:
//
// BitLocker cannot be upgraded during disk encryption or decryption.
//
#ifndef STATUS_FVE_NOT_ALLOWED_TO_UPGRADE_WHILE_CONVERTING
#define STATUS_FVE_NOT_ALLOWED_TO_UPGRADE_WHILE_CONVERTING ((NTSTATUS)0xC0210036L)
#endif//STATUS_FVE_NOT_ALLOWED_TO_UPGRADE_WHILE_CONVERTING

//
// MessageId: STATUS_FVE_WIPE_CANCEL_NOT_APPLICABLE
//
// MessageText:
//
// Wipe of free space is not currently taking place.
//
#ifndef STATUS_FVE_WIPE_CANCEL_NOT_APPLICABLE
#define STATUS_FVE_WIPE_CANCEL_NOT_APPLICABLE ((NTSTATUS)0xC0210037L)
#endif//STATUS_FVE_WIPE_CANCEL_NOT_APPLICABLE

//
// MessageId: STATUS_FVE_EDRIVE_DRY_RUN_FAILED
//
// MessageText:
//
// Your computer doesn't support BitLocker hardware-based encryption. Check with your computer manufacturer for firmware updates.
//
#ifndef STATUS_FVE_EDRIVE_DRY_RUN_FAILED
#define STATUS_FVE_EDRIVE_DRY_RUN_FAILED ((NTSTATUS)0xC0210038L)
#endif//STATUS_FVE_EDRIVE_DRY_RUN_FAILED

//
// MessageId: STATUS_FVE_SECUREBOOT_DISABLED
//
// MessageText:
//
// Secure Boot has been disabled. Either Secure Boot must be re-enabled, or BitLocker must be suspended for Windows to start normally.
//
#ifndef STATUS_FVE_SECUREBOOT_DISABLED
#define STATUS_FVE_SECUREBOOT_DISABLED   ((NTSTATUS)0xC0210039L)
#endif//STATUS_FVE_SECUREBOOT_DISABLED

//
// MessageId: STATUS_FVE_SECUREBOOT_CONFIG_CHANGE
//
// MessageText:
//
// Secure Boot policy has unexpectedly changed.
//
#ifndef STATUS_FVE_SECUREBOOT_CONFIG_CHANGE
#define STATUS_FVE_SECUREBOOT_CONFIG_CHANGE ((NTSTATUS)0xC021003AL)
#endif//STATUS_FVE_SECUREBOOT_CONFIG_CHANGE

//
// MessageId: STATUS_FVE_DEVICE_LOCKEDOUT
//
// MessageText:
//
// Device Lock has been triggered due to too many incorrect password attempts.
//
#ifndef STATUS_FVE_DEVICE_LOCKEDOUT
#define STATUS_FVE_DEVICE_LOCKEDOUT      ((NTSTATUS)0xC021003BL)
#endif//STATUS_FVE_DEVICE_LOCKEDOUT

//
// MessageId: STATUS_FVE_VOLUME_EXTEND_PREVENTS_EOW_DECRYPT
//
// MessageText:
//
// Device encryption removal is blocked due to volume being extended beyond its original size.
//
#ifndef STATUS_FVE_VOLUME_EXTEND_PREVENTS_EOW_DECRYPT
#define STATUS_FVE_VOLUME_EXTEND_PREVENTS_EOW_DECRYPT ((NTSTATUS)0xC021003CL)
#endif//STATUS_FVE_VOLUME_EXTEND_PREVENTS_EOW_DECRYPT

//
// MessageId: STATUS_FVE_NOT_DE_VOLUME
//
// MessageText:
//
// This action isn't supported because this drive isn't automatically managed with device encryption.
//
#ifndef STATUS_FVE_NOT_DE_VOLUME
#define STATUS_FVE_NOT_DE_VOLUME         ((NTSTATUS)0xC021003DL)
#endif//STATUS_FVE_NOT_DE_VOLUME

//
// MessageId: STATUS_FVE_PROTECTION_DISABLED
//
// MessageText:
//
// BitLocker Drive Encryption has been suspended on this drive. All BitLocker key protectors configured for this drive are effectively disabled, and the drive will be automatically unlocked using an unencrypted (clear) key.
//
#ifndef STATUS_FVE_PROTECTION_DISABLED
#define STATUS_FVE_PROTECTION_DISABLED   ((NTSTATUS)0xC021003EL)
#endif//STATUS_FVE_PROTECTION_DISABLED

//
// MessageId: STATUS_FVE_PROTECTION_CANNOT_BE_DISABLED
//
// MessageText:
//
// BitLocker can't be suspended on this drive until the next restart.
//
#ifndef STATUS_FVE_PROTECTION_CANNOT_BE_DISABLED
#define STATUS_FVE_PROTECTION_CANNOT_BE_DISABLED ((NTSTATUS)0xC021003FL)
#endif//STATUS_FVE_PROTECTION_CANNOT_BE_DISABLED

//
// MessageId: STATUS_FVE_OSV_KSR_NOT_ALLOWED
//
// MessageText:
//
// BitLocker Drive Encryption policy does not allow KSR operation with protected OS volume.
//
#ifndef STATUS_FVE_OSV_KSR_NOT_ALLOWED
#define STATUS_FVE_OSV_KSR_NOT_ALLOWED   ((NTSTATUS)0xC0210040L)
#endif//STATUS_FVE_OSV_KSR_NOT_ALLOWED


//
// FWP error codes (fwpkclnt.sys)
//

//
// MessageId: STATUS_FWP_CALLOUT_NOT_FOUND
//
// MessageText:
//
// The callout does not exist.
//
#ifndef STATUS_FWP_CALLOUT_NOT_FOUND
#define STATUS_FWP_CALLOUT_NOT_FOUND     ((NTSTATUS)0xC0220001L)
#endif//STATUS_FWP_CALLOUT_NOT_FOUND

//
// MessageId: STATUS_FWP_CONDITION_NOT_FOUND
//
// MessageText:
//
// The filter condition does not exist.
//
#ifndef STATUS_FWP_CONDITION_NOT_FOUND
#define STATUS_FWP_CONDITION_NOT_FOUND   ((NTSTATUS)0xC0220002L)
#endif//STATUS_FWP_CONDITION_NOT_FOUND

//
// MessageId: STATUS_FWP_FILTER_NOT_FOUND
//
// MessageText:
//
// The filter does not exist.
//
#ifndef STATUS_FWP_FILTER_NOT_FOUND
#define STATUS_FWP_FILTER_NOT_FOUND      ((NTSTATUS)0xC0220003L)
#endif//STATUS_FWP_FILTER_NOT_FOUND

//
// MessageId: STATUS_FWP_LAYER_NOT_FOUND
//
// MessageText:
//
// The layer does not exist.
//
#ifndef STATUS_FWP_LAYER_NOT_FOUND
#define STATUS_FWP_LAYER_NOT_FOUND       ((NTSTATUS)0xC0220004L)
#endif//STATUS_FWP_LAYER_NOT_FOUND

//
// MessageId: STATUS_FWP_PROVIDER_NOT_FOUND
//
// MessageText:
//
// The provider does not exist.
//
#ifndef STATUS_FWP_PROVIDER_NOT_FOUND
#define STATUS_FWP_PROVIDER_NOT_FOUND    ((NTSTATUS)0xC0220005L)
#endif//STATUS_FWP_PROVIDER_NOT_FOUND

//
// MessageId: STATUS_FWP_PROVIDER_CONTEXT_NOT_FOUND
//
// MessageText:
//
// The provider context does not exist.
//
#ifndef STATUS_FWP_PROVIDER_CONTEXT_NOT_FOUND
#define STATUS_FWP_PROVIDER_CONTEXT_NOT_FOUND ((NTSTATUS)0xC0220006L)
#endif//STATUS_FWP_PROVIDER_CONTEXT_NOT_FOUND

//
// MessageId: STATUS_FWP_SUBLAYER_NOT_FOUND
//
// MessageText:
//
// The sublayer does not exist.
//
#ifndef STATUS_FWP_SUBLAYER_NOT_FOUND
#define STATUS_FWP_SUBLAYER_NOT_FOUND    ((NTSTATUS)0xC0220007L)
#endif//STATUS_FWP_SUBLAYER_NOT_FOUND

//
// MessageId: STATUS_FWP_NOT_FOUND
//
// MessageText:
//
// The object does not exist.
//
#ifndef STATUS_FWP_NOT_FOUND
#define STATUS_FWP_NOT_FOUND             ((NTSTATUS)0xC0220008L)
#endif//STATUS_FWP_NOT_FOUND

//
// MessageId: STATUS_FWP_ALREADY_EXISTS
//
// MessageText:
//
// An object with that GUID or LUID already exists.
//
#ifndef STATUS_FWP_ALREADY_EXISTS
#define STATUS_FWP_ALREADY_EXISTS        ((NTSTATUS)0xC0220009L)
#endif//STATUS_FWP_ALREADY_EXISTS

//
// MessageId: STATUS_FWP_IN_USE
//
// MessageText:
//
// The object is referenced by other objects so cannot be deleted.
//
#ifndef STATUS_FWP_IN_USE
#define STATUS_FWP_IN_USE                ((NTSTATUS)0xC022000AL)
#endif//STATUS_FWP_IN_USE

//
// MessageId: STATUS_FWP_DYNAMIC_SESSION_IN_PROGRESS
//
// MessageText:
//
// The call is not allowed from within a dynamic session.
//
#ifndef STATUS_FWP_DYNAMIC_SESSION_IN_PROGRESS
#define STATUS_FWP_DYNAMIC_SESSION_IN_PROGRESS ((NTSTATUS)0xC022000BL)
#endif//STATUS_FWP_DYNAMIC_SESSION_IN_PROGRESS

//
// MessageId: STATUS_FWP_WRONG_SESSION
//
// MessageText:
//
// The call was made from the wrong session so cannot be completed.
//
#ifndef STATUS_FWP_WRONG_SESSION
#define STATUS_FWP_WRONG_SESSION         ((NTSTATUS)0xC022000CL)
#endif//STATUS_FWP_WRONG_SESSION

//
// MessageId: STATUS_FWP_NO_TXN_IN_PROGRESS
//
// MessageText:
//
// The call must be made from within an explicit transaction.
//
#ifndef STATUS_FWP_NO_TXN_IN_PROGRESS
#define STATUS_FWP_NO_TXN_IN_PROGRESS    ((NTSTATUS)0xC022000DL)
#endif//STATUS_FWP_NO_TXN_IN_PROGRESS

//
// MessageId: STATUS_FWP_TXN_IN_PROGRESS
//
// MessageText:
//
// The call is not allowed from within an explicit transaction.
//
#ifndef STATUS_FWP_TXN_IN_PROGRESS
#define STATUS_FWP_TXN_IN_PROGRESS       ((NTSTATUS)0xC022000EL)
#endif//STATUS_FWP_TXN_IN_PROGRESS

//
// MessageId: STATUS_FWP_TXN_ABORTED
//
// MessageText:
//
// The explicit transaction has been forcibly cancelled.
//
#ifndef STATUS_FWP_TXN_ABORTED
#define STATUS_FWP_TXN_ABORTED           ((NTSTATUS)0xC022000FL)
#endif//STATUS_FWP_TXN_ABORTED

//
// MessageId: STATUS_FWP_SESSION_ABORTED
//
// MessageText:
//
// The session has been cancelled.
//
#ifndef STATUS_FWP_SESSION_ABORTED
#define STATUS_FWP_SESSION_ABORTED       ((NTSTATUS)0xC0220010L)
#endif//STATUS_FWP_SESSION_ABORTED

//
// MessageId: STATUS_FWP_INCOMPATIBLE_TXN
//
// MessageText:
//
// The call is not allowed from within a read-only transaction.
//
#ifndef STATUS_FWP_INCOMPATIBLE_TXN
#define STATUS_FWP_INCOMPATIBLE_TXN      ((NTSTATUS)0xC0220011L)
#endif//STATUS_FWP_INCOMPATIBLE_TXN

//
// MessageId: STATUS_FWP_TIMEOUT
//
// MessageText:
//
// The call timed out while waiting to acquire the transaction lock.
//
#ifndef STATUS_FWP_TIMEOUT
#define STATUS_FWP_TIMEOUT               ((NTSTATUS)0xC0220012L)
#endif//STATUS_FWP_TIMEOUT

//
// MessageId: STATUS_FWP_NET_EVENTS_DISABLED
//
// MessageText:
//
// Collection of network diagnostic events is disabled.
//
#ifndef STATUS_FWP_NET_EVENTS_DISABLED
#define STATUS_FWP_NET_EVENTS_DISABLED   ((NTSTATUS)0xC0220013L)
#endif//STATUS_FWP_NET_EVENTS_DISABLED

//
// MessageId: STATUS_FWP_INCOMPATIBLE_LAYER
//
// MessageText:
//
// The operation is not supported by the specified layer.
//
#ifndef STATUS_FWP_INCOMPATIBLE_LAYER
#define STATUS_FWP_INCOMPATIBLE_LAYER    ((NTSTATUS)0xC0220014L)
#endif//STATUS_FWP_INCOMPATIBLE_LAYER

//
// MessageId: STATUS_FWP_KM_CLIENTS_ONLY
//
// MessageText:
//
// The call is allowed for kernel-mode callers only.
//
#ifndef STATUS_FWP_KM_CLIENTS_ONLY
#define STATUS_FWP_KM_CLIENTS_ONLY       ((NTSTATUS)0xC0220015L)
#endif//STATUS_FWP_KM_CLIENTS_ONLY

//
// MessageId: STATUS_FWP_LIFETIME_MISMATCH
//
// MessageText:
//
// The call tried to associate two objects with incompatible lifetimes.
//
#ifndef STATUS_FWP_LIFETIME_MISMATCH
#define STATUS_FWP_LIFETIME_MISMATCH     ((NTSTATUS)0xC0220016L)
#endif//STATUS_FWP_LIFETIME_MISMATCH

//
// MessageId: STATUS_FWP_BUILTIN_OBJECT
//
// MessageText:
//
// The object is built in so cannot be deleted.
//
#ifndef STATUS_FWP_BUILTIN_OBJECT
#define STATUS_FWP_BUILTIN_OBJECT        ((NTSTATUS)0xC0220017L)
#endif//STATUS_FWP_BUILTIN_OBJECT

//
// MessageId: STATUS_FWP_TOO_MANY_CALLOUTS
//
// MessageText:
//
// The maximum number of callouts has been reached.
//
#ifndef STATUS_FWP_TOO_MANY_CALLOUTS
#define STATUS_FWP_TOO_MANY_CALLOUTS     ((NTSTATUS)0xC0220018L)
#endif//STATUS_FWP_TOO_MANY_CALLOUTS

//
// MessageId: STATUS_FWP_NOTIFICATION_DROPPED
//
// MessageText:
//
// A notification could not be delivered because a message queue is at its maximum capacity.
//
#ifndef STATUS_FWP_NOTIFICATION_DROPPED
#define STATUS_FWP_NOTIFICATION_DROPPED  ((NTSTATUS)0xC0220019L)
#endif//STATUS_FWP_NOTIFICATION_DROPPED

//
// MessageId: STATUS_FWP_TRAFFIC_MISMATCH
//
// MessageText:
//
// The traffic parameters do not match those for the security association context.
//
#ifndef STATUS_FWP_TRAFFIC_MISMATCH
#define STATUS_FWP_TRAFFIC_MISMATCH      ((NTSTATUS)0xC022001AL)
#endif//STATUS_FWP_TRAFFIC_MISMATCH

//
// MessageId: STATUS_FWP_INCOMPATIBLE_SA_STATE
//
// MessageText:
//
// The call is not allowed for the current security association state.
//
#ifndef STATUS_FWP_INCOMPATIBLE_SA_STATE
#define STATUS_FWP_INCOMPATIBLE_SA_STATE ((NTSTATUS)0xC022001BL)
#endif//STATUS_FWP_INCOMPATIBLE_SA_STATE

//
// MessageId: STATUS_FWP_NULL_POINTER
//
// MessageText:
//
// A required pointer is null.
//
#ifndef STATUS_FWP_NULL_POINTER
#define STATUS_FWP_NULL_POINTER          ((NTSTATUS)0xC022001CL)
#endif//STATUS_FWP_NULL_POINTER

//
// MessageId: STATUS_FWP_INVALID_ENUMERATOR
//
// MessageText:
//
// An enumerator is not valid.
//
#ifndef STATUS_FWP_INVALID_ENUMERATOR
#define STATUS_FWP_INVALID_ENUMERATOR    ((NTSTATUS)0xC022001DL)
#endif//STATUS_FWP_INVALID_ENUMERATOR

//
// MessageId: STATUS_FWP_INVALID_FLAGS
//
// MessageText:
//
// The flags field contains an invalid value.
//
#ifndef STATUS_FWP_INVALID_FLAGS
#define STATUS_FWP_INVALID_FLAGS         ((NTSTATUS)0xC022001EL)
#endif//STATUS_FWP_INVALID_FLAGS

//
// MessageId: STATUS_FWP_INVALID_NET_MASK
//
// MessageText:
//
// A network mask is not valid.
//
#ifndef STATUS_FWP_INVALID_NET_MASK
#define STATUS_FWP_INVALID_NET_MASK      ((NTSTATUS)0xC022001FL)
#endif//STATUS_FWP_INVALID_NET_MASK

//
// MessageId: STATUS_FWP_INVALID_RANGE
//
// MessageText:
//
// An FWP_RANGE is not valid.
//
#ifndef STATUS_FWP_INVALID_RANGE
#define STATUS_FWP_INVALID_RANGE         ((NTSTATUS)0xC0220020L)
#endif//STATUS_FWP_INVALID_RANGE

//
// MessageId: STATUS_FWP_INVALID_INTERVAL
//
// MessageText:
//
// The time interval is not valid.
//
#ifndef STATUS_FWP_INVALID_INTERVAL
#define STATUS_FWP_INVALID_INTERVAL      ((NTSTATUS)0xC0220021L)
#endif//STATUS_FWP_INVALID_INTERVAL

//
// MessageId: STATUS_FWP_ZERO_LENGTH_ARRAY
//
// MessageText:
//
// An array that must contain at least one element is zero length.
//
#ifndef STATUS_FWP_ZERO_LENGTH_ARRAY
#define STATUS_FWP_ZERO_LENGTH_ARRAY     ((NTSTATUS)0xC0220022L)
#endif//STATUS_FWP_ZERO_LENGTH_ARRAY

//
// MessageId: STATUS_FWP_NULL_DISPLAY_NAME
//
// MessageText:
//
// The displayData.name field cannot be null.
//
#ifndef STATUS_FWP_NULL_DISPLAY_NAME
#define STATUS_FWP_NULL_DISPLAY_NAME     ((NTSTATUS)0xC0220023L)
#endif//STATUS_FWP_NULL_DISPLAY_NAME

//
// MessageId: STATUS_FWP_INVALID_ACTION_TYPE
//
// MessageText:
//
// The action type is not one of the allowed action types for a filter.
//
#ifndef STATUS_FWP_INVALID_ACTION_TYPE
#define STATUS_FWP_INVALID_ACTION_TYPE   ((NTSTATUS)0xC0220024L)
#endif//STATUS_FWP_INVALID_ACTION_TYPE

//
// MessageId: STATUS_FWP_INVALID_WEIGHT
//
// MessageText:
//
// The filter weight is not valid.
//
#ifndef STATUS_FWP_INVALID_WEIGHT
#define STATUS_FWP_INVALID_WEIGHT        ((NTSTATUS)0xC0220025L)
#endif//STATUS_FWP_INVALID_WEIGHT

//
// MessageId: STATUS_FWP_MATCH_TYPE_MISMATCH
//
// MessageText:
//
// A filter condition contains a match type that is not compatible with the operands.
//
#ifndef STATUS_FWP_MATCH_TYPE_MISMATCH
#define STATUS_FWP_MATCH_TYPE_MISMATCH   ((NTSTATUS)0xC0220026L)
#endif//STATUS_FWP_MATCH_TYPE_MISMATCH

//
// MessageId: STATUS_FWP_TYPE_MISMATCH
//
// MessageText:
//
// An FWP_VALUE or FWPM_CONDITION_VALUE is of the wrong type.
//
#ifndef STATUS_FWP_TYPE_MISMATCH
#define STATUS_FWP_TYPE_MISMATCH         ((NTSTATUS)0xC0220027L)
#endif//STATUS_FWP_TYPE_MISMATCH

//
// MessageId: STATUS_FWP_OUT_OF_BOUNDS
//
// MessageText:
//
// An integer value is outside the allowed range.
//
#ifndef STATUS_FWP_OUT_OF_BOUNDS
#define STATUS_FWP_OUT_OF_BOUNDS         ((NTSTATUS)0xC0220028L)
#endif//STATUS_FWP_OUT_OF_BOUNDS

//
// MessageId: STATUS_FWP_RESERVED
//
// MessageText:
//
// A reserved field is non-zero.
//
#ifndef STATUS_FWP_RESERVED
#define STATUS_FWP_RESERVED              ((NTSTATUS)0xC0220029L)
#endif//STATUS_FWP_RESERVED

//
// MessageId: STATUS_FWP_DUPLICATE_CONDITION
//
// MessageText:
//
// A filter cannot contain multiple conditions operating on a single field.
//
#ifndef STATUS_FWP_DUPLICATE_CONDITION
#define STATUS_FWP_DUPLICATE_CONDITION   ((NTSTATUS)0xC022002AL)
#endif//STATUS_FWP_DUPLICATE_CONDITION

//
// MessageId: STATUS_FWP_DUPLICATE_KEYMOD
//
// MessageText:
//
// A policy cannot contain the same keying module more than once.
//
#ifndef STATUS_FWP_DUPLICATE_KEYMOD
#define STATUS_FWP_DUPLICATE_KEYMOD      ((NTSTATUS)0xC022002BL)
#endif//STATUS_FWP_DUPLICATE_KEYMOD

//
// MessageId: STATUS_FWP_ACTION_INCOMPATIBLE_WITH_LAYER
//
// MessageText:
//
// The action type is not compatible with the layer.
//
#ifndef STATUS_FWP_ACTION_INCOMPATIBLE_WITH_LAYER
#define STATUS_FWP_ACTION_INCOMPATIBLE_WITH_LAYER ((NTSTATUS)0xC022002CL)
#endif//STATUS_FWP_ACTION_INCOMPATIBLE_WITH_LAYER

//
// MessageId: STATUS_FWP_ACTION_INCOMPATIBLE_WITH_SUBLAYER
//
// MessageText:
//
// The action type is not compatible with the sublayer.
//
#ifndef STATUS_FWP_ACTION_INCOMPATIBLE_WITH_SUBLAYER
#define STATUS_FWP_ACTION_INCOMPATIBLE_WITH_SUBLAYER ((NTSTATUS)0xC022002DL)
#endif//STATUS_FWP_ACTION_INCOMPATIBLE_WITH_SUBLAYER

//
// MessageId: STATUS_FWP_CONTEXT_INCOMPATIBLE_WITH_LAYER
//
// MessageText:
//
// The raw context or the provider context is not compatible with the layer.
//
#ifndef STATUS_FWP_CONTEXT_INCOMPATIBLE_WITH_LAYER
#define STATUS_FWP_CONTEXT_INCOMPATIBLE_WITH_LAYER ((NTSTATUS)0xC022002EL)
#endif//STATUS_FWP_CONTEXT_INCOMPATIBLE_WITH_LAYER

//
// MessageId: STATUS_FWP_CONTEXT_INCOMPATIBLE_WITH_CALLOUT
//
// MessageText:
//
// The raw context or the provider context is not compatible with the callout.
//
#ifndef STATUS_FWP_CONTEXT_INCOMPATIBLE_WITH_CALLOUT
#define STATUS_FWP_CONTEXT_INCOMPATIBLE_WITH_CALLOUT ((NTSTATUS)0xC022002FL)
#endif//STATUS_FWP_CONTEXT_INCOMPATIBLE_WITH_CALLOUT

//
// MessageId: STATUS_FWP_INCOMPATIBLE_AUTH_METHOD
//
// MessageText:
//
// The authentication method is not compatible with the policy type.
//
#ifndef STATUS_FWP_INCOMPATIBLE_AUTH_METHOD
#define STATUS_FWP_INCOMPATIBLE_AUTH_METHOD ((NTSTATUS)0xC0220030L)
#endif//STATUS_FWP_INCOMPATIBLE_AUTH_METHOD

//
// MessageId: STATUS_FWP_INCOMPATIBLE_DH_GROUP
//
// MessageText:
//
// The Diffie-Hellman group is not compatible with the policy type.
//
#ifndef STATUS_FWP_INCOMPATIBLE_DH_GROUP
#define STATUS_FWP_INCOMPATIBLE_DH_GROUP ((NTSTATUS)0xC0220031L)
#endif//STATUS_FWP_INCOMPATIBLE_DH_GROUP

//
// MessageId: STATUS_FWP_EM_NOT_SUPPORTED
//
// MessageText:
//
// An IKE policy cannot contain an Extended Mode policy.
//
#ifndef STATUS_FWP_EM_NOT_SUPPORTED
#define STATUS_FWP_EM_NOT_SUPPORTED      ((NTSTATUS)0xC0220032L)
#endif//STATUS_FWP_EM_NOT_SUPPORTED

//
// MessageId: STATUS_FWP_NEVER_MATCH
//
// MessageText:
//
// The enumeration template or subscription will never match any objects.
//
#ifndef STATUS_FWP_NEVER_MATCH
#define STATUS_FWP_NEVER_MATCH           ((NTSTATUS)0xC0220033L)
#endif//STATUS_FWP_NEVER_MATCH

//
// MessageId: STATUS_FWP_PROVIDER_CONTEXT_MISMATCH
//
// MessageText:
//
// The provider context is of the wrong type.
//
#ifndef STATUS_FWP_PROVIDER_CONTEXT_MISMATCH
#define STATUS_FWP_PROVIDER_CONTEXT_MISMATCH ((NTSTATUS)0xC0220034L)
#endif//STATUS_FWP_PROVIDER_CONTEXT_MISMATCH

//
// MessageId: STATUS_FWP_INVALID_PARAMETER
//
// MessageText:
//
// The parameter is incorrect.
//
#ifndef STATUS_FWP_INVALID_PARAMETER
#define STATUS_FWP_INVALID_PARAMETER     ((NTSTATUS)0xC0220035L)
#endif//STATUS_FWP_INVALID_PARAMETER

//
// MessageId: STATUS_FWP_TOO_MANY_SUBLAYERS
//
// MessageText:
//
// The maximum number of sublayers has been reached.
//
#ifndef STATUS_FWP_TOO_MANY_SUBLAYERS
#define STATUS_FWP_TOO_MANY_SUBLAYERS    ((NTSTATUS)0xC0220036L)
#endif//STATUS_FWP_TOO_MANY_SUBLAYERS

//
// MessageId: STATUS_FWP_CALLOUT_NOTIFICATION_FAILED
//
// MessageText:
//
// The notification function for a callout returned an error.
//
#ifndef STATUS_FWP_CALLOUT_NOTIFICATION_FAILED
#define STATUS_FWP_CALLOUT_NOTIFICATION_FAILED ((NTSTATUS)0xC0220037L)
#endif//STATUS_FWP_CALLOUT_NOTIFICATION_FAILED

//
// MessageId: STATUS_FWP_INVALID_AUTH_TRANSFORM
//
// MessageText:
//
// The IPsec authentication transform is not valid.
//
#ifndef STATUS_FWP_INVALID_AUTH_TRANSFORM
#define STATUS_FWP_INVALID_AUTH_TRANSFORM ((NTSTATUS)0xC0220038L)
#endif//STATUS_FWP_INVALID_AUTH_TRANSFORM

//
// MessageId: STATUS_FWP_INVALID_CIPHER_TRANSFORM
//
// MessageText:
//
// The IPsec cipher transform is not valid.
//
#ifndef STATUS_FWP_INVALID_CIPHER_TRANSFORM
#define STATUS_FWP_INVALID_CIPHER_TRANSFORM ((NTSTATUS)0xC0220039L)
#endif//STATUS_FWP_INVALID_CIPHER_TRANSFORM

//
// MessageId: STATUS_FWP_INCOMPATIBLE_CIPHER_TRANSFORM
//
// MessageText:
//
// The IPsec cipher transform is not compatible with the policy.
//
#ifndef STATUS_FWP_INCOMPATIBLE_CIPHER_TRANSFORM
#define STATUS_FWP_INCOMPATIBLE_CIPHER_TRANSFORM ((NTSTATUS)0xC022003AL)
#endif//STATUS_FWP_INCOMPATIBLE_CIPHER_TRANSFORM

//
// MessageId: STATUS_FWP_INVALID_TRANSFORM_COMBINATION
//
// MessageText:
//
// The combination of IPsec transform types is not valid.
//
#ifndef STATUS_FWP_INVALID_TRANSFORM_COMBINATION
#define STATUS_FWP_INVALID_TRANSFORM_COMBINATION ((NTSTATUS)0xC022003BL)
#endif//STATUS_FWP_INVALID_TRANSFORM_COMBINATION

//
// MessageId: STATUS_FWP_DUPLICATE_AUTH_METHOD
//
// MessageText:
//
// A policy cannot contain the same auth method more than once.
//
#ifndef STATUS_FWP_DUPLICATE_AUTH_METHOD
#define STATUS_FWP_DUPLICATE_AUTH_METHOD ((NTSTATUS)0xC022003CL)
#endif//STATUS_FWP_DUPLICATE_AUTH_METHOD

//
// MessageId: STATUS_FWP_INVALID_TUNNEL_ENDPOINT
//
// MessageText:
//
// A tunnel endpoint configuration is invalid.
//
#ifndef STATUS_FWP_INVALID_TUNNEL_ENDPOINT
#define STATUS_FWP_INVALID_TUNNEL_ENDPOINT ((NTSTATUS)0xC022003DL)
#endif//STATUS_FWP_INVALID_TUNNEL_ENDPOINT

//
// MessageId: STATUS_FWP_L2_DRIVER_NOT_READY
//
// MessageText:
//
// The WFP MAC Layers are not ready.
//
#ifndef STATUS_FWP_L2_DRIVER_NOT_READY
#define STATUS_FWP_L2_DRIVER_NOT_READY   ((NTSTATUS)0xC022003EL)
#endif//STATUS_FWP_L2_DRIVER_NOT_READY

//
// MessageId: STATUS_FWP_KEY_DICTATOR_ALREADY_REGISTERED
//
// MessageText:
//
// A key manager capable of key dictation is already registered
//
#ifndef STATUS_FWP_KEY_DICTATOR_ALREADY_REGISTERED
#define STATUS_FWP_KEY_DICTATOR_ALREADY_REGISTERED ((NTSTATUS)0xC022003FL)
#endif//STATUS_FWP_KEY_DICTATOR_ALREADY_REGISTERED

//
// MessageId: STATUS_FWP_KEY_DICTATION_INVALID_KEYING_MATERIAL
//
// MessageText:
//
// A key manager dictated invalid keys
//
#ifndef STATUS_FWP_KEY_DICTATION_INVALID_KEYING_MATERIAL
#define STATUS_FWP_KEY_DICTATION_INVALID_KEYING_MATERIAL ((NTSTATUS)0xC0220040L)
#endif//STATUS_FWP_KEY_DICTATION_INVALID_KEYING_MATERIAL

//
// MessageId: STATUS_FWP_CONNECTIONS_DISABLED
//
// MessageText:
//
// The BFE IPsec Connection Tracking is disabled.
//
#ifndef STATUS_FWP_CONNECTIONS_DISABLED
#define STATUS_FWP_CONNECTIONS_DISABLED  ((NTSTATUS)0xC0220041L)
#endif//STATUS_FWP_CONNECTIONS_DISABLED

//
// MessageId: STATUS_FWP_INVALID_DNS_NAME
//
// MessageText:
//
// The DNS name is invalid.
//
#ifndef STATUS_FWP_INVALID_DNS_NAME
#define STATUS_FWP_INVALID_DNS_NAME      ((NTSTATUS)0xC0220042L)
#endif//STATUS_FWP_INVALID_DNS_NAME

//
// MessageId: STATUS_FWP_STILL_ON
//
// MessageText:
//
// The engine option is still enabled due to other configuration settings.
//
#ifndef STATUS_FWP_STILL_ON
#define STATUS_FWP_STILL_ON              ((NTSTATUS)0xC0220043L)
#endif//STATUS_FWP_STILL_ON

//
// MessageId: STATUS_FWP_IKEEXT_NOT_RUNNING
//
// MessageText:
//
// The IKEEXT service is not running.  This service only runs when there is IPsec policy applied to the machine.
//
#ifndef STATUS_FWP_IKEEXT_NOT_RUNNING
#define STATUS_FWP_IKEEXT_NOT_RUNNING    ((NTSTATUS)0xC0220044L)
#endif//STATUS_FWP_IKEEXT_NOT_RUNNING

//
// MessageId: STATUS_FWP_TCPIP_NOT_READY
//
// MessageText:
//
// The TCP/IP stack is not ready.
//
#ifndef STATUS_FWP_TCPIP_NOT_READY
#define STATUS_FWP_TCPIP_NOT_READY       ((NTSTATUS)0xC0220100L)
#endif//STATUS_FWP_TCPIP_NOT_READY

//
// MessageId: STATUS_FWP_INJECT_HANDLE_CLOSING
//
// MessageText:
//
// The injection handle is being closed by another thread.
//
#ifndef STATUS_FWP_INJECT_HANDLE_CLOSING
#define STATUS_FWP_INJECT_HANDLE_CLOSING ((NTSTATUS)0xC0220101L)
#endif//STATUS_FWP_INJECT_HANDLE_CLOSING

//
// MessageId: STATUS_FWP_INJECT_HANDLE_STALE
//
// MessageText:
//
// The injection handle is stale.
//
#ifndef STATUS_FWP_INJECT_HANDLE_STALE
#define STATUS_FWP_INJECT_HANDLE_STALE   ((NTSTATUS)0xC0220102L)
#endif//STATUS_FWP_INJECT_HANDLE_STALE

//
// MessageId: STATUS_FWP_CANNOT_PEND
//
// MessageText:
//
// The classify cannot be pended.
//
#ifndef STATUS_FWP_CANNOT_PEND
#define STATUS_FWP_CANNOT_PEND           ((NTSTATUS)0xC0220103L)
#endif//STATUS_FWP_CANNOT_PEND

//
// MessageId: STATUS_FWP_DROP_NOICMP
//
// MessageText:
//
// The packet should be dropped, no ICMP should be sent.
//
#ifndef STATUS_FWP_DROP_NOICMP
#define STATUS_FWP_DROP_NOICMP           ((NTSTATUS)0xC0220104L)
#endif//STATUS_FWP_DROP_NOICMP


//
// NDIS error codes (ndis.sys)
//

//
// MessageId: STATUS_NDIS_CLOSING
//
// MessageText:
//
// The binding to the network interface is being closed.
//
#ifndef STATUS_NDIS_CLOSING
#define STATUS_NDIS_CLOSING              ((NTSTATUS)0xC0230002L)
#endif//STATUS_NDIS_CLOSING

//
// MessageId: STATUS_NDIS_BAD_VERSION
//
// MessageText:
//
// An invalid version was specified.
//
#ifndef STATUS_NDIS_BAD_VERSION
#define STATUS_NDIS_BAD_VERSION          ((NTSTATUS)0xC0230004L)
#endif//STATUS_NDIS_BAD_VERSION

//
// MessageId: STATUS_NDIS_BAD_CHARACTERISTICS
//
// MessageText:
//
// An invalid characteristics table was used.
//
#ifndef STATUS_NDIS_BAD_CHARACTERISTICS
#define STATUS_NDIS_BAD_CHARACTERISTICS  ((NTSTATUS)0xC0230005L)
#endif//STATUS_NDIS_BAD_CHARACTERISTICS

//
// MessageId: STATUS_NDIS_ADAPTER_NOT_FOUND
//
// MessageText:
//
// Failed to find the network interface or network interface is not ready.
//
#ifndef STATUS_NDIS_ADAPTER_NOT_FOUND
#define STATUS_NDIS_ADAPTER_NOT_FOUND    ((NTSTATUS)0xC0230006L)
#endif//STATUS_NDIS_ADAPTER_NOT_FOUND

//
// MessageId: STATUS_NDIS_OPEN_FAILED
//
// MessageText:
//
// Failed to open the network interface.
//
#ifndef STATUS_NDIS_OPEN_FAILED
#define STATUS_NDIS_OPEN_FAILED          ((NTSTATUS)0xC0230007L)
#endif//STATUS_NDIS_OPEN_FAILED

//
// MessageId: STATUS_NDIS_DEVICE_FAILED
//
// MessageText:
//
// Network interface has encountered an internal unrecoverable failure.
//
#ifndef STATUS_NDIS_DEVICE_FAILED
#define STATUS_NDIS_DEVICE_FAILED        ((NTSTATUS)0xC0230008L)
#endif//STATUS_NDIS_DEVICE_FAILED

//
// MessageId: STATUS_NDIS_MULTICAST_FULL
//
// MessageText:
//
// The multicast list on the network interface is full.
//
#ifndef STATUS_NDIS_MULTICAST_FULL
#define STATUS_NDIS_MULTICAST_FULL       ((NTSTATUS)0xC0230009L)
#endif//STATUS_NDIS_MULTICAST_FULL

//
// MessageId: STATUS_NDIS_MULTICAST_EXISTS
//
// MessageText:
//
// An attempt was made to add a duplicate multicast address to the list.
//
#ifndef STATUS_NDIS_MULTICAST_EXISTS
#define STATUS_NDIS_MULTICAST_EXISTS     ((NTSTATUS)0xC023000AL)
#endif//STATUS_NDIS_MULTICAST_EXISTS

//
// MessageId: STATUS_NDIS_MULTICAST_NOT_FOUND
//
// MessageText:
//
// At attempt was made to remove a multicast address that was never added.
//
#ifndef STATUS_NDIS_MULTICAST_NOT_FOUND
#define STATUS_NDIS_MULTICAST_NOT_FOUND  ((NTSTATUS)0xC023000BL)
#endif//STATUS_NDIS_MULTICAST_NOT_FOUND

//
// MessageId: STATUS_NDIS_REQUEST_ABORTED
//
// MessageText:
//
// Netowork interface aborted the request.
//
#ifndef STATUS_NDIS_REQUEST_ABORTED
#define STATUS_NDIS_REQUEST_ABORTED      ((NTSTATUS)0xC023000CL)
#endif//STATUS_NDIS_REQUEST_ABORTED

//
// MessageId: STATUS_NDIS_RESET_IN_PROGRESS
//
// MessageText:
//
// Network interface can not process the request because it is being reset.
//
#ifndef STATUS_NDIS_RESET_IN_PROGRESS
#define STATUS_NDIS_RESET_IN_PROGRESS    ((NTSTATUS)0xC023000DL)
#endif//STATUS_NDIS_RESET_IN_PROGRESS

//
// MessageId: STATUS_NDIS_NOT_SUPPORTED
//
// MessageText:
//
// Netword interface does not support this request.
//
#ifndef STATUS_NDIS_NOT_SUPPORTED
#define STATUS_NDIS_NOT_SUPPORTED        ((NTSTATUS)0xC02300BBL)
#endif//STATUS_NDIS_NOT_SUPPORTED

//
// MessageId: STATUS_NDIS_INVALID_PACKET
//
// MessageText:
//
// An attempt was made to send an invalid packet on a network interface.
//
#ifndef STATUS_NDIS_INVALID_PACKET
#define STATUS_NDIS_INVALID_PACKET       ((NTSTATUS)0xC023000FL)
#endif//STATUS_NDIS_INVALID_PACKET

//
// MessageId: STATUS_NDIS_ADAPTER_NOT_READY
//
// MessageText:
//
// Network interface is not ready to complete this operation.
//
#ifndef STATUS_NDIS_ADAPTER_NOT_READY
#define STATUS_NDIS_ADAPTER_NOT_READY    ((NTSTATUS)0xC0230011L)
#endif//STATUS_NDIS_ADAPTER_NOT_READY

//
// MessageId: STATUS_NDIS_INVALID_LENGTH
//
// MessageText:
//
// The length of the buffer submitted for this operation is not valid.
//
#ifndef STATUS_NDIS_INVALID_LENGTH
#define STATUS_NDIS_INVALID_LENGTH       ((NTSTATUS)0xC0230014L)
#endif//STATUS_NDIS_INVALID_LENGTH

//
// MessageId: STATUS_NDIS_INVALID_DATA
//
// MessageText:
//
// The data used for this operation is not valid.
//
#ifndef STATUS_NDIS_INVALID_DATA
#define STATUS_NDIS_INVALID_DATA         ((NTSTATUS)0xC0230015L)
#endif//STATUS_NDIS_INVALID_DATA

//
// MessageId: STATUS_NDIS_BUFFER_TOO_SHORT
//
// MessageText:
//
// The length of buffer submitted for this operation is too small.
//
#ifndef STATUS_NDIS_BUFFER_TOO_SHORT
#define STATUS_NDIS_BUFFER_TOO_SHORT     ((NTSTATUS)0xC0230016L)
#endif//STATUS_NDIS_BUFFER_TOO_SHORT

//
// MessageId: STATUS_NDIS_INVALID_OID
//
// MessageText:
//
// Network interface does not support this OID (Object Identifier)
//
#ifndef STATUS_NDIS_INVALID_OID
#define STATUS_NDIS_INVALID_OID          ((NTSTATUS)0xC0230017L)
#endif//STATUS_NDIS_INVALID_OID

//
// MessageId: STATUS_NDIS_ADAPTER_REMOVED
//
// MessageText:
//
// The network interface has been removed.
//
#ifndef STATUS_NDIS_ADAPTER_REMOVED
#define STATUS_NDIS_ADAPTER_REMOVED      ((NTSTATUS)0xC0230018L)
#endif//STATUS_NDIS_ADAPTER_REMOVED

//
// MessageId: STATUS_NDIS_UNSUPPORTED_MEDIA
//
// MessageText:
//
// Network interface does not support this media type.
//
#ifndef STATUS_NDIS_UNSUPPORTED_MEDIA
#define STATUS_NDIS_UNSUPPORTED_MEDIA    ((NTSTATUS)0xC0230019L)
#endif//STATUS_NDIS_UNSUPPORTED_MEDIA

//
// MessageId: STATUS_NDIS_GROUP_ADDRESS_IN_USE
//
// MessageText:
//
// An attempt was made to remove a token ring group address that is in use by other components.
//
#ifndef STATUS_NDIS_GROUP_ADDRESS_IN_USE
#define STATUS_NDIS_GROUP_ADDRESS_IN_USE ((NTSTATUS)0xC023001AL)
#endif//STATUS_NDIS_GROUP_ADDRESS_IN_USE

//
// MessageId: STATUS_NDIS_FILE_NOT_FOUND
//
// MessageText:
//
// An attempt was made to map a file that can not be found.
//
#ifndef STATUS_NDIS_FILE_NOT_FOUND
#define STATUS_NDIS_FILE_NOT_FOUND       ((NTSTATUS)0xC023001BL)
#endif//STATUS_NDIS_FILE_NOT_FOUND

//
// MessageId: STATUS_NDIS_ERROR_READING_FILE
//
// MessageText:
//
// An error occurred while NDIS tried to map the file.
//
#ifndef STATUS_NDIS_ERROR_READING_FILE
#define STATUS_NDIS_ERROR_READING_FILE   ((NTSTATUS)0xC023001CL)
#endif//STATUS_NDIS_ERROR_READING_FILE

//
// MessageId: STATUS_NDIS_ALREADY_MAPPED
//
// MessageText:
//
// An attempt was made to map a file that is alreay mapped.
//
#ifndef STATUS_NDIS_ALREADY_MAPPED
#define STATUS_NDIS_ALREADY_MAPPED       ((NTSTATUS)0xC023001DL)
#endif//STATUS_NDIS_ALREADY_MAPPED

//
// MessageId: STATUS_NDIS_RESOURCE_CONFLICT
//
// MessageText:
//
// An attempt to allocate a hardware resource failed because the resource is used by another component.
//
#ifndef STATUS_NDIS_RESOURCE_CONFLICT
#define STATUS_NDIS_RESOURCE_CONFLICT    ((NTSTATUS)0xC023001EL)
#endif//STATUS_NDIS_RESOURCE_CONFLICT

//
// MessageId: STATUS_NDIS_MEDIA_DISCONNECTED
//
// MessageText:
//
// The I/O operation failed because network media is disconnected or wireless access point is out of range.
//
#ifndef STATUS_NDIS_MEDIA_DISCONNECTED
#define STATUS_NDIS_MEDIA_DISCONNECTED   ((NTSTATUS)0xC023001FL)
#endif//STATUS_NDIS_MEDIA_DISCONNECTED

//
// MessageId: STATUS_NDIS_INVALID_ADDRESS
//
// MessageText:
//
// The network address used in the request is invalid.
//
#ifndef STATUS_NDIS_INVALID_ADDRESS
#define STATUS_NDIS_INVALID_ADDRESS      ((NTSTATUS)0xC0230022L)
#endif//STATUS_NDIS_INVALID_ADDRESS

//
// MessageId: STATUS_NDIS_INVALID_DEVICE_REQUEST
//
// MessageText:
//
// The specified request is not a valid operation for the target device.
//
#ifndef STATUS_NDIS_INVALID_DEVICE_REQUEST
#define STATUS_NDIS_INVALID_DEVICE_REQUEST ((NTSTATUS)0xC0230010L)
#endif//STATUS_NDIS_INVALID_DEVICE_REQUEST

//
// MessageId: STATUS_NDIS_PAUSED
//
// MessageText:
//
// The offload operation on the network interface has been paused.
//
#ifndef STATUS_NDIS_PAUSED
#define STATUS_NDIS_PAUSED               ((NTSTATUS)0xC023002AL)
#endif//STATUS_NDIS_PAUSED

//
// MessageId: STATUS_NDIS_INTERFACE_NOT_FOUND
//
// MessageText:
//
// Network interface was not found.
//
#ifndef STATUS_NDIS_INTERFACE_NOT_FOUND
#define STATUS_NDIS_INTERFACE_NOT_FOUND  ((NTSTATUS)0xC023002BL)
#endif//STATUS_NDIS_INTERFACE_NOT_FOUND

//
// MessageId: STATUS_NDIS_UNSUPPORTED_REVISION
//
// MessageText:
//
// The revision number specified in the structure is not supported.
//
#ifndef STATUS_NDIS_UNSUPPORTED_REVISION
#define STATUS_NDIS_UNSUPPORTED_REVISION ((NTSTATUS)0xC023002CL)
#endif//STATUS_NDIS_UNSUPPORTED_REVISION

//
// MessageId: STATUS_NDIS_INVALID_PORT
//
// MessageText:
//
// The specified port does not exist on this network interface.
//
#ifndef STATUS_NDIS_INVALID_PORT
#define STATUS_NDIS_INVALID_PORT         ((NTSTATUS)0xC023002DL)
#endif//STATUS_NDIS_INVALID_PORT

//
// MessageId: STATUS_NDIS_INVALID_PORT_STATE
//
// MessageText:
//
// The current state of the specified port on this network interface does not support the requested operation.
//
#ifndef STATUS_NDIS_INVALID_PORT_STATE
#define STATUS_NDIS_INVALID_PORT_STATE   ((NTSTATUS)0xC023002EL)
#endif//STATUS_NDIS_INVALID_PORT_STATE

//
// MessageId: STATUS_NDIS_LOW_POWER_STATE
//
// MessageText:
//
// The miniport adapter is in lower power state.
//
#ifndef STATUS_NDIS_LOW_POWER_STATE
#define STATUS_NDIS_LOW_POWER_STATE      ((NTSTATUS)0xC023002FL)
#endif//STATUS_NDIS_LOW_POWER_STATE

//
// MessageId: STATUS_NDIS_REINIT_REQUIRED
//
// MessageText:
//
// This operation requires the miniport adapter to be reinitialized.
//
#ifndef STATUS_NDIS_REINIT_REQUIRED
#define STATUS_NDIS_REINIT_REQUIRED      ((NTSTATUS)0xC0230030L)
#endif//STATUS_NDIS_REINIT_REQUIRED


//
// NDIS error codes (802.11 wireless LAN)
//

//
// MessageId: STATUS_NDIS_DOT11_AUTO_CONFIG_ENABLED
//
// MessageText:
//
// The wireless local area network interface is in auto configuration mode and doesn't support the requested parameter change operation.
//
#ifndef STATUS_NDIS_DOT11_AUTO_CONFIG_ENABLED
#define STATUS_NDIS_DOT11_AUTO_CONFIG_ENABLED ((NTSTATUS)0xC0232000L)
#endif//STATUS_NDIS_DOT11_AUTO_CONFIG_ENABLED

//
// MessageId: STATUS_NDIS_DOT11_MEDIA_IN_USE
//
// MessageText:
//
// The wireless local area network interface is busy and can not perform the requested operation.
//
#ifndef STATUS_NDIS_DOT11_MEDIA_IN_USE
#define STATUS_NDIS_DOT11_MEDIA_IN_USE   ((NTSTATUS)0xC0232001L)
#endif//STATUS_NDIS_DOT11_MEDIA_IN_USE

//
// MessageId: STATUS_NDIS_DOT11_POWER_STATE_INVALID
//
// MessageText:
//
// The wireless local area network interface is powered down and doesn't support the requested operation.
//
#ifndef STATUS_NDIS_DOT11_POWER_STATE_INVALID
#define STATUS_NDIS_DOT11_POWER_STATE_INVALID ((NTSTATUS)0xC0232002L)
#endif//STATUS_NDIS_DOT11_POWER_STATE_INVALID

//
// MessageId: STATUS_NDIS_PM_WOL_PATTERN_LIST_FULL
//
// MessageText:
//
// The list of wake on LAN patterns is full.
//
#ifndef STATUS_NDIS_PM_WOL_PATTERN_LIST_FULL
#define STATUS_NDIS_PM_WOL_PATTERN_LIST_FULL ((NTSTATUS)0xC0232003L)
#endif//STATUS_NDIS_PM_WOL_PATTERN_LIST_FULL

//
// MessageId: STATUS_NDIS_PM_PROTOCOL_OFFLOAD_LIST_FULL
//
// MessageText:
//
// The list of low power protocol offloads is full.
//
#ifndef STATUS_NDIS_PM_PROTOCOL_OFFLOAD_LIST_FULL
#define STATUS_NDIS_PM_PROTOCOL_OFFLOAD_LIST_FULL ((NTSTATUS)0xC0232004L)
#endif//STATUS_NDIS_PM_PROTOCOL_OFFLOAD_LIST_FULL

//
// MessageId: STATUS_NDIS_DOT11_AP_CHANNEL_CURRENTLY_NOT_AVAILABLE
//
// MessageText:
//
// The wireless local area network interface cannot start an AP on the specified channel right now.
//
#ifndef STATUS_NDIS_DOT11_AP_CHANNEL_CURRENTLY_NOT_AVAILABLE
#define STATUS_NDIS_DOT11_AP_CHANNEL_CURRENTLY_NOT_AVAILABLE ((NTSTATUS)0xC0232005L)
#endif//STATUS_NDIS_DOT11_AP_CHANNEL_CURRENTLY_NOT_AVAILABLE

//
// MessageId: STATUS_NDIS_DOT11_AP_BAND_CURRENTLY_NOT_AVAILABLE
//
// MessageText:
//
// The wireless local area network interface cannot start an AP on the specified band right now.
//
#ifndef STATUS_NDIS_DOT11_AP_BAND_CURRENTLY_NOT_AVAILABLE
#define STATUS_NDIS_DOT11_AP_BAND_CURRENTLY_NOT_AVAILABLE ((NTSTATUS)0xC0232006L)
#endif//STATUS_NDIS_DOT11_AP_BAND_CURRENTLY_NOT_AVAILABLE

//
// MessageId: STATUS_NDIS_DOT11_AP_CHANNEL_NOT_ALLOWED
//
// MessageText:
//
// The wireless local area network interface cannot start an AP on this channel due to regulatory reasons.
//
#ifndef STATUS_NDIS_DOT11_AP_CHANNEL_NOT_ALLOWED
#define STATUS_NDIS_DOT11_AP_CHANNEL_NOT_ALLOWED ((NTSTATUS)0xC0232007L)
#endif//STATUS_NDIS_DOT11_AP_CHANNEL_NOT_ALLOWED

//
// MessageId: STATUS_NDIS_DOT11_AP_BAND_NOT_ALLOWED
//
// MessageText:
//
// The wireless local area network interface cannot start an AP on this band due to regulatory reasons.
//
#ifndef STATUS_NDIS_DOT11_AP_BAND_NOT_ALLOWED
#define STATUS_NDIS_DOT11_AP_BAND_NOT_ALLOWED ((NTSTATUS)0xC0232008L)
#endif//STATUS_NDIS_DOT11_AP_BAND_NOT_ALLOWED

//
// NDIS informational codes(ndis.sys)
//

//
// MessageId: STATUS_NDIS_INDICATION_REQUIRED
//
// MessageText:
//
// The request will be completed later by NDIS status indication.
//
#ifndef STATUS_NDIS_INDICATION_REQUIRED
#define STATUS_NDIS_INDICATION_REQUIRED  ((NTSTATUS)0x40230001L)
#endif//STATUS_NDIS_INDICATION_REQUIRED

//
// NDIS Chimney Offload codes (ndis.sys)
//

//
// MessageId: STATUS_NDIS_OFFLOAD_POLICY
//
// MessageText:
//
// The TCP connection is not offloadable because of a local policy setting.
//
#ifndef STATUS_NDIS_OFFLOAD_POLICY
#define STATUS_NDIS_OFFLOAD_POLICY       ((NTSTATUS)0xC023100FL)
#endif//STATUS_NDIS_OFFLOAD_POLICY

//
// MessageId: STATUS_NDIS_OFFLOAD_CONNECTION_REJECTED
//
// MessageText:
//
// The TCP connection is not offloadable by the Chimney offload target.
//
#ifndef STATUS_NDIS_OFFLOAD_CONNECTION_REJECTED
#define STATUS_NDIS_OFFLOAD_CONNECTION_REJECTED ((NTSTATUS)0xC0231012L)
#endif//STATUS_NDIS_OFFLOAD_CONNECTION_REJECTED

//
// MessageId: STATUS_NDIS_OFFLOAD_PATH_REJECTED
//
// MessageText:
//
// The IP Path object is not in an offloadable state.
//
#ifndef STATUS_NDIS_OFFLOAD_PATH_REJECTED
#define STATUS_NDIS_OFFLOAD_PATH_REJECTED ((NTSTATUS)0xC0231013L)
#endif//STATUS_NDIS_OFFLOAD_PATH_REJECTED

//
// TPM hardware errors {0x0000..0x003ff}
//
//
// MessageId: STATUS_TPM_ERROR_MASK
//
// MessageText:
//
// This is an error mask to convert TPM hardware errors to win errors.
//
#ifndef STATUS_TPM_ERROR_MASK
#define STATUS_TPM_ERROR_MASK            ((NTSTATUS)0xC0290000L)
#endif//STATUS_TPM_ERROR_MASK

//
// MessageId: STATUS_TPM_AUTHFAIL
//
// MessageText:
//
// Authentication failed.
//
#ifndef STATUS_TPM_AUTHFAIL
#define STATUS_TPM_AUTHFAIL              ((NTSTATUS)0xC0290001L)
#endif//STATUS_TPM_AUTHFAIL

//
// MessageId: STATUS_TPM_BADINDEX
//
// MessageText:
//
// The index to a PCR, DIR or other register is incorrect.
//
#ifndef STATUS_TPM_BADINDEX
#define STATUS_TPM_BADINDEX              ((NTSTATUS)0xC0290002L)
#endif//STATUS_TPM_BADINDEX

//
// MessageId: STATUS_TPM_BAD_PARAMETER
//
// MessageText:
//
// One or more parameter is bad.
//
#ifndef STATUS_TPM_BAD_PARAMETER
#define STATUS_TPM_BAD_PARAMETER         ((NTSTATUS)0xC0290003L)
#endif//STATUS_TPM_BAD_PARAMETER

//
// MessageId: STATUS_TPM_AUDITFAILURE
//
// MessageText:
//
// An operation completed successfully but the auditing of that operation failed.
//
#ifndef STATUS_TPM_AUDITFAILURE
#define STATUS_TPM_AUDITFAILURE          ((NTSTATUS)0xC0290004L)
#endif//STATUS_TPM_AUDITFAILURE

//
// MessageId: STATUS_TPM_CLEAR_DISABLED
//
// MessageText:
//
// The clear disable flag is set and all clear operations now require physical access.
//
#ifndef STATUS_TPM_CLEAR_DISABLED
#define STATUS_TPM_CLEAR_DISABLED        ((NTSTATUS)0xC0290005L)
#endif//STATUS_TPM_CLEAR_DISABLED

//
// MessageId: STATUS_TPM_DEACTIVATED
//
// MessageText:
//
// Activate the Trusted Platform Module (TPM).
//
#ifndef STATUS_TPM_DEACTIVATED
#define STATUS_TPM_DEACTIVATED           ((NTSTATUS)0xC0290006L)
#endif//STATUS_TPM_DEACTIVATED

//
// MessageId: STATUS_TPM_DISABLED
//
// MessageText:
//
// Enable the Trusted Platform Module (TPM).
//
#ifndef STATUS_TPM_DISABLED
#define STATUS_TPM_DISABLED              ((NTSTATUS)0xC0290007L)
#endif//STATUS_TPM_DISABLED

//
// MessageId: STATUS_TPM_DISABLED_CMD
//
// MessageText:
//
// The target command has been disabled.
//
#ifndef STATUS_TPM_DISABLED_CMD
#define STATUS_TPM_DISABLED_CMD          ((NTSTATUS)0xC0290008L)
#endif//STATUS_TPM_DISABLED_CMD

//
// MessageId: STATUS_TPM_FAIL
//
// MessageText:
//
// The operation failed.
//
#ifndef STATUS_TPM_FAIL
#define STATUS_TPM_FAIL                  ((NTSTATUS)0xC0290009L)
#endif//STATUS_TPM_FAIL

//
// MessageId: STATUS_TPM_BAD_ORDINAL
//
// MessageText:
//
// The ordinal was unknown or inconsistent.
//
#ifndef STATUS_TPM_BAD_ORDINAL
#define STATUS_TPM_BAD_ORDINAL           ((NTSTATUS)0xC029000AL)
#endif//STATUS_TPM_BAD_ORDINAL

//
// MessageId: STATUS_TPM_INSTALL_DISABLED
//
// MessageText:
//
// The ability to install an owner is disabled.
//
#ifndef STATUS_TPM_INSTALL_DISABLED
#define STATUS_TPM_INSTALL_DISABLED      ((NTSTATUS)0xC029000BL)
#endif//STATUS_TPM_INSTALL_DISABLED

//
// MessageId: STATUS_TPM_INVALID_KEYHANDLE
//
// MessageText:
//
// The key handle cannot be interpreted.
//
#ifndef STATUS_TPM_INVALID_KEYHANDLE
#define STATUS_TPM_INVALID_KEYHANDLE     ((NTSTATUS)0xC029000CL)
#endif//STATUS_TPM_INVALID_KEYHANDLE

//
// MessageId: STATUS_TPM_KEYNOTFOUND
//
// MessageText:
//
// The key handle points to an invalid key.
//
#ifndef STATUS_TPM_KEYNOTFOUND
#define STATUS_TPM_KEYNOTFOUND           ((NTSTATUS)0xC029000DL)
#endif//STATUS_TPM_KEYNOTFOUND

//
// MessageId: STATUS_TPM_INAPPROPRIATE_ENC
//
// MessageText:
//
// Unacceptable encryption scheme.
//
#ifndef STATUS_TPM_INAPPROPRIATE_ENC
#define STATUS_TPM_INAPPROPRIATE_ENC     ((NTSTATUS)0xC029000EL)
#endif//STATUS_TPM_INAPPROPRIATE_ENC

//
// MessageId: STATUS_TPM_MIGRATEFAIL
//
// MessageText:
//
// Migration authorization failed.
//
#ifndef STATUS_TPM_MIGRATEFAIL
#define STATUS_TPM_MIGRATEFAIL           ((NTSTATUS)0xC029000FL)
#endif//STATUS_TPM_MIGRATEFAIL

//
// MessageId: STATUS_TPM_INVALID_PCR_INFO
//
// MessageText:
//
// PCR information could not be interpreted.
//
#ifndef STATUS_TPM_INVALID_PCR_INFO
#define STATUS_TPM_INVALID_PCR_INFO      ((NTSTATUS)0xC0290010L)
#endif//STATUS_TPM_INVALID_PCR_INFO

//
// MessageId: STATUS_TPM_NOSPACE
//
// MessageText:
//
// No room to load key.
//
#ifndef STATUS_TPM_NOSPACE
#define STATUS_TPM_NOSPACE               ((NTSTATUS)0xC0290011L)
#endif//STATUS_TPM_NOSPACE

//
// MessageId: STATUS_TPM_NOSRK
//
// MessageText:
//
// There is no Storage Root Key (SRK) set.
//
#ifndef STATUS_TPM_NOSRK
#define STATUS_TPM_NOSRK                 ((NTSTATUS)0xC0290012L)
#endif//STATUS_TPM_NOSRK

//
// MessageId: STATUS_TPM_NOTSEALED_BLOB
//
// MessageText:
//
// An encrypted blob is invalid or was not created by this TPM.
//
#ifndef STATUS_TPM_NOTSEALED_BLOB
#define STATUS_TPM_NOTSEALED_BLOB        ((NTSTATUS)0xC0290013L)
#endif//STATUS_TPM_NOTSEALED_BLOB

//
// MessageId: STATUS_TPM_OWNER_SET
//
// MessageText:
//
// The Trusted Platform Module (TPM) already has an owner.
//
#ifndef STATUS_TPM_OWNER_SET
#define STATUS_TPM_OWNER_SET             ((NTSTATUS)0xC0290014L)
#endif//STATUS_TPM_OWNER_SET

//
// MessageId: STATUS_TPM_RESOURCES
//
// MessageText:
//
// The TPM has insufficient internal resources to perform the requested action.
//
#ifndef STATUS_TPM_RESOURCES
#define STATUS_TPM_RESOURCES             ((NTSTATUS)0xC0290015L)
#endif//STATUS_TPM_RESOURCES

//
// MessageId: STATUS_TPM_SHORTRANDOM
//
// MessageText:
//
// A random string was too short.
//
#ifndef STATUS_TPM_SHORTRANDOM
#define STATUS_TPM_SHORTRANDOM           ((NTSTATUS)0xC0290016L)
#endif//STATUS_TPM_SHORTRANDOM

//
// MessageId: STATUS_TPM_SIZE
//
// MessageText:
//
// The TPM does not have the space to perform the operation.
//
#ifndef STATUS_TPM_SIZE
#define STATUS_TPM_SIZE                  ((NTSTATUS)0xC0290017L)
#endif//STATUS_TPM_SIZE

//
// MessageId: STATUS_TPM_WRONGPCRVAL
//
// MessageText:
//
// The named PCR value does not match the current PCR value.
//
#ifndef STATUS_TPM_WRONGPCRVAL
#define STATUS_TPM_WRONGPCRVAL           ((NTSTATUS)0xC0290018L)
#endif//STATUS_TPM_WRONGPCRVAL

//
// MessageId: STATUS_TPM_BAD_PARAM_SIZE
//
// MessageText:
//
// The paramSize argument to the command has the incorrect value .
//
#ifndef STATUS_TPM_BAD_PARAM_SIZE
#define STATUS_TPM_BAD_PARAM_SIZE        ((NTSTATUS)0xC0290019L)
#endif//STATUS_TPM_BAD_PARAM_SIZE

//
// MessageId: STATUS_TPM_SHA_THREAD
//
// MessageText:
//
// There is no existing SHA-1 thread.
//
#ifndef STATUS_TPM_SHA_THREAD
#define STATUS_TPM_SHA_THREAD            ((NTSTATUS)0xC029001AL)
#endif//STATUS_TPM_SHA_THREAD

//
// MessageId: STATUS_TPM_SHA_ERROR
//
// MessageText:
//
// The calculation is unable to proceed because the existing SHA-1 thread has already encountered an error.
//
#ifndef STATUS_TPM_SHA_ERROR
#define STATUS_TPM_SHA_ERROR             ((NTSTATUS)0xC029001BL)
#endif//STATUS_TPM_SHA_ERROR

//
// MessageId: STATUS_TPM_FAILEDSELFTEST
//
// MessageText:
//
// The TPM hardware device reported a failure during its internal self test. Try restarting the computer to resolve the problem. If the problem continues, you might need to replace your TPM hardware or motherboard.
//
#ifndef STATUS_TPM_FAILEDSELFTEST
#define STATUS_TPM_FAILEDSELFTEST        ((NTSTATUS)0xC029001CL)
#endif//STATUS_TPM_FAILEDSELFTEST

//
// MessageId: STATUS_TPM_AUTH2FAIL
//
// MessageText:
//
// The authorization for the second key in a 2 key function failed authorization.
//
#ifndef STATUS_TPM_AUTH2FAIL
#define STATUS_TPM_AUTH2FAIL             ((NTSTATUS)0xC029001DL)
#endif//STATUS_TPM_AUTH2FAIL

//
// MessageId: STATUS_TPM_BADTAG
//
// MessageText:
//
// The tag value sent to for a command is invalid.
//
#ifndef STATUS_TPM_BADTAG
#define STATUS_TPM_BADTAG                ((NTSTATUS)0xC029001EL)
#endif//STATUS_TPM_BADTAG

//
// MessageId: STATUS_TPM_IOERROR
//
// MessageText:
//
// An IO error occurred transmitting information to the TPM.
//
#ifndef STATUS_TPM_IOERROR
#define STATUS_TPM_IOERROR               ((NTSTATUS)0xC029001FL)
#endif//STATUS_TPM_IOERROR

//
// MessageId: STATUS_TPM_ENCRYPT_ERROR
//
// MessageText:
//
// The encryption process had a problem.
//
#ifndef STATUS_TPM_ENCRYPT_ERROR
#define STATUS_TPM_ENCRYPT_ERROR         ((NTSTATUS)0xC0290020L)
#endif//STATUS_TPM_ENCRYPT_ERROR

//
// MessageId: STATUS_TPM_DECRYPT_ERROR
//
// MessageText:
//
// The decryption process did not complete.
//
#ifndef STATUS_TPM_DECRYPT_ERROR
#define STATUS_TPM_DECRYPT_ERROR         ((NTSTATUS)0xC0290021L)
#endif//STATUS_TPM_DECRYPT_ERROR

//
// MessageId: STATUS_TPM_INVALID_AUTHHANDLE
//
// MessageText:
//
// An invalid handle was used.
//
#ifndef STATUS_TPM_INVALID_AUTHHANDLE
#define STATUS_TPM_INVALID_AUTHHANDLE    ((NTSTATUS)0xC0290022L)
#endif//STATUS_TPM_INVALID_AUTHHANDLE

//
// MessageId: STATUS_TPM_NO_ENDORSEMENT
//
// MessageText:
//
// The TPM does not have an Endorsement Key (EK) installed.
//
#ifndef STATUS_TPM_NO_ENDORSEMENT
#define STATUS_TPM_NO_ENDORSEMENT        ((NTSTATUS)0xC0290023L)
#endif//STATUS_TPM_NO_ENDORSEMENT

//
// MessageId: STATUS_TPM_INVALID_KEYUSAGE
//
// MessageText:
//
// The usage of a key is not allowed.
//
#ifndef STATUS_TPM_INVALID_KEYUSAGE
#define STATUS_TPM_INVALID_KEYUSAGE      ((NTSTATUS)0xC0290024L)
#endif//STATUS_TPM_INVALID_KEYUSAGE

//
// MessageId: STATUS_TPM_WRONG_ENTITYTYPE
//
// MessageText:
//
// The submitted entity type is not allowed.
//
#ifndef STATUS_TPM_WRONG_ENTITYTYPE
#define STATUS_TPM_WRONG_ENTITYTYPE      ((NTSTATUS)0xC0290025L)
#endif//STATUS_TPM_WRONG_ENTITYTYPE

//
// MessageId: STATUS_TPM_INVALID_POSTINIT
//
// MessageText:
//
// The command was received in the wrong sequence relative to TPM_Init and a subsequent TPM_Startup.
//
#ifndef STATUS_TPM_INVALID_POSTINIT
#define STATUS_TPM_INVALID_POSTINIT      ((NTSTATUS)0xC0290026L)
#endif//STATUS_TPM_INVALID_POSTINIT

//
// MessageId: STATUS_TPM_INAPPROPRIATE_SIG
//
// MessageText:
//
// Signed data cannot include additional DER information.
//
#ifndef STATUS_TPM_INAPPROPRIATE_SIG
#define STATUS_TPM_INAPPROPRIATE_SIG     ((NTSTATUS)0xC0290027L)
#endif//STATUS_TPM_INAPPROPRIATE_SIG

//
// MessageId: STATUS_TPM_BAD_KEY_PROPERTY
//
// MessageText:
//
// The key properties in TPM_KEY_PARMs are not supported by this TPM.
//
#ifndef STATUS_TPM_BAD_KEY_PROPERTY
#define STATUS_TPM_BAD_KEY_PROPERTY      ((NTSTATUS)0xC0290028L)
#endif//STATUS_TPM_BAD_KEY_PROPERTY

//
// MessageId: STATUS_TPM_BAD_MIGRATION
//
// MessageText:
//
// The migration properties of this key are incorrect.
//
#ifndef STATUS_TPM_BAD_MIGRATION
#define STATUS_TPM_BAD_MIGRATION         ((NTSTATUS)0xC0290029L)
#endif//STATUS_TPM_BAD_MIGRATION

//
// MessageId: STATUS_TPM_BAD_SCHEME
//
// MessageText:
//
// The signature or encryption scheme for this key is incorrect or not permitted in this situation.
//
#ifndef STATUS_TPM_BAD_SCHEME
#define STATUS_TPM_BAD_SCHEME            ((NTSTATUS)0xC029002AL)
#endif//STATUS_TPM_BAD_SCHEME

//
// MessageId: STATUS_TPM_BAD_DATASIZE
//
// MessageText:
//
// The size of the data (or blob) parameter is bad or inconsistent with the referenced key.
//
#ifndef STATUS_TPM_BAD_DATASIZE
#define STATUS_TPM_BAD_DATASIZE          ((NTSTATUS)0xC029002BL)
#endif//STATUS_TPM_BAD_DATASIZE

//
// MessageId: STATUS_TPM_BAD_MODE
//
// MessageText:
//
// A mode parameter is bad, such as capArea or subCapArea for TPM_GetCapability, phsicalPresence parameter for TPM_PhysicalPresence, or migrationType for TPM_CreateMigrationBlob.
//
#ifndef STATUS_TPM_BAD_MODE
#define STATUS_TPM_BAD_MODE              ((NTSTATUS)0xC029002CL)
#endif//STATUS_TPM_BAD_MODE

//
// MessageId: STATUS_TPM_BAD_PRESENCE
//
// MessageText:
//
// Either the physicalPresence or physicalPresenceLock bits have the wrong value.
//
#ifndef STATUS_TPM_BAD_PRESENCE
#define STATUS_TPM_BAD_PRESENCE          ((NTSTATUS)0xC029002DL)
#endif//STATUS_TPM_BAD_PRESENCE

//
// MessageId: STATUS_TPM_BAD_VERSION
//
// MessageText:
//
// The TPM cannot perform this version of the capability.
//
#ifndef STATUS_TPM_BAD_VERSION
#define STATUS_TPM_BAD_VERSION           ((NTSTATUS)0xC029002EL)
#endif//STATUS_TPM_BAD_VERSION

//
// MessageId: STATUS_TPM_NO_WRAP_TRANSPORT
//
// MessageText:
//
// The TPM does not allow for wrapped transport sessions.
//
#ifndef STATUS_TPM_NO_WRAP_TRANSPORT
#define STATUS_TPM_NO_WRAP_TRANSPORT     ((NTSTATUS)0xC029002FL)
#endif//STATUS_TPM_NO_WRAP_TRANSPORT

//
// MessageId: STATUS_TPM_AUDITFAIL_UNSUCCESSFUL
//
// MessageText:
//
// TPM audit construction failed and the underlying command was returning a failure code also.
//
#ifndef STATUS_TPM_AUDITFAIL_UNSUCCESSFUL
#define STATUS_TPM_AUDITFAIL_UNSUCCESSFUL ((NTSTATUS)0xC0290030L)
#endif//STATUS_TPM_AUDITFAIL_UNSUCCESSFUL

//
// MessageId: STATUS_TPM_AUDITFAIL_SUCCESSFUL
//
// MessageText:
//
// TPM audit construction failed and the underlying command was returning success.
//
#ifndef STATUS_TPM_AUDITFAIL_SUCCESSFUL
#define STATUS_TPM_AUDITFAIL_SUCCESSFUL  ((NTSTATUS)0xC0290031L)
#endif//STATUS_TPM_AUDITFAIL_SUCCESSFUL

//
// MessageId: STATUS_TPM_NOTRESETABLE
//
// MessageText:
//
// Attempt to reset a PCR register that does not have the resettable attribute.
//
#ifndef STATUS_TPM_NOTRESETABLE
#define STATUS_TPM_NOTRESETABLE          ((NTSTATUS)0xC0290032L)
#endif//STATUS_TPM_NOTRESETABLE

//
// MessageId: STATUS_TPM_NOTLOCAL
//
// MessageText:
//
// Attempt to reset a PCR register that requires locality and locality modifier not part of command transport.
//
#ifndef STATUS_TPM_NOTLOCAL
#define STATUS_TPM_NOTLOCAL              ((NTSTATUS)0xC0290033L)
#endif//STATUS_TPM_NOTLOCAL

//
// MessageId: STATUS_TPM_BAD_TYPE
//
// MessageText:
//
// Make identity blob not properly typed.
//
#ifndef STATUS_TPM_BAD_TYPE
#define STATUS_TPM_BAD_TYPE              ((NTSTATUS)0xC0290034L)
#endif//STATUS_TPM_BAD_TYPE

//
// MessageId: STATUS_TPM_INVALID_RESOURCE
//
// MessageText:
//
// When saving context identified resource type does not match actual resource.
//
#ifndef STATUS_TPM_INVALID_RESOURCE
#define STATUS_TPM_INVALID_RESOURCE      ((NTSTATUS)0xC0290035L)
#endif//STATUS_TPM_INVALID_RESOURCE

//
// MessageId: STATUS_TPM_NOTFIPS
//
// MessageText:
//
// The TPM is attempting to execute a command only available when in FIPS mode.
//
#ifndef STATUS_TPM_NOTFIPS
#define STATUS_TPM_NOTFIPS               ((NTSTATUS)0xC0290036L)
#endif//STATUS_TPM_NOTFIPS

//
// MessageId: STATUS_TPM_INVALID_FAMILY
//
// MessageText:
//
// The command is attempting to use an invalid family ID.
//
#ifndef STATUS_TPM_INVALID_FAMILY
#define STATUS_TPM_INVALID_FAMILY        ((NTSTATUS)0xC0290037L)
#endif//STATUS_TPM_INVALID_FAMILY

//
// MessageId: STATUS_TPM_NO_NV_PERMISSION
//
// MessageText:
//
// The permission to manipulate the NV storage is not available.
//
#ifndef STATUS_TPM_NO_NV_PERMISSION
#define STATUS_TPM_NO_NV_PERMISSION      ((NTSTATUS)0xC0290038L)
#endif//STATUS_TPM_NO_NV_PERMISSION

//
// MessageId: STATUS_TPM_REQUIRES_SIGN
//
// MessageText:
//
// The operation requires a signed command.
//
#ifndef STATUS_TPM_REQUIRES_SIGN
#define STATUS_TPM_REQUIRES_SIGN         ((NTSTATUS)0xC0290039L)
#endif//STATUS_TPM_REQUIRES_SIGN

//
// MessageId: STATUS_TPM_KEY_NOTSUPPORTED
//
// MessageText:
//
// Wrong operation to load an NV key.
//
#ifndef STATUS_TPM_KEY_NOTSUPPORTED
#define STATUS_TPM_KEY_NOTSUPPORTED      ((NTSTATUS)0xC029003AL)
#endif//STATUS_TPM_KEY_NOTSUPPORTED

//
// MessageId: STATUS_TPM_AUTH_CONFLICT
//
// MessageText:
//
// NV_LoadKey blob requires both owner and blob authorization.
//
#ifndef STATUS_TPM_AUTH_CONFLICT
#define STATUS_TPM_AUTH_CONFLICT         ((NTSTATUS)0xC029003BL)
#endif//STATUS_TPM_AUTH_CONFLICT

//
// MessageId: STATUS_TPM_AREA_LOCKED
//
// MessageText:
//
// The NV area is locked and not writtable.
//
#ifndef STATUS_TPM_AREA_LOCKED
#define STATUS_TPM_AREA_LOCKED           ((NTSTATUS)0xC029003CL)
#endif//STATUS_TPM_AREA_LOCKED

//
// MessageId: STATUS_TPM_BAD_LOCALITY
//
// MessageText:
//
// The locality is incorrect for the attempted operation.
//
#ifndef STATUS_TPM_BAD_LOCALITY
#define STATUS_TPM_BAD_LOCALITY          ((NTSTATUS)0xC029003DL)
#endif//STATUS_TPM_BAD_LOCALITY

//
// MessageId: STATUS_TPM_READ_ONLY
//
// MessageText:
//
// The NV area is read only and can't be written to.
//
#ifndef STATUS_TPM_READ_ONLY
#define STATUS_TPM_READ_ONLY             ((NTSTATUS)0xC029003EL)
#endif//STATUS_TPM_READ_ONLY

//
// MessageId: STATUS_TPM_PER_NOWRITE
//
// MessageText:
//
// There is no protection on the write to the NV area.
//
#ifndef STATUS_TPM_PER_NOWRITE
#define STATUS_TPM_PER_NOWRITE           ((NTSTATUS)0xC029003FL)
#endif//STATUS_TPM_PER_NOWRITE

//
// MessageId: STATUS_TPM_FAMILYCOUNT
//
// MessageText:
//
// The family count value does not match.
//
#ifndef STATUS_TPM_FAMILYCOUNT
#define STATUS_TPM_FAMILYCOUNT           ((NTSTATUS)0xC0290040L)
#endif//STATUS_TPM_FAMILYCOUNT

//
// MessageId: STATUS_TPM_WRITE_LOCKED
//
// MessageText:
//
// The NV area has already been written to.
//
#ifndef STATUS_TPM_WRITE_LOCKED
#define STATUS_TPM_WRITE_LOCKED          ((NTSTATUS)0xC0290041L)
#endif//STATUS_TPM_WRITE_LOCKED

//
// MessageId: STATUS_TPM_BAD_ATTRIBUTES
//
// MessageText:
//
// The NV area attributes conflict.
//
#ifndef STATUS_TPM_BAD_ATTRIBUTES
#define STATUS_TPM_BAD_ATTRIBUTES        ((NTSTATUS)0xC0290042L)
#endif//STATUS_TPM_BAD_ATTRIBUTES

//
// MessageId: STATUS_TPM_INVALID_STRUCTURE
//
// MessageText:
//
// The structure tag and version are invalid or inconsistent.
//
#ifndef STATUS_TPM_INVALID_STRUCTURE
#define STATUS_TPM_INVALID_STRUCTURE     ((NTSTATUS)0xC0290043L)
#endif//STATUS_TPM_INVALID_STRUCTURE

//
// MessageId: STATUS_TPM_KEY_OWNER_CONTROL
//
// MessageText:
//
// The key is under control of the TPM Owner and can only be evicted by the TPM Owner.
//
#ifndef STATUS_TPM_KEY_OWNER_CONTROL
#define STATUS_TPM_KEY_OWNER_CONTROL     ((NTSTATUS)0xC0290044L)
#endif//STATUS_TPM_KEY_OWNER_CONTROL

//
// MessageId: STATUS_TPM_BAD_COUNTER
//
// MessageText:
//
// The counter handle is incorrect.
//
#ifndef STATUS_TPM_BAD_COUNTER
#define STATUS_TPM_BAD_COUNTER           ((NTSTATUS)0xC0290045L)
#endif//STATUS_TPM_BAD_COUNTER

//
// MessageId: STATUS_TPM_NOT_FULLWRITE
//
// MessageText:
//
// The write is not a complete write of the area.
//
#ifndef STATUS_TPM_NOT_FULLWRITE
#define STATUS_TPM_NOT_FULLWRITE         ((NTSTATUS)0xC0290046L)
#endif//STATUS_TPM_NOT_FULLWRITE

//
// MessageId: STATUS_TPM_CONTEXT_GAP
//
// MessageText:
//
// The gap between saved context counts is too large.
//
#ifndef STATUS_TPM_CONTEXT_GAP
#define STATUS_TPM_CONTEXT_GAP           ((NTSTATUS)0xC0290047L)
#endif//STATUS_TPM_CONTEXT_GAP

//
// MessageId: STATUS_TPM_MAXNVWRITES
//
// MessageText:
//
// The maximum number of NV writes without an owner has been exceeded.
//
#ifndef STATUS_TPM_MAXNVWRITES
#define STATUS_TPM_MAXNVWRITES           ((NTSTATUS)0xC0290048L)
#endif//STATUS_TPM_MAXNVWRITES

//
// MessageId: STATUS_TPM_NOOPERATOR
//
// MessageText:
//
// No operator AuthData value is set.
//
#ifndef STATUS_TPM_NOOPERATOR
#define STATUS_TPM_NOOPERATOR            ((NTSTATUS)0xC0290049L)
#endif//STATUS_TPM_NOOPERATOR

//
// MessageId: STATUS_TPM_RESOURCEMISSING
//
// MessageText:
//
// The resource pointed to by context is not loaded.
//
#ifndef STATUS_TPM_RESOURCEMISSING
#define STATUS_TPM_RESOURCEMISSING       ((NTSTATUS)0xC029004AL)
#endif//STATUS_TPM_RESOURCEMISSING

//
// MessageId: STATUS_TPM_DELEGATE_LOCK
//
// MessageText:
//
// The delegate administration is locked.
//
#ifndef STATUS_TPM_DELEGATE_LOCK
#define STATUS_TPM_DELEGATE_LOCK         ((NTSTATUS)0xC029004BL)
#endif//STATUS_TPM_DELEGATE_LOCK

//
// MessageId: STATUS_TPM_DELEGATE_FAMILY
//
// MessageText:
//
// Attempt to manage a family other then the delegated family.
//
#ifndef STATUS_TPM_DELEGATE_FAMILY
#define STATUS_TPM_DELEGATE_FAMILY       ((NTSTATUS)0xC029004CL)
#endif//STATUS_TPM_DELEGATE_FAMILY

//
// MessageId: STATUS_TPM_DELEGATE_ADMIN
//
// MessageText:
//
// Delegation table management not enabled.
//
#ifndef STATUS_TPM_DELEGATE_ADMIN
#define STATUS_TPM_DELEGATE_ADMIN        ((NTSTATUS)0xC029004DL)
#endif//STATUS_TPM_DELEGATE_ADMIN

//
// MessageId: STATUS_TPM_TRANSPORT_NOTEXCLUSIVE
//
// MessageText:
//
// There was a command executed outside of an exclusive transport session.
//
#ifndef STATUS_TPM_TRANSPORT_NOTEXCLUSIVE
#define STATUS_TPM_TRANSPORT_NOTEXCLUSIVE ((NTSTATUS)0xC029004EL)
#endif//STATUS_TPM_TRANSPORT_NOTEXCLUSIVE

//
// MessageId: STATUS_TPM_OWNER_CONTROL
//
// MessageText:
//
// Attempt to context save a owner evict controlled key.
//
#ifndef STATUS_TPM_OWNER_CONTROL
#define STATUS_TPM_OWNER_CONTROL         ((NTSTATUS)0xC029004FL)
#endif//STATUS_TPM_OWNER_CONTROL

//
// MessageId: STATUS_TPM_DAA_RESOURCES
//
// MessageText:
//
// The DAA command has no resources availble to execute the command.
//
#ifndef STATUS_TPM_DAA_RESOURCES
#define STATUS_TPM_DAA_RESOURCES         ((NTSTATUS)0xC0290050L)
#endif//STATUS_TPM_DAA_RESOURCES

//
// MessageId: STATUS_TPM_DAA_INPUT_DATA0
//
// MessageText:
//
// The consistency check on DAA parameter inputData0 has failed.
//
#ifndef STATUS_TPM_DAA_INPUT_DATA0
#define STATUS_TPM_DAA_INPUT_DATA0       ((NTSTATUS)0xC0290051L)
#endif//STATUS_TPM_DAA_INPUT_DATA0

//
// MessageId: STATUS_TPM_DAA_INPUT_DATA1
//
// MessageText:
//
// The consistency check on DAA parameter inputData1 has failed.
//
#ifndef STATUS_TPM_DAA_INPUT_DATA1
#define STATUS_TPM_DAA_INPUT_DATA1       ((NTSTATUS)0xC0290052L)
#endif//STATUS_TPM_DAA_INPUT_DATA1

//
// MessageId: STATUS_TPM_DAA_ISSUER_SETTINGS
//
// MessageText:
//
// The consistency check on DAA_issuerSettings has failed.
//
#ifndef STATUS_TPM_DAA_ISSUER_SETTINGS
#define STATUS_TPM_DAA_ISSUER_SETTINGS   ((NTSTATUS)0xC0290053L)
#endif//STATUS_TPM_DAA_ISSUER_SETTINGS

//
// MessageId: STATUS_TPM_DAA_TPM_SETTINGS
//
// MessageText:
//
// The consistency check on DAA_tpmSpecific has failed.
//
#ifndef STATUS_TPM_DAA_TPM_SETTINGS
#define STATUS_TPM_DAA_TPM_SETTINGS      ((NTSTATUS)0xC0290054L)
#endif//STATUS_TPM_DAA_TPM_SETTINGS

//
// MessageId: STATUS_TPM_DAA_STAGE
//
// MessageText:
//
// The atomic process indicated by the submitted DAA command is not the expected process.
//
#ifndef STATUS_TPM_DAA_STAGE
#define STATUS_TPM_DAA_STAGE             ((NTSTATUS)0xC0290055L)
#endif//STATUS_TPM_DAA_STAGE

//
// MessageId: STATUS_TPM_DAA_ISSUER_VALIDITY
//
// MessageText:
//
// The issuer's validity check has detected an inconsistency.
//
#ifndef STATUS_TPM_DAA_ISSUER_VALIDITY
#define STATUS_TPM_DAA_ISSUER_VALIDITY   ((NTSTATUS)0xC0290056L)
#endif//STATUS_TPM_DAA_ISSUER_VALIDITY

//
// MessageId: STATUS_TPM_DAA_WRONG_W
//
// MessageText:
//
// The consistency check on w has failed.
//
#ifndef STATUS_TPM_DAA_WRONG_W
#define STATUS_TPM_DAA_WRONG_W           ((NTSTATUS)0xC0290057L)
#endif//STATUS_TPM_DAA_WRONG_W

//
// MessageId: STATUS_TPM_BAD_HANDLE
//
// MessageText:
//
// The handle is incorrect.
//
#ifndef STATUS_TPM_BAD_HANDLE
#define STATUS_TPM_BAD_HANDLE            ((NTSTATUS)0xC0290058L)
#endif//STATUS_TPM_BAD_HANDLE

//
// MessageId: STATUS_TPM_BAD_DELEGATE
//
// MessageText:
//
// Delegation is not correct.
//
#ifndef STATUS_TPM_BAD_DELEGATE
#define STATUS_TPM_BAD_DELEGATE          ((NTSTATUS)0xC0290059L)
#endif//STATUS_TPM_BAD_DELEGATE

//
// MessageId: STATUS_TPM_BADCONTEXT
//
// MessageText:
//
// The context blob is invalid.
//
#ifndef STATUS_TPM_BADCONTEXT
#define STATUS_TPM_BADCONTEXT            ((NTSTATUS)0xC029005AL)
#endif//STATUS_TPM_BADCONTEXT

//
// MessageId: STATUS_TPM_TOOMANYCONTEXTS
//
// MessageText:
//
// Too many contexts held by the TPM.
//
#ifndef STATUS_TPM_TOOMANYCONTEXTS
#define STATUS_TPM_TOOMANYCONTEXTS       ((NTSTATUS)0xC029005BL)
#endif//STATUS_TPM_TOOMANYCONTEXTS

//
// MessageId: STATUS_TPM_MA_TICKET_SIGNATURE
//
// MessageText:
//
// Migration authority signature validation failure.
//
#ifndef STATUS_TPM_MA_TICKET_SIGNATURE
#define STATUS_TPM_MA_TICKET_SIGNATURE   ((NTSTATUS)0xC029005CL)
#endif//STATUS_TPM_MA_TICKET_SIGNATURE

//
// MessageId: STATUS_TPM_MA_DESTINATION
//
// MessageText:
//
// Migration destination not authenticated.
//
#ifndef STATUS_TPM_MA_DESTINATION
#define STATUS_TPM_MA_DESTINATION        ((NTSTATUS)0xC029005DL)
#endif//STATUS_TPM_MA_DESTINATION

//
// MessageId: STATUS_TPM_MA_SOURCE
//
// MessageText:
//
// Migration source incorrect.
//
#ifndef STATUS_TPM_MA_SOURCE
#define STATUS_TPM_MA_SOURCE             ((NTSTATUS)0xC029005EL)
#endif//STATUS_TPM_MA_SOURCE

//
// MessageId: STATUS_TPM_MA_AUTHORITY
//
// MessageText:
//
// Incorrect migration authority.
//
#ifndef STATUS_TPM_MA_AUTHORITY
#define STATUS_TPM_MA_AUTHORITY          ((NTSTATUS)0xC029005FL)
#endif//STATUS_TPM_MA_AUTHORITY

//
// MessageId: STATUS_TPM_PERMANENTEK
//
// MessageText:
//
// Attempt to revoke the EK and the EK is not revocable.
//
#ifndef STATUS_TPM_PERMANENTEK
#define STATUS_TPM_PERMANENTEK           ((NTSTATUS)0xC0290061L)
#endif//STATUS_TPM_PERMANENTEK

//
// MessageId: STATUS_TPM_BAD_SIGNATURE
//
// MessageText:
//
// Bad signature of CMK ticket.
//
#ifndef STATUS_TPM_BAD_SIGNATURE
#define STATUS_TPM_BAD_SIGNATURE         ((NTSTATUS)0xC0290062L)
#endif//STATUS_TPM_BAD_SIGNATURE

//
// MessageId: STATUS_TPM_NOCONTEXTSPACE
//
// MessageText:
//
// There is no room in the context list for additional contexts.
//
#ifndef STATUS_TPM_NOCONTEXTSPACE
#define STATUS_TPM_NOCONTEXTSPACE        ((NTSTATUS)0xC0290063L)
#endif//STATUS_TPM_NOCONTEXTSPACE

//
// TPM vendor specific hardware errors {0x0400..0x04ff}
//
//
// MessageId: STATUS_TPM_COMMAND_BLOCKED
//
// MessageText:
//
// The command was blocked.
//
#ifndef STATUS_TPM_COMMAND_BLOCKED
#define STATUS_TPM_COMMAND_BLOCKED       ((NTSTATUS)0xC0290400L)
#endif//STATUS_TPM_COMMAND_BLOCKED

//
// MessageId: STATUS_TPM_INVALID_HANDLE
//
// MessageText:
//
// The specified handle was not found.
//
#ifndef STATUS_TPM_INVALID_HANDLE
#define STATUS_TPM_INVALID_HANDLE        ((NTSTATUS)0xC0290401L)
#endif//STATUS_TPM_INVALID_HANDLE

//
// MessageId: STATUS_TPM_DUPLICATE_VHANDLE
//
// MessageText:
//
// The TPM returned a duplicate handle and the command needs to be resubmitted.
//
#ifndef STATUS_TPM_DUPLICATE_VHANDLE
#define STATUS_TPM_DUPLICATE_VHANDLE     ((NTSTATUS)0xC0290402L)
#endif//STATUS_TPM_DUPLICATE_VHANDLE

//
// MessageId: STATUS_TPM_EMBEDDED_COMMAND_BLOCKED
//
// MessageText:
//
// The command within the transport was blocked.
//
#ifndef STATUS_TPM_EMBEDDED_COMMAND_BLOCKED
#define STATUS_TPM_EMBEDDED_COMMAND_BLOCKED ((NTSTATUS)0xC0290403L)
#endif//STATUS_TPM_EMBEDDED_COMMAND_BLOCKED

//
// MessageId: STATUS_TPM_EMBEDDED_COMMAND_UNSUPPORTED
//
// MessageText:
//
// The command within the transport is not supported.
//
#ifndef STATUS_TPM_EMBEDDED_COMMAND_UNSUPPORTED
#define STATUS_TPM_EMBEDDED_COMMAND_UNSUPPORTED ((NTSTATUS)0xC0290404L)
#endif//STATUS_TPM_EMBEDDED_COMMAND_UNSUPPORTED

//
// TPM non-fatal hardware errors {0x0800..0x08ff}
//
//
// MessageId: STATUS_TPM_RETRY
//
// MessageText:
//
// The TPM is too busy to respond to the command immediately, but the command could be resubmitted at a later time.
//
#ifndef STATUS_TPM_RETRY
#define STATUS_TPM_RETRY                 ((NTSTATUS)0xC0290800L)
#endif//STATUS_TPM_RETRY

//
// MessageId: STATUS_TPM_NEEDS_SELFTEST
//
// MessageText:
//
// SelfTestFull has not been run.
//
#ifndef STATUS_TPM_NEEDS_SELFTEST
#define STATUS_TPM_NEEDS_SELFTEST        ((NTSTATUS)0xC0290801L)
#endif//STATUS_TPM_NEEDS_SELFTEST

//
// MessageId: STATUS_TPM_DOING_SELFTEST
//
// MessageText:
//
// The TPM is currently executing a full selftest.
//
#ifndef STATUS_TPM_DOING_SELFTEST
#define STATUS_TPM_DOING_SELFTEST        ((NTSTATUS)0xC0290802L)
#endif//STATUS_TPM_DOING_SELFTEST

//
// MessageId: STATUS_TPM_DEFEND_LOCK_RUNNING
//
// MessageText:
//
// The TPM is defending against dictionary attacks and is in a time-out period.
//
#ifndef STATUS_TPM_DEFEND_LOCK_RUNNING
#define STATUS_TPM_DEFEND_LOCK_RUNNING   ((NTSTATUS)0xC0290803L)
#endif//STATUS_TPM_DEFEND_LOCK_RUNNING


//
// TPM software Error codes (tpm.sys)
//

//
// MessageId: STATUS_TPM_COMMAND_CANCELED
//
// MessageText:
//
// The command was cancelled.
//
#ifndef STATUS_TPM_COMMAND_CANCELED
#define STATUS_TPM_COMMAND_CANCELED      ((NTSTATUS)0xC0291001L)
#endif//STATUS_TPM_COMMAND_CANCELED

//
// MessageId: STATUS_TPM_TOO_MANY_CONTEXTS
//
// MessageText:
//
// A new TPM context could not be created because there are too many open contexts.
//
#ifndef STATUS_TPM_TOO_MANY_CONTEXTS
#define STATUS_TPM_TOO_MANY_CONTEXTS     ((NTSTATUS)0xC0291002L)
#endif//STATUS_TPM_TOO_MANY_CONTEXTS

//
// MessageId: STATUS_TPM_NOT_FOUND
//
// MessageText:
//
// TPM driver is not compatible with the version of TPM found on the system.
//
#ifndef STATUS_TPM_NOT_FOUND
#define STATUS_TPM_NOT_FOUND             ((NTSTATUS)0xC0291003L)
#endif//STATUS_TPM_NOT_FOUND

//
// MessageId: STATUS_TPM_ACCESS_DENIED
//
// MessageText:
//
// The caller does not have the appropriate rights to perform the requested operation.
//
#ifndef STATUS_TPM_ACCESS_DENIED
#define STATUS_TPM_ACCESS_DENIED         ((NTSTATUS)0xC0291004L)
#endif//STATUS_TPM_ACCESS_DENIED

//
// MessageId: STATUS_TPM_INSUFFICIENT_BUFFER
//
// MessageText:
//
// The caller does not have the appropriate rights to perform the requested operation.
//
#ifndef STATUS_TPM_INSUFFICIENT_BUFFER
#define STATUS_TPM_INSUFFICIENT_BUFFER   ((NTSTATUS)0xC0291005L)
#endif//STATUS_TPM_INSUFFICIENT_BUFFER

//
// MessageId: STATUS_TPM_PPI_FUNCTION_UNSUPPORTED
//
// MessageText:
//
// The Physical Presence Interface of this firmware does not support the requested method.
//
#ifndef STATUS_TPM_PPI_FUNCTION_UNSUPPORTED
#define STATUS_TPM_PPI_FUNCTION_UNSUPPORTED ((NTSTATUS)0xC0291006L)
#endif//STATUS_TPM_PPI_FUNCTION_UNSUPPORTED


//
// Platform Crypto Provider Error Codes (PCPKSP.dll and future platform crypto providers)
//

//
// MessageId: STATUS_PCP_ERROR_MASK
//
// MessageText:
//
// This is an error mask to convert Platform Crypto Provider errors to win errors.
//
#ifndef STATUS_PCP_ERROR_MASK
#define STATUS_PCP_ERROR_MASK            ((NTSTATUS)0xC0292000L)
#endif//STATUS_PCP_ERROR_MASK

//
// MessageId: STATUS_PCP_DEVICE_NOT_READY
//
// MessageText:
//
// The Platform Crypto Device is currently not ready. It needs to be fully provisioned to be operational.
//
#ifndef STATUS_PCP_DEVICE_NOT_READY
#define STATUS_PCP_DEVICE_NOT_READY      ((NTSTATUS)0xC0292001L)
#endif//STATUS_PCP_DEVICE_NOT_READY

//
// MessageId: STATUS_PCP_INVALID_HANDLE
//
// MessageText:
//
// The handle provided to the Platform Crypto Provider is invalid.
//
#ifndef STATUS_PCP_INVALID_HANDLE
#define STATUS_PCP_INVALID_HANDLE        ((NTSTATUS)0xC0292002L)
#endif//STATUS_PCP_INVALID_HANDLE

//
// MessageId: STATUS_PCP_INVALID_PARAMETER
//
// MessageText:
//
// A parameter provided to the Platform Crypto Provider is invalid.
//
#ifndef STATUS_PCP_INVALID_PARAMETER
#define STATUS_PCP_INVALID_PARAMETER     ((NTSTATUS)0xC0292003L)
#endif//STATUS_PCP_INVALID_PARAMETER

//
// MessageId: STATUS_PCP_FLAG_NOT_SUPPORTED
//
// MessageText:
//
// A provided flag to the Platform Crypto Provider is not supported.
//
#ifndef STATUS_PCP_FLAG_NOT_SUPPORTED
#define STATUS_PCP_FLAG_NOT_SUPPORTED    ((NTSTATUS)0xC0292004L)
#endif//STATUS_PCP_FLAG_NOT_SUPPORTED

//
// MessageId: STATUS_PCP_NOT_SUPPORTED
//
// MessageText:
//
// The requested operation is not supported by this Platform Crypto Provider.
//
#ifndef STATUS_PCP_NOT_SUPPORTED
#define STATUS_PCP_NOT_SUPPORTED         ((NTSTATUS)0xC0292005L)
#endif//STATUS_PCP_NOT_SUPPORTED

//
// MessageId: STATUS_PCP_BUFFER_TOO_SMALL
//
// MessageText:
//
// The buffer is too small to contain all data. No information has been written to the buffer.
//
#ifndef STATUS_PCP_BUFFER_TOO_SMALL
#define STATUS_PCP_BUFFER_TOO_SMALL      ((NTSTATUS)0xC0292006L)
#endif//STATUS_PCP_BUFFER_TOO_SMALL

//
// MessageId: STATUS_PCP_INTERNAL_ERROR
//
// MessageText:
//
// An unexpected internal error has occurred in the Platform Crypto Provider.
//
#ifndef STATUS_PCP_INTERNAL_ERROR
#define STATUS_PCP_INTERNAL_ERROR        ((NTSTATUS)0xC0292007L)
#endif//STATUS_PCP_INTERNAL_ERROR

//
// MessageId: STATUS_PCP_AUTHENTICATION_FAILED
//
// MessageText:
//
// The authorization to use a provider object has failed.
//
#ifndef STATUS_PCP_AUTHENTICATION_FAILED
#define STATUS_PCP_AUTHENTICATION_FAILED ((NTSTATUS)0xC0292008L)
#endif//STATUS_PCP_AUTHENTICATION_FAILED

//
// MessageId: STATUS_PCP_AUTHENTICATION_IGNORED
//
// MessageText:
//
// The Platform Crypto Device has ignored the authorization for the provider object, to mitigate against a dictionary attack.
//
#ifndef STATUS_PCP_AUTHENTICATION_IGNORED
#define STATUS_PCP_AUTHENTICATION_IGNORED ((NTSTATUS)0xC0292009L)
#endif//STATUS_PCP_AUTHENTICATION_IGNORED

//
// MessageId: STATUS_PCP_POLICY_NOT_FOUND
//
// MessageText:
//
// The referenced policy was not found.
//
#ifndef STATUS_PCP_POLICY_NOT_FOUND
#define STATUS_PCP_POLICY_NOT_FOUND      ((NTSTATUS)0xC029200AL)
#endif//STATUS_PCP_POLICY_NOT_FOUND

//
// MessageId: STATUS_PCP_PROFILE_NOT_FOUND
//
// MessageText:
//
// The referenced profile was not found.
//
#ifndef STATUS_PCP_PROFILE_NOT_FOUND
#define STATUS_PCP_PROFILE_NOT_FOUND     ((NTSTATUS)0xC029200BL)
#endif//STATUS_PCP_PROFILE_NOT_FOUND

//
// MessageId: STATUS_PCP_VALIDATION_FAILED
//
// MessageText:
//
// The validation was not succesful.
//
#ifndef STATUS_PCP_VALIDATION_FAILED
#define STATUS_PCP_VALIDATION_FAILED     ((NTSTATUS)0xC029200CL)
#endif//STATUS_PCP_VALIDATION_FAILED

//
// MessageId: STATUS_PCP_DEVICE_NOT_FOUND
//
// MessageText:
//
// A Platform Crypto Device was not found.  Operations that require a Platform Crypto Device will not be submitted.
//
#ifndef STATUS_PCP_DEVICE_NOT_FOUND
#define STATUS_PCP_DEVICE_NOT_FOUND      ((NTSTATUS)0xC029200DL)
#endif//STATUS_PCP_DEVICE_NOT_FOUND

//
// MessageId: STATUS_PCP_WRONG_PARENT
//
// MessageText:
//
// An attempt was made to import or load a key under an incorrect storage parent.
//
#ifndef STATUS_PCP_WRONG_PARENT
#define STATUS_PCP_WRONG_PARENT          ((NTSTATUS)0xC029200EL)
#endif//STATUS_PCP_WRONG_PARENT

//
// MessageId: STATUS_PCP_KEY_NOT_LOADED
//
// MessageText:
//
// The TPM key is not loaded.
//
#ifndef STATUS_PCP_KEY_NOT_LOADED
#define STATUS_PCP_KEY_NOT_LOADED        ((NTSTATUS)0xC029200FL)
#endif//STATUS_PCP_KEY_NOT_LOADED

//
// MessageId: STATUS_PCP_NO_KEY_CERTIFICATION
//
// MessageText:
//
// The TPM key certification has not been generated.
//
#ifndef STATUS_PCP_NO_KEY_CERTIFICATION
#define STATUS_PCP_NO_KEY_CERTIFICATION  ((NTSTATUS)0xC0292010L)
#endif//STATUS_PCP_NO_KEY_CERTIFICATION

//
// MessageId: STATUS_PCP_KEY_NOT_FINALIZED
//
// MessageText:
//
// The TPM key is not yet finalized.
//
#ifndef STATUS_PCP_KEY_NOT_FINALIZED
#define STATUS_PCP_KEY_NOT_FINALIZED     ((NTSTATUS)0xC0292011L)
#endif//STATUS_PCP_KEY_NOT_FINALIZED

//
// MessageId: STATUS_PCP_ATTESTATION_CHALLENGE_NOT_SET
//
// MessageText:
//
// The TPM attestation challenge is not set.
//
#ifndef STATUS_PCP_ATTESTATION_CHALLENGE_NOT_SET
#define STATUS_PCP_ATTESTATION_CHALLENGE_NOT_SET ((NTSTATUS)0xC0292012L)
#endif//STATUS_PCP_ATTESTATION_CHALLENGE_NOT_SET

//
// MessageId: STATUS_PCP_NOT_PCR_BOUND
//
// MessageText:
//
// The TPM key is not bound to PCR info.
//
#ifndef STATUS_PCP_NOT_PCR_BOUND
#define STATUS_PCP_NOT_PCR_BOUND         ((NTSTATUS)0xC0292013L)
#endif//STATUS_PCP_NOT_PCR_BOUND

//
// MessageId: STATUS_PCP_KEY_ALREADY_FINALIZED
//
// MessageText:
//
// The TPM key is already finalized.
//
#ifndef STATUS_PCP_KEY_ALREADY_FINALIZED
#define STATUS_PCP_KEY_ALREADY_FINALIZED ((NTSTATUS)0xC0292014L)
#endif//STATUS_PCP_KEY_ALREADY_FINALIZED

//
// MessageId: STATUS_PCP_KEY_USAGE_POLICY_NOT_SUPPORTED
//
// MessageText:
//
// The TPM key usage policy is not supported.
//
#ifndef STATUS_PCP_KEY_USAGE_POLICY_NOT_SUPPORTED
#define STATUS_PCP_KEY_USAGE_POLICY_NOT_SUPPORTED ((NTSTATUS)0xC0292015L)
#endif//STATUS_PCP_KEY_USAGE_POLICY_NOT_SUPPORTED

//
// MessageId: STATUS_PCP_KEY_USAGE_POLICY_INVALID
//
// MessageText:
//
// The TPM key usage policy is invalid.
//
#ifndef STATUS_PCP_KEY_USAGE_POLICY_INVALID
#define STATUS_PCP_KEY_USAGE_POLICY_INVALID ((NTSTATUS)0xC0292016L)
#endif//STATUS_PCP_KEY_USAGE_POLICY_INVALID

//
// MessageId: STATUS_PCP_SOFT_KEY_ERROR
//
// MessageText:
//
// There was a problem with the software key being imported into the TPM.
//
#ifndef STATUS_PCP_SOFT_KEY_ERROR
#define STATUS_PCP_SOFT_KEY_ERROR        ((NTSTATUS)0xC0292017L)
#endif//STATUS_PCP_SOFT_KEY_ERROR

//
// MessageId: STATUS_PCP_KEY_NOT_AUTHENTICATED
//
// MessageText:
//
// The TPM key is not authenticated.
//
#ifndef STATUS_PCP_KEY_NOT_AUTHENTICATED
#define STATUS_PCP_KEY_NOT_AUTHENTICATED ((NTSTATUS)0xC0292018L)
#endif//STATUS_PCP_KEY_NOT_AUTHENTICATED

//
// MessageId: STATUS_PCP_KEY_NOT_AIK
//
// MessageText:
//
// The TPM key is not an AIK.
//
#ifndef STATUS_PCP_KEY_NOT_AIK
#define STATUS_PCP_KEY_NOT_AIK           ((NTSTATUS)0xC0292019L)
#endif//STATUS_PCP_KEY_NOT_AIK

//
// MessageId: STATUS_PCP_KEY_NOT_SIGNING_KEY
//
// MessageText:
//
// The TPM key is not a signing key.
//
#ifndef STATUS_PCP_KEY_NOT_SIGNING_KEY
#define STATUS_PCP_KEY_NOT_SIGNING_KEY   ((NTSTATUS)0xC029201AL)
#endif//STATUS_PCP_KEY_NOT_SIGNING_KEY

//
// MessageId: STATUS_PCP_LOCKED_OUT
//
// MessageText:
//
// The TPM is locked out.
//
#ifndef STATUS_PCP_LOCKED_OUT
#define STATUS_PCP_LOCKED_OUT            ((NTSTATUS)0xC029201BL)
#endif//STATUS_PCP_LOCKED_OUT

//
// MessageId: STATUS_PCP_CLAIM_TYPE_NOT_SUPPORTED
//
// MessageText:
//
// The claim type requested is not supported.
//
#ifndef STATUS_PCP_CLAIM_TYPE_NOT_SUPPORTED
#define STATUS_PCP_CLAIM_TYPE_NOT_SUPPORTED ((NTSTATUS)0xC029201CL)
#endif//STATUS_PCP_CLAIM_TYPE_NOT_SUPPORTED

//
// MessageId: STATUS_PCP_TPM_VERSION_NOT_SUPPORTED
//
// MessageText:
//
// The current TPM version is not supported.
//
#ifndef STATUS_PCP_TPM_VERSION_NOT_SUPPORTED
#define STATUS_PCP_TPM_VERSION_NOT_SUPPORTED ((NTSTATUS)0xC029201DL)
#endif//STATUS_PCP_TPM_VERSION_NOT_SUPPORTED

//
// MessageId: STATUS_PCP_BUFFER_LENGTH_MISMATCH
//
// MessageText:
//
// The buffer lengths do not match.
//
#ifndef STATUS_PCP_BUFFER_LENGTH_MISMATCH
#define STATUS_PCP_BUFFER_LENGTH_MISMATCH ((NTSTATUS)0xC029201EL)
#endif//STATUS_PCP_BUFFER_LENGTH_MISMATCH

//
// MessageId: STATUS_PCP_IFX_RSA_KEY_CREATION_BLOCKED
//
// MessageText:
//
// The RSA key creation is blocked on this TPM due to known security vulnerabilities.
//
#ifndef STATUS_PCP_IFX_RSA_KEY_CREATION_BLOCKED
#define STATUS_PCP_IFX_RSA_KEY_CREATION_BLOCKED ((NTSTATUS)0xC029201FL)
#endif//STATUS_PCP_IFX_RSA_KEY_CREATION_BLOCKED

//
// MessageId: STATUS_PCP_TICKET_MISSING
//
// MessageText:
//
// A ticket required to use a key was not provided.
//
#ifndef STATUS_PCP_TICKET_MISSING
#define STATUS_PCP_TICKET_MISSING        ((NTSTATUS)0xC0292020L)
#endif//STATUS_PCP_TICKET_MISSING

//
// MessageId: STATUS_PCP_RAW_POLICY_NOT_SUPPORTED
//
// MessageText:
//
// This key has a raw policy so the KSP can't authenticate against it.
//
#ifndef STATUS_PCP_RAW_POLICY_NOT_SUPPORTED
#define STATUS_PCP_RAW_POLICY_NOT_SUPPORTED ((NTSTATUS)0xC0292021L)
#endif//STATUS_PCP_RAW_POLICY_NOT_SUPPORTED


//
// Remote TPM Error Codes
//

//
// MessageId: STATUS_RTPM_CONTEXT_CONTINUE
//
// MessageText:
//
// The remote TPM context exchange is not complete. The context should be transported to the target and continued.
//
#ifndef STATUS_RTPM_CONTEXT_CONTINUE
#define STATUS_RTPM_CONTEXT_CONTINUE     ((NTSTATUS)0x00293000L)
#endif//STATUS_RTPM_CONTEXT_CONTINUE

//
// MessageId: STATUS_RTPM_CONTEXT_COMPLETE
//
// MessageText:
//
// The remote TPM operation is complete.
//
#ifndef STATUS_RTPM_CONTEXT_COMPLETE
#define STATUS_RTPM_CONTEXT_COMPLETE     ((NTSTATUS)0x00293001L)
#endif//STATUS_RTPM_CONTEXT_COMPLETE

//
// MessageId: STATUS_RTPM_NO_RESULT
//
// MessageText:
//
// No result associated with this instance exists.
//
#ifndef STATUS_RTPM_NO_RESULT
#define STATUS_RTPM_NO_RESULT            ((NTSTATUS)0xC0293002L)
#endif//STATUS_RTPM_NO_RESULT

//
// MessageId: STATUS_RTPM_PCR_READ_INCOMPLETE
//
// MessageText:
//
// The TPM returned incomplete PCR results. This maybe due to an unsupported selection set. Attempt the read again with a different selection set.
//
#ifndef STATUS_RTPM_PCR_READ_INCOMPLETE
#define STATUS_RTPM_PCR_READ_INCOMPLETE  ((NTSTATUS)0xC0293003L)
#endif//STATUS_RTPM_PCR_READ_INCOMPLETE

//
// MessageId: STATUS_RTPM_INVALID_CONTEXT
//
// MessageText:
//
// The rTPM context has been corrupted. The rTPM operation must be restarted.
//
#ifndef STATUS_RTPM_INVALID_CONTEXT
#define STATUS_RTPM_INVALID_CONTEXT      ((NTSTATUS)0xC0293004L)
#endif//STATUS_RTPM_INVALID_CONTEXT

//
// MessageId: STATUS_RTPM_UNSUPPORTED_CMD
//
// MessageText:
//
// The rTPM target does not support remote processing of the specified TPM command.
//
#ifndef STATUS_RTPM_UNSUPPORTED_CMD
#define STATUS_RTPM_UNSUPPORTED_CMD      ((NTSTATUS)0xC0293005L)
#endif//STATUS_RTPM_UNSUPPORTED_CMD


//
// Misc TPM Error Codes
//

//
// MessageId: STATUS_TPM_ZERO_EXHAUST_ENABLED
//
// MessageText:
//
// TPM related network operations are blocked as Zero Exhaust mode is enabled on client.
//
#ifndef STATUS_TPM_ZERO_EXHAUST_ENABLED
#define STATUS_TPM_ZERO_EXHAUST_ENABLED  ((NTSTATUS)0xC0294000L)
#endif//STATUS_TPM_ZERO_EXHAUST_ENABLED

//
// Hypervisor error codes - changes to these codes must be reflected in HvStatus.h
//

//
// MessageId: STATUS_HV_INVALID_HYPERCALL_CODE
//
// MessageText:
//
// The hypervisor does not support the operation because the specified hypercall code is not supported.
//
#ifndef STATUS_HV_INVALID_HYPERCALL_CODE
#define STATUS_HV_INVALID_HYPERCALL_CODE ((NTSTATUS)0xC0350002L)
#endif//STATUS_HV_INVALID_HYPERCALL_CODE

//
// MessageId: STATUS_HV_INVALID_HYPERCALL_INPUT
//
// MessageText:
//
// The hypervisor does not support the operation because the encoding for the hypercall input register is not supported.
//
#ifndef STATUS_HV_INVALID_HYPERCALL_INPUT
#define STATUS_HV_INVALID_HYPERCALL_INPUT ((NTSTATUS)0xC0350003L)
#endif//STATUS_HV_INVALID_HYPERCALL_INPUT

//
// MessageId: STATUS_HV_INVALID_ALIGNMENT
//
// MessageText:
//
// The hypervisor could not perform the operation because a parameter has an invalid alignment.
//
#ifndef STATUS_HV_INVALID_ALIGNMENT
#define STATUS_HV_INVALID_ALIGNMENT      ((NTSTATUS)0xC0350004L)
#endif//STATUS_HV_INVALID_ALIGNMENT

//
// MessageId: STATUS_HV_INVALID_PARAMETER
//
// MessageText:
//
// The hypervisor could not perform the operation because an invalid parameter was specified.
//
#ifndef STATUS_HV_INVALID_PARAMETER
#define STATUS_HV_INVALID_PARAMETER      ((NTSTATUS)0xC0350005L)
#endif//STATUS_HV_INVALID_PARAMETER

//
// MessageId: STATUS_HV_ACCESS_DENIED
//
// MessageText:
//
// Access to the specified object was denied.
//
#ifndef STATUS_HV_ACCESS_DENIED
#define STATUS_HV_ACCESS_DENIED          ((NTSTATUS)0xC0350006L)
#endif//STATUS_HV_ACCESS_DENIED

//
// MessageId: STATUS_HV_INVALID_PARTITION_STATE
//
// MessageText:
//
// The hypervisor could not perform the operation because the partition is entering or in an invalid state.
//
#ifndef STATUS_HV_INVALID_PARTITION_STATE
#define STATUS_HV_INVALID_PARTITION_STATE ((NTSTATUS)0xC0350007L)
#endif//STATUS_HV_INVALID_PARTITION_STATE

//
// MessageId: STATUS_HV_OPERATION_DENIED
//
// MessageText:
//
// The operation is not allowed in the current state.
//
#ifndef STATUS_HV_OPERATION_DENIED
#define STATUS_HV_OPERATION_DENIED       ((NTSTATUS)0xC0350008L)
#endif//STATUS_HV_OPERATION_DENIED

//
// MessageId: STATUS_HV_UNKNOWN_PROPERTY
//
// MessageText:
//
// The hypervisor does not recognize the specified partition property.
//
#ifndef STATUS_HV_UNKNOWN_PROPERTY
#define STATUS_HV_UNKNOWN_PROPERTY       ((NTSTATUS)0xC0350009L)
#endif//STATUS_HV_UNKNOWN_PROPERTY

//
// MessageId: STATUS_HV_PROPERTY_VALUE_OUT_OF_RANGE
//
// MessageText:
//
// The specified value of a partition property is out of range or violates an invariant.
//
#ifndef STATUS_HV_PROPERTY_VALUE_OUT_OF_RANGE
#define STATUS_HV_PROPERTY_VALUE_OUT_OF_RANGE ((NTSTATUS)0xC035000AL)
#endif//STATUS_HV_PROPERTY_VALUE_OUT_OF_RANGE

//
// MessageId: STATUS_HV_INSUFFICIENT_MEMORY
//
// MessageText:
//
// There is not enough memory in the hypervisor pool to complete the operation.
//
#ifndef STATUS_HV_INSUFFICIENT_MEMORY
#define STATUS_HV_INSUFFICIENT_MEMORY    ((NTSTATUS)0xC035000BL)
#endif//STATUS_HV_INSUFFICIENT_MEMORY

//
// MessageId: STATUS_HV_PARTITION_TOO_DEEP
//
// MessageText:
//
// The maximum partition depth has been exceeded for the partition hierarchy.
//
#ifndef STATUS_HV_PARTITION_TOO_DEEP
#define STATUS_HV_PARTITION_TOO_DEEP     ((NTSTATUS)0xC035000CL)
#endif//STATUS_HV_PARTITION_TOO_DEEP

//
// MessageId: STATUS_HV_INVALID_PARTITION_ID
//
// MessageText:
//
// A partition with the specified partition Id does not exist.
//
#ifndef STATUS_HV_INVALID_PARTITION_ID
#define STATUS_HV_INVALID_PARTITION_ID   ((NTSTATUS)0xC035000DL)
#endif//STATUS_HV_INVALID_PARTITION_ID

//
// MessageId: STATUS_HV_INVALID_VP_INDEX
//
// MessageText:
//
// The hypervisor could not perform the operation because the specified VP index is invalid.
//
#ifndef STATUS_HV_INVALID_VP_INDEX
#define STATUS_HV_INVALID_VP_INDEX       ((NTSTATUS)0xC035000EL)
#endif//STATUS_HV_INVALID_VP_INDEX

//
// MessageId: STATUS_HV_INVALID_PORT_ID
//
// MessageText:
//
// The hypervisor could not perform the operation because the specified port identifier is invalid.
//
#ifndef STATUS_HV_INVALID_PORT_ID
#define STATUS_HV_INVALID_PORT_ID        ((NTSTATUS)0xC0350011L)
#endif//STATUS_HV_INVALID_PORT_ID

//
// MessageId: STATUS_HV_INVALID_CONNECTION_ID
//
// MessageText:
//
// The hypervisor could not perform the operation because the specified connection identifier is invalid.
//
#ifndef STATUS_HV_INVALID_CONNECTION_ID
#define STATUS_HV_INVALID_CONNECTION_ID  ((NTSTATUS)0xC0350012L)
#endif//STATUS_HV_INVALID_CONNECTION_ID

//
// MessageId: STATUS_HV_INSUFFICIENT_BUFFERS
//
// MessageText:
//
// Not enough buffers were supplied to send a message.
//
#ifndef STATUS_HV_INSUFFICIENT_BUFFERS
#define STATUS_HV_INSUFFICIENT_BUFFERS   ((NTSTATUS)0xC0350013L)
#endif//STATUS_HV_INSUFFICIENT_BUFFERS

//
// MessageId: STATUS_HV_NOT_ACKNOWLEDGED
//
// MessageText:
//
// The previous virtual interrupt has not been acknowledged.
//
#ifndef STATUS_HV_NOT_ACKNOWLEDGED
#define STATUS_HV_NOT_ACKNOWLEDGED       ((NTSTATUS)0xC0350014L)
#endif//STATUS_HV_NOT_ACKNOWLEDGED

//
// MessageId: STATUS_HV_INVALID_VP_STATE
//
// MessageText:
//
// A virtual processor is not in the correct state for the indicated operation.
//
#ifndef STATUS_HV_INVALID_VP_STATE
#define STATUS_HV_INVALID_VP_STATE       ((NTSTATUS)0xC0350015L)
#endif//STATUS_HV_INVALID_VP_STATE

//
// MessageId: STATUS_HV_ACKNOWLEDGED
//
// MessageText:
//
// The previous virtual interrupt has already been acknowledged.
//
#ifndef STATUS_HV_ACKNOWLEDGED
#define STATUS_HV_ACKNOWLEDGED           ((NTSTATUS)0xC0350016L)
#endif//STATUS_HV_ACKNOWLEDGED

//
// MessageId: STATUS_HV_INVALID_SAVE_RESTORE_STATE
//
// MessageText:
//
// The indicated partition is not in a valid state for saving or restoring.
//
#ifndef STATUS_HV_INVALID_SAVE_RESTORE_STATE
#define STATUS_HV_INVALID_SAVE_RESTORE_STATE ((NTSTATUS)0xC0350017L)
#endif//STATUS_HV_INVALID_SAVE_RESTORE_STATE

//
// MessageId: STATUS_HV_INVALID_SYNIC_STATE
//
// MessageText:
//
// The hypervisor could not complete the operation because a required feature of the synthetic interrupt controller (SynIC) was disabled.
//
#ifndef STATUS_HV_INVALID_SYNIC_STATE
#define STATUS_HV_INVALID_SYNIC_STATE    ((NTSTATUS)0xC0350018L)
#endif//STATUS_HV_INVALID_SYNIC_STATE

//
// MessageId: STATUS_HV_OBJECT_IN_USE
//
// MessageText:
//
// The hypervisor could not perform the operation because the object or value was either already in use or being used for a purpose that would not permit completing the operation.
//
#ifndef STATUS_HV_OBJECT_IN_USE
#define STATUS_HV_OBJECT_IN_USE          ((NTSTATUS)0xC0350019L)
#endif//STATUS_HV_OBJECT_IN_USE

//
// MessageId: STATUS_HV_INVALID_PROXIMITY_DOMAIN_INFO
//
// MessageText:
//
// The proximity domain information is invalid.
//
#ifndef STATUS_HV_INVALID_PROXIMITY_DOMAIN_INFO
#define STATUS_HV_INVALID_PROXIMITY_DOMAIN_INFO ((NTSTATUS)0xC035001AL)
#endif//STATUS_HV_INVALID_PROXIMITY_DOMAIN_INFO

//
// MessageId: STATUS_HV_NO_DATA
//
// MessageText:
//
// An attempt to retrieve debugging data failed because none was available.
//
#ifndef STATUS_HV_NO_DATA
#define STATUS_HV_NO_DATA                ((NTSTATUS)0xC035001BL)
#endif//STATUS_HV_NO_DATA

//
// MessageId: STATUS_HV_INACTIVE
//
// MessageText:
//
// The physical connection being used for debugging has not recorded any receive activity since the last operation.
//
#ifndef STATUS_HV_INACTIVE
#define STATUS_HV_INACTIVE               ((NTSTATUS)0xC035001CL)
#endif//STATUS_HV_INACTIVE

//
// MessageId: STATUS_HV_NO_RESOURCES
//
// MessageText:
//
// There are not enough resources to complete the operation.
//
#ifndef STATUS_HV_NO_RESOURCES
#define STATUS_HV_NO_RESOURCES           ((NTSTATUS)0xC035001DL)
#endif//STATUS_HV_NO_RESOURCES

//
// MessageId: STATUS_HV_FEATURE_UNAVAILABLE
//
// MessageText:
//
// A hypervisor feature is not available to the user.
//
#ifndef STATUS_HV_FEATURE_UNAVAILABLE
#define STATUS_HV_FEATURE_UNAVAILABLE    ((NTSTATUS)0xC035001EL)
#endif//STATUS_HV_FEATURE_UNAVAILABLE

//
// MessageId: STATUS_HV_INSUFFICIENT_BUFFER
//
// MessageText:
//
// The specified buffer was too small to contain all of the requested data.
//
#ifndef STATUS_HV_INSUFFICIENT_BUFFER
#define STATUS_HV_INSUFFICIENT_BUFFER    ((NTSTATUS)0xC0350033L)
#endif//STATUS_HV_INSUFFICIENT_BUFFER

//
// MessageId: STATUS_HV_INSUFFICIENT_DEVICE_DOMAINS
//
// MessageText:
//
// The maximum number of domains supported by the platform I/O remapping hardware is currently in use. No domains are available to assign this device to this partition.
//
#ifndef STATUS_HV_INSUFFICIENT_DEVICE_DOMAINS
#define STATUS_HV_INSUFFICIENT_DEVICE_DOMAINS ((NTSTATUS)0xC0350038L)
#endif//STATUS_HV_INSUFFICIENT_DEVICE_DOMAINS

//
// MessageId: STATUS_HV_CPUID_FEATURE_VALIDATION_ERROR
//
// MessageText:
//
// Validation of CPUID data of the processor failed.
//
#ifndef STATUS_HV_CPUID_FEATURE_VALIDATION_ERROR
#define STATUS_HV_CPUID_FEATURE_VALIDATION_ERROR ((NTSTATUS)0xC035003CL)
#endif//STATUS_HV_CPUID_FEATURE_VALIDATION_ERROR

//
// MessageId: STATUS_HV_CPUID_XSAVE_FEATURE_VALIDATION_ERROR
//
// MessageText:
//
// Validation of XSAVE CPUID data of the processor failed.
//
#ifndef STATUS_HV_CPUID_XSAVE_FEATURE_VALIDATION_ERROR
#define STATUS_HV_CPUID_XSAVE_FEATURE_VALIDATION_ERROR ((NTSTATUS)0xC035003DL)
#endif//STATUS_HV_CPUID_XSAVE_FEATURE_VALIDATION_ERROR

//
// MessageId: STATUS_HV_PROCESSOR_STARTUP_TIMEOUT
//
// MessageText:
//
// Processor did not respond within the timeout period.
//
#ifndef STATUS_HV_PROCESSOR_STARTUP_TIMEOUT
#define STATUS_HV_PROCESSOR_STARTUP_TIMEOUT ((NTSTATUS)0xC035003EL)
#endif//STATUS_HV_PROCESSOR_STARTUP_TIMEOUT

//
// MessageId: STATUS_HV_SMX_ENABLED
//
// MessageText:
//
// SMX has been enabled in the BIOS.
//
#ifndef STATUS_HV_SMX_ENABLED
#define STATUS_HV_SMX_ENABLED            ((NTSTATUS)0xC035003FL)
#endif//STATUS_HV_SMX_ENABLED

//
// MessageId: STATUS_HV_INVALID_LP_INDEX
//
// MessageText:
//
// The hypervisor could not perform the operation because the specified LP index is invalid.
//
#ifndef STATUS_HV_INVALID_LP_INDEX
#define STATUS_HV_INVALID_LP_INDEX       ((NTSTATUS)0xC0350041L)
#endif//STATUS_HV_INVALID_LP_INDEX

//
// MessageId: STATUS_HV_INVALID_REGISTER_VALUE
//
// MessageText:
//
// The supplied register value is invalid.
//
#ifndef STATUS_HV_INVALID_REGISTER_VALUE
#define STATUS_HV_INVALID_REGISTER_VALUE ((NTSTATUS)0xC0350050L)
#endif//STATUS_HV_INVALID_REGISTER_VALUE

//
// MessageId: STATUS_HV_INVALID_VTL_STATE
//
// MessageText:
//
// The supplied virtual trust level is not in the correct state to perform the requested operation.
//
#ifndef STATUS_HV_INVALID_VTL_STATE
#define STATUS_HV_INVALID_VTL_STATE      ((NTSTATUS)0xC0350051L)
#endif//STATUS_HV_INVALID_VTL_STATE

//
// MessageId: STATUS_HV_NX_NOT_DETECTED
//
// MessageText:
//
// No execute feature (NX) is not present or not enabled in the BIOS.
//
#ifndef STATUS_HV_NX_NOT_DETECTED
#define STATUS_HV_NX_NOT_DETECTED        ((NTSTATUS)0xC0350055L)
#endif//STATUS_HV_NX_NOT_DETECTED

//
// MessageId: STATUS_HV_INVALID_DEVICE_ID
//
// MessageText:
//
// The supplied device ID is invalid.
//
#ifndef STATUS_HV_INVALID_DEVICE_ID
#define STATUS_HV_INVALID_DEVICE_ID      ((NTSTATUS)0xC0350057L)
#endif//STATUS_HV_INVALID_DEVICE_ID

//
// MessageId: STATUS_HV_INVALID_DEVICE_STATE
//
// MessageText:
//
// The operation is not allowed in the current device state.
//
#ifndef STATUS_HV_INVALID_DEVICE_STATE
#define STATUS_HV_INVALID_DEVICE_STATE   ((NTSTATUS)0xC0350058L)
#endif//STATUS_HV_INVALID_DEVICE_STATE

//
// MessageId: STATUS_HV_PENDING_PAGE_REQUESTS
//
// MessageText:
//
// The device had pending page requests which were discarded.
//
#ifndef STATUS_HV_PENDING_PAGE_REQUESTS
#define STATUS_HV_PENDING_PAGE_REQUESTS  ((NTSTATUS)0x00350059L)
#endif//STATUS_HV_PENDING_PAGE_REQUESTS

//
// MessageId: STATUS_HV_PAGE_REQUEST_INVALID
//
// MessageText:
//
// The supplied page request specifies a memory access that the guest does not have permissions to perform.
//
#ifndef STATUS_HV_PAGE_REQUEST_INVALID
#define STATUS_HV_PAGE_REQUEST_INVALID   ((NTSTATUS)0xC0350060L)
#endif//STATUS_HV_PAGE_REQUEST_INVALID

//
// MessageId: STATUS_HV_INVALID_CPU_GROUP_ID
//
// MessageText:
//
// A CPU group with the specified CPU group Id does not exist.
//
#ifndef STATUS_HV_INVALID_CPU_GROUP_ID
#define STATUS_HV_INVALID_CPU_GROUP_ID   ((NTSTATUS)0xC035006FL)
#endif//STATUS_HV_INVALID_CPU_GROUP_ID

//
// MessageId: STATUS_HV_INVALID_CPU_GROUP_STATE
//
// MessageText:
//
// The hypervisor could not perform the operation because the CPU group is entering or in an invalid state.
//
#ifndef STATUS_HV_INVALID_CPU_GROUP_STATE
#define STATUS_HV_INVALID_CPU_GROUP_STATE ((NTSTATUS)0xC0350070L)
#endif//STATUS_HV_INVALID_CPU_GROUP_STATE

//
// MessageId: STATUS_HV_OPERATION_FAILED
//
// MessageText:
//
// The requested operation failed.
//
#ifndef STATUS_HV_OPERATION_FAILED
#define STATUS_HV_OPERATION_FAILED       ((NTSTATUS)0xC0350071L)
#endif//STATUS_HV_OPERATION_FAILED

//
// MessageId: STATUS_HV_NOT_ALLOWED_WITH_NESTED_VIRT_ACTIVE
//
// MessageText:
//
// The hypervisor could not perform the operation because it is not allowed with nested virtualization active.
//
#ifndef STATUS_HV_NOT_ALLOWED_WITH_NESTED_VIRT_ACTIVE
#define STATUS_HV_NOT_ALLOWED_WITH_NESTED_VIRT_ACTIVE ((NTSTATUS)0xC0350072L)
#endif//STATUS_HV_NOT_ALLOWED_WITH_NESTED_VIRT_ACTIVE

//
// MessageId: STATUS_HV_NOT_PRESENT
//
// MessageText:
//
// No hypervisor is present on this system.
//
#ifndef STATUS_HV_NOT_PRESENT
#define STATUS_HV_NOT_PRESENT            ((NTSTATUS)0xC0351000L)
#endif//STATUS_HV_NOT_PRESENT


//
// MessageId: STATUS_HV_NOTHING_TO_DO
//
// This is undocumented - taken from:
// http://driverdev-devel.linuxdriverproject.narkive.com/5W3pcHTb/patch-00-54-announce-microsoft-hyper-v-drivers-for-linux
//
#ifndef STATUS_HV_NOTHING_TO_DO
#define STATUS_HV_NOTHING_TO_DO                 ((NTSTATUS)0xC035101EL)
#endif//STATUS_HV_NOTHING_TO_DO

//
// Virtualization status codes - these codes are used by the Virtualization Infrustructure Driver (VID) and other components
//                               of the virtualization stack.
//
//
// Errors:
//

//
// MessageId: STATUS_VID_DUPLICATE_HANDLER
//
// MessageText:
//
// The handler for the virtualization infrastructure driver is already registered. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_DUPLICATE_HANDLER
#define STATUS_VID_DUPLICATE_HANDLER     ((NTSTATUS)0xC0370001L)
#endif//STATUS_VID_DUPLICATE_HANDLER

//
// MessageId: STATUS_VID_TOO_MANY_HANDLERS
//
// MessageText:
//
// The number of registered handlers for the virtualization infrastructure driver exceeded the maximum. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_TOO_MANY_HANDLERS
#define STATUS_VID_TOO_MANY_HANDLERS     ((NTSTATUS)0xC0370002L)
#endif//STATUS_VID_TOO_MANY_HANDLERS

//
// MessageId: STATUS_VID_QUEUE_FULL
//
// MessageText:
//
// The message queue for the virtualization infrastructure driver is full and cannot accept new messages. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_QUEUE_FULL
#define STATUS_VID_QUEUE_FULL            ((NTSTATUS)0xC0370003L)
#endif//STATUS_VID_QUEUE_FULL

//
// MessageId: STATUS_VID_HANDLER_NOT_PRESENT
//
// MessageText:
//
// No handler exists to handle the message for the virtualization infrastructure driver. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_HANDLER_NOT_PRESENT
#define STATUS_VID_HANDLER_NOT_PRESENT   ((NTSTATUS)0xC0370004L)
#endif//STATUS_VID_HANDLER_NOT_PRESENT

//
// MessageId: STATUS_VID_INVALID_OBJECT_NAME
//
// MessageText:
//
// The name of the partition or message queue for the virtualization infrastructure driver is invalid. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_INVALID_OBJECT_NAME
#define STATUS_VID_INVALID_OBJECT_NAME   ((NTSTATUS)0xC0370005L)
#endif//STATUS_VID_INVALID_OBJECT_NAME

//
// MessageId: STATUS_VID_PARTITION_NAME_TOO_LONG
//
// MessageText:
//
// The partition name of the virtualization infrastructure driver exceeds the maximum.
//
#ifndef STATUS_VID_PARTITION_NAME_TOO_LONG
#define STATUS_VID_PARTITION_NAME_TOO_LONG ((NTSTATUS)0xC0370006L)
#endif//STATUS_VID_PARTITION_NAME_TOO_LONG

//
// MessageId: STATUS_VID_MESSAGE_QUEUE_NAME_TOO_LONG
//
// MessageText:
//
// The message queue name of the virtualization infrastructure driver exceeds the maximum.
//
#ifndef STATUS_VID_MESSAGE_QUEUE_NAME_TOO_LONG
#define STATUS_VID_MESSAGE_QUEUE_NAME_TOO_LONG ((NTSTATUS)0xC0370007L)
#endif//STATUS_VID_MESSAGE_QUEUE_NAME_TOO_LONG

//
// MessageId: STATUS_VID_PARTITION_ALREADY_EXISTS
//
// MessageText:
//
// Cannot create the partition for the virtualization infrastructure driver because another partition with the same name already exists.
//
#ifndef STATUS_VID_PARTITION_ALREADY_EXISTS
#define STATUS_VID_PARTITION_ALREADY_EXISTS ((NTSTATUS)0xC0370008L)
#endif//STATUS_VID_PARTITION_ALREADY_EXISTS

//
// MessageId: STATUS_VID_PARTITION_DOES_NOT_EXIST
//
// MessageText:
//
// The virtualization infrastructure driver has encountered an error. The requested partition does not exist. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_PARTITION_DOES_NOT_EXIST
#define STATUS_VID_PARTITION_DOES_NOT_EXIST ((NTSTATUS)0xC0370009L)
#endif//STATUS_VID_PARTITION_DOES_NOT_EXIST

//
// MessageId: STATUS_VID_PARTITION_NAME_NOT_FOUND
//
// MessageText:
//
// The virtualization infrastructure driver has encountered an error. Could not find the requested partition. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_PARTITION_NAME_NOT_FOUND
#define STATUS_VID_PARTITION_NAME_NOT_FOUND ((NTSTATUS)0xC037000AL)
#endif//STATUS_VID_PARTITION_NAME_NOT_FOUND

//
// MessageId: STATUS_VID_MESSAGE_QUEUE_ALREADY_EXISTS
//
// MessageText:
//
// A message queue with the same name already exists for the virtualization infrastructure driver.
//
#ifndef STATUS_VID_MESSAGE_QUEUE_ALREADY_EXISTS
#define STATUS_VID_MESSAGE_QUEUE_ALREADY_EXISTS ((NTSTATUS)0xC037000BL)
#endif//STATUS_VID_MESSAGE_QUEUE_ALREADY_EXISTS

//
// MessageId: STATUS_VID_EXCEEDED_MBP_ENTRY_MAP_LIMIT
//
// MessageText:
//
// The memory block page for the virtualization infrastructure driver cannot be mapped because the page map limit has been reached. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_EXCEEDED_MBP_ENTRY_MAP_LIMIT
#define STATUS_VID_EXCEEDED_MBP_ENTRY_MAP_LIMIT ((NTSTATUS)0xC037000CL)
#endif//STATUS_VID_EXCEEDED_MBP_ENTRY_MAP_LIMIT

//
// MessageId: STATUS_VID_MB_STILL_REFERENCED
//
// MessageText:
//
// The memory block for the virtualization infrastructure driver is still being used and cannot be destroyed.
//
#ifndef STATUS_VID_MB_STILL_REFERENCED
#define STATUS_VID_MB_STILL_REFERENCED   ((NTSTATUS)0xC037000DL)
#endif//STATUS_VID_MB_STILL_REFERENCED

//
// MessageId: STATUS_VID_CHILD_GPA_PAGE_SET_CORRUPTED
//
// MessageText:
//
// Cannot unlock the page array for the guest operating system memory address because it does not match a previous lock request. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_CHILD_GPA_PAGE_SET_CORRUPTED
#define STATUS_VID_CHILD_GPA_PAGE_SET_CORRUPTED ((NTSTATUS)0xC037000EL)
#endif//STATUS_VID_CHILD_GPA_PAGE_SET_CORRUPTED

//
// MessageId: STATUS_VID_INVALID_NUMA_SETTINGS
//
// MessageText:
//
// The non-uniform memory access (NUMA) node settings do not match the system NUMA topology. In order to start the virtual machine, you will need to modify the NUMA configuration.
//
#ifndef STATUS_VID_INVALID_NUMA_SETTINGS
#define STATUS_VID_INVALID_NUMA_SETTINGS ((NTSTATUS)0xC037000FL)
#endif//STATUS_VID_INVALID_NUMA_SETTINGS

//
// MessageId: STATUS_VID_INVALID_NUMA_NODE_INDEX
//
// MessageText:
//
// The non-uniform memory access (NUMA) node index does not match a valid index in the system NUMA topology.
//
#ifndef STATUS_VID_INVALID_NUMA_NODE_INDEX
#define STATUS_VID_INVALID_NUMA_NODE_INDEX ((NTSTATUS)0xC0370010L)
#endif//STATUS_VID_INVALID_NUMA_NODE_INDEX

//
// MessageId: STATUS_VID_NOTIFICATION_QUEUE_ALREADY_ASSOCIATED
//
// MessageText:
//
// The memory block for the virtualization infrastructure driver is already associated with a message queue.
//
#ifndef STATUS_VID_NOTIFICATION_QUEUE_ALREADY_ASSOCIATED
#define STATUS_VID_NOTIFICATION_QUEUE_ALREADY_ASSOCIATED ((NTSTATUS)0xC0370011L)
#endif//STATUS_VID_NOTIFICATION_QUEUE_ALREADY_ASSOCIATED

//
// MessageId: STATUS_VID_INVALID_MEMORY_BLOCK_HANDLE
//
// MessageText:
//
// The handle is not a valid memory block handle for the virtualization infrastructure driver.
//
#ifndef STATUS_VID_INVALID_MEMORY_BLOCK_HANDLE
#define STATUS_VID_INVALID_MEMORY_BLOCK_HANDLE ((NTSTATUS)0xC0370012L)
#endif//STATUS_VID_INVALID_MEMORY_BLOCK_HANDLE

//
// MessageId: STATUS_VID_PAGE_RANGE_OVERFLOW
//
// MessageText:
//
// The request exceeded the memory block page limit for the virtualization infrastructure driver. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_PAGE_RANGE_OVERFLOW
#define STATUS_VID_PAGE_RANGE_OVERFLOW   ((NTSTATUS)0xC0370013L)
#endif//STATUS_VID_PAGE_RANGE_OVERFLOW

//
// MessageId: STATUS_VID_INVALID_MESSAGE_QUEUE_HANDLE
//
// MessageText:
//
// The handle is not a valid message queue handle for the virtualization infrastructure driver.
//
#ifndef STATUS_VID_INVALID_MESSAGE_QUEUE_HANDLE
#define STATUS_VID_INVALID_MESSAGE_QUEUE_HANDLE ((NTSTATUS)0xC0370014L)
#endif//STATUS_VID_INVALID_MESSAGE_QUEUE_HANDLE

//
// MessageId: STATUS_VID_INVALID_GPA_RANGE_HANDLE
//
// MessageText:
//
// The handle is not a valid page range handle for the virtualization infrastructure driver.
//
#ifndef STATUS_VID_INVALID_GPA_RANGE_HANDLE
#define STATUS_VID_INVALID_GPA_RANGE_HANDLE ((NTSTATUS)0xC0370015L)
#endif//STATUS_VID_INVALID_GPA_RANGE_HANDLE

//
// MessageId: STATUS_VID_NO_MEMORY_BLOCK_NOTIFICATION_QUEUE
//
// MessageText:
//
// Cannot install client notifications because no message queue for the virtualization infrastructure driver is associated with the memory block.
//
#ifndef STATUS_VID_NO_MEMORY_BLOCK_NOTIFICATION_QUEUE
#define STATUS_VID_NO_MEMORY_BLOCK_NOTIFICATION_QUEUE ((NTSTATUS)0xC0370016L)
#endif//STATUS_VID_NO_MEMORY_BLOCK_NOTIFICATION_QUEUE

//
// MessageId: STATUS_VID_MEMORY_BLOCK_LOCK_COUNT_EXCEEDED
//
// MessageText:
//
// The request to lock or map a memory block page failed because the virtualization infrastructure driver memory block limit has been reached. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
//
//
#ifndef STATUS_VID_MEMORY_BLOCK_LOCK_COUNT_EXCEEDED
#define STATUS_VID_MEMORY_BLOCK_LOCK_COUNT_EXCEEDED ((NTSTATUS)0xC0370017L)
#endif//STATUS_VID_MEMORY_BLOCK_LOCK_COUNT_EXCEEDED

//
// MessageId: STATUS_VID_INVALID_PPM_HANDLE
//
// MessageText:
//
// The handle is not a valid parent partition mapping handle for the virtualization infrastructure driver.
//
#ifndef STATUS_VID_INVALID_PPM_HANDLE
#define STATUS_VID_INVALID_PPM_HANDLE    ((NTSTATUS)0xC0370018L)
#endif//STATUS_VID_INVALID_PPM_HANDLE

//
// MessageId: STATUS_VID_MBPS_ARE_LOCKED
//
// MessageText:
//
// Notifications cannot be created on the memory block because it is use.
//
#ifndef STATUS_VID_MBPS_ARE_LOCKED
#define STATUS_VID_MBPS_ARE_LOCKED       ((NTSTATUS)0xC0370019L)
#endif//STATUS_VID_MBPS_ARE_LOCKED

//
// MessageId: STATUS_VID_MESSAGE_QUEUE_CLOSED
//
// MessageText:
//
// The message queue for the virtualization infrastructure driver has been closed. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_MESSAGE_QUEUE_CLOSED
#define STATUS_VID_MESSAGE_QUEUE_CLOSED  ((NTSTATUS)0xC037001AL)
#endif//STATUS_VID_MESSAGE_QUEUE_CLOSED

//
// MessageId: STATUS_VID_VIRTUAL_PROCESSOR_LIMIT_EXCEEDED
//
// MessageText:
//
// Cannot add a virtual processor to the partition because the maximum has been reached.
//
#ifndef STATUS_VID_VIRTUAL_PROCESSOR_LIMIT_EXCEEDED
#define STATUS_VID_VIRTUAL_PROCESSOR_LIMIT_EXCEEDED ((NTSTATUS)0xC037001BL)
#endif//STATUS_VID_VIRTUAL_PROCESSOR_LIMIT_EXCEEDED

//
// MessageId: STATUS_VID_STOP_PENDING
//
// MessageText:
//
// Cannot stop the virtual processor immediately because of a pending intercept.
//
#ifndef STATUS_VID_STOP_PENDING
#define STATUS_VID_STOP_PENDING          ((NTSTATUS)0xC037001CL)
#endif//STATUS_VID_STOP_PENDING

//
// MessageId: STATUS_VID_INVALID_PROCESSOR_STATE
//
// MessageText:
//
// Invalid state for the virtual processor. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_INVALID_PROCESSOR_STATE
#define STATUS_VID_INVALID_PROCESSOR_STATE ((NTSTATUS)0xC037001DL)
#endif//STATUS_VID_INVALID_PROCESSOR_STATE

//
// MessageId: STATUS_VID_EXCEEDED_KM_CONTEXT_COUNT_LIMIT
//
// MessageText:
//
// The maximum number of kernel mode clients for the virtualization infrastructure driver has been reached. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_EXCEEDED_KM_CONTEXT_COUNT_LIMIT
#define STATUS_VID_EXCEEDED_KM_CONTEXT_COUNT_LIMIT ((NTSTATUS)0xC037001EL)
#endif//STATUS_VID_EXCEEDED_KM_CONTEXT_COUNT_LIMIT

//
// MessageId: STATUS_VID_KM_INTERFACE_ALREADY_INITIALIZED
//
// MessageText:
//
// This kernel mode interface for the virtualization infrastructure driver has already been initialized. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_KM_INTERFACE_ALREADY_INITIALIZED
#define STATUS_VID_KM_INTERFACE_ALREADY_INITIALIZED ((NTSTATUS)0xC037001FL)
#endif//STATUS_VID_KM_INTERFACE_ALREADY_INITIALIZED

//
// MessageId: STATUS_VID_MB_PROPERTY_ALREADY_SET_RESET
//
// MessageText:
//
// Cannot set or reset the memory block property more than once for the virtualization infrastructure driver. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_MB_PROPERTY_ALREADY_SET_RESET
#define STATUS_VID_MB_PROPERTY_ALREADY_SET_RESET ((NTSTATUS)0xC0370020L)
#endif//STATUS_VID_MB_PROPERTY_ALREADY_SET_RESET

//
// MessageId: STATUS_VID_MMIO_RANGE_DESTROYED
//
// MessageText:
//
// The memory mapped I/O for this page range no longer exists. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_MMIO_RANGE_DESTROYED
#define STATUS_VID_MMIO_RANGE_DESTROYED  ((NTSTATUS)0xC0370021L)
#endif//STATUS_VID_MMIO_RANGE_DESTROYED

//
// MessageId: STATUS_VID_INVALID_CHILD_GPA_PAGE_SET
//
// MessageText:
//
// The lock or unlock request uses an invalid guest operating system memory address. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_INVALID_CHILD_GPA_PAGE_SET
#define STATUS_VID_INVALID_CHILD_GPA_PAGE_SET ((NTSTATUS)0xC0370022L)
#endif//STATUS_VID_INVALID_CHILD_GPA_PAGE_SET

//
// MessageId: STATUS_VID_RESERVE_PAGE_SET_IS_BEING_USED
//
// MessageText:
//
// Cannot destroy or reuse the reserve page set for the virtualization infrastructure driver because it is in use. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_RESERVE_PAGE_SET_IS_BEING_USED
#define STATUS_VID_RESERVE_PAGE_SET_IS_BEING_USED ((NTSTATUS)0xC0370023L)
#endif//STATUS_VID_RESERVE_PAGE_SET_IS_BEING_USED

//
// MessageId: STATUS_VID_RESERVE_PAGE_SET_TOO_SMALL
//
// MessageText:
//
// The reserve page set for the virtualization infrastructure driver is too small to use in the lock request. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_RESERVE_PAGE_SET_TOO_SMALL
#define STATUS_VID_RESERVE_PAGE_SET_TOO_SMALL ((NTSTATUS)0xC0370024L)
#endif//STATUS_VID_RESERVE_PAGE_SET_TOO_SMALL

//
// MessageId: STATUS_VID_MBP_ALREADY_LOCKED_USING_RESERVED_PAGE
//
// MessageText:
//
// Cannot lock or map the memory block page for the virtualization infrastructure driver because it has already been locked using a reserve page set page. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_MBP_ALREADY_LOCKED_USING_RESERVED_PAGE
#define STATUS_VID_MBP_ALREADY_LOCKED_USING_RESERVED_PAGE ((NTSTATUS)0xC0370025L)
#endif//STATUS_VID_MBP_ALREADY_LOCKED_USING_RESERVED_PAGE

//
// MessageId: STATUS_VID_MBP_COUNT_EXCEEDED_LIMIT
//
// MessageText:
//
// Cannot create the memory block for the virtualization infrastructure driver because the requested number of pages exceeded the limit. Restarting the virtual machine may fix the problem. If the problem persists, try restarting the physical computer.
//
#ifndef STATUS_VID_MBP_COUNT_EXCEEDED_LIMIT
#define STATUS_VID_MBP_COUNT_EXCEEDED_LIMIT ((NTSTATUS)0xC0370026L)
#endif//STATUS_VID_MBP_COUNT_EXCEEDED_LIMIT

//
// MessageId: STATUS_VID_SAVED_STATE_CORRUPT
//
// MessageText:
//
// Cannot restore this virtual machine because the saved state data cannot be read. Delete the saved state data and then try to start the virtual machine.
//
#ifndef STATUS_VID_SAVED_STATE_CORRUPT
#define STATUS_VID_SAVED_STATE_CORRUPT   ((NTSTATUS)0xC0370027L)
#endif//STATUS_VID_SAVED_STATE_CORRUPT

//
// MessageId: STATUS_VID_SAVED_STATE_UNRECOGNIZED_ITEM
//
// MessageText:
//
// Cannot restore this virtual machine because an item read from the saved state data is not recognized. Delete the saved state data and then try to start the virtual machine.
//
#ifndef STATUS_VID_SAVED_STATE_UNRECOGNIZED_ITEM
#define STATUS_VID_SAVED_STATE_UNRECOGNIZED_ITEM ((NTSTATUS)0xC0370028L)
#endif//STATUS_VID_SAVED_STATE_UNRECOGNIZED_ITEM

//
// MessageId: STATUS_VID_SAVED_STATE_INCOMPATIBLE
//
// MessageText:
//
// Cannot restore this virtual machine to the saved state because of hypervisor incompatibility. Delete the saved state data and then try to start the virtual machine.
//
#ifndef STATUS_VID_SAVED_STATE_INCOMPATIBLE
#define STATUS_VID_SAVED_STATE_INCOMPATIBLE ((NTSTATUS)0xC0370029L)
#endif//STATUS_VID_SAVED_STATE_INCOMPATIBLE

//
// MessageId: STATUS_VID_VTL_ACCESS_DENIED
//
// MessageText:
//
// The specified VTL does not have the permission to access the resource.
//
#ifndef STATUS_VID_VTL_ACCESS_DENIED
#define STATUS_VID_VTL_ACCESS_DENIED     ((NTSTATUS)0xC037002AL)
#endif//STATUS_VID_VTL_ACCESS_DENIED

//
// Warnings:
//
//
// MessageId: STATUS_VID_REMOTE_NODE_PARENT_GPA_PAGES_USED
//
// MessageText:
//
// A virtual machine is running with its memory allocated across multiple NUMA nodes. This does not indicate a problem unless the performance of your virtual machine is unusually slow. If you are experiencing performance problems, you may need to modify the NUMA configuration.
//
#ifndef STATUS_VID_REMOTE_NODE_PARENT_GPA_PAGES_USED
#define STATUS_VID_REMOTE_NODE_PARENT_GPA_PAGES_USED ((NTSTATUS)0x80370001L)
#endif//STATUS_VID_REMOTE_NODE_PARENT_GPA_PAGES_USED


//
// IPSEC error codes (tcpip.sys)
//

//
// MessageId: STATUS_IPSEC_BAD_SPI
//
// MessageText:
//
// The SPI in the packet does not match a valid IPsec SA.
//
#ifndef STATUS_IPSEC_BAD_SPI
#define STATUS_IPSEC_BAD_SPI             ((NTSTATUS)0xC0360001L)
#endif//STATUS_IPSEC_BAD_SPI

//
// MessageId: STATUS_IPSEC_SA_LIFETIME_EXPIRED
//
// MessageText:
//
// Packet was received on an IPsec SA whose lifetime has expired.
//
#ifndef STATUS_IPSEC_SA_LIFETIME_EXPIRED
#define STATUS_IPSEC_SA_LIFETIME_EXPIRED ((NTSTATUS)0xC0360002L)
#endif//STATUS_IPSEC_SA_LIFETIME_EXPIRED

//
// MessageId: STATUS_IPSEC_WRONG_SA
//
// MessageText:
//
// Packet was received on an IPsec SA that does not match the packet characteristics.
//
#ifndef STATUS_IPSEC_WRONG_SA
#define STATUS_IPSEC_WRONG_SA            ((NTSTATUS)0xC0360003L)
#endif//STATUS_IPSEC_WRONG_SA

//
// MessageId: STATUS_IPSEC_REPLAY_CHECK_FAILED
//
// MessageText:
//
// Packet sequence number replay check failed.
//
#ifndef STATUS_IPSEC_REPLAY_CHECK_FAILED
#define STATUS_IPSEC_REPLAY_CHECK_FAILED ((NTSTATUS)0xC0360004L)
#endif//STATUS_IPSEC_REPLAY_CHECK_FAILED

//
// MessageId: STATUS_IPSEC_INVALID_PACKET
//
// MessageText:
//
// IPsec header and/or trailer in the packet is invalid.
//
#ifndef STATUS_IPSEC_INVALID_PACKET
#define STATUS_IPSEC_INVALID_PACKET      ((NTSTATUS)0xC0360005L)
#endif//STATUS_IPSEC_INVALID_PACKET

//
// MessageId: STATUS_IPSEC_INTEGRITY_CHECK_FAILED
//
// MessageText:
//
// IPsec integrity check failed.
//
#ifndef STATUS_IPSEC_INTEGRITY_CHECK_FAILED
#define STATUS_IPSEC_INTEGRITY_CHECK_FAILED ((NTSTATUS)0xC0360006L)
#endif//STATUS_IPSEC_INTEGRITY_CHECK_FAILED

//
// MessageId: STATUS_IPSEC_CLEAR_TEXT_DROP
//
// MessageText:
//
// IPsec dropped a clear text packet.
//
#ifndef STATUS_IPSEC_CLEAR_TEXT_DROP
#define STATUS_IPSEC_CLEAR_TEXT_DROP     ((NTSTATUS)0xC0360007L)
#endif//STATUS_IPSEC_CLEAR_TEXT_DROP

//
// MessageId: STATUS_IPSEC_AUTH_FIREWALL_DROP
//
// MessageText:
//
// IPsec dropped an incoming ESP packet in authenticated firewall mode. This drop is benign.
//
#ifndef STATUS_IPSEC_AUTH_FIREWALL_DROP
#define STATUS_IPSEC_AUTH_FIREWALL_DROP  ((NTSTATUS)0xC0360008L)
#endif//STATUS_IPSEC_AUTH_FIREWALL_DROP

//
// MessageId: STATUS_IPSEC_THROTTLE_DROP
//
// MessageText:
//
// IPsec dropped a packet due to DoS throttling.
//
#ifndef STATUS_IPSEC_THROTTLE_DROP
#define STATUS_IPSEC_THROTTLE_DROP       ((NTSTATUS)0xC0360009L)
#endif//STATUS_IPSEC_THROTTLE_DROP

//
// MessageId: STATUS_IPSEC_DOSP_BLOCK
//
// MessageText:
//
// IPsec DoS Protection matched an explicit block rule.
//
#ifndef STATUS_IPSEC_DOSP_BLOCK
#define STATUS_IPSEC_DOSP_BLOCK          ((NTSTATUS)0xC0368000L)
#endif//STATUS_IPSEC_DOSP_BLOCK

//
// MessageId: STATUS_IPSEC_DOSP_RECEIVED_MULTICAST
//
// MessageText:
//
// IPsec DoS Protection received an IPsec specific multicast packet which is not allowed.
//
#ifndef STATUS_IPSEC_DOSP_RECEIVED_MULTICAST
#define STATUS_IPSEC_DOSP_RECEIVED_MULTICAST ((NTSTATUS)0xC0368001L)
#endif//STATUS_IPSEC_DOSP_RECEIVED_MULTICAST

//
// MessageId: STATUS_IPSEC_DOSP_INVALID_PACKET
//
// MessageText:
//
// IPsec DoS Protection received an incorrectly formatted packet.
//
#ifndef STATUS_IPSEC_DOSP_INVALID_PACKET
#define STATUS_IPSEC_DOSP_INVALID_PACKET ((NTSTATUS)0xC0368002L)
#endif//STATUS_IPSEC_DOSP_INVALID_PACKET

//
// MessageId: STATUS_IPSEC_DOSP_STATE_LOOKUP_FAILED
//
// MessageText:
//
// IPsec DoS Protection failed to look up state.
//
#ifndef STATUS_IPSEC_DOSP_STATE_LOOKUP_FAILED
#define STATUS_IPSEC_DOSP_STATE_LOOKUP_FAILED ((NTSTATUS)0xC0368003L)
#endif//STATUS_IPSEC_DOSP_STATE_LOOKUP_FAILED

//
// MessageId: STATUS_IPSEC_DOSP_MAX_ENTRIES
//
// MessageText:
//
// IPsec DoS Protection failed to create state because the maximum number of entries allowed by policy has been reached.
//
#ifndef STATUS_IPSEC_DOSP_MAX_ENTRIES
#define STATUS_IPSEC_DOSP_MAX_ENTRIES    ((NTSTATUS)0xC0368004L)
#endif//STATUS_IPSEC_DOSP_MAX_ENTRIES

//
// MessageId: STATUS_IPSEC_DOSP_KEYMOD_NOT_ALLOWED
//
// MessageText:
//
// IPsec DoS Protection received an IPsec negotiation packet for a keying module which is not allowed by policy.
//
#ifndef STATUS_IPSEC_DOSP_KEYMOD_NOT_ALLOWED
#define STATUS_IPSEC_DOSP_KEYMOD_NOT_ALLOWED ((NTSTATUS)0xC0368005L)
#endif//STATUS_IPSEC_DOSP_KEYMOD_NOT_ALLOWED

//
// MessageId: STATUS_IPSEC_DOSP_MAX_PER_IP_RATELIMIT_QUEUES
//
// MessageText:
//
// IPsec DoS Protection failed to create a per internal IP rate limit queue because the maximum number of queues allowed by policy has been reached.
//
#ifndef STATUS_IPSEC_DOSP_MAX_PER_IP_RATELIMIT_QUEUES
#define STATUS_IPSEC_DOSP_MAX_PER_IP_RATELIMIT_QUEUES ((NTSTATUS)0xC0368006L)
#endif//STATUS_IPSEC_DOSP_MAX_PER_IP_RATELIMIT_QUEUES


//
// Volume manager status codes (volmgr.sys and volmgrx.sys)
//

//
// WARNINGS
//
//
// MessageId: STATUS_VOLMGR_INCOMPLETE_REGENERATION
//
// MessageText:
//
// The regeneration operation was not able to copy all data from the active plexes due to bad sectors.
//
#ifndef STATUS_VOLMGR_INCOMPLETE_REGENERATION
#define STATUS_VOLMGR_INCOMPLETE_REGENERATION ((NTSTATUS)0x80380001L)
#endif//STATUS_VOLMGR_INCOMPLETE_REGENERATION

//
// MessageId: STATUS_VOLMGR_INCOMPLETE_DISK_MIGRATION
//
// MessageText:
//
// One or more disks were not fully migrated to the target pack. They may or may not require reimport after fixing the hardware problems.
//
#ifndef STATUS_VOLMGR_INCOMPLETE_DISK_MIGRATION
#define STATUS_VOLMGR_INCOMPLETE_DISK_MIGRATION ((NTSTATUS)0x80380002L)
#endif//STATUS_VOLMGR_INCOMPLETE_DISK_MIGRATION

//
// ERRORS
//
//
// MessageId: STATUS_VOLMGR_DATABASE_FULL
//
// MessageText:
//
// The configuration database is full.
//
#ifndef STATUS_VOLMGR_DATABASE_FULL
#define STATUS_VOLMGR_DATABASE_FULL      ((NTSTATUS)0xC0380001L)
#endif//STATUS_VOLMGR_DATABASE_FULL

//
// MessageId: STATUS_VOLMGR_DISK_CONFIGURATION_CORRUPTED
//
// MessageText:
//
// The configuration data on the disk is corrupted.
//
#ifndef STATUS_VOLMGR_DISK_CONFIGURATION_CORRUPTED
#define STATUS_VOLMGR_DISK_CONFIGURATION_CORRUPTED ((NTSTATUS)0xC0380002L)
#endif//STATUS_VOLMGR_DISK_CONFIGURATION_CORRUPTED

//
// MessageId: STATUS_VOLMGR_DISK_CONFIGURATION_NOT_IN_SYNC
//
// MessageText:
//
// The configuration on the disk is not insync with the in-memory configuration.
//
#ifndef STATUS_VOLMGR_DISK_CONFIGURATION_NOT_IN_SYNC
#define STATUS_VOLMGR_DISK_CONFIGURATION_NOT_IN_SYNC ((NTSTATUS)0xC0380003L)
#endif//STATUS_VOLMGR_DISK_CONFIGURATION_NOT_IN_SYNC

//
// MessageId: STATUS_VOLMGR_PACK_CONFIG_UPDATE_FAILED
//
// MessageText:
//
// A majority of disks failed to be updated with the new configuration.
//
#ifndef STATUS_VOLMGR_PACK_CONFIG_UPDATE_FAILED
#define STATUS_VOLMGR_PACK_CONFIG_UPDATE_FAILED ((NTSTATUS)0xC0380004L)
#endif//STATUS_VOLMGR_PACK_CONFIG_UPDATE_FAILED

//
// MessageId: STATUS_VOLMGR_DISK_CONTAINS_NON_SIMPLE_VOLUME
//
// MessageText:
//
// The disk contains non-simple volumes.
//
#ifndef STATUS_VOLMGR_DISK_CONTAINS_NON_SIMPLE_VOLUME
#define STATUS_VOLMGR_DISK_CONTAINS_NON_SIMPLE_VOLUME ((NTSTATUS)0xC0380005L)
#endif//STATUS_VOLMGR_DISK_CONTAINS_NON_SIMPLE_VOLUME

//
// MessageId: STATUS_VOLMGR_DISK_DUPLICATE
//
// MessageText:
//
// The same disk was specified more than once in the migration list.
//
#ifndef STATUS_VOLMGR_DISK_DUPLICATE
#define STATUS_VOLMGR_DISK_DUPLICATE     ((NTSTATUS)0xC0380006L)
#endif//STATUS_VOLMGR_DISK_DUPLICATE

//
// MessageId: STATUS_VOLMGR_DISK_DYNAMIC
//
// MessageText:
//
// The disk is already dynamic.
//
#ifndef STATUS_VOLMGR_DISK_DYNAMIC
#define STATUS_VOLMGR_DISK_DYNAMIC       ((NTSTATUS)0xC0380007L)
#endif//STATUS_VOLMGR_DISK_DYNAMIC

//
// MessageId: STATUS_VOLMGR_DISK_ID_INVALID
//
// MessageText:
//
// The specified disk id is invalid. There are no disks with the specified disk id.
//
#ifndef STATUS_VOLMGR_DISK_ID_INVALID
#define STATUS_VOLMGR_DISK_ID_INVALID    ((NTSTATUS)0xC0380008L)
#endif//STATUS_VOLMGR_DISK_ID_INVALID

//
// MessageId: STATUS_VOLMGR_DISK_INVALID
//
// MessageText:
//
// The specified disk is an invalid disk. Operation cannot complete on an invalid disk.
//
#ifndef STATUS_VOLMGR_DISK_INVALID
#define STATUS_VOLMGR_DISK_INVALID       ((NTSTATUS)0xC0380009L)
#endif//STATUS_VOLMGR_DISK_INVALID

//
// MessageId: STATUS_VOLMGR_DISK_LAST_VOTER
//
// MessageText:
//
// The specified disk(s) cannot be removed since it is the last remaining voter.
//
#ifndef STATUS_VOLMGR_DISK_LAST_VOTER
#define STATUS_VOLMGR_DISK_LAST_VOTER    ((NTSTATUS)0xC038000AL)
#endif//STATUS_VOLMGR_DISK_LAST_VOTER

//
// MessageId: STATUS_VOLMGR_DISK_LAYOUT_INVALID
//
// MessageText:
//
// The specified disk has an invalid disk layout.
//
#ifndef STATUS_VOLMGR_DISK_LAYOUT_INVALID
#define STATUS_VOLMGR_DISK_LAYOUT_INVALID ((NTSTATUS)0xC038000BL)
#endif//STATUS_VOLMGR_DISK_LAYOUT_INVALID

//
// MessageId: STATUS_VOLMGR_DISK_LAYOUT_NON_BASIC_BETWEEN_BASIC_PARTITIONS
//
// MessageText:
//
// The disk layout contains non-basic partitions which appear after basic paritions. This is an invalid disk layout.
//
#ifndef STATUS_VOLMGR_DISK_LAYOUT_NON_BASIC_BETWEEN_BASIC_PARTITIONS
#define STATUS_VOLMGR_DISK_LAYOUT_NON_BASIC_BETWEEN_BASIC_PARTITIONS ((NTSTATUS)0xC038000CL)
#endif//STATUS_VOLMGR_DISK_LAYOUT_NON_BASIC_BETWEEN_BASIC_PARTITIONS

//
// MessageId: STATUS_VOLMGR_DISK_LAYOUT_NOT_CYLINDER_ALIGNED
//
// MessageText:
//
// The disk layout contains partitions which are not cylinder aligned.
//
#ifndef STATUS_VOLMGR_DISK_LAYOUT_NOT_CYLINDER_ALIGNED
#define STATUS_VOLMGR_DISK_LAYOUT_NOT_CYLINDER_ALIGNED ((NTSTATUS)0xC038000DL)
#endif//STATUS_VOLMGR_DISK_LAYOUT_NOT_CYLINDER_ALIGNED

//
// MessageId: STATUS_VOLMGR_DISK_LAYOUT_PARTITIONS_TOO_SMALL
//
// MessageText:
//
// The disk layout contains partitions which are samller than the minimum size.
//
#ifndef STATUS_VOLMGR_DISK_LAYOUT_PARTITIONS_TOO_SMALL
#define STATUS_VOLMGR_DISK_LAYOUT_PARTITIONS_TOO_SMALL ((NTSTATUS)0xC038000EL)
#endif//STATUS_VOLMGR_DISK_LAYOUT_PARTITIONS_TOO_SMALL

//
// MessageId: STATUS_VOLMGR_DISK_LAYOUT_PRIMARY_BETWEEN_LOGICAL_PARTITIONS
//
// MessageText:
//
// The disk layout contains primary partitions in between logical drives. This is an invalid disk layout.
//
#ifndef STATUS_VOLMGR_DISK_LAYOUT_PRIMARY_BETWEEN_LOGICAL_PARTITIONS
#define STATUS_VOLMGR_DISK_LAYOUT_PRIMARY_BETWEEN_LOGICAL_PARTITIONS ((NTSTATUS)0xC038000FL)
#endif//STATUS_VOLMGR_DISK_LAYOUT_PRIMARY_BETWEEN_LOGICAL_PARTITIONS

//
// MessageId: STATUS_VOLMGR_DISK_LAYOUT_TOO_MANY_PARTITIONS
//
// MessageText:
//
// The disk layout contains more than the maximum number of supported partitions.
//
#ifndef STATUS_VOLMGR_DISK_LAYOUT_TOO_MANY_PARTITIONS
#define STATUS_VOLMGR_DISK_LAYOUT_TOO_MANY_PARTITIONS ((NTSTATUS)0xC0380010L)
#endif//STATUS_VOLMGR_DISK_LAYOUT_TOO_MANY_PARTITIONS

//
// MessageId: STATUS_VOLMGR_DISK_MISSING
//
// MessageText:
//
// The specified disk is missing. The operation cannot complete on a missing disk.
//
#ifndef STATUS_VOLMGR_DISK_MISSING
#define STATUS_VOLMGR_DISK_MISSING       ((NTSTATUS)0xC0380011L)
#endif//STATUS_VOLMGR_DISK_MISSING

//
// MessageId: STATUS_VOLMGR_DISK_NOT_EMPTY
//
// MessageText:
//
// The specified disk is not empty.
//
#ifndef STATUS_VOLMGR_DISK_NOT_EMPTY
#define STATUS_VOLMGR_DISK_NOT_EMPTY     ((NTSTATUS)0xC0380012L)
#endif//STATUS_VOLMGR_DISK_NOT_EMPTY

//
// MessageId: STATUS_VOLMGR_DISK_NOT_ENOUGH_SPACE
//
// MessageText:
//
// There is not enough usable space for this operation.
//
#ifndef STATUS_VOLMGR_DISK_NOT_ENOUGH_SPACE
#define STATUS_VOLMGR_DISK_NOT_ENOUGH_SPACE ((NTSTATUS)0xC0380013L)
#endif//STATUS_VOLMGR_DISK_NOT_ENOUGH_SPACE

//
// MessageId: STATUS_VOLMGR_DISK_REVECTORING_FAILED
//
// MessageText:
//
// The force revectoring of bad sectors failed.
//
#ifndef STATUS_VOLMGR_DISK_REVECTORING_FAILED
#define STATUS_VOLMGR_DISK_REVECTORING_FAILED ((NTSTATUS)0xC0380014L)
#endif//STATUS_VOLMGR_DISK_REVECTORING_FAILED

//
// MessageId: STATUS_VOLMGR_DISK_SECTOR_SIZE_INVALID
//
// MessageText:
//
// The specified disk has an invalid sector size.
//
#ifndef STATUS_VOLMGR_DISK_SECTOR_SIZE_INVALID
#define STATUS_VOLMGR_DISK_SECTOR_SIZE_INVALID ((NTSTATUS)0xC0380015L)
#endif//STATUS_VOLMGR_DISK_SECTOR_SIZE_INVALID

//
// MessageId: STATUS_VOLMGR_DISK_SET_NOT_CONTAINED
//
// MessageText:
//
// The specified disk set contains volumes which exist on disks outside of the set.
//
#ifndef STATUS_VOLMGR_DISK_SET_NOT_CONTAINED
#define STATUS_VOLMGR_DISK_SET_NOT_CONTAINED ((NTSTATUS)0xC0380016L)
#endif//STATUS_VOLMGR_DISK_SET_NOT_CONTAINED

//
// MessageId: STATUS_VOLMGR_DISK_USED_BY_MULTIPLE_MEMBERS
//
// MessageText:
//
// A disk in the volume layout provides extents to more than one member of a plex.
//
#ifndef STATUS_VOLMGR_DISK_USED_BY_MULTIPLE_MEMBERS
#define STATUS_VOLMGR_DISK_USED_BY_MULTIPLE_MEMBERS ((NTSTATUS)0xC0380017L)
#endif//STATUS_VOLMGR_DISK_USED_BY_MULTIPLE_MEMBERS

//
// MessageId: STATUS_VOLMGR_DISK_USED_BY_MULTIPLE_PLEXES
//
// MessageText:
//
// A disk in the volume layout provides extents to more than one plex.
//
#ifndef STATUS_VOLMGR_DISK_USED_BY_MULTIPLE_PLEXES
#define STATUS_VOLMGR_DISK_USED_BY_MULTIPLE_PLEXES ((NTSTATUS)0xC0380018L)
#endif//STATUS_VOLMGR_DISK_USED_BY_MULTIPLE_PLEXES

//
// MessageId: STATUS_VOLMGR_DYNAMIC_DISK_NOT_SUPPORTED
//
// MessageText:
//
// Dynamic disks are not supported on this system.
//
#ifndef STATUS_VOLMGR_DYNAMIC_DISK_NOT_SUPPORTED
#define STATUS_VOLMGR_DYNAMIC_DISK_NOT_SUPPORTED ((NTSTATUS)0xC0380019L)
#endif//STATUS_VOLMGR_DYNAMIC_DISK_NOT_SUPPORTED

//
// MessageId: STATUS_VOLMGR_EXTENT_ALREADY_USED
//
// MessageText:
//
// The specified extent is already used by other volumes.
//
#ifndef STATUS_VOLMGR_EXTENT_ALREADY_USED
#define STATUS_VOLMGR_EXTENT_ALREADY_USED ((NTSTATUS)0xC038001AL)
#endif//STATUS_VOLMGR_EXTENT_ALREADY_USED

//
// MessageId: STATUS_VOLMGR_EXTENT_NOT_CONTIGUOUS
//
// MessageText:
//
// The specified volume is retained and can only be extended into a contiguous extent. The specified extent to grow the volume is not contiguous with the specified volume.
//
#ifndef STATUS_VOLMGR_EXTENT_NOT_CONTIGUOUS
#define STATUS_VOLMGR_EXTENT_NOT_CONTIGUOUS ((NTSTATUS)0xC038001BL)
#endif//STATUS_VOLMGR_EXTENT_NOT_CONTIGUOUS

//
// MessageId: STATUS_VOLMGR_EXTENT_NOT_IN_PUBLIC_REGION
//
// MessageText:
//
// The specified volume extent is not within the public region of the disk.
//
#ifndef STATUS_VOLMGR_EXTENT_NOT_IN_PUBLIC_REGION
#define STATUS_VOLMGR_EXTENT_NOT_IN_PUBLIC_REGION ((NTSTATUS)0xC038001CL)
#endif//STATUS_VOLMGR_EXTENT_NOT_IN_PUBLIC_REGION

//
// MessageId: STATUS_VOLMGR_EXTENT_NOT_SECTOR_ALIGNED
//
// MessageText:
//
// The specifed volume extent is not sector aligned.
//
#ifndef STATUS_VOLMGR_EXTENT_NOT_SECTOR_ALIGNED
#define STATUS_VOLMGR_EXTENT_NOT_SECTOR_ALIGNED ((NTSTATUS)0xC038001DL)
#endif//STATUS_VOLMGR_EXTENT_NOT_SECTOR_ALIGNED

//
// MessageId: STATUS_VOLMGR_EXTENT_OVERLAPS_EBR_PARTITION
//
// MessageText:
//
// The specified parition overlaps an EBR (the first track of an extended partition on a MBR disks).
//
#ifndef STATUS_VOLMGR_EXTENT_OVERLAPS_EBR_PARTITION
#define STATUS_VOLMGR_EXTENT_OVERLAPS_EBR_PARTITION ((NTSTATUS)0xC038001EL)
#endif//STATUS_VOLMGR_EXTENT_OVERLAPS_EBR_PARTITION

//
// MessageId: STATUS_VOLMGR_EXTENT_VOLUME_LENGTHS_DO_NOT_MATCH
//
// MessageText:
//
// The specified extent lengths cannot be used to construct a volume with specified length.
//
#ifndef STATUS_VOLMGR_EXTENT_VOLUME_LENGTHS_DO_NOT_MATCH
#define STATUS_VOLMGR_EXTENT_VOLUME_LENGTHS_DO_NOT_MATCH ((NTSTATUS)0xC038001FL)
#endif//STATUS_VOLMGR_EXTENT_VOLUME_LENGTHS_DO_NOT_MATCH

//
// MessageId: STATUS_VOLMGR_FAULT_TOLERANT_NOT_SUPPORTED
//
// MessageText:
//
// The system does not support fault tolerant volumes.
//
#ifndef STATUS_VOLMGR_FAULT_TOLERANT_NOT_SUPPORTED
#define STATUS_VOLMGR_FAULT_TOLERANT_NOT_SUPPORTED ((NTSTATUS)0xC0380020L)
#endif//STATUS_VOLMGR_FAULT_TOLERANT_NOT_SUPPORTED

//
// MessageId: STATUS_VOLMGR_INTERLEAVE_LENGTH_INVALID
//
// MessageText:
//
// The specified interleave length is invalid.
//
#ifndef STATUS_VOLMGR_INTERLEAVE_LENGTH_INVALID
#define STATUS_VOLMGR_INTERLEAVE_LENGTH_INVALID ((NTSTATUS)0xC0380021L)
#endif//STATUS_VOLMGR_INTERLEAVE_LENGTH_INVALID

//
// MessageId: STATUS_VOLMGR_MAXIMUM_REGISTERED_USERS
//
// MessageText:
//
// There is already a maximum number of registered users.
//
#ifndef STATUS_VOLMGR_MAXIMUM_REGISTERED_USERS
#define STATUS_VOLMGR_MAXIMUM_REGISTERED_USERS ((NTSTATUS)0xC0380022L)
#endif//STATUS_VOLMGR_MAXIMUM_REGISTERED_USERS

//
// MessageId: STATUS_VOLMGR_MEMBER_IN_SYNC
//
// MessageText:
//
// The specified member is already in-sync with the other active members. It does not need to be regenerated.
//
#ifndef STATUS_VOLMGR_MEMBER_IN_SYNC
#define STATUS_VOLMGR_MEMBER_IN_SYNC     ((NTSTATUS)0xC0380023L)
#endif//STATUS_VOLMGR_MEMBER_IN_SYNC

//
// MessageId: STATUS_VOLMGR_MEMBER_INDEX_DUPLICATE
//
// MessageText:
//
// The same member index was specified more than once.
//
#ifndef STATUS_VOLMGR_MEMBER_INDEX_DUPLICATE
#define STATUS_VOLMGR_MEMBER_INDEX_DUPLICATE ((NTSTATUS)0xC0380024L)
#endif//STATUS_VOLMGR_MEMBER_INDEX_DUPLICATE

//
// MessageId: STATUS_VOLMGR_MEMBER_INDEX_INVALID
//
// MessageText:
//
// The specified member index is greater or equal than the number of members in the volume plex.
//
#ifndef STATUS_VOLMGR_MEMBER_INDEX_INVALID
#define STATUS_VOLMGR_MEMBER_INDEX_INVALID ((NTSTATUS)0xC0380025L)
#endif//STATUS_VOLMGR_MEMBER_INDEX_INVALID

//
// MessageId: STATUS_VOLMGR_MEMBER_MISSING
//
// MessageText:
//
// The specified member is missing. It cannot be regenerated.
//
#ifndef STATUS_VOLMGR_MEMBER_MISSING
#define STATUS_VOLMGR_MEMBER_MISSING     ((NTSTATUS)0xC0380026L)
#endif//STATUS_VOLMGR_MEMBER_MISSING

//
// MessageId: STATUS_VOLMGR_MEMBER_NOT_DETACHED
//
// MessageText:
//
// The specified member is not detached. Cannot replace a member which is not detached.
//
#ifndef STATUS_VOLMGR_MEMBER_NOT_DETACHED
#define STATUS_VOLMGR_MEMBER_NOT_DETACHED ((NTSTATUS)0xC0380027L)
#endif//STATUS_VOLMGR_MEMBER_NOT_DETACHED

//
// MessageId: STATUS_VOLMGR_MEMBER_REGENERATING
//
// MessageText:
//
// The specified member is already regenerating.
//
#ifndef STATUS_VOLMGR_MEMBER_REGENERATING
#define STATUS_VOLMGR_MEMBER_REGENERATING ((NTSTATUS)0xC0380028L)
#endif//STATUS_VOLMGR_MEMBER_REGENERATING

//
// MessageId: STATUS_VOLMGR_ALL_DISKS_FAILED
//
// MessageText:
//
// All disks belonging to the pack failed.
//
#ifndef STATUS_VOLMGR_ALL_DISKS_FAILED
#define STATUS_VOLMGR_ALL_DISKS_FAILED   ((NTSTATUS)0xC0380029L)
#endif//STATUS_VOLMGR_ALL_DISKS_FAILED

//
// MessageId: STATUS_VOLMGR_NO_REGISTERED_USERS
//
// MessageText:
//
// There are currently no registered users for notifications. The task number is irrelevant unless there are registered users.
//
#ifndef STATUS_VOLMGR_NO_REGISTERED_USERS
#define STATUS_VOLMGR_NO_REGISTERED_USERS ((NTSTATUS)0xC038002AL)
#endif//STATUS_VOLMGR_NO_REGISTERED_USERS

//
// MessageId: STATUS_VOLMGR_NO_SUCH_USER
//
// MessageText:
//
// The specified notification user does not exist. Failed to unregister user for notifications.
//
#ifndef STATUS_VOLMGR_NO_SUCH_USER
#define STATUS_VOLMGR_NO_SUCH_USER       ((NTSTATUS)0xC038002BL)
#endif//STATUS_VOLMGR_NO_SUCH_USER

//
// MessageId: STATUS_VOLMGR_NOTIFICATION_RESET
//
// MessageText:
//
// The notifications have been reset. Notifications for the current user are invalid. Unregister and re-register for notifications.
//
#ifndef STATUS_VOLMGR_NOTIFICATION_RESET
#define STATUS_VOLMGR_NOTIFICATION_RESET ((NTSTATUS)0xC038002CL)
#endif//STATUS_VOLMGR_NOTIFICATION_RESET

//
// MessageId: STATUS_VOLMGR_NUMBER_OF_MEMBERS_INVALID
//
// MessageText:
//
// The specified number of members is invalid.
//
#ifndef STATUS_VOLMGR_NUMBER_OF_MEMBERS_INVALID
#define STATUS_VOLMGR_NUMBER_OF_MEMBERS_INVALID ((NTSTATUS)0xC038002DL)
#endif//STATUS_VOLMGR_NUMBER_OF_MEMBERS_INVALID

//
// MessageId: STATUS_VOLMGR_NUMBER_OF_PLEXES_INVALID
//
// MessageText:
//
// The specified number of plexes is invalid.
//
#ifndef STATUS_VOLMGR_NUMBER_OF_PLEXES_INVALID
#define STATUS_VOLMGR_NUMBER_OF_PLEXES_INVALID ((NTSTATUS)0xC038002EL)
#endif//STATUS_VOLMGR_NUMBER_OF_PLEXES_INVALID

//
// MessageId: STATUS_VOLMGR_PACK_DUPLICATE
//
// MessageText:
//
// The specified source and target packs are identical.
//
#ifndef STATUS_VOLMGR_PACK_DUPLICATE
#define STATUS_VOLMGR_PACK_DUPLICATE     ((NTSTATUS)0xC038002FL)
#endif//STATUS_VOLMGR_PACK_DUPLICATE

//
// MessageId: STATUS_VOLMGR_PACK_ID_INVALID
//
// MessageText:
//
// The specified pack id is invalid. There are no packs with the specified pack id.
//
#ifndef STATUS_VOLMGR_PACK_ID_INVALID
#define STATUS_VOLMGR_PACK_ID_INVALID    ((NTSTATUS)0xC0380030L)
#endif//STATUS_VOLMGR_PACK_ID_INVALID

//
// MessageId: STATUS_VOLMGR_PACK_INVALID
//
// MessageText:
//
// The specified pack is the invalid pack. The operation cannot complete with the invalid pack.
//
#ifndef STATUS_VOLMGR_PACK_INVALID
#define STATUS_VOLMGR_PACK_INVALID       ((NTSTATUS)0xC0380031L)
#endif//STATUS_VOLMGR_PACK_INVALID

//
// MessageId: STATUS_VOLMGR_PACK_NAME_INVALID
//
// MessageText:
//
// The specified pack name is invalid.
//
#ifndef STATUS_VOLMGR_PACK_NAME_INVALID
#define STATUS_VOLMGR_PACK_NAME_INVALID  ((NTSTATUS)0xC0380032L)
#endif//STATUS_VOLMGR_PACK_NAME_INVALID

//
// MessageId: STATUS_VOLMGR_PACK_OFFLINE
//
// MessageText:
//
// The specified pack is offline.
//
#ifndef STATUS_VOLMGR_PACK_OFFLINE
#define STATUS_VOLMGR_PACK_OFFLINE       ((NTSTATUS)0xC0380033L)
#endif//STATUS_VOLMGR_PACK_OFFLINE

//
// MessageId: STATUS_VOLMGR_PACK_HAS_QUORUM
//
// MessageText:
//
// The specified pack already has a quorum of healthy disks.
//
#ifndef STATUS_VOLMGR_PACK_HAS_QUORUM
#define STATUS_VOLMGR_PACK_HAS_QUORUM    ((NTSTATUS)0xC0380034L)
#endif//STATUS_VOLMGR_PACK_HAS_QUORUM

//
// MessageId: STATUS_VOLMGR_PACK_WITHOUT_QUORUM
//
// MessageText:
//
// The pack does not have a quorum of healthy disks.
//
#ifndef STATUS_VOLMGR_PACK_WITHOUT_QUORUM
#define STATUS_VOLMGR_PACK_WITHOUT_QUORUM ((NTSTATUS)0xC0380035L)
#endif//STATUS_VOLMGR_PACK_WITHOUT_QUORUM

//
// MessageId: STATUS_VOLMGR_PARTITION_STYLE_INVALID
//
// MessageText:
//
// The specified disk has an unsupported partition style. Only MBR and GPT partition styles are supported.
//
#ifndef STATUS_VOLMGR_PARTITION_STYLE_INVALID
#define STATUS_VOLMGR_PARTITION_STYLE_INVALID ((NTSTATUS)0xC0380036L)
#endif//STATUS_VOLMGR_PARTITION_STYLE_INVALID

//
// MessageId: STATUS_VOLMGR_PARTITION_UPDATE_FAILED
//
// MessageText:
//
// Failed to update the disk's partition layout.
//
#ifndef STATUS_VOLMGR_PARTITION_UPDATE_FAILED
#define STATUS_VOLMGR_PARTITION_UPDATE_FAILED ((NTSTATUS)0xC0380037L)
#endif//STATUS_VOLMGR_PARTITION_UPDATE_FAILED

//
// MessageId: STATUS_VOLMGR_PLEX_IN_SYNC
//
// MessageText:
//
// The specified plex is already in-sync with the other active plexes. It does not need to be regenerated.
//
#ifndef STATUS_VOLMGR_PLEX_IN_SYNC
#define STATUS_VOLMGR_PLEX_IN_SYNC       ((NTSTATUS)0xC0380038L)
#endif//STATUS_VOLMGR_PLEX_IN_SYNC

//
// MessageId: STATUS_VOLMGR_PLEX_INDEX_DUPLICATE
//
// MessageText:
//
// The same plex index was specified more than once.
//
#ifndef STATUS_VOLMGR_PLEX_INDEX_DUPLICATE
#define STATUS_VOLMGR_PLEX_INDEX_DUPLICATE ((NTSTATUS)0xC0380039L)
#endif//STATUS_VOLMGR_PLEX_INDEX_DUPLICATE

//
// MessageId: STATUS_VOLMGR_PLEX_INDEX_INVALID
//
// MessageText:
//
// The specified plex index is greater or equal than the number of plexes in the volume.
//
#ifndef STATUS_VOLMGR_PLEX_INDEX_INVALID
#define STATUS_VOLMGR_PLEX_INDEX_INVALID ((NTSTATUS)0xC038003AL)
#endif//STATUS_VOLMGR_PLEX_INDEX_INVALID

//
// MessageId: STATUS_VOLMGR_PLEX_LAST_ACTIVE
//
// MessageText:
//
// The specified plex is the last active plex in the volume. The plex cannot be removed or else the volume will go offline.
//
#ifndef STATUS_VOLMGR_PLEX_LAST_ACTIVE
#define STATUS_VOLMGR_PLEX_LAST_ACTIVE   ((NTSTATUS)0xC038003BL)
#endif//STATUS_VOLMGR_PLEX_LAST_ACTIVE

//
// MessageId: STATUS_VOLMGR_PLEX_MISSING
//
// MessageText:
//
// The specified plex is missing.
//
#ifndef STATUS_VOLMGR_PLEX_MISSING
#define STATUS_VOLMGR_PLEX_MISSING       ((NTSTATUS)0xC038003CL)
#endif//STATUS_VOLMGR_PLEX_MISSING

//
// MessageId: STATUS_VOLMGR_PLEX_REGENERATING
//
// MessageText:
//
// The specified plex is currently regenerating.
//
#ifndef STATUS_VOLMGR_PLEX_REGENERATING
#define STATUS_VOLMGR_PLEX_REGENERATING  ((NTSTATUS)0xC038003DL)
#endif//STATUS_VOLMGR_PLEX_REGENERATING

//
// MessageId: STATUS_VOLMGR_PLEX_TYPE_INVALID
//
// MessageText:
//
// The specified plex type is invalid.
//
#ifndef STATUS_VOLMGR_PLEX_TYPE_INVALID
#define STATUS_VOLMGR_PLEX_TYPE_INVALID  ((NTSTATUS)0xC038003EL)
#endif//STATUS_VOLMGR_PLEX_TYPE_INVALID

//
// MessageId: STATUS_VOLMGR_PLEX_NOT_RAID5
//
// MessageText:
//
// The operation is only supported on RAID-5 plexes.
//
#ifndef STATUS_VOLMGR_PLEX_NOT_RAID5
#define STATUS_VOLMGR_PLEX_NOT_RAID5     ((NTSTATUS)0xC038003FL)
#endif//STATUS_VOLMGR_PLEX_NOT_RAID5

//
// MessageId: STATUS_VOLMGR_PLEX_NOT_SIMPLE
//
// MessageText:
//
// The operation is only supported on simple plexes.
//
#ifndef STATUS_VOLMGR_PLEX_NOT_SIMPLE
#define STATUS_VOLMGR_PLEX_NOT_SIMPLE    ((NTSTATUS)0xC0380040L)
#endif//STATUS_VOLMGR_PLEX_NOT_SIMPLE

//
// MessageId: STATUS_VOLMGR_STRUCTURE_SIZE_INVALID
//
// MessageText:
//
// The Size fields in the VM_VOLUME_LAYOUT input structure are incorrectly set.
//
#ifndef STATUS_VOLMGR_STRUCTURE_SIZE_INVALID
#define STATUS_VOLMGR_STRUCTURE_SIZE_INVALID ((NTSTATUS)0xC0380041L)
#endif//STATUS_VOLMGR_STRUCTURE_SIZE_INVALID

//
// MessageId: STATUS_VOLMGR_TOO_MANY_NOTIFICATION_REQUESTS
//
// MessageText:
//
// There is already a pending request for notifications. Wait for the existing request to return before requesting for more notifications.
//
#ifndef STATUS_VOLMGR_TOO_MANY_NOTIFICATION_REQUESTS
#define STATUS_VOLMGR_TOO_MANY_NOTIFICATION_REQUESTS ((NTSTATUS)0xC0380042L)
#endif//STATUS_VOLMGR_TOO_MANY_NOTIFICATION_REQUESTS

//
// MessageId: STATUS_VOLMGR_TRANSACTION_IN_PROGRESS
//
// MessageText:
//
// There is currently a transaction in process.
//
#ifndef STATUS_VOLMGR_TRANSACTION_IN_PROGRESS
#define STATUS_VOLMGR_TRANSACTION_IN_PROGRESS ((NTSTATUS)0xC0380043L)
#endif//STATUS_VOLMGR_TRANSACTION_IN_PROGRESS

//
// MessageId: STATUS_VOLMGR_UNEXPECTED_DISK_LAYOUT_CHANGE
//
// MessageText:
//
// An unexpected layout change occurred outside of the volume manager.
//
#ifndef STATUS_VOLMGR_UNEXPECTED_DISK_LAYOUT_CHANGE
#define STATUS_VOLMGR_UNEXPECTED_DISK_LAYOUT_CHANGE ((NTSTATUS)0xC0380044L)
#endif//STATUS_VOLMGR_UNEXPECTED_DISK_LAYOUT_CHANGE

//
// MessageId: STATUS_VOLMGR_VOLUME_CONTAINS_MISSING_DISK
//
// MessageText:
//
// The specified volume contains a missing disk.
//
#ifndef STATUS_VOLMGR_VOLUME_CONTAINS_MISSING_DISK
#define STATUS_VOLMGR_VOLUME_CONTAINS_MISSING_DISK ((NTSTATUS)0xC0380045L)
#endif//STATUS_VOLMGR_VOLUME_CONTAINS_MISSING_DISK

//
// MessageId: STATUS_VOLMGR_VOLUME_ID_INVALID
//
// MessageText:
//
// The specified volume id is invalid. There are no volumes with the specified volume id.
//
#ifndef STATUS_VOLMGR_VOLUME_ID_INVALID
#define STATUS_VOLMGR_VOLUME_ID_INVALID  ((NTSTATUS)0xC0380046L)
#endif//STATUS_VOLMGR_VOLUME_ID_INVALID

//
// MessageId: STATUS_VOLMGR_VOLUME_LENGTH_INVALID
//
// MessageText:
//
// The specified volume length is invalid.
//
#ifndef STATUS_VOLMGR_VOLUME_LENGTH_INVALID
#define STATUS_VOLMGR_VOLUME_LENGTH_INVALID ((NTSTATUS)0xC0380047L)
#endif//STATUS_VOLMGR_VOLUME_LENGTH_INVALID

//
// MessageId: STATUS_VOLMGR_VOLUME_LENGTH_NOT_SECTOR_SIZE_MULTIPLE
//
// MessageText:
//
// The specified size for the volume is not a multiple of the sector size.
//
#ifndef STATUS_VOLMGR_VOLUME_LENGTH_NOT_SECTOR_SIZE_MULTIPLE
#define STATUS_VOLMGR_VOLUME_LENGTH_NOT_SECTOR_SIZE_MULTIPLE ((NTSTATUS)0xC0380048L)
#endif//STATUS_VOLMGR_VOLUME_LENGTH_NOT_SECTOR_SIZE_MULTIPLE

//
// MessageId: STATUS_VOLMGR_VOLUME_NOT_MIRRORED
//
// MessageText:
//
// The operation is only supported on mirrored volumes.
//
#ifndef STATUS_VOLMGR_VOLUME_NOT_MIRRORED
#define STATUS_VOLMGR_VOLUME_NOT_MIRRORED ((NTSTATUS)0xC0380049L)
#endif//STATUS_VOLMGR_VOLUME_NOT_MIRRORED

//
// MessageId: STATUS_VOLMGR_VOLUME_NOT_RETAINED
//
// MessageText:
//
// The specified volume does not have a retain partition.
//
#ifndef STATUS_VOLMGR_VOLUME_NOT_RETAINED
#define STATUS_VOLMGR_VOLUME_NOT_RETAINED ((NTSTATUS)0xC038004AL)
#endif//STATUS_VOLMGR_VOLUME_NOT_RETAINED

//
// MessageId: STATUS_VOLMGR_VOLUME_OFFLINE
//
// MessageText:
//
// The specified volume is offline.
//
#ifndef STATUS_VOLMGR_VOLUME_OFFLINE
#define STATUS_VOLMGR_VOLUME_OFFLINE     ((NTSTATUS)0xC038004BL)
#endif//STATUS_VOLMGR_VOLUME_OFFLINE

//
// MessageId: STATUS_VOLMGR_VOLUME_RETAINED
//
// MessageText:
//
// The specified volume already has a retain partition.
//
#ifndef STATUS_VOLMGR_VOLUME_RETAINED
#define STATUS_VOLMGR_VOLUME_RETAINED    ((NTSTATUS)0xC038004CL)
#endif//STATUS_VOLMGR_VOLUME_RETAINED

//
// MessageId: STATUS_VOLMGR_NUMBER_OF_EXTENTS_INVALID
//
// MessageText:
//
// The specified number of extents is invalid.
//
#ifndef STATUS_VOLMGR_NUMBER_OF_EXTENTS_INVALID
#define STATUS_VOLMGR_NUMBER_OF_EXTENTS_INVALID ((NTSTATUS)0xC038004DL)
#endif//STATUS_VOLMGR_NUMBER_OF_EXTENTS_INVALID

//
// MessageId: STATUS_VOLMGR_DIFFERENT_SECTOR_SIZE
//
// MessageText:
//
// All disks participating to the volume must have the same sector size.
//
#ifndef STATUS_VOLMGR_DIFFERENT_SECTOR_SIZE
#define STATUS_VOLMGR_DIFFERENT_SECTOR_SIZE ((NTSTATUS)0xC038004EL)
#endif//STATUS_VOLMGR_DIFFERENT_SECTOR_SIZE

//
// MessageId: STATUS_VOLMGR_BAD_BOOT_DISK
//
// MessageText:
//
// The boot disk experienced failures.
//
#ifndef STATUS_VOLMGR_BAD_BOOT_DISK
#define STATUS_VOLMGR_BAD_BOOT_DISK      ((NTSTATUS)0xC038004FL)
#endif//STATUS_VOLMGR_BAD_BOOT_DISK

//
// MessageId: STATUS_VOLMGR_PACK_CONFIG_OFFLINE
//
// MessageText:
//
// The configuration of the pack is offline.
//
#ifndef STATUS_VOLMGR_PACK_CONFIG_OFFLINE
#define STATUS_VOLMGR_PACK_CONFIG_OFFLINE ((NTSTATUS)0xC0380050L)
#endif//STATUS_VOLMGR_PACK_CONFIG_OFFLINE

//
// MessageId: STATUS_VOLMGR_PACK_CONFIG_ONLINE
//
// MessageText:
//
// The configuration of the pack is online.
//
#ifndef STATUS_VOLMGR_PACK_CONFIG_ONLINE
#define STATUS_VOLMGR_PACK_CONFIG_ONLINE ((NTSTATUS)0xC0380051L)
#endif//STATUS_VOLMGR_PACK_CONFIG_ONLINE

//
// MessageId: STATUS_VOLMGR_NOT_PRIMARY_PACK
//
// MessageText:
//
// The specified pack is not the primary pack.
//
#ifndef STATUS_VOLMGR_NOT_PRIMARY_PACK
#define STATUS_VOLMGR_NOT_PRIMARY_PACK   ((NTSTATUS)0xC0380052L)
#endif//STATUS_VOLMGR_NOT_PRIMARY_PACK

//
// MessageId: STATUS_VOLMGR_PACK_LOG_UPDATE_FAILED
//
// MessageText:
//
// All disks failed to be updated with the new content of the log.
//
#ifndef STATUS_VOLMGR_PACK_LOG_UPDATE_FAILED
#define STATUS_VOLMGR_PACK_LOG_UPDATE_FAILED ((NTSTATUS)0xC0380053L)
#endif//STATUS_VOLMGR_PACK_LOG_UPDATE_FAILED

//
// MessageId: STATUS_VOLMGR_NUMBER_OF_DISKS_IN_PLEX_INVALID
//
// MessageText:
//
// The specified number of disks in a plex is invalid.
//
#ifndef STATUS_VOLMGR_NUMBER_OF_DISKS_IN_PLEX_INVALID
#define STATUS_VOLMGR_NUMBER_OF_DISKS_IN_PLEX_INVALID ((NTSTATUS)0xC0380054L)
#endif//STATUS_VOLMGR_NUMBER_OF_DISKS_IN_PLEX_INVALID

//
// MessageId: STATUS_VOLMGR_NUMBER_OF_DISKS_IN_MEMBER_INVALID
//
// MessageText:
//
// The specified number of disks in a plex member is invalid.
//
#ifndef STATUS_VOLMGR_NUMBER_OF_DISKS_IN_MEMBER_INVALID
#define STATUS_VOLMGR_NUMBER_OF_DISKS_IN_MEMBER_INVALID ((NTSTATUS)0xC0380055L)
#endif//STATUS_VOLMGR_NUMBER_OF_DISKS_IN_MEMBER_INVALID

//
// MessageId: STATUS_VOLMGR_VOLUME_MIRRORED
//
// MessageText:
//
// The operation is not supported on mirrored volumes.
//
#ifndef STATUS_VOLMGR_VOLUME_MIRRORED
#define STATUS_VOLMGR_VOLUME_MIRRORED    ((NTSTATUS)0xC0380056L)
#endif//STATUS_VOLMGR_VOLUME_MIRRORED

//
// MessageId: STATUS_VOLMGR_PLEX_NOT_SIMPLE_SPANNED
//
// MessageText:
//
// The operation is only supported on simple and spanned plexes.
//
#ifndef STATUS_VOLMGR_PLEX_NOT_SIMPLE_SPANNED
#define STATUS_VOLMGR_PLEX_NOT_SIMPLE_SPANNED ((NTSTATUS)0xC0380057L)
#endif//STATUS_VOLMGR_PLEX_NOT_SIMPLE_SPANNED

//
// MessageId: STATUS_VOLMGR_NO_VALID_LOG_COPIES
//
// MessageText:
//
// The pack has no valid log copies.
//
#ifndef STATUS_VOLMGR_NO_VALID_LOG_COPIES
#define STATUS_VOLMGR_NO_VALID_LOG_COPIES ((NTSTATUS)0xC0380058L)
#endif//STATUS_VOLMGR_NO_VALID_LOG_COPIES

//
// MessageId: STATUS_VOLMGR_PRIMARY_PACK_PRESENT
//
// MessageText:
//
// A primary pack is already present.
//
#ifndef STATUS_VOLMGR_PRIMARY_PACK_PRESENT
#define STATUS_VOLMGR_PRIMARY_PACK_PRESENT ((NTSTATUS)0xC0380059L)
#endif//STATUS_VOLMGR_PRIMARY_PACK_PRESENT

//
// MessageId: STATUS_VOLMGR_NUMBER_OF_DISKS_INVALID
//
// MessageText:
//
// The specified number of disks is invalid.
//
#ifndef STATUS_VOLMGR_NUMBER_OF_DISKS_INVALID
#define STATUS_VOLMGR_NUMBER_OF_DISKS_INVALID ((NTSTATUS)0xC038005AL)
#endif//STATUS_VOLMGR_NUMBER_OF_DISKS_INVALID

//
// MessageId: STATUS_VOLMGR_MIRROR_NOT_SUPPORTED
//
// MessageText:
//
// The system does not support mirrored volumes.
//
#ifndef STATUS_VOLMGR_MIRROR_NOT_SUPPORTED
#define STATUS_VOLMGR_MIRROR_NOT_SUPPORTED ((NTSTATUS)0xC038005BL)
#endif//STATUS_VOLMGR_MIRROR_NOT_SUPPORTED

//
// MessageId: STATUS_VOLMGR_RAID5_NOT_SUPPORTED
//
// MessageText:
//
// The system does not support RAID-5 volumes.
//
#ifndef STATUS_VOLMGR_RAID5_NOT_SUPPORTED
#define STATUS_VOLMGR_RAID5_NOT_SUPPORTED ((NTSTATUS)0xC038005CL)
#endif//STATUS_VOLMGR_RAID5_NOT_SUPPORTED

//
// Boot Code Data (BCD) status codes
//

//
// MessageId: STATUS_BCD_NOT_ALL_ENTRIES_IMPORTED
//
// MessageText:
//
// Some BCD entries were not imported correctly from the BCD store.
//
#ifndef STATUS_BCD_NOT_ALL_ENTRIES_IMPORTED
#define STATUS_BCD_NOT_ALL_ENTRIES_IMPORTED ((NTSTATUS)0x80390001L)
#endif//STATUS_BCD_NOT_ALL_ENTRIES_IMPORTED

//
// MessageId: STATUS_BCD_TOO_MANY_ELEMENTS
//
// MessageText:
//
// Entries enumerated have exceeded the allowed threshold.
//
#ifndef STATUS_BCD_TOO_MANY_ELEMENTS
#define STATUS_BCD_TOO_MANY_ELEMENTS     ((NTSTATUS)0xC0390002L)
#endif//STATUS_BCD_TOO_MANY_ELEMENTS

//
// MessageId: STATUS_BCD_NOT_ALL_ENTRIES_SYNCHRONIZED
//
// MessageText:
//
// Some BCD entries were not synchronized correctly with the firmware.
//
#ifndef STATUS_BCD_NOT_ALL_ENTRIES_SYNCHRONIZED
#define STATUS_BCD_NOT_ALL_ENTRIES_SYNCHRONIZED ((NTSTATUS)0x80390003L)
#endif//STATUS_BCD_NOT_ALL_ENTRIES_SYNCHRONIZED


//
// vhdparser error codes (vhdmp.sys)
//

//
// MessageId: STATUS_VHD_DRIVE_FOOTER_MISSING
//
// MessageText:
//
// The virtual hard disk is corrupted. The virtual hard disk drive footer is missing.
//
#ifndef STATUS_VHD_DRIVE_FOOTER_MISSING
#define STATUS_VHD_DRIVE_FOOTER_MISSING  ((NTSTATUS)0xC03A0001L)
#endif//STATUS_VHD_DRIVE_FOOTER_MISSING

//
// MessageId: STATUS_VHD_DRIVE_FOOTER_CHECKSUM_MISMATCH
//
// MessageText:
//
// The virtual hard disk is corrupted. The virtual hard disk drive footer checksum does not match the on-disk checksum.
//
#ifndef STATUS_VHD_DRIVE_FOOTER_CHECKSUM_MISMATCH
#define STATUS_VHD_DRIVE_FOOTER_CHECKSUM_MISMATCH ((NTSTATUS)0xC03A0002L)
#endif//STATUS_VHD_DRIVE_FOOTER_CHECKSUM_MISMATCH

//
// MessageId: STATUS_VHD_DRIVE_FOOTER_CORRUPT
//
// MessageText:
//
// The virtual hard disk is corrupted. The virtual hard disk drive footer in the virtual hard disk is corrupted.
//
#ifndef STATUS_VHD_DRIVE_FOOTER_CORRUPT
#define STATUS_VHD_DRIVE_FOOTER_CORRUPT  ((NTSTATUS)0xC03A0003L)
#endif//STATUS_VHD_DRIVE_FOOTER_CORRUPT

//
// MessageId: STATUS_VHD_FORMAT_UNKNOWN
//
// MessageText:
//
// The system does not recognize the file format of this virtual hard disk.
//
#ifndef STATUS_VHD_FORMAT_UNKNOWN
#define STATUS_VHD_FORMAT_UNKNOWN        ((NTSTATUS)0xC03A0004L)
#endif//STATUS_VHD_FORMAT_UNKNOWN

//
// MessageId: STATUS_VHD_FORMAT_UNSUPPORTED_VERSION
//
// MessageText:
//
// The version does not support this version of the file format.
//
#ifndef STATUS_VHD_FORMAT_UNSUPPORTED_VERSION
#define STATUS_VHD_FORMAT_UNSUPPORTED_VERSION ((NTSTATUS)0xC03A0005L)
#endif//STATUS_VHD_FORMAT_UNSUPPORTED_VERSION

//
// MessageId: STATUS_VHD_SPARSE_HEADER_CHECKSUM_MISMATCH
//
// MessageText:
//
// The virtual hard disk is corrupted. The sparse header checksum does not match the on-disk checksum.
//
#ifndef STATUS_VHD_SPARSE_HEADER_CHECKSUM_MISMATCH
#define STATUS_VHD_SPARSE_HEADER_CHECKSUM_MISMATCH ((NTSTATUS)0xC03A0006L)
#endif//STATUS_VHD_SPARSE_HEADER_CHECKSUM_MISMATCH

//
// MessageId: STATUS_VHD_SPARSE_HEADER_UNSUPPORTED_VERSION
//
// MessageText:
//
// The system does not support this version of the virtual hard disk.This version of the sparse header is not supported.
//
#ifndef STATUS_VHD_SPARSE_HEADER_UNSUPPORTED_VERSION
#define STATUS_VHD_SPARSE_HEADER_UNSUPPORTED_VERSION ((NTSTATUS)0xC03A0007L)
#endif//STATUS_VHD_SPARSE_HEADER_UNSUPPORTED_VERSION

//
// MessageId: STATUS_VHD_SPARSE_HEADER_CORRUPT
//
// MessageText:
//
// The virtual hard disk is corrupted. The sparse header in the virtual hard disk is corrupt.
//
#ifndef STATUS_VHD_SPARSE_HEADER_CORRUPT
#define STATUS_VHD_SPARSE_HEADER_CORRUPT ((NTSTATUS)0xC03A0008L)
#endif//STATUS_VHD_SPARSE_HEADER_CORRUPT

//
// MessageId: STATUS_VHD_BLOCK_ALLOCATION_FAILURE
//
// MessageText:
//
// Failed to write to the virtual hard disk failed because the system failed to allocate a new block in the virtual hard disk.
//
#ifndef STATUS_VHD_BLOCK_ALLOCATION_FAILURE
#define STATUS_VHD_BLOCK_ALLOCATION_FAILURE ((NTSTATUS)0xC03A0009L)
#endif//STATUS_VHD_BLOCK_ALLOCATION_FAILURE

//
// MessageId: STATUS_VHD_BLOCK_ALLOCATION_TABLE_CORRUPT
//
// MessageText:
//
// The virtual hard disk is corrupted. The block allocation table in the virtual hard disk is corrupt.
//
#ifndef STATUS_VHD_BLOCK_ALLOCATION_TABLE_CORRUPT
#define STATUS_VHD_BLOCK_ALLOCATION_TABLE_CORRUPT ((NTSTATUS)0xC03A000AL)
#endif//STATUS_VHD_BLOCK_ALLOCATION_TABLE_CORRUPT

//
// MessageId: STATUS_VHD_INVALID_BLOCK_SIZE
//
// MessageText:
//
// The system does not support this version of the virtual hard disk. The block size is invalid.
//
#ifndef STATUS_VHD_INVALID_BLOCK_SIZE
#define STATUS_VHD_INVALID_BLOCK_SIZE    ((NTSTATUS)0xC03A000BL)
#endif//STATUS_VHD_INVALID_BLOCK_SIZE

//
// MessageId: STATUS_VHD_BITMAP_MISMATCH
//
// MessageText:
//
// The virtual hard disk is corrupted. The block bitmap does not match with the block data present in the virtual hard disk.
//
#ifndef STATUS_VHD_BITMAP_MISMATCH
#define STATUS_VHD_BITMAP_MISMATCH       ((NTSTATUS)0xC03A000CL)
#endif//STATUS_VHD_BITMAP_MISMATCH

//
// MessageId: STATUS_VHD_PARENT_VHD_NOT_FOUND
//
// MessageText:
//
// The chain of virtual hard disks is broken. The system cannot locate the parent virtual hard disk for the differencing disk.
//
#ifndef STATUS_VHD_PARENT_VHD_NOT_FOUND
#define STATUS_VHD_PARENT_VHD_NOT_FOUND  ((NTSTATUS)0xC03A000DL)
#endif//STATUS_VHD_PARENT_VHD_NOT_FOUND

//
// MessageId: STATUS_VHD_CHILD_PARENT_ID_MISMATCH
//
// MessageText:
//
// The chain of virtual hard disks is corrupted. There is a mismatch in the identifiers of the parent virtual hard disk and differencing disk.
//
#ifndef STATUS_VHD_CHILD_PARENT_ID_MISMATCH
#define STATUS_VHD_CHILD_PARENT_ID_MISMATCH ((NTSTATUS)0xC03A000EL)
#endif//STATUS_VHD_CHILD_PARENT_ID_MISMATCH

//
// MessageId: STATUS_VHD_CHILD_PARENT_TIMESTAMP_MISMATCH
//
// MessageText:
//
// The chain of virtual hard disks is corrupted. The time stamp of the parent virtual hard disk does not match the time stamp of the differencing disk.
//
#ifndef STATUS_VHD_CHILD_PARENT_TIMESTAMP_MISMATCH
#define STATUS_VHD_CHILD_PARENT_TIMESTAMP_MISMATCH ((NTSTATUS)0xC03A000FL)
#endif//STATUS_VHD_CHILD_PARENT_TIMESTAMP_MISMATCH

//
// MessageId: STATUS_VHD_METADATA_READ_FAILURE
//
// MessageText:
//
// Failed to read the metadata of the virtual hard disk.
//
#ifndef STATUS_VHD_METADATA_READ_FAILURE
#define STATUS_VHD_METADATA_READ_FAILURE ((NTSTATUS)0xC03A0010L)
#endif//STATUS_VHD_METADATA_READ_FAILURE

//
// MessageId: STATUS_VHD_METADATA_WRITE_FAILURE
//
// MessageText:
//
// Failed to write to the metadata of the virtual hard disk.
//
#ifndef STATUS_VHD_METADATA_WRITE_FAILURE
#define STATUS_VHD_METADATA_WRITE_FAILURE ((NTSTATUS)0xC03A0011L)
#endif//STATUS_VHD_METADATA_WRITE_FAILURE

//
// MessageId: STATUS_VHD_INVALID_SIZE
//
// MessageText:
//
// The size of the virtual hard disk is not valid.
//
#ifndef STATUS_VHD_INVALID_SIZE
#define STATUS_VHD_INVALID_SIZE          ((NTSTATUS)0xC03A0012L)
#endif//STATUS_VHD_INVALID_SIZE

//
// MessageId: STATUS_VHD_INVALID_FILE_SIZE
//
// MessageText:
//
// The file size of this virtual hard disk is not valid.
//
#ifndef STATUS_VHD_INVALID_FILE_SIZE
#define STATUS_VHD_INVALID_FILE_SIZE     ((NTSTATUS)0xC03A0013L)
#endif//STATUS_VHD_INVALID_FILE_SIZE

//
// MessageId: STATUS_VIRTDISK_PROVIDER_NOT_FOUND
//
// MessageText:
//
// A virtual disk support provider for the specified file was not found.
//
#ifndef STATUS_VIRTDISK_PROVIDER_NOT_FOUND
#define STATUS_VIRTDISK_PROVIDER_NOT_FOUND ((NTSTATUS)0xC03A0014L)
#endif//STATUS_VIRTDISK_PROVIDER_NOT_FOUND

//
// MessageId: STATUS_VIRTDISK_NOT_VIRTUAL_DISK
//
// MessageText:
//
// The specified disk is not a virtual disk.
//
#ifndef STATUS_VIRTDISK_NOT_VIRTUAL_DISK
#define STATUS_VIRTDISK_NOT_VIRTUAL_DISK ((NTSTATUS)0xC03A0015L)
#endif//STATUS_VIRTDISK_NOT_VIRTUAL_DISK

//
// MessageId: STATUS_VHD_PARENT_VHD_ACCESS_DENIED
//
// MessageText:
//
// The chain of virtual hard disks is inaccessible. The process has not been granted access rights to the parent virtual hard disk for the differencing disk.
//
#ifndef STATUS_VHD_PARENT_VHD_ACCESS_DENIED
#define STATUS_VHD_PARENT_VHD_ACCESS_DENIED ((NTSTATUS)0xC03A0016L)
#endif//STATUS_VHD_PARENT_VHD_ACCESS_DENIED

//
// MessageId: STATUS_VHD_CHILD_PARENT_SIZE_MISMATCH
//
// MessageText:
//
// The chain of virtual hard disks is corrupted. There is a mismatch in the virtual sizes of the parent virtual hard disk and differencing disk.
//
#ifndef STATUS_VHD_CHILD_PARENT_SIZE_MISMATCH
#define STATUS_VHD_CHILD_PARENT_SIZE_MISMATCH ((NTSTATUS)0xC03A0017L)
#endif//STATUS_VHD_CHILD_PARENT_SIZE_MISMATCH

//
// MessageId: STATUS_VHD_DIFFERENCING_CHAIN_CYCLE_DETECTED
//
// MessageText:
//
// The chain of virtual hard disks is corrupted. A differencing disk is indicated in its own parent chain.
//
#ifndef STATUS_VHD_DIFFERENCING_CHAIN_CYCLE_DETECTED
#define STATUS_VHD_DIFFERENCING_CHAIN_CYCLE_DETECTED ((NTSTATUS)0xC03A0018L)
#endif//STATUS_VHD_DIFFERENCING_CHAIN_CYCLE_DETECTED

//
// MessageId: STATUS_VHD_DIFFERENCING_CHAIN_ERROR_IN_PARENT
//
// MessageText:
//
// The chain of virtual hard disks is inaccessible. There was an error opening a virtual hard disk further up the chain.
//
#ifndef STATUS_VHD_DIFFERENCING_CHAIN_ERROR_IN_PARENT
#define STATUS_VHD_DIFFERENCING_CHAIN_ERROR_IN_PARENT ((NTSTATUS)0xC03A0019L)
#endif//STATUS_VHD_DIFFERENCING_CHAIN_ERROR_IN_PARENT

//
// MessageId: STATUS_VIRTUAL_DISK_LIMITATION
//
// MessageText:
//
// The requested operation could not be completed due to a virtual disk system limitation.  Virtual hard disk files must be uncompressed and unencrypted and must not be sparse.
//
#ifndef STATUS_VIRTUAL_DISK_LIMITATION
#define STATUS_VIRTUAL_DISK_LIMITATION   ((NTSTATUS)0xC03A001AL)
#endif//STATUS_VIRTUAL_DISK_LIMITATION

//
// MessageId: STATUS_VHD_INVALID_TYPE
//
// MessageText:
//
// The requested operation cannot be performed on a virtual disk of this type.
//
#ifndef STATUS_VHD_INVALID_TYPE
#define STATUS_VHD_INVALID_TYPE          ((NTSTATUS)0xC03A001BL)
#endif//STATUS_VHD_INVALID_TYPE

//
// MessageId: STATUS_VHD_INVALID_STATE
//
// MessageText:
//
// The requested operation cannot be performed on the virtual disk in its current state.
//
#ifndef STATUS_VHD_INVALID_STATE
#define STATUS_VHD_INVALID_STATE         ((NTSTATUS)0xC03A001CL)
#endif//STATUS_VHD_INVALID_STATE

//
// MessageId: STATUS_VIRTDISK_UNSUPPORTED_DISK_SECTOR_SIZE
//
// MessageText:
//
// The sector size of the physical disk on which the virtual disk resides is not supported.
//
#ifndef STATUS_VIRTDISK_UNSUPPORTED_DISK_SECTOR_SIZE
#define STATUS_VIRTDISK_UNSUPPORTED_DISK_SECTOR_SIZE ((NTSTATUS)0xC03A001DL)
#endif//STATUS_VIRTDISK_UNSUPPORTED_DISK_SECTOR_SIZE

//
// MessageId: STATUS_VIRTDISK_DISK_ALREADY_OWNED
//
// MessageText:
//
// The disk is already owned by a different owner.
//
#ifndef STATUS_VIRTDISK_DISK_ALREADY_OWNED
#define STATUS_VIRTDISK_DISK_ALREADY_OWNED ((NTSTATUS)0xC03A001EL)
#endif//STATUS_VIRTDISK_DISK_ALREADY_OWNED

//
// MessageId: STATUS_VIRTDISK_DISK_ONLINE_AND_WRITABLE
//
// MessageText:
//
// The disk must be offline or read-only.
//
#ifndef STATUS_VIRTDISK_DISK_ONLINE_AND_WRITABLE
#define STATUS_VIRTDISK_DISK_ONLINE_AND_WRITABLE ((NTSTATUS)0xC03A001FL)
#endif//STATUS_VIRTDISK_DISK_ONLINE_AND_WRITABLE

//
// MessageId: STATUS_CTLOG_TRACKING_NOT_INITIALIZED
//
// MessageText:
//
// Change Tracking is not initialized for this virtual disk.
//
#ifndef STATUS_CTLOG_TRACKING_NOT_INITIALIZED
#define STATUS_CTLOG_TRACKING_NOT_INITIALIZED ((NTSTATUS)0xC03A0020L)
#endif//STATUS_CTLOG_TRACKING_NOT_INITIALIZED

//
// MessageId: STATUS_CTLOG_LOGFILE_SIZE_EXCEEDED_MAXSIZE
//
// MessageText:
//
// Size of change tracking file exceeded the maximum size limit.
//
#ifndef STATUS_CTLOG_LOGFILE_SIZE_EXCEEDED_MAXSIZE
#define STATUS_CTLOG_LOGFILE_SIZE_EXCEEDED_MAXSIZE ((NTSTATUS)0xC03A0021L)
#endif//STATUS_CTLOG_LOGFILE_SIZE_EXCEEDED_MAXSIZE

//
// MessageId: STATUS_CTLOG_VHD_CHANGED_OFFLINE
//
// MessageText:
//
// VHD file is changed due to compaction, expansion, or offline updates.
//
#ifndef STATUS_CTLOG_VHD_CHANGED_OFFLINE
#define STATUS_CTLOG_VHD_CHANGED_OFFLINE ((NTSTATUS)0xC03A0022L)
#endif//STATUS_CTLOG_VHD_CHANGED_OFFLINE

//
// MessageId: STATUS_CTLOG_INVALID_TRACKING_STATE
//
// MessageText:
//
// Change Tracking for the virtual disk is not in a valid state to perform this request.  Change tracking could be discontinued or already in the requested state.
//
#ifndef STATUS_CTLOG_INVALID_TRACKING_STATE
#define STATUS_CTLOG_INVALID_TRACKING_STATE ((NTSTATUS)0xC03A0023L)
#endif//STATUS_CTLOG_INVALID_TRACKING_STATE

//
// MessageId: STATUS_CTLOG_INCONSISTENT_TRACKING_FILE
//
// MessageText:
//
// Change Tracking file for the virtual disk is not in a valid state.
//
#ifndef STATUS_CTLOG_INCONSISTENT_TRACKING_FILE
#define STATUS_CTLOG_INCONSISTENT_TRACKING_FILE ((NTSTATUS)0xC03A0024L)
#endif//STATUS_CTLOG_INCONSISTENT_TRACKING_FILE

//
// MessageId: STATUS_VHD_METADATA_FULL
//
// MessageText:
//
// There is not enough space in the virtual disk file for the provided metadata item.
//
#ifndef STATUS_VHD_METADATA_FULL
#define STATUS_VHD_METADATA_FULL         ((NTSTATUS)0xC03A0028L)
#endif//STATUS_VHD_METADATA_FULL

//
// MessageId: STATUS_VHD_INVALID_CHANGE_TRACKING_ID
//
// MessageText:
//
// The specified change tracking identifier is not valid.
//
#ifndef STATUS_VHD_INVALID_CHANGE_TRACKING_ID
#define STATUS_VHD_INVALID_CHANGE_TRACKING_ID ((NTSTATUS)0xC03A0029L)
#endif//STATUS_VHD_INVALID_CHANGE_TRACKING_ID

//
// MessageId: STATUS_VHD_CHANGE_TRACKING_DISABLED
//
// MessageText:
//
// Change tracking is disabled for the specified virtual hard disk, so no change tracking information is available.
//
#ifndef STATUS_VHD_CHANGE_TRACKING_DISABLED
#define STATUS_VHD_CHANGE_TRACKING_DISABLED ((NTSTATUS)0xC03A002AL)
#endif//STATUS_VHD_CHANGE_TRACKING_DISABLED

//
// MessageId: STATUS_VHD_MISSING_CHANGE_TRACKING_INFORMATION
//
// MessageText:
//
// There is no change tracking data available associated with the specified change tracking identifier.
//
#ifndef STATUS_VHD_MISSING_CHANGE_TRACKING_INFORMATION
#define STATUS_VHD_MISSING_CHANGE_TRACKING_INFORMATION ((NTSTATUS)0xC03A0030L)
#endif//STATUS_VHD_MISSING_CHANGE_TRACKING_INFORMATION

//
// MessageId: STATUS_VHD_RESIZE_WOULD_TRUNCATE_DATA
//
// MessageText:
//
// The requested resize operation might truncate user data residing on the virtual disk.
//
#ifndef STATUS_VHD_RESIZE_WOULD_TRUNCATE_DATA
#define STATUS_VHD_RESIZE_WOULD_TRUNCATE_DATA ((NTSTATUS)0xC03A0031L)
#endif//STATUS_VHD_RESIZE_WOULD_TRUNCATE_DATA

//
// MessageId: STATUS_VHD_COULD_NOT_COMPUTE_MINIMUM_VIRTUAL_SIZE
//
// MessageText:
//
// The minimum safe size of the virtual disk could not be determined. This may be due to a missing or corrupt partition table.
//
#ifndef STATUS_VHD_COULD_NOT_COMPUTE_MINIMUM_VIRTUAL_SIZE
#define STATUS_VHD_COULD_NOT_COMPUTE_MINIMUM_VIRTUAL_SIZE ((NTSTATUS)0xC03A0032L)
#endif//STATUS_VHD_COULD_NOT_COMPUTE_MINIMUM_VIRTUAL_SIZE

//
// MessageId: STATUS_VHD_ALREADY_AT_OR_BELOW_MINIMUM_VIRTUAL_SIZE
//
// MessageText:
//
// The size of the virtual disk cannot be safely reduced further.
//
#ifndef STATUS_VHD_ALREADY_AT_OR_BELOW_MINIMUM_VIRTUAL_SIZE
#define STATUS_VHD_ALREADY_AT_OR_BELOW_MINIMUM_VIRTUAL_SIZE ((NTSTATUS)0xC03A0033L)
#endif//STATUS_VHD_ALREADY_AT_OR_BELOW_MINIMUM_VIRTUAL_SIZE


//
// Vhd warnings.
//

//
// MessageId: STATUS_QUERY_STORAGE_ERROR
//
// MessageText:
//
// The virtualization storage subsystem has generated an error.
//
#ifndef STATUS_QUERY_STORAGE_ERROR
#define STATUS_QUERY_STORAGE_ERROR       ((NTSTATUS)0x803A0001L)
#endif//STATUS_QUERY_STORAGE_ERROR


//
// NtGdi warnings.
//

//
// MessageId: STATUS_GDI_HANDLE_LEAK
//
// MessageText:
//
// GDI handles were potentially leaked by the application.
//
#ifndef STATUS_GDI_HANDLE_LEAK
#define STATUS_GDI_HANDLE_LEAK           ((NTSTATUS)0x803F0001L)
#endif//STATUS_GDI_HANDLE_LEAK


//
// Resume Key Filter (RKF) error codes.
//
//
// MessageId: STATUS_RKF_KEY_NOT_FOUND
//
// MessageText:
//
// The Resume Key Filter could not find the resume key supplied for the operation.
//
#ifndef STATUS_RKF_KEY_NOT_FOUND
#define STATUS_RKF_KEY_NOT_FOUND         ((NTSTATUS)0xC0400001L)
#endif//STATUS_RKF_KEY_NOT_FOUND

//
// MessageId: STATUS_RKF_DUPLICATE_KEY
//
// MessageText:
//
// The Resume Key Filter found an existing resume key that matches the one supplied for the handle.
//
#ifndef STATUS_RKF_DUPLICATE_KEY
#define STATUS_RKF_DUPLICATE_KEY         ((NTSTATUS)0xC0400002L)
#endif//STATUS_RKF_DUPLICATE_KEY

//
// MessageId: STATUS_RKF_BLOB_FULL
//
// MessageText:
//
// The Resume Key Filter data blob attached to the handle is full. No more space is available.
//
#ifndef STATUS_RKF_BLOB_FULL
#define STATUS_RKF_BLOB_FULL             ((NTSTATUS)0xC0400003L)
#endif//STATUS_RKF_BLOB_FULL

//
// MessageId: STATUS_RKF_STORE_FULL
//
// MessageText:
//
// The Resume Key Filter handle store is full. No more resume handles can be accepted.
//
#ifndef STATUS_RKF_STORE_FULL
#define STATUS_RKF_STORE_FULL            ((NTSTATUS)0xC0400004L)
#endif//STATUS_RKF_STORE_FULL

//
// MessageId: STATUS_RKF_FILE_BLOCKED
//
// MessageText:
//
// The Resume Key Filter failed the operation because the file is temporarily blocked pending the resume of existing handles on the file.
//
#ifndef STATUS_RKF_FILE_BLOCKED
#define STATUS_RKF_FILE_BLOCKED          ((NTSTATUS)0xC0400005L)
#endif//STATUS_RKF_FILE_BLOCKED

//
// MessageId: STATUS_RKF_ACTIVE_KEY
//
// MessageText:
//
// The Resume Key Filter found an existing resume key that matches the one supplied on a handle that's active/open. The operation requires an inactive/closed handle.
//
#ifndef STATUS_RKF_ACTIVE_KEY
#define STATUS_RKF_ACTIVE_KEY            ((NTSTATUS)0xC0400006L)
#endif//STATUS_RKF_ACTIVE_KEY


//
// RDBSS / MiniRdr internal error codes.
//
//
// MessageId: STATUS_RDBSS_RESTART_OPERATION
//
// MessageText:
//
// The operation must be restarted by RDBSS.
//
#ifndef STATUS_RDBSS_RESTART_OPERATION
#define STATUS_RDBSS_RESTART_OPERATION   ((NTSTATUS)0xC0410001L)
#endif//STATUS_RDBSS_RESTART_OPERATION

//
// MessageId: STATUS_RDBSS_CONTINUE_OPERATION
//
// MessageText:
//
// The operation must continue processing.
//
#ifndef STATUS_RDBSS_CONTINUE_OPERATION
#define STATUS_RDBSS_CONTINUE_OPERATION  ((NTSTATUS)0xC0410002L)
#endif//STATUS_RDBSS_CONTINUE_OPERATION

//
// MessageId: STATUS_RDBSS_POST_OPERATION
//
// MessageText:
//
// The operation must be posted to a thread to be retried at passive IRQL.
//
#ifndef STATUS_RDBSS_POST_OPERATION
#define STATUS_RDBSS_POST_OPERATION      ((NTSTATUS)0xC0410003L)
#endif//STATUS_RDBSS_POST_OPERATION

//
// MessageId: STATUS_RDBSS_RETRY_LOOKUP
//
// MessageText:
//
// The caller must retry by looking up the object in the name table.
//
#ifndef STATUS_RDBSS_RETRY_LOOKUP
#define STATUS_RDBSS_RETRY_LOOKUP        ((NTSTATUS)0xC0410004L)
#endif//STATUS_RDBSS_RETRY_LOOKUP

//
// Bluetooth Attribute Protocol Warnings
//

//
// MessageId: STATUS_BTH_ATT_INVALID_HANDLE
//
// MessageText:
//
// The attribute handle given was not valid on this server.
//
#ifndef STATUS_BTH_ATT_INVALID_HANDLE
#define STATUS_BTH_ATT_INVALID_HANDLE    ((NTSTATUS)0xC0420001L)
#endif//STATUS_BTH_ATT_INVALID_HANDLE

//
// MessageId: STATUS_BTH_ATT_READ_NOT_PERMITTED
//
// MessageText:
//
// The attribute cannot be read.
//
#ifndef STATUS_BTH_ATT_READ_NOT_PERMITTED
#define STATUS_BTH_ATT_READ_NOT_PERMITTED ((NTSTATUS)0xC0420002L)
#endif//STATUS_BTH_ATT_READ_NOT_PERMITTED

//
// MessageId: STATUS_BTH_ATT_WRITE_NOT_PERMITTED
//
// MessageText:
//
// The attribute cannot be written.
//
#ifndef STATUS_BTH_ATT_WRITE_NOT_PERMITTED
#define STATUS_BTH_ATT_WRITE_NOT_PERMITTED ((NTSTATUS)0xC0420003L)
#endif//STATUS_BTH_ATT_WRITE_NOT_PERMITTED

//
// MessageId: STATUS_BTH_ATT_INVALID_PDU
//
// MessageText:
//
// The attribute PDU was invalid.
//
#ifndef STATUS_BTH_ATT_INVALID_PDU
#define STATUS_BTH_ATT_INVALID_PDU       ((NTSTATUS)0xC0420004L)
#endif//STATUS_BTH_ATT_INVALID_PDU

//
// MessageId: STATUS_BTH_ATT_INSUFFICIENT_AUTHENTICATION
//
// MessageText:
//
// The attribute requires authentication before it can be read or written.
//
#ifndef STATUS_BTH_ATT_INSUFFICIENT_AUTHENTICATION
#define STATUS_BTH_ATT_INSUFFICIENT_AUTHENTICATION ((NTSTATUS)0xC0420005L)
#endif//STATUS_BTH_ATT_INSUFFICIENT_AUTHENTICATION

//
// MessageId: STATUS_BTH_ATT_REQUEST_NOT_SUPPORTED
//
// MessageText:
//
// Attribute server does not support the request received from the client.
//
#ifndef STATUS_BTH_ATT_REQUEST_NOT_SUPPORTED
#define STATUS_BTH_ATT_REQUEST_NOT_SUPPORTED ((NTSTATUS)0xC0420006L)
#endif//STATUS_BTH_ATT_REQUEST_NOT_SUPPORTED

//
// MessageId: STATUS_BTH_ATT_INVALID_OFFSET
//
// MessageText:
//
// Offset specified was past the end of the attribute.
//
#ifndef STATUS_BTH_ATT_INVALID_OFFSET
#define STATUS_BTH_ATT_INVALID_OFFSET    ((NTSTATUS)0xC0420007L)
#endif//STATUS_BTH_ATT_INVALID_OFFSET

//
// MessageId: STATUS_BTH_ATT_INSUFFICIENT_AUTHORIZATION
//
// MessageText:
//
// The attribute requires authorization before it can be read or written.
//
#ifndef STATUS_BTH_ATT_INSUFFICIENT_AUTHORIZATION
#define STATUS_BTH_ATT_INSUFFICIENT_AUTHORIZATION ((NTSTATUS)0xC0420008L)
#endif//STATUS_BTH_ATT_INSUFFICIENT_AUTHORIZATION

//
// MessageId: STATUS_BTH_ATT_PREPARE_QUEUE_FULL
//
// MessageText:
//
// Too many prepare writes have been queued.
//
#ifndef STATUS_BTH_ATT_PREPARE_QUEUE_FULL
#define STATUS_BTH_ATT_PREPARE_QUEUE_FULL ((NTSTATUS)0xC0420009L)
#endif//STATUS_BTH_ATT_PREPARE_QUEUE_FULL

//
// MessageId: STATUS_BTH_ATT_ATTRIBUTE_NOT_FOUND
//
// MessageText:
//
// No attribute found within the given attribute handle range.
//
#ifndef STATUS_BTH_ATT_ATTRIBUTE_NOT_FOUND
#define STATUS_BTH_ATT_ATTRIBUTE_NOT_FOUND ((NTSTATUS)0xC042000AL)
#endif//STATUS_BTH_ATT_ATTRIBUTE_NOT_FOUND

//
// MessageId: STATUS_BTH_ATT_ATTRIBUTE_NOT_LONG
//
// MessageText:
//
// The attribute cannot be read or written using the Read Blob Request.
//
#ifndef STATUS_BTH_ATT_ATTRIBUTE_NOT_LONG
#define STATUS_BTH_ATT_ATTRIBUTE_NOT_LONG ((NTSTATUS)0xC042000BL)
#endif//STATUS_BTH_ATT_ATTRIBUTE_NOT_LONG

//
// MessageId: STATUS_BTH_ATT_INSUFFICIENT_ENCRYPTION_KEY_SIZE
//
// MessageText:
//
// The Encryption Key Size used for encrypting this link is insufficient.
//
#ifndef STATUS_BTH_ATT_INSUFFICIENT_ENCRYPTION_KEY_SIZE
#define STATUS_BTH_ATT_INSUFFICIENT_ENCRYPTION_KEY_SIZE ((NTSTATUS)0xC042000CL)
#endif//STATUS_BTH_ATT_INSUFFICIENT_ENCRYPTION_KEY_SIZE

//
// MessageId: STATUS_BTH_ATT_INVALID_ATTRIBUTE_VALUE_LENGTH
//
// MessageText:
//
// The attribute value length is invalid for the operation.
//
#ifndef STATUS_BTH_ATT_INVALID_ATTRIBUTE_VALUE_LENGTH
#define STATUS_BTH_ATT_INVALID_ATTRIBUTE_VALUE_LENGTH ((NTSTATUS)0xC042000DL)
#endif//STATUS_BTH_ATT_INVALID_ATTRIBUTE_VALUE_LENGTH

//
// MessageId: STATUS_BTH_ATT_UNLIKELY
//
// MessageText:
//
// The attribute request that was requested has encountered an error that was unlikely, and therefore could not be completed as requested.
//
#ifndef STATUS_BTH_ATT_UNLIKELY
#define STATUS_BTH_ATT_UNLIKELY          ((NTSTATUS)0xC042000EL)
#endif//STATUS_BTH_ATT_UNLIKELY

//
// MessageId: STATUS_BTH_ATT_INSUFFICIENT_ENCRYPTION
//
// MessageText:
//
// The attribute requires encryption before it can be read or written.
//
#ifndef STATUS_BTH_ATT_INSUFFICIENT_ENCRYPTION
#define STATUS_BTH_ATT_INSUFFICIENT_ENCRYPTION ((NTSTATUS)0xC042000FL)
#endif//STATUS_BTH_ATT_INSUFFICIENT_ENCRYPTION

//
// MessageId: STATUS_BTH_ATT_UNSUPPORTED_GROUP_TYPE
//
// MessageText:
//
// The attribute type is not a supported grouping attribute as defined by a higher layer specification.
//
#ifndef STATUS_BTH_ATT_UNSUPPORTED_GROUP_TYPE
#define STATUS_BTH_ATT_UNSUPPORTED_GROUP_TYPE ((NTSTATUS)0xC0420010L)
#endif//STATUS_BTH_ATT_UNSUPPORTED_GROUP_TYPE

//
// MessageId: STATUS_BTH_ATT_INSUFFICIENT_RESOURCES
//
// MessageText:
//
// Insufficient Resources to complete the request.
//
#ifndef STATUS_BTH_ATT_INSUFFICIENT_RESOURCES
#define STATUS_BTH_ATT_INSUFFICIENT_RESOURCES ((NTSTATUS)0xC0420011L)
#endif//STATUS_BTH_ATT_INSUFFICIENT_RESOURCES

//
// MessageId: STATUS_BTH_ATT_UNKNOWN_ERROR
//
// MessageText:
//
// An error that lies in the reserved range has been received.
//
#ifndef STATUS_BTH_ATT_UNKNOWN_ERROR
#define STATUS_BTH_ATT_UNKNOWN_ERROR     ((NTSTATUS)0xC0421000L)
#endif//STATUS_BTH_ATT_UNKNOWN_ERROR

//
// Secure Boot error messages.
//
//
// MessageId: STATUS_SECUREBOOT_ROLLBACK_DETECTED
//
// MessageText:
//
// Secure Boot detected that rollback of protected data has been attempted.
//
#ifndef STATUS_SECUREBOOT_ROLLBACK_DETECTED
#define STATUS_SECUREBOOT_ROLLBACK_DETECTED ((NTSTATUS)0xC0430001L)
#endif//STATUS_SECUREBOOT_ROLLBACK_DETECTED

//
// MessageId: STATUS_SECUREBOOT_POLICY_VIOLATION
//
// MessageText:
//
// The value is protected by Secure Boot policy and cannot be modified or deleted.
//
#ifndef STATUS_SECUREBOOT_POLICY_VIOLATION
#define STATUS_SECUREBOOT_POLICY_VIOLATION ((NTSTATUS)0xC0430002L)
#endif//STATUS_SECUREBOOT_POLICY_VIOLATION

//
// MessageId: STATUS_SECUREBOOT_INVALID_POLICY
//
// MessageText:
//
// The Secure Boot policy is invalid.
//
#ifndef STATUS_SECUREBOOT_INVALID_POLICY
#define STATUS_SECUREBOOT_INVALID_POLICY ((NTSTATUS)0xC0430003L)
#endif//STATUS_SECUREBOOT_INVALID_POLICY

//
// MessageId: STATUS_SECUREBOOT_POLICY_PUBLISHER_NOT_FOUND
//
// MessageText:
//
// A new Secure Boot policy did not contain the current publisher on its update list.
//
#ifndef STATUS_SECUREBOOT_POLICY_PUBLISHER_NOT_FOUND
#define STATUS_SECUREBOOT_POLICY_PUBLISHER_NOT_FOUND ((NTSTATUS)0xC0430004L)
#endif//STATUS_SECUREBOOT_POLICY_PUBLISHER_NOT_FOUND

//
// MessageId: STATUS_SECUREBOOT_POLICY_NOT_SIGNED
//
// MessageText:
//
// The Secure Boot policy is either not signed or is signed by a non-trusted signer.
//
#ifndef STATUS_SECUREBOOT_POLICY_NOT_SIGNED
#define STATUS_SECUREBOOT_POLICY_NOT_SIGNED ((NTSTATUS)0xC0430005L)
#endif//STATUS_SECUREBOOT_POLICY_NOT_SIGNED

//
// MessageId: STATUS_SECUREBOOT_NOT_ENABLED
//
// MessageText:
//
// Secure Boot is not enabled on this machine.
//
#ifndef STATUS_SECUREBOOT_NOT_ENABLED
#define STATUS_SECUREBOOT_NOT_ENABLED    ((NTSTATUS)0x80430006L)
#endif//STATUS_SECUREBOOT_NOT_ENABLED

//
// MessageId: STATUS_SECUREBOOT_FILE_REPLACED
//
// MessageText:
//
// Secure Boot requires that certain files and drivers are not replaced by other files or drivers.
//
#ifndef STATUS_SECUREBOOT_FILE_REPLACED
#define STATUS_SECUREBOOT_FILE_REPLACED  ((NTSTATUS)0xC0430007L)
#endif//STATUS_SECUREBOOT_FILE_REPLACED

//
// MessageId: STATUS_SECUREBOOT_POLICY_NOT_AUTHORIZED
//
// MessageText:
//
// The Secure Boot Supplemental Policy file was not authorized on this machine.
//
#ifndef STATUS_SECUREBOOT_POLICY_NOT_AUTHORIZED
#define STATUS_SECUREBOOT_POLICY_NOT_AUTHORIZED ((NTSTATUS)0xC0430008L)
#endif//STATUS_SECUREBOOT_POLICY_NOT_AUTHORIZED

//
// MessageId: STATUS_SECUREBOOT_POLICY_UNKNOWN
//
// MessageText:
//
// The Supplemntal Policy is not recognized on this device.
//
#ifndef STATUS_SECUREBOOT_POLICY_UNKNOWN
#define STATUS_SECUREBOOT_POLICY_UNKNOWN ((NTSTATUS)0xC0430009L)
#endif//STATUS_SECUREBOOT_POLICY_UNKNOWN

//
// MessageId: STATUS_SECUREBOOT_POLICY_MISSING_ANTIROLLBACKVERSION
//
// MessageText:
//
// The Antirollback version was not found in the Secure Boot Policy.
//
#ifndef STATUS_SECUREBOOT_POLICY_MISSING_ANTIROLLBACKVERSION
#define STATUS_SECUREBOOT_POLICY_MISSING_ANTIROLLBACKVERSION ((NTSTATUS)0xC043000AL)
#endif//STATUS_SECUREBOOT_POLICY_MISSING_ANTIROLLBACKVERSION

//
// MessageId: STATUS_SECUREBOOT_PLATFORM_ID_MISMATCH
//
// MessageText:
//
// The Platform ID specified in the Secure Boot policy does not match the Platform ID on this device.
//
#ifndef STATUS_SECUREBOOT_PLATFORM_ID_MISMATCH
#define STATUS_SECUREBOOT_PLATFORM_ID_MISMATCH ((NTSTATUS)0xC043000BL)
#endif//STATUS_SECUREBOOT_PLATFORM_ID_MISMATCH

//
// MessageId: STATUS_SECUREBOOT_POLICY_ROLLBACK_DETECTED
//
// MessageText:
//
// The Secure Boot policy file has an older Antirollback Version than this device.
//
#ifndef STATUS_SECUREBOOT_POLICY_ROLLBACK_DETECTED
#define STATUS_SECUREBOOT_POLICY_ROLLBACK_DETECTED ((NTSTATUS)0xC043000CL)
#endif//STATUS_SECUREBOOT_POLICY_ROLLBACK_DETECTED

//
// MessageId: STATUS_SECUREBOOT_POLICY_UPGRADE_MISMATCH
//
// MessageText:
//
// The Secure Boot policy file does not match the upgraded legacy policy.
//
#ifndef STATUS_SECUREBOOT_POLICY_UPGRADE_MISMATCH
#define STATUS_SECUREBOOT_POLICY_UPGRADE_MISMATCH ((NTSTATUS)0xC043000DL)
#endif//STATUS_SECUREBOOT_POLICY_UPGRADE_MISMATCH

//
// MessageId: STATUS_SECUREBOOT_REQUIRED_POLICY_FILE_MISSING
//
// MessageText:
//
// The Secure Boot policy file is required but could not be found.
//
#ifndef STATUS_SECUREBOOT_REQUIRED_POLICY_FILE_MISSING
#define STATUS_SECUREBOOT_REQUIRED_POLICY_FILE_MISSING ((NTSTATUS)0xC043000EL)
#endif//STATUS_SECUREBOOT_REQUIRED_POLICY_FILE_MISSING

//
// MessageId: STATUS_SECUREBOOT_NOT_BASE_POLICY
//
// MessageText:
//
// Supplemental Secure Boot policy file can not be loaded as a base Secure Boot policy.
//
#ifndef STATUS_SECUREBOOT_NOT_BASE_POLICY
#define STATUS_SECUREBOOT_NOT_BASE_POLICY ((NTSTATUS)0xC043000FL)
#endif//STATUS_SECUREBOOT_NOT_BASE_POLICY

//
// MessageId: STATUS_SECUREBOOT_NOT_SUPPLEMENTAL_POLICY
//
// MessageText:
//
// Base Secure Boot policy file can not be loaded as a Supplemental Secure Boot policy.
//
#ifndef STATUS_SECUREBOOT_NOT_SUPPLEMENTAL_POLICY
#define STATUS_SECUREBOOT_NOT_SUPPLEMENTAL_POLICY ((NTSTATUS)0xC0430010L)
#endif//STATUS_SECUREBOOT_NOT_SUPPLEMENTAL_POLICY

//
// Platform Manifest Error Messages
//
//
// MessageId: STATUS_PLATFORM_MANIFEST_NOT_AUTHORIZED
//
// MessageText:
//
// The Platform Manifest file was not authorized on this machine.
//
#ifndef STATUS_PLATFORM_MANIFEST_NOT_AUTHORIZED
#define STATUS_PLATFORM_MANIFEST_NOT_AUTHORIZED ((NTSTATUS)0xC0EB0001L)
#endif//STATUS_PLATFORM_MANIFEST_NOT_AUTHORIZED

//
// MessageId: STATUS_PLATFORM_MANIFEST_INVALID
//
// MessageText:
//
// The Platform Manifest file was not valid.
//
#ifndef STATUS_PLATFORM_MANIFEST_INVALID
#define STATUS_PLATFORM_MANIFEST_INVALID ((NTSTATUS)0xC0EB0002L)
#endif//STATUS_PLATFORM_MANIFEST_INVALID

//
// MessageId: STATUS_PLATFORM_MANIFEST_FILE_NOT_AUTHORIZED
//
// MessageText:
//
// The file is not authorized on this platform because an entry was not found in the Platform Manifest.
//
#ifndef STATUS_PLATFORM_MANIFEST_FILE_NOT_AUTHORIZED
#define STATUS_PLATFORM_MANIFEST_FILE_NOT_AUTHORIZED ((NTSTATUS)0xC0EB0003L)
#endif//STATUS_PLATFORM_MANIFEST_FILE_NOT_AUTHORIZED

//
// MessageId: STATUS_PLATFORM_MANIFEST_CATALOG_NOT_AUTHORIZED
//
// MessageText:
//
// The catalog is not authorized on this platform because an entry was not found in the Platform Manifest.
//
#ifndef STATUS_PLATFORM_MANIFEST_CATALOG_NOT_AUTHORIZED
#define STATUS_PLATFORM_MANIFEST_CATALOG_NOT_AUTHORIZED ((NTSTATUS)0xC0EB0004L)
#endif//STATUS_PLATFORM_MANIFEST_CATALOG_NOT_AUTHORIZED

//
// MessageId: STATUS_PLATFORM_MANIFEST_BINARY_ID_NOT_FOUND
//
// MessageText:
//
// The file is not authorized on this platform because a Binary ID was not found in the embedded signature.
//
#ifndef STATUS_PLATFORM_MANIFEST_BINARY_ID_NOT_FOUND
#define STATUS_PLATFORM_MANIFEST_BINARY_ID_NOT_FOUND ((NTSTATUS)0xC0EB0005L)
#endif//STATUS_PLATFORM_MANIFEST_BINARY_ID_NOT_FOUND

//
// MessageId: STATUS_PLATFORM_MANIFEST_NOT_ACTIVE
//
// MessageText:
//
// No active Platform Manifest exists on this system.
//
#ifndef STATUS_PLATFORM_MANIFEST_NOT_ACTIVE
#define STATUS_PLATFORM_MANIFEST_NOT_ACTIVE ((NTSTATUS)0xC0EB0006L)
#endif//STATUS_PLATFORM_MANIFEST_NOT_ACTIVE

//
// MessageId: STATUS_PLATFORM_MANIFEST_NOT_SIGNED
//
// MessageText:
//
// The Platform Manifest file was not properly signed.
//
#ifndef STATUS_PLATFORM_MANIFEST_NOT_SIGNED
#define STATUS_PLATFORM_MANIFEST_NOT_SIGNED ((NTSTATUS)0xC0EB0007L)
#endif//STATUS_PLATFORM_MANIFEST_NOT_SIGNED

//
// System Integrity Policy error messages.
//
//
// MessageId: STATUS_SYSTEM_INTEGRITY_ROLLBACK_DETECTED
//
// MessageText:
//
// System Integrity detected that policy rollback has been attempted.
//
#ifndef STATUS_SYSTEM_INTEGRITY_ROLLBACK_DETECTED
#define STATUS_SYSTEM_INTEGRITY_ROLLBACK_DETECTED ((NTSTATUS)0xC0E90001L)
#endif//STATUS_SYSTEM_INTEGRITY_ROLLBACK_DETECTED

//
// MessageId: STATUS_SYSTEM_INTEGRITY_POLICY_VIOLATION
//
// MessageText:
//
// System Integrity policy has been violated.
//
#ifndef STATUS_SYSTEM_INTEGRITY_POLICY_VIOLATION
#define STATUS_SYSTEM_INTEGRITY_POLICY_VIOLATION ((NTSTATUS)0xC0E90002L)
#endif//STATUS_SYSTEM_INTEGRITY_POLICY_VIOLATION

//
// MessageId: STATUS_SYSTEM_INTEGRITY_INVALID_POLICY
//
// MessageText:
//
// The System Integrity policy is invalid.
//
#ifndef STATUS_SYSTEM_INTEGRITY_INVALID_POLICY
#define STATUS_SYSTEM_INTEGRITY_INVALID_POLICY ((NTSTATUS)0xC0E90003L)
#endif//STATUS_SYSTEM_INTEGRITY_INVALID_POLICY

//
// MessageId: STATUS_SYSTEM_INTEGRITY_POLICY_NOT_SIGNED
//
// MessageText:
//
// The System Integrity policy is either not signed or is signed by a non-trusted signer.
//
#ifndef STATUS_SYSTEM_INTEGRITY_POLICY_NOT_SIGNED
#define STATUS_SYSTEM_INTEGRITY_POLICY_NOT_SIGNED ((NTSTATUS)0xC0E90004L)
#endif//STATUS_SYSTEM_INTEGRITY_POLICY_NOT_SIGNED

//
// Clip modern app and windows licensing error messages.
//
//
// MessageId: STATUS_NO_APPLICABLE_APP_LICENSES_FOUND
//
// MessageText:
//
// No applicable app licenses found.
//
#ifndef STATUS_NO_APPLICABLE_APP_LICENSES_FOUND
#define STATUS_NO_APPLICABLE_APP_LICENSES_FOUND ((NTSTATUS)0xC0EA0001L)
#endif//STATUS_NO_APPLICABLE_APP_LICENSES_FOUND

//
// MessageId: STATUS_CLIP_LICENSE_NOT_FOUND
//
// MessageText:
//
// CLiP license not found.
//
#ifndef STATUS_CLIP_LICENSE_NOT_FOUND
#define STATUS_CLIP_LICENSE_NOT_FOUND    ((NTSTATUS)0xC0EA0002L)
#endif//STATUS_CLIP_LICENSE_NOT_FOUND

//
// MessageId: STATUS_CLIP_DEVICE_LICENSE_MISSING
//
// MessageText:
//
// CLiP device license not found.
//
#ifndef STATUS_CLIP_DEVICE_LICENSE_MISSING
#define STATUS_CLIP_DEVICE_LICENSE_MISSING ((NTSTATUS)0xC0EA0003L)
#endif//STATUS_CLIP_DEVICE_LICENSE_MISSING

//
// MessageId: STATUS_CLIP_LICENSE_INVALID_SIGNATURE
//
// MessageText:
//
// CLiP license has an invalid signature.
//
#ifndef STATUS_CLIP_LICENSE_INVALID_SIGNATURE
#define STATUS_CLIP_LICENSE_INVALID_SIGNATURE ((NTSTATUS)0xC0EA0004L)
#endif//STATUS_CLIP_LICENSE_INVALID_SIGNATURE

//
// MessageId: STATUS_CLIP_KEYHOLDER_LICENSE_MISSING_OR_INVALID
//
// MessageText:
//
// CLiP keyholder license is invalid or missing.
//
#ifndef STATUS_CLIP_KEYHOLDER_LICENSE_MISSING_OR_INVALID
#define STATUS_CLIP_KEYHOLDER_LICENSE_MISSING_OR_INVALID ((NTSTATUS)0xC0EA0005L)
#endif//STATUS_CLIP_KEYHOLDER_LICENSE_MISSING_OR_INVALID

//
// MessageId: STATUS_CLIP_LICENSE_EXPIRED
//
// MessageText:
//
// CLiP license has expired.
//
#ifndef STATUS_CLIP_LICENSE_EXPIRED
#define STATUS_CLIP_LICENSE_EXPIRED      ((NTSTATUS)0xC0EA0006L)
#endif//STATUS_CLIP_LICENSE_EXPIRED

//
// MessageId: STATUS_CLIP_LICENSE_SIGNED_BY_UNKNOWN_SOURCE
//
// MessageText:
//
// CLiP license is signed by an unknown source.
//
#ifndef STATUS_CLIP_LICENSE_SIGNED_BY_UNKNOWN_SOURCE
#define STATUS_CLIP_LICENSE_SIGNED_BY_UNKNOWN_SOURCE ((NTSTATUS)0xC0EA0007L)
#endif//STATUS_CLIP_LICENSE_SIGNED_BY_UNKNOWN_SOURCE

//
// MessageId: STATUS_CLIP_LICENSE_NOT_SIGNED
//
// MessageText:
//
// CLiP license is not signed.
//
#ifndef STATUS_CLIP_LICENSE_NOT_SIGNED
#define STATUS_CLIP_LICENSE_NOT_SIGNED   ((NTSTATUS)0xC0EA0008L)
#endif//STATUS_CLIP_LICENSE_NOT_SIGNED

//
// MessageId: STATUS_CLIP_LICENSE_HARDWARE_ID_OUT_OF_TOLERANCE
//
// MessageText:
//
// CLiP license hardware ID is out of tolerance.
//
#ifndef STATUS_CLIP_LICENSE_HARDWARE_ID_OUT_OF_TOLERANCE
#define STATUS_CLIP_LICENSE_HARDWARE_ID_OUT_OF_TOLERANCE ((NTSTATUS)0xC0EA0009L)
#endif//STATUS_CLIP_LICENSE_HARDWARE_ID_OUT_OF_TOLERANCE

//
// MessageId: STATUS_CLIP_LICENSE_DEVICE_ID_MISMATCH
//
// MessageText:
//
// CLiP license device ID does not match the device ID in the bound device license.
//
#ifndef STATUS_CLIP_LICENSE_DEVICE_ID_MISMATCH
#define STATUS_CLIP_LICENSE_DEVICE_ID_MISMATCH ((NTSTATUS)0xC0EA000AL)
#endif//STATUS_CLIP_LICENSE_DEVICE_ID_MISMATCH

//
// Audio error messages.
//
//
// MessageId: STATUS_AUDIO_ENGINE_NODE_NOT_FOUND
//
// MessageText:
//
// PortCls could not find an audio engine node exposed by a miniport driver claiming support for IMiniportAudioEngineNode.
//
#ifndef STATUS_AUDIO_ENGINE_NODE_NOT_FOUND
#define STATUS_AUDIO_ENGINE_NODE_NOT_FOUND ((NTSTATUS)0xC0440001L)
#endif//STATUS_AUDIO_ENGINE_NODE_NOT_FOUND

//
// MessageId: STATUS_HDAUDIO_EMPTY_CONNECTION_LIST
//
// MessageText:
//
// HD Audio widget encountered an unexpected empty connection list.
//
#ifndef STATUS_HDAUDIO_EMPTY_CONNECTION_LIST
#define STATUS_HDAUDIO_EMPTY_CONNECTION_LIST ((NTSTATUS)0xC0440002L)
#endif//STATUS_HDAUDIO_EMPTY_CONNECTION_LIST

//
// MessageId: STATUS_HDAUDIO_CONNECTION_LIST_NOT_SUPPORTED
//
// MessageText:
//
// HD Audio widget does not support the connection list parameter.
//
#ifndef STATUS_HDAUDIO_CONNECTION_LIST_NOT_SUPPORTED
#define STATUS_HDAUDIO_CONNECTION_LIST_NOT_SUPPORTED ((NTSTATUS)0xC0440003L)
#endif//STATUS_HDAUDIO_CONNECTION_LIST_NOT_SUPPORTED

//
// MessageId: STATUS_HDAUDIO_NO_LOGICAL_DEVICES_CREATED
//
// MessageText:
//
// No HD Audio subdevices were successfully created.
//
#ifndef STATUS_HDAUDIO_NO_LOGICAL_DEVICES_CREATED
#define STATUS_HDAUDIO_NO_LOGICAL_DEVICES_CREATED ((NTSTATUS)0xC0440004L)
#endif//STATUS_HDAUDIO_NO_LOGICAL_DEVICES_CREATED

//
// MessageId: STATUS_HDAUDIO_NULL_LINKED_LIST_ENTRY
//
// MessageText:
//
// An unexpected NULL pointer was encountered in a linked list.
//
#ifndef STATUS_HDAUDIO_NULL_LINKED_LIST_ENTRY
#define STATUS_HDAUDIO_NULL_LINKED_LIST_ENTRY ((NTSTATUS)0xC0440005L)
#endif//STATUS_HDAUDIO_NULL_LINKED_LIST_ENTRY

//
// Spaceport success codes (spaceport.sys)
//
//
// MessageId: STATUS_SPACES_REPAIRED
//
// MessageText:
//
// The repair was successful.
//
#ifndef STATUS_SPACES_REPAIRED
#define STATUS_SPACES_REPAIRED           ((NTSTATUS)0x00E70000L)
#endif//STATUS_SPACES_REPAIRED

//
// MessageId: STATUS_SPACES_PAUSE
//
// MessageText:
//
// The operation has been paused.
//
#ifndef STATUS_SPACES_PAUSE
#define STATUS_SPACES_PAUSE              ((NTSTATUS)0x00E70001L)
#endif//STATUS_SPACES_PAUSE

//
// MessageId: STATUS_SPACES_COMPLETE
//
// MessageText:
//
// The operation is complete.
//
#ifndef STATUS_SPACES_COMPLETE
#define STATUS_SPACES_COMPLETE           ((NTSTATUS)0x00E70002L)
#endif//STATUS_SPACES_COMPLETE

//
// MessageId: STATUS_SPACES_REDIRECT
//
// MessageText:
//
// The operation should be redirected to another node.
//
#ifndef STATUS_SPACES_REDIRECT
#define STATUS_SPACES_REDIRECT           ((NTSTATUS)0x00E70003L)
#endif//STATUS_SPACES_REDIRECT

//
// Spaceport error codes (spaceport.sys)
//
//
// MessageId: STATUS_SPACES_FAULT_DOMAIN_TYPE_INVALID
//
// MessageText:
//
// The specified fault domain type or combination of minimum / maximum fault domain type is not valid.
//
#ifndef STATUS_SPACES_FAULT_DOMAIN_TYPE_INVALID
#define STATUS_SPACES_FAULT_DOMAIN_TYPE_INVALID ((NTSTATUS)0xC0E70001L)
#endif//STATUS_SPACES_FAULT_DOMAIN_TYPE_INVALID

//
// MessageId: STATUS_SPACES_RESILIENCY_TYPE_INVALID
//
// MessageText:
//
// The specified resiliency type is not valid.
//
#ifndef STATUS_SPACES_RESILIENCY_TYPE_INVALID
#define STATUS_SPACES_RESILIENCY_TYPE_INVALID ((NTSTATUS)0xC0E70003L)
#endif//STATUS_SPACES_RESILIENCY_TYPE_INVALID

//
// MessageId: STATUS_SPACES_DRIVE_SECTOR_SIZE_INVALID
//
// MessageText:
//
// The sector size of the physical disk is not supported by the storage pool.
//
#ifndef STATUS_SPACES_DRIVE_SECTOR_SIZE_INVALID
#define STATUS_SPACES_DRIVE_SECTOR_SIZE_INVALID ((NTSTATUS)0xC0E70004L)
#endif//STATUS_SPACES_DRIVE_SECTOR_SIZE_INVALID

//
// MessageId: STATUS_SPACES_DRIVE_REDUNDANCY_INVALID
//
// MessageText:
//
// The value for fault tolerance is outside of the supported range of values.
//
#ifndef STATUS_SPACES_DRIVE_REDUNDANCY_INVALID
#define STATUS_SPACES_DRIVE_REDUNDANCY_INVALID ((NTSTATUS)0xC0E70006L)
#endif//STATUS_SPACES_DRIVE_REDUNDANCY_INVALID

//
// MessageId: STATUS_SPACES_NUMBER_OF_DATA_COPIES_INVALID
//
// MessageText:
//
// The number of data copies requested is outside of the supported range of values.
//
#ifndef STATUS_SPACES_NUMBER_OF_DATA_COPIES_INVALID
#define STATUS_SPACES_NUMBER_OF_DATA_COPIES_INVALID ((NTSTATUS)0xC0E70007L)
#endif//STATUS_SPACES_NUMBER_OF_DATA_COPIES_INVALID

//
// MessageId: STATUS_SPACES_INTERLEAVE_LENGTH_INVALID
//
// MessageText:
//
// The value for interleave length is outside of the supported range of values or is not a power of 2.
//
#ifndef STATUS_SPACES_INTERLEAVE_LENGTH_INVALID
#define STATUS_SPACES_INTERLEAVE_LENGTH_INVALID ((NTSTATUS)0xC0E70009L)
#endif//STATUS_SPACES_INTERLEAVE_LENGTH_INVALID

//
// MessageId: STATUS_SPACES_NUMBER_OF_COLUMNS_INVALID
//
// MessageText:
//
// The number of columns specified is outside of the supported range of values.
//
#ifndef STATUS_SPACES_NUMBER_OF_COLUMNS_INVALID
#define STATUS_SPACES_NUMBER_OF_COLUMNS_INVALID ((NTSTATUS)0xC0E7000AL)
#endif//STATUS_SPACES_NUMBER_OF_COLUMNS_INVALID

//
// MessageId: STATUS_SPACES_NOT_ENOUGH_DRIVES
//
// MessageText:
//
// There were not enough physical disks to complete the requested operation.
//
#ifndef STATUS_SPACES_NOT_ENOUGH_DRIVES
#define STATUS_SPACES_NOT_ENOUGH_DRIVES  ((NTSTATUS)0xC0E7000BL)
#endif//STATUS_SPACES_NOT_ENOUGH_DRIVES

//
// MessageId: STATUS_SPACES_EXTENDED_ERROR
//
// MessageText:
//
// Extended error information is available.
//
#ifndef STATUS_SPACES_EXTENDED_ERROR
#define STATUS_SPACES_EXTENDED_ERROR     ((NTSTATUS)0xC0E7000CL)
#endif//STATUS_SPACES_EXTENDED_ERROR

//
// MessageId: STATUS_SPACES_PROVISIONING_TYPE_INVALID
//
// MessageText:
//
// The specified provisioning type is not valid.
//
#ifndef STATUS_SPACES_PROVISIONING_TYPE_INVALID
#define STATUS_SPACES_PROVISIONING_TYPE_INVALID ((NTSTATUS)0xC0E7000DL)
#endif//STATUS_SPACES_PROVISIONING_TYPE_INVALID

//
// MessageId: STATUS_SPACES_ALLOCATION_SIZE_INVALID
//
// MessageText:
//
// The allocation size is outside of the supported range of values.
//
#ifndef STATUS_SPACES_ALLOCATION_SIZE_INVALID
#define STATUS_SPACES_ALLOCATION_SIZE_INVALID ((NTSTATUS)0xC0E7000EL)
#endif//STATUS_SPACES_ALLOCATION_SIZE_INVALID

//
// MessageId: STATUS_SPACES_ENCLOSURE_AWARE_INVALID
//
// MessageText:
//
// Enclosure awareness is not supported for this virtual disk.
//
#ifndef STATUS_SPACES_ENCLOSURE_AWARE_INVALID
#define STATUS_SPACES_ENCLOSURE_AWARE_INVALID ((NTSTATUS)0xC0E7000FL)
#endif//STATUS_SPACES_ENCLOSURE_AWARE_INVALID

//
// MessageId: STATUS_SPACES_WRITE_CACHE_SIZE_INVALID
//
// MessageText:
//
// The write cache size is outside of the supported range of values.
//
#ifndef STATUS_SPACES_WRITE_CACHE_SIZE_INVALID
#define STATUS_SPACES_WRITE_CACHE_SIZE_INVALID ((NTSTATUS)0xC0E70010L)
#endif//STATUS_SPACES_WRITE_CACHE_SIZE_INVALID

//
// MessageId: STATUS_SPACES_NUMBER_OF_GROUPS_INVALID
//
// MessageText:
//
// The value for number of groups is outside of the supported range of values.
//
#ifndef STATUS_SPACES_NUMBER_OF_GROUPS_INVALID
#define STATUS_SPACES_NUMBER_OF_GROUPS_INVALID ((NTSTATUS)0xC0E70011L)
#endif//STATUS_SPACES_NUMBER_OF_GROUPS_INVALID

//
// MessageId: STATUS_SPACES_DRIVE_OPERATIONAL_STATE_INVALID
//
// MessageText:
//
// The OperationalState of the physical disk is invalid for this operation.
//
#ifndef STATUS_SPACES_DRIVE_OPERATIONAL_STATE_INVALID
#define STATUS_SPACES_DRIVE_OPERATIONAL_STATE_INVALID ((NTSTATUS)0xC0E70012L)
#endif//STATUS_SPACES_DRIVE_OPERATIONAL_STATE_INVALID

//
// MessageId: STATUS_SPACES_UPDATE_COLUMN_STATE
//
// MessageText:
//
// A column's state needs to be updated.
//
#ifndef STATUS_SPACES_UPDATE_COLUMN_STATE
#define STATUS_SPACES_UPDATE_COLUMN_STATE ((NTSTATUS)0xC0E70013L)
#endif//STATUS_SPACES_UPDATE_COLUMN_STATE

//
// MessageId: STATUS_SPACES_MAP_REQUIRED
//
// MessageText:
//
// An extent needs to be allocated.
//
#ifndef STATUS_SPACES_MAP_REQUIRED
#define STATUS_SPACES_MAP_REQUIRED       ((NTSTATUS)0xC0E70014L)
#endif//STATUS_SPACES_MAP_REQUIRED

//
// MessageId: STATUS_SPACES_UNSUPPORTED_VERSION
//
// MessageText:
//
// The metadata version is unsupported.
//
#ifndef STATUS_SPACES_UNSUPPORTED_VERSION
#define STATUS_SPACES_UNSUPPORTED_VERSION ((NTSTATUS)0xC0E70015L)
#endif//STATUS_SPACES_UNSUPPORTED_VERSION

//
// MessageId: STATUS_SPACES_CORRUPT_METADATA
//
// MessageText:
//
// The metadata read was corrupt.
//
#ifndef STATUS_SPACES_CORRUPT_METADATA
#define STATUS_SPACES_CORRUPT_METADATA   ((NTSTATUS)0xC0E70016L)
#endif//STATUS_SPACES_CORRUPT_METADATA

//
// MessageId: STATUS_SPACES_DRT_FULL
//
// MessageText:
//
// The DRT is full.
//
#ifndef STATUS_SPACES_DRT_FULL
#define STATUS_SPACES_DRT_FULL           ((NTSTATUS)0xC0E70017L)
#endif//STATUS_SPACES_DRT_FULL

//
// MessageId: STATUS_SPACES_INCONSISTENCY
//
// MessageText:
//
// An inconsistency was found.
//
#ifndef STATUS_SPACES_INCONSISTENCY
#define STATUS_SPACES_INCONSISTENCY      ((NTSTATUS)0xC0E70018L)
#endif//STATUS_SPACES_INCONSISTENCY

//
// MessageId: STATUS_SPACES_LOG_NOT_READY
//
// MessageText:
//
// The log is not ready.
//
#ifndef STATUS_SPACES_LOG_NOT_READY
#define STATUS_SPACES_LOG_NOT_READY      ((NTSTATUS)0xC0E70019L)
#endif//STATUS_SPACES_LOG_NOT_READY

//
// MessageId: STATUS_SPACES_NO_REDUNDANCY
//
// MessageText:
//
// No good copy of data was available.
//
#ifndef STATUS_SPACES_NO_REDUNDANCY
#define STATUS_SPACES_NO_REDUNDANCY      ((NTSTATUS)0xC0E7001AL)
#endif//STATUS_SPACES_NO_REDUNDANCY

//
// MessageId: STATUS_SPACES_DRIVE_NOT_READY
//
// MessageText:
//
// The drive is not ready.
//
#ifndef STATUS_SPACES_DRIVE_NOT_READY
#define STATUS_SPACES_DRIVE_NOT_READY    ((NTSTATUS)0xC0E7001BL)
#endif//STATUS_SPACES_DRIVE_NOT_READY

//
// MessageId: STATUS_SPACES_DRIVE_SPLIT
//
// MessageText:
//
// The data on this drive is stale.
//
#ifndef STATUS_SPACES_DRIVE_SPLIT
#define STATUS_SPACES_DRIVE_SPLIT        ((NTSTATUS)0xC0E7001CL)
#endif//STATUS_SPACES_DRIVE_SPLIT

//
// MessageId: STATUS_SPACES_DRIVE_LOST_DATA
//
// MessageText:
//
// The data on this drive has been lost.
//
#ifndef STATUS_SPACES_DRIVE_LOST_DATA
#define STATUS_SPACES_DRIVE_LOST_DATA    ((NTSTATUS)0xC0E7001DL)
#endif//STATUS_SPACES_DRIVE_LOST_DATA

//
// Volsnap status codes (volsnap.sys)
//
//
// MessageId: STATUS_VOLSNAP_BOOTFILE_NOT_VALID
//
// MessageText:
//
// The bootfile is too small to support persistent snapshots.
//
#ifndef STATUS_VOLSNAP_BOOTFILE_NOT_VALID
#define STATUS_VOLSNAP_BOOTFILE_NOT_VALID ((NTSTATUS)0xC0500003L)
#endif//STATUS_VOLSNAP_BOOTFILE_NOT_VALID

//
// MessageId: STATUS_VOLSNAP_ACTIVATION_TIMEOUT
//
// MessageText:
//
// Activation of persistent snapshots on this volume took longer than was allowed.
//
#ifndef STATUS_VOLSNAP_ACTIVATION_TIMEOUT
#define STATUS_VOLSNAP_ACTIVATION_TIMEOUT ((NTSTATUS)0xC0500004L)
#endif//STATUS_VOLSNAP_ACTIVATION_TIMEOUT

//
// Sdbus status codes (sdbus.sys)
//
//
// MessageId: STATUS_IO_PREEMPTED
//
// MessageText:
//
// The operation was preempted by a higher priority operation. It must be resumed later.
//
#ifndef STATUS_IO_PREEMPTED
#define STATUS_IO_PREEMPTED              ((NTSTATUS)0xC0510001L)
#endif//STATUS_IO_PREEMPTED

//
// Shared VHDX status codes (svhdxflt.sys)
//
//
// MessageId: STATUS_SVHDX_ERROR_STORED
//
// MessageText:
//
// The proper error code with sense data was stored on server side.
//
#ifndef STATUS_SVHDX_ERROR_STORED
#define STATUS_SVHDX_ERROR_STORED        ((NTSTATUS)0xC05C0000L)
#endif//STATUS_SVHDX_ERROR_STORED

//
// MessageId: STATUS_SVHDX_ERROR_NOT_AVAILABLE
//
// MessageText:
//
// The requested error data is not available on the server.
//
#ifndef STATUS_SVHDX_ERROR_NOT_AVAILABLE
#define STATUS_SVHDX_ERROR_NOT_AVAILABLE ((NTSTATUS)0xC05CFF00L)
#endif//STATUS_SVHDX_ERROR_NOT_AVAILABLE

//
// MessageId: STATUS_SVHDX_UNIT_ATTENTION_AVAILABLE
//
// MessageText:
//
// Unit Attention data is available for the initiator to query.
//
#ifndef STATUS_SVHDX_UNIT_ATTENTION_AVAILABLE
#define STATUS_SVHDX_UNIT_ATTENTION_AVAILABLE ((NTSTATUS)0xC05CFF01L)
#endif//STATUS_SVHDX_UNIT_ATTENTION_AVAILABLE

//
// MessageId: STATUS_SVHDX_UNIT_ATTENTION_CAPACITY_DATA_CHANGED
//
// MessageText:
//
// The data capacity of the device has changed, resulting in a Unit Attention condition.
//
#ifndef STATUS_SVHDX_UNIT_ATTENTION_CAPACITY_DATA_CHANGED
#define STATUS_SVHDX_UNIT_ATTENTION_CAPACITY_DATA_CHANGED ((NTSTATUS)0xC05CFF02L)
#endif//STATUS_SVHDX_UNIT_ATTENTION_CAPACITY_DATA_CHANGED

//
// MessageId: STATUS_SVHDX_UNIT_ATTENTION_RESERVATIONS_PREEMPTED
//
// MessageText:
//
// A previous operation resulted in this initiator's reservations being preempted, resulting in a Unit Attention condition.
//
#ifndef STATUS_SVHDX_UNIT_ATTENTION_RESERVATIONS_PREEMPTED
#define STATUS_SVHDX_UNIT_ATTENTION_RESERVATIONS_PREEMPTED ((NTSTATUS)0xC05CFF03L)
#endif//STATUS_SVHDX_UNIT_ATTENTION_RESERVATIONS_PREEMPTED

//
// MessageId: STATUS_SVHDX_UNIT_ATTENTION_RESERVATIONS_RELEASED
//
// MessageText:
//
// A previous operation resulted in this initiator's reservations being released, resulting in a Unit Attention condition.
//
#ifndef STATUS_SVHDX_UNIT_ATTENTION_RESERVATIONS_RELEASED
#define STATUS_SVHDX_UNIT_ATTENTION_RESERVATIONS_RELEASED ((NTSTATUS)0xC05CFF04L)
#endif//STATUS_SVHDX_UNIT_ATTENTION_RESERVATIONS_RELEASED

//
// MessageId: STATUS_SVHDX_UNIT_ATTENTION_REGISTRATIONS_PREEMPTED
//
// MessageText:
//
// A previous operation resulted in this initiator's registrations being preempted, resulting in a Unit Attention condition.
//
#ifndef STATUS_SVHDX_UNIT_ATTENTION_REGISTRATIONS_PREEMPTED
#define STATUS_SVHDX_UNIT_ATTENTION_REGISTRATIONS_PREEMPTED ((NTSTATUS)0xC05CFF05L)
#endif//STATUS_SVHDX_UNIT_ATTENTION_REGISTRATIONS_PREEMPTED

//
// MessageId: STATUS_SVHDX_UNIT_ATTENTION_OPERATING_DEFINITION_CHANGED
//
// MessageText:
//
// The data storage format of the device has changed, resulting in a Unit Attention condition.
//
#ifndef STATUS_SVHDX_UNIT_ATTENTION_OPERATING_DEFINITION_CHANGED
#define STATUS_SVHDX_UNIT_ATTENTION_OPERATING_DEFINITION_CHANGED ((NTSTATUS)0xC05CFF06L)
#endif//STATUS_SVHDX_UNIT_ATTENTION_OPERATING_DEFINITION_CHANGED

//
// MessageId: STATUS_SVHDX_RESERVATION_CONFLICT
//
// MessageText:
//
// The current initiator is not allowed to perform the SCSI command because of a reservation conflict.
//
#ifndef STATUS_SVHDX_RESERVATION_CONFLICT
#define STATUS_SVHDX_RESERVATION_CONFLICT ((NTSTATUS)0xC05CFF07L)
#endif//STATUS_SVHDX_RESERVATION_CONFLICT

//
// MessageId: STATUS_SVHDX_WRONG_FILE_TYPE
//
// MessageText:
//
// Multiple virtual machines sharing a virtual hard disk is supported only on Fixed or Dynamic VHDX format virtual hard disks.
//
#ifndef STATUS_SVHDX_WRONG_FILE_TYPE
#define STATUS_SVHDX_WRONG_FILE_TYPE     ((NTSTATUS)0xC05CFF08L)
#endif//STATUS_SVHDX_WRONG_FILE_TYPE

//
// MessageId: STATUS_SVHDX_VERSION_MISMATCH
//
// MessageText:
//
// The server version does not match the requested version.
//
#ifndef STATUS_SVHDX_VERSION_MISMATCH
#define STATUS_SVHDX_VERSION_MISMATCH    ((NTSTATUS)0xC05CFF09L)
#endif//STATUS_SVHDX_VERSION_MISMATCH

//
// MessageId: STATUS_VHD_SHARED
//
// MessageText:
//
// The requested operation cannot be performed on the virtual disk as it is currently used in shared mode.
//
#ifndef STATUS_VHD_SHARED
#define STATUS_VHD_SHARED                ((NTSTATUS)0xC05CFF0AL)
#endif//STATUS_VHD_SHARED

//
// MessageId: STATUS_SVHDX_NO_INITIATOR
//
// MessageText:
//
// Invalid Shared VHDX open due to lack of initiator ID. Check for related Continuous Availability failures.
//
#ifndef STATUS_SVHDX_NO_INITIATOR
#define STATUS_SVHDX_NO_INITIATOR        ((NTSTATUS)0xC05CFF0BL)
#endif//STATUS_SVHDX_NO_INITIATOR

//
// MessageId: STATUS_VHDSET_BACKING_STORAGE_NOT_FOUND
//
// MessageText:
//
// The requested operation failed due to a missing backing storage file.
//
#ifndef STATUS_VHDSET_BACKING_STORAGE_NOT_FOUND
#define STATUS_VHDSET_BACKING_STORAGE_NOT_FOUND ((NTSTATUS)0xC05CFF0CL)
#endif//STATUS_VHDSET_BACKING_STORAGE_NOT_FOUND

//
// SMB status codes
//
//
// MessageId: STATUS_SMB_NO_PREAUTH_INTEGRITY_HASH_OVERLAP
//
// MessageText:
//
// Failed to negotiate a preauthentication integrity hash function.
//
#ifndef STATUS_SMB_NO_PREAUTH_INTEGRITY_HASH_OVERLAP
#define STATUS_SMB_NO_PREAUTH_INTEGRITY_HASH_OVERLAP ((NTSTATUS)0xC05D0000L)
#endif//STATUS_SMB_NO_PREAUTH_INTEGRITY_HASH_OVERLAP

//
// MessageId: STATUS_SMB_BAD_CLUSTER_DIALECT
//
// MessageText:
//
// The current cluster functional level does not support this SMB dialect.
//
#ifndef STATUS_SMB_BAD_CLUSTER_DIALECT
#define STATUS_SMB_BAD_CLUSTER_DIALECT   ((NTSTATUS)0xC05D0001L)
#endif//STATUS_SMB_BAD_CLUSTER_DIALECT

//
// MessageId: STATUS_SMB_GUEST_LOGON_BLOCKED
//
// MessageText:
//
// You can't access this shared folder because your organization's security policies block unauthenticated guest access. These policies help protect your PC from unsafe or malicious devices on the network.
//
#ifndef STATUS_SMB_GUEST_LOGON_BLOCKED
#define STATUS_SMB_GUEST_LOGON_BLOCKED   ((NTSTATUS)0xC05D0002L)
#endif//STATUS_SMB_GUEST_LOGON_BLOCKED

//
// Embedded Security Core
//
// Reserved id values 0x0001 - 0x00FF
//                    0x8xxx
//                    0x4xxx
//
// MessageId: STATUS_SECCORE_INVALID_COMMAND
//
// MessageText:
//
// The command was not recognized by the security core
//
#ifndef STATUS_SECCORE_INVALID_COMMAND
#define STATUS_SECCORE_INVALID_COMMAND   ((NTSTATUS)0xC0E80000L)
#endif//STATUS_SECCORE_INVALID_COMMAND

//
// Virtual Secure Mode (VSM)
//
//
// MessageId: STATUS_VSM_NOT_INITIALIZED
//
// MessageText:
//
// Virtual Secure Mode (VSM) is not initialized. The hypervisor or VSM may not be present or enabled.
//
#ifndef STATUS_VSM_NOT_INITIALIZED
#define STATUS_VSM_NOT_INITIALIZED       ((NTSTATUS)0xC0450000L)
#endif//STATUS_VSM_NOT_INITIALIZED

//
// MessageId: STATUS_VSM_DMA_PROTECTION_NOT_IN_USE
//
// MessageText:
//
// The hypervisor is not protecting DMA because an IOMMU is not present or not enabled in the BIOS.
//
#ifndef STATUS_VSM_DMA_PROTECTION_NOT_IN_USE
#define STATUS_VSM_DMA_PROTECTION_NOT_IN_USE ((NTSTATUS)0xC0450001L)
#endif//STATUS_VSM_DMA_PROTECTION_NOT_IN_USE

//
// Application Execution (AppExec)
//
//
// MessageId: STATUS_APPEXEC_CONDITION_NOT_SATISFIED
//
// MessageText:
//
// The condition supplied for the app execution request was not satisfied, so the request was not performed.
//
#ifndef STATUS_APPEXEC_CONDITION_NOT_SATISFIED
#define STATUS_APPEXEC_CONDITION_NOT_SATISFIED ((NTSTATUS)0xC0EC0000L)
#endif//STATUS_APPEXEC_CONDITION_NOT_SATISFIED

//
// MessageId: STATUS_APPEXEC_HANDLE_INVALIDATED
//
// MessageText:
//
// The supplied handle has been invalidated and may not be used for the requested operation.
//
#ifndef STATUS_APPEXEC_HANDLE_INVALIDATED
#define STATUS_APPEXEC_HANDLE_INVALIDATED ((NTSTATUS)0xC0EC0001L)
#endif//STATUS_APPEXEC_HANDLE_INVALIDATED

//
// MessageId: STATUS_APPEXEC_INVALID_HOST_GENERATION
//
// MessageText:
//
// The supplied host generation has been invalidated and may not be used for the requested operation.
//
#ifndef STATUS_APPEXEC_INVALID_HOST_GENERATION
#define STATUS_APPEXEC_INVALID_HOST_GENERATION ((NTSTATUS)0xC0EC0002L)
#endif//STATUS_APPEXEC_INVALID_HOST_GENERATION

//
// MessageId: STATUS_APPEXEC_UNEXPECTED_PROCESS_REGISTRATION
//
// MessageText:
//
// An attempt to register a process failed because the target host was not in a valid state to receive process registrations.
//
#ifndef STATUS_APPEXEC_UNEXPECTED_PROCESS_REGISTRATION
#define STATUS_APPEXEC_UNEXPECTED_PROCESS_REGISTRATION ((NTSTATUS)0xC0EC0003L)
#endif//STATUS_APPEXEC_UNEXPECTED_PROCESS_REGISTRATION

//
// MessageId: STATUS_APPEXEC_INVALID_HOST_STATE
//
// MessageText:
//
// The host is not in a valid state to support the execution request.
//
#ifndef STATUS_APPEXEC_INVALID_HOST_STATE
#define STATUS_APPEXEC_INVALID_HOST_STATE ((NTSTATUS)0xC0EC0004L)
#endif//STATUS_APPEXEC_INVALID_HOST_STATE

//
// MessageId: STATUS_APPEXEC_NO_DONOR
//
// MessageText:
//
// The operation was not completed because a required resource donor was not found for the host.
//
#ifndef STATUS_APPEXEC_NO_DONOR
#define STATUS_APPEXEC_NO_DONOR          ((NTSTATUS)0xC0EC0005L)
#endif//STATUS_APPEXEC_NO_DONOR

//
// MessageId: STATUS_APPEXEC_HOST_ID_MISMATCH
//
// MessageText:
//
// The operation was not completed because an unexpected host ID was encountered.
//
#ifndef STATUS_APPEXEC_HOST_ID_MISMATCH
#define STATUS_APPEXEC_HOST_ID_MISMATCH  ((NTSTATUS)0xC0EC0006L)
#endif//STATUS_APPEXEC_HOST_ID_MISMATCH

//
// Map a WIN32 error value into an NTSTATUS
// Note: This assumes that WIN32 errors fall in the range -32k to 32k.
//

#define __NTSTATUS_FROM_WIN32(x) ((NTSTATUS)(x) <= 0 ? ((NTSTATUS)(x)) : ((NTSTATUS) (((x) & 0x0000FFFF) | (FACILITY_NTWIN32 << 16) | ERROR_SEVERITY_ERROR)))

#ifdef INLINE_NTSTATUS_FROM_WIN32
#ifndef __midl
__inline NTSTATUS_FROM_WIN32(long x) { return x <= 0 ? (NTSTATUS)x : (NTSTATUS)(((x) & 0x0000FFFF) | (FACILITY_NTWIN32 << 16) | ERROR_SEVERITY_ERROR); }
#else
#define NTSTATUS_FROM_WIN32(x) __NTSTATUS_FROM_WIN32(x)
#endif
#else
#define NTSTATUS_FROM_WIN32(x) __NTSTATUS_FROM_WIN32(x)
#endif


/*lint -restore */  // Resume checking for different macro definitions // winnt
// end_ntsecapi

#endif // WIN32_NO_STATUS // winnt
#endif // _NTSTATUS_
