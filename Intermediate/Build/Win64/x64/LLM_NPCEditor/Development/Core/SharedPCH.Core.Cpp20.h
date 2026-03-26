// PCH for CoreSharedPCH.h
#include "SharedDefinitions.Core.Cpp20.h"
#include "CoreSharedPCH.h"
#ifdef __ISPC_ALIGN__
#error ispc.generated.h files are not allowed in precompiled headers (This is a build time optimization to reduce action dependencies)
#endif
