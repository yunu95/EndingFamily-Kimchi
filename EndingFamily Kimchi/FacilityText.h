#pragma once
#include "TextImage.h"

class Facility;
class FacilityText :
    public TextImage
{
private:
    Facility* facility = nullptr;
protected:
    virtual void Update() override;
public:
    void SetFacility(Facility* facility);
};

