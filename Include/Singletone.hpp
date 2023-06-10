#ifndef UTILS_SINGLETONE_HPP
#define UTILS_SINGLETONE_HPP

template<typename TRealisation>
class Singletone {
private:
	// Приватные копирующий конструктор и оператор присваивания
	// нужны чтобы исключить возможность копирования объекта
    Singletone(const Singletone&);
    Singletone& operator = (const Singletone&);
protected:
    // Конструктор и деструктор доступные только наследникам
    ~Singletone() {}
    Singletone() {}
public:
    // Получение ссылки на экземпляр объекта-синглтон.
    static TRealisation& instance() {
        static TRealisation inst;
        return inst;
    }
};

#endif