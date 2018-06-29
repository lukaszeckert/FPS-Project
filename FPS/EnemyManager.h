#pragma once
#include "Enemy.h"
#include <vector>

class EnemyManager
{
	std::vector<Enemy*> enemies;
	static EnemyManager *enemyManager;
	EnemyManager();
	~EnemyManager();
public:
	static EnemyManager& getEnemyManager();
	static void destroyEnemyManager();
	void update(float dTime);
	void createEnemy(glm::vec3 position, Object* object, ShaderInterface *shader);
	void destroyEnemy(Enemy* enemy);

};

