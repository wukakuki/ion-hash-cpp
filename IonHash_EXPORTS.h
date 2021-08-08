/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#pragma once

#ifdef _MSC_VER
//disable windows complaining about max template size.
    #pragma warning (disable : 4503)
#endif // _MSC_VER

#if defined (USE_WINDOWS_DLL_SEMANTICS) || defined (_WIN32)
    #ifdef _MSC_VER
        #pragma warning(disable : 4251)
    #endif // _MSC_VER

    #ifdef USE_IMPORT_EXPORT
        #ifdef ION_HASH_EXPORTS
            #define ION_HASH_EXPORTS __declspec(dllexport)
        #else
            #define ION_HASH_EXPORTS __declspec(dllimport)
        #endif /* ION_HASH_EXPORTS */
    #else
        #define ION_HASH_EXPORTS
    #endif // USE_IMPORT_EXPORT
#else // defined (USE_WINDOWS_DLL_SEMANTICS) || defined (WIN32)
    #define ION_HASH_EXPORTS
#endif // defined (USE_WINDOWS_DLL_SEMANTICS) || defined (WIN32)
