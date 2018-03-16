#pragma once
#include "IInputDataStream.h"
#include "ByteChunk.h"

#include <deque>
#include <memory>
#include <cassert>
#include <boost/optional/optional.hpp>

// Декоратор для входного потока, тоже являющийся входным потоком.
// Сначала считывает данные при помощи декорируемого объекта, затем
//  производит компрессию данных простейшей вариацией RLE-алгоритма.
class DecompressInputStreamDecorator : public IInputDataStream
{
public:
	DecompressInputStreamDecorator(std::unique_ptr<IInputDataStream> && input);

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	// Пытается распаковать size байт в исходное состояние и записать их в буфер.
	// Возвращает реальное количество распакованных байт.
	std::streamsize UnpackDataFromStreamAndFillBuffer(std::streamsize size);
	boost::optional<ByteChunk> TryReadNextChunk();

	std::unique_ptr<IInputDataStream> m_input;
	std::deque<uint8_t> m_decompressedBuffer;
};
