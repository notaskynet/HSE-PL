# Лабораторная работа №6
Срок выполнения: с 2022-11-23 по 2022-11-26. 
Срок сдачи: 2022-11-28.

## Классы в языке Си++

### Ответвление
Необходимо создать ответвление (fork) моего репозитория Lab-06 (название 
оставить без изменения, а видимость поставить приватной). Назничить меня в 
новом репозитории соавтором с правами администратора. Вики, Задачи а также
Проекты отключить.

В локальной копии создавать ветки (branch) по необходимости.

### Этап разработки
Доработать класс `bigint` из лабораторной работы №5.
Класс должен соответствовать следующему интерфейсу:
```
class bigint {
    char   *data;
    size_t  size;
    bool    neg ;
    
  public:
    bigint();
    bigint(const bigint&);
   ~bigint();
    
    explicit bigint(long);
    explicit bigint(unsigned long);
    explicit bigint(const char*);
    
    void print() const;
    
    static bigint add(const bigint& left, const bigint& right);
    static bigint sub(const bigint& left, const bigint& right);
    static bigint mul(const bigint& left, const bigint& right);
    static bigint div(const bigint& left, const bigint& right);
    static bigint div(const bigint& left, const bigint& right, bigint& rest);
    // Lab-06
    static bigint gcd(const bigint& a, const bigint& b);
    static unsigned long Eratosthenes(bigint *sieve, unsigned long size);
    static bigint sqrt(const bigint& value);
};
```
Метод `gcd` реализует алгоритм Евклида. Метод `Eratosthenes` строит решето 
Эратосфена, размера не более `size`, и возвращает количество первых ненулевых
элементов. Метод `sqrt` вычисляет квадратный корень.

Реализацию методов класса вынести в файл исходного кода `bigint.cpp`.

В основной функции, размещенной в файле `main.cpp`, продемонстрировать
применение разработанного класса и его методов.

По выполненной работе составить отчет по ГОСТ 7.32. В отчете отразить изменения,
относительно лабораторной работы №5. Отчет включить в состав исходных кодов
программы в виде файла формата PDF.

### Запрос слияния
Выполнить запрос на слияние (pull request) и назначить меня рецензентом.

