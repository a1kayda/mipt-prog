
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
void fire(sf::Vector2f d, sf::Vector2f center, sf::Time time, sf::Sprite sprite, float sizex, float sizey)
{
	sprite.setPosition(center.x, center.y);
	sprite.setScale(0.1f, 0.1f);
//	while(sprite.getPosition().x < sizex && sprite.getPosition().x > 0 && sprite.getPosition().y < sizey && sprite.getPosition().y > 0)
//	{
//
//	}
	
}
int main(int argc, char const** argv)
{
    // Create the main window
	sf::Texture texture1;
	if (!texture1.loadFromFile("bullet.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite sprite1(texture1);
	
	
	float sizex, sizey;
	sizex = 748;
	sizey = 421;
    sf::RenderWindow window(sf::VideoMode(sizex, sizey), "SFML window");
	window.setFramerateLimit(60);
	sf::Clock clock;
	
	// Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("hm.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a bg
	sf::Texture texturebg;
	if (!texturebg.loadFromFile("background.png")) {
		return EXIT_FAILURE;
	}
	texturebg.setSmooth(true);
	sf::Sprite bg(texturebg);
	bg.setTexture(texturebg);
	//Load a pearson
    sf::Texture texture;
    if (!texture.loadFromFile("pears.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
//	sf::Texture texture1;
//	if (!texture.loadFromFile("bullet.png")) {
//		return EXIT_FAILURE;
//	}
//	sf::Sprite gun(texture1);
//	bg.setPosition(374, 205.5);
//	bg.setScale(1, 1);
	sprite.setPosition(400, 300);
	sprite.setScale(0.2f, 0.2f);
	sf::Vector2u spriteSize = sprite.getTexture()->getSize();
//	sf::Vector2f dforbullet, centerforbullet;
//    // Create a graphical text to display
//    sf::Font font;
//    if (!font.loadFromFile("sansation.ttf")) {
//        return EXIT_FAILURE;
//    }
//    sf::Text text("Hello SFML", font, 50);
//    text.setFillColor(sf::Color::Black);
//
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("Hotline-Macarena.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    music.play();
	
    // Start the game loop
    while (window.isOpen())
	{
		sprite.setOrigin(spriteSize.x / 2, spriteSize.y / 2);
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f center = sprite.getPosition();
		sf::Vector2f d = sf::Vector2f(mousePosition.x, mousePosition.y) - center;
		sf::Time time = clock.getElapsedTime();
		// Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
			
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
			
        }
		window.clear();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && center.x > 0)
			sprite.move(-10, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && center.x < sizex)
			sprite.move(10, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && center.y > 0)
			sprite.move(0, -10);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && center.y < sizey)
			sprite.move(0, 10);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
//			centerforbullet = center;
//			dforbullet = d;
//			fire(d, center, time, sprite1);
		}
		window.draw(bg);
        window.draw(sprite);
		sprite.setRotation(atan2f(d.y, d.x) * 180 / M_PI);
        window.display();
    }

    return 0;
}


