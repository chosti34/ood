#include "stdafx.h"

#include "FileInputStream.h"
#include "FileOutputStream.h"

#include "DecompressInputStreamDecorator.h"
#include "CompressOutputStreamDecorator.h"

#include "DecryptInputStreamDecorator.h"
#include "EncryptOutputStreamDecorator.h"

#include <boost/range/adaptor/reversed.hpp>

namespace
{
enum class OptionType
{
	Encrypt,
	Decrypt,
	Compress,
	Decompress
};

struct DecorateOption
{
	OptionType type;
	boost::optional<unsigned> seed;
};

class DecoratorCreator
{
public:
	DecoratorCreator(
		std::unique_ptr<IInputDataStream>& input,
		std::unique_ptr<IOutputDataStream>& output)
		: m_input(input)
		, m_output(output)
		, m_inputDecorateOptions()
		, m_outputDecorateOptions()
	{
	}

	void ParseOptions(std::vector<std::string>&& options)
	{
		for (auto it = options.begin(); it != options.end(); ++it)
		{
			if (*it == "--encrypt")
			{
				if (std::next(it) == options.end())
				{
					throw std::runtime_error("--encrypt option must have a value");
				}
				m_outputDecorateOptions.emplace_back(DecorateOption{ OptionType::Encrypt, std::stoul(*std::next(it++)) });
			}
			if (*it == "--decrypt")
			{
				if (std::next(it) == options.end())
				{
					throw std::runtime_error("--decrypt option must have a value");
				}
				m_inputDecorateOptions.emplace_back(DecorateOption{ OptionType::Decrypt, std::stoul(*std::next(it++)) });
			}
			if (*it == "--compress")
			{
				m_outputDecorateOptions.emplace_back(DecorateOption{ OptionType::Compress, boost::none });
			}
			if (*it == "--decompress")
			{
				m_inputDecorateOptions.emplace_back(DecorateOption{ OptionType::Decompress, boost::none });
			}
		}
	}

	void DecorateInputStream()
	{
		for (const auto& option : m_inputDecorateOptions)
		{
			if (option.type == OptionType::Decrypt)
			{
				m_input = std::make_unique<DecryptInputStreamDecorator>(std::move(m_input), option.seed.value());
			}
			else if (option.type == OptionType::Decompress)
			{
				m_input = std::make_unique<DecompressInputStreamDecorator>(std::move(m_input));
			}
		}
	}

	void DecorateOutputStream()
	{
		for (const auto& option : boost::adaptors::reverse(m_outputDecorateOptions))
		{
			if (option.type == OptionType::Encrypt)
			{
				m_output = std::make_unique<EncryptOutputStreamDecorator>(std::move(m_output), option.seed.value());
			}
			else if (option.type == OptionType::Compress)
			{
				m_output = std::make_unique<CompressOutputStreamDecorator>(std::move(m_output));
			}
		}
	}

private:
	std::unique_ptr<IInputDataStream>& m_input;
	std::unique_ptr<IOutputDataStream>& m_output;

	std::vector<DecorateOption> m_outputDecorateOptions;
	std::vector<DecorateOption> m_inputDecorateOptions;
};

void PrintUsageInstructions(std::ostream& output)
{
	output << "Usage: Streams.exe [options] <input file> <output file>\n"
		<< "List of available options:\n"
		<< "--encrypt <seed> - data will be encrypted with specified seed before output operations are performed\n"
		<< "--decrypt <seed> - read data will be decrypted with specified seed\n"
		<< "--compress - data will be compressed via RLE algorithm before output operations are performed\n"
		<< "--decompress - read data compressed via RLE algorithm will be decompressed\n"
		<< "Example usage: Streams.exe --encrypt 3 --encrypt 4 --compress input.txt output.txt" << std::endl;
}
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << "Invalid arguments count..." << std::endl;
		PrintUsageInstructions(std::cout);
		return 1;
	}

	try
	{
		std::unique_ptr<IInputDataStream> input = std::make_unique<FileInputStream>(argv[argc - 2u]);
		std::unique_ptr<IOutputDataStream> output = std::make_unique<FileOutputStream>(argv[argc - 1u]);

		DecoratorCreator creator(input, output);
		creator.ParseOptions(std::vector<std::string>(argv + 1u, argv + argc - 2u));

		creator.DecorateInputStream();
		creator.DecorateOutputStream();

		while (!input->IsEOF())
		{
			output->WriteByte(input->ReadByte());
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
