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

struct PickupEvents : public PickupEventHandler, public Singleton<PickupEvents>
{
	void onPlayerPickUpPickup(IPlayer& player, IPickup& pickup) override
	{
		if (pickup.getLegacyPlayer() == nullptr)
		{
			ComponentManager::Get()->CallEvent("onPlayerPickUpPickup", EventReturnHandler::None, &player, &pickup);
		}
		else if (auto data = queryExtension<IPlayerPickupData>(player))
		{
			ComponentManager::Get()->CallEvent("onPlayerPickUpPlayerPickup", EventReturnHandler::None, &player, &pickup);
		}
	}
};
