/*
 * Copyright (C) 2019 Andrea Ravalli (anravalli@gmail.com)
 *
 * This Program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This Program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MonsterChase; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "monsterchase.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MonsterChase game;
    game.show();

    return a.exec();
}
