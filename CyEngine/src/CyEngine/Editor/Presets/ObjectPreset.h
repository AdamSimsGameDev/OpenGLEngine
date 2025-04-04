#pragma once

#include "CyEngine/Core.h"
#include "CyEngine/World.h"

namespace Cy
{
#define DEFINE_OBJECT_PRESET(Preset, Name) bool Preset##::reg = Preset##::Init(#Name);

    class ObjectPresetBase
    {
    public:
        virtual ~ObjectPresetBase() {}
        virtual Object* SpawnObject(World* World) const = 0;

        static std::unordered_map<String, ObjectPresetBase*> ObjectPresets;
    };

    template<typename T>
    class ObjectPreset : public ObjectPresetBase
    {
    public:
        ObjectPreset()
        {
            reg;
        }

        static bool reg;
        static bool Init(String Key)
        {
            T* t = new T();
            ObjectPresetBase::ObjectPresets.emplace( Key, t );
            return true;
        }
    };

    class ObjectPresetCube : public ObjectPreset<ObjectPresetCube>
    {
    public:
        virtual Object* SpawnObject(World* World) const override;
    };

    class ObjectPresetSphere : public ObjectPreset<ObjectPresetSphere>
    {
    public:
        virtual Object* SpawnObject( World* World ) const override;
    };
}
