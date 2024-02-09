#ifndef BASEERROR_H
#define BASEERROR_H

#include <QException>

const QPair<int, QString> ERROR_NO(0, "No error");

const QPair<int, QString> ERROR_CODE_UNKNOWN(-1, "Unknown error");

const QPair<int, QString> ERROR_CODE_FILE_NOT_FOUND(11, "File not found");
const QPair<int, QString> ERROR_CODE_FILE_CANNOT_BE_OPENED(12, "File cannot not be opened");

const QPair<int, QString> ERROR_CODE_CONFIG(21, "Invalid config");

class BaseError: public QException
{
public:
    BaseError(int code, const QString &message);

private:
    int code;
    QString message;

    // QException interface
public:
    void raise() const override;
    QException *clone() const override;

    int getCode() const;
    QString getMessage() const;
};

class NoError: public BaseError
{
public:
    NoError();
};

class ErrUnknown: public BaseError
{
public:
    ErrUnknown();
};

#endif // BASEERROR_H
