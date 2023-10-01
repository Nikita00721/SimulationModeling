# SimulationModeling
Репозиторий для курса "Имитационное моделирование". Преподаватель: Духанов А. В.

В задании №2 я реализовал ДПСЧ с использованием линейного конгруэнтного метода, протестировал его графическим способом с помощью гистограммы и статичстическим способом "Хи-квадрат".

Линейный конгруэнтный метод является одним из методов генерации псевдослучайных чисел и основывается на рекуррентном математическом соотношении. 
Основная идея заключается в том, что на каждом шаге генерируется новое число на основе предыдущего числа (начальное число называется семенем) с использованием линейной функции.

Общая формула метода выглядит следующим образом:
X(n+1) = (a * X(n) + c) % m

Где:
X(n) - текущее псевдослучайное число (или состояние генератора) в последовательности.
X(n+1) - следующее псевдослучайное число в последовательности.
"a", "c", и "m" - константы генератора, которые выбираются таким образом, чтобы обеспечить хорошую статистическую случайность.
"%" - операция взятия по модулю.


Графический метод тестирования датчика псевдослучайных чисел с использованием гистограммы помогает визуализировать, насколько равномерно распределены сгенерированные числа в пределах заданного интервала. 
Преимущество графического метода заключается в его интуитивной наглядности. Если гистограмма показывает равномерное распределение, это может быть признаком качественной работы ДПСЧ. 
Однако следует отметить, что этот метод не обнаруживает всех видов неравномерностей и корреляций в последовательности псевдослучайных чисел, поэтому его результаты следует дополнять другими методами тестирования, такими как статистические тесты.
Визуализация моего графическог метода представлена в самой программе.

В качестве ститистического метода я выбрал метод "Хи-квадрат"
Для начала, данные разбиваются на категории или интервалы в соответствии с заданными параметрами. Затем создается таблица сопряженности, в которой учитывается, сколько наблюдений попадает в каждую комбинацию категорий.
Ожидаемые значения в таблице сопряженности вычисляются на основе нулевой гипотезы. Это ожидаемое количество наблюдений в каждой ячейке, если нулевая гипотеза верна.
Расчет статистики Хи-квадрат выполняется с использованием формулы, которая сравнивает наблюдаемые и ожидаемые значения в таблице сопряженности.
Для выяснения, насколько полученное значение статистики Хи-квадрат отличается от того, что можно было бы ожидать случайно, используется таблица распределения Хи-квадрат. Оценивается уровень значимости (p-значение).
Если p-значение меньше заранее выбранного уровня значимости (обычно 0.05), то нулевая гипотеза отвергается. Это означает, что наблюдаемые данные статистически значимо отличаются от ожидаемых данных или модели.
Если p-значение больше уровня значимости, то нет достаточных доказательств для отвержения нулевой гипотезы.
