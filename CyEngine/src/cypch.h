#pragma once

#ifdef CY_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <typeinfo>

#include "CyEngine/String.h"
#include "CyEngine/GUID.h"
#include "CyEngine/Collections/Array.h"
#include "CyEngine/Collections/Queue.h"
#include "CyEngine/Maths/Vector.h"
#include "CyEngine/Maths/Quat.h"
#include "CyEngine/Maths/Matrix.h"
