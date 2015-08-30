#include <tree/Object/Internal/Editor.hpp>

// Constructor.
tree::PlayerEditor::PlayerEditor(tree::Player *player)
: m_player(player),
  m_branch(nullptr),
  m_mode(0)
{

}

// Destructor.
tree::PlayerEditor::~PlayerEditor()
{
    delete m_branch;
}

// Select new branch to add.
void tree::PlayerEditor::select(tree::Branch *branch)
{
    delete m_branch;
    m_branch = branch;
}

// Execute the editor.
bool tree::PlayerEditor::act(tree::Stage &stage)
{
    // Stop the editor.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        return false;
    }

    // Preview new branch.
    if (m_branch) {
        m_branch->preview(
            m_player,
            m_player->getPosition(),
            stage.mouse
        );
    }
    return true;
}

// Draw editor elements.
void tree::PlayerEditor::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    m_branch->draw(target, states);
}
