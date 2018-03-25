#pragma once
#include <vector>
#include <memory>
#include "Shape.h"
#include <boost/iterator/indirect_iterator.hpp>

class PictureDraft final
{
	using Storage = std::vector<std::unique_ptr<Shape>>;

public:
	PictureDraft() = default;
	~PictureDraft() = default;

	typedef boost::indirect_iterator<Storage::const_iterator, const Shape&> ConstIterator;

	ConstIterator begin()const;
	ConstIterator end()const;

	// Разрешаем создание объекта из временного экземпляра
	PictureDraft(PictureDraft&&) = default;
	PictureDraft& operator=(PictureDraft&&) = default;

	// Запрещаем копирование и присваивание объекта
	PictureDraft(const PictureDraft&) = delete;
	PictureDraft& operator=(const PictureDraft&) = delete;

	bool IsEmpty()const;
	void AddShape(std::unique_ptr<Shape>&& shape);

private:
	std::vector<std::unique_ptr<Shape>> m_shapes;
};

inline PictureDraft::ConstIterator begin(const PictureDraft& draft)
{
	return draft.begin();
}

inline PictureDraft::ConstIterator end(const PictureDraft& draft)
{
	return draft.end();
}
