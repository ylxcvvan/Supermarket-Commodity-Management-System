#ifndef MODELUSER_H
#define MODELUSER_H
#include<QString>
class ModelUser
{
private:
    QString Name;
    QString Password;

public:
    ModelUser(QString n,QString pwd="123456");

    const QString& getName();
    const QString& getPassword();
};

#endif // MODELUSER_H
