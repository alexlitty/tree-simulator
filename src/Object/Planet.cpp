#include <tree/Engine/Constant.hpp>
#include <tree/Math.hpp>
#include <tree/Object/Planet.hpp>
#include <tree/Resource/Color.hpp>
#include <tree/Resource/Shader.hpp>
#include <tree/Utility/Brush.hpp>

// Main constructor.
tree::Planet::Planet(b2Vec2 position)
{
    this->createsGravity = true;

    // Physics body.
    b2BodyDef bodyDef;
    bodyDef.position = position;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = false;
    setBody(bodyDef);

    // Physical shape.
    b2CircleShape pShape;
    pShape.m_radius = 1.0f;

    // Visual shape.
    m_shape.setPointCount(60);
    m_shape.setRadius(1.0f);

    // Physical fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &pShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.85f;
    fixtureDef.restitution = 0.25f;
    fixtureDef.filter.categoryBits = tree::COLLISION_WORLD;
    fixtureDef.filter.maskBits = -1;
    m_fixture = this->addFixture(fixtureDef);
}

// Constructor, with initial nugget.
tree::Planet::Planet(b2Vec2 position, tree::nugget initialNugget)
: tree::Planet::Planet(position)
{
    nuggets.add(initialNugget);
    this->generate();
}

// Destructor.
tree::Planet::~Planet()
{
    delete m_texture;
}

// Gets the radius of this planet.
float tree::Planet::getRadius() const
{
    return nuggets.total() * 1.0f;
}

// Gets the density of this planet.
float tree::Planet::getNuggetDensity() const
{
    return 3E8 * this->nuggets.total();
}

// Receives a new nugget.
void tree::Planet::receiveNugget(tree::nugget nugget)
{
    this->nuggets.add(nugget, 10);
    this->generate();
}

// Generates this planet.
void tree::Planet::generate()
{
    float radius = this->getRadius();

    // Update physical shape.
    m_fixture->GetShape()->m_radius = radius;
    m_fixture->SetDensity(this->getNuggetDensity());
    this->updateMass();

    // Update physical settings.
    m_torquePower = 3E15;

    // Update visual shape.
    m_shape.setRadius(radius);
    m_shape.setPointCount(
        (std::floor(radius / 30) + 1) * 60
    );
    tree::centerOrigin(m_shape);

    // Calculate new texture size.
    unsigned int textureSize = tree::nextPowerOfTwo(
        static_cast<unsigned int>(radius)
    );

    // New texture required.
    if (!m_texture || textureSize != m_texture->getSize().x) {

        // Delete old texture, create new texture.
        delete m_texture;
        m_texture = new sf::RenderTexture;
        m_texture->create(textureSize, textureSize);
        m_texture->setSmooth(false);

        // Set new texture view.
        m_texture->setView(
            sf::View(
                sf::FloatRect(0, 0, textureSize, textureSize)
            )
        );
    }

    // Clear texture.
    m_texture->clear();
    tree::brush::palette = tree::nuggetPalette(nuggets.list[0].type);
    tree::brush::noise(m_texture);

    // Generate planet, based on nugget composition.
    for (auto comp : nuggets.list) {
        tree::brush::palette = tree::nuggetPalette(comp.type);
        tree::brush::spots(
            m_texture,
            120,
            textureSize / 3,
            textureSize / 2
        );
    }
    m_texture->display();

    // Apply new texture to shape.
    m_shape.setTexture(&m_texture->getTexture(), true);

    // Update highlight.
    m_highlight.setPointCount(m_shape.getPointCount());
    m_highlight.setRadius(m_shape.getRadius());
    tree::centerOrigin(m_highlight);
    m_highlight.setFillColor(sf::Color(0, 0, 0, 25));
    m_highlight.setOutlineColor(sf::Color(225, 225, 225, 50));
    m_highlight.setOutlineThickness(-1.0f);
}

// Draw the planet.
void tree::Planet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    this->addPhysicalTransform(states.transform);

    // Draw planet.
    states.shader = &tree::Shader::Fisheye;
    target.draw(m_shape, states);

    // Draw planet highlight.
    states.shader = nullptr;
    if (this->isNuggetableTarget()) {
        target.draw(m_highlight, states);
    }
}
