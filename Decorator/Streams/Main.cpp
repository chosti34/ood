#include "stdafx.h"
#include "FileInputStream.h"
#include "FileOutputStream.h"
#include "DecompressInputStreamDecorator.h"
#include "CompressOutputStreamDecorator.h"
#include "DecryptInputStreamDecorator.h"
#include "EncryptOutputStreamDecorator.h"

void Decorate(
	std::unique_ptr<IInputDataStream>& input,
	std::unique_ptr<IOutputDataStream>& output,
	std::vector<std::string>&& args)
{
	std::vector<boost::optional<unsigned>> outputOperations;

	for (size_t i = 0; i < args.size(); ++i)
	{
		if (args[i] == "--encrypt")
		{
			if (i + 1 >= args.size())
			{
				throw std::runtime_error("--encrypt key must have value");
			}
			outputOperations.push_back(std::stoi(args[++i]));
		}
		if (args[i] == "--decrypt")
		{
			if (i + 1 >= args.size())
			{
				throw std::runtime_error("--decrypt key must have value");
			}
			input = std::make_unique<DecryptInputStreamDecorator>(std::move(input), std::stoi(args[++i]));
		}
		if (args[i] == "--compress")
		{
			outputOperations.push_back(boost::none);
		}
		if (args[i] == "--decompress")
		{
			input = std::make_unique<DecompressInputStreamDecorator>(std::move(input));
		}
	}

	// Оборачивем декораторы для выходных потоков наизнанку, чтобы сохранить порядок операций
	for (auto it = outputOperations.rbegin(); it != outputOperations.rend(); ++it)
	{
		auto optional = *it;
		if (optional.is_initialized())
		{
			output = std::make_unique<EncryptOutputStreamDecorator>(std::move(output), optional.value());
		}
		else
		{
			output = std::make_unique<CompressOutputStreamDecorator>(std::move(output));
		}
	}
}

void PrintUsageInstructions(std::ostream& output)
{
	output << "Usage: Streams.exe [options] <input file> <output file>\n"
		<< "List of available options:\n"
		<< "--encrypt <seed> - data will be encrypted with specified seed before output operations are performed\n"
		<< "--decrypt <seed> - read data will be decrypted with specified seed\n"
		<< "--compress - data will be compressed via RLE algorithm before output operations are performed\n"
		<< "--decompress - read data compressed via RLE algorithm will be decompressed\n"
		<< "Example usage: Streams.exe --encrypt 3 --encrypt 4 --compress input.txt output.txt\n";
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
		std::unique_ptr<IInputDataStream> input = std::make_unique<FileInputStream>(argv[argc - 2]);
		std::unique_ptr<IOutputDataStream> output = std::make_unique<FileOutputStream>(argv[argc - 1]);
		Decorate(input, output, std::vector<std::string>(argv, argv + argc));

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
