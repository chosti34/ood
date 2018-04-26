#include "stdafx.h"
#include "../ImageFileStorage.h"
#include <boost/filesystem.hpp>
#include <string>

namespace fs = boost::filesystem;

namespace
{
void CreateDirectoryAndFiles(const std::string& directory)
{
	fs::create_directories(directory + "/a/b.txt");
	std::vector<fs::path> paths = {
		directory + "/a/b.txt/1.txt",
		directory + "/a/b.txt/2.txt",
		directory + "/a/3.dat",
		directory + "/4.dat"
	};
	for (const auto& filepath : paths)
	{
		std::ofstream(filepath.native()) << "test";
	}
}

std::vector<fs::path> GetDirectoryContent(const std::string& directory)
{
	fs::recursive_directory_iterator begin(directory);
	fs::recursive_directory_iterator end;

	std::vector<fs::path> content;
	std::copy_if(begin, end, std::back_inserter(content), [](const fs::path& path) {
		return fs::is_regular_file(path);
	});
	return content;
}
}

BOOST_AUTO_TEST_SUITE(CImageFileStorage)
	BOOST_AUTO_TEST_CASE(when_created_removes_directory_content_if_exists)
	{
		CreateDirectoryAndFiles("tmp");
		const std::vector<fs::path> expectedContent = {
			R"(tmp\4.dat)",
			R"(tmp\a\3.dat)",
			R"(tmp\a\b.txt\1.txt)",
			R"(tmp\a\b.txt\2.txt)"
		};
		BOOST_CHECK(expectedContent == GetDirectoryContent("tmp"));

		ImageFileStorage storage("tmp");
		BOOST_CHECK(!fs::exists("tmp"));
	}

	BOOST_AUTO_TEST_CASE(throws_exception_when_trying_to_add_unexisting_image)
	{
		ImageFileStorage storage("tmp");
		BOOST_REQUIRE_THROW(storage.AddImage("some-unexisting-image.jpg"), std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(throws_exception_when_trying_to_add_image_with_unsupported_file_extension)
	{
		ImageFileStorage storage("tmp");
		{
			std::ofstream("file.txt") << "hello";
		}
		BOOST_CHECK(fs::exists("file.txt"));
		BOOST_REQUIRE_THROW(storage.AddImage("file.txt"), std::invalid_argument);
		fs::remove("file.txt");
	}

	BOOST_AUTO_TEST_CASE(copies_image_file_into_directory_with_new_generated_name)
	{
		ImageFileStorage storage("tmp");

		// Папка не будет создана, пока мы не добавляли картинок
		BOOST_CHECK(!fs::exists("tmp"));

		{
			std::ofstream mockImage("test.jpg");
			mockImage << "hello";
		}

		auto path = storage.AddImage("test.jpg");
		std::ifstream file(path);
		BOOST_CHECK(file.is_open());

		std::string line;
		file >> line;
		BOOST_CHECK(line == "hello");

		fs::remove("test.jpg");
	}

	BOOST_AUTO_TEST_CASE(removes_directory_content_on_destruction)
	{
		{
			ImageFileStorage storage("tmp");
			BOOST_CHECK(!fs::exists("tmp"));
			CreateDirectoryAndFiles("tmp");
			const std::vector<fs::path> expectedContent = {
				R"(tmp\4.dat)",
				R"(tmp\a\3.dat)",
				R"(tmp\a\b.txt\1.txt)",
				R"(tmp\a\b.txt\2.txt)"
			};
			BOOST_CHECK(expectedContent == GetDirectoryContent("tmp"));
		}
		// После удалния объекта папка 'tmp' тоже должна удалиться
		BOOST_CHECK(!fs::exists("tmp"));
	}
BOOST_AUTO_TEST_SUITE_END()
