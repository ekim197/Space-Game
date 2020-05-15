#include <SFML/Graphics.hpp>

class Entity{
    sf::RectangleShape body;     // The body of the Enitity (Rectangle for now)
    float speed;                // The speed the entity inherits
    sf::Vector2f velocity;      // The actual movement speed the entity experiences
    bool isBackground;          // Whether the Player can interact with the Entity

public:
    //Constructors and Destructors
    Entity(sf::Texture* texture, sf::Vector2f size = sf::Vector2f(100.0f, 100.0f) , float spd = 0.0f, bool isBg = 0);
    Entity(const Entity& obj) = default;
    ~Entity(){}

    // Getters
    sf::RectangleShape getBody(){ return body; }
    float getSpeed() { return speed; }
    sf::Vector2f getVelocity() { return velocity; }
    bool getIsBg() { return isBackground; }
    sf::Vector2f getPosition(){ return body.getPosition();}

    // Setters
    void setBody(sf::RectangleShape objBody) { body = objBody; }
    void setSpeed(float objSpeed) { speed = objSpeed; }
    void setIsBg(bool objIsBg) { isBackground = objIsBg; }

    //Other
    void update();
    void draw(sf::RenderWindow& window) { window.draw(body); };

};
