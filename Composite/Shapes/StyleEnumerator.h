#pragma once
#include <functional>
#include <boost/optional.hpp>

template <typename Style>
using StyleCallback = std::function<void(Style&)>;

template <typename Style>
using StyleEnumerator = std::function<void(StyleCallback<Style>&&)>;

// Возвращает boost::none в трёх случаях:
//  * когда композитная фигура не имеет дочерних элементов
//  * когда все дочерние элементы имеют boost::none в качестве свойства
//  * когда свойства элементов не одинаковы
// Иначе, возвращается одинаковое свойство стиля
template <typename Style, typename Property>
boost::optional<Property> GetValueIfAllSame(const StyleEnumerator<Style>& enumerate,
	std::function<boost::optional<Property>(const Style&)> && getProperty)
{
	const Style* first = nullptr;
	bool allSame = true;

	enumerate([&](Style& style) {
		if (!first)
		{
			first = &style;
		}
		else if (getProperty(style) != getProperty(*first))
		{
			allSame = false;
		}
	});

	// TODO: можно закэшировать свойство первого элемента
	return (!first || !allSame) ? boost::none : getProperty(*first);
}
