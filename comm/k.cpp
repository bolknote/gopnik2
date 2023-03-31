#include <cstdlib>
#include <cstring>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../utils.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int k() {
    // объект героя
    hero *main_hero;
    // объект врага
    hero *enemy = nullptr;
    // объект "братвы"
    hero *lads;

    hero *old_enemy;

    hero *hero1;

    hero *hero2;

    // сообщения функции
    const char *mess[30] = {
            "Чё машешь копытами? Ищи мудака, которого будешь пинать!\n",
            "Враг сдох\n",
            "Ты сдох\n",
            "Ты надыбал %s",
            "А у %sа был косячок.\n",
            "Пиво победителю!\n",
            "Сматывайся, пока мусора не нагрянули!\n",
            "Ты стал настолько крут, что можешь заходить в местный притон!\n",
            "Твою братву отпинали\n",
            "Твоей братве надоело париться из-за такого беспонтового пацана\n",
            "Ты отпинал этого мудака! Пацаны этого не забудут.\n",
            "Твоя понтовость в притоне повысилась на %i\n",
            "Пацаны отвезли тебя в больницу, а то бы ты сдох\n",
            "Вы не надыбали бабла, но ты помог пацанам отбиться от ментов\n",
            "Мотай быстрее, пока охрана не отпинала!\n",
            "Делай отсюда ноги, пока не подошло подкрепление!\n",
            "У тебя нет пистолета\n",
            "Ты чё, в центре города стрелять вздумал?! Мигом менты накроют!\n",
            "Сейчас на тебя замахнулся %s %i уровня\n",
            "Один из твоих корешей запинал одного врага!\n",
            "Один из врагов запинал твоего кореша!\n",
            "К тебе присоединился один твой кореш\n",
            "К тебе присоединился ещё один твой кореш\n",
            "Эти ублюдки запинали всех твоих корешей! Ты просто обязан отомстить!\n",
            "Ты запинал последнего врага и вдруг понял, что стоишь один среди %i трупов\n",
            "Самое время делать ноги, пока никто не спалил!\n",
            "На некоторое время ты схоронился в общаге, где бурно отпраздновал с пацанами\nпобеду неимоверным количеством выпитого пива и выкуренных косяков.\n",
            "Вы запинали этих ублюдков, в который раз доказав свою правоту!\nНакупив бухла, вы отправились в общагу праздновать победу\n",
            "Ты по-чоткому выручил своих корешей! Они этого не забудут!\n",
            "Прошло энное количество дней. Сейчас ты бухой и обдолбанный\nстоишь у стен общаги и вновь готов творить свои гоповские дела!\n"};

    // сообщения при ударе героя
    const char *hero_kick_mess[7] = {
            "Из-за большой ловкости ты можешь ударить ещё раз\n",
            "Точный удар! Ты сломал врагу челюсть!\n",
            "Отличный удар! Ты сломал врагу ногу!\n",
            "Двойной урон! ",
            "Ты ударил врага на %iз. У него осталось %i.\n",
            "Ты промазал\n",
            ""};

    // сообщения при ударе врага
    const char *enemy_kick_mess[7] = {
            "Из-за хорошей ловкости враг может ударить ещё раз\n",
            "Тебе сломали челюсть\n",
            "Тебе сломали ногу\n",
            "Тебе нехило врезали! ",
            "Враг ударил тебя на %iз. У тебя осталось %i.\n",
            "Враг промазал\n",
            "Защита не спасла твои кривые клыки\n"};

    // сообщения при ударе "братвы"
    const char *lads_kick_mess[7] = {
            "Из-за своей хорошей ловкости братва может ударить ещё раз\n",
            "Один из твоих корешей как следует зарядил врагу по челюсти\n",
            "Один из твоих корешей как следует зарядил врагу по ноге\n",
            "",
            "Братва отпинала врага на %iз. У него осталось %i.\n",
            "Братва промазала\n",
            ""};

    // сообщения при ударе кореша
    const char *pal_kick_mess[7] = {
            "Из-за своей хорошей ловкости он может ударить ещё раз\n",
            "Он как следует зарядил врагу по челюсти\n",
            "Он как следует зарядил врагу по ноге\n",
            "",
            "Он ударил врага на %iз. У врага осталось %i.\n",
            "Он промазал\n",
            ""};

    // фразы зрителей
    const char *audience_mess[10] = {
            "Начинают собираться зрители\n",
            "Делайте ваши ставки!\n",
            "Чувак, не подведи! Я на тебя полтинник поставил!\n",
            "Победителя угощаю пивом!\n",
            "Ну чё ты мудишься? Бей давай уже!\n",
            "Давай, двинь ему по ебалу!\n",
            "Чё-то хуёво вы дерётесь.\n",
            "Сильнее бей!\n",
            "Вот вчера тоже одного пинали, а потом подошла его басота...\n",
            "И куда только менты смотрят!\n"};

    // сообщения при выстреле героя
    const char *hero_fire_mess[4] = {
            "Это был хреновый выстрел.",
            "Ты выстрелил и ранил врага на %iз. У него осталось %i.",
            " Осталось %i патронов\n",
            "Чем стрелять собрался? Патронов-то нету\n"};

    int
    // индекс инвентаря
    inv_index,
    // старый район
    old_district,
    // старый уровень
    old_level,
    // режим стрелы
    // индекс противника
    str_enemy_index,
    // индекс союзника
    str_hero_index,
    // кол-во пустых ударов героя
    empty_k_count,
    // урон, на который отпинала
    // братва врага за один удар
    lads_loss,
    // новая локация
    new_loc,
    // добавляемая понтовость
    att;

    int
            i,
            j, flag;

    float
    // относительное здоровье противника
    enemy_rel_health,
    // относительное здоровье героя
    hero_rel_health;

    if (cur_game->active_loc == 0) {
        settextattr(YELLOW);
        printf("%s", mess[0]);

        return 0;
    }

    // стрела #1
    // ---------
    if (cur_game->open_str) {
        // производим поиск нового противника для героя

        old_enemy = cur_game->enemy;

        flag = 0;

        for (i = 0; i < STR_AMOUNT; i++) {
            if (cur_game->str_enemy[i] == old_enemy) {
                // определяем индекс старого противника
                str_enemy_index = i;
            } else {
                // определяем, есть ли ещё живые противники
                if (cur_game->str_enemy[i]->get_health() > 0) {
                    flag = 1;
                }
            }
        }

        if (flag) {
            // рэндомным образом определяем
            // нового противника для главного героя
            while (
                    (old_enemy == cur_game->enemy) ||
                    (cur_game->enemy->get_health() == 0)) {
                cur_game->enemy = cur_game->str_enemy[str_enemy_index = getrandom(-1, STR_AMOUNT - 1)];
            }
        }

        // данная ситуация, по сути, невозможна,
        // но на всякий случай...
        if (cur_game->enemy == nullptr) {
            cur_game->enemy = cur_game->str_enemy[0];
            // printf ("%s","gotofight\n"); // !!!

            goto end_fight;
        }

        settextattr(YELLOW);
        printf(mess[18], cur_game->enemy->get_type(), cur_game->enemy->get_level());
    }
    // end стрела #1
    // -------------

    main_hero = cur_game->main_hero;
    enemy = cur_game->enemy;
    lads = cur_game->lads;

    flag = 1;

    // если дана команда выстрела
    if (strcmp(cur_game->active_cmd, "f") == 0) {
        inv_index = game::search_inv(main_hero, "Пистолет");

        if (main_hero->inv[inv_index].have == 0) {
            settextattr(RED);
            printf("%s", mess[16]);

            return 0;
        } else {
            inv_index = game::search_inv(main_hero, "Глушитель");

            if (
                    (main_hero->inv[inv_index].have == 0) &&
                    (main_hero->station)) {
                settextattr(RED);
                printf("%s", mess[17]);

                return 0;
            } else {
                flag = 0;
            }
        }
    }

    cur_game->num_k++;

    if (cur_game->num_k == 1) {
        main_hero->old_att = main_hero->get_att();
    }

    if (cur_game->active_loc == 1) {
        if (cur_game->num_k == 4) {
            settextattr(WHITE);
            printf("%s", audience_mess[0]);
        }

        if (cur_game->num_k > 4) {
            if (chance(1, 5)) {
                settextattr(YELLOW);
                printf("Голоса из толпы: %s", audience_mess[getrandom(0, 9)]);
            }
        }
    }

    empty_k_count = main_hero->get_level() % 10 + main_hero->get_min_empty_kick_count() + main_hero->district;

    if (flag) {
        // удар героя
        game::kick_realiz(main_hero, enemy, empty_k_count, hero_kick_mess, 10, 12);
    } else {
        // выстрел героя
        game::fire_realiz(main_hero, enemy, empty_k_count, hero_fire_mess, 10, 12);
    }

    // стрела #2
    // ---------
    if (cur_game->open_str) {
        i = 0;

        // производим удары "свободных" союзников
        // по текущему противнику главного героя
        for (j = 0; j < STR_AMOUNT; j++) {
            if (enemy->get_health() == 0) {
                break;
            }

            if (cur_game->str_hero[j]->str_free) {
                settextattr(GREEN);

                if (i == 0) {
                    printf("%s", mess[21]);
                } else {
                    printf("%s", mess[22]);
                }

                game::kick_realiz(
                        cur_game->str_hero[j],
                        enemy, empty_k_count, pal_kick_mess, 10, 12);
                game::kick_realiz(enemy, cur_game->str_hero[j], 10, nullptr, 10, 12);

                if (cur_game->str_hero[j]->get_health() == 0) {
                    cur_game->str_hero[j]->str_free = false;

                    settextattr(RED);
                    printf("%s", mess[20]);
                }

                i++;
            }
        }
    }
    // end стрела #2
    // -------------

    if (
            (cur_game->lads_init) &&
            (lads->get_health() > 0)) {
        if (main_hero->get_att() > 0) {
            lads->empty_kick_count = 0;

            // удар "братвы"
            lads_loss = game::kick_realiz(lads, enemy, 0, lads_kick_mess, 10, 12);

            main_hero->sub_att(lads_loss);
            lads->sub_health(lads_loss);

            if ((lads->get_health() == 0) && (enemy->get_health() > 0)) {
                settextattr(RED);
                printf("%s", mess[8]);
            }
        } else {
            delete cur_game->lads;
            cur_game->lads_init = 0;

            settextattr(YELLOW);
            printf("%s", mess[9]);
        }
    }

    empty_k_count = 10 - (main_hero->get_level() % 10);

    hero_rel_health = (float) main_hero->get_health() / (float) main_hero->get_max_health();
    enemy_rel_health = (float) enemy->get_health() / (float) enemy->get_max_health();

    // усложнение игры в определённой ситуации...
    // -- может что-то даст...
    if (
            (hero_rel_health > 0.8) &&
            (enemy_rel_health < 0.5)) {
        enemy->empty_kick_count = 0;
        empty_k_count = 0;
    }

    // удар врага
    game::kick_realiz(enemy, main_hero, empty_k_count, enemy_kick_mess, 12, 10);

    // стрела #3
    // ---------
    if (cur_game->open_str) {
        j = 0;

        // производим взаимные удары героев басот
        for (i = 0; i < STR_AMOUNT; i++) {
            // пропускаем индекс противника уже
            // задействованного против главного героя
            if (i == str_enemy_index) {
                continue;
            }

            str_hero_index = (i < str_enemy_index) ? (i + 1) : (i);

            // союзник
            hero1 = cur_game->str_hero[str_hero_index];
            // противник
            hero2 = cur_game->str_enemy[i];

            // пропускаем данный индекс, если союзник
            // уже мёртв или "свободен"
            if (
                    (hero1->get_health() == 0) ||
                    (hero1->str_free)) {
                if (hero1->get_health() == 0) {
                    j++;
                }

                continue;
            }

            // пропускаем индекс мёртвого противника
            // и делаем "свободным" текущего союзника
            if (hero2->get_health() == 0) {
                hero1->str_free = true;
                hero1->empty_kick_count = 0;

                continue;
            }

            // реализуем удары
            game::kick_realiz(hero1, hero2, 10, nullptr, 10, 12);
            game::kick_realiz(hero2, hero1, 10, nullptr, 12, 10);

            // выводим сообщение, что запинали союзника
            if (hero1->get_health() == 0) {
                j++;

                settextattr(RED);
                printf("%s", mess[20]);
            }

            // выводим сообщение, что запинали противника
            if (hero2->get_health() == 0) {
                settextattr(GREEN);
                printf("%s", mess[19]);

                // делаем свободным текущего союзника
                hero1->str_free = true;
                hero1->empty_kick_count = 0;
            }
        }

        if (
                (!cur_game->str_dead_mess) &&
                (j == (STR_AMOUNT - 1))) {
            cur_game->str_dead_mess = 1;

            settextattr(RED);
            printf("%s", mess[23]);
        }

        // если текущий противник главного героя мёртв,
        // то проверяем наличие ещё живых противников,
        // чтобы не было преждевременного окончания стрелы
        if (enemy->get_health() == 0) {
            for (i = 0; i < STR_AMOUNT; i++) {
                if (cur_game->str_enemy[i]->get_health() > 0) {
                    enemy = nullptr;

                    break;
                }
            }
        }
    }
    // end стрела #3
    // -------------

    end_fight:

    // враг сдох
    if (
            (enemy != nullptr) &&
            (enemy->get_health() == 0)) {
        cur_game->num_k = 0;
        main_hero->empty_kick_count = 0;

        settextattr(GREEN);
        printf("%s", mess[1]);

        old_level = main_hero->get_level();
        old_district = main_hero->add_exp(
                enemy->get_force() +
                enemy->get_smart() +
                enemy->get_vita() +
                enemy->get_luck());

        // перебор инвентаря противника

        settextattr(BLUE);

        for (i = 0; i < enemy->inv_amount; i++) {
            inv_index = game::search_inv(main_hero, enemy->inv[i].name);

            main_hero->inv[inv_index].have++;
            printf(mess[3], main_hero->inv[inv_index].name);

            // дополнительные заморочки с русским языком...
            if (strcmp(
                    main_hero->inv[inv_index].name +
                    strlen(main_hero->inv[inv_index].name) - 1,
                    "а") == 0) {
                backspace();
                printf("%s", "у");
            }

            printf("%s", "\n");

            // дополнительный перебор инвентаря...
            cur_game->supple_inv_run_over(inv_index);
            /*
                  if (main_hero->inv [inv_index].loss > 2)
                  {
                    cur_game->supple_inv_run_over (inv_index);
                  }
            */
        }

        main_hero->add_money(enemy->get_money());
        main_hero->add_stuff(enemy->get_stuff());
        main_hero->add_beer(1 + main_hero->district);

        // --test
        if (
                (hero_rel_health < 0.25) &&
                (main_hero->get_money() < cur_game->pl[0].members[1].price) &&
                ((main_hero->broken_jaw) ||
                 (main_hero->broken_foot))) {
            main_hero->add_money(getrandom(cur_game->pl[0].members[1].price - main_hero->get_money() - 1,
                                           cur_game->pl[0].members[1].price));
        }

        if (enemy->get_ciga() > 0) {
            printf(mess[4], enemy->get_type());

            main_hero->add_ciga(enemy->get_ciga());
        }

        printf("%s", mess[5]);

        new_loc = 0;

        // борьба на рынке
        if (cur_game->get_stay_mar() == -1) {
            cur_game->set_stay_mar(20);

            settextattr(YELLOW);
            printf("%s", mess[6]);
        }

        // борьба в клубе
        if (cur_game->get_stay_kl() == -1) {
            cur_game->set_stay_kl(40);

            settextattr(YELLOW);
            printf("%s", mess[14]);
        }

        // борьба в метро
        if (cur_game->stay_met == -1) {
            cur_game->stay_met = 10;

            settextattr(YELLOW);
            printf("%s", mess[15]);
        }

        // открытие доступа к притону
        if (
                (old_level != main_hero->get_level()) &&
                ((main_hero->get_level() % 10) >= 5) &&
                (main_hero->station == 0) &&
                (cur_game->get_open_pr() == 0)) {
            cur_game->set_open_pr();

            settextattr(BLUE);
            printf("%s", mess[7]);
        }

        // отпин мудака в притоне
        if (cur_game->get_open_hp()) {
            main_hero->add_att(enemy->get_max_health());
            cur_game->set_open_hp(0);
            new_loc = 4;

            settextattr(YELLOW);
            printf("%s", mess[10]);

            settextattr(BLUE);
            printf(mess[11], enemy->get_max_health());
        }

        // отпин мента в притоне
        if (cur_game->get_open_d()) {
            att = enemy->get_max_health() - (main_hero->old_att - main_hero->get_att());

            if (att > 0) {
                main_hero->set_att(main_hero->old_att);
                main_hero->add_att(att);

                cur_game->set_open_d(0);
                new_loc = 4;

                settextattr(YELLOW);
                printf("%s", mess[13]);

                settextattr(BLUE);
                printf(mess[11], att);
            }
        }

        // стрела
        if (cur_game->open_str) {
            att = 0;

            for (i = 0; i < STR_AMOUNT; i++) {
                att += cur_game->str_enemy[i]->get_max_health();
            }

            att = (int) att / STR_AMOUNT;

            cur_game->open_str = false;
            cur_game->stay_str = 0;

            // делаем героя обдолбанным
            cur_game->stay_kos = 20;
            main_hero->stoned = true;

            // делаем героя бухим
            cur_game->stay_mh = 10;
            main_hero->drunk = true;

            // переносим героя на Петроградскую
            main_hero->station = 4;
            cur_game->new_station();

            // повышаем понтовость
            main_hero->add_att(att);

            // восстанавливаем здоровье героя
            main_hero->add_health(main_hero->get_max_health());
            main_hero->broken_foot = false;
            main_hero->broken_jaw = false;

            settextattr(YELLOW);

            if (cur_game->str_dead_mess) {
                printf(mess[24], STR_AMOUNT * 2 - 1);
                printf("%s", mess[25]);
                printf("%s", mess[26]);
            } else {
                printf("%s", mess[27]);
            }

            printf("%s", mess[28]);

            settextattr(BLUE);
            printf(mess[11], att);

            get_key();

            settextattr(YELLOW);
            printf("%s", mess[29]);

            // корректная очистка
            // ----
            delete[] cur_game->str_hero;
            delete[] cur_game->str_enemy;

            cur_game->str_enemy_amount = 0;
            cur_game->str_hero_amount = 0;
            // ----
        }

        // переход в новый район
        if (old_district != main_hero->district) {
            cur_game->new_district();
            new_loc = 0;
        }

        if (cur_game->enemy_init) {
            // удаляем объект врага
            delete enemy;
            cur_game->enemy_init = 0;
        }

        // удаляем объект "братвы"
        if (cur_game->lads_init) {
            delete cur_game->lads;
            cur_game->lads_init = 0;
        }

        // переход к новой локации
        cur_game->set_loc(new_loc);

        return 0;
    }

    // герой сдох
    if (main_hero->get_health() == 0) {
        cur_game->num_k = 0;
        main_hero->empty_kick_count = 0;

        // проверка условия восстановления героя
        if (
                (!cur_game->end_of_game) &&
                (main_hero->get_att() > 0) &&
                (
                        // 1ое условие
                        (
                                (cur_game->lads_init) &&
                                (lads->get_health() > 0)) ||
                        // 2ое условие
                        (cur_game->get_open_hp()) ||
                        // 3е условие
                        (cur_game->get_open_d()))) {
            if (cur_game->get_stay_mar() == -1) {
                cur_game->set_stay_mar(20);
            }

            if (cur_game->get_stay_kl() == -1) {
                cur_game->set_stay_kl(40);
            }

            if (cur_game->stay_met == -1) {
                cur_game->stay_met = 10;
            }

//            if (cur_game->get_open_hp() == 2) {
//                cur_game->set_open_hp(0);
//            }

//            if (cur_game->get_open_d() == 2) {
//                cur_game->set_open_d(0);
//            }

            main_hero->sub_att(20);

            // восстанавливаем здоровье героя
            main_hero->add_health(main_hero->get_max_health());
            main_hero->broken_foot = false;
            main_hero->broken_jaw = false;

            main_hero->sub_money(main_hero->get_money());
            main_hero->sub_beer(main_hero->get_beer());
            main_hero->sub_stuff(main_hero->get_stuff());
            main_hero->sub_ciga(main_hero->get_ciga());

            settextattr(BLUE);
            printf("%s", mess[12]);

            // переход к новой локации
            cur_game->set_loc(0);
        } else {
            settextattr(RED);
            printf("%s", mess[2]);
            get_key();
        }

        // удаляем объект "братвы"
        if (cur_game->lads_init) {
            delete cur_game->lads;
            cur_game->lads_init = 0;
        }

        if (cur_game->enemy_init) {
            delete enemy;
            cur_game->enemy_init = 0;
        }

        if (cur_game->active_loc == 0) {
            return 0;
        } else {
            return 1;
        }
    }

    return 0;
}
