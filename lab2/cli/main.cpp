#include "documents/document.hpp"
#include "documents/contract.hpp"
#include "organization/employee.hpp"
#include "organization/counterparty.hpp"
#include "registration/registrationRecord.hpp"
#include "workflow/task.hpp"
#include "workflow/approval.hpp"
#include "archive/archiveRecord.hpp"
#include <windows.h>
#include <iostream>

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    employee author{"emp-01", "Иван Иванов"};
    author.activateEmployee();

    document agreement{"doc-01", "Договор поставки"};
    agreement.linkEmployee(author);
    agreement.submitDocument();

    counterparty supplier{"cp-01", "ООО Поставщик"};
    contract supplyContract{"contract-01", "Договор поставки №1"};
    supplyContract.linkCounterparty(supplier);
    supplyContract.signContract();

    registrationRecord registration{"reg-01", "Входящий документ"};
    registration.cancelRegistration();

    task reviewTask{"task-01", "Проверить договор"};
    reviewTask.linkEmployee(author);
    reviewTask.completeTask();

    approval approvalRecord{"approval-01", "Согласование договора"};
    approvalRecord.linkEmployee(author);
    approvalRecord.approveDocument();

    archiveRecord archive{"archive-01", "Архив договора"};
    archive.archiveDocument();

    std::cout << "Система электронного документооборота\n";
    std::cout << "Документ: " << agreement.getName() << '\n';
    std::cout << "Автор: " << author.getName() << '\n';
    std::cout << "Статус документа: " << agreement.getStatus() << '\n';
    std::cout << "Статус поручения: " << reviewTask.getStatus() << '\n';
    return 0;
}
