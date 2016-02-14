#include <tree/Object/Internal/Editor.hpp>
#include <tree/Object/Branch.hpp>

// Constructor.
tree::PlayerEditor::PlayerEditor(tree::Player *_player)
: player(_player),
  previewActive(false)
{
    currentBranch = player->rootBranch;
    previewBranch = new tree::branch::Wood();
}

// Destructor.
tree::PlayerEditor::~PlayerEditor()
{
    delete previewBranch;
}

// Selects the next branch.
void tree::PlayerEditor::selectNextBranch(tree::BranchDirection direction)
{

    // Next branch is already instantiated. Navigate to it.
    for (auto const &next : currentBranch->children) {
        if (next.first == direction) {
            currentBranch = next.second;
            return;
        }
    }

    // Already previewing branch. Move back to parent first.
    if (previewActive) {
        this->selectParentBranch();
    }

    // Preview branch.
    previewActive = true;
    currentBranch->addChild(direction, previewBranch);
}

// Selects the parent branch.
void tree::PlayerEditor::selectParentBranch()
{
    // Preview branch is selected. Just stop previewing it.
    if (previewActive) {
        currentBranch->removeChild(previewBranch);
        previewActive = false;
        return;
    }

    // A real branch is selected. Select parent.
    if (currentBranch->parent != nullptr) {
        currentBranch = currentBranch->parent;
    }
}

// Execute the editor.
bool tree::PlayerEditor::act(tree::Stage &stage)
{
    // Invalid branch.
    if (currentBranch == nullptr) {
        return false;
    }

    // Look for editing input.
    for (auto event : stage.events) {
        if (event.type == sf::Event::KeyPressed) {

            // Stop editing.
            if (event.key.code == sf::Keyboard::R) {
                return false;
            }

            // Next middle branch.
            else if (event.key.code == sf::Keyboard::Up) {
                
            }
        }
    }

    // Continue editing.
    return true;
}

// Draw editor elements.
void tree::PlayerEditor::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (previewBranch) {
        previewBranch->draw(target, states);
    }
}
