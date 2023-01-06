#ifndef USER_H
#define USER_H

#include <QtGlobal>
#include <QString>
#include "messenger_declarations.h"

class User
{

private:

    UserStatus_e m_status;  /* User Status */
    QString m_address;      /* IP address */

public:
    User();

    UserStatus_e GetStatus(void);
    void SetStatus(UserStatus_e status);

    QString GetAddress(void);
    void SetAddress(QString address);

    bool isNotInactive(void);
    bool isInactive(void);
};

#endif // USER_H
