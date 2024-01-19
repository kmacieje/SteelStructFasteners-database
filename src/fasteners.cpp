#include "fasteners.h"

SFasteners::SFasteners(int itemNo = 0, const QString& element = "", const QString& symbol = "", float weight = 0.0, const QString& material = "", const QString& surface = "", float propClass = 0.0, int din = 0)
    : fItemNo(itemNo), fElement(element), fSymbol(symbol), fWeight(weight),
    fMaterial(material), fSurface(surface), fPropClass(propClass), fDIN(din)
{} //default and parametric constructor

///////////////////////////////////////////////////////////
// These functions are class getters and setters which are fundamentals of the encapsulation principle.
///////////////////////////////////////////////////////////
int SFasteners::getItemNo(void) const
{
    return fItemNo;
}

void SFasteners::setItemNo(int itemNo)
{
    fItemNo = itemNo;
}

QString SFasteners::getElement(void) const
{
    return fElement;
}

void SFasteners::setElement(const QString& element)
{
    fElement = element;
}

QString SFasteners::getSymbol(void) const
{
    return fSymbol;
}

void SFasteners::setSymbol(const QString& symbol)
{
    fSymbol = symbol;
}

float SFasteners::getWeight(void) const
{
    return fWeight;
}

void SFasteners::setWeight(float weight)
{
    fWeight = weight;
}

QString SFasteners::getMaterial(void) const
{
    return fMaterial;
}

void SFasteners::setMaterial(const QString& material)
{
    fMaterial = material;
}

QString SFasteners::getSurface(void) const
{
    return fSurface;
}

void SFasteners::setSurface(const QString& surface)
{
    fSurface = surface;
}

float SFasteners::getPropClass(void) const
{
    return fPropClass;
}

void SFasteners::setPropClass(float propClass)
{
    fPropClass = propClass;
}

int SFasteners::getDIN(void) const
{
    return fDIN;
}

void SFasteners::setDIN(int din)
{
    fDIN = din;
}
