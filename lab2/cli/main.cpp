#include "archive/archiveRecord.hpp"
#include "archive/archiveStorage.hpp"
#include "archive/fileStorage.hpp"
#include "documents/document.hpp"
#include "documents/documentType.hpp"
#include "exceptions/documentManagementException.hpp"
#include "organization/department.hpp"
#include "organization/employee.hpp"
#include "registration/registrationRecord.hpp"
#include "workflow/approval.hpp"
#include "workflow/task.hpp"
#include "workflow/workflowDefinition.hpp"
#include "workflow/workflowInstance.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace
{
    int readInt(const std::string &prompt, int minimum = 0)
    {
        while (true)
        {
            std::cout << prompt;
            std::string value;
            if (!std::getline(std::cin, value))
                return -1;

            try
            {
                std::size_t position = 0;
                const int result = std::stoi(value, &position);
                if (position == value.size() && result >= minimum)
                    return result;
            }
            catch (const std::exception &)
            {
            }

            std::cout << "Введите целое число не меньше " << minimum << ".\n";
        }
    }

    std::string readString(const std::string &prompt)
    {
        std::cout << prompt;
        std::string value;
        std::getline(std::cin, value);
        return value;
    }

    void printDepartments(const std::vector<std::unique_ptr<department>> &departments)
    {
        std::cout << "Отделы организации:\n";
        for (std::size_t index = 0; index < departments.size(); ++index)
        {
            std::cout << "  " << index + 1 << ". " << departments[index]->getName()
                      << " (" << (departments[index]->getStatus() == "opendepartment" ? "открыт" : "закрыт")
                      << ")\n";
        }
    }

    int selectDepartment(const std::vector<std::unique_ptr<department>> &departments)
    {
        printDepartments(departments);
        if (departments.empty())
            return -1;

        const int number = readInt("Выберите отдел: ", 1);
        if (number < 1 || number > static_cast<int>(departments.size()))
        {
            std::cout << "Отдел с таким номером не найден.\n";
            return -1;
        }
        return number - 1;
    }

    void addEmployee(
        std::vector<std::unique_ptr<employee>> &employees,
        const std::vector<std::unique_ptr<department>> &departments,
        std::vector<std::size_t> &employeeDepartments)
    {
        std::cout << "\nИнформация о новом сотруднике\n";
        const int departmentIndex = selectDepartment(departments);
        if (departmentIndex < 0)
            return;

        const std::string name = readString("ФИО: ");
        const std::string id = "EMP-" + std::to_string(employees.size() + 1);

        auto newEmployee = std::make_unique<employee>(id, name);
        newEmployee->linkDepartment(*departments[departmentIndex]);
        if (!newEmployee->validateEmployee())
            throw invalidDocumentDataException("Не удалось создать сотрудника: проверьте ФИО.");

        newEmployee->activateEmployee();
        employees.push_back(std::move(newEmployee));
        employeeDepartments.push_back(static_cast<std::size_t>(departmentIndex));
        std::cout << "Сотрудник добавлен. Его ID: " << id << "\n";
    }

    void printEmployees(
        const std::vector<std::unique_ptr<employee>> &employees,
        const std::vector<std::unique_ptr<department>> &departments,
        const std::vector<std::size_t> &employeeDepartments)
    {
        if (employees.empty())
        {
            std::cout << "Сотрудников пока нет.\n";
            return;
        }

        std::cout << "\nСписок сотрудников:\n";
        for (std::size_t index = 0; index < employees.size(); ++index)
        {
            const employee &current = *employees[index];
            std::cout << "  ID " << index + 1 << ": " << current.getName()
                      << ", отдел: " << departments[employeeDepartments[index]]->getName()
                      << ", статус: "
                      << (current.getStatus() == "activateemployee" ? "активен" : "не активен")
                      << "\n";
        }
    }

    int selectEmployee(
        const std::vector<std::unique_ptr<employee>> &employees,
        const std::vector<std::unique_ptr<department>> &departments,
        const std::vector<std::size_t> &employeeDepartments)
    {
        printEmployees(employees, departments, employeeDepartments);
        if (employees.empty())
            return -1;

        const int id = readInt("Введите ID сотрудника: ", 1);
        if (id < 1 || id > static_cast<int>(employees.size()))
        {
            std::cout << "Сотрудник с таким ID не найден.\n";
            return -1;
        }
        return id - 1;
    }

    bool hasApproval(
        std::size_t documentIndex,
        const std::vector<std::unique_ptr<approval>> &approvals,
        const std::vector<std::size_t> &approvalDocuments)
    {
        for (std::size_t index = 0; index < approvalDocuments.size(); ++index)
        {
            if (approvalDocuments[index] == documentIndex &&
                approvals[index]->getStatus() == "approve")
                return true;
        }
        return false;
    }

    bool hasRegistration(
        std::size_t documentIndex,
        const std::vector<std::size_t> &registrationDocuments)
    {
        for (const std::size_t registeredDocument : registrationDocuments)
            if (registeredDocument == documentIndex)
                return true;
        return false;
    }

    bool hasArchive(
        std::size_t documentIndex,
        const std::vector<std::size_t> &archiveDocuments)
    {
        for (const std::size_t archivedDocument : archiveDocuments)
            if (archivedDocument == documentIndex)
                return true;
        return false;
    }

    std::string documentStatusName(
        std::size_t documentIndex,
        const document &current,
        const std::vector<std::unique_ptr<approval>> &approvals,
        const std::vector<std::size_t> &approvalDocuments,
        const std::vector<std::size_t> &registrationDocuments,
        const std::vector<std::size_t> &archiveDocuments)
    {
        if (hasArchive(documentIndex, archiveDocuments))
            return "в архиве";
        if (hasRegistration(documentIndex, registrationDocuments))
            return "зарегистрирован";
        if (hasApproval(documentIndex, approvals, approvalDocuments))
            return "согласован";
        if (current.getStatus() == "submit")
            return "на согласовании";
        return "черновик";
    }

    void printDocuments(
        const std::vector<std::unique_ptr<document>> &documents,
        const std::vector<std::unique_ptr<approval>> &approvals,
        const std::vector<std::size_t> &approvalDocuments,
        const std::vector<std::size_t> &registrationDocuments,
        const std::vector<std::size_t> &archiveDocuments)
    {
        if (documents.empty())
        {
            std::cout << "Документов пока нет.\n";
            return;
        }

        std::cout << "\nСписок документов:\n";
        for (std::size_t index = 0; index < documents.size(); ++index)
        {
            std::cout << "  ID " << index + 1 << ": " << documents[index]->getName()
                      << ", статус: "
                      << documentStatusName(index, *documents[index], approvals,
                                            approvalDocuments, registrationDocuments,
                                            archiveDocuments)
                      << "\n";
        }
    }

    int selectDocument(
        const std::vector<std::unique_ptr<document>> &documents,
        const std::vector<std::unique_ptr<approval>> &approvals,
        const std::vector<std::size_t> &approvalDocuments,
        const std::vector<std::size_t> &registrationDocuments,
        const std::vector<std::size_t> &archiveDocuments)
    {
        printDocuments(documents, approvals, approvalDocuments,
                       registrationDocuments, archiveDocuments);
        if (documents.empty())
            return -1;

        const int id = readInt("Введите ID документа: ", 1);
        if (id < 1 || id > static_cast<int>(documents.size()))
        {
            std::cout << "Документ с таким ID не найден.\n";
            return -1;
        }
        return id - 1;
    }

    void createDocument(
        std::vector<std::unique_ptr<document>> &documents,
        const std::vector<std::unique_ptr<employee>> &employees,
        const std::vector<std::unique_ptr<department>> &departments,
        const std::vector<std::size_t> &employeeDepartments)
    {
        const int employeeIndex = selectEmployee(employees, departments, employeeDepartments);
        if (employeeIndex < 0)
            return;

        const std::string name = readString("Название документа: ");
        const std::string id = "DOC-" + std::to_string(documents.size() + 1);
        auto newDocument = std::make_unique<document>(id, name);
        newDocument->linkEmployee(*employees[employeeIndex]);

        if (!newDocument->prepareDocument())
            throw invalidDocumentDataException("Название документа не может быть пустым.");

        documents.push_back(std::move(newDocument));
        std::cout << "Документ создан. Его ID: " << id << "\n";
    }

    void submitDocument(
        std::vector<std::unique_ptr<document>> &documents,
        std::vector<std::unique_ptr<workflowInstance>> &workflows,
        const std::vector<std::unique_ptr<approval>> &approvals,
        const std::vector<std::size_t> &approvalDocuments,
        const std::vector<std::size_t> &registrationDocuments,
        const std::vector<std::size_t> &archiveDocuments)
    {
        const int documentIndex = selectDocument(documents, approvals, approvalDocuments,
                                                 registrationDocuments, archiveDocuments);
        if (documentIndex < 0)
            return;

        document &selected = *documents[documentIndex];
        if (!selected.prepareDocument())
            throw invalidDocumentDataException("Документ содержит некорректные данные.");
        if (!selected.getStatus().empty())
            throw invalidDocumentStatusException("Документ уже отправлен на обработку.");

        const std::string id = "WF-" + std::to_string(workflows.size() + 1);
        auto workflow = std::make_unique<workflowInstance>(id, selected.getName());
        workflow->linkDocument(selected);
        if (!workflow->validateWorkflowInstance())
            throw workflowException("Не удалось создать процесс согласования.");

        selected.submitDocument();
        workflow->startWorkflow();
        workflows.push_back(std::move(workflow));
        std::cout << "Документ отправлен на согласование.\n";
    }

    void printWorkflows(const std::vector<std::unique_ptr<workflowInstance>> &workflows)
    {
        if (workflows.empty())
        {
            std::cout << "Активных процессов согласования нет.\n";
            return;
        }

        std::cout << "\nПроцессы согласования:\n";
        for (const auto &workflow : workflows)
        {
            std::cout << "  " << workflow->getName() << " — "
                      << (workflow->getStatus() == "start" ? "запущен" : "не запущен")
                      << "\n";
        }
    }

    void approveDocument(
        const std::vector<std::unique_ptr<document>> &documents,
        const std::vector<std::unique_ptr<employee>> &employees,
        const std::vector<std::unique_ptr<department>> &departments,
        const std::vector<std::size_t> &employeeDepartments,
        std::vector<std::unique_ptr<approval>> &approvals,
        std::vector<std::size_t> &approvalDocuments,
        const std::vector<std::size_t> &registrationDocuments,
        const std::vector<std::size_t> &archiveDocuments)
    {
        const int documentIndex = selectDocument(documents, approvals, approvalDocuments,
                                                 registrationDocuments, archiveDocuments);
        if (documentIndex < 0)
            return;

        const document &selected = *documents[documentIndex];
        if (selected.getStatus() != "submit")
            throw workflowException("Сначала отправьте документ на согласование.");
        if (hasApproval(static_cast<std::size_t>(documentIndex), approvals, approvalDocuments))
            throw invalidDocumentStatusException("Документ уже был согласован.");

        const int employeeIndex = selectEmployee(employees, departments, employeeDepartments);
        if (employeeIndex < 0)
            return;

        const std::string id = "APR-" + std::to_string(approvals.size() + 1);
        auto newApproval = std::make_unique<approval>(id, selected.getName());
        newApproval->linkEmployee(*employees[employeeIndex]);
        if (!newApproval->validateApproval())
            throw workflowException("Не удалось создать запись согласования.");

        newApproval->approveDocument();
        approvals.push_back(std::move(newApproval));
        approvalDocuments.push_back(static_cast<std::size_t>(documentIndex));
        std::cout << "Документ согласован сотрудником: "
                  << employees[employeeIndex]->getName() << ".\n";
    }

    void printApprovals(
        const std::vector<std::unique_ptr<approval>> &approvals,
        const std::vector<std::size_t> &approvalDocuments,
        const std::vector<std::unique_ptr<document>> &documents)
    {
        if (approvals.empty())
        {
            std::cout << "Согласованных документов пока нет.\n";
            return;
        }

        std::cout << "\nСогласования:\n";
        for (std::size_t index = 0; index < approvals.size(); ++index)
        {
            std::cout << "  Документ: " << documents[approvalDocuments[index]]->getName()
                      << ", статус: "
                      << (approvals[index]->getStatus() == "approve" ? "согласован" : "ожидает")
                      << "\n";
        }
    }

    void registerDocument(
        const std::vector<std::unique_ptr<document>> &documents,
        const std::vector<std::unique_ptr<approval>> &approvals,
        const std::vector<std::size_t> &approvalDocuments,
        std::vector<std::unique_ptr<registrationRecord>> &registrations,
        std::vector<std::size_t> &registrationDocuments,
        const std::vector<std::size_t> &archiveDocuments)
    {
        const int documentIndex = selectDocument(documents, approvals, approvalDocuments,
                                                 registrationDocuments, archiveDocuments);
        if (documentIndex < 0)
            return;

        const std::size_t index = static_cast<std::size_t>(documentIndex);
        if (!hasApproval(index, approvals, approvalDocuments))
            throw workflowException("Перед регистрацией документ должен быть согласован.");
        if (hasRegistration(index, registrationDocuments))
            throw documentAlreadyRegisteredException("Документ уже зарегистрирован.");

        const std::string id = "REG-" + std::to_string(registrations.size() + 1);
        auto record = std::make_unique<registrationRecord>(id, documents[index]->getName());
        record->linkDocument(*documents[index]);
        if (!record->validateRegistration())
            throw invalidDocumentDataException("Не удалось создать регистрационную запись.");

        registrations.push_back(std::move(record));
        registrationDocuments.push_back(index);
        std::cout << "Документ зарегистрирован. Номер записи: " << id << "\n";
    }

    void printRegistrations(
        const std::vector<std::unique_ptr<registrationRecord>> &registrations,
        const std::vector<std::size_t> &registrationDocuments,
        const std::vector<std::unique_ptr<document>> &documents)
    {
        if (registrations.empty())
        {
            std::cout << "Зарегистрированных документов пока нет.\n";
            return;
        }

        std::cout << "\nЖурнал регистрации:\n";
        for (std::size_t index = 0; index < registrations.size(); ++index)
        {
            std::cout << "  " << registrations[index]->getName()
                      << ", документ: " << documents[registrationDocuments[index]]->getName()
                      << ", статус: "
                      << (registrations[index]->getStatus().empty() ? "действует" : "отменена")
                      << "\n";
        }
    }

    void createTask(
        std::vector<std::unique_ptr<task>> &tasks,
        const std::vector<std::unique_ptr<employee>> &employees,
        const std::vector<std::unique_ptr<department>> &departments,
        const std::vector<std::size_t> &employeeDepartments,
        std::vector<std::size_t> &taskEmployees)
    {
        const int employeeIndex = selectEmployee(employees, departments, employeeDepartments);
        if (employeeIndex < 0)
            return;

        const std::string name = readString("Содержание задачи: ");
        const std::string id = "TASK-" + std::to_string(tasks.size() + 1);
        auto newTask = std::make_unique<task>(id, name);
        newTask->linkEmployee(*employees[employeeIndex]);
        if (!newTask->validateTask())
            throw invalidDocumentDataException("Содержание задачи не может быть пустым.");

        tasks.push_back(std::move(newTask));
        taskEmployees.push_back(static_cast<std::size_t>(employeeIndex));
        std::cout << "Задача создана. Ее ID: " << id << "\n";
    }

    void printTasks(
        const std::vector<std::unique_ptr<task>> &tasks,
        const std::vector<std::unique_ptr<employee>> &employees,
        const std::vector<std::size_t> &taskEmployees)
    {
        if (tasks.empty())
        {
            std::cout << "Задач пока нет.\n";
            return;
        }

        std::cout << "\nСписок задач:\n";
        for (std::size_t index = 0; index < tasks.size(); ++index)
        {
            std::cout << "  ID " << index + 1 << ": " << tasks[index]->getName()
                      << ", исполнитель: " << employees[taskEmployees[index]]->getName()
                      << ", статус: "
                      << (tasks[index]->getStatus() == "complete" ? "выполнена" : "новая")
                      << "\n";
        }
    }

    void completeTask(std::vector<std::unique_ptr<task>> &tasks)
    {
        if (tasks.empty())
        {
            std::cout << "Задач пока нет.\n";
            return;
        }

        std::cout << "\nСписок задач:\n";
        for (std::size_t index = 0; index < tasks.size(); ++index)
        {
            std::cout << "  ID " << index + 1 << ": " << tasks[index]->getName() << "\n";
        }

        const int id = readInt("Введите ID задачи для завершения: ", 1);
        if (id < 1 || id > static_cast<int>(tasks.size()))
            throw taskNotFoundException("Задача с таким ID не найдена.");
        if (tasks[id - 1]->getStatus() == "complete")
        {
            std::cout << "Задача уже выполнена.\n";
            return;
        }

        tasks[id - 1]->completeTask();
        std::cout << "Задача отмечена как выполненная.\n";
    }

    void archiveDocument(
        const std::vector<std::unique_ptr<document>> &documents,
        const std::vector<std::unique_ptr<approval>> &approvals,
        const std::vector<std::size_t> &approvalDocuments,
        const std::vector<std::size_t> &registrationDocuments,
        std::vector<std::unique_ptr<archiveRecord>> &archiveRecords,
        std::vector<std::size_t> &archiveDocuments)
    {
        const int documentIndex = selectDocument(documents, approvals, approvalDocuments,
                                                 registrationDocuments, archiveDocuments);
        if (documentIndex < 0)
            return;

        const std::size_t index = static_cast<std::size_t>(documentIndex);
        if (!hasRegistration(index, registrationDocuments))
            throw archiveException("В архив можно поместить только зарегистрированный документ.");
        if (hasArchive(index, archiveDocuments))
            throw archiveException("Документ уже находится в архиве.");

        const std::string id = "ARC-" + std::to_string(archiveRecords.size() + 1);
        auto record = std::make_unique<archiveRecord>(id, documents[index]->getName());
        record->linkDocument(*documents[index]);
        if (!record->validateArchiveRecord())
            throw archiveException("Не удалось создать архивную запись.");

        record->archiveDocument();
        archiveRecords.push_back(std::move(record));
        archiveDocuments.push_back(index);
        std::cout << "Документ помещен в архив.\n";
    }

    void printArchive(
        const std::vector<std::unique_ptr<archiveRecord>> &archiveRecords,
        const std::vector<std::size_t> &archiveDocuments,
        const std::vector<std::unique_ptr<document>> &documents)
    {
        if (archiveRecords.empty())
        {
            std::cout << "Архив пока пуст.\n";
            return;
        }

        std::cout << "\nАрхив документов:\n";
        for (std::size_t index = 0; index < archiveRecords.size(); ++index)
        {
            std::cout << "  " << archiveRecords[index]->getName()
                      << ", документ: " << documents[archiveDocuments[index]]->getName()
                      << ", статус: "
                      << (archiveRecords[index]->getStatus() == "archive" ? "в архиве" : "не архивирован")
                      << "\n";
        }
    }
}

int main()
{
    std::vector<std::unique_ptr<department>> departments;
    const std::vector<std::string> departmentNames = {
        "Канцелярия", "Юридический отдел", "Бухгалтерия"};

    for (std::size_t index = 0; index < departmentNames.size(); ++index)
    {
        const std::string id = "DEP-" + std::to_string(index + 1);
        auto newDepartment = std::make_unique<department>(id, departmentNames[index]);
        if (newDepartment->validateDepartment())
        {
            newDepartment->openDepartment();
            departments.push_back(std::move(newDepartment));
        }
    }

    workflowDefinition standardWorkflow("WF-DEFAULT", "Стандартное согласование");
    standardWorkflow.publishWorkflow();
    documentType standardDocumentType("TYPE-DEFAULT", "Внутренний документ");
    standardDocumentType.linkWorkflowDefinition(standardWorkflow);
    standardDocumentType.enableType();

    fileStorage mainStorage("FS-DEFAULT", "Основное хранилище");
    mainStorage.checkStorageCapacity();
    archiveStorage mainArchive("ARCH-DEFAULT", "Архив организации");
    mainArchive.linkFileStorage(mainStorage);
    mainArchive.openArchiveStorage();

    std::vector<std::unique_ptr<employee>> employees;
    std::vector<std::size_t> employeeDepartments;
    std::vector<std::unique_ptr<document>> documents;
    std::vector<std::unique_ptr<workflowInstance>> workflows;
    std::vector<std::unique_ptr<approval>> approvals;
    std::vector<std::size_t> approvalDocuments;
    std::vector<std::unique_ptr<registrationRecord>> registrations;
    std::vector<std::size_t> registrationDocuments;
    std::vector<std::unique_ptr<task>> tasks;
    std::vector<std::size_t> taskEmployees;
    std::vector<std::unique_ptr<archiveRecord>> archiveRecords;
    std::vector<std::size_t> archiveDocuments;

    std::cout << "Система электронного документооборота\n";
    std::cout << "Тип документа по умолчанию: " << standardDocumentType.getName() << "\n";
    try
    {
        addEmployee(employees, departments, employeeDepartments);
    }
    catch (const documentManagementException &error)
    {
        std::cout << "Ошибка: " << error.what() << "\n";
    }

    bool running = true;
    while (running && std::cin.good())
    {
        std::cout << "\n1. Добавить сотрудника\n"
                  << "2. Показать сотрудников\n"
                  << "3. Создать документ\n"
                  << "4. Показать документы\n"
                  << "5. Отправить документ на согласование\n"
                  << "6. Показать ход обработки документов\n"
                  << "7. Согласовать документ\n"
                  << "8. Зарегистрировать документ\n"
                  << "9. Показать журнал регистрации\n"
                  << "10. Создать задачу сотруднику\n"
                  << "11. Показать задачи\n"
                  << "12. Завершить задачу\n"
                  << "13. Поместить документ в архив\n"
                  << "14. Показать архив\n"
                  << "0. Выход\n";
        const int command = readInt("Выберите действие: ", 0);

        try
        {
            if (command == 1)
            {
                addEmployee(employees, departments, employeeDepartments);
            }
            else if (command == 2)
            {
                printEmployees(employees, departments, employeeDepartments);
            }
            else if (command == 3)
            {
                createDocument(documents, employees, departments, employeeDepartments);
            }
            else if (command == 4)
            {
                printDocuments(documents, approvals, approvalDocuments,
                               registrationDocuments, archiveDocuments);
            }
            else if (command == 5)
            {
                submitDocument(documents, workflows, approvals, approvalDocuments,
                               registrationDocuments, archiveDocuments);
            }
            else if (command == 6)
            {
                printWorkflows(workflows);
                printApprovals(approvals, approvalDocuments, documents);
            }
            else if (command == 7)
            {
                approveDocument(documents, employees, departments, employeeDepartments,
                                approvals, approvalDocuments, registrationDocuments,
                                archiveDocuments);
            }
            else if (command == 8)
            {
                registerDocument(documents, approvals, approvalDocuments, registrations,
                                 registrationDocuments, archiveDocuments);
            }
            else if (command == 9)
            {
                printRegistrations(registrations, registrationDocuments, documents);
            }
            else if (command == 10)
            {
                createTask(tasks, employees, departments, employeeDepartments, taskEmployees);
            }
            else if (command == 11)
            {
                printTasks(tasks, employees, taskEmployees);
            }
            else if (command == 12)
            {
                completeTask(tasks);
            }
            else if (command == 13)
            {
                archiveDocument(documents, approvals, approvalDocuments,
                                registrationDocuments, archiveRecords, archiveDocuments);
            }
            else if (command == 14)
            {
                printArchive(archiveRecords, archiveDocuments, documents);
            }
            else if (command == 0 || command == -1)
            {
                running = false;
            }
            else
            {
                std::cout << "Неизвестная команда.\n";
            }
        }
        catch (const documentManagementException &error)
        {
            std::cout << "Ошибка: " << error.what() << "\n";
        }
    }

    std::cout << "Работа системы завершена.\n";
    return 0;
}
