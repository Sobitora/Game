//texture bullet

////bullet
//Sprite bullet;
//bullet.setTexture(bulletTexture);
//vector<Sprite> bullets;
//bullets.push_back(Sprite(bullet));
//int shootertime = 0;
//Vector2f currVelocity2(0.f, 0.f);
//vector<Vector2f> currvelocity;
//currvelocity.push_back(Vector2f(currVelocity2));
//float maxspeed(15.f);


//texture enemy
//Texture EnemyTexture;
//if (!EnemyTexture.loadFromFile("img/enemytest (1).png")) {
//	cout << "Load failed" << endl;
//}

//enemy
//Sprite enemytest;
//enemytest.setTexture(EnemyTexture);
//int EnemySizeX = EnemyTexture.getSize().x / 8;
//int EnemySizeY = EnemyTexture.getSize().y;
//enemytest.setTextureRect(IntRect(0, 0, EnemySizeX, EnemySizeY));
////RectangleShape enemy(Vector2f(50.f, 50.f));
////enemy.setFillColor(Color::Yellow);
//vector<Sprite>enemies;
//enemies.push_back(Sprite(enemytest));
//int spawnEnemy = 0;

		//spawn enemy
		//if (spawnEnemy < 30) {
		//	spawnEnemy++;
		//}
		//if (spawnEnemy >= 30) {
		//	enemytest.setPosition((rand() % int(window.getSize().x - EnemySizeX)), 0.f);
		//	enemies.push_back(Sprite(enemytest));	
		//	spawnEnemy = 0;
		//}
		//for (size_t i = 0;i < enemies.size();i++) {
		//	enemies[i].move(0.f, 4.f);
		//	//enemies[i].setTextureRect(IntRect(EnemySizeX * animationFrane, EnemySizeY, EnemySizeX, EnemySizeY));
		//	if (enemies[i].getPosition().y > window.getSize().y-20) {
		//		enemies.erase(enemies.begin() + i);
		//	}
		//}

//shooot
		//if (shootertime < 4) { //timedelayshoot
		//	shootertime++;
		//}
		//if (Mouse::isButtonPressed(Mouse::Left) && shootertime >= 4) {
		//	bullet.setPosition(shapeSprite.getPosition().x, shapeSprite.getPosition().y);
		//	bullets.push_back(Sprite(bullet));
		//	shootertime = 0;
		//}
		//for (size_t i = 0;i < bullets.size();i++) {
		//	bullets[i].move(0.f, -10.f);
		//	if (bullets[i].getPosition().y < 0) {
		//		bullets.erase(bullets.begin() + i);
		//	}
		//}