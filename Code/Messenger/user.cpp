#include "user.h"

User::User()
{

    m_status = statusInactive;
    m_address.clear();

}

UserStatus_e User::GetStatus(void)
{
    return m_status;
}

void User::SetStatus(UserStatus_e status)
{
    m_status = status;
}

QString User::GetAddress(void)
{
    return m_address;
}

void User::SetAddress(QString address)
{
    m_address = address;
}



