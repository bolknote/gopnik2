#pragma once

int _ae();   // добавить опыта
int _clsc(); // очистить экран
int _sv();   // показать все характеристики противника
int _w();    // выйти из режима битвы
int a();     // кое-что спросить в притоне
int bmar();  // идти к барыгам
int d();     // идти на дело
int e();     // выйти из игры
int girl();  // завалиться к своей девчонке
int help();  // вывести помощь
int hp();    // отпинать наезжавшего на пацанов в притоне
int i();     // посмотреть описания команд
int inv();   // вывести список инвентаря, которым владеет герой
int jmp();   // перепрыгнуть через турникет

int k();     // удары героя и противника
int k(bool); // удары героя и противника (если флаг true, то герой не будет бить)
int kl();    // идти в клуб
int kos();   // дунуть
int lar();   // зайти в ларёк
int loa();   // загрузить игру
int mar();   // идти на рынок
int mh();    // выпить пива
int meet();  // кадрить девчонку
int met();   // идти в метро
int ob();    // разводить лохов на деньги
int p();     // угостить пацанов пивом
int pon();   // узнать отношение в притоне
int pr();    // идти в притон
int r();     // занять 4 рубля в притоне
int raid();  // узнать про наезд в притоне
int run();   // сбежать
int rep();   // идти к ветиринару
int s();     // показать характеристики героя
int sav();   // сохранить игру
int sl();    // выйти из слэма
int so();    // посмотреть характеристики братвы
int ssl();   // слэмиться
int str();   // идти на стрелу
int stat();  // вывести список станций метро
int stdi();  // прыгнуть со сцены
int sstay(); // отслеживание команд процесса
int sv();    // показать характеристики противника
int svo();   // показать характеристики противника во время стрелки
int t();     // воровать деньги
int tok();   // легально пройти через турникет в метро
int trn();   // идти в качалку
int tus();   // тусовать на дискотеке
int up(int, int, int *);

int v();   // позвать подмогу
int vpl(); // отобразить прайс-лист текущей локации
int w();   // поиск противников
int wes(); // продать ненужные вещи
int x();   // толкнуть хлам
/* --функции по обработке прайс-листов-- */
int h(int, int, int *);   // ветеринар
int b(int, int, int *);   // рынок
int bar(int, int, int *); // клуб
int lar_b(int, int, int *); // ларёк
int bb(int, int, int *);  // барыги
/* --функции по обработке числовых команд-- */
int bsale(int); // продажа вещей
int cstat(int); // выбор станции
int rsl(int);   // слэм
int gamb(); // игровые автоматы
