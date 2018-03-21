#pragma once
#include <vector>
#include <memory>
#include "Shape.h"

class PictureDraft final
{
public:
	PictureDraft() = default;
	~PictureDraft() = default;

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
