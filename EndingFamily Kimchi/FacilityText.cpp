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
        sstream << (facility->isPerson ? "��밡 : " : "���԰��� : ") << doubleToKimchi(facility->GetPrice()+0.999) << endl << endl;
        sstream << (facility->isPerson ? "�ο��� : " : "�ü��� : ") << facility->facilityNum << (facility->isPerson ? "��" : "��") << endl << endl;
        sstream << (facility->isPerson ? "�δ� kps : " : "�ü��� kps : ") << endl <<doubleToKps(facility->kps) << endl << endl;
        sstream << "��ü kps : " << endl << doubleToKps(facility->kpsTotal()) << endl << endl;
        sstream << "��ü kps ����: " << endl << (Facility::kpsGlobal() == 0 ? 0 : facility->kpsTotal() * 100 / Facility::kpsGlobal()) << "%" << endl << endl;
    }
    SetText(width, height, sstream.str());
}
void FacilityText::SetFacility(Facility* facility)
{
    this->facility = facility;
}
