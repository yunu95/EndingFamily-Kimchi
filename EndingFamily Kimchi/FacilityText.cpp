#include "FacilityText.h"
#include "Facility.h"
#include "GlobalFunctions.h"
#include <string>
#include <sstream>
#include <iostream>

void FacilityText::Update()
{
    stringstream sstream;
    if (facility)
    {
        sstream << (facility->isPerson ? "고용가 : " : "구입가격 : ") << doubleToKimchi(facility->GetPrice()+0.999) << endl << endl;
        sstream << (facility->isPerson ? "인원수 : " : "시설수 : ") << facility->facilityNum << (facility->isPerson ? "명" : "개") << endl << endl;
        sstream << (facility->isPerson ? "인당 kps : " : "시설당 kps : ") << endl <<doubleToKps(facility->kps) << endl << endl;
        sstream << "전체 kps : " << endl << doubleToKps(facility->kpsTotal()) << endl << endl;
        sstream << "전체 kps 지분: " << endl << (Facility::kpsGlobal() == 0 ? 0 : facility->kpsTotal() * 100 / Facility::kpsGlobal()) << "%" << endl << endl;
    }
    SetText(width, height, sstream.str());
}
void FacilityText::SetFacility(Facility* facility)
{
    this->facility = facility;
}
