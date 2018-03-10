#include "stdafx.h"

#include "FileInputStream.h"
#include "FileOutputStream.h"

#include "RLEDecompressInputDataStreamDecorator.h"
#include "RLECompressOutputDataStreamDecorator.h"

#include "DecryptInputDataStreamDecorator.h"
#include "EncryptOutputDataStreamDecorator.h"

void Decorate(std::unique_ptr<IInputDataStream>& input, std::unique_ptr<IOutputDataStream>&, const std::vector<std::string>& args)
{
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cerr << "Invalid arguments count..." << std::endl;
		std::cerr << "Usage: Streams.exe [options] <input file> <output file>" << std::endl;
		return 1;
	}

	try
	{
		std::unique_ptr<IInputDataStream> input = std::make_unique<FileInputStream>(argv[argc - 2]);
		std::unique_ptr<IOutputDataStream> output = std::make_unique<FileOutputStream>(argv[argc - 1]);

		Decorate(input, output, std::vector<std::string>(argv, argv + argc));

		/*std::vector<unsigned> encryptDecoratorSeeds;

		for (int i = 1; i < argc; ++i)
		{
			if (strcmp(argv[i], "--encrypt") == 0)
			{
				if (i >= argc)
				{
					throw std::runtime_error("--encrypt key expected seed");
				}
				encryptDecoratorSeeds.push_back(std::stoi(argv[++i]));
			}
			if (strcmp(argv[i], "--decrypt") == 0)
			{
				if (i >= argc)
				{
					throw std::runtime_error("--decrypt key expected seed");
				}
				input = std::make_unique<DecryptInputDataStreamDecorator>(std::move(input), std::stoi(argv[++i]));
			}
			if (strcmp(argv[i], "--compress") == 0)
			{
				output = std::make_unique<RLECompressOutputDataStreamDecorator>(std::move(output));
			}
			if (strcmp(argv[i], "--decompress") == 0)
			{
				input = std::make_unique<RLEDecompressInputDataStreamDecorator>(std::move(input));
			}
		}

		for (auto it = encryptDecoratorSeeds.rbegin(); it != encryptDecoratorSeeds.rend(); ++it)
		{
			output = std::make_unique<EncryptOutputDataStreamDecorator>(std::move(output), *it);
		}*/

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
