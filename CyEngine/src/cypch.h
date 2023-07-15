#pragma once

#ifdef CY_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "CyEngine/Core.h"
#include "CyEngine/Log.h"
#include "CyEngine/Transform.h"

// Input
#include "CyEngine/Input.h"
#include "CyEngine/KeyCode.h"

// Maths
#include "CyEngine/Maths/Colour.h"
#include "CyEngine/Maths/Maths.h"
#include "CyEngine/Maths/Matrix.h"
#include "CyEngine/Maths/Quat.h"
#include "CyEngine/Maths/Vector.h"
