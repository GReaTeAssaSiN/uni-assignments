#ifndef ADDITIONALLISTOFSYMBOLICNAMES_H
#define ADDITIONALLISTOFSYMBOLICNAMES_H

#include <QString>

struct OneSymbolicName
{
    QString name{};
    QString address{};
    //Конструктор по умолчанию.
    OneSymbolicName() = default;
    //Конструктор с параметрами.
    OneSymbolicName(const QString& n, const QString& a)
        : name(n), address(a) {}
};

#endif // ADDITIONALLISTOFSYMBOLICNAMES_H
