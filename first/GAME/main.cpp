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
	int time;
	bool kaphip;
	
	Item(Texture* textture)
	{
		this->TexTure = textture;
		this->shape.setTexture(*textture);
		this->shape.setScale(0.5f, 0.5f);
		this->time = 0;
		this->kaphip = false;
	}
};

int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(1080, 720), "Aden", Style::Default);
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

	//Aden
	Texture Aden;
	if (!Aden.loadFromFile("img/Aden.png")) {
		cout << "Load failed" << endl;
	}
	Sprite AdenUI;
	AdenUI.setTexture(Aden);
	AdenUI.setPosition(window.getSize().x / 2-AdenUI.getGlobalBounds().width/2, 0.f);

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
	Start.setPosition(window.getSize().x / 2, window.getSize().y / 2 -120);
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
	Score.setPosition(window.getSize().x / 2, window.getSize().y / 2 +80);
	bool Showscore = false;

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
	Exit.setPosition(window.getSize().x / 2, window.getSize().y / 2 +280);

	//Creater
	Font font;
	if (!font.loadFromFile("front/Leoscar Serif.ttf")) {
		cout << "Could not load front";
	}
	Text Creater;
	Creater.setFont(font);
	Creater.setCharacterSize(23);
	Creater.setStyle(Text::Bold);
	Creater.setOutlineColor(Color::Black);
	Creater.setOutlineThickness(3);
	Creater.setString("64011109  Nutchapon  Tripat");
	Creater.setPosition(window.getSize().x-Creater.getGlobalBounds().width-20, window.getSize().y -50);

	//BGinputname
	Texture BGinputname;
	if (!BGinputname.loadFromFile("img/name2.png"))
	{
		cout << "Load failed" << endl;
	}
	Sprite bginputname(BGinputname);
	bginputname.setScale(1.5f, 1.5f);
	bginputname.setPosition(window.getSize().x / 2 - bginputname.getGlobalBounds().width / 2, window.getSize().y / 2 - bginputname.getGlobalBounds().height / 2 - 50);
	bool nameplayer = false;

	//Fontname
	Text nameUI;
	nameUI.setFont(font);
	nameUI.setCharacterSize(40);
	nameUI.setStyle(Text::Bold);
	nameUI.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 + 30);
	string test;

	//Backgroundplay
	Texture Forest;
	if (!Forest.loadFromFile("img/forest.jfif"))
	{
		cout << "Load failed" << endl;
	}
	Sprite Background(Forest);
	Background.setScale(0.8f, 0.8f);

	//Player	
	Texture Playertexture;
	Playertexture.loadFromFile("img/zelda2 (2).png");
	int FramePlayerX = Playertexture.getSize().x / 12;
	int FramePlayerY = Playertexture.getSize().y / 4;

	Player player(&Playertexture);
	player.shape.setTextureRect(IntRect(0, 0, FramePlayerX, FramePlayerY));
	Vector2f SpawnPoint = { window.getSize().x / 2 - player.shape.getGlobalBounds().width ,window.getSize().y / 2 - player.shape.getGlobalBounds().height  };
	player.shape.setPosition(SpawnPoint);

	//Enemy
	Texture Enemytexture;
	if (!Enemytexture.loadFromFile("img/enemytest (1).png")) {
		cout << "Load failed" << endl;
	}
	int FrameEnemyX = Enemytexture.getSize().x / 8;
	int FrameEnemyY = Enemytexture.getSize().y;

	Enemy enemy(&Enemytexture);
	enemy.shape.setTextureRect(IntRect(0, 0, FrameEnemyX, FrameEnemyY));
	vector<Enemy>Enemies;

	//Ghost
	Texture EnemyGhost;
	if (!EnemyGhost.loadFromFile("img/ghost.png")) {
		cout << "Load failed" << endl;
	}
	int FrameEnemyGhostX = EnemyGhost.getSize().x / 3;
	int FrameEnemyGhostY = EnemyGhost.getSize().y / 4;

	Enemy Ghost(&EnemyGhost);
	Ghost.shape.setTextureRect(IntRect(0, FrameEnemyGhostY*2, FrameEnemyGhostX, FrameEnemyGhostY));
	vector<Enemy>Ghosts;

	//Oak
	Texture EnemyOak;
	if (!EnemyOak.loadFromFile("img/Oak.png")) {
		cout << "Load failed" << endl;
	}
	int FrameEnemyOakX = EnemyOak.getSize().x / 3;
	int FrameEnemyOakY = EnemyOak.getSize().y / 4;

	Enemy Oak(&EnemyOak);
	Oak.shape.setTextureRect(IntRect(0, FrameEnemyOakY, FrameEnemyOakX, FrameEnemyOakY));
	vector<Enemy>Oaks;

	int SpawnEnemy = 0;
	int randnum;
	int timerspawnenemy = 0;
	int sec = 0;

	//bulletenemy
	//left
	Texture bulletleft;
	if (!bulletleft.loadFromFile("img/bulletleft.png")) {
		cout << "Load failed" << endl;
	}
	int FrameEnemybulletleftX = bulletleft.getSize().x / 3;
	int FrameEnemybulletleftY = bulletleft.getSize().y ;

	Bullet BulletleftUI(&bulletleft);
	BulletleftUI.shape.setTextureRect(IntRect(0, 0, FrameEnemybulletleftX, FrameEnemybulletleftY));
	vector<Bullet>BulletsleftUI;
	int SpawnBulletenemy = 0;
	int timerspawnbulletenemy = 0;

	//right
	Texture bulletright;
	if (!bulletright.loadFromFile("img/bulletleft.png")) {
		cout << "Load failed" << endl;
	}
	int FrameEnemybulletrightX = bulletright.getSize().x / 3;
	int FrameEnemybulletrightY = bulletright.getSize().y;

	Bullet BulletrightUI(&bulletright);
	BulletrightUI.shape.setTextureRect(IntRect(0, 0, FrameEnemybulletrightX, FrameEnemybulletrightY));
	vector<Bullet>BulletsrightUI;

	//Heal
	Texture ItemHeal;
	if (!ItemHeal.loadFromFile("img/heart.png")) {
		cout << "Load failed" << endl;
	}
	int FrameItemHealX = ItemHeal.getSize().x / 3;
	int FrameItemHealY = ItemHeal.getSize().y / 2;
	Item Heal(&ItemHeal);
	Heal.shape.setTextureRect(IntRect(0, 0, FrameItemHealX, FrameItemHealY));
	vector<Item>Heals;
	int rategame = 0;

	//star
	Texture ItemStar;
	if (!ItemStar.loadFromFile("img/star.png")) {
		cout << "Load failed" << endl;
	}
	int FrameItemStarX = ItemStar.getSize().x / 8;
	int FrameItemStarY = ItemStar.getSize().y;
	Item Star(&ItemStar);
	Star.shape.setTextureRect(IntRect(0, 0, FrameItemStarX, FrameItemStarY));
	Star.shape.setScale(1.2f,1.2f);
	vector<Item>Stars;



	//Bullet
	Texture bulletTexture;
	if(!bulletTexture.loadFromFile("img/piwpiw.png"))
	{
		cout << "Load failed" << endl;
	}
	int FramebulletX = bulletTexture.getSize().x / 4;
	int FramebulletY = bulletTexture.getSize().y;

	Bullet bullet(&bulletTexture);
	bullet.shape.setTextureRect(IntRect(0, 0, FramebulletX, FramebulletY));
	vector<Bullet>bullets;
	int count = 0;

	//Vector 360degree
	Vector2f playercenter;
	Vector2f mouseposwindow;
	Vector2f aimDir;
	float ainDirNorm;
	Vector2f abc;

	//scoring
	Text scoring;
	scoring.setFont(font);
	scoring.setCharacterSize(50);
	scoring.setStyle(Text::Bold);
	scoring.setOutlineColor(Color::Black);
	scoring.setOutlineThickness(3);
	scoring.setString("Score : ");
	int Scores = 0;

	//animation
	int animationFramePlayer = 0;
	int animationFrameEnemy = 0;
	int animationFrameGhost = 0;
	int animationFrameOak = 0;
	int animationBulletleft = 0;
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

	//highScoreUI
	Texture Scoreboard;
	if (!Scoreboard.loadFromFile("img/highscore.png"))
	{
		cout << "Load failed" << endl;
	}
	Sprite ScoreboardUI(Scoreboard);
	ScoreboardUI.setScale(2.9f, 2.9f);
	ScoreboardUI.setPosition(window.getSize().x / 2 - ScoreboardUI.getGlobalBounds().width / 2, window.getSize().y / 2 - ScoreboardUI.getGlobalBounds().height / 2 );
	bool dead = false;

	Text textscoreboard;
	textscoreboard.setFont(font);
	textscoreboard.setCharacterSize(50);
	textscoreboard.setStyle(Text::Bold);

	Text nameboardUI;
	nameboardUI.setFont(font);
	nameboardUI.setCharacterSize(40);
	nameboardUI.setStyle(Text::Bold);
	nameboardUI.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 + 30);

	//buttonHome
	Texture Buttonhome;
	if (!Buttonhome.loadFromFile("img/buttonhome.png"))
	{
		cout << "Load failed" << endl;
	}
	Sprite HomeUI(Buttonhome);
	HomeUI.setPosition(window.getSize().x - HomeUI.getGlobalBounds().width, window.getSize().y - HomeUI.getGlobalBounds().height);
	bool Home = true;


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::TextEntered && !nameplayer && Play) {
				if (event.text.unicode < 128) {
					//test += static_cast<char>(event.text.unicode);
					if (Keyboard::isKeyPressed(Keyboard::Backspace)){
						if (!test.empty()) {
							test.pop_back();
						}
					}
					else { test += static_cast<char>(event.text.unicode); }
			}
			}

		}

		playercenter = Vector2f(player.shape.getPosition().x +FramePlayerX/2, player.shape.getPosition().y+ FramePlayerY/2);
		mouseposwindow = Vector2f(Mouse::getPosition(window));
		aimDir = mouseposwindow - playercenter;
		ainDirNorm = sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
		abc = aimDir / ainDirNorm;
		
		if (!Play && Home)
		{
			window.draw(BGmenu);
			window.draw(AdenUI);
			window.draw(Creater);
			window.draw(Start);
			if (Start.getGlobalBounds().contains(mouseposwindow)) {
				Start.setTextureRect(IntRect(FramestartbuttonX * 1, 0, FramestartbuttonX, FramestartbuttonY));
				if (Mouse::isButtonPressed(Mouse::Left)) {
					Start.setTextureRect(IntRect(FramestartbuttonX * 2, 0, FramestartbuttonX, FramestartbuttonY));
				Play = true;
				Home = false;
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
					Showscore = true;
					Home = false;
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
			window.draw(BGmenu);
			window.draw(bginputname);
			window.draw(nameUI);
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				test += '\n';
				nameplayer = true;
			}
		}

			
		if (Play && nameplayer && player.HP > 0) {
			
			//draw
			window.draw(Background);
			window.draw(player.shape);
			window.draw(player.HPshow);
			for (size_t i = 0;i < BulletsleftUI.size();i++) {
				window.draw(BulletsleftUI[i].shape);
			}
			for (size_t i = 0;i < BulletsrightUI.size();i++) {
				BulletsrightUI[i].shape.setRotation(180);
				window.draw(BulletsrightUI[i].shape);
			}
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
				if (!Heals[i].kaphip) {
					window.draw(Heals[i].shape);
				}
				Heals[i].shape.setTextureRect(IntRect(FrameItemHealX * ((animationHeart/4) % 3), FrameItemHealY * (animationHeart / 12), FrameItemHealX, FrameItemHealY));
			}
			for (size_t i = 0;i < Stars.size();i++) {
				if (!Stars[i].kaphip) {
					window.draw(Stars[i].shape);
				}
			}
			window.draw(scoring);

			//Score
			scoring.setString("Score : " + to_string(Scores));

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
				player.HP = 0;
			}



			//Spawn enemy
			sec++;
			if (sec >= 300) {
				if (timerspawnenemy < 8) {
					timerspawnenemy++;
				}
				if (timerspawnenemy == 8) {
					if (timerspawnbulletenemy < 14) {
						timerspawnbulletenemy++;
					}
					else
					{
						rategame == 3;
					}
				}
				sec = 0;
			}
			if (SpawnEnemy < (120-(timerspawnenemy*10))) {
				SpawnEnemy++;
			}
			if (SpawnEnemy >= (120-(timerspawnenemy*10))) {
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
				SpawnEnemy = 0;
			}

			for (size_t i = 0;i < Enemies.size();i++) {
				Enemies[i].move.x = player.shape.getPosition().x - Enemies[i].shape.getPosition().x;
				Enemies[i].move.y = player.shape.getPosition().y - Enemies[i].shape.getPosition().y;
				Enemies[i].distance = sqrt(pow(Enemies[i].move.x, 2) + pow(Enemies[i].move.y, 2));
				Enemies[i].move /= Enemies[i].distance;
				Enemies[i].shape.move(Enemies[i].move.x,Enemies[i].move.y);
				Enemies[i].shape.setTextureRect(IntRect(FrameEnemyX* (((animationFrameEnemy+i)/2)%8), 0, FrameEnemyX, FrameEnemyY));
				if (Enemies[i].shape.getPosition().y > window.getSize().y - 20) {
					Enemies.erase(Enemies.begin() + i);
				}
			}

			//Spawn Ghost
			for (size_t i = 0;i < Ghosts.size();i++) {
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
			}

			//Spawn Oak
			for (size_t i = 0;i < Oaks.size();i++) {
				Oaks[i].move.x = player.shape.getPosition().x - Oaks[i].shape.getPosition().x;
				Oaks[i].move.y = player.shape.getPosition().y - Oaks[i].shape.getPosition().y;
				Oaks[i].distance = sqrt(pow(Oaks[i].move.x, 2) + pow(Oaks[i].move.y, 2));
				Oaks[i].move /= Oaks[i].distance;
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
			}

			//Spawn Bulletleft&right
			if (SpawnBulletenemy < (300 - (timerspawnbulletenemy * 10))) {
				SpawnBulletenemy++;
			}
			if (SpawnBulletenemy >= (300-(timerspawnbulletenemy*10))) {
				randnum = rand() % 2;
				if (randnum == 0) {
					BulletleftUI.shape.setPosition(0.f, player.shape.getPosition().y);
					BulletsleftUI.push_back(Bullet(BulletleftUI));
				}
				if (randnum == 1) {
					BulletrightUI.shape.setPosition(window.getSize().x, player.shape.getPosition().y +70);
					BulletsrightUI.push_back(Bullet(BulletrightUI));
				}
				SpawnBulletenemy = 0;
			}
			for (size_t i = 0;i < BulletsleftUI.size();i++) {
				BulletsleftUI[i].shape.move(5.f,0.f);
				BulletsleftUI[i].shape.setTextureRect(IntRect(FrameEnemybulletleftX*(((animationBulletleft+i)/7)%3),0,FrameEnemybulletleftX,FrameEnemybulletleftY));
				if (BulletsleftUI[i].shape.getPosition().x > window.getSize().x - 20) {
					BulletsleftUI.erase(BulletsleftUI.begin() + i);
				}
			}

			for (size_t i = 0;i < BulletsrightUI.size();i++) {
				BulletsrightUI[i].shape.move(-5.f, 0.f);
				BulletsrightUI[i].shape.setTextureRect(IntRect(FrameEnemybulletrightX * (((animationBulletleft + i) / 7) % 3), 0, FrameEnemybulletrightX, FrameEnemybulletrightY));
				if (BulletsrightUI[i].shape.getPosition().x < 20) {
					BulletsrightUI.erase(BulletsrightUI.begin() + i);
				}
			}


			//shoot
			if (count < 10) { //timedelayshoot
				count++;
			}

			if (Mouse::isButtonPressed(Mouse::Left) && count >= 10) {
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

			//time item
			for (size_t i = 0;i < Heals.size();i++) {
				Heals[i].time++;
				if (Heals[i].time >= 480) {
					if (((Heals[i].time % 30) / 2) == 1) {
						Heals[i].kaphip = true;
					}
					else { Heals[i].kaphip = false; }
				}
				if (Heals[i].time == 600) {
					Heals.erase(Heals.begin() + i);
				}
			}

			for (size_t i = 0;i < Stars.size();i++) {
				Stars[i].time++;
				if (Stars[i].time >= 480) {
					if (((Stars[i].time % 30) / 2) == 1) {
						Stars[i].kaphip = true;
					}
					else { Stars[i].kaphip = false; }
				}
				if (Stars[i].time == 600) {
					Stars.erase(Stars.begin() + i);
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
							randnum = rand() % (4+rategame);
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
							randnum = rand() % 4;
							if (randnum == 3) {
								Stars.push_back(Item(Star));
								Stars[Stars.size() - 1].shape.setPosition(Oaks[k].shape.getPosition());
							}
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
					Enemies.erase(Enemies.begin() + i);
				}
			}

			for (size_t i = 0;i < Ghosts.size();i++) {
				if (player.shape.getGlobalBounds().intersects(Ghosts[i].shape.getGlobalBounds())) {
					player.HP--;
					Ghosts.erase(Ghosts.begin() + i);
				}
			}

			for (size_t i = 0;i < Oaks.size();i++) {
				if (player.shape.getGlobalBounds().intersects(Oaks[i].shape.getGlobalBounds())) {
					player.HP--;
					Oaks.erase(Oaks.begin() + i);
				}
			}

			for (size_t i = 0;i < BulletsleftUI.size();i++) {
				if (player.shape.getGlobalBounds().intersects(BulletsleftUI[i].shape.getGlobalBounds())) {
					player.HP--;
					BulletsleftUI.erase(BulletsleftUI.begin() + i);
				}
			}

			for (size_t i = 0;i < BulletsrightUI.size();i++) {
				if (player.shape.getGlobalBounds().intersects(BulletsrightUI[i].shape.getGlobalBounds())) {
					player.HP--;
					BulletsrightUI.erase(BulletsrightUI.begin() + i);
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

			for (size_t i = 0;i < Stars.size();i++) {
				if (player.shape.getGlobalBounds().intersects(Stars[i].shape.getGlobalBounds())) {
					Scores += 10 + (rand() % 11);
					Stars.erase(Stars.begin() + i);
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
			animationBulletleft++;
			if (animationBulletleft >= 24) {
				animationBulletleft = 0;
			}

			
		}

		if (!(player.HP > 0) || Showscore) {
			window.draw(Background);
			window.draw(ScoreboardUI);
			if (Showscore) {
				window.draw(HomeUI);
				if (HomeUI.getGlobalBounds().contains(mouseposwindow)) {
					if (Mouse::isButtonPressed(Mouse::Left)) {
						Home = true;
						Showscore = false;
					}
				}
			}
			for (int i = 0;i < 5;i++) {
				textscoreboard.setString(to_string(scores[i]));
				textscoreboard.setPosition(window.getSize().x / 2 - textscoreboard.getGlobalBounds().width / 2 + 200, window.getSize().y / 2 - textscoreboard.getGlobalBounds().height / 2 + (i*80) - 130);
				textscoreboard.setOutlineColor(Color::Red);
				textscoreboard.setOutlineThickness(3);
				window.draw(textscoreboard);
				nameboardUI.setString(names[i]);
				nameboardUI.setCharacterSize(50);
				nameboardUI.setOutlineColor(Color::Red);
				nameboardUI.setOutlineThickness(3);
				nameboardUI.setPosition(window.getSize().x / 2 - nameboardUI.getGlobalBounds().width / 2 - 200, window.getSize().y / 2 - nameboardUI.getGlobalBounds().height / 2 + (i * 80) - 110);
				window.draw(nameboardUI);
			}

			if (!(player.HP > 0)) {
				for (int i = 0;i < 5;i++) {
					if (names[i] == test) {
						if (scores[i] == Scores) {
							savescore = false;
						}
					}
					//else { savescore = true; }
				}
				if (savescore) {
					scores[5] = Scores;
					names[5] = test;
					for (int i = 0;i < 6;i++) {
						for (int j = 0;j < 5;j++) {
							if (scores[j] < scores[j + 1]) {
								swap(scores[j], scores[j + 1]);
								swap(names[j], names[j + 1]);
								break;
							}
						}
					}
					for (int i = 0;i < 5;i++) {
						cout << names[i];
						cout << scores[i] << endl;
					}
					ofstream wscore("score.txt");
					ofstream wname("name.txt");
					for (int j = 0;j < 5;j++)
					{
						//cout << scores[j] << endl;
						wscore << scores[j] << endl;
						wname << names[j] ;
					}
					wscore.close();
					wname.close();
					/*cout << test;*/
				}
			}
		}
		window.display();
		window.clear();
	}
	return 0;
}