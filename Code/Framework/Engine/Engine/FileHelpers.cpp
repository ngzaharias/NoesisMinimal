#include "EnginePCH.h"
#include "Engine/FileHelpers.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <Shlobj.h>

str::Path eng::GetAppDataDirectory()
{
#ifdef _WIN32
	wchar_t* wDirectory = nullptr;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &wDirectory);

	size_t* count = nullptr;
	char cDirectory[MAX_PATH] = { 0 };
	wcstombs_s(count, cDirectory, wDirectory, MAX_PATH);

	str::String string = cDirectory;
	return str::Path(std::move(string), "\\ZEngine\\");
#endif
}

str::Path eng::GetAssetsDirectory()
{
#ifdef _WIN32
	const std::filesystem::path directory = std::filesystem::current_path();

	str::Path path = directory.string();
	while (!path.IsEmpty())
	{
		path += "\\Assets";
		if (std::filesystem::is_directory(path.ToChar()))
			return str::Path(path, "\\");

		path = path.GetParent();
		path = path.GetParent();
	}

	return {};
#endif
}

str::Path eng::GetConfigDirectory()
{
#ifdef _WIN32
	const std::filesystem::path directory = std::filesystem::current_path();

	str::Path path = directory.string();
	while (!path.IsEmpty())
	{
		path += "\\Config";
		if (std::filesystem::is_directory(path.ToChar()))
			return str::Path(path, "\\");

		path = path.GetParent();
		path = path.GetParent();
	}

	return {};
#endif
}

str::Path eng::GetCurrentFilepath()
{
#ifdef _WIN32
	const std::filesystem::path directory = std::filesystem::current_path();
	return directory.string();
#endif
}

str::Path eng::GetExecutableFilepath()
{
#ifdef _WIN32
	wchar_t wDirectory[MAX_PATH] = { 0 };
	GetModuleFileNameW(nullptr, wDirectory, MAX_PATH);

	size_t* count = nullptr;
	char cDirectory[MAX_PATH] = { 0 };
	wcstombs_s(count, cDirectory, wDirectory, MAX_PATH);

	str::String string = cDirectory;
	return str::Path(std::move(string));
#endif
}

str::Path eng::GetLevelsDirectory()
{
#ifdef _WIN32
	const std::filesystem::path directory = std::filesystem::current_path();

	str::Path path = directory.string();
	while (!path.IsEmpty())
	{
		path += "\\Levels";
		if (std::filesystem::is_directory(path.ToChar()))
			return str::Path(path, "\\");

		path = path.GetParent();
		path = path.GetParent();
	}

	return {};
#endif
}

str::Path eng::GetThirdPartyDirectory()
{
#ifdef _WIN32
	const std::filesystem::path directory = std::filesystem::current_path();

	str::Path path = directory.string();
	while (!path.IsEmpty())
	{
		path += "\\3rdParty";
		if (std::filesystem::is_directory(path.ToChar()))
			return str::Path(path, "\\");

		path = path.GetParent();
		path = path.GetParent();
	}

	return {};
#endif
}

str::Path eng::GetWorkingDirectory()
{
#ifdef _WIN32
	wchar_t wDirectory[MAX_PATH] = { 0 };
	GetCurrentDirectoryW(MAX_PATH - 1, wDirectory);

	size_t* count = nullptr;
	char cDirectory[MAX_PATH] = { 0 };
	wcstombs_s(count, cDirectory, wDirectory, MAX_PATH);

	str::String string = cDirectory;
	return str::Path(std::move(string), "\\");
#endif
}

bool eng::LoadFileAsBinary(const str::Path& filepath, str::String& out_String)
{
	std::ifstream is;
	std::ostringstream stream;
	is.open(filepath.ToChar(), std::ios::binary);
	if (!is.is_open())
		return false;

	stream << is.rdbuf();
	is.close();

	out_String = stream.str();
	return true;
}

bool eng::LoadFileAsChar(const str::Path& filepath, Array<char>& out_Array)
{
	std::ifstream is;
	is.open(filepath.ToChar(), std::ios::ate | std::ios::binary);
	if (!is.is_open())
		return { };

	const size_t fileSize = (size_t)is.tellg();
	out_Array.Resize(static_cast<int32>(fileSize));
	is.seekg(0);

	is.read(out_Array.GetData(), fileSize);
	is.close();

	return true;
}