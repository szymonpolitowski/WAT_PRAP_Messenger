#ifndef USERSTATUS_H
#define USERSTATUS_H
#include "messenger_declarations.h"
#include <QtWidgets/QComboBox>

class UserStatus
{
private:
    UserStatus_e status;
    QComboBox *statusBox;
    const char *status_name[statusMaxIndex] = {"Nieaktywny", "Aktywny", "Nie przeszkadzac"};

public:
    UserStatus();
    UserStatus(QComboBox *ptrStatusBox);

    UserStatus_e GetStatus(void);

    void Update(int new_status);

};

#endif // USERSTATUS_H
