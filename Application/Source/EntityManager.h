#pragma once
#include "Entity.h"

class EntityManager
{
public:
	EntityManager();
	//Simple type alias
	using Entity = std::uint32_t;

	//Used to def arr later on
	const Entity MAX_ENTITIES = 5000;

	Entity CreateEntity();
	

	void DestroyEntity(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Invalidate the destroyed entity's signature
		mSignatures[entity].reset();

		// Put the destroyed ID at the back of the queue
		mAvailableEntities.push(entity);
		--mLivingEntityCount;
	}

	void SetSignature(Entity entity, Signature signature)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Put this entity's signature into the array
		mSignatures[entity] = signature;
	}

	Signature GetSignature(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Get this entity's signature from the array
		return mSignatures[entity];
	}

private:
	// Queue of unused entity IDs
	std::queue<Entity> mAvailableEntities{};

	// Array of signatures where the index corresponds to the entity ID
	std::array<Signature, MAX_ENTITIES> mSignatures{};

	// Total living entities - used to keep limits on how many exist
	uint32_t mLivingEntityCount{};
}


