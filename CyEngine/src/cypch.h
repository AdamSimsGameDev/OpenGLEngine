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

#include "CyEngine/Class.h"
#include "CyEngine/Core.h"
#include "CyEngine/CoreMinimal.h"
#include "CyEngine/Log.h"
#include "CyEngine/Objects/Object.h"
#include "CyEngine/Objects/SceneObject.h"
#include "CyEngine/Scene.h"
#include "CyEngine/Components/Component.h"

// Input
#include "CyEngine/Input.h"
#include "CyEngine/KeyCode.h"

// Maths
#include "CyEngine/Maths/Colour.h"
#include "CyEngine/Maths/Maths.h"
#include "CyEngine/Maths/Matrix.h"
#include "CyEngine/Maths/Quat.h"
#include "CyEngine/Maths/Vector.h"
#include "CyEngine/Transform.h"

