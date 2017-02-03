/* Copyright (c) Citrix Systems Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, 
 * with or without modification, are permitted provided 
 * that the following conditions are met:
 * 
 * *   Redistributions of source code must retain the above 
 *     copyright notice, this list of conditions and the 
 *     following disclaimer.
 * *   Redistributions in binary form must reproduce the above 
 *     copyright notice, this list of conditions and the 
 *     following disclaimer in the documentation and/or other 
 *     materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE.
 */ 

#ifndef _XENVBD_XENVBD_H
#define _XENVBD_XENVBD_H

#include "fdo.h"
#include <xen.h>

// Global Constants
#define XENVBD_MAX_TARGETS              (255)

#define XENVBD_MAX_RING_PAGE_ORDER      (4)
#define XENVBD_MAX_RING_PAGES           (1 << XENVBD_MAX_RING_PAGE_ORDER)

#define XENVBD_MAX_SEGMENTS_PER_REQUEST (BLKIF_MAX_SEGMENTS_PER_REQUEST)
#define XENVBD_MAX_REQUESTS_PER_SRB     (16)
#define XENVBD_MAX_SEGMENTS_PER_SRB     (XENVBD_MAX_REQUESTS_PER_SRB * XENVBD_MAX_SEGMENTS_PER_REQUEST)
#define XENVBD_MAX_TRANSFER_LENGTH      (XENVBD_MAX_SEGMENTS_PER_SRB * PAGE_SIZE)
#define XENVBD_MAX_PHYSICAL_BREAKS      (XENVBD_MAX_SEGMENTS_PER_SRB - 1)
#define XENVBD_MAX_QUEUE_DEPTH          (254)

#define XENVBD_MIN_GRANT_REFS           (XENVBD_MAX_SEGMENTS_PER_SRB)

typedef struct _XENVBD_PARAMETERS {
    BOOLEAN     SynthesizeInquiry;
    BOOLEAN     PVCDRom;
} XENVBD_PARAMETERS;

extern XENVBD_PARAMETERS    DriverParameters;

extern HANDLE
DriverGetParametersKey(
    VOID
    );

extern NTSTATUS
DriverDispatchPnp(
    IN  PDEVICE_OBJECT  DeviceObject,
    IN  PIRP            Irp
    );

extern NTSTATUS
DriverDispatchPower(
    IN  PDEVICE_OBJECT  DeviceObject,
    IN  PIRP            Irp
    );

// Fdo Device Extension management
extern VOID
DriverLinkFdo(
    __in PXENVBD_FDO             Fdo
    );

extern VOID
DriverUnlinkFdo(
    __in PXENVBD_FDO             Fdo
    );

extern VOID
DriverRequestReboot(
    VOID
    );

__checkReturn
__drv_allocatesMem(mem)
extern PCHAR
DriverFormat(
    __in PCHAR                   Format,
    ...
    );

extern VOID
DriverFormatFree(
    __in __drv_freesMem(mem) PCHAR Buffer
    );

#endif // _XENVBD_XENVBD_H
