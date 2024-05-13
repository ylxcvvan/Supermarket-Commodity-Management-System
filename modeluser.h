#ifndef MODELUSER_H
#define MODELUSER_H
#include<QString>
class ModelUser
{
private:
    QString name;
    QString password;

public:
    ModelUser();

    const QString& getName();
    const QString& getPassword();
};

#endif // MODELUSER_H
