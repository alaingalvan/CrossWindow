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
	// Title of the dialog
    std::string title;

	// Label used by the Accept button of the dialog
	std::string okLabel;

	// Whether to only interact with folders (for open dialog only)
	bool openFolders = false;

	// Pairs of (File Description, ["jpg", "png", "myFileType"])
    std::vector<std::pair<std::string, std::vector<std::string>>> filters;
};
}