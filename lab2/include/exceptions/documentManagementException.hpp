#pragma once

#include <stdexcept>
#include <string>

class documentManagementException : public std::runtime_error
{
public:
    explicit documentManagementException(const std::string &message)
        : std::runtime_error(message) {}
};

class documentNotFoundException : public documentManagementException
{
public:
    using documentManagementException::documentManagementException;
};

class invalidDocumentDataException : public documentManagementException
{
public:
    using documentManagementException::documentManagementException;
};

class documentAlreadyRegisteredException : public documentManagementException
{
public:
    using documentManagementException::documentManagementException;
};

class documentAccessDeniedException : public documentManagementException
{
public:
    using documentManagementException::documentManagementException;
};

class invalidDocumentStatusException : public documentManagementException
{
public:
    using documentManagementException::documentManagementException;
};

class documentVersionConflictException : public documentManagementException
{
public:
    using documentManagementException::documentManagementException;
};

class workflowException : public documentManagementException
{
public:
    using documentManagementException::documentManagementException;
};

class approvalRejectedException : public documentManagementException
{
public:
    using documentManagementException::documentManagementException;
};

class taskNotFoundException : public documentManagementException
{
public:
    using documentManagementException::documentManagementException;
};

class taskDeadlineExceededException : public documentManagementException
{
public:
    using documentManagementException::documentManagementException;
};

class invalidDigitalSignatureException : public documentManagementException
{
public:
    using documentManagementException::documentManagementException;
};

class archiveException : public documentManagementException
{
public:
    using documentManagementException::documentManagementException;
};
