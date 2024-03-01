#pragma once
#include "Screen.h"

namespace tails
{
/**
 * \brief Test class to test functionality of creation, update, destroy, input, etc.
 */
class TestScreen : public Screen
{
public:
    void display() override;
    void update(float deltaTime) override;

protected:
    TextWidget* m_textWidget {nullptr};
};

}
