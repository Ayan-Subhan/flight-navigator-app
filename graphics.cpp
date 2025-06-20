#include <fstream>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<cmath>

class visual {
    float city_x[11] = {700, 245, 500, 890, 488, 510, 784, 920, 540, 861, 815};
    float city_y[11] = {250, 195, 177, 224, 165, 163, 340, 470, 163, 224, 265};
    int num_cities;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Sprite introsprite;

public:
    visual() {
        num_cities = 11;

        if (!backgroundTexture.loadFromFile("image.jpg")) {
            std::cerr << "Failed to load image.jpg!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);
    }

    void drawBackground(sf::RenderWindow &window) {
        window.draw(backgroundSprite); // Draw the background image
    }
    void drawintro(sf::RenderWindow &window) {
    window.clear(sf::Color(200, 200, 200)); // Light gray background

    // Load the intro texture
    sf::Texture introTexture;
    if (!introTexture.loadFromFile("intro.png")) { // Use the new image
        std::cerr << "Failed to load intro.png!" << std::endl;
        return;
    }

    sf::Sprite introsprite;
    introsprite.setTexture(introTexture);

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = introTexture.getSize();

    // Center the image
    float posX = (windowSize.x - textureSize.x) / 2.0f;
    float posY = (windowSize.y - textureSize.y) / 2.0f - 50.f; // Slightly upward adjustment
    introsprite.setPosition(posX, posY);



    // Draw the intro image
    window.draw(introsprite);

    // Add text "SkyNavAI" below the image with font size 20
    sf::Font font;
    if (!font.loadFromFile("arial.TTF")) { // Replace with your font file
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("SkyNavAI");
    text.setCharacterSize(20);            // Font size 20
    text.setFillColor(sf::Color::Black); // Black text
    text.setStyle(sf::Text::Bold);

    // Center the text below the image
    sf::FloatRect textBounds = text.getLocalBounds();
    float textPosX = (windowSize.x - textBounds.width) / 2.0f;
    float textPosY = posY + textureSize.y + 20.f; // 20px below the image

    text.setPosition(textPosX, textPosY);

    // Draw the text
    window.draw(text);
}



    void drawCities(sf::RenderWindow &window) {
        for (int i = 0; i < num_cities; ++i) {
            sf::CircleShape city(3); // Circle radius of 3
            city.setFillColor(sf::Color::Blue);
            city.setPosition(city_x[i] - 3, city_y[i] - 3); // Center the circle at the coordinates
            window.draw(city);
        }
    }

void drawArrows(sf::RenderWindow &window, int i, int j) {
	
    if (i >= 0 && i < num_cities && j >= 0 && j < num_cities) {
        // Draw the main line
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(city_x[i], city_y[i]), sf::Color::Red), // Start point
            sf::Vertex(sf::Vector2f(city_x[j], city_y[j]), sf::Color::Red)  // End point
        };
        window.draw(line, 2, sf::Lines);

        // Calculate direction vector and normalize it
        float dx = city_x[j] - city_x[i];
        float dy = city_y[j] - city_y[i];
        float length = std::sqrt(dx * dx + dy * dy);

        if (length != 0) {
            dx /= length;
            dy /= length;

            // Define arrowhead size
            float arrow_size = 10.0f;

            // Calculate perpendicular vector for the arrowhead
            float perp_x = -dy;
            float perp_y = dx;

            // Calculate arrowhead points
            sf::Vector2f end(city_x[j], city_y[j]);
            sf::Vector2f left = end - sf::Vector2f(dx * arrow_size, dy * arrow_size) + sf::Vector2f(perp_x * arrow_size * 0.5f, perp_y * arrow_size * 0.5f);
            sf::Vector2f right = end - sf::Vector2f(dx * arrow_size, dy * arrow_size) - sf::Vector2f(perp_x * arrow_size * 0.5f, perp_y * arrow_size * 0.5f);

            // Draw arrowhead as a triangle
            sf::Vertex arrowhead[] = {
                sf::Vertex(end, sf::Color::Red),   // Tip of the arrow
                sf::Vertex(left, sf::Color::Red), // Left side of the arrowhead
                sf::Vertex(right, sf::Color::Red) // Right side of the arrowhead
            };
            window.draw(arrowhead, 3, sf::Triangles);
        }
    } else {
        std::cerr << "Invalid city indexes: " << i << ", " << j << std::endl;
    }
    sf::sleep(sf::seconds(1));
}	

	void drawdash(sf::RenderWindow &window,int i){
	    if (i >= 0 && i < num_cities) {
                sf::RectangleShape dash(sf::Vector2f(35.f, 5.f)); // A small horizontal line (5x2)
                dash.setFillColor(sf::Color::Green);
                dash.setPosition(city_x[i]-17.f , city_y[i]-5.f ); // Center the dash at the city coordinates
                window.draw(dash);
            } else {
                std::cerr << "Invalid city index: " << i << std::endl;
            }
	}
	
	int calculatedis(int i,int j){
		int dist=sqrt(((city_x[i]-city_x[j])*(city_x[i]-city_x[j]))+((city_y[i]-city_y[j])*(city_y[i]-city_y[j])));
		return dist;
	}



void drawoutro(sf::RenderWindow &window) {
    window.clear(sf::Color(255, 150, 150)); // Light red background

    // Load the intro texture
    sf::Texture introTexture;
    if (!introTexture.loadFromFile("outro.png")) { // Use the new image
        std::cerr << "Failed to load intro.png!" << std::endl;
        return;
    }

    sf::Sprite introsprite;
    introsprite.setTexture(introTexture);

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = introTexture.getSize();

    // Center the image
    float posX = (windowSize.x - textureSize.x) / 2.0f;
    float posY = (windowSize.y - textureSize.y) / 2.0f - 50.f; // Slightly upward adjustment
    introsprite.setPosition(posX, posY);



    // Draw the intro image
    window.draw(introsprite);

    // Add text "SkyNavAI" below the image with font size 20
    sf::Font font;
    if (!font.loadFromFile("arial.TTF")) { // Replace with your font file
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("THANK YOU");
    text.setCharacterSize(20);            // Font size 20
    text.setFillColor(sf::Color::Black); // Black text
    text.setStyle(sf::Text::Bold);

    // Center the text below the image
    sf::FloatRect textBounds = text.getLocalBounds();
    float textPosX = (windowSize.x - textBounds.width) / 2.0f;
    float textPosY = posY + textureSize.y + 20.f; // 20px below the image

    text.setPosition(textPosX, textPosY);

    // Draw the text
    window.draw(text);
    
    text.setFont(font);
    text.setString("Knowledge is not only an asset to yourself but a tool that when used wisely can mend the world ");
    text.setCharacterSize(15);            // Font size 20
    text.setFillColor(sf::Color::Black); // Black text
    text.setStyle(sf::Text::Bold);

    // Center the text below the image
    sf::FloatRect textBounds1 = text.getLocalBounds();
    float textPosX1 = (windowSize.x - textBounds.width)/4.0f ;
    float textPosY1 = posY + textureSize.y + 40.f; // 20px below the image

    text.setPosition(textPosX1, textPosY1);

    // Draw the text
    window.draw(text);
}


};
