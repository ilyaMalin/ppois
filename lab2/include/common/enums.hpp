#pragma once

enum class documentStatus
{
    draft,
    registered,
    underReview,
    approved,
    rejected,
    archived
};

enum class taskStatus
{
    newTask,
    assigned,
    inProgress,
    completed,
    overdue,
    cancelled
};

enum class approvalStatus
{
    pending,
    approved,
    rejected,
    revisionRequired
};

enum class workflowStatus
{
    created,
    active,
    completed,
    cancelled
};

enum class userStatus
{
    active,
    blocked,
    disabled
};

enum class archiveStatus
{
    active,
    stored,
    expired,
    destroyed
};

enum class deliveryStatus
{
    prepared,
    sent,
    delivered,
    failed
};
