#pragma once

#include <string>
#include <vector>

namespace xwin
{

enum class MessageType
{
    Warning,
    MessageTypeMax
};

struct MessageDesc
{
    MessageType type; //OK, Error, etc.
};

struct OpenSaveDialogDesc
{
    std::string title;

    std::vector<std::pair<std::string, std::vector<std::string>>> filters;
};
}