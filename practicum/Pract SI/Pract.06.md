﻿
# Задачи

**Задача 1.** В една софтуерна компания се провежда турнир по белот с благотворителна цел.

Трябва да създадете клас **BelotTournament**, който да провежда турнира.
За да бъде проведен един турнир, трябва да има отбори от софтуерни инженери. Всеки отбор се състои от 2 софтуерни инженери. Всеки **софтуерен инженер** има име (низ с произволна дължина), позиция (низ с произволна дължина) и заплата (цяло число). 

Броят на отборите трябва да е четен и по-голям от 2. При опит да започне турнира с нечетен брой отбори, последният добавен отбор бива премахнат преди началото на турнира.

Когато имато достатъчно отбори, чиито участници са валидни, тогава турнирът може да започне. Отборите биват разпределени на случаен принцип. След това се провежда дуел между отборите. Един дуел може да има максимално 3 рунда, като първият отбор достигнал 2 победи, печели дуела. Един рунд се провежда като за всеки отбор се четат точки от конзолата, които се добавя към общите точки на отбора. Рунда печели отборът, който първи достигне число 151. Това се повтаря за всички печеливши отбори, докато не остане един единствен отбор, който е победител. Тъй като турнирът е с благотворителна цел, всеки от загубилите участници дарява 2% от заплатата си, а 1% дават на всеки от печелившия отбор. Да се пресметне колко пари е събрала фирмата от турнира за дарение.