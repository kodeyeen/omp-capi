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

struct CoreEvents : public CoreEventHandler, public Singleton<CoreEvents>
{
	void onTick(Microseconds elapsed, TimePoint now) override
	{
		long long nowSeconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

		ComponentManager::Get()->CallEvent("onTick", EventReturnHandler::None, int(elapsed.count()), nowSeconds);
	}
};
