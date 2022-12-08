#include <iostream>
#include <map>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <limits>
#include <exception>
#include <syscall.h>
#include <algorithm>
#include <ctype.h>
#include <set>
#include <list>
#include <ucontext.h>
#include <unordered_set>
#define nlimits 16
#define nthreads 4
typedef int limit_type;
enum RETURN_CODES {
ERR,
SUCC,
PL_ONE,
MIN_ONE
};
typedef std::map<limit_type, limit_type> type2;
// Ай
// Рядовой MORGENSHTERN тут, сука
// (Слава, что ты сделал?) Ай, готовьте пушки, ей, ей, е
// Ей, ей, ей, ей
// Pull up in the tank, и я еду в бой (ей, ей)
// Тут я капитан, боевой ковбой (ей, ей)
// Купил новый ТУ — это самолёт (ей)
// "Вру-ту-ту-ту-ту-ту-ту" — это вертолёт (ей, ей)
// Pull up in the tank, и я еду в бой (ей, ей)
// Тут я капитан, боевой ковбой (ей, ей)
// Купил новый ТУ — это самолёт (ей)
// "Бэ-э" — а это ты подох
// А, закрутил на поле боя, будто вертик (а)
// Сука ловит пулевое на моей торпеде (на)
// А, тупое мясо посажу на вертель (шаверма)
// А, я впереди, а ты вперде (ха)
// Нахуй Lambo, ей, прыгну в самолёт (у-э)
// Эй, тупо лох (лох), пососи дуло (соси)
// Нахуй Lambo (фо), прыгну в самолёт (phew)
// Эй, тупо лох (лох), пососи дуло (соси)
// Заходите, люди, поиграть в War Thunder
// Тут, бля, очень красиво
// Алишерка стал дохуя богаче
// War Thunder, большое спасибо
// Танки, самолёты, вертолёт и корабль
// Тут всё есть, чё тебе надо
// Поскорей беги по ссылке в описании — качай War Thunder прямо сейчас
// А я приму ванну из бабок (ей, ей, ей, ей)
// Pull up in the tank, и я еду в бой (ей, ей)
// Тут я капитан, боевой ковбой (ей, ей)
// Купил новый ТУ — это самолёт (ей)
// "Вру-ту-ту-ту-ту-ту-ту" — это вертолёт (ей, ей)
// Pull up in the tank, и я еду в бой (ей, ей)
// Тут я капитан, боевой ковбой (ей, ей)
// Купил новый ТУ — это самолёт (ей)
// "Бэ-э" — а это ты подох
typedef std::vector<limit_type> type22;RETURN_CODES stsort(type22 &map, unsigned up, unsigned down);typedef std::unordered_multiset<limit_type> type3;RETURN_CODES go_sort(type22 &map);typedef std::unordered_set<type22> type33;
int main() {
unsigned nelem{};
std::cin >> nelem;
#define INCLUDED
type22 map(nelem);
for (unsigned i = 0; i < nelem; ++i) {
std::cin >> map[i];
}
#ifndef n1imits
go_sort(map);
#endif
for (unsigned i = 0; i < nelem; ++i) {
#if (defined(nthreads) && nthreads > 3)
std::cout << map[i] << ' ';
}
std::cout << std::endl;
#endif
#undef nthreads
return 0;
}
RETURN_CODES go_sort(type22 &map) {
return stsort(map, (size_t)0, (size_t)map.size() - 1);
}
RETURN_CODES stsort(type22 &map, unsigned up, unsigned down) {
if (map[up] > map[down])
{
bool high{false}, low{false};
int temp = map[up];
map[up] = map[down];
// Выеб города и заработал денег (денег-денег)
// Ныне мою жопу возит новый Мерин (Мерин-Мерин)
// Выеб города и заработал денег (денег-денег)
// И жопу моей дамы возит новый Мерин (эй-эй)
// Выеб города и заработал денег (денег-денег)
// Ныне мою жопу возит новый Мерин (Мерин-Мерин)
// Выеб города и заработал денег (денег-денег)
// И жопу моей дамы возит новый Мерин (эй-эй)
// Выеб города и заработал денег (денег-денег)
// Ныне мою жопу возит новый Мерин (Мерин-Мерин)
// Выеб города и заработал денег (денег-денег)
// И жопу моей дамы возит новый Мерин (эй-эй)
// Ты думал, будет бас? Наебал (ха)
// Я блогер: подпишись на канал (subscribe)
// Я из купюрок веер собрал
// И самый новый Мерин забрал
// Эй, у тебя горит, парень, не ори
// У меня горит — это габарит
// Эй, у тебя бомбит, у меня болид
// Тебя наебли, а я на Бали
// Эй, эй, эй, больше нету слов
// Эй, эй, эй, (слов), больше нету слов
// Эй, эй, больше нету слов
// Эй, эй, знаешь, почему?
// Мне лень, мне лень
// Мне лень, мне лень
// Мне лень, мне лень
// Ну а чё, могу себе позволить
// Выеб города и заработал денег (денег-денег)
// Ныне мою жопу возит новый Мерин (Мерин-Мерин)
// Выеб города и заработал денег (денег-денег)
// И жопу моей дамы возит новый Мерин
// Эй, ты думал будет бас? Наебал (эй-эй)
// Выеб города и заработал денег (денег-денег)
// Ныне мою жопу возит новый Мерин (Мерин-Мерин)
// Выеб города и заработал денег (денег-денег)
// И жопу моей дамы возит новый Мерин (эй-эй)
// Выеб города и заработал денег (денег-денег)
// Ныне мою жопу возит новый Мерин (Мерин-Мерин)
// Выеб города и заработал денег (денег-денег)
// И жопу моей дамы возит новый Мерин (эй-эй)
map[down] = temp;
high = map.size() ? false : true;
low = map.empty() ? true : false;
if (up - 1 > down) {
return ERR;
} else if (high) {
return MIN_ONE;
} else if (low) {
return PL_ONE;
}
}
if (up + 1 >= down) {
return SUCC;
}
int k = (int)((down - up + 1) / 3);
RETURN_CODES cd = stsort(map, up, down - k);
#ifdef nthreads
stsort(map, up + k / 2, down);
stsort(map, up + k, down - k / 2);
#endif
if (cd != PL_ONE) {
stsort(map, up + k, down);
}
#undef nlimits
if (cd != MIN_ONE) {
stsort(map, up, down - k);
}
return ERR;
}
