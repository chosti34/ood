#pragma once
#include <string>

// Ввели стандартную и двойную порцию для латте и капучино.
//  Вместо enum'а можно было бы создать подклассы.
enum class CoffeePortionSize
{
	Standard,
	Double
};

// Порции для молочного коктейля: маленькая, средняя и большая.
enum class MilkshakePortionSize
{
	Small,
	Medium,
	Large
};

// Типы чая: зеленый, белый, чёрный, улун.
enum class TeaKind
{
	Green,
	White,
	Black,
	Oolong
};

std::string ToString(MilkshakePortionSize portionSize);
std::string ToString(CoffeePortionSize portionSize);
std::string ToString(TeaKind kind);
