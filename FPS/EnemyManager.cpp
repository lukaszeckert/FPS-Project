#include "EnemyManager.h"

EnemyManager* EnemyManager::enemyManager = nullptr;

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

EnemyManager&  EnemyManager::getEnemyManager()
{
	if (enemyManager == nullptr)
		enemyManager = new EnemyManager();
	return *enemyManager;
}

void EnemyManager::destroyEnemyManager()
{
	delete enemyManager;
}

void EnemyManager::update(float dTime)
{
	
	for (auto it : enemies)
		it->update(dTime);
	for(int i=0;i<enemies.size();++i)
		if (enemies[i]->getHp() <= 0)
		{
			destroyEnemy(enemies[i]);
			i--;
		}
}

void EnemyManager::createEnemy(glm::vec3 position, Object * object, ShaderInterface * shader)
{
	auto entity = new Entity(position, object, shader, EntityType::ENEMY);
	ResourceManager::getResourceManager().getEntityArray()->push_back(entity);
	auto enemy = new Enemy(entity,100.0f);
	enemies.push_back(enemy);
}

void EnemyManager::destroyEnemy(Enemy * enemy)
{
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [enemy](auto it) {return enemy == it; }),enemies.end());
	delete enemy;
}
