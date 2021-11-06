#include"SFML.h"
using namespace sf;
using namespace std;

class Player
{
public:
	Sprite shape;
	Texture* TexTure;
	int HP;
	int HPMax;
	RectangleShape HPshow;

	Player(Texture *texture)
	{
		this->HPMax = 10;
		this->HP = this->HPMax;
		this->HPshow.setFillColor(Color::Red);
		this->HPshow.setOutlineThickness(1.f);
		this->HPshow.setOutlineColor(Color::Blue);
		this->HPshow.setOrigin(HP * 5.f, 2.5f);
		this->TexTure = texture;
		this->shape.setTexture(*texture);
		}
	};

class Enemy
{
public:
	Sprite shape;
	Texture* TexTure;
	Vector2f move;
	float distance;
	int HP;
	int HPMax;
	RectangleShape HPshow;
	Enemy(Texture* texture)
	{
		this->HPMax = 3;
		this->HP = this->HPMax;
		this->HPshow.setFillColor(Color::Red);
		this->HPshow.setOutlineThickness(1.f);
		this->HPshow.setOutlineColor(Color::Blue);
		this->HPshow.setOrigin(HP * 10.f, 7.5f);
		this->TexTure = texture;
		this->shape.setTexture(*texture);

	}
};

class Bullet
{
public:
	Sprite shape;
	Texture* TexTure;
	Vector2f currVelocity;
	float	 maxSpeed;

	Bullet(Texture *textTure)
		: currVelocity(100.f, 100.f), maxSpeed(10.f)
	{
		this->TexTure = textTure;
		this->shape.setTexture(*textTure);
		this->shape.setScale(2.f, 2.f);
	}
};

class Item
{
public:
	Sprite shape;
	Texture* TexTure;
	
	Item(Texture* textture)
	{
		this->TexTure = textture;
		this->shape.setTexture(*textture);
		this->shape.setScale(0.5f, 0.5f);
	}
};

int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(1080, 720), "testdata", Style::Default);
	window.setFramerateLimit(60);

	//Menu
	
	//BGmenu
	Texture Sunday;
	if (!Sunday.loadFromFile("img/sunday.jfif"))
	{
		cout << "Load failed" << endl;
	}
	Sprite BGmenu(Sunday);
	BGmenu.setScale(0.8f, 0.8f);

	//Start
	Texture Startbutton;
	//Startbutton.loadFromFile("img/buttonstart.png");
	if (!Startbutton.loadFromFile("img/play.png")) {
		cout << "Load failed" << endl;
	}
	

	int FramestartbuttonX = Startbutton.getSize().x / 3;
	int FramestartbuttonY = Startbutton.getSize().y;
	Sprite Start;
	Start.setTexture(Startbutton);
	Start.setTextureRect(IntRect(0, 0, FramestartbuttonX, FramestartbuttonY));
	Start.setOrigin(FramestartbuttonX / 2, FramestartbuttonY / 2);
	Start.setPosition(window.getSize().x / 2, window.getSize().y / 2-200);
	bool Play = false;

	//Score
	Texture Scorebutton;
	if (!Scorebutton.loadFromFile("img/score.png")) {
		cout << "Load failed" << endl;
	}
	int FramescorebuttonX = Scorebutton.getSize().x / 3;
	int FramescorebuttonY = Scorebutton.getSize().y;
	Sprite Score;
	Score.setTexture(Scorebutton);
	Score.setTextureRect(IntRect(0, 0, FramescorebuttonX, FramescorebuttonY));
	Score.setOrigin(FramescorebuttonX / 2, FramescorebuttonY / 2);
	Score.setPosition(window.getSize().x / 2, window.getSize().y / 2 );

	//Exit
	Texture Exitbutton;
	if (!Exitbutton.loadFromFile("img/exit.png")) {
		cout << "Load failed" << endl;
	}
	int FrameexitbuttonX = Exitbutton.getSize().x / 3;
	int FrameexitbuttonY = Exitbutton.getSize().y;
	Sprite Exit;
	Exit.setTexture(Exitbutton);
	Exit.setTextureRect(IntRect(0, 0, FrameexitbuttonX, FrameexitbuttonY));
	Exit.setOrigin(FrameexitbuttonX / 2, FrameexitbuttonY / 2);
	Exit.setPosition(window.getSize().x / 2, window.getSize().y / 2+200);


	//Texture Player	
	Texture Playertexture;
	Playertexture.loadFromFile("img/zelda2 (2).png");
	int FramePlayerX = Playertexture.getSize().x / 12;
	int FramePlayerY = Playertexture.getSize().y / 4;

	//Player
	Player player(&Playertexture);
	player.shape.setTextureRect(IntRect(0, 0, FramePlayerX, FramePlayerY));
	//player.shape.setOrigin(SizeX / 2, SizeY / 2);
	Vector2f SpawnPoint = { window.getSize().x / 2 - player.shape.getGlobalBounds().width ,window.getSize().y / 2 - player.shape.getGlobalBounds().height  };
	player.shape.setPosition(SpawnPoint);

	//Texture Enemy
	Texture Enemytexture;
	if (!Enemytexture.loadFromFile("img/enemytest (1).png")) {
		cout << "Load failed" << endl;
	}
	int FrameEnemyX = Enemytexture.getSize().x / 8;
	int FrameEnemyY = Enemytexture.getSize().y;

	//Enemy
	Enemy enemy(&Enemytexture);
	enemy.shape.setTextureRect(IntRect(0, 0, FrameEnemyX, FrameEnemyY));
	vector<Enemy>Enemies;
	//Enemies.push_back(Enemy(enemy));
	int SpawnEnemy = 0;

	//Textture Ghost
	Texture EnemyGhost;
	if (!EnemyGhost.loadFromFile("img/ghost.png")) {
		cout << "Load failed" << endl;
	}
	int FrameEnemyGhostX = EnemyGhost.getSize().x / 3;
	int FrameEnemyGhostY = EnemyGhost.getSize().y / 4;

	//EnemyGhost
	Enemy Ghost(&EnemyGhost);
	Ghost.shape.setTextureRect(IntRect(0, FrameEnemyGhostY*2, FrameEnemyGhostX, FrameEnemyGhostY));
	vector<Enemy>Ghosts;
	//Ghosts.push_back(Enemy(Ghost));
	int SpawnEnemyGhost = 0;

	//Texture Oak
	Texture EnemyOak;
	if (!EnemyOak.loadFromFile("img/Oak.png")) {
		cout << "Load failed" << endl;
	}
	int FrameEnemyOakX = EnemyOak.getSize().x / 3;
	int FrameEnemyOakY = EnemyOak.getSize().y / 4;

	//Enemy Oak
	Enemy Oak(&EnemyOak);
	Oak.shape.setTextureRect(IntRect(0, FrameEnemyOakY, FrameEnemyOakX, FrameEnemyOakY));
	vector<Enemy>Oaks;
	//Oaks.push_back(Enemy(Oak));

	int randnum;

	Texture ItemHeal;
	if (!ItemHeal.loadFromFile("img/heart.png")) {
		cout << "Load failed" << endl;
	}
	int FrameItemHealX = ItemHeal.getSize().x / 3;
	int FrameItemHealY = ItemHeal.getSize().y / 2;
	Item Heal(&ItemHeal);
	Heal.shape.setTextureRect(IntRect(0, 0, FrameItemHealX, FrameItemHealY));
	vector<Item>Heals;




	//Vector 360degree
	Vector2f playercenter;
	Vector2f mouseposwindow;
	Vector2f aimDir;
	float ainDirNorm;
	Vector2f abc;

	//Texture Bullet
	Texture bulletTexture;
	if(!bulletTexture.loadFromFile("img/piwpiw.png"))
	{
		cout << "Load failed" << endl;
	}
	int FramebulletX = bulletTexture.getSize().x / 4;
	int FramebulletY = bulletTexture.getSize().y;

	//Bullet 360degree
	Bullet bullet(&bulletTexture);
	bullet.shape.setTextureRect(IntRect(0, 0, FramebulletX, FramebulletY));
		vector<Bullet>bullets;
		//bullets.push_back(Bullet(bullet));
		int count = 0;




	
	//Fontscore
	Font font;
	if (!font.loadFromFile("front/Leoscar Serif.ttf")) {
		cout <<"Could not load front";
	}
	Text score;
	score.setFont(font);
	score.setCharacterSize(35);
	//score.setFillColor(Color::Yellow);
	score.setStyle(Text::Bold);
	int Scores = 0;
	score.setString("Score : ");


	//Background
	Texture Forest;
	if (!Forest.loadFromFile("img/forest.jfif"))
	{
		cout << "Load failed" << endl;
	}
	Sprite Background(Forest);
	Background.setScale(0.8f, 0.8f);

	//BGinputname
	Texture BGmenuname;
	if (!BGmenuname.loadFromFile("img/sunday.jfif"))
	{
		cout << "Load failed" << endl;
	}
	Sprite bgmenuname(BGmenuname);
	bgmenuname.setScale(0.8f, 0.8f);
	
	Texture BGinputname;
	if (!BGinputname.loadFromFile("img/name2.png"))
	{
		cout << "Load failed" << endl;
	}
	Sprite bginputname(BGinputname);
	bginputname.setScale(1.5f, 1.5f);
	bginputname.setPosition(window.getSize().x/2-bginputname.getGlobalBounds().width/2, window.getSize().y/2-bginputname.getGlobalBounds().height/2-50);
	bool nameplayer = false;

	//Fontname
	Font fontname;
	if (!fontname.loadFromFile("front/Leoscar Serif.ttf")) {
		cout << "Could not load front";
	}
	Text nameUI;
	nameUI.setFont(fontname);
	nameUI.setCharacterSize(40);
	nameUI.setStyle(Text::Bold);
	nameUI.setPosition(window.getSize().x/2-100, window.getSize().y/2+30);
	String test;
	//name.setString(test);
	

	int animationFramePlayer = 0;
	int animationFrameEnemy = 0;
	int animationFrameGhost = 0;
	int animationFrameOak = 0;
	int animationBullet = 0;
	int animationHeart = 0;



	//highScore
	int scores[6], number = 0;
	string rscore;
	ifstream fscore("score.txt");
	while (getline(fscore, rscore)) {
		scores[number++] = stoi(rscore);
	}
	fscore.close();
	string names[6], rname;
	number = 0;
	ifstream fname("name.txt");
	while (getline(fname, rname)) {
		names[number++] = rname+'\n';
	}
	fname.close();
	bool savescore = true;


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::TextEntered && !nameplayer && Play) {
			//	//stoi(event.text.unicode);
			//	cout << event.text.unicode;
				if (event.text.unicode < 128) {
					//test += static_cast<char>(event.text.unicode);
					if (Keyboard::isKeyPressed(Keyboard::Backspace)){
						test = test.substring(0, test.getSize() - 1);
					}
					else { test += static_cast<char>(event.text.unicode); }
			}
			}
			/*if (Event::KeyPressed) {
				cout << event.key.code;
			}*/
		}

		playercenter = Vector2f(player.shape.getPosition().x +FramePlayerX/2, player.shape.getPosition().y+ FramePlayerY/2);
		mouseposwindow = Vector2f(Mouse::getPosition(window));
		aimDir = mouseposwindow - playercenter;
		ainDirNorm = sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
		abc = aimDir / ainDirNorm;
		
		if (!Play)
		{
			window.draw(BGmenu);
			window.draw(Start);
			if (Start.getGlobalBounds().contains(mouseposwindow)) {
				Start.setTextureRect(IntRect(FramestartbuttonX * 1, 0, FramestartbuttonX, FramestartbuttonY));
				if (Mouse::isButtonPressed(Mouse::Left)) {
					Start.setTextureRect(IntRect(FramestartbuttonX * 2, 0, FramestartbuttonX, FramestartbuttonY));
				Play = true;
				}
			}
			else
			{
				Start.setTextureRect(IntRect(FramestartbuttonX * 0, 0, FramestartbuttonX, FramestartbuttonY));

			}

			window.draw(Score);
			if (Score.getGlobalBounds().contains(mouseposwindow)) {
				Score.setTextureRect(IntRect(FramescorebuttonX * 1, 0, FramescorebuttonX, FramescorebuttonY));
				if (Mouse::isButtonPressed(Mouse::Left)) {
					Score.setTextureRect(IntRect(FramescorebuttonX * 2, 0, FramescorebuttonX, FramescorebuttonY));
					//Play = true;
				}
			}
			else
			{
				Score.setTextureRect(IntRect(FramescorebuttonX * 0, 0, FramescorebuttonX, FramescorebuttonY));

			}

			window.draw(Exit);
			if (Exit.getGlobalBounds().contains(mouseposwindow)) {
				Exit.setTextureRect(IntRect(FrameexitbuttonX * 1, 0, FrameexitbuttonX, FrameexitbuttonY));
				if (Mouse::isButtonPressed(Mouse::Left)) {
					Exit.setTextureRect(IntRect(FrameexitbuttonX * 2, 0, FrameexitbuttonX, FrameexitbuttonY));
					window.close();
				}
			}
			else
			{
				Exit.setTextureRect(IntRect(FrameexitbuttonX * 0, 0, FrameexitbuttonX, FrameexitbuttonY));

			}

		}
		
		if (Play && !nameplayer) {
			nameUI.setString(test);
			window.draw(bgmenuname);
			window.draw(bginputname);
			window.draw(nameUI);
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				nameplayer = true;
			}
		}

			
		if (Play && nameplayer && player.HP > 0) {
			window.draw(Background);

			//Score
			score.setString("Score : " + to_string(Scores));


			


			//draw
			window.draw(player.shape);
			window.draw(player.HPshow);
			for (size_t i = 0;i < Enemies.size();i++) {
				Enemies[i].HPshow.setSize(Vector2f((float)Enemies[i].HP * 20.f, 5.f));
				Enemies[i].HPshow.setPosition(Enemies[i].shape.getPosition().x + FrameEnemyX / 2, Enemies[i].shape.getPosition().y - 5);
				window.draw(Enemies[i].shape);
				window.draw(Enemies[i].HPshow);
			}
			for (size_t i = 0;i < Ghosts.size();i++) {
				Ghosts[i].HPshow.setSize(Vector2f((float)Ghosts[i].HP * 20.f, 5.f));
				Ghosts[i].HPshow.setPosition(Ghosts[i].shape.getPosition().x + FrameEnemyGhostX / 2, Ghosts[i].shape.getPosition().y - 5);
				window.draw(Ghosts[i].shape);
				window.draw(Ghosts[i].HPshow);
			}
			for (size_t i = 0;i < Oaks.size();i++) {
				Oaks[i].HPshow.setSize(Vector2f((float)Oaks[i].HP * 20.f, 5.f));
				Oaks[i].HPshow.setPosition(Oaks[i].shape.getPosition().x + FrameEnemyOakX / 2, Oaks[i].shape.getPosition().y - 5);
				window.draw(Oaks[i].shape);
				window.draw(Oaks[i].HPshow);
			}
			for (size_t i = 0;i < bullets.size();i++) {
				window.draw(bullets[i].shape);
			}
			for (size_t i = 0;i < Heals.size();i++) {
				window.draw(Heals[i].shape);
				Heals[i].shape.setTextureRect(IntRect(FrameItemHealX * ((animationHeart/4) % 3), FrameItemHealY * (animationHeart / 12), FrameItemHealX, FrameItemHealY));
			}
			window.draw(score);
			//window.display();
			//cout << Keyboard::isKeyPressed(Keyboard::Key::Add);

			//Playermove
			if (Keyboard::isKeyPressed(Keyboard::A) && player.shape.getPosition().x > 0)
			{
				player.shape.move(-3.f, 0.f);
				player.shape.setTextureRect(IntRect(FramePlayerX * animationFramePlayer, FramePlayerY * 3, FramePlayerX, FramePlayerY));
			}
			if (Keyboard::isKeyPressed(Keyboard::D) && player.shape.getPosition().x + FramePlayerX < window.getSize().x)
			{
				player.shape.move(3.f, 0.f);
				player.shape.setTextureRect(IntRect(FramePlayerX * animationFramePlayer, FramePlayerY * 1, FramePlayerX, FramePlayerY));
			}
			if (sf::Keyboard::isKeyPressed(Keyboard::W) && player.shape.getPosition().y > 150)
			{
				player.shape.move(0.f, -3.f);
				player.shape.setTextureRect(IntRect(FramePlayerX * animationFramePlayer, 0, FramePlayerX, FramePlayerY));
			}
			if (Keyboard::isKeyPressed(Keyboard::S) && player.shape.getPosition().y + FramePlayerY < window.getSize().y)
			{
				player.shape.move(0.f, 3.f);
				player.shape.setTextureRect(IntRect(FramePlayerX * animationFramePlayer, FramePlayerY * 2, FramePlayerX, FramePlayerY));
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}



			//Spawn enemy
			if (SpawnEnemy < 60) {
				SpawnEnemy++;
			}
			if (SpawnEnemy >= 60) {
				randnum = rand() % 3;
				if (randnum == 0) {
					enemy.shape.setPosition((rand() % int(window.getSize().x - FrameEnemyX)), 0.f);
					Enemies.push_back(Enemy(enemy));
				}
				if (randnum == 1) {
					Ghost.shape.setPosition(0.f, (rand() % int(window.getSize().y - FrameEnemyGhostY -150))+150);
					Ghosts.push_back(Enemy(Ghost));
				}
				if (randnum == 2) {
					Oak.shape.setPosition(window.getSize().x, (rand() % int(window.getSize().y - FrameEnemyOakY -150))+150);
					Oaks.push_back(Enemy(Oak));
				}
				//cout << randnum << endl;
				SpawnEnemy = 0;
			}

			for (size_t i = 0;i < Enemies.size();i++) {
				Enemies[i].move.x = player.shape.getPosition().x - Enemies[i].shape.getPosition().x;
				Enemies[i].move.y = player.shape.getPosition().y - Enemies[i].shape.getPosition().y;
				Enemies[i].distance = sqrt(pow(Enemies[i].move.x, 2) + pow(Enemies[i].move.y, 2));
				Enemies[i].move /= Enemies[i].distance;
				//if(Enemies[i].shape.getPosition().x>player.shape.getPosition().x){ Enemies[i].shape.move(-2.f, 0.f); }
				//if (Enemies[i].shape.getPosition().x < player.shape.getPosition().x) { Enemies[i].shape.move(2.f, 0.f); }
				//if (Enemies[i].shape.getPosition().y > player.shape.getPosition().y) { Enemies[i].shape.move(0.f, -4.f); }
				//if (Enemies[i].shape.getPosition().y < player.shape.getPosition().y) { Enemies[i].shape.move(0.f, 4.f); }
				Enemies[i].shape.move(Enemies[i].move.x,Enemies[i].move.y);
				Enemies[i].shape.setTextureRect(IntRect(FrameEnemyX* (((animationFrameEnemy+i)/2)%8), 0, FrameEnemyX, FrameEnemyY));
				if (Enemies[i].shape.getPosition().y > window.getSize().y - 20) {
					Enemies.erase(Enemies.begin() + i);
				}
			}

			//Spawn Ghost
			if (SpawnEnemyGhost < 30) {
				SpawnEnemyGhost++;
			}
			if (SpawnEnemyGhost >= 30) {
				/*Ghost.shape.setPosition(0.f, rand() % int(window.getSize().y - FrameEnemyGhostY));
				Ghosts.push_back(Enemy(Ghost));*/
				SpawnEnemyGhost = 0;
			}
			for (size_t i = 0;i < Ghosts.size();i++) {
				//Ghosts[i].move /= Ghosts[i].distance;
				Ghosts[i].move.x = player.shape.getPosition().x - Ghosts[i].shape.getPosition().x;
				Ghosts[i].move.y = player.shape.getPosition().y - Ghosts[i].shape.getPosition().y;
				Ghosts[i].distance = sqrt(pow(Ghosts[i].move.x, 2) + pow(Ghosts[i].move.y, 2));
				Ghosts[i].move /= Ghosts[i].distance;
				Ghosts[i].shape.move(Ghosts[i].move.x,Ghosts[i].move.y);
				if (abs(Ghosts[i].move.x) > abs(Ghosts[i].move.y) && Ghosts[i].shape.getPosition().x > player.shape.getPosition().x) {
					Ghosts[i].shape.setTextureRect(IntRect(FrameEnemyGhostX * (((animationFrameGhost + i) / 7) % 3), FrameEnemyGhostY , FrameEnemyGhostX, FrameEnemyGhostY));
				}
				if (abs(Ghosts[i].move.x) > abs(Ghosts[i].move.y) && Ghosts[i].shape.getPosition().x < player.shape.getPosition().x) {
					Ghosts[i].shape.setTextureRect(IntRect(FrameEnemyGhostX * (((animationFrameGhost + i) / 7) % 3), FrameEnemyGhostY * 2, FrameEnemyGhostX, FrameEnemyGhostY));
				}
				if (abs(Ghosts[i].move.x) < abs(Ghosts[i].move.y) && Ghosts[i].shape.getPosition().y < player.shape.getPosition().y) {
					Ghosts[i].shape.setTextureRect(IntRect(FrameEnemyGhostX * (((animationFrameGhost + i) / 7) % 3), 0, FrameEnemyGhostX, FrameEnemyGhostY));
				}
				if (abs(Ghosts[i].move.x) < abs(Ghosts[i].move.y) && Ghosts[i].shape.getPosition().y > player.shape.getPosition().y) {
					Ghosts[i].shape.setTextureRect(IntRect(FrameEnemyGhostX * (((animationFrameGhost + i) / 7) % 3), FrameEnemyGhostY*3, FrameEnemyGhostX, FrameEnemyGhostY));
				}
				/*if (Ghosts[i].shape.getPosition().x > window.getSize().x - 20) {
					Ghosts.erase(Ghosts.begin() + i);
				}*/
			}

			//Spawn Oak
			for (size_t i = 0;i < Oaks.size();i++) {
				//Oaks[i].move /= Oaks[i].distance;
				Oaks[i].move.x = player.shape.getPosition().x - Oaks[i].shape.getPosition().x;
				Oaks[i].move.y = player.shape.getPosition().y - Oaks[i].shape.getPosition().y;
				Oaks[i].distance = sqrt(pow(Oaks[i].move.x, 2) + pow(Oaks[i].move.y, 2));
				Oaks[i].move /= Oaks[i].distance;
				//Oaks[i].shape.setRotation(atan2(Oaks[i].move.y, Oaks[i].move.x) * 180 / 3.14159265359 + 180);
				Oaks[i].shape.move(Oaks[i].move.x, Oaks[i].move.y);
				if (abs(Oaks[i].move.x) > abs(Oaks[i].move.y) && Oaks[i].shape.getPosition().x > player.shape.getPosition().x) {
					Oaks[i].shape.setTextureRect(IntRect(FrameEnemyOakX * (((animationFrameOak + i) / 7) % 3), FrameEnemyOakY, FrameEnemyOakX, FrameEnemyOakY));
				}
				if (abs(Oaks[i].move.x) > abs(Oaks[i].move.y) && Oaks[i].shape.getPosition().x < player.shape.getPosition().x) {
					Oaks[i].shape.setTextureRect(IntRect(FrameEnemyOakX * (((animationFrameOak + i) / 7) % 3), FrameEnemyOakY * 2, FrameEnemyOakX, FrameEnemyOakY));
				}
				if (abs(Oaks[i].move.x) < abs(Oaks[i].move.y) && Oaks[i].shape.getPosition().y < player.shape.getPosition().y) {
					Oaks[i].shape.setTextureRect(IntRect(FrameEnemyOakX * (((animationFrameOak + i) / 7) % 3), 0, FrameEnemyOakX, FrameEnemyOakY));
				}
				if (abs(Oaks[i].move.x) < abs(Oaks[i].move.y) && Oaks[i].shape.getPosition().y > player.shape.getPosition().y)  {
					Oaks[i].shape.setTextureRect(IntRect(FrameEnemyOakX * (((animationFrameOak + i) / 7) % 3), FrameEnemyOakY * 3, FrameEnemyOakX, FrameEnemyOakY));
				}
				//if (Oaks[i].shape.getPosition().x > window.getSize().x - 20) {
				//	Oaks.erase(Oaks.begin() + i);
				//}
			}


			//shoot
			if (count < 5) { //timedelayshoot
				count++;
			}

			if (Mouse::isButtonPressed(Mouse::Left) && count >= 5) {
				bullet.shape.setPosition(playercenter);
				bullet.currVelocity = abc * bullet.maxSpeed;
				bullets.push_back(Bullet(bullet));
				count = 0;
			}

			for (size_t i = 0; i < bullets.size(); i++)
			{
				bullets[i].shape.move(bullets[i].currVelocity);
				bullets[i].shape.setTextureRect(IntRect(FramebulletX* (((animationBullet + i)/5) % 4), 0, FramebulletX, FramebulletY));
				if (bullets[i].shape.getPosition().y < 0 ||
					bullets[i].shape.getPosition().x < 0 ||
					bullets[i].shape.getPosition().y + bullet.TexTure->getSize().y> window.getSize().y ||
					bullets[i].shape.getPosition().x + bullet.TexTure->getSize().x> window.getSize().x)
				{
					bullets.erase(bullets.begin() + i);
				}
			}

			//shot+enemy
			if (!Enemies.empty() && !bullets.empty())
			{
				for (size_t i = 0;i < bullets.size();i++) {
					for (size_t k = 0;k < Enemies.size();k++) {
						if (bullets[i].shape.getGlobalBounds().intersects(Enemies[k].shape.getGlobalBounds())) {
							bullets.erase(bullets.begin() + i);
							Enemies[k].HP--;
							if (Enemies[k].HP == 0)
							{
								Enemies.erase(Enemies.begin() + k);

								Scores+=enemy.HPMax;
							}
							break;
						}
					}
				}
			}

			for (size_t i = 0;i < bullets.size();i++) {
				for (size_t k = 0;k < Ghosts.size();k++) {
					if (bullets[i].shape.getGlobalBounds().intersects(Ghosts[k].shape.getGlobalBounds())) {
						bullets.erase(bullets.begin() + i);
						Ghosts[k].HP--;
						if (Ghosts[k].HP == 0)
						{
							randnum = rand() % 4;
							if (randnum == 3) {
								Heals.push_back(Item(Heal));
							Heals[Heals.size() - 1].shape.setPosition(Ghosts[k].shape.getPosition());
							}
							Ghosts.erase(Ghosts.begin() + k);
							Scores += Ghost.HPMax;
						}
						break;
					}
				}
			}

			for (size_t i = 0;i < bullets.size();i++) {
				for (size_t k = 0;k < Oaks.size();k++) {
					if (bullets[i].shape.getGlobalBounds().intersects(Oaks[k].shape.getGlobalBounds())) {
						bullets.erase(bullets.begin() + i);
						Oaks[k].HP--;
						if (Oaks[k].HP == 0)
						{
							Oaks.erase(Oaks.begin() + k);
							Scores += Oak.HPMax;
						}
						break;
					}
				}
			}


			//Player+enemy
			for (size_t i = 0;i < Enemies.size();i++) {
				if (player.shape.getGlobalBounds().intersects(Enemies[i].shape.getGlobalBounds())) {
					player.HP--;
					//hp--;
					Enemies.erase(Enemies.begin() + i);
				}
			}

			for (size_t i = 0;i < Ghosts.size();i++) {
				if (player.shape.getGlobalBounds().intersects(Ghosts[i].shape.getGlobalBounds())) {
					player.HP--;
					//hp--;
					Ghosts.erase(Ghosts.begin() + i);
				}
			}

			for (size_t i = 0;i < Oaks.size();i++) {
				if (player.shape.getGlobalBounds().intersects(Oaks[i].shape.getGlobalBounds())) {
					player.HP--;
					//hp--;
					Oaks.erase(Oaks.begin() + i);
				}
			}

			player.HPshow.setSize(Vector2f((float)player.HP * 10.f, 15.f));
			player.HPshow.setPosition(player.shape.getPosition().x + FramePlayerX / 2, player.shape.getPosition().y - 30);

			//Player+Item
			for (size_t i = 0;i < Heals.size();i++) {
				if (player.shape.getGlobalBounds().intersects(Heals[i].shape.getGlobalBounds())) {
					if (player.HP < player.HPMax) {
						player.HP++;
					}
					Heals.erase(Heals.begin() + i);
				}
			}
	


			//Frame
			animationFramePlayer++;
			if (animationFramePlayer >= 11) {
				animationFramePlayer = 0;
			}
			animationFrameEnemy++;
			if (animationFrameEnemy >= 16) {
				animationFrameEnemy = 0;
			}
			animationFrameGhost++;
			if (animationFrameGhost >= 21) {
				animationFrameGhost = 0;
			}
			animationFrameOak++;
			if (animationFrameOak >= 21) {
				animationFrameOak = 0;
			}
			animationBullet++;
			if (animationBullet >= 20) {
				animationBullet = 0;
			}
			animationHeart++;
			if (animationHeart >= 24) {
				animationHeart = 0;
			}

			
		}

		//if (!(player.HP > 0)) {
		//	window.draw(Background);
		//	for (int i = 0;i < 5;i++) {
		//		if (test == names[i]) {
		//			savescore = false;
		//		}
		//		//else { savescore = true; }
		//	}
		//	if (savescore) {
		//		scores[5] = Scores;
		//		names[5] = test;
		//	}
		//	//cout << test;
		//	for (int i = 0;i < 6;i++) {
		//		for (int j = 0;j < 5;j++) {
		//			if (scores[j] < scores[j + 1]) {
		//				swap(scores[j], scores[j + 1]);
		//				swap(names[j], names[j + 1]);
		//			}
		//		}
		//	}
		//	for (int i = 0;i < 6;i++) {
		//		//cout << scores[i] << endl;
		//		//cout << names[i];
		//	}
		//}
		window.display();
		window.clear();
	}
	return 0;
}