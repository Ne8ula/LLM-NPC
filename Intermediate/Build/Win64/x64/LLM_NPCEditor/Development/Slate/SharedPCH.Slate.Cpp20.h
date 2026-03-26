// PCH for SlateSharedPCH.h
#include "SharedDefinitions.Slate.Cpp20.h"
#include "SlateSharedPCH.h"
#ifdef __ISPC_ALIGN__
#error ispc.generated.h files are not allowed in precompiled headers (This is a build time optimization to reduce action dependencies)
#endif
