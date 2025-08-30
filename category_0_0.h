#ifndef CATEGORY_____H
#define CATEGORY_____H

#include "category.h"

/////////////////////////////////////////////////
/// \brief The Category_0_0 class
///Класс представления системы проведения соревнований System_0, общий круг
////////////////////////////////////////////////////////////////////
class Category_0_0 : public Category
{
public:
    Category_0_0(
                int,       // id категории
                int,       // id базовой категории (с коьпьютера секретаря)
                int,       // 0 - статус
                QString    // данные (спортсмены, оценки ...)
                );
};

#endif // CATEGORY_____H
