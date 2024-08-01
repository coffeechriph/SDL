/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2024 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "SDL_internal.h"

#ifndef SDL_D3D12_H
#define SDL_D3D12_H

#if !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES))

/* From the DirectX-Headers build system:
 * "MinGW has RPC headers which define old versions, and complain if D3D
 * headers are included before the RPC headers, since D3D headers were
 * generated with new MIDL and "require" new RPC headers."
 */
#define __REQUIRED_RPCNDR_H_VERSION__ 475

/* May not be defined in winapifamily.h, can safely be ignored */
#ifndef WINAPI_PARTITION_GAMES
#define WINAPI_PARTITION_GAMES 0
#endif /* WINAPI_PARTITION_GAMES */

#define COBJMACROS
#include "d3d12.h"
#include <dxgi1_6.h>
#include <dxgidebug.h>

#define D3D_GUID(X) &(X)

#define D3D_SAFE_RELEASE(X)      \
    if (X) {                     \
        (X)->lpVtbl->Release(X); \
        X = NULL;                \
    }

/* FIXME: Remove this in favor of the COBJMACROS defines */
#define D3D_CALL(THIS, FUNC, ...)     (THIS)->lpVtbl->FUNC((THIS), ##__VA_ARGS__)
#define D3D_CALL_RET(THIS, FUNC, ...) (THIS)->lpVtbl->FUNC((THIS), ##__VA_ARGS__)

#else /* !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)) */

#if defined(SDL_PLATFORM_XBOXONE)
#include <d3d12_x.h>
#else /* SDL_PLATFORM_XBOXSERIES */
#include <d3d12_xs.h>
#endif

#define D3D_GUID(X) (X)

#define D3D_SAFE_RELEASE(X) \
    if (X) {                \
        (X)->Release();     \
        X = NULL;           \
    }

/* Older versions of the Xbox GDK may not have this defined */
#ifndef D3D12_TEXTURE_DATA_PITCH_ALIGNMENT
#define D3D12_TEXTURE_DATA_PITCH_ALIGNMENT 256
#endif

/* DXGI_PRESENT flags are removed on Xbox */
#define DXGI_PRESENT_ALLOW_TEARING 0

/* FIXME: Xbox D3D12 does not define the COBJMACROS, so we need to define them ourselves */
#define D3D_CALL(THIS, FUNC, ...)             (THIS)->FUNC(__VA_ARGS__)
#define D3D_CALL_RET(THIS, FUNC, RETVAL, ...) *(RETVAL) = (THIS)->FUNC(__VA_ARGS__)

#endif /* !(defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)) */

#endif /* SDL_D3D12_H */
