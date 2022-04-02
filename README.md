# vk_c
Вариант #15
В Вашем распоряжении массив из 100 млн n-мерных векторов вещественных чисел. На вход подаётся n-мерный вектор. Требуется определить ближайший к нему с точки зрения косинусного расстояния. Реализуйте последовательный алгоритм и параллельный с использованием нескольких потоков.

Пример запуска с дефолтными параметрами (и отключенными флагами):
You have not set dimension, so the launch will be with the default value: 4
If you want to set dimension set -d5 (for example)
You have not set threads quantity, so the launch will be with the best value for your system: 4
If you want to set threads quantity set -p5 (for example)
Number of threads: 4
Time by 4 threads:3.362776
Time by 4 threads:7.105421
Time by 4 threads:7.695555
Time by one thread:15.137928
Time by one thread:15.026632
Time by one thread:17.162121
End of testing!


Среднее время выполнения 4 потокоми: 6.1 сек
Среднее время выполнения одним потоком: 15.8 сек
Замеры проводились на macbook air, m1.