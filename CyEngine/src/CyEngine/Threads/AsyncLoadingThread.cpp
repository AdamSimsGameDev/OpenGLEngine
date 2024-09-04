#include "cypch.h"
#include "AsyncLoadingThread.h"
#include "CyEngine/AssetManager/AssetManager.h"
#include "CyEngine/AssetManager/AssetInfo.h"

namespace Cy
{
	void AsyncLoadingThread::ThreadTick()
	{
		AssetManager& Manager = AssetManager::Get();

		AssetInfo* NextAsset = nullptr;
		while (NextAsset == nullptr)
		{
			if (Manager.AssetAsyncLoadQueue.Dequeue(NextAsset))
			{
				// If the asset is no longer being loaded or we have already loaded it, skip it
				if (!NextAsset->IsLoading() || NextAsset->IsLoaded())
				{
					NextAsset = nullptr;
					continue;
				}
			}

			break;
		}

		// Load the asset
		if (NextAsset)
		{
			Manager.LoadImmediate(NextAsset);
		}
	}
}