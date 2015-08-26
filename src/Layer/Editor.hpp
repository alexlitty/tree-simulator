#include <tree/Layer/PlayerEditor.hpp>

// Constructor.
tree::Layer::PlayerEditor::PlayerEditor(sf::RenderWindow &window, tree::Player *player)
: m_window(window),
  m_player(player),
  m_branch(nullptr),
  m_mode(0)
{

}

// Destructor.
tree::Layer::PlayerEditor::~PlayerEditor()
{
    delete m_branch;
}

// Select new branch to add.
void tree::Layer::PlayerEditor::select(tree::Branch *branch)
{
    delete m_branch;
    m_branch = branch;
}

// Execute the editor.
bool execute(std::vector<sf::Event> &events)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        return false;
    }

    // 
}

// Draw editor elements.
void draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    m_branch->draw(target, states);
}
