#include <tree/Gui/NuggetSelect.hpp>
#include <tree/Math.hpp>
#include <tree/Resource/Color.hpp>

// Constructor.
tree::gui::NuggetSelect::NuggetSelect()
{
    m_preview.setRadius(100.0f);
    tree::Math::centerOrigin(m_preview);
}

// Provides the next available nugget.
void tree::gui::NuggetSelect::nextNugget(tree::nugget &nugget, bool direction)
{
    switch (nugget) {
        case tree::nugget::spore:
            nugget = direction
                ? tree::nugget::plasma
                : tree::nugget::lava;
            break;

        case tree::nugget::plasma:
            nugget = direction
                ? tree::nugget::rock
                : tree::nugget::spore;
            break;

        case tree::nugget::rock:
            nugget = direction
                ? tree::nugget::water
                : tree::nugget::plasma;
            break;

        case tree::nugget::water:
            nugget = direction
                ? tree::nugget::lava
                : tree::nugget::rock;
            break;

        default:
            nugget = direction
                ? tree::nugget::spore
                : tree::nugget::water;
            break;
    }
}

// Act.
bool tree::gui::NuggetSelect::act(tree::Stage &stage)
{
    // Align graphic to lower-right corner.
    m_preview.setPosition(stage.windowSize.x, stage.windowSize.y);

    // Update selected nugget.
    for (sf::Event event : stage.events) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Z
             || event.key.code == sf::Keyboard::X)
            {
                this->nextNugget(
                    stage.nugget,
                    (event.key.code == sf::Keyboard::X)
                );

                m_preview.setFillColor(
                    tree::nuggetColor(stage.nugget)
                );
            }
        }
    }

    // Update preview, based on selected nugget.
    return true;
}

// Draw.
void tree::gui::NuggetSelect::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_preview, states);
}
