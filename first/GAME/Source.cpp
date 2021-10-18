#include"SFML.h"

using namespace sf;
using namespace std;

class Bullet {
public:
	CircleShape shape;
	Vector2f currVelocity;
	float maxspeed;

	Bullet(float radius = 5.f)
		:currVelocity(0.f, 0.f), maxspeed(15.f)
	{
		this->shape.setRadius(radius);
		this->shape.setFillColor(Color::Red);
	}
};

int main() {
	RenderWindow window(VideoMode(800, 600), "360 Shoter", Style::Default);
	window.setFramerateLimit(60);

	CircleShape player(25.f);
	player.setFillColor(Color::White);

	Vector2f playercenter;
	Vector2f mousePoswindow;
	Vector2f aimDir;
	Vector2f aimDirNorm;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		//Update
		playercenter = Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
		mousePoswindow = Vector2f(Mouse::getPosition(window));
		aimDir = mousePoswindow - playercenter;
		aimDirNorm = aimDir/sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		cout << aimDirNorm.x << " " << aimDirNorm.y << "\n";

		window.clear();
		window.draw(player);
		window.display();
	}
	return 0;
}