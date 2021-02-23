#pragma once
#include "GameObject.h"
class Text : public GameObject
{
public:

    enum MODE
    {
        STATIC_WORLDTEXT,
        DIALOGUE_WORLDTEXT,
        STATIC_SCREENTEXT,
        DIALOGUE_SCREENTEXT,
        TOTAL_MODE
    };

    Text();
    ~Text();

    virtual void Draw(Renderer* renderer, bool EnableLight) override;
    void SetMode(MODE mode);
    void SetText(std::string text);
    void SetTimer(float timer);
    void SetColor(Color color);

    void StartTimer();
    void UpdateTimer(double dt);
    void RestartTimer();
    void Setindex(int index);

    float getTimer();
    int getindex();
    std::string GetText();
private:
    bool countdown;
    float timer;
    int index;
    std::string text;
    Color color;
    MODE mode;
};
