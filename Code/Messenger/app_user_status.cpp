#include "app_user_status.h"
#include <QtGlobal>
#include <iostream>



UserStatus::UserStatus()
{
    status = statusInactive;
    statusBox = nullptr;
    Q_ASSERT(statusBox);
}

UserStatus::UserStatus(QComboBox *ptrStatusBox)
{
    status = statusInactive;

    Q_ASSERT(ptrStatusBox);
    statusBox = ptrStatusBox;

    //set up User Status Box
    for(int i = 0; i < statusMaxIndex; i++) {
//        statusBox->addItem(this->status_name[i]);
    }
}

UserStatus_e UserStatus::GetStatus() {
    return this->status;
}

void UserStatus::Update(int new_status) {
    Q_ASSERT(new_status >= 0 && (new_status < statusMaxIndex));
    this->status = (UserStatus_e)new_status;
//    std::cout << "USER STATUS: new status: " << new_status << " = " << this->status_name[new_status] << std::endl;
}

