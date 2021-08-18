#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/screen1ViewBase.hpp>
#include <gui/screen1_screen/screen1Presenter.hpp>

class screen1View : public screen1ViewBase
{
public:
    screen1View();
    virtual ~screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREEN1VIEW_HPP
