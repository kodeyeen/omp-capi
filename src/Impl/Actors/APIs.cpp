/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2024, open.mp team and contributors.
 */

#include "../ComponentManager.hpp"

OMP_CAPI(Actor_Create, objectPtr(int model, float x, float y, float z, float rot))
{
	IActorsComponent* component = ComponentManager::Get()->actors;
	if (component)
	{
		IActor* actor = component->create(model, { x, y, z }, rot);
		if (actor)
		{
			return actor;
		}
	}
	return nullptr;
}

OMP_CAPI(Actor_Destroy, void(objectPtr actor))
{
	POOL_ENTITY(actors, IActor, actor, actor_);
	actors->release(actor_->getID());
}

OMP_CAPI(Actor_FromID, objectPtr(int actorid))
{
	IActorsComponent* component = ComponentManager::Get()->actors;
	if (component)
	{
		return component->get(actorid);
	}
	return nullptr;
}

OMP_CAPI(Actor_GetID, int(objectPtr actor))
{
	POOL_ENTITY_RET(actors, IActor, actor, actor_, INVALID_ACTOR_ID);
	return actor_->getID();
}

OMP_CAPI(Actor_IsStreamedInFor, bool(objectPtr actor, objectPtr player))
{
	POOL_ENTITY_RET(actors, IActor, actor, actor_, false);
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	return actor_->isStreamedInForPlayer(*player_);
}

OMP_CAPI(Actor_SetVirtualWorld, void(objectPtr actor, int vw))
{
	POOL_ENTITY(actors, IActor, actor, actor_);
	actor_->setVirtualWorld(vw);
}

OMP_CAPI(Actor_GetVirtualWorld, int(objectPtr actor))
{
	POOL_ENTITY_RET(actors, IActor, actor, actor_, 0);
	return actor_->getVirtualWorld();
}

OMP_CAPI(Actor_ApplyAnimation, void(objectPtr actor, StringCharPtr name, StringCharPtr library, float delta, bool loop, bool lockX, bool lockY, bool freeze, int time))
{
	POOL_ENTITY(actors, IActor, actor, actor_);
	const AnimationData animationData(delta, loop, lockX, lockY, freeze, uint32_t(time), library, name);
	actor_->applyAnimation(animationData);
}

OMP_CAPI(Actor_ClearAnimations, void(objectPtr actor))
{
	POOL_ENTITY(actors, IActor, actor, actor_);
	actor_->clearAnimations();
}

OMP_CAPI(Actor_SetPos, void(objectPtr actor, float x, float y, float z))
{
	POOL_ENTITY(actors, IActor, actor, actor_);
	actor_->setPosition({ x, y, z });
}

OMP_CAPI(Actor_GetPos, void(objectPtr actor, float* x, float* y, float* z))
{
	POOL_ENTITY(actors, IActor, actor, actor_);
	const Vector3& pos = actor_->getPosition();

	*x = pos.x;
	*y = pos.y;
	*z = pos.z;
}

OMP_CAPI(Actor_SetFacingAngle, void(objectPtr actor, float angle))
{
	POOL_ENTITY(actors, IActor, actor, actor_);
	actor_->setRotation(Vector3(0.0f, 0.0f, angle));
}

OMP_CAPI(Actor_GetFacingAngle, float(objectPtr actor))
{
	POOL_ENTITY_RET(actors, IActor, actor, actor_, 0.0f);
	return actor_->getRotation().ToEuler().z;
}

OMP_CAPI(Actor_SetHealth, void(objectPtr actor, float hp))
{
	POOL_ENTITY(actors, IActor, actor, actor_);
	actor_->setHealth(hp);
}

OMP_CAPI(Actor_GetHealth, float(objectPtr actor))
{
	POOL_ENTITY_RET(actors, IActor, actor, actor_, 0.0f);
	return actor_->getHealth();
}

OMP_CAPI(Actor_SetInvulnerable, void(objectPtr actor, bool toggle))
{
	POOL_ENTITY(actors, IActor, actor, actor_);
	actor_->setInvulnerable(toggle);
}

OMP_CAPI(Actor_IsInvulnerable, bool(objectPtr actor))
{
	POOL_ENTITY_RET(actors, IActor, actor, actor_, false);
	return actor_->isInvulnerable();
}

OMP_CAPI(Actor_IsValid, bool(objectPtr actor))
{
	POOL_ENTITY_RET(actors, IActor, actor, actor_, false);
	if (!actors->get(actor_->getID()))
		return false;
	return true;
}

OMP_CAPI(Actor_SetSkin, void(objectPtr actor, int skin))
{
	POOL_ENTITY(actors, IActor, actor, actor_);
	actor_->setSkin(skin);
}

OMP_CAPI(Actor_GetSkin, int(objectPtr actor))
{
	POOL_ENTITY_RET(actors, IActor, actor, actor_, 0);
	return actor_->getSkin();
}

OMP_CAPI(Actor_GetAnimation, void(objectPtr actor, OutputStringViewPtr library, OutputStringViewPtr name, float* delta, bool* loop, bool* lockX, bool* lockY, bool* freeze, int* time))
{
	POOL_ENTITY(actors, IActor, actor, actor_);
	const AnimationData& anim = actor_->getAnimation();

	SET_CAPI_STRING_VIEW(library, anim.lib);
	SET_CAPI_STRING_VIEW(name, anim.name);
	*delta = anim.delta;
	*loop = anim.loop;
	*lockX = anim.lockX;
	*lockY = anim.lockY;
	*freeze = anim.freeze;
	*time = int(anim.time);
}

OMP_CAPI(Actor_GetSpawnInfo, void(objectPtr actor, float* x, float* y, float* z, float* angle, int* skin))
{
	POOL_ENTITY(actors, IActor, actor, actor_);
	const ActorSpawnData& spawnData = actor_->getSpawnData();

	*x = spawnData.position.x;
	*y = spawnData.position.y;
	*z = spawnData.position.z;
	*angle = spawnData.facingAngle;
	*skin = spawnData.skin;
}
