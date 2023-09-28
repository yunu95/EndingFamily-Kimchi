#pragma once


// author : ±èÇöÀç
class ISelectable
{
public:
    virtual void Highlight() = 0;
    virtual void Dehightlight() = 0;
    virtual void Select() = 0;
    virtual void SetEnabled(bool enabled) = 0;
    virtual bool GetEnabled() = 0;
};
