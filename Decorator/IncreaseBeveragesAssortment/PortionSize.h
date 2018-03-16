#pragma once
#include <string>

// Ввели стандартную и двойную порцию для латте и капучино.
//  Вместо enum'а можно было бы создать подклассы.
enum class CoffeePortionSize
{
	Standard,
	Double
};

// Можно было бы ввести подклассы
enum class MilkshakePortionSize
{
	Small,
	Medium,
	Large
};

std::string ToString(MilkshakePortionSize portionSize);
std::string ToString(CoffeePortionSize portionSize);
