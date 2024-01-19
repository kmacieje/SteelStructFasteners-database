#ifndef SFASTENERS_H
#define SFASTENERS_H

#include <QString>

class SFasteners
{
private:
    int fItemNo;
    QString fElement;
    QString fSymbol;
    float fWeight;
    QString fMaterial;
    QString fSurface;
    float fPropClass;
    int fDIN;

public:
     SFasteners(int itemNo, const QString& element, const QString& symbol,
                float weight, const QString& material, const QString& surface,
                float propClass, int din);

    int getItemNo() const;
    void setItemNo(int itemNo);

    QString getElement() const;
    void setElement(const QString& element);

    QString getSymbol() const;
    void setSymbol(const QString& symbol);

    float getWeight() const;
    void setWeight(float weight);

    QString getMaterial() const;
    void setMaterial(const QString& material);

    QString getSurface() const;
    void setSurface(const QString& surface);

    float getPropClass() const;
    void setPropClass(float propClass);

    int getDIN() const;
    void setDIN(int din);
};

#endif // SFASTENERS_H
