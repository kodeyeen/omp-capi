/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2024, open.mp team and contributors.
 */

#pragma once
#include "../ComponentManager.hpp"
#include "../../Utils/Singleton.hpp"
#include "sdk.hpp"

struct CustomModelsEvents : public PlayerModelsEventHandler, public Singleton<CustomModelsEvents>
{
	virtual void onPlayerFinishedDownloading(IPlayer& player) override
	{
		ComponentManager::Get()->CallEvent("onPlayerFinishedDownloading", EventReturnHandler::None, &player);
	}

	virtual bool onPlayerRequestDownload(IPlayer& player, ModelDownloadType type, uint32_t checksum) override
	{
		return ComponentManager::Get()->CallEvent("onPlayerRequestDownload", EventReturnHandler::StopAtFalse, &player, int(type), int(checksum));
	}
};
